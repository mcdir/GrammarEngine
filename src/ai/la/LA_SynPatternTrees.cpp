// LC->29.09.2013

#include <lem/solarix/dictionary.h>
#include <lem/solarix/la_autom.h>
#include <lem/solarix/PM_FunctionLoader.h>
#include <lem/solarix/LexiconStorage.h>
#include <lem/solarix/SynPattern.h>
#include <lem/solarix/LA_SynPatternTrees.h>

using namespace Solarix;

LA_SynPatternTrees::LA_SynPatternTrees( Solarix::Dictionary *Dict )
{
 dict = Dict;
 storage = NULL;
 return;
}

LA_SynPatternTrees::~LA_SynPatternTrees(void)
{
 Delete();
 return;
}


void LA_SynPatternTrees::Delete(void)
{
 for( lem::Container::size_type i=0; i<pattern_tree.size(); ++i )
  delete pattern_tree[i].second;

 for( lem::Container::size_type i=0; i<named_filter_trees.size(); ++i )
  delete named_filter_trees[i];

 pattern_tree.clear();
 named_filter_trees.clear();

 id2filter.clear();
 id2name.clear();

 return;
}



void LA_SynPatternTrees::Connect( LexiconStorage *Storage )
{
 #if defined LEM_THREADS
 lem::Process::CritSecLocker lock(&cs_init); 
 #endif

 Delete();
 storage = Storage;

 return;
}



const SynPatternTreeNode& LA_SynPatternTrees::GetDefaultFilter( int id_language )
{
 #if defined LEM_THREADS
 lem::Process::RWU_ReaderGuard rlock(cs_default_filter);
 #endif

 // ������������� ���, �������� ������ ������ ��� ���������� ����� ��� ���������.
 for( lem::Container::size_type i=0; i<pattern_tree.size(); ++i )
  if( pattern_tree[i].first == id_language )
   return *pattern_tree[i].second;

 // ���, � ���� ���. ������ ���� ��������� ���������� �� ����� �������� � ����� �������� � ����,
 // � ����� � ������ ������� ���������� �� ��.
 #if defined LEM_THREADS
 lem::Process::RWU_WriterGuard wlock(rlock);
 #endif

 for( lem::Container::size_type i=0; i<pattern_tree.size(); ++i )
  if( pattern_tree[i].first == id_language )
   return *pattern_tree[i].second;

 std::pair<SynPatternTreeNode*,lem::UCString> tree(NULL,lem::UCString());

 const int id = storage->FindSynPatternTree( id_language, L"", SOLID_PATTERN );
 if( id==UNKNOWN )
  {
   tree.first = new SynPatternTreeNode();
  }
 else
  {
   tree = storage->GetSynPatternTree(id);
  }
 
 LEM_CHECKIT_Z( tree.second.empty() );

 tree.first->Link( dict->GetLexAuto().GetFunctions().Get() );

 pattern_tree.push_back( std::make_pair( id_language, tree.first ) );
 id2name.insert( std::make_pair( id, tree.second ) );
 id2filter.insert( std::make_pair( id, tree.first ) );

 return *tree.first;
}







const SynPatternTreeNode& LA_SynPatternTrees::GetIncompleteFilter( int id_language )
{
 #if defined LEM_THREADS
 lem::Process::RWU_ReaderGuard rlock(cs_default_filter);
 #endif

 for( lem::Container::size_type i=0; i<incomplete_pattern_tree.size(); ++i )
  if( incomplete_pattern_tree[i].first == id_language )
   return *incomplete_pattern_tree[i].second;

 #if defined LEM_THREADS
 lem::Process::RWU_WriterGuard wlock(rlock);
 #endif

 for( lem::Container::size_type i=0; i<incomplete_pattern_tree.size(); ++i )
  if( incomplete_pattern_tree[i].first == id_language )
   return *incomplete_pattern_tree[i].second;

 std::pair<SynPatternTreeNode*,lem::UCString> tree(NULL,lem::UCString());

 const int id = storage->FindSynPatternTree( id_language, L"", INCOMPLETE_PATTERN );
 if( id==UNKNOWN )
  {
   tree.first = new SynPatternTreeNode();
  }
 else
  {
   tree = storage->GetSynPatternTree(id);
  }
 
 LEM_CHECKIT_Z( tree.second.empty() );

 tree.first->Link( dict->GetLexAuto().GetFunctions().Get() );
 incomplete_pattern_tree.push_back( std::make_pair( id_language, tree.first ) );

 id2name.insert( std::make_pair( id, tree.second ) );
 id2filter.insert( std::make_pair( id, tree.first ) );

 return *tree.first;
}



