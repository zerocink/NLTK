//---------------------------------------------------------------------------

#ifndef nlTeamH
#define nlTeamH

//===========================================================================
// fichiers en-tête utilisés
//---------------------------------------------------------------------------
#include "dbEngine.h"
//===========================================================================


//===========================================================================
// CONSTANTES : liste des valeurs pour le champ INSEASON
//---------------------------------------------------------------------------
#define INSEASON_UNDEF          ((WORD)-1)
#define INSEASON_PACIFIC        1
#define INSEASON_MIDWEST        2
#define INSEASON_CENTRAL        3
#define INSEASON_ATLANTIC       4
//===========================================================================
// CONSTANTES : liste des valeurs pour le champ TEAMCODE
//---------------------------------------------------------------------------
#define TEAMCODE_UNDEF          ((WORD)-1)
#define TEAMCODE_NBATEAM		0
#define TEAMCODE_WESTALLSTAR    1
#define TEAMCODE_EASTALLSTAR    2
#define TEAMCODE_FREEAGENTS 	3
#define TEAMCODE_CUSTOMTEAM     4
#define TEAMCODE_RETIRED        5
#define TEAMCODE_DECADEALLSTAR  6
#define TEAMCODE_REFEREE        8
#define TEAMCODE_ROOKIEPOOL     9
#define TEAMCODE_LEGENDPOOL     10
//===========================================================================
// CONSTANTES : liste des valeurs pour le champ CONFERENCE
//---------------------------------------------------------------------------
#define CONFERENCE_UNDEF        ((WORD)-1)
#define CONFERENCE_WEST         0
#define CONFERENCE_EAST         1
#define CONFERENCE_ALLSTAR      2
#define CONFERENCE_FREEAGENTS   3
//===========================================================================
// CONSTANTES : liste des valeurs pour le champ DIVISION
//---------------------------------------------------------------------------
#define DIVISION_UNDEF          ((WORD)-1)
#define DIVISION_PACIFIC        0
#define DIVISION_MIDWEST        1
#define DIVISION_CENTRAL        2
#define DIVISION_ATLANTIC   	3
#define DIVISION_ALLSTARS       4
#define DIVISION_FREEAGENTS 	5
//===========================================================================

//===========================================================================
// Pré-déclarations des classes
//---------------------------------------------------------------------------
class CNLTeam;
//===========================================================================





//===========================================================================
class CNLTeam
{
    public	:

    	// constructeurs & destructeur :
        //------------------------------
		        __fastcall CNLTeam();
                __fastcall CNLTeam( CDBTable* t );
        virtual __fastcall ~CNLTeam();

        // méthodes publiques :
        //---------------------
        bool __fastcall loadFromTable( CDBTable* t );

        // propriétés publiques :
        //-----------------------
        __property WORD 	  TeamNum		= { read = getTeamNum  		};
        __property AnsiString TeamName      = { read = getTeamName      };
        __property AnsiString CityName      = { read = getCityName      };
        __property AnsiString Abrev         = { read = getAbrev         };
        __property WORD       InSeason		= { read = getInSeason		};
        __property WORD       TeamCode  	= { read = getTeamCode		};
        __property WORD       Conference    = { read = getConference    };
        __property WORD       Division      = { read = getDivision 		};

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
        WORD 		__fastcall getTeamNum();
        AnsiString  __fastcall getTeamName();
        AnsiString  __fastcall getCityName();
        AnsiString  __fastcall getAbrev();
        WORD        __fastcall getInSeason();
        WORD        __fastcall getTeamCode();
        WORD        __fastcall getConference();
        WORD        __fastcall getDivision();

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
