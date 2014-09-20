// .NET ������� ��� ������ ������� ������������ API ��������������� �������
// ��� ����� ������� ������ � ��� ������� ������������ ������ gren_fx2 � �������������� ������ � ���.
//
// ���������� �� API:
// http://www.solarix.ru/api/ru/list.shtml
// http://www.solarix.ru/for_developers/api/grammar-engine-api.shtml
// http://www.solarix.ru/for_developers/api/dotnet_assembly.shtml
//
// CHANGELOG:
// 17.07.2008 - ������� ������� WinDLL API �� stdcall � ��������������� ������� ����� �� CallingConvention.StdCall
// 25.07.2008 - ��������� sol_FindClass, sol_FindEnum, sol_FindEnumState, sol_EnumInClass
// 27.07.2008 - ��������� sol_SeekNGrams
// 01.08.2008 - ��� ������������ ����������� DLL �������� � bool �������� �� int
// 04.04.2008 - ������� ����� ����������� �������� ��� API ���������� ������
// 15.11.2008 - ��������� sol_LoadKnowledgeBase, �������� ���� FG_PEDANTIC_ANALYSIS
// 15.11.2008 - ������� ���������� �� ������ � ������ ������� ���������� ������
// 16.11.2008 - ��������� ������� ��� API ����������
// 13.02.2009 - ��������� ������� API SentenceBroker'�
// 08.04.2009 - �� API ������� sol_PreloadCaches
// 21.06.2009 - ��������� � ��������� � ���������� ��������������
// 20.07.2009 - ��������� API ������� � ���� N-�����
// 22.12.2009 - �� ������ �������� ����� ��������� ���������� ������ � ��������������
// 02.08.2010 - ��������� sol_SaveDictionary
// 06.08.2010 - ��������� ������� sol_GetPhraseLanguage, sol_GetPhraseClass � sol_AddWord
// 19.08.2010 - ��������� ������� sol_LinksInfoFlagsTxt, sol_SetLinkFlags
// 04.09.2010 - ��������� ������� sol_GetError, sol_ClearError
// 19.06.2011 - ��������� sol_GetTranslationLog � sol_GetTranslationLogFx ��� ������ ����������
//              ����������� � �����������.
// 02.10.2011 - ��������� � ��������� sol_MorphologyAnalysis � sol_SyntaxAnalysis
// 22.10.2011 - ��������� � API sol_Tokenize -> sol_TokenizeW
// 13.11.2011 - ��������� ������� sol_GetCoordNameFX � sol_GetCoordStateNameFX
// 09.01.2012 - ��������� � ��������� ������� sol_Syllabs
// 07.01.2013 - �������� ���� SOL_GREN_MODEL ��� ��������� ������������� ������
//
// CD->30.01.2008
// LC->25.03.2014
// --------------

using System;
using System.Runtime.InteropServices;

namespace SolarixGrammarEngineNET
{
 using HGREN = System.IntPtr;

 public sealed class GrammarEngine
 {
  #if( DEBUG )
  private const string gren_dll = "solarix_grammar_engined.dll";
  #else
  private const string gren_dll = "solarix_grammar_engine.dll";
  #endif


  /// <summary>
  /// Control flags for sol_MorphologyAnalysis and sol_SyntaxAnalysis.
  /// See http://www.solarix.ru/api/ru/sol_MorphologyAnalysis.shtml for details
  /// </summary>
  [Flags]
  public enum MorphologyFlags
  {
   /// <summary>
   /// ����� ������� �� ���������.
   /// </summary>
   DEFAULT=0,

   /// <summary>
   /// ��������� �������� ����� � ��������� ��� ����������� �������
   /// </summary>
   SOL_GREN_ALLOW_FUZZY           = 0x00000002,

   /// <summary>
   /// ��������� ������ ������ ������ �����������, � ��� ������������� �������� ��� ������
   /// � �������������� ������ - ������������ �� �������.
   /// </summary>
   SOL_GREN_COMPLETE_ONLY         = 0x00000004,

   /// <summary>
   /// ������������ ������� � ����� \x1F ��� ����������� ������ ����.
   /// ����� �������, ���������� ��� ����� ��������� ����������� ������ ������, �
   /// ������� ������� ������ ��������� �����������.
   /// </summary>
   SOL_GREN_PRETOKENIZED          = 0x00000008,

   /// <summary>
   /// ��������� ������ ����������� ��������� �����������.
   /// </summary>
   SOL_GREN_TOKENIZE_ONLY         = 0x00000010,

   /// <summary>
   /// ���������� ����: ��������� ��������� ������� ���������� ��������� ������������ ����
   /// </summary>
   SOL_GREN_DISABLE_FILTERS       = 0x00000020,

   /// <summary>
   /// ��������� ������������ ������������� ������ ���������� ����� ��� �������� ����� ������������ ��������� ����������.
   /// ������������� ����� ����� ������� ����������� ������ � ����� ������������ ������� (������ dictionary.xml) � �������
   /// ������ ������ ��� ������������ ������.
   /// </summary>
   SOL_GREN_MODEL                 = 0x00000800,

   /// <summary>
   /// ��������� ����������� �������� � sol_MorphologyAnalysis ������ � ������� ������������� ������, � ������� �������� �� ������������.
   /// ��������� ����� �������� ����������� ����������� �������, ���� ���������� ������ �������������.
   /// </summary>
   SOL_GREN_MODEL_ONLY            = 0x00002000
  }


  [Flags]
  public enum SyntaxFlags
  {
   DEFAULT=0,

   /// <summary>
   /// ����������� ����� � �������������� ������ ���, ����� ��� ��� ������������ ��� � ������� ��������
   /// ������� ����-������. ���� ������ ������������ ������, ��� ��� ��-�� ����������� ������������ �������� ��������
   /// ����� ����� �������������� � �������� � ����� �������.
   /// </summary>
   SOL_GREN_REORDER_TREE          = 0x00000400,

   SOL_GREN_FINDFACTS             = 0x00001000,
  }

  /// <summary>
  /// ������� ����� ��� ������ ��������� ������� ������ ������.
  /// ����������� ��� �������� ���������� ������ � <see cref="sol_CreateGrammarEngineExW">sol_CreateGrammarEngineExW</see>.
  /// </summary>
  [Flags]
  public enum EngineInstanceFlags
  {
   /// <summary>
   /// ����� ������������� ���������� �� ��������� - ���� ������� �������� � ������ �����.
   /// </summary>
   SOL_GREN_DEFAULT = 0,

  /// <summary>
  /// ���� ����������� ��� �������� ���������� ������ � ������ � ������
  /// ����������� ������� �������� ������: ������ ������ �������� ����� �������
  /// � ������ ��� ����������� ������� ������ ����� ���������� ���������
  /// ������ � ����� �� ���� �������������.
  /// 
  /// ���� ��������� ������� ������ ��� ������������� ��������� ������� �������.
  /// ��� SQL ������� ���������� ������ ������������ �� ���� �������������.
  /// 
  /// Dictionary instance control flag.
  /// 
  /// See http://www.solarix.ru/api/ru/sol_LoadDictionary.shtml for details
  /// </summary>
  SOL_GREN_LAZY_LEXICON = 0x00000001
  }

