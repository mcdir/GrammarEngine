// -----------------------------------------------------------------------------
// File SOL_PARM.H
//
// (c) Koziev Elijah
//
// Content:
// ������ �������� ���������� - ����������� �� ���������� ����� ������� (�� ����
// ������������ �������������) ����������� �����, �������� ��������� ���������
// ������� � ��������� ����������� �������, ����� ������������� �������������
// ����� �� ��� ������ ��� �����������.
// -----------------------------------------------------------------------------
//
// CD->06.10.1995
// LC->04.01.2011
// --------------

#ifndef SOL_CRITERIA__H
#define SOL_CRITERIA__H
#pragma once

 #include <lem/noncopyable.h>
 #include <lem/containers.h>
 #include <lem/math/fp1.h>
 #include <lem/nullable.h>

 namespace lem
 {
  namespace Iridium { class Macro_Parser; }
  class OFormatter;
  class Stream;
  struct Sol_IO;
 }

 namespace Solarix
 {

  /*******************************************************************
   ������ ��� ����������� �������� ��������� - �������� � ���������
   ����������, ����������� ������� ���������.
  ********************************************************************/
  class Criterion
  {
   private:
    lem::UCString name; // ��� ��������

    lem::UFString str; // ��������� ��������
    lem::Nullable<double> rval; // ������������ ��������, ���� ������ ��������� ����� ��������������

   public:
    Criterion(void);

    Criterion( const Criterion &c );

    #if defined SOL_LOADTXT
    Criterion( const lem::Sol_IO &dict, lem::Iridium::Macro_Parser &txtfile );
    #endif

    Criterion( const lem::UCString &_name, const lem::UFString &_str );

    void operator=( const Criterion &c );

    const lem::UCString& GetName(void) const { return name; }

    const lem::UFString& GetString(void) const { return str; }
    int GetInt(void) const;
    double GetDouble(void) const;

    #if defined SOL_LOADTXT
    void LoadTxt( const lem::Sol_IO &io, lem::Iridium::Macro_Parser &txtfile );
    #endif

    void SaveBin( lem::Stream &bin ) const;
    void LoadBin( lem::Stream &bin );
  };


  class CriterionEnumerator;

  class Criteria_List : lem::NonCopyable
  {
   protected:
    Criteria_List(void) {}

   public:
    virtual ~Criteria_List(void) {}

    #if defined SOL_LOADTXT
    virtual void LoadTxt( const lem::Sol_IO &io, lem::Iridium::Macro_Parser &txtfile )=0;
    #endif

    virtual int Find( const lem::UCString &name )=0;
    virtual const Criterion& operator[]( int id )=0;
    virtual const Criterion& operator[]( const lem::UCString &name )=0;

    virtual void SaveBin( lem::Stream &bin ) const=0;
    virtual void LoadBin( lem::Stream &bin )=0;

    virtual CriterionEnumerator* Enumerate(void)=0;
  };

 } // end of namespace 'Solarix'

#endif
