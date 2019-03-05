//---------------------------------------------------------------------------

#ifndef nlSavedGameH
#define nlSavedGameH
//===========================================================================
// fichiers en-tête utilisés
//---------------------------------------------------------------------------
#include "nlTeam.h"
#include "nlPlayer.h"
#include "nlCareer.h"
//===========================================================================


//===========================================================================
// Pré-déclarations des classes
//---------------------------------------------------------------------------
class CNLSavedGame;
//===========================================================================


//===========================================================================
#define ROSTER_SIZE 15
//---------------------------------------------------------------------------
struct CNLRoster
{
    CNLTeam* team;
    CNLPlayer* players[ ROSTER_SIZE ];
};
//===========================================================================


//===========================================================================
#define DRAFT_ROUND_COUNT	2
#define DRAFT_PLACE_COUNT   30
//---------------------------------------------------------------------------
struct CNLDraft
{
    WORD year;
    CNLPlayer* players[ DRAFT_ROUND_COUNT ][ DRAFT_PLACE_COUNT ];
};
//===========================================================================


//===========================================================================
enum tNLSavedGame
{
    nlsgNotSupported = 0,
    nlsgSeason = 6,
    nlsgPlayoffs = 7
};
class CNLSavedGame
{

    public  :

        // constructeurs & destructeur :
        //------------------------------
                __fastcall CNLSavedGame( AnsiString path );
        virtual __fastcall ~CNLSavedGame();

        // méthodes publiques :
		//---------------------
		bool __fastcall open( bool loadCareer );
		bool __fastcall close();

        bool __fastcall playersAccept();	// demande acceptation puis applications des modifications
		bool __fastcall playersUpdate();    // applications des modifications

		void __fastcall loadPlayerCareer( int playerId , TList* lc );	// charge la liste des stats en carrière d'un joueur

		// propriétés publiques :
        //-----------------------
        __property AnsiString path 							 = { read = _path 				};
        __property CNLTeam*   teamByNum	   [ WORD teamNum  ] = { read = getTeamByNum 		};
        __property CNLTeam*   teamByIndex  [ int index 	   ] = { read = getTeamByIndex		};
        __property int        teamCount 					 = { read = getTeamCount		};
        __property CNLPlayer* playerById   [ WORD playerId ] = { read = getPlayerById 		};
        __property CNLPlayer* playerByIndex[ int index 	   ] = { read = getPlayerByIndex	};
        __property int        playerCount                	 = { read = getPlayerCount 		};
		__property bool       playersDif                     = { read = getPlayersDif		};
		__property CNLCareer* careerByIndex[ int index     ] = { read = getCareerByIndex    };
		__property int        careerCount                    = { read = getCareerCount		};

        __property tNLSavedGame type 			= { read = _type 			};
        __property AnsiString   name 			= { read = _name		    };
        __property int          salaryCap 		= { read = _salaryCap		};
        __property TDate        dateActive		= { read = getDateActive    };
		__property TDate        dateAllStarGame = { read = _dateAllStarGame	};
        __property TDate        dateEndTransf   = { read = _dateEndTransf	};
		__property TDate        dateInSeason    = { read = _dateInSeason    };
        __property TDate        dateInPlayoffs  = { read = _dateInPlayoffs  };

    private :

    	// méthodes internes :
        //--------------------
        void __fastcall zero();
        void __fastcall init();
        void __fastcall deinit();

        void __fastcall deleteCareer();
        void __fastcall deletePlayers();
        void __fastcall deleteTeams();

        bool __fastcall readSave();
        bool __fastcall openTeams();
		bool __fastcall openPlayers();
		bool __fastcall openCareer();
        bool __fastcall closeTeams();
		bool __fastcall closePlayers();
		bool __fastcall closeCareer();

        // méthodes get / set des propriétés :
        //------------------------------------
        CNLTeam* 	__fastcall getTeamByNum( WORD teamNum );
        CNLTeam* 	__fastcall getTeamByIndex( int index );
        int      	__fastcall getTeamCount();
        CNLPlayer* 	__fastcall getPlayerById( WORD playerId );
		CNLPlayer* 	__fastcall getPlayerByIndex( int index );
		int         __fastcall getPlayerCount();
		bool        __fastcall getPlayersDif();
		CNLCareer*  __fastcall getCareerByIndex( int index );
		int         __fastcall getCareerCount();
		TDate       __fastcall getDateActive();

        // variables internes :
        //---------------------
        AnsiString 		_path;
		TList*     		_teams;
		TList*     		_players;
		TList*          _career;
        CDBTable* 		_tableTeams;
		CDBTable*  		_tablePlayers;
		CDBTable*       _tableCareer;
		tNLSavedGame    _type;
		AnsiString   	_name;
        int          	_salaryCap;
		TDate        	_dateAllStarGame;
        TDate        	_dateEndTransf;
        TDate        	_dateInSeason;
        TDate        	_dateInPlayoffs;

};
//===========================================================================


#endif