  /// <summary>
  /// �������� ���������� ��������������� ������ � ������.
  /// ��� �������� ��������� dictConfigPath ����� ����� ���������� ��������� ����.
  /// ������ ������� ��������� ���� �������� ����� � ������. ���� ����������� ��� ���� ������ ������ �
  /// �������� ������������� �����������, ������� ������������ ������� sol_CreateGrammarEngineExW �
  /// ��������� ����� EngineInstanceFlags.SOL_GREN_LAZY_LEXICON.
  /// 
  /// ������-������������: http://www.solarix.ru/api/ru/sol_CreateGrammarEngine.shtml
  /// </summary>
  /// <param name="DictPath">������ ������ ��� ���� � ����� ������������ ��������� ���� (dictionary.xml)</param>
  /// <returns>������������ ���������� ���������� ������ ��� IntPtr.Zero � ����� ������</returns>
  /// <seealso cref="sol_CreateGrammarEngineExW">sol_CreateGrammarEngineExW</seealso>
  [DllImport(gren_dll, CharSet=CharSet.Unicode, CallingConvention=CallingConvention.StdCall)]
  public static extern HGREN sol_CreateGrammarEngineW( string dictConfigPath );

  /// <summary>
  /// �������� ���������� ��������������� ������ � ������.
  /// </summary>
  /// <param name="dictConfigPath">���� � ����� ������������ ������� (������ dictionary.xml)</param>
  /// <param name="instanceFlags">����� ��� ������� ������ ������ ������</param>
  /// <returns></returns>
  [DllImport(gren_dll, CharSet=CharSet.Unicode, CallingConvention=CallingConvention.StdCall)]
  public static extern HGREN sol_CreateGrammarEngineExW( string dictConfigPath, EngineInstanceFlags instanceFlags );

  /// <summary>
  /// ����������� ���������� ��������������� ������ � ������, ������������ ���� ���������� ��������.
  /// ������-������������: http://www.solarix.ru/api/ru/sol_DeleteGrammarEngine.shtml
  /// </summary>
  /// <param name="hEngine">���������� ����������, ������������ ��� ������ sol_CreateGrammarEngineW ��� sol_CreateGrammarEngineExW</param>
  /// <returns>1 ��� ���������� �����������, 0 ��� ������������� ������ (������������ ���������� ����������)</returns>
  [DllImport(gren_dll, CallingConvention=CallingConvention.StdCall)]
  public static extern int sol_DeleteGrammarEngine( HGREN hEngine );

  // http://www.solarix.ru/api/ru/sol_LoadDictionary.shtml
  [DllImport(gren_dll, CharSet=CharSet.Unicode, CallingConvention=CallingConvention.StdCall)]
  public static extern int sol_LoadDictionaryW( HGREN hEngine, System.String dictPath );

  // http://www.solarix.ru/api/ru/sol_LoadDictionary.shtml
  [DllImport(gren_dll, CharSet=CharSet.Unicode, CallingConvention=CallingConvention.StdCall)]
  public static extern int sol_LoadDictionaryExW( HGREN hEngine, System.String dictPath, EngineInstanceFlags flags );

   /// <summary>
   /// ���������� ���������� ������ ����������������� ������ (����� ��������� ���������).
   /// </summary>
   [DllImport(gren_dll, CallingConvention=CallingConvention.StdCall)]
   public static extern int sol_GetVersion( HGREN hEngine, ref int majorNumber, ref int minorNumber, ref int buildNumber );

   /// <summary>
   /// ���������� ����� ������ ������������ �������.
   /// </summary>
   [DllImport(gren_dll, CallingConvention=CallingConvention.StdCall)]
   public static extern int sol_DictionaryVersion( HGREN hEngine );

   // http://www.solarix.ru/api/ru/sol_CountEntries.shtml
   [DllImport(gren_dll, CallingConvention=CallingConvention.StdCall)]
   public static extern int sol_CountEntries( HGREN hEngine );

   [DllImport(gren_dll, CallingConvention=CallingConvention.StdCall)]
   public static extern int sol_CountForms( HGREN hEngine );

   // http://www.solarix.ru/api/ru/sol_CountLinks.shtml
   [DllImport(gren_dll, CallingConvention=CallingConvention.StdCall)]
   public static extern int sol_CountLinks( HGREN hEngine );

   [DllImport(gren_dll, CallingConvention=CallingConvention.StdCall)]
   public static extern void sol_SetLanguage( HGREN hEngine, int LanguageID );

   // http://www.solarix.ru/api/ru/sol_MaxLexemLen.shtml
   [DllImport(gren_dll, CallingConvention=CallingConvention.StdCall)]
   public static extern int sol_MaxLexemLen( HGREN hEngine );

   // http://www.solarix.ru/api/ru/sol_FindEntry.shtml
   [DllImport(gren_dll, CharSet=CharSet.Unicode, CallingConvention=CallingConvention.StdCall)]
   public static extern int sol_FindEntry( HGREN hEngine, string name, int partOfSpeechId, int languageId );

   // http://www.solarix.ru/api/ru/sol_FindClass.shtml
   [DllImport(gren_dll, CharSet=CharSet.Unicode, CallingConvention=CallingConvention.StdCall)]
   public static extern int sol_FindClass( HGREN hEngine, string partOfSpeechName );

   // http://www.solarix.ru/api/ru/sol_FindEnum.shtml
   [DllImport(gren_dll, CharSet=CharSet.Unicode, CallingConvention=CallingConvention.StdCall)]
   public static extern int sol_FindEnum( HGREN hEngine, string attributeName );

   // http://www.solarix.ru/api/ru/sol_FindEnumState.shtml
   [DllImport(gren_dll, CharSet=CharSet.Unicode, CallingConvention=CallingConvention.StdCall)]
   public static extern int sol_FindEnumState( HGREN hEngine, int attributeId, string stateName );

   [DllImport(gren_dll, CharSet=CharSet.Unicode, CallingConvention=CallingConvention.StdCall)]
   public static extern int sol_EnumInClass( HGREN hEngine, int partOfSpeechId, int attributeId );


   [DllImport(gren_dll, CharSet=CharSet.Unicode, CallingConvention=CallingConvention.StdCall)]
   public static extern int sol_FindTagW( HGREN hEngine, string tagName );

   [DllImport(gren_dll, CharSet=CharSet.Unicode, CallingConvention=CallingConvention.StdCall)]
   public static extern int sol_FindTagValueW( HGREN hEngine, int tagID, string valueName );

   [DllImport(gren_dll, CharSet=CharSet.Unicode, CallingConvention=CallingConvention.StdCall)]
   public static extern System.IntPtr sol_FindStringsEx( HGREN hEngine, String name, int Allow_Dynforms,
   int Synonyms, int Grammar_Links, int Translations, int Semantics, int nJumps );

   // http://www.solarix.ru/api/ru/sol_CountStrings.shtml
   [DllImport(gren_dll, CallingConvention=CallingConvention.StdCall)]
   public static extern int sol_CountStrings( System.IntPtr hStr );

   // http://www.solarix.ru/api/ru/sol_GetStringLen.shtml
   [DllImport(gren_dll, CharSet=CharSet.Unicode, CallingConvention=CallingConvention.StdCall)]
   public static extern int sol_GetStringLen( System.IntPtr hStr, int i );

   // http://www.solarix.ru/api/ru/sol_GetString.shtml
   [DllImport(gren_dll, CharSet=CharSet.Unicode, CallingConvention=CallingConvention.StdCall)]
   public static extern int sol_GetStringW( System.IntPtr hStr, int i, System.Text.StringBuilder buffer );

   // http://www.solarix.ru/api/ru/sol_DeleteStrings.shtml
   [DllImport(gren_dll, CallingConvention=CallingConvention.StdCall)]
   public static extern int sol_DeleteStrings( System.IntPtr hStr );



   [DllImport(gren_dll, CallingConvention=CallingConvention.StdCall)]
   public static extern int sol_CountNodeMarks( System.IntPtr hNode );

