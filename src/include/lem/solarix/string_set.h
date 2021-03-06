// -----------------------------------------------------------------------------
// File STRING_SET.H
//
// (c) Koziev Elijah, Russia
//
// Content:
// UCStringSet class - ������ ����� (UCString).
// -----------------------------------------------------------------------------
//
// CD->09.08.1997
// LC->12.12.2008
// --------------

#ifndef SOL_STRINGSET__H
#define SOL_STRINGSET__H
#pragma once

 #include <lem/containers.h>
 #include <lem/cstring.h>
 #include <lem/fstring.h>

 namespace lem
 {
  namespace Iridium { class Macro_Parser; }
  class OFormatter;
  struct Sol_IO;
 }

 namespace Solarix
 {
  using lem::Iridium::Macro_Parser;
  using lem::OFormatter;
  using lem::MCollect;
  using lem::UCString;
  using lem::UFString;
  using lem::Sol_IO;
  using lem::Stream;

  class Dictionary;

 /****************************************************************
  ��������� ���������� �����, ������������ ��� ���������� ������
  ����, ���������� ��������� ��������� (������ ���������).
 *****************************************************************/
 class UCStringSet : public MCollect<UCString>
 {
  private:
   MCollect<int> weight;

  public:
   UCStringSet(void);
   UCStringSet( const UCString &s );

   #if defined SOL_LOADTXT
   UCStringSet( const Sol_IO &io, Macro_Parser& txt );
   #endif

   #if defined SOL_LOADTXT
   void LoadTxt( const Sol_IO &io, Macro_Parser &txtfile );
   #endif

   void AddList( const UCStringSet& ss );
   void Add( const UCString &lexem, int w=0 );

   #if defined SOL_SAVETXT
   void SaveTxt( OFormatter& txtfile ) const;
   #endif

   void Print( OFormatter &s ) const;

   const UFString string(void) const;
   int Find( const UCString& name ) const;
   int FindNoCase( const UCString& name ) const;

   bool operator==( const UCStringSet &x ) const;
   bool operator!=( const UCStringSet &x ) const;

   void Save_Packed( lem::Stream &bin ) const;
   void Load_Packed( lem::Stream &bin );
 };

 #if defined SOL_LOADTXT
 extern const UCString sol_read_multyname(
                                          const Sol_IO &dict,
                                          Macro_Parser& txtfile,
                                          int breaker
                                         );
 #endif

 } // namespace 'Solarix'

#endif