const lem::UCString & LA_SynPatternTrees::GetPatternName( int id_tree )
{
 if( id2name.find(id_tree)==id2name.end() )
  {
   LEM_STOPIT;
   return id2name.begin()->second;
  }
 else
  return id2name.find(id_tree)->second;
}


const SynPatternTreeNode& LA_SynPatternTrees::GetNamedFilter( int id_tree )
{
 #if defined LEM_THREADS
 lem::Process::RWU_ReaderGuard rlock(cs_named);
 #endif
 
 // ������� ������� � ����, �������� �� ��� ��������� ��� ������.
 std::map< int, const SynPatternTreeNode* >::const_iterator it = id2filter.find(id_tree);
 if( it!=id2filter.end() )
  {
   // ��, �����.
   return *it->second;
  }
 else
  {
   // � ���� ����. ��� ��� � ���� ����� ������ ������ ����� ����� ������ �������� � ��� ����� ��
   // ������, �� �� ������� �������� ���������� ��������, ����� ��� ��� ������ � ����, � ��� �����
   // ������ ��������� ������ �� ��������� � ���������� ��� � ����.
   #if defined LEM_THREADS
   lem::Process::RWU_WriterGuard wlock(rlock);
   #endif

   it = id2filter.find(id_tree);
   if( it!=id2filter.end() )
    {
     // �� ���, ������ ����� ����� ��������� ������ � ���.
     return *it->second;
    }

   std::pair<SynPatternTreeNode*,lem::UCString> info = storage->GetSynPatternTree(id_tree);

   LEM_CHECKIT_Z( !info.second.empty() );
   info.first->Link( dict->GetLexAuto().GetFunctions().Get() );

   named_filter_trees.push_back( info.first );
   id2filter.insert( std::make_pair(id_tree,info.first) );
   id2name.insert( std::make_pair(id_tree,info.second) );

   return *info.first;
  }
}


void LA_SynPatternTrees::StoreFilterTree( int id, const lem::UCString &name, SynPatternTreeNode *tree, int id_language, int pattern_type )
{
 #if defined LEM_THREADS
 lem::Process::RWU_ReaderGuard rlock(cs_named);
 lem::Process::RWU_WriterGuard wlock(rlock);
 #endif

 if( name.empty() )
  {
   if( pattern_type==LA_SynPatternTrees::SOLID_PATTERN )
    {
     for( lem::Container::size_type i=0; i<pattern_tree.size(); ++i )
      if( pattern_tree[i].first == id_language )
       {
        lem::MemFormatter mem;
        mem.printf( "Filter tree is already stored for language=%d", id_language );
        throw lem::E_BaseException(mem.string());
       }

     pattern_tree.push_back( std::make_pair( id_language, tree ) );
    }
   else if( pattern_type==LA_SynPatternTrees::INCOMPLETE_PATTERN )
    {
     for( lem::Container::size_type i=0; i<incomplete_pattern_tree.size(); ++i )
      if( incomplete_pattern_tree[i].first == id_language )
       {
        lem::MemFormatter mem;
        mem.printf( "Incomplete tree is already stored for language=%d", id_language );
        throw lem::E_BaseException(mem.string());
       }

     incomplete_pattern_tree.push_back( std::make_pair( id_language, tree ) );
    }
   else
    {
     LEM_STOPIT;
    }
  }
 else
  {
   lem::UCString uname( lem::to_upper(name) );

   named_filter_trees.push_back( tree );
   id2filter.insert( std::make_pair(id,tree) );
   id2name.insert( std::make_pair(id,uname) );
  }

 storage->StoreSynPatternTree( id_language, name, id, tree, pattern_type );

 return;
}
