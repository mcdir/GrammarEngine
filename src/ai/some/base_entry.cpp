// -----------------------------------------------------------------------------
// File BASE_ENTRY.CPP
//
// (c) by Koziev Elijah     all rights reserved 
//
// SOLARIX Intellectronix Project http://www.solarix.ru
//                                http://sourceforge.net/projects/solarix  
//
// You must not eliminate, delete or supress these copyright strings
// from the file!
//
// Content:
// SOLARIX Grammar engine
// ����� Base_Entry - ������� ����� ��� ����������� ������������� ���������
// ������ ����������.
//
// 21.11.2006 - ����������� ���� �������.
// -----------------------------------------------------------------------------
//
// CD->10.08.1996
// LC->20.11.2010
// --------------

#include <lem/macro_parser.h>

#include <lem/solarix/tokens.h>
#include <lem/solarix/dictionary.h>
#include <lem/solarix/grammar.h>
#include <lem/solarix/exceptions.h>
#include <lem/solarix/form_table.h>
#include <lem/solarix/CoordList.h>
#include <lem/solarix/ClassList.h>

using namespace lem;
using namespace Solarix;
using namespace lem::Iridium;


Base_Entry::Base_Entry(void):Form_Table()
{
}

#if defined SOL_LOADTXT && defined SOL_COMPILER
Base_Entry::Base_Entry(
                       Macro_Parser& txtfile,
                       Grammar& gram,
                       bool IsRealized
                      ):Form_Table()
{
 LoadTxt(txtfile,gram,IsRealized);
 return;
}
#endif

Base_Entry::Base_Entry( Stream& bin ):Form_Table()
{
 LoadBin(bin);
}


#if defined SOL_LOADTXT && defined SOL_COMPILER
/*************************************************************************
 ����������� ������ ����� ����������� ������ �����, ����� �����������
 ��������� � ���� �������� ������ ������������� �����. ������� ��������
 t ���� ������ ����� ����. ���� ���� ����� ������������� �������� �������
 ������������� ������ ������, �� ������������ true, ����� false.
**************************************************************************/
bool Base_Entry::ProcessSection(
                                 Macro_Parser &txtfile,
                                 Grammar &gram,
                                 const BethToken &t
                                )
{
 return Form_Table::ProcessSection(txtfile,gram,t);
}
#endif

#if defined SOL_LOADTXT && defined SOL_COMPILER
/**********************************************************
 �������� ���� �������� ������ �� ���������� ����� �������.
 ���� ���� ������� �� ���������� �������������� ������.
***********************************************************/
void Base_Entry::LoadBody(
                           Macro_Parser &txtfile,
                           Grammar& gram
                          )
{
 if( is_realized )
  {
   // ���� ������ ���������� '{', �� ������ ����� �����������
   // �������� ��������� ������.

   const BSourceState prefig = txtfile.tellp();
   const BethToken isfig = txtfile.read();

   #if LEM_DEBUGGING==1
   int nf = CountForms();
   #endif

   if( isfig.GetToken()!=B_OFIGPAREN )
    txtfile.seekp(prefig);
   else
    LoadTxtEx( txtfile, gram );

   if( CountForms()==0 )
    BeforeFirstForm(gram);    

   CheckAttr( txtfile, gram );
  }

 #if defined SOL_DETAILED
 if( gram.GetDict().GetDebugLevel_ir()>=3 )
  {
   // ���-���������: ��������� ���������� ������.
   gram.GetIO().mecho().printf( "Ok\n" );
  }
 #endif

 return;
}
#endif