   [DllImport(gren_dll, CharSet=CharSet.Unicode, CallingConvention=CallingConvention.StdCall)]
   public static extern int sol_GetNodeMarkNameW( System.IntPtr hNode, int mark_index, System.Text.StringBuilder name_buffer );

   [DllImport(gren_dll, CallingConvention=CallingConvention.StdCall)]
   public static extern IntPtr sol_SerializeNodeMark( System.IntPtr hEngine, System.IntPtr hNode, int mark_index, int format );

   [DllImport(gren_dll, CallingConvention=CallingConvention.StdCall)]
   public static extern int sol_GetLongStringLenW( System.IntPtr hString );

   [DllImport(gren_dll, CharSet=CharSet.Unicode, CallingConvention=CallingConvention.StdCall)]
   public static extern int sol_GetLongStringW( System.IntPtr hString, System.Text.StringBuilder buffer );

   [DllImport(gren_dll, CallingConvention=CallingConvention.StdCall)]
   public static extern int sol_DeleteLongString( System.IntPtr hString );



   [DllImport(gren_dll, CharSet=CharSet.Unicode, CallingConvention=CallingConvention.StdCall)]
   public static extern int sol_Stemmer( HGREN hEngine, string Word );

   // http://www.solarix.ru/api/ru/sol_GetEntryName.shtml
   [DllImport(gren_dll, CharSet=CharSet.Unicode, CallingConvention=CallingConvention.StdCall)]
   public static extern int sol_GetEntryName( HGREN hEngine, int EntryID, System.Text.StringBuilder Result );

   // http://www.solarix.ru/api/ru/sol_GetEntryClass.shtml
   [DllImport(gren_dll, CallingConvention=CallingConvention.StdCall)]
   public static extern int sol_GetEntryClass( HGREN hEngine, int EntryID );

   // http://www.solarix.ru/api/ru/sol_GetEntryCoordState.shtml
   [DllImport(gren_dll, CallingConvention=CallingConvention.StdCall)]
   public static extern int sol_GetEntryCoordState( HGREN hEngine, int EntryID, int CategoryID );

   // http://www.solarix.ru/api/ru/sol_FindEntryCoordPair.shtml
   [DllImport(gren_dll, CallingConvention=CallingConvention.StdCall)]
   public static extern int sol_FindEntryCoordPair( HGREN hEngine, int EntryID, int CategoryID, int StateID );

   // http://www.solarix.ru/api/ru/sol_GetClassName.shtml
   [DllImport(gren_dll, CharSet=CharSet.Unicode, CallingConvention=CallingConvention.StdCall)]
   public static extern int sol_GetClassName( HGREN hEngine, int ClassIndex, System.Text.StringBuilder Result );

   public static string sol_GetClassNameFX( IntPtr hEngine, int ClassIndex )
   {
    System.Text.StringBuilder b = new System.Text.StringBuilder();
    b.Capacity=32;
    sol_GetClassName( hEngine, ClassIndex, b );
    return b.ToString();
   }

   // http://www.solarix.ru/api/ru/sol_GetCoordType.shtml
   [DllImport(gren_dll, CharSet=CharSet.Unicode, CallingConvention=CallingConvention.StdCall)]
   public static extern int sol_GetCoordType( HGREN hEngine, int CoordID, int PartOfSpeechID );

   // http://www.solarix.ru/api/ru/sol_GetCoordName.shtml
   [DllImport(gren_dll, CharSet=CharSet.Unicode, CallingConvention=CallingConvention.StdCall)]
   public static extern int sol_GetCoordName( HGREN hEngine, int CoordID, System.Text.StringBuilder Result );

   // http://www.solarix.ru/api/ru/sol_GetCoordStateName.shtml
   [DllImport(gren_dll, CharSet=CharSet.Unicode, CallingConvention=CallingConvention.StdCall)]
   public static extern int sol_GetCoordStateName(
                                                  HGREN hEngine,
                                                  int CoordID,
                                                  int StateID,
                                                  System.Text.StringBuilder Result
                                                 );

   // http://www.solarix.ru/api/en/sol_CountCoordStates.shtml
   [DllImport(gren_dll, CharSet=CharSet.Unicode, CallingConvention=CallingConvention.StdCall)]
   public static extern int sol_CountCoordStates( System.IntPtr h, int CoordID );

   // http://www.solarix.ru/api/en/sol_GetNounGender.shtml
   [DllImport(gren_dll, CallingConvention=CallingConvention.StdCall)]
   public static extern int sol_GetNounGender( System.IntPtr hStr, int EntryIndex );

   [DllImport(gren_dll, CharSet=CharSet.Unicode, CallingConvention=CallingConvention.StdCall)]
   public static extern int sol_GetNounForm( HGREN hEngine, int EntryIndex, int Number, int Case, System.Text.StringBuilder Result );

   [DllImport(gren_dll, CharSet=CharSet.Unicode, CallingConvention=CallingConvention.StdCall)]
   public static extern int sol_GetVerbForm( HGREN hEngine, int EntryIndex,
    int Number, int Gender, int Tense, int Person, System.Text.StringBuilder Result );

   [DllImport(gren_dll, CharSet=CharSet.Unicode, CallingConvention=CallingConvention.StdCall)]
   public static extern int sol_GetAdjectiveForm( HGREN hEngine, int EntryIndex,
    int Number, int Gender, int Case, int Anim, int Shortness, int Compar_Form, System.Text.StringBuilder Result );

   [DllImport(gren_dll, CharSet=CharSet.Unicode, CallingConvention=CallingConvention.StdCall)]
   public static extern int sol_CorrNounNumber( HGREN hEngine, int EntryIndex,
    int Value, int Case, int Anim, System.Text.StringBuilder Result );

   [DllImport(gren_dll, CharSet=CharSet.Unicode, CallingConvention=CallingConvention.StdCall)]
   public static extern int sol_CorrVerbNumber( HGREN hEngine, int EntryIndex,
    int Value, int Gender, int Tense, System.Text.StringBuilder Result );

   [DllImport(gren_dll, CharSet=CharSet.Unicode, CallingConvention=CallingConvention.StdCall)]
   public static extern int sol_CorrAdjNumber( HGREN hEngine, int EntryIndex,
    int Value, int Case, int Gender, int Anim, System.Text.StringBuilder Result );

   [DllImport(gren_dll, CharSet=CharSet.Unicode, CallingConvention=CallingConvention.StdCall)]
   public static extern int sol_Syllabs( IntPtr hEngine, string OrgWord, char SyllabDelimiter, System.Text.StringBuilder Result, int LanguageID );


   [DllImport(gren_dll, CharSet=CharSet.Unicode, CallingConvention=CallingConvention.StdCall)]
   public static extern int sol_FindWord( HGREN hEngine, string Word,
    System.IntPtr EntryIndex, System.IntPtr Form, System.IntPtr Class );

   [DllImport(gren_dll, CharSet=CharSet.Unicode, CallingConvention=CallingConvention.StdCall)]
   public static extern int sol_SeekWord( HGREN hEngine, string Word, int Allow_Dynforms );

   [DllImport(gren_dll, CharSet=CharSet.Unicode, CallingConvention=CallingConvention.StdCall)]
   public static extern int sol_TranslateToNoun( HGREN hEngine, int EntryIndex );

   [DllImport(gren_dll, CharSet=CharSet.Unicode, CallingConvention=CallingConvention.StdCall)]
   public static extern int sol_TranslateToInfinitive( HGREN hEngine, int EntryIndex );

   [DllImport(gren_dll, CharSet=CharSet.Unicode, CallingConvention=CallingConvention.StdCall)]
   public static extern System.IntPtr sol_TranslateToBases( HGREN hEngine, string Word, int AllowDynforms );

