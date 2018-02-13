//---------------------------------------------------------------------------

#pragma hdrstop

//===========================================================================
#include <vcl.h>
#include "NLTK_common.h"
//---------------------------------------------------------------------------
#include "nlSavedGame.h"
//---------------------------------------------------------------------------
//===========================================================================

#pragma package(smart_init)

//===========================================================================
// initialisation des variables statiques :
//---------------------------------------------------------------------------
//===========================================================================


//===========================================================================
// CONSTANTES : liste des noms de fichiers composants la sauvegarde
//---------------------------------------------------------------------------
#define FILE_SAVE       AnsiString( "\\save.dat" )
#define FILE_PLAYERS    AnsiString( "\\players.dbf" )
#define FILE_TEAMS      AnsiString( "\\teams.dbf" )
#define FILE_CAREER     AnsiString( "\\career.dbf" )
#define FILE_DAILYNEWS  AnsiString( "\\dailynws.dbf" )
#define FILE_SCHEDULE   AnsiString( "\\schedule.dbf" )
#define FILE_TEAMCAREER AnsiString( "\\tmcareer.dbf" )
//===========================================================================


//===========================================================================
//===========================================================================
//===========================================================================
//===========================================================================
//===========================================================================
//---------------------------------------------------------------------------
__fastcall CNLSavedGame::CNLSavedGame( AnsiString path )
{
    this->zero();

    this->_path = path;

    this->init();

}
//---------------------------------------------------------------------------
__fastcall CNLSavedGame::~CNLSavedGame()
{
    this->deinit();
    this->zero();
}
//---------------------------------------------------------------------------
bool __fastcall CNLSavedGame::open()
{
    bool ok = false;

    // step 1 : open + read save.dat :
    //--------------------------------
    ok = this->readSave();

    // step 2 : open teams.dbf :
    //--------------------------
    if ( ok ) ok = this->openTeams();

    // step 3 : open players.dbf :
    //----------------------------
    if ( ok ) ok = this->openPlayers();


    return ok;
}
//---------------------------------------------------------------------------
bool __fastcall CNLSavedGame::close()
{
    bool ok_p = this->closePlayers();
    bool ok_t = this->closeTeams();

    return (ok_p && ok_t);
}
//---------------------------------------------------------------------------
void __fastcall CNLSavedGame::zero()
{
    this->_path			= TXT_NULL;
    this->_teams		= NULL;
    this->_players		= NULL;
    this->_tableTeams	= NULL;
    this->_tablePlayers	= NULL;
}
//---------------------------------------------------------------------------
void __fastcall CNLSavedGame::init()
{
    if ( !this->_teams ) this->_teams = new TList();
    if ( !this->_players ) this->_players = new TList();
    if ( !this->_tableTeams ) this->_tableTeams = new CDBTable( this->_path + FILE_TEAMS );
    if ( !this->_tablePlayers ) this->_tablePlayers = new CDBTable( this->_path + FILE_PLAYERS );
}
//---------------------------------------------------------------------------
void __fastcall CNLSavedGame::deinit()
{
    this->close();
    if ( this->_tablePlayers )
    {
        delete this->_tablePlayers;
        this->_tablePlayers = NULL;
    }
    if ( this->_tableTeams )
    {
        delete this->_tableTeams;
        this->_tableTeams = NULL;
    }
    if ( this->_players )
    {
        this->deletePlayers();
        delete this->_players;
        this->_players = NULL;
    }
    if ( this->_teams )
    {
        this->deleteTeams();
        delete this->_teams;
        this->_teams = NULL;
    }
}
//---------------------------------------------------------------------------
void __fastcall CNLSavedGame::deletePlayers()
{
    if ( this->_players )
    {

        while ( this->_players->Count )
        {
            CNLPlayer* p = (CNLPlayer*)this->_players->Items[ 0 ];
            if ( p )
            {
                this->_players->Items[0] = NULL;
            	delete p;
                p = NULL;
            }
            this->_players->Delete( 0 );
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall CNLSavedGame::deleteTeams()
{
    if ( this->_teams )
    {
        while ( this->_teams->Count )
        {
            CNLTeam* t = (CNLTeam*)this->_teams->Items[ 0 ];
            if ( t )
            {
                this->_teams->Items[0] = NULL;
            	delete t;
                t = NULL;
            }
            this->_teams->Delete( 0 );
        }
    }
}
//---------------------------------------------------------------------------
bool __fastcall CNLSavedGame::readSave()
{
    return true;
}
//---------------------------------------------------------------------------
bool __fastcall CNLSavedGame::openTeams()
{
    bool ok = false;

    if ( this->_tableTeams && !this->_tableTeams->isOpen )
    {
        ok = this->_tableTeams->open();

        if ( ok && this->_teams && this->_teams->Count == 0 )
        {
            int indexDebug = 0;
            ok = this->_tableTeams->first();
            while ( ok )
            {
                CNLTeam* t = new CNLTeam( this->_tableTeams );
                AnsiString nameDebug = t->TeamName;
                if ( t->InSeason > 0 || t->TeamCode == TEAMCODE_FREEAGENTS )
                {
                    this->_teams->Add( t );
                }
                else
                {
                    delete t;
                    t = NULL;
                }

                ok = this->_tableTeams->next();
                indexDebug++;
            }
            ok = true;
        }
        else
        {
            ok = false;
        }

    }

    return ok;
}
//---------------------------------------------------------------------------
bool __fastcall CNLSavedGame::openPlayers()
{
    bool ok = false;

    if ( this->_tablePlayers && !this->_tablePlayers->isOpen )
    {
        ok = this->_tablePlayers->open();

        if ( ok && this->_players && this->_players->Count == 0 )
        {
            int indexDebug = 0;
            ok = this->_tablePlayers->first();
            while ( ok )
            {
                CNLPlayer* p = new CNLPlayer( this->_tablePlayers );
                AnsiString nameDebug = p->Name;
                if ( p->InSeason )
                {
                    this->_players->Add( p );
                }
                else
                {
                    delete p;
                    p = NULL;
                }

                ok = this->_tablePlayers->next();
                indexDebug++;
            }
            ok = true;
        }
        else
        {
            ok = false;
        }

    }

    return ok;
}
//---------------------------------------------------------------------------
bool __fastcall CNLSavedGame::closeTeams()
{
    if ( this->_tableTeams )
    {
        return this->_tableTeams->close();
    }

    return true;
}
//---------------------------------------------------------------------------
bool __fastcall CNLSavedGame::closePlayers()
{
    if ( this->_tablePlayers )
    {
        return this->_tablePlayers->close();
    }
    return true;
}
//---------------------------------------------------------------------------
CNLTeam* __fastcall CNLSavedGame::getTeamByNum( WORD teamNum )
{
    if ( this->_teams )
    {
        for ( int i = 0 ; i < this->_teams->Count ; i++ )
        {
            CNLTeam* t = this->teamByIndex[ i ];
        	if ( t && t->TeamNum == teamNum ) return t;
        }
    }

    return NULL;
}
//---------------------------------------------------------------------------
CNLTeam* __fastcall CNLSavedGame::getTeamByIndex( int index )
{
    if ( this->_teams )
    {
        return (CNLTeam*)this->_teams->Items[ index ];
    }

    return NULL;
}
//---------------------------------------------------------------------------
int __fastcall CNLSavedGame::getTeamCount()
{
    if ( this->_teams ) return this->_teams->Count;

    return 0;
}
//---------------------------------------------------------------------------
CNLPlayer* __fastcall CNLSavedGame::getPlayerById( WORD playerId )
{
    if ( this->_players )
    {
        for ( int i = 0 ; i < this->_players->Count ; i++ )
        {
            CNLPlayer* p = this->playerByIndex[ i ];
        	if ( p && p->ID == playerId ) return p;
        }
    }

    return NULL;
}
//---------------------------------------------------------------------------
CNLPlayer* __fastcall CNLSavedGame::getPlayerByIndex( int index )
{
    if ( this->_players )
    {
        return (CNLPlayer*)this->_players->Items[ index ];
    }

    return NULL;
}
//---------------------------------------------------------------------------
int __fastcall CNLSavedGame::getPlayerCount()
{
    if ( this->_players ) return this->_players->Count;

    return 0;
}
//===========================================================================
//===========================================================================
//===========================================================================
//===========================================================================

