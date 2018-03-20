//---------------------------------------------------------------------------

#ifndef nlSavedGameH
#define nlSavedGameH
//===========================================================================
// fichiers en-t�te utilis�s
//---------------------------------------------------------------------------
#include "nlTeam.h"
#include "nlPlayer.h"
//===========================================================================


//===========================================================================
// Pr�-d�clarations des classes
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
class CNLSavedGame
{

    public  :

        // constructeurs & destructeur :
        //------------------------------
                __fastcall CNLSavedGame( AnsiString path );
        virtual __fastcall ~CNLSavedGame();

        // m�thodes publiques :
        //---------------------
        bool __fastcall open();
        bool __fastcall close();

        bool __fastcall playersAccept();	// demande acceptation puis applications des modifications
        bool __fastcall playersUpdate();    // applications des modifications

        // propri�t�s publiques :
        //-----------------------
        __property AnsiString path 							 = { read = _path 				};
        __property CNLTeam*   teamByNum	   [ WORD teamNum  ] = { read = getTeamByNum 		};
        __property CNLTeam*   teamByIndex  [ int index 	   ] = { read = getTeamByIndex		};
        __property int        teamCount 					 = { read = getTeamCount		};
        __property CNLPlayer* playerById   [ WORD playerId ] = { read = getPlayerById 		};
        __property CNLPlayer* playerByIndex[ int index 	   ] = { read = getPlayerByIndex	};
        __property int        playerCount                	 = { read = getPlayerCount 		};
        __property bool       playersDif                     = { read = getPlayersDif		};

    private :

    	// m�thodes internes :
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

        // m�thodes get / set des propri�t�s :
        //------------------------------------
        CNLTeam* 	__fastcall getTeamByNum( WORD teamNum );
        CNLTeam* 	__fastcall getTeamByIndex( int index );
        int      	__fastcall getTeamCount();
        CNLPlayer* 	__fastcall getPlayerById( WORD playerId );
        CNLPlayer* 	__fastcall getPlayerByIndex( int index );
        int         __fastcall getPlayerCount();
        bool        __fastcall getPlayersDif();

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