   // http://www.solarix.ru/api/ru/sol_ProjectWord.shtml
   [DllImport(gren_dll, CharSet=CharSet.Unicode, CallingConvention=CallingConvention.StdCall)]
   public static extern System.IntPtr sol_ProjectWord( HGREN hEngine, string Word, int AllowDynforms );

   [DllImport(gren_dll, CharSet=CharSet.Unicode, CallingConvention=CallingConvention.StdCall)]
   public static extern System.IntPtr sol_ProjectMisspelledWord( HGREN hEngine, string Word, int AllowDynforms, int nmaxmiss );

   // http://www.solarix.ru/api/ru/sol_CountProjections.shtml
   [DllImport(gren_dll, CallingConvention=CallingConvention.StdCall)]
   public static extern int sol_CountProjections( System.IntPtr hList );

   // http://www.solarix.ru/api/ru/sol_DeleteProjections.shtml
   [DllImport(gren_dll, CallingConvention=CallingConvention.StdCall)]
   public static extern void sol_DeleteProjections( System.IntPtr hList );

   // http://www.solarix.ru/api/ru/sol_GetIEntry.shtml
   [DllImport(gren_dll, CallingConvention=CallingConvention.StdCall)]
   public static extern int sol_GetIEntry( System.IntPtr hList, int Index );

   // http://www.solarix.ru/api/ru/sol_GetProjCoordState.shtml
   [DllImport(gren_dll, CallingConvention=CallingConvention.StdCall)]
   public static extern int sol_GetProjCoordState( HGREN hEngine, System.IntPtr hList, int Index, int Coord );

   // http://www.solarix.ru/api/ru/sol_GetNounGender.shtml
   [DllImport(gren_dll, CallingConvention=CallingConvention.StdCall)]
   public static extern void sol_DeleteResPack( System.IntPtr hPack );

   // http://www.solarix.ru/api/ru/sol_CountGrafs.shtml
   [DllImport(gren_dll, CallingConvention=CallingConvention.StdCall)]
   public static extern int sol_CountGrafs( System.IntPtr hPack );

   // http://www.solarix.ru/api/ru/sol_CountRoots.shtml
   [DllImport(gren_dll, CallingConvention=CallingConvention.StdCall)]
   public static extern int sol_CountRoots( System.IntPtr hPack, int iGraf );

   // http://www.solarix.ru/api/ru/sol_GetRoot.shtml
   [DllImport(gren_dll, CallingConvention=CallingConvention.StdCall)]
   public static extern System.IntPtr sol_GetRoot( System.IntPtr hPack, int iGraf, int iRoot );

   // http://www.solarix.ru/api/ru/sol_CountLeafs.shtml
   [DllImport(gren_dll, CallingConvention=CallingConvention.StdCall)]
   public static extern int sol_CountLeafs( System.IntPtr hNode );

   // http://www.solarix.ru/api/ru/sol_GetLeaf.shtml
   [DllImport(gren_dll, CallingConvention=CallingConvention.StdCall)]
   public static extern System.IntPtr sol_GetLeaf( System.IntPtr hNode, int iLeaf );

   // http://www.solarix.ru/api/ru/sol_GetNodeVersionCount.shtml
   [DllImport(gren_dll, CallingConvention=CallingConvention.StdCall)]
   public static extern int sol_GetNodeVersionCount( HGREN hEngine, System.IntPtr hNode );

   // http://www.solarix.ru/api/ru/sol_GetLeafLinkType.shtml
   [DllImport(gren_dll, CallingConvention=CallingConvention.StdCall)]
   public static extern int sol_GetLeafLinkType( System.IntPtr hNode, int iLeaf );


   // http://www.solarix.ru/api/ru/sol_GetNodeIEntry.shtml
   [DllImport(gren_dll, CallingConvention=CallingConvention.StdCall)]
   public static extern int sol_GetNodeIEntry( HGREN hEngine, System.IntPtr hNode );

  // http://www.solarix.ru/api/ru/sol_GetNodeVerIEntry.shtml
  [DllImport(gren_dll, CharSet = CharSet.Unicode, CallingConvention = CallingConvention.StdCall)]
  public static extern int sol_GetNodeVerIEntry( IntPtr hEngine, IntPtr hNode, int ialt );

   // http://www.solarix.ru/api/ru/sol_GetNodeContents.shtml
   [DllImport(gren_dll, CharSet=CharSet.Unicode, CallingConvention=CallingConvention.StdCall)]
   public static extern void sol_GetNodeContents( System.IntPtr hNode, System.Text.StringBuilder Result );

   // http://www.solarix.ru/api/ru/sol_GetNodePosition.shtml
   [DllImport(gren_dll, CharSet=CharSet.Unicode, CallingConvention=CallingConvention.StdCall)]
   public static extern int sol_GetNodePosition( System.IntPtr hNode );

   // http://www.solarix.ru/api/ru/sol_GetNodeCoordState.shtml
   [DllImport(gren_dll, CallingConvention=CallingConvention.StdCall)]
   public static extern int sol_GetNodeCoordState( System.IntPtr hNode, int CoordID );

   // http://www.solarix.ru/api/ru/sol_GetNodeVerCoordState.shtml
   [DllImport(gren_dll, CallingConvention=CallingConvention.StdCall)]
   public static extern int sol_GetNodeVerCoordState( System.IntPtr hNode, int iver, int CoordID );

   // http://www.solarix.ru/api/ru/sol_GetNodeCoordPair.shtml
   [DllImport(gren_dll, CallingConvention=CallingConvention.StdCall)]
   public static extern int sol_GetNodeCoordPair( System.IntPtr hNode, int CoordID, int StateID );

   // http://www.solarix.ru/api/ru/sol_GetNodeVerCoordPair.shtml
   [DllImport(gren_dll, CallingConvention=CallingConvention.StdCall)]
   public static extern int sol_GetNodeVerCoordPair( System.IntPtr hNode, int iver, int CoordID, int StateID );

   // http://www.solarix.ru/api/ru/sol_GetNodePairsCount.shtml
   [DllImport(gren_dll, CallingConvention=CallingConvention.StdCall)]
   public static extern int sol_GetNodePairsCount( System.IntPtr hNode );

   // http://www.solarix.ru/api/ru/sol_GetNodeVerPairsCount.shtml
   [DllImport(gren_dll, CallingConvention=CallingConvention.StdCall)]
   public static extern int sol_GetNodeVerPairsCount( System.IntPtr hNode, int iver );

   // http://www.solarix.ru/api/ru/sol_GetNodePairCoord.shtml
   [DllImport(gren_dll, CallingConvention=CallingConvention.StdCall)]
   public static extern int sol_GetNodePairCoord( System.IntPtr hNode, int ipair );

   // http://www.solarix.ru/api/ru/sol_GetNodeVerPairCoord.shtml
   [DllImport(gren_dll, CallingConvention=CallingConvention.StdCall)]
   public static extern int sol_GetNodeVerPairCoord( System.IntPtr hNode, int iver, int ipair );

   // http://www.solarix.ru/api/ru/sol_GetNodePairState.shtml
   [DllImport(gren_dll, CallingConvention=CallingConvention.StdCall)]
   public static extern int sol_GetNodePairState( System.IntPtr hNode, int ipair );

   // http://www.solarix.ru/api/ru/sol_GetNodeVerPairState.shtml
   [DllImport(gren_dll, CallingConvention=CallingConvention.StdCall)]
   public static extern int sol_GetNodeVerPairState( System.IntPtr hNode, int iver, int ipair );

   // http://www.solarix.ru/api/ru/sol_CountInts.shtml
   [DllImport(gren_dll, CallingConvention=CallingConvention.StdCall)]
   public static extern int sol_CountInts( System.IntPtr hInts );

