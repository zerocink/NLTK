//---------------------------------------------------------------------------

#ifndef dbEngineH
#define dbEngineH
//---------------------------------------------------------------------------
#include "dbf.h"
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
class CDBField;
class CDBRecord;
class CDBTable;
//---------------------------------------------------------------------------
class CDBEngine	// classe statique
{
    public :

        // m�thodes publiques statiques :
        //-------------------------------
        static	AnsiString __fastcall boolToString( bool b );
        static	bool       __fastcall stringToBool( AnsiString s );
        static  TDate      __fastcall stringToDate( const AnsiString& s );
        static  AnsiString __fastcall dateToString( const TDate& dt );
};
//---------------------------------------------------------------------------
class CDBField
{
	friend class CDBRecord;

	public	:

		// m�thodes publiques :
		//---------------------
		bool __fastcall readFromTable( CDBTable* t );	// rom --> ram
		bool __fastcall writeToTable( CDBTable* t );     // rom <-- ram

		// prori�t�s publiques :
		//----------------------
		__property AnsiString name	= { read = _name 				};	// nom du champs de donn�e
		__property AnsiString rom	= { read = _rom 				};  // valeur se trouvant en rom (dans la table)
		__property AnsiString ram	= { read = _ram , write = _ram 	};	// valeur se trouvant en ram (dans la m�moire tampon)
		__property bool       dif   = { read = getDif 				};  // diff�rence entre ram et rom

	private :

		// constructeurs & destructeur :
		//------------------------------
				__fastcall CDBField( AnsiString name );
		virtual __fastcall ~CDBField();

		// m�thodes internes :
		//--------------------
		void __fastcall zero();
		void __fastcall init();
		void __fastcall deinit();

		// m�thodes get / set des propri�t�s :
		//------------------------------------
		bool __fastcall getDif();

		// variables internes :
		//---------------------
		AnsiString _name;
		AnsiString _rom;
		AnsiString _ram;
};
//---------------------------------------------------------------------------
class CDBRecord
{

	public	:

		// constructeurs & destructeur :
		//------------------------------
				__fastcall CDBRecord();
		virtual __fastcall ~CDBRecord();

		// m�thodes publiques :
		//---------------------
		bool __fastcall createFields( TStrings* names );
		bool __fastcall deleteFields( TStrings* names );
		bool __fastcall deleteAllFields();
		bool __fastcall deleteFieldByIndex( int index );
		bool __fastcall readFromTable( CDBTable* t );
		bool __fastcall writeToTable( CDBTable* t );
        void __fastcall loadDifs( TStrings* difs );

		// propri�t�s publiques :
		//-----------------------
        __property int          recordIndex                     = { read = _recordIndex   };
		__property CDBField* 	fields[ int index ] 			= { read = getFields	   };
		__property int       	fieldsCount         			= { read = getFieldsCount };
		__property int       	indexOfField[ AnsiString name ] = { read = getIndexOfField };
		__property bool      	dif				 				= { read = getDif };
        __property AnsiString 	ram[ AnsiString fieldName ] 	= { read = getRam , write = setRam };

	private	:

		// m�thodes internes :
		//--------------------
		void __fastcall zero();
		void __fastcall init();
		void __fastcall deinit();

		// m�thodes get / set des propri�t�s :
		//------------------------------------
		CDBField*   __fastcall getFields( int index );
		int         __fastcall getFieldsCount();
		int         __fastcall getIndexOfField( AnsiString name );
        bool        __fastcall getDif();
        AnsiString  __fastcall getRam( AnsiString fieldName );
        void        __fastcall setRam( AnsiString fieldName , AnsiString ram );

		// variables internes :
		//---------------------
        int         _recordIndex;
		TList* 		_fields;
};
//---------------------------------------------------------------------------
class CDBTable
{
	public	:

		// constructeurs & destructeur :
		//------------------------------
				__fastcall CDBTable( AnsiString filename );
		virtual __fastcall ~CDBTable();

		// m�thodes publiques :
		//---------------------
		bool __fastcall open();
		bool __fastcall close();

		bool __fastcall first();
		bool __fastcall last();
		bool __fastcall next();
		bool __fastcall prior();
        bool __fastcall setPosition( int recordIndex );

		bool __fastcall loadFieldNames( TStrings* names );
		bool __fastcall getFieldValueString( AnsiString fieldName , AnsiString& fieldValue );
		bool __fastcall setFieldValueString( AnsiString fieldName , AnsiString fieldValue );
        bool __fastcall post();

		// propri�t�s publiques :
		//-----------------------
		__property bool isOpen = { read = getIsOpen	};
		__property dbf_uint recordIndex = { read = _recordIndex };
		__property dbf_uint recordCount = { read = _recordCount };
		__property dbf_uint fieldCount = { read = _fieldCount };

	private	:

		// variables internes :
		//---------------------
		AnsiString _filename;
		DBF_HANDLE _h;
		dbf_uint   _recordIndex;
		dbf_uint   _recordCount;
		dbf_uint   _bofMarker;
		dbf_uint   _eofMarker;
		dbf_uint   _fieldCount;
		DBF_INFO   _info;
		TStrings*  _fields;

		// m�thodes internes :
		//--------------------
		void __fastcall zero();
		void __fastcall init();
		void __fastcall deinit();

		// m�thodes get / set des propri�t�s :
		//------------------------------------
		bool __fastcall getIsOpen();

};
//---------------------------------------------------------------------------
#endif
