//---------------------------------------------------------------------------

#ifndef nlCareerH
#define nlCareerH

//===========================================================================
// fichiers en-tête utilisés
//---------------------------------------------------------------------------
#include "dbEngine.h"
#include "nlStats.h"
//===========================================================================




//===========================================================================
// Pré-déclarations des classes
//---------------------------------------------------------------------------
class CNLCareer;
//===========================================================================





//===========================================================================
class CNLCareer
{
    public	:

    	// constructeurs & destructeur :
        //------------------------------
				__fastcall CNLCareer();
				__fastcall CNLCareer( CDBTable* t );
		virtual __fastcall ~CNLCareer();

        // méthodes publiques :
		//---------------------
		bool __fastcall loadFromTable( CDBTable* t );
		void __fastcall loadSeasonStats( CNLPlayerStats& ps );

        // propriétés publiques :
        //-----------------------
		__property WORD       Year			= { read = getYear			};
		__property WORD 	  TeamNum		= { read = getTeamNum  		};
		__property AnsiString Team      	= { read = getTeam	        };
		__property WORD       PlayerId      = { read = getPlayerId		};

		__property WORD       SeasonGM		= { read = getSeasonGM 	 	};
		__property WORD       SeasonGMS		= { read = getSeasonGMS	    };
		__property WORD       SeasonFGM     = { read = getSeasonFGM     };
		__property WORD       SeasonFGA     = { read = getSeasonFGA     };
		__property WORD       Season3PM     = { read = getSeason3PM     };
		__property WORD       Season3PA     = { read = getSeason3PA     };
		__property WORD       SeasonFTM     = { read = getSeasonFTM     };
		__property WORD       SeasonFTA     = { read = getSeasonFTA     };
		__property WORD       SeasonORB     = { read = getSeasonORB     };
		__property WORD       SeasonDRB     = { read = getSeasonDRB     };
		__property WORD       SeasonAST     = { read = getSeasonAST	 	};
		__property WORD       SeasonSTL     = { read = getSeasonSTL     };
		__property WORD       SeasonBLK     = { read = getSeasonBLK		};
		__property WORD       SeasonTO      = { read = getSeasonTO      };
		__property WORD       SeasonFLS     = { read = getSeasonFLS     };
		__property WORD       SeasonMIN     = { read = getSeasonMIN     };
		__property WORD       SeasonEJT     = { read = getSeasonEJT     };


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
		WORD        __fastcall getYear();
		WORD 		__fastcall getTeamNum();
		AnsiString  __fastcall getTeam();
		WORD        __fastcall getPlayerId();
		WORD		__fastcall getSeasonGM();
		WORD       	__fastcall getSeasonGMS();
		WORD       	__fastcall getSeasonFGM();
		WORD       	__fastcall getSeasonFGA();
		WORD       	__fastcall getSeason3PM();
		WORD       	__fastcall getSeason3PA();
		WORD       	__fastcall getSeasonFTM();
		WORD       	__fastcall getSeasonFTA();
		WORD       	__fastcall getSeasonORB();
		WORD       	__fastcall getSeasonDRB();
		WORD       	__fastcall getSeasonAST();
		WORD       	__fastcall getSeasonSTL();
		WORD       	__fastcall getSeasonBLK();
		WORD       	__fastcall getSeasonTO();
		WORD       	__fastcall getSeasonFLS();
		WORD       	__fastcall getSeasonMIN();
		WORD       	__fastcall getSeasonEJT();

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