   // http://www.solarix.ru/api/ru/sol_GetInt.shtml
   [DllImport(gren_dll, CallingConvention=CallingConvention.StdCall)]
   public static extern int sol_GetInt( System.IntPtr hInts, int i );

   // http://www.solarix.ru/api/ru/sol_DeleteInts.shtml
   [DllImport(gren_dll, CallingConvention=CallingConvention.StdCall)]
   public static extern void sol_DeleteInts( System.IntPtr hInts );

   [DllImport(gren_dll, CharSet = CharSet.Unicode, CallingConvention=CallingConvention.StdCall)]
   public static extern IntPtr sol_SeekThesaurus( IntPtr hEngine, int EntryIndex, int Synonyms, int Grammar_Links, int Translation, int Semantics, int nJumps );

   // *********************************************************************************
   // N-grams database functions
   // Overview on Russian: http://www.solarix.ru/for_developers/api/ngrams-api.shtml
   // *********************************************************************************

   // http://www.solarix.ru/api/en/sol_CountNGrams.shtml
   [DllImport(gren_dll, CharSet = CharSet.Unicode, CallingConvention=CallingConvention.StdCall)]
   public static extern int sol_CountNGrams( HGREN hEngine, int Type, int Order, out UInt32 Hi, out UInt32 Lo );

   // This is a simple and helpful wrapper for low-level sol_CountNGrams. It returns the 64 bit count value.
   public static UInt64 sol_CountNGramsFX( IntPtr hEngine, int Type, int Order )
   {
    UInt32 Hi=0, Lo=0;
    if( sol_CountNGrams( hEngine, Type, Order, out Hi, out Lo )==0 )
     return 0;
    
    UInt64 res = ( ((UInt64)Hi) << 32 ) | Lo;
    return res;
   }

   // http://www.solarix.ru/api/ru/sol_Seek1Grams.shtml
   [DllImport(gren_dll, CharSet = CharSet.Unicode, CallingConvention=CallingConvention.StdCall)]
   public static extern int sol_Seek1Grams( IntPtr hEngine, int Type, String word1 );

   // http://www.solarix.ru/api/ru/sol_Seek2Grams.shtml
   [DllImport(gren_dll, CharSet = CharSet.Unicode, CallingConvention=CallingConvention.StdCall)]
   public static extern int sol_Seek2Grams( IntPtr hEngine, int Type, String word1, String word2 );

   // http://www.solarix.ru/api/ru/sol_Seek3Grams.shtml
   [DllImport(gren_dll, CharSet = CharSet.Unicode, CallingConvention=CallingConvention.StdCall)]
   public static extern int sol_Seek3Grams( IntPtr hEngine, int Type, String word1, String word2, String word3 );

   // http://www.solarix.ru/api/ru/sol_Seek4Grams.shtml
   [DllImport(gren_dll, CharSet = CharSet.Unicode, CallingConvention=CallingConvention.StdCall)]
   public static extern int sol_Seek4Grams( IntPtr hEngine, int Type, String word1, String word2, String word3, String word4 );

   // http://www.solarix.ru/api/ru/sol_Seek5Grams.shtml
   [DllImport(gren_dll, CharSet = CharSet.Unicode, CallingConvention=CallingConvention.StdCall)]
   public static extern int sol_Seek5Grams( IntPtr hEngine, int Type, String word1, String word2, String word3, String word4, String word5 );

  // --- SentenceBroker API --- 

  // http://www.solarix.ru/api/ru/sol_CreateSentenceBroker.shtml
  [DllImport(gren_dll, CharSet=CharSet.Unicode, CallingConvention=CallingConvention.StdCall)]
  public static extern IntPtr sol_CreateSentenceBroker( HGREN hEngine, string Filename, string DefaultCodepage, int language );

  // http://www.solarix.ru/api/ru/sol_CreateSentenceBrokerMem.shtml
  [DllImport(gren_dll, CharSet=CharSet.Unicode, CallingConvention=CallingConvention.StdCall)]
  public static extern IntPtr sol_CreateSentenceBrokerMemW( HGREN hEngine, string Text, int language );

  // http://www.solarix.ru/api/ru/sol_FetchSentence.shtml
  [DllImport(gren_dll, CharSet=CharSet.Unicode, CallingConvention=CallingConvention.StdCall)]
  public static extern int sol_FetchSentence( System.IntPtr hBroker );

  // http://www.solarix.ru/api/ru/sol_GetFetchedSentenceLen.shtml
  [DllImport(gren_dll, CharSet=CharSet.Unicode, CallingConvention=CallingConvention.StdCall)]
  public static extern int sol_GetFetchedSentenceLen( System.IntPtr hBroker );

  // http://www.solarix.ru/api/ru/sol_GetFetchedSentence.shtml
  [DllImport(gren_dll, CharSet=CharSet.Unicode, CallingConvention=CallingConvention.StdCall)]
  public static extern int sol_GetFetchedSentence( System.IntPtr hBroker, System.Text.StringBuilder Buffer );

  // http://www.solarix.ru/api/ru/sol_DeleteSentenceBroker.shtml
  [DllImport(gren_dll, CharSet=CharSet.Unicode, CallingConvention=CallingConvention.StdCall)]
  public static extern void sol_DeleteSentenceBroker( System.IntPtr hBroker );

  // http://www.solarix.ru/api/ru/sol_Tokenize.shtml
  [DllImport(gren_dll, CharSet=CharSet.Unicode, CallingConvention=CallingConvention.StdCall)]
  public static extern IntPtr sol_TokenizeW( HGREN hEngine, string Text, int language );

  [DllImport(gren_dll, CallingConvention = CallingConvention.StdCall)]
   public static extern int sol_Bits();

  // http://www.solarix.ru/api/ru/sol_ListLinksTxt.shtml
  [DllImport(gren_dll, CallingConvention = CallingConvention.StdCall)]
  public static extern IntPtr sol_ListLinksTxt( IntPtr hEng, int Key1, int LinkType, int Flags );

  // http://www.solarix.ru/api/ru/sol_DeleteLinksInfo.shtml
  [DllImport(gren_dll, CallingConvention = CallingConvention.StdCall)]
  public static extern int sol_DeleteLinksInfo(IntPtr hEng, IntPtr /*HLINKSINFO*/ hList);

  // http://www.solarix.ru/api/ru/sol_LinksInfoCount.shtml
  [DllImport(gren_dll, CallingConvention = CallingConvention.StdCall)]
   public static extern int sol_LinksInfoCount(IntPtr hEng, IntPtr /*HLINKSINFO*/ hList);

  // http://www.solarix.ru/api/ru/sol_LinksInfoType.shtml
  [DllImport(gren_dll, CallingConvention = CallingConvention.StdCall)]
   public static extern int sol_LinksInfoType(IntPtr hEng, IntPtr /*HLINKSINFO*/ hList, int Index);

  // http://www.solarix.ru/api/ru/sol_LinksInfoID.shtml
  [DllImport(gren_dll, CallingConvention = CallingConvention.StdCall)]
   public static extern int sol_LinksInfoID(IntPtr hEng, IntPtr /*HLINKSINFO*/ hList, int Index);

  // http://www.solarix.ru/api/ru/sol_LinksInfoEKey1.shtml
  [DllImport(gren_dll, CallingConvention = CallingConvention.StdCall)]
   public static extern int sol_LinksInfoEKey1(IntPtr hEng, IntPtr /*HLINKSINFO*/ hList, int Index);

