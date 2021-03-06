#include <lem/date_time.h>
#include <lem/solarix/dictionary.h>
#include <lem/solarix/la_autom.h>
#include <lem/solarix/BasicLexer.h>
#include <lem/solarix/res_pack.h>
#include <lem/solarix/LA_SynPatternTrees.h>
#include <lem/solarix/SynPatternTreeNodeMatchingResults.h>
#include <lem/solarix/LexerTextPos.h>
#include <lem/solarix/SynConnectorCache.h>
#include <lem/solarix/TreeMatchingExperience.h>
#include <lem/solarix/ElapsedTimeConstraint.h>
#include <lem/solarix/PreparedLexer.h>
#include <lem/solarix/MorphologyModels.h>
#include <lem/solarix/aa_autom.h>
#include <lem/solarix/TextAnalysisSession.h>

#if LEM_DEBUGGING==1
#include <lem/solarix/LexiconStorage.h>
#endif


using namespace Solarix;


TextAnalysisSession::TextAnalysisSession( Solarix::Dictionary * _dict, TrTrace * _trace )
 : dict(_dict), trace(_trace), lexer(NULL), pack(NULL)
{
 FindFacts = false;
 rules = & dict->GetLexAuto().GetSynPatternTrees();
 return;
}


TextAnalysisSession::~TextAnalysisSession()
{
 lem_rub_off(lexer);
 lem_rub_off(pack);
}



void TextAnalysisSession::Analyze( bool ApplyPatterns, bool DoSyntaxLinks, const ElapsedTimeConstraint &constraints )
{
 lem_rub_off(pack);

 // ������ ��� ������ ���� ������ � �������� � lexer.

 #if defined SOL_DEBUGGING
 // �������� ������ ����� �����������.
 if( trace!=NULL )
  {
   trace->MorphologicalAnalysisStarts(*lexer);
  }
 #endif

 if( params.ApplyModel )
  {
   if( dict->GetLexAuto().GetModel().GetSequenceLabeler().IsAvailable() )
    {
     SequenceLabelerModel & model = dict->GetLexAuto().GetModel().GetSequenceLabeler();
     model.Apply( *lexer, *dict, constraints, false );

     #if defined SOL_DEBUGGING
     if( trace!=NULL )
      {
       // ������� � ��������� ���������� ���������� ������
       trace->AfterModelApplication(*lexer);
      }
     #endif
    }
  }

 lem::Ptr<SynPatternTreeNodeMatchingResults> results;

 bool UseDefaultScheme=true;
 if( ApplyPatterns )
  {
   // ������� workflow - ����������� ���������������, �� ������, ���������.
   enum { UseTopDown, UseIncompleteTopDown };
   lem::MCollect<int> scheduled_algorithms;

   if( params.UseTopDownThenSparse )
    {
     scheduled_algorithms.push_back( UseTopDown );
     scheduled_algorithms.push_back( UseIncompleteTopDown );
    }
   else if( params.CompleteAnalysisOnly )
    {
     scheduled_algorithms.push_back( UseTopDown );
    }
   else    
    {
     scheduled_algorithms.push_back( UseIncompleteTopDown );
    }

   TreeMatchingExperience experience;

   for( lem::Container::size_type step=0; step<scheduled_algorithms.size(); ++step )
    {
     int algorithm = scheduled_algorithms[step];

     if( algorithm==UseTopDown )
      {
       // ������ ���������� ������ ��� �����-���� �����������.
       results = TopDownParsing( ApplyPatterns, DoSyntaxLinks, experience, constraints );

       if( results.NotNull() && !results->empty() )
        {
         #if LEM_DEBUGGING==1
         //results->Print( *dict, *lem::mout );
         #endif

         UseDefaultScheme=false;
         results->ApplyTokenScores();
         pack = results->BuildGrafs( *dict, *lexer, DoSyntaxLinks, false, trace );

         #if LEM_DEBUGGING==1
         //pack->Print( *lem::mout, dict->GetSynGram(), true );
         #endif

         break;
        }
      }
     else if( algorithm==UseIncompleteTopDown )
      {
       // �������� ������, ���� ������ �� ��������.
       lexer->ChangeParams().SkipInnerTokens = false;
       lexer->ChangeParams().SkipOuterToken = true;
       lexer->ChangeParams().CompleteAnalysisOnly = false;

       if( lexer->ChangeParams().MaxSkipToken==0 )
        lexer->ChangeParams().ConfigureSkipToken();

       experience.ClearPatternMatchings();

       results = TopDownParsing( ApplyPatterns, DoSyntaxLinks, experience, constraints );

       if( (results.IsNull() || results->empty()) && !constraints.Exceeded() )
        {
         const SynPatternTreeNode & filter = rules->GetIncompleteFilter( params.GetLanguageID() );
      
         if( !filter.Empty() )
          {
           results = filter.IncompleteAnalysis(
                                               dict->GetLexAuto(),
                                               dict->GetSynGram(),
                                               *rules,
                                               dict->GetLexAuto().GetWordEntrySet(),
                                               *lexer,
                                               params.GetLanguageID(),
                                               experience,
                                               constraints,
                                               trace
                                              );
          }
        }

       if( results.NotNull() && !results->empty() )
        {
         #if LEM_DEBUGGING==1
         //results->Print( *dict, *lem::mout );
         #endif
       
         UseDefaultScheme=false;
       
         results->ApplyTokenScores();
         pack = results->BuildGrafs( *dict, *lexer, DoSyntaxLinks, false, trace );
         break;
        }
      }

     if( constraints.Exceeded() )
      break; // �������� ����� �������, ���������� �� ������.
    }
  }

 if( UseDefaultScheme )
  {
   // ������� ������� �� ������ ��� ���������, ������� ������ ����������� ��������� �� ����� ����������� � �����������
   // ���� ��������� ��������.
   SynPatternTreeNodeMatchingResults empty;
   pack = empty.BuildGrafs( *dict, *lexer, false, params.CompleteAnalysisOnly, trace );
  }

 #if defined SOL_DEBUGGING
 if( trace!=NULL )
  trace->MorphologicalAnalysisFinishes( * pack );
 #endif

 return;
}






SynPatternTreeNodeMatchingResults* TextAnalysisSession::TopDownParsing(
                                                                       bool ApplyPatterns,
                                                                       bool DoSyntaxLinks,
                                                                       TreeMatchingExperience & experience,
                                                                       const ElapsedTimeConstraint & constraints
                                                                      )
{
 const SynPatternTreeNode & filter = rules->GetDefaultFilter( params.GetLanguageID() );

 SynPatternTreeNodeMatchingResults * results = NULL;

 if( !filter.Empty() )
  {
   results = filter.CompleteAnalysis(
                                     dict->GetLexAuto(),
                                     dict->GetSynGram(),
                                     *rules,
                                     dict->GetLexAuto().GetWordEntrySet(),
                                     *lexer,
                                     params.GetLanguageID(),
                                     experience,
                                     constraints,
                                     trace
                                    );
  }

 return results;
}
