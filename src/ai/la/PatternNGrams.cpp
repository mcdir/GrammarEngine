#include <lem/macro_parser.h>
#include <lem/solarix/tokens.h>
#include <lem/solarix/dictionary.h>
#include <lem/solarix/la_autom.h>
#include <lem/solarix/TreeScorers.h>
#include <lem/solarix/SynPatternCompilation.h>
#include <lem/solarix/PatternNGrams.h>

using namespace Solarix;


PatternNGrams::PatternNGrams(void) : explicit_scores(0)
{}


PatternNGrams::PatternNGrams( const PatternNGrams & x )
 : ngrams(x.ngrams), functions(x.functions), explicit_scores(x.explicit_scores)
{
}

void PatternNGrams::operator=( const PatternNGrams & x )
{
 explicit_scores = 0;
 ngrams = x.ngrams;
 functions = x.functions;
}

bool PatternNGrams::operator!=( const PatternNGrams & x ) const
{
 return ngrams != x.ngrams || explicit_scores!=x.explicit_scores || functions!=x.functions;
}

#if defined SOL_LOADTXT && defined SOL_COMPILER
void PatternNGrams::LoadTxt( 
                            Dictionary &dict,
                            lem::Iridium::Macro_Parser & txtfile,
                            VariableChecker & compilation_context
                           )
{
 txtfile.read_it( B_OFIGPAREN );

 while( !txtfile.eof() )
  {
   if( txtfile.probe( B_CFIGPAREN ) )
    break;

   if( txtfile.probe( B_SUB ) )
    {
     explicit_scores = -txtfile.read_int();
    }
   else if( lem::is_int( txtfile.pick() ) )
    {
     explicit_scores = txtfile.read_int();
    }
   else if( txtfile.probe( L"@" ) )
    {
     // TODO: ����� ���� ���������� �� ������� ������� PatternNGramFunction::load_txt
     PatternNGramFunction * f = new PatternNGramFunction();
     f->LoadTxt( UNKNOWN, dict, txtfile, compilation_context );
     functions.push_back(f);
    }
   else
    {
     lem::Iridium::BethToken t = txtfile.read();
     int id_group = dict.GetLexAuto().GetTreeScorers().FindGroup( t.string(), true );
     if( id_group!=UNKNOWN )
      {
       PatternNGramFunction * f = new PatternNGramFunction();
       f->LoadTxt( id_group, dict, txtfile, compilation_context );
       functions.push_back(f);
      }
     else
      {
       txtfile.seekp(t);
       PatternNGram * ngram = new PatternNGram();
       ngram->LoadTxt( dict, txtfile, compilation_context );
       ngrams.push_back(ngram);
      }
    }
  }

 return;
}
#endif    

void PatternNGrams::SaveBin( lem::Stream &bin ) const
{
 ngrams.SaveBin(bin);
 functions.SaveBin(bin);
 bin.write_int( explicit_scores );
 return;
}


void PatternNGrams::LoadBin( lem::Stream &bin )
{
 ngrams.LoadBin(bin);
 functions.LoadBin(bin);
 explicit_scores = bin.read_int();
 return;
}



#if defined SOL_CAA
NGramScore PatternNGrams::Match(
                                Dictionary & dict,
                                const lem::MCollect<int> & PatternSequenceNumber,
                                const SynPatternResultBackTrace * x_result,
                                SynPatternResult * cur_result,
                                KnowledgeBase & kbase,
                                TreeMatchingExperience &experience,
                                TrTrace *trace_log
                               ) const
{
 NGramScore res(explicit_scores);

 for( lem::Container::size_type i=0; i<ngrams.size(); ++i )
  {
   res += NGramScore( ngrams[i]->Match( dict, PatternSequenceNumber, cur_result, kbase, experience ) );
  }

 for( lem::Container::size_type i=0; i<functions.size(); ++i )
  {
   res += NGramScore( functions[i]->Match( dict, PatternSequenceNumber, x_result, cur_result, kbase, experience, trace_log ) );
  }

 return res;
}
#endif
