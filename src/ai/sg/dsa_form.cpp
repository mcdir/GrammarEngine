// -----------------------------------------------------------------------------
// File DSA_FORM.CPP
//
// (c) by Koziev Elijah
//
// Content:
// SOLARIX Intellectronix Project  http://www.solarix.ru
//
// ����� SG_DeclensionForm - �������� ������ �������� ������� ����������������.
// ���� ������� ��������� �� ��������� ������� ����� ����� �������� ����
// �������������� �����, ������ ����� �������������� ��������� ��� ����������
// ������������ ��������� ������.
// -----------------------------------------------------------------------------
//
// CD->10.03.1997
// LC->23.06.2011
// --------------

#include <lem/conversions.h>
#include <lem/sol_io.h>

#include <lem/solarix/tokens.h>
#include <lem/solarix/exceptions.h>
#include <lem/solarix/dictionary.h>
#include <lem/solarix/ClassList.h>
#include <lem/solarix/PartOfSpeech.h>
//#include <lem/solarix/sg_autom.h>
#include <lem/solarix/gg_autom.h>
//#include <lem/solarix/dsa_main.h>
#include <lem/solarix/Paradigma.h>
#include <lem/solarix/ParadigmaForm.h>

using namespace lem;
using namespace Solarix;

SG_DeclensionForm::SG_DeclensionForm(void)
{
 valid_condition=false;
}

SG_DeclensionForm::SG_DeclensionForm( const SG_DeclensionForm &df )
{ Init(df); }


SG_DeclensionForm::SG_DeclensionForm(
                                     const CP_Array &Dim,
                                     const UCString &Command
                                    )
{
 dim=Dim;
 form=strip_quotes(Command);
 Check();

 valid_condition=valid_flexer_flags=false;

 return;
}


SG_DeclensionForm::SG_DeclensionForm(
                                     const lem::UFString & lexem_generator,
                                     const lem::UFString & rx_condition,
                                     const lem::UFString & rx_flexer_flags,
                                     const CP_Array & dims
                                    )
 : dim(dims), form(lexem_generator.c_str())
{
 valid_condition = !rx_condition.empty();
 valid_flexer_flags = !rx_flexer_flags.empty();

 condition_str = rx_condition;
 flexer_flags_str = rx_flexer_flags;
 

 if( !condition_str.empty() )
  condition = boost::wregex( condition_str.c_str(), boost::basic_regex<wchar_t>::icase );

 if( !flexer_flags.empty() )
  flexer_flags = boost::wregex( flexer_flags_str.c_str(), boost::basic_regex<wchar_t>::icase );
 
 return; 
}




void SG_DeclensionForm::Init( const SG_DeclensionForm &df )
{
 dim  = df.dim;
 form = df.form;

 #if !defined FAIND_NO_BOOST_REGEX
 condition = df.condition;
 flexer_flags = df.flexer_flags;
 #endif

 condition_str = df.condition_str;
 valid_condition = df.valid_condition;
 valid_flexer_flags = df.valid_flexer_flags;
 flexer_flags_str = df.flexer_flags_str;

 return;
}


void SG_DeclensionForm::operator=( const SG_DeclensionForm &df )
{
 Init(df);
 return;
}


#if defined SOL_LOADTXT && defined SOL_COMPILER
/***********************************************************************
 ���������� � ����������� ���������� �����, �� ������� ���������� �����
 ������� �� ����������������. ��������� ���������� � ������ �����: ��
 �������� ��� � ����� ����������.
************************************************************************/
void SG_DeclensionForm::Translate( int id_class, const GraphGram &gram )
{
 if( !form.empty() )
  {
   int id_language=UNKNOWN;
   if( !lem::is_quantor(id_class) )
    {
     const SG_Class &c = gram.GetDict().GetSynGram().GetClass( id_class );
     id_language = c.GetLanguage();
    }
    
   if( id_language!=UNKNOWN )
    {
     const SG_Language &lang = gram.GetDict().GetSynGram().languages()[id_language];
     const lem::MCollect<int> &id_alphabets = lang.GetAlphabets();
     form.Translate(gram,2,id_alphabets);
    }
   else
    {
     form.Translate(gram,2);
    }
  } 

 return;
}
#endif