  // http://www.solarix.ru/api/ru/sol_LinksInfoEKey2.shtml
  [DllImport(gren_dll, CallingConvention = CallingConvention.StdCall)]
   public static extern int sol_LinksInfoEKey2(IntPtr hEng, IntPtr /*HLINKSINFO*/ hList, int Index);

  // http://www.solarix.ru/api/ru/sol_LinksInfoTagsTxt.shtml
  [DllImport(gren_dll, CharSet=CharSet.Unicode, CallingConvention=CallingConvention.StdCall)]
   public static extern /*wchar_t**/ IntPtr sol_LinksInfoTagsTxt(IntPtr hEng, IntPtr /*HLINKSINFO*/ hList, int Index);

  // http://www.solarix.ru/api/ru/sol_LinksInfoFlagsTxt.shtml
  [DllImport(gren_dll, CharSet=CharSet.Unicode, CallingConvention=CallingConvention.StdCall)]
  public static extern /*wchar_t**/ IntPtr sol_LinksInfoFlagsTxt(IntPtr hEng, IntPtr /*HLINKSINFO*/ hList, int Index);

  // http://www.solarix.ru/api/ru/sol_DeleteLink.shtml
  [DllImport(gren_dll, CallingConvention = CallingConvention.StdCall)]
   public static extern int sol_DeleteLink(IntPtr hEng, int LinkID, int LinkType);

  // http://www.solarix.ru/api/ru/sol_AddLink.shtml
  [DllImport(gren_dll, CharSet=CharSet.Unicode, CallingConvention=CallingConvention.StdCall)]
   public static extern int sol_AddLink(IntPtr hEng, int LinkType, int IE1, int LinkCode, int IE2, string Tags);


  // http://www.solarix.ru/api/ru/sol_FindLanguage.shtml
  [DllImport(gren_dll, CharSet=CharSet.Unicode, CallingConvention=CallingConvention.StdCall)]
   public static extern int sol_FindLanguage( IntPtr hEng, string LanguageName );

   /// <summary>
   /// Find a phrase given a phrase text.
   /// <para>http://www.solarix.ru/api/en/sol_FindPhrase.shtml</para>
   /// </summary>
  [DllImport(gren_dll, CharSet=CharSet.Unicode, CallingConvention=CallingConvention.StdCall)]
   public static extern int sol_FindPhrase( IntPtr hEng, string Phrase, int Flags );

   /// <summary>
   /// Create new phrase entry in lexicon.
   /// <para>http://www.solarix.ru/api/en/sol_AddPhrase.shtml</para>
   /// </summary>
  [DllImport(gren_dll, CharSet=CharSet.Unicode, CallingConvention=CallingConvention.StdCall)]
   public static extern int sol_AddPhrase( IntPtr hEng, string Phrase, int LanguageID, int ClassID, int ProcessingFlags );

   /// <summary>
   /// Retrieve the text contents of the phrase.
   /// <para>http://www.solarix.ru/api/en/sol_GetPhraseText.shtml</para>
   /// </summary>
  [DllImport(gren_dll, CallingConvention = CallingConvention.StdCall)]
   public static extern /*wchar_t**/ IntPtr sol_GetPhraseText( IntPtr hEng, int PhraseId );

  public static string sol_GetPhraseTextFX( IntPtr hEngine, int PhraseId )
  {
   IntPtr wchar_ptr = sol_GetPhraseText(hEngine,PhraseId);
   
   if( wchar_ptr==(IntPtr)null )
    return "";

   string res = Marshal.PtrToStringUni(wchar_ptr);
   sol_Free(hEngine,wchar_ptr);
   return res;
  }

   /// <summary>
   /// Get the language ID if it was set for the phrase
   /// <para>http://www.solarix.ru/api/en/sol_GetPhraseLanguage.shtml</para>
   /// </summary>
  [DllImport(gren_dll, CallingConvention = CallingConvention.StdCall)]
   public static extern int sol_GetPhraseLanguage( IntPtr hEng, int PhraseId );
  
   /// <summary>
   /// Get the part of speech ID if it was set for the phrase
   /// <para>http://www.solarix.ru/api/en/sol_GetPhraseClass.shtml</para>
   /// </summary>
  [DllImport(gren_dll, CallingConvention = CallingConvention.StdCall)]
   public static extern int sol_GetPhraseClass( IntPtr hEng, int PhraseId );
  

  // http://www.solarix.ru/api/ru/sol_Free.shtml
  [DllImport(gren_dll, CallingConvention = CallingConvention.StdCall)]
  public static extern int sol_Free(IntPtr hEngine, IntPtr ptr);


  public static string sol_LinksInfoTagsTxtFX(IntPtr hEngine, IntPtr /*HLINKSINFO*/ hList, int Index )
  {
   IntPtr wchar_ptr = sol_LinksInfoTagsTxt( hEngine, hList, Index );

   if( wchar_ptr==(IntPtr)null )
    return "";
    
   string res = Marshal.PtrToStringUni(wchar_ptr);
   return res;
  }  

  
  public static string sol_LinksInfoFlagsTxtFX(IntPtr hEngine, IntPtr /*HLINKSINFO*/ hList, int Index )
  {
   IntPtr wchar_ptr = sol_LinksInfoFlagsTxt( hEngine, hList, Index );

   if( wchar_ptr==(IntPtr)null )
    return "";
    
   string res = Marshal.PtrToStringUni(wchar_ptr);
   return res;
  }  

  // http://www.solarix.ru/api/ru/sol_AddWord.shtml
  [DllImport(gren_dll, CharSet=CharSet.Unicode, CallingConvention=CallingConvention.StdCall)]
  public static extern int sol_AddWord( IntPtr hEng, string Txt );

  [DllImport(gren_dll, CharSet=CharSet.Unicode, CallingConvention=CallingConvention.StdCall)]
  public static extern int sol_ProcessPhraseEntry(
                                                  IntPtr hEngine,
                                                  int PhraseId,
                                                  string Scenario,
                                                  int Language,
                                                  char DelimiterChar
                                                 );

  // http://www.solarix.ru/api/ru/sol_DeletePhrase.shtml
  [DllImport(gren_dll, CharSet=CharSet.Unicode, CallingConvention=CallingConvention.StdCall)]
  public static extern int sol_DeletePhrase( IntPtr hEngine, int PhraseId );


  // http://www.solarix.ru/api/ru/sol_ListEntries.shtml
  [DllImport(gren_dll, CharSet = CharSet.Unicode, CallingConvention = CallingConvention.StdCall)]
  public static extern IntPtr /*HGREN_INTARRAY*/ sol_ListEntries(IntPtr hEng, int Flags, int EntryType, string Mask, int Language, int Class);


  [DllImport(gren_dll, CharSet = CharSet.Unicode, CallingConvention = CallingConvention.StdCall)]
  public static extern int sol_SaveDictionary( IntPtr hEngine, int Flags, string Folder );


  /// <summary>
  /// ���������� ���������������� ������� ��� ���� � ��������� �����������.
  /// � ��� ����� ����� ��������� ����������� �������� � �������������� ������������� ������ �����, ���� ���
  /// ���������� � �������.
  /// http://www.solarix.ru/api/ru/sol_MorphologyAnalysis.shtml
  /// </summary>
  /// <returns>������������ ���������� ��������� � ������������ ������� (��. ��������� <see cref="sol_CountRoots">sol_CountRoots</see> � ������)</returns>
  [DllImport(gren_dll, CharSet = CharSet.Unicode, CallingConvention = CallingConvention.StdCall)]
  public static extern IntPtr /*HGREN_RESPACK*/ sol_MorphologyAnalysis(
                                                                       IntPtr hEngine,
                                                                       string sentence,
                                                                       MorphologyFlags flags,
                                                                       SyntaxFlags unusedFlags,
                                                                       int constraints,
                                                                       int languageId
                                                                      );

