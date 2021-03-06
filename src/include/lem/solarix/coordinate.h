// -----------------------------------------------------------------------------
// File COORDINATE.H
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
// LEM C++ library  http://www.solarix.ru
// GramCoordState and GramCoord classes.
// GramCoord - �������������� ����������, ����� ������������� ���������,
// ������ C-����������� enum { a, b, c ... }
// -----------------------------------------------------------------------------
//
// CD->06.10.1995
// LC->20.11.2010
// --------------

#ifndef SOL_COORD__H
#define SOL_COORD__H
#pragma once

 #include <lem/containers.h>
 #include <lem/smart_pointers.h>
 #include <lem/binding.h>
 #include <lem/solarix/GramCoordUpdator.h>
 #include <lem/solarix/string_set.h>

 namespace lem
 {
  class OFormatter;
  class Stream;

  namespace Iridium {
                     class Macro_Parser;
                     class BethToken;
                    }
 }


 namespace Solarix
 {
  using lem::OFormatter;
  using lem::Stream;
  using lem::Collect;
  using lem::IntCollect;
  using lem::Iridium::BethToken;
  using lem::Iridium::Macro_Parser;

  /*******************************************************************
   ����� ��� �������� ������� ���� ��������� � ���������. ������������
   ��� �������� ����������� � ��������� �����������. ������ ����������
   ����������� ����� ������ � ������� ���������, ������� ��� �����
   ���������.
  ********************************************************************/

  class Grammar;

  class GramCoordState : public UCStringSet
  {
   public:
    #if defined SOL_LOADTXT
     UCString c_name; // ��� ��������� C ��� ���������� � API ������
     lem::MCollect<UCString> c_names; // ���� ����� ���������� ��� ������� ������������
     void LoadSubstates( const Sol_IO &io, Macro_Parser &txtfile );
    #endif

    int weight;

   public:
    GramCoordState(void);
    GramCoordState( const GramCoordState &x );
    GramCoordState( const lem::UCString &name );
    GramCoordState( const lem::UCString &name, int w );

    void operator=( const GramCoordState &x );

    // ���������� ��� ��������� ��� ��� ������� �������� � ���������.
    inline const UCString& GetName(void) const { return front(); }

    #if defined SOL_LOADTXT
    inline const UCString& get_C_Name(void) const { return c_name; }
    #endif

    inline int GetWeight(void) const { return weight; }

    #if defined SOL_COMPILER
    void Save_API( int istate0, OFormatter &cpp, lem::Binding::Language lang ) const;
    void Clear_API_Names(void);
    #endif

    #if defined SOL_SAVEBIN
    void SaveBin( lem::Stream &bin ) const;
    #endif

    void LoadBin( lem::Stream &bin );

    #if defined SOL_LOADTXT
    void LoadTxt( const Sol_IO &io, Macro_Parser &txtfile );
    #endif
  };

  class GramCoord
  {
   public:
    int id;
    lem::Ptr<GramCoordUpdator> updator;
    UCStringSet name;              // ��� ����������, � ����� ��������.

   private:
    Collect<GramCoordState> state; // ����� ��������� ����������

    #if defined SOL_LOADTXT
    bool is_realized;              // false ��� ����������, true ��� ����������.
    UCString c_name;               // ��� ��������� ��� ���������� � ����� ������ API
    #endif

   public:
    GramCoord(void);
    GramCoord( const GramCoord& c );

    #if defined SOL_LOADTXT
    GramCoord(
              Macro_Parser& txtfile,
              const Grammar& gram,
              bool IsRealized
             );
    #endif

    GramCoord( lem::Stream& binfile );

    void Add( const GramCoord &c );
    void Add( const GramCoordState &c );

    #if defined SOL_LOADTXT
    void AddState( const UCString &s );
    #endif

    void operator=( const GramCoord& c );

    #if defined SOL_LOADTXT
    void LoadTxt(
                 Macro_Parser &txtfile,
                 const Grammar& gram,
                 bool IsRealized
                );
    #endif

    #if defined SOL_SAVEBIN
    void SaveBin( lem::Stream& binfile ) const;
    #endif

    void LoadBin( lem::Stream& binfile );

    const GramCoordState& GetTopState( int i ) const { return state[i]; }
    GramCoordState& GetTopState( int i ) { return state[i]; }

    inline const UCStringSet& GetName(void) const { return name; }

    int IsName( const UCString& s ) const;

    #if defined SOL_LOADTXT
    inline bool IsRealized(void) const { return is_realized; }
    void SetRealized(void) { is_realized=true; }
    #endif

    inline const Collect<GramCoordState>& states(void) const { return state; }

    inline bool IsBistable(void) const { return state.empty(); }

    int FindState( const UCString& sname ) const;
    const UCString& GetStateName( int RI ) const;
    int GetIndexOfState( int LI ) const;
    bool IsDefState( int RI ) const;
    bool HasDefStates(void) const;
    bool IsHeadState( int RI ) const;

    /*************************************************************
     ����������� �� ��� ��������� ����� ��������� ������������
    *************************************************************/
    inline bool SameSubgroup( int int1, int int2 ) const
    { return GetSubgroup(int1)==GetSubgroup(int2); }

    int GetSubgroup( int RI ) const;
    const IntCollect GetSubgroupIndeces( int isubgroup ) const;
    int GetTotalStates(void) const;

    bool operator==( const GramCoord& x ) const;
    bool operator!=( const GramCoord& x ) const;

    #if defined SOL_SAVETXT
    void SaveTxt( OFormatter& txtfile ) const;
    #endif

    #if defined SOL_LOADTXT
    inline const UCString& get_C_Name(void) const { return c_name; }
    #endif

    #if defined SOL_COMPILER
    void Save_API( OFormatter &cpp, lem::Binding::Language lang ) const;
    #endif
  };

  class Dictionary;
  extern void sol_check_s_name(
                               const Dictionary &dict,
                               Macro_Parser& txtfile,
                               const BethToken& s,
                               bool strict
                              );

  extern void sol_check_coord_name(
                                   const Dictionary &dict,
                                   Macro_Parser& txtfile,
                                   const BethToken& s
                                  );
  
 } // namespace 'Solarix'

#endif