/*************************************************************************
 ��������� ������������ ������� �� ����������������. � ������ �����������
 ������ �������� ��������� � ���������� �������������� ��������.
**************************************************************************/
void SG_DeclensionForm::Check(void) const
{
 int ipos=0, len = form.length();
 wchar_t ch;

 while( ipos<len && (ch=form[ipos++]) )
  switch(ch)
   {
    case B_COMMAND_METACHAR: // '%' - ������ �������
     {
      switch( ch=form[ipos++] ) // ������ �������
       {
        case B_DOUBLE_METACHAR:
         {
          // ������� ������������ ���������� ������� �� ����� ����������
          break;
         }  

        case B_REDUCE_METACHAR:
         {
          // ������� �������� �� n �������� ������: "...%-n..."
          const wchar_t number = form[ipos++];

          if( !is_udigit(number) )
           {
            merr->printf( "\nMust be a number in Form Builer Automat command:\n [%us]\n", form.c_str() );
            merr->printf( "%H ^\n", ipos );
            throw E_ParserError();
           }

          break;
         }

        case B_STRESS_METACHAR: // '+'
         {
          // ������� ���������� �������� ������ "...%+abcz%..." ��� "...%+abc"
          // ������ ������: "...%+{RRR..RR}"
          if( ch==B_GROUP_BEGIN_METACHAR )
           {
            while(
                  (ch = ipos<len ? form[ipos++] : 0)!=B_GROUP_END_METACHAR
                 )
             if( ch==0 )
              {
               // ������� ����������� - ����� ������.
               merr->printf(
                            "\nMust be a number "
                            " in Form Builer Automat command:\n [%us]\n"
                            , form.c_str()
                           );
               merr->printf( "%H ^\n", ipos );
               throw E_ParserError();
              }
           }
          else
           while( ipos<len && ch && ch!=B_COMMAND_METACHAR )
            {
             ch=form[ipos++];
            }

          break;
         }

        case B_PREFIX_INSERT_METACHAR: // 'a'
        case B_CUT_METACHAR:           // 'c'
         {
          // ������� ��������� �������, ���������� �� n �������� �� �������
          // ����� ������� �����, �� ���� ������ � ������� �����-n-1 ��������.
          // ���� n=0, �� �������� ��������� ������, � ��� �����.
          // ������: "...%cn..."
          //
          // ������� ������� ������� � �������, ������������� �� ������
          // �����: ������ "%aNR"

          const wchar_t number = form[ipos++];

          if( !is_udigit(number) )
           {
            merr->printf(
                        "\nMust be a number "
                        "in Form Builer Automat command:\n [%us]\n"
                        , form.c_str()
                       );
            merr->printf( "%H ^\n", ipos );
            throw E_ParserError();
           }

          if( ch==B_PREFIX_INSERT_METACHAR )
           {
            // ���������� ������ ������: "...%aN{RRR...R}
            if( form[ipos]==B_GROUP_BEGIN_METACHAR )
             {
              while( (ch=ipos<len ? form[ipos++] : 0)!=B_GROUP_END_METACHAR )
               if( ch==0 )
                {
                 // ������� ����������� - ����� ������.
                 merr->printf(
                              "\nMust be a number "
                              "in Form Builer Automat command:\n [%us]\n"
                              , form.c_str()
                             );
                 merr->printf( "%H ^\n", ipos );
                 throw E_ParserError();
                }
             }
            else
             {
              ipos++;
             }
           }

          break;
         }

        default:
         {
          merr->printf(
                       "\nUnrecognaized control character "
                       "in Form Builder Automat command:\n[%us]\n"
                       , form.c_str()
                      );
          merr->printf( "%H ^\n", ipos );
          throw E_ParserError();
         }
       }

      break;
     }

    default:
     {
      merr->printf(
                   "\nUnrecognaized control character %uc (0x%X16d)"
                   " in Form Builder Automat command:\n[%us]\n"
                   , ch, ch, form.c_str()
                  );
      merr->printf( "%H ^\n", ipos );
      throw E_ParserError();
     }
   }

 return;
}


#if defined SOL_LOADTXT && defined SOL_COMPILER
void SG_DeclensionForm::ReadAdditionalInfo( Grammar &gram, const SG_DeclensionTable &table, Macro_Parser& txtfile )
{
 // :: flexer ���_��������� for ����������_���������
 
 while( !txtfile.eof() )
  {
   BethToken t = txtfile.read();

   if( t==B_FOR )
    {
     UFString re = strip_quotes( txtfile.read().string() ).c_str();
     if( table.GetClass()!=UNKNOWN )
      {
       const SG_Class &cls = (const SG_Class&)gram.classes()[ table.GetClass() ];

       const int id_lang = cls.GetLanguage();
       if( id_lang!=UNKNOWN )
        {
         const SG_Language &lang = gram.GetDict().GetSynGram().languages()[id_lang];
         lang.SubstParadigmPattern(re);
        }
      }

     condition_str = re;
     condition = boost::wregex( re.c_str(), boost::basic_regex<wchar_t>::icase );
     valid_condition = true;
    }
   else if( t==B_FLEXER )
    {
     UFString re = strip_quotes( txtfile.read().string() ).c_str();

     flexer_flags_str = re; 
     flexer_flags = boost::wregex( re.c_str(), boost::basic_regex<wchar_t>::icase );
     valid_flexer_flags = true;
    }
   else
    {
     txtfile.seekp(t);
     break;
    }
  }

 return;
}
#endif


bool SG_DeclensionForm::MatchCondition( const UCString &str, const UFString &entry_flexer_flags ) const
{
 #if !defined FAIND_NO_BOOST_REGEX
 if(
    (!valid_condition || condition.empty()) &&
    (!valid_flexer_flags || flexer_flags.empty())
   ) 
  return true;

 if( valid_condition && !boost::regex_match( str.c_str(), condition ) )
  return false;

 if( valid_flexer_flags && !boost::regex_search( entry_flexer_flags.c_str(), flexer_flags ) )
  return false;

 return true;
 #else
 return false;
 #endif
}