  /// <summary>
  /// ���������� ��������������� ������� �����������.
  /// http://www.solarix.ru/api/ru/sol_SyntaxAnalysis.shtml
  /// </summary>
  /// <returns>������������ ���������� ��������� � ������������ ������� (��. ��������� <see cref="sol_CountRoots">sol_CountRoots</see> � ������)</returns>
  [DllImport(gren_dll, CharSet=CharSet.Unicode, CallingConvention=CallingConvention.StdCall)]
   public static extern System.IntPtr sol_SyntaxAnalysis(
                                                         HGREN hEngine,
                                                         string sentence,
                                                         MorphologyFlags flags,
                                                         SyntaxFlags unusedFlags,
                                                         int constraints,
                                                         int languageID
                                                        );


  [DllImport(gren_dll, CharSet = CharSet.Unicode, CallingConvention = CallingConvention.StdCall)]
  public static extern IntPtr /*HFLEXIONS*/ sol_FindFlexionHandlers( IntPtr hEnging, string WordBasicForm, int SearchEntries );

  [DllImport(gren_dll, CharSet = CharSet.Unicode, CallingConvention = CallingConvention.StdCall)]
  public static extern int sol_DeleteFlexionHandlers( IntPtr hEngine, IntPtr /*HFLEXIONS*/ hFlexs );

  [DllImport(gren_dll, CharSet = CharSet.Unicode, CallingConvention = CallingConvention.StdCall)]
  public static extern int sol_CountEntriesInFlexionHandlers( IntPtr hEngine, IntPtr /*HFLEXIONS*/ hFlexs );

  [DllImport(gren_dll, CharSet = CharSet.Unicode, CallingConvention = CallingConvention.StdCall)]
  public static extern int sol_CountParadigmasInFlexionHandlers( IntPtr hEngine, IntPtr /*HFLEXIONS*/ hFlexs );

  [DllImport(gren_dll, CharSet = CharSet.Unicode, CallingConvention = CallingConvention.StdCall)]
  public static extern int sol_GetEntryInFlexionHandlers( IntPtr hEngine, IntPtr /*HFLEXIONS*/ hFlexs, int Index );

  [DllImport(gren_dll, CharSet = CharSet.Unicode, CallingConvention = CallingConvention.StdCall)]
  public static extern int sol_GetParadigmaInFlexionHandlers( IntPtr hEngine, IntPtr /*HFLEXIONS*/ hFlexs, int Index, System.Text.StringBuilder ParadigmaName );

  [DllImport(gren_dll, CharSet = CharSet.Unicode, CallingConvention = CallingConvention.StdCall)]
  public static extern IntPtr /*HFLEXIONTABLE*/ sol_BuildFlexionHandler(
                                                                        IntPtr hEngine,
                                                                        IntPtr /*HFLEXIONS*/ hFlexs,
                                                                        string ParadigmaName,
                                                                        int EntryIndex
                                                                       );

  [DllImport(gren_dll, CharSet = CharSet.Unicode, CallingConvention = CallingConvention.StdCall)]
  public static extern IntPtr /*const wchar_t* */ sol_GetFlexionHandlerWordform(
                                                                                IntPtr hEngine,
                                                                                IntPtr /*HFLEXIONTABLE*/ hFlex,
                                                                                string dims
                                                                               );

  public static string sol_GetFlexionHandlerWordformFX(
                                                       IntPtr hEngine,
                                                       IntPtr /*HFLEXIONTABLE*/ hFlex,
                                                       string dims
                                                      )
  {
   IntPtr wchar_ptr = sol_GetFlexionHandlerWordform( hEngine, hFlex, dims );

   if( wchar_ptr==(IntPtr)null )
    return "";
    
   string res = Marshal.PtrToStringUni(wchar_ptr);
   return res;
  }


  [DllImport(gren_dll, CharSet = CharSet.Unicode, CallingConvention = CallingConvention.StdCall)]
  public static extern int sol_DeleteFlexionHandler( IntPtr hEngine, IntPtr /*HFLEXIONTABLE*/ hFlex );

  // http://www.solarix.ru/api/ru/sol_SetLinkFlags.shtml
  [DllImport(gren_dll, CharSet = CharSet.Unicode, CallingConvention = CallingConvention.StdCall)]
  public static extern int sol_SetLinkFlags( IntPtr hEngine, int id_link, string Flags );

  // http://www.solarix.ru/api/ru/sol_SetLinkTags.shtml
  [DllImport(gren_dll, CharSet = CharSet.Unicode, CallingConvention = CallingConvention.StdCall)]
  public static extern int sol_SetLinkTags( IntPtr hEngine, int LinkType, int id_link, string Tags );

  [DllImport(gren_dll, CharSet = CharSet.Unicode, CallingConvention = CallingConvention.StdCall)]
  public static extern int sol_SetPhraseNote( IntPtr hEngine, int te_id, string Name, string Value );

  [DllImport(gren_dll, CallingConvention = CallingConvention.StdCall)]
  public static extern int sol_ReserveLexiconSpace( IntPtr hEngine, int n );

  // http://www.solarix.ru/api/ru/sol_GetError.shtml
  [DllImport(gren_dll, CharSet = CharSet.Unicode, CallingConvention = CallingConvention.StdCall)]
  public static extern int sol_GetError( IntPtr hEngine, System.Text.StringBuilder buffer, int buffer_len );

  // http://www.solarix.ru/api/ru/sol_GetErrorLen.shtml
  [DllImport(gren_dll, CharSet = CharSet.Unicode, CallingConvention = CallingConvention.StdCall)]
  public static extern int sol_GetErrorLen( IntPtr hEngine );

  // http://www.solarix.ru/api/ru/sol_ClearError.shtml
  [DllImport(gren_dll, CharSet = CharSet.Unicode, CallingConvention = CallingConvention.StdCall)]
  public static extern int sol_ClearError( IntPtr hEngine );

  public static string sol_GetErrorFX( IntPtr hEngine )
  {
   int len = sol_GetErrorLen(hEngine);
   if( len==0 )
    return "";

   System.Text.StringBuilder b = new System.Text.StringBuilder( len+1 );
   sol_GetError( hEngine, b, len );
   sol_ClearError(hEngine);
   return b.ToString();
  }


  // http://www.solarix.ru/api/ru/sol_RestoreCasing.shtml
  [DllImport(gren_dll, CharSet = CharSet.Unicode, CallingConvention = CallingConvention.StdCall)]
  public static extern int sol_RestoreCasing( IntPtr hEngine, [In,Out] System.Text.StringBuilder Word, int EntryIndex );

  [DllImport(gren_dll, CharSet = CharSet.Unicode, CallingConvention = CallingConvention.StdCall)]
  public static extern IntPtr sol_GenerateWordforms( HGREN hEngine, int EntryID, int npairs, [MarshalAs(UnmanagedType.LPArray, SizeParamIndex=2)] int[] pairs );


  // -----------------------------


  [DllImport(gren_dll, CharSet=CharSet.Ansi, CallingConvention=CallingConvention.StdCall)]
  public static extern IntPtr sol_OpenCorpusStorage8( HGREN hEngine, string Filename, bool for_writing );

  [DllImport(gren_dll, CallingConvention=CallingConvention.StdCall)]
  public static extern int sol_CloseCorpusStorage( HGREN hEngine, IntPtr hStream );

  [DllImport(gren_dll, CharSet = CharSet.Unicode, CallingConvention=CallingConvention.StdCall)]
  public static extern int sol_WriteSyntaxTree( HGREN hEngine, IntPtr hStream, string Sentence, IntPtr hTree );