#if defined SOL_LOADTXT && defined SOL_COMPILER
/********************************************************************
 ������ �� ���������� ����� ������ ������������ �������� ������.
 ��� ����������� ��������� ��������������� ������ ���������-���������,
 �����, �������������� ���� � ������������� ��� ����������� �������
 ����.
*********************************************************************/
void Base_Entry::LoadTxtEx(
                            Macro_Parser& txtfile,
                            Grammar& gram
                           )
{
 // *** ��������� �������� ������ ***
 bool looping=true;
 BethToken token;
 CP_Array common;

 while( looping )
  {
   if( txtfile.eof() )
    {
     Print_Error(txtfile);
     gram.GetIO().merr().printf( "End of file has been reached before entry body completely loaded\n" );
     throw E_ParserError();
    }

   const BSourceState back = txtfile.tellp();
   token = txtfile.read();

   if( token.GetToken()==B_CFIGPAREN )
    {
     // �������� ������ ���������
     looping=false;
     break;
    }

   if( token.GetToken()==B_OTRIPAREN )
    {
     txtfile.seekp(token.GetBegin());
     SkipNetSection(txtfile,gram);
     continue;
    }

   if( ProcessSection(txtfile,gram,token) )
    continue;

   txtfile.seekp(back);

   if( LoadAttribute(txtfile,gram) )
    continue;

   // ��������� ����������.
   LoadForm(
            txtfile,
            gram,
            common,
            GramCoordAdr(UNKNOWN,UNKNOWN),
            UNKNOWN,
            GramCoordAdr(UNKNOWN,UNKNOWN),
            UNKNOWN,
            UNKNOWN
           );

  } // ����� ����� ���������� �������� ������

 return;
}
#endif



#if defined SOL_LOADTXT && defined SOL_COMPILER
void Base_Entry::BeforeFirstForm( Grammar& gram )
{
 if( is_quantor(GetClass()) ) 
  return;

 const GramClass& cl = gram.classes()[GetClass()];
 const int na=cl.attrs().size();

 for( int i=0; i<na; i++ )
  {
   const GramCoordAdr iglob = cl.attrs()[i];

   const GramClass &cls = gram.classes()[GetClass()];

   if( GetAttrState(iglob)==UNKNOWN )
    {
     // ��� �������� ������ �������� �� ���������?
     lem::zbool has_def;
     for( lem::Container::size_type j=0; j<cls.attr_defaults.size(); ++j )
      if( cls.attr_defaults[j].first==iglob )
       {
        if( cls.attr_defaults[j].second!=UNKNOWN )
         {
          int ia = attr.FindOnce(iglob);
          if( ia!=UNKNOWN )
           attr.Remove(ia);
 
          attr.push_back(GramCoordPair(iglob,cls.attr_defaults[j].second));
         }

        has_def=true;
        break;       
       }

     if( !has_def )
      {
       // ���� ��� ���������� � ����� ������ ������������
       // �����������, �� ������� ���������� ���������
       // �������� ��� FALSE.

       if( gram.coords()[iglob.GetIndex()].states().empty() )
        attr.push_back(GramCoordPair(iglob,false));
      }
    }
  }

 return;
}
#endif


#if defined SOL_LOADTXT && defined SOL_COMPILER
/*********************************************************************
 ��� �������� ������ ���� ����������! ����� ���������� ����� ������
 ���� �������� ������.
**********************************************************************/
void Base_Entry::CheckAttr( Macro_Parser& txtfile, Grammar& gram )
{
 if( is_quantor(GetClass()) ) 
  return;

 const GramClass& cl = gram.classes()[GetClass()];
 const int na = CastSizeToInt(cl.attrs().size());

 for( int i=0; i<na; i++ )
  {
   const GramCoordAdr iglob = cl.attrs()[i];

   const GramClass &cls = gram.classes()[GetClass()];

   if( GetAttrState(iglob)==UNKNOWN )
    {
     lem::zbool def_unk;
     for( lem::Container::size_type j=0; j<cl.attr_defaults.size(); ++j )
      if( cl.attr_defaults[j].first==iglob && cl.attr_defaults[j].second==UNKNOWN ) 
       {
        def_unk=true;
        break; 
       } 

     if( !def_unk )
      {
       // ��������� ��������� �� ����������!
       Print_Error(txtfile);
       gram.GetIO().merr().printf(
                                  "Not defined attribute [%us] state\n",
                                  gram.coords()[iglob.GetIndex()].GetName()[iglob.GetVar()].c_str()
                                 );
       throw E_ParserError();
      }
    }
  }

 return;
}
#endif
