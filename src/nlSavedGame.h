//---------------------------------------------------------------------------

#ifndef nlSavedGameH
#define nlSavedGameH
//===========================================================================
// fichiers en-tête utilisés
//---------------------------------------------------------------------------
#include "nlTeam.h"
#include "nlPlayer.h"
//===========================================================================


//===========================================================================
// Pré-déclarations des classes
//---------------------------------------------------------------------------
class CNLSavedGame;
//===========================================================================


//===========================================================================
#define ROSTER_SIZE 15
struct CNLRoster
{
    CNLTeam* team;
    CNLPlayer* players[ ROSTER_SIZE ];
};
//===========================================================================


//===========================================================================
class CNLSavedGame
{

    public  :

        // constructeurs & destructeur :
        //------------------------------
                __fastcall CNLSavedGame( AnsiString path );
        virtual __fastcall ~CNLSavedGame();

        // méthodes publiques :
        //---------------------
        bool __fastcall open();
        bool __fastcall close();

        // propriétés publiques :
        //-----------------------
        __property AnsiString path 							 = { read = _path 				};
        __property CNLTeam*   teamByNum	   [ WORD teamNum  ] = { read = getTeamByNum 		};
        __property CNLTeam*   teamByIndex  [ int index 	   ] = { read = getTeamByIndex		};
        __property int        teamCount 					 = { read = getTeamCount		};
        __property CNLPlayer* playerById   [ WORD playerId ] = { read = getPlayerById 		};
        __property CNLPlayer* playerByIndex[ int index 	   ] = { read = getPlayerByIndex	};
        __property int        playerCount                	 = { read = getPlayerCount 		};

    private :

    	// méthodes internes :
        //--------------------
        void __fastcall zero();
        void __fastcall init();
        void __fastcall deinit();

        void __fastcall deletePlayers();
        void __fastcall deleteTeams();

        bool __fastcall readSave();
        bool __fastcall openTeams();
        bool __fastcall openPlayers();
        bool __fastcall closeTeams();
        bool __fastcall closePlayers();

        // méthodes get / set des propriétés :
        //------------------------------------
        CNLTeam* 	__fastcall getTeamByNum( WORD teamNum );
        CNLTeam* 	__fastcall getTeamByIndex( int index );
        int      	__fastcall getTeamCount();
        CNLPlayer* 	__fastcall getPlayerById( WORD playerId );
        CNLPlayer* 	__fastcall getPlayerByIndex( int index );
        int         __fastcall getPlayerCount();

        // variables internes :
        //---------------------
        AnsiString 		_path;
        TList*     		_teams;
        TList*     		_players;
        CDBTable* 		_tableTeams;
        CDBTable*  		_tablePlayers;
};
//===========================================================================


#endif