  [DllImport(gren_dll, CallingConvention=CallingConvention.StdCall)]
  public static extern IntPtr sol_LoadSyntaxTree( HGREN hEngine, IntPtr hStream );

  [DllImport(gren_dll, CallingConvention=CallingConvention.StdCall)]
  public static extern IntPtr sol_GetTreeHandle( IntPtr hData );

  [DllImport(gren_dll, CharSet=CharSet.Unicode, CallingConvention=CallingConvention.StdCall)]
  [return: MarshalAs(UnmanagedType.LPWStr)]
  public static extern string sol_GetSentenceW( IntPtr hData );
 
  [DllImport(gren_dll, CallingConvention=CallingConvention.StdCall)]
  public static extern int sol_FreeSyntaxTree( IntPtr hTree );



  // -----------------------------


  public static System.Collections.ArrayList sol_GenerateWordformsFX( HGREN hEngine, int EntryID, System.Collections.ArrayList CoordID, System.Collections.ArrayList StateID )
  {
   int npairs = CoordID.Count;
   int[] pairs = new int[npairs*2];
   for( int i=0, j=0; i<npairs; ++i )
    {
     pairs[j++] = (int)CoordID[i];
     pairs[j++] = (int)StateID[i];
    }

   System.Collections.ArrayList res = new System.Collections.ArrayList();
   IntPtr hStr = sol_GenerateWordforms( hEngine, EntryID, npairs, pairs );
   if( hStr != (IntPtr)0 )
    {
     int nstr = sol_CountStrings(hStr);
     for( int k=0; k<nstr; ++k )
      res.Add( sol_GetStringFX( hStr, k ) );

     sol_DeleteStrings(hStr);
    }
   
   return res; 
  }


  public static string sol_GetStringFX( IntPtr hToks, int i )
  {
   int string_len = sol_GetStringLen( hToks, i );
   System.Text.StringBuilder b = new System.Text.StringBuilder(string_len+1);
   sol_GetStringW( hToks, i, b );
   return b.ToString();
  }

  /// <summary>
  /// ��������� �������� ��������� ������ (������ ��� ����������, ��������� ����� �����) � ��������� ID.
  /// </summary>
  public static string sol_GetEntryNameFX( IntPtr hEngine, int entryId )
  {
   System.Text.StringBuilder b = new System.Text.StringBuilder(32); // ���������� ��������� 32 - ���������� ������ ���� ������� 32 �������� � �������� ���.
   sol_GetEntryName( hEngine, entryId, b );
   return b.ToString();
  }


  public static string sol_GetCoordNameFX( IntPtr hEngine, int coordID )
  {
   System.Text.StringBuilder b = new System.Text.StringBuilder(32);
   sol_GetCoordName( hEngine, coordID, b );
   return b.ToString();
  }

  public static string sol_GetCoordStateNameFX( IntPtr hEngine, int coordID, int stateID )
  {
   System.Text.StringBuilder b = new System.Text.StringBuilder(32);
   sol_GetCoordStateName( hEngine, coordID, stateID, b );
   return b.ToString();
  }


  public static string sol_RestoreCasingFX( IntPtr hEngine, string Word, int id_entry )
  {
   System.Text.StringBuilder b = new System.Text.StringBuilder(32);
   b.Append(Word);
   sol_RestoreCasing( hEngine, b, id_entry );
   return b.ToString();
  }

  public static string sol_GetNodeContentsFX( IntPtr hNode )
  {
   System.Text.StringBuilder b = new System.Text.StringBuilder(32);
   sol_GetNodeContents( hNode, b );
   return b.ToString();
  }

  /// <summary>
  /// ��������� ������ � ������� ������ ��������������� ������ � ���� "XX.YY.ZZ ��������"
  /// </summary>
  public static string sol_GetVersionFX( IntPtr hEngine )
  {
   int Major=0, Minor=0, Build=0;
   int bits = GrammarEngine.sol_Bits();
   string bits_str = bits==64 ? "x64" : "x86";
   GrammarEngine.sol_GetVersion( hEngine, ref Major, ref Minor, ref Build );
   return string.Format( "{0}.{1}.{2} {3}", Major, Minor, Build, bits_str );
  }

  public static int[] sol_SeekThesaurusFX( IntPtr hEngine, int EntryID, bool Synonyms, bool Grammar_Links, bool Translation, bool Semantics, int nJumps )
  {
   IntPtr hList = sol_SeekThesaurus( hEngine, EntryID, Synonyms ? 1 : 0, Grammar_Links ? 1 : 0, Translation ? 1 : 0, Semantics ? 1 : 0, nJumps );
   if( hList!=(IntPtr)0 )
    {
     int n = sol_CountInts( hList );
     int[] res = new int[n];
     for( int i=0; i<n; ++i )
      res[i] = sol_GetInt( hList, i );

     sol_DeleteInts(hList);
     return res;
    }
   else
    {
     return new int[0];
    }
  }


  // Split the string into words and return the list of these words.
  // Language-specific rules are used to process dots, hyphens etc.
  public static string[] sol_TokenizeFX( IntPtr hEngine, string Text, int LanguageID )
  {
   IntPtr hTokens = sol_TokenizeW( hEngine, Text, LanguageID );

   string[] tokens=null;
   int max_word_len = sol_MaxLexemLen(hEngine)+1;

   if( hTokens!=(IntPtr)null )
    {
     int ntoken = sol_CountStrings( hTokens );
     tokens = new string[ntoken];
   
     System.Text.StringBuilder buffer = new System.Text.StringBuilder(max_word_len);
     for( int i=0; i<ntoken; ++i )
      {
       buffer.Length=0;
       sol_GetStringW( hTokens, i, buffer );
       tokens[i] = buffer.ToString();
      }

     sol_DeleteStrings(hTokens);
    }

   return tokens;   
  }

  /// <summary>
  /// ��������� ���������� ����������� �� ������������ ������.
  /// </summary>
  /// <param name="hBroker">���������� ������������ ������, ���������, ��������, � ������� <see cref="sol_CreateSentenceBroker">sol_CreateSentenceBroker</see></param>
  /// <returns>�����������, ����������� �� �������� ������ ������������</returns>
  public static string sol_GetFetchedSentenceFX( System.IntPtr hBroker )
  {
   int sentence_length = sol_GetFetchedSentenceLen(hBroker);
   System.Text.StringBuilder b = new System.Text.StringBuilder(sentence_length+2);
   sol_GetFetchedSentence( hBroker, b );
   return b.ToString();
  }


  public static int[] sol_ListEntriesFX( IntPtr hEngine, int Flags, int EntryType, string Mask, int Language, int Class )
  {
   IntPtr hList = sol_ListEntries( hEngine, Flags, EntryType, Mask, Language, Class );
   if( hList==(IntPtr)null )
    return new int[0];

   int n = sol_CountInts(hList);
   int[] res = new int[n];
   
   for( int i=0; i<n; ++i )
    res[i] = sol_GetInt(hList,i);

   sol_DeleteInts(hList);

   return res;
  }


 public static string sol_GetNodeMarkNameFX( System.IntPtr hNode, int mark_index )
 {
  System.Text.StringBuilder b = new System.Text.StringBuilder(64);
  sol_GetNodeMarkNameW( hNode, mark_index, b );
  return b.ToString();
 }

 public static string sol_GetLongStringFX( System.IntPtr hString )
 {
  int l = sol_GetLongStringLenW(hString);
  System.Text.StringBuilder b = new System.Text.StringBuilder(l+1);
  sol_GetLongStringW( hString, b );
  return b.ToString();
 }

 }
}
