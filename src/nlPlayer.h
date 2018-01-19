//---------------------------------------------------------------------------

#ifndef nlPlayerH
#define nlPlayerH

//===========================================================================
// fichiers en-tête utilisés
//---------------------------------------------------------------------------
#include "dbEngine.h"
//===========================================================================



//===========================================================================
// Pré-déclarations des classes
//---------------------------------------------------------------------------
class CNLPlayer;
//===========================================================================


//===========================================================================
class CNLPlayer
{
    public	:

    	// constructeurs & destructeur :
        //------------------------------
		        __fastcall CNLPlayer();
                __fastcall CNLPlayer( CDBTable* t );
        virtual __fastcall ~CNLPlayer();

        // méthodes publiques :
        //---------------------
        bool __fastcall loadFromTable( CDBTable* t );

        // propriétés publiques :
        //-----------------------
        __property DWORD      ID		= { read = getID    	};
        __property AnsiString Name 		= { read = getName 		};
        __property AnsiString FName 	= { read = getFName		};
        __property AnsiString Number	= { read = getNumber    };
        __property DWORD      Weight 	= { read = getWeight	};
        __property DWORD      Height    = { read = getHeight	};
        __property AnsiString Position1 = { read = getPosition1 };
        __property AnsiString Position2 = { read = getPosition2 };

    private :

    	// méthodes internes :
        //--------------------
        void __fastcall zero();
        void __fastcall init();
        void __fastcall deinit();

        // méthodes internes statiques :
        //------------------------------
        static void __fastcall createFieldNames();
        static void __fastcall deleteFieldNames();

        // méthodes get / set des propriétés :
        //------------------------------------
        DWORD 		__fastcall getID();
        AnsiString 	__fastcall getName();
        AnsiString  __fastcall getFName();
        AnsiString  __fastcall getNumber();
        DWORD       __fastcall getWeight();
        DWORD       __fastcall getHeight();
        AnsiString  __fastcall getPosition1();
        AnsiString  __fastcall getPosition2();


        // variables internes :
        //---------------------
        CDBRecord* _record;

        // variables internes statiques :
        //-------------------------------
        static DWORD 		_instanceCount;
        static TStrings*    _fieldNames;
};
//===========================================================================
#endif
