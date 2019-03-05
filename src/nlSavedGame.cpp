//---------------------------------------------------------------------------

#pragma hdrstop

//===========================================================================
#include <vcl.h>
#include "NLTK_common.h"
//---------------------------------------------------------------------------
#include "nlSavedGame.h"
#include "wAcceptChanges.h"
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
// CONSTANTES : offsets des données à lire dans le fichier SAVE.DAT
//---------------------------------------------------------------------------
#define SAVE_OFFSET_TYPE    			0x0000
#define SAVE_OFFSET_NAME    			0x0003
#define SAVE_OFFSET_SALARY_CAP      	0x0462
#define SAVE_OFFSET_DATE_ALLSTARGAME	0x07B2
#define SAVE_OFFSET_DATE_ENDTRANSF  	0x07BB
#define SAVE_OFFSET_DATE_INSEASON   	0x07C4
#define SAVE_OFFSET_DATE_INPLAYOFFS 	0x07C4
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
bool __fastcall CNLSavedGame::open( bool loadCareer )
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

	// step 4 : open career.dbf :
	//---------------------------
	if ( ok && loadCareer ) ok = this->openCareer();


    return ok;
}
//---------------------------------------------------------------------------
bool __fastcall CNLSavedGame::close()
{
	bool ok_c = this->closeCareer();
	bool ok_p = this->closePlayers();
	bool ok_t = this->closeTeams();

	return (ok_c && ok_p && ok_t);
}
//---------------------------------------------------------------------------
bool __fastcall CNLSavedGame::playersAccept()
{
    if ( this->_players )
    {
        TStrings* changes = new TStringList();
        changes->Add( "Liste des changements :" );
        changes->Add( "" );

        if ( this->playersDif )
        {
            for ( int i = 0 ; i < this->playerCount ; i++ )
            {
                CNLPlayer* p = this->playerByIndex[ i ];
                if ( p && p->dif )
                {
                    AnsiString line;
                    line.sprintf( "> id = %d ; %s %s" , p->ID , p->FName , p->Name );
                    changes->Add( line );

                    TStrings* difs = new TStringList();

                    p->loadDifs( difs );

                    for ( int i = 0 ; i < difs->Count ; i++ )
                    {
                        changes->Add( AnsiString( "    . " ) + difs->Strings[ i ]  );
                    }
                    changes->Add( "" );

                    delete difs;
                    difs = NULL;
                }
            }
        }
        else
        {
            changes->Add("aucun changement à appliquer");
        }

        TAcceptChangesDlg* accept = new TAcceptChangesDlg( NULL );
        bool ok = accept->execute( changes );

        delete accept;
        accept = NULL;

        delete changes;
        changes = NULL;

        return ok;

    }

    return false;
}
//---------------------------------------------------------------------------
bool __fastcall CNLSavedGame::playersUpdate()
{
	if ( this->_tablePlayers )
	{
        this->_tablePlayers->first();

        for ( int i = 0 ; i < this->playerCount ; i++ )
        {
            CNLPlayer* p = this->playerByIndex[ i ];
            if ( p && p->dif )
            {
                if ( this->_tablePlayers->setPosition( p->recordIndex ) )
                {
                    if ( !p->saveToTable( this->_tablePlayers ) )
                    {
                        return false;
                    }
                }
                else return false;
            }
        }

        return true;;
    }
    return false;
}
//---------------------------------------------------------------------------
void __fastcall CNLSavedGame::loadPlayerCareer( int playerId , TList* lc )
{
	if ( lc )
	{
		for ( int i = 0 ; i < this->careerCount ; i++ )
		{
			CNLCareer* c = this->careerByIndex[ i ];
			if ( c && c->PlayerId == playerId )
			{
				lc->Add( c );
			}
		}
    }
}
//---------------------------------------------------------------------------
void __fastcall CNLSavedGame::zero()
{
    this->_path				= TXT_NULL;
    this->_teams			= NULL;
	this->_players			= NULL;
	this->_career           = NULL;
	this->_tableTeams		= NULL;
	this->_tablePlayers		= NULL;
    this->_tableCareer  	= NULL;
    this->_type         	= (tNLSavedGame)0;
	this->_name				= TXT_NULL;
    this->_salaryCap		= 0;
    this->_dateAllStarGame	= (TDate)0;
    this->_dateEndTransf	= (TDate)0;
    this->_dateInSeason		= (TDate)0;
    this->_dateInPlayoffs	= (TDate)0;
}
//---------------------------------------------------------------------------
void __fastcall CNLSavedGame::init()
{
    if ( !this->_teams ) this->_teams = new TList();
	if ( !this->_players ) this->_players = new TList();
	if ( !this->_career ) this->_career = new TList();
    if ( !this->_tableTeams ) this->_tableTeams = new CDBTable( this->_path + FILE_TEAMS );
	if ( !this->_tablePlayers ) this->_tablePlayers = new CDBTable( this->_path + FILE_PLAYERS );
    if ( !this->_tableCareer ) this->_tableCareer = new CDBTable( this->_path + FILE_CAREER );
}
//---------------------------------------------------------------------------
void __fastcall CNLSavedGame::deinit()
{
	this->close();
	if ( this->_tableCareer )
	{
		delete this->_tableCareer;
		this->_tableCareer = NULL;
    }
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
	if ( this->_career )
	{
		delete this->_career;
		this->_career = NULL;
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
void __fastcall CNLSavedGame::deleteCareer()
{
	if ( this->_career )
	{
		while ( this->_career->Count )
		{
			CNLCareer* c = (CNLCareer*)this->_career->Items[ 0 ];
			if ( c )
			{
				this->_career->Items[0] = NULL;
				delete c;
				c = NULL;
			}
            this->_career->Delete( 0 );
        }
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
    bool ok = false;

    AnsiString saveFile = this->_path + FILE_SAVE;
    if ( FileExists( saveFile ) )
    {

        // ouverture du fichier en lecture :
        //----------------------------------
        TFileStream* f = new TFileStream( saveFile , fmOpenRead );

        // lecture type de sauvegarde :
        //-----------------------------
        int type = 0;
        f->Position = SAVE_OFFSET_TYPE;
        if ( f->Read( &type , sizeof(type) ) )
        {
            switch ( type )
            {
                case 6	: this->_type = nlsgSeason; break;
                case 7	: this->_type = nlsgPlayoffs; break;
                default	: this->_type = nlsgNotSupported;
            }
        }

        if ( this->_type != nlsgNotSupported )
        {
            char buf[20];
        	ZeroMemory( buf , sizeof( buf ) );

            // lecture nom de la sauvegarde :
            //-------------------------------
            f->Position = SAVE_OFFSET_NAME;
            if ( f->Read( buf , sizeof(buf) ) )
            {
            	this->_name = AnsiString( buf );
            }
            else
            {
                this->_name = TXT_NULL;
            }
            ZeroMemory( buf , sizeof( buf ) );

            // lecture salary cap :
            //---------------------
            f->Position = SAVE_OFFSET_SALARY_CAP;
            int sc = 0;
            if ( f->Read( &sc , sizeof(sc) ) )
            {
                this->_salaryCap = sc;
            }
            else
            {
                this->_salaryCap = 0;
            }

            // lecture date all star game :
            //----------------------------
            f->Position = SAVE_OFFSET_DATE_ALLSTARGAME;
            if ( f->Read( buf , 8 ) )
            {
                this->_dateAllStarGame = CDBEngine::stringToDate( AnsiString( buf ) );
            }
            else
            {
                this->_dateAllStarGame = (TDate)0;
            }
            ZeroMemory( buf , sizeof(buf) );

            // lecture date limite des transferts :
            //-------------------------------------
            f->Position = SAVE_OFFSET_DATE_ENDTRANSF;
            if ( f->Read( buf , 8 ) )
            {
                this->_dateEndTransf = CDBEngine::stringToDate( AnsiString( buf ) );
            }
            else
            {
                this->_dateEndTransf = (TDate)0;
            }
            ZeroMemory( buf , sizeof(buf) );

            // lecture date actuelle en saison :
            //----------------------------------
            f->Position = SAVE_OFFSET_DATE_INSEASON;
            if ( f->Read( buf , 8 ) )
            {
                this->_dateInSeason = CDBEngine::stringToDate( AnsiString( buf ) );
            }
            else
            {
                this->_dateInSeason = (TDate)0;
            }
            ZeroMemory( buf , sizeof(buf) );

            // lecture date actuelle en playoffs :
            //------------------------------------
            f->Position = SAVE_OFFSET_DATE_INPLAYOFFS;
            if ( f->Read( buf , 8 ) )
            {
                this->_dateInPlayoffs = CDBEngine::stringToDate( AnsiString( buf ) );
            }
            else
            {
                this->_dateInPlayoffs = (TDate)0;
            }
            ZeroMemory( buf , sizeof(buf) );

            ok = true;

        }
        else
        {
            this->_name = TXT_NULL;
            this->_salaryCap = 0;
            this->_dateAllStarGame = (TDate)0;
            this->_dateEndTransf = (TDate)0;
            this->_dateInSeason = (TDate)0;
            this->_dateInPlayoffs = (TDate)0;
        }

        delete f;
        f = NULL;
    }
    else
    {
        this->_type = nlsgNotSupported;
    }

	return ok;
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
bool __fastcall CNLSavedGame::openCareer()
{
	bool ok = false;

	if ( this->_tableCareer && !this->_tableCareer->isOpen )
	{
		ok = this->_tableCareer->open();

		if ( ok && this->_career && this->_career->Count == 0 )
        {
            int indexDebug = 0;
			ok = this->_tableCareer->first();
            while ( ok )
            {
				CNLCareer* c = new CNLCareer( this->_tableCareer );
				if ( this->playerById[ c->PlayerId ] )
				{
					this->_career->Add( c );
				}
				else
				{
					delete c;
					c = NULL;
				}

				ok = this->_tableCareer->next();
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
bool __fastcall CNLSavedGame::closeCareer()
{
	if ( this->_tableCareer )
	{
		return this->_tableCareer->close();
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
//---------------------------------------------------------------------------
bool __fastcall CNLSavedGame::getPlayersDif()
{
    if ( this->_players )
    {
        for ( int i = 0 ; i < this->_players->Count ; i++ )
        {
            CNLPlayer* p = (CNLPlayer*)this->_players->Items[ i ];
            if ( p && p->dif ) return true;
        }
    }
    return false;
}
//---------------------------------------------------------------------------
CNLCareer* __fastcall CNLSavedGame::getCareerByIndex( int index )
{
	if ( this->_career )
	{
		return (CNLCareer*)this->_career->Items[ index ];
	}

	return NULL;
}
//---------------------------------------------------------------------------
int __fastcall CNLSavedGame::getCareerCount()
{
	if ( this->_career ) return this->_career->Count;

	return 0;
}
//---------------------------------------------------------------------------
TDate __fastcall CNLSavedGame::getDateActive()
{
    switch ( this->_type )
    {
        case nlsgSeason	: return this->_dateInSeason;
        case nlsgPlayoffs : return this->_dateInPlayoffs;
    }

    return (TDate)0;
}
//===========================================================================
//===========================================================================
//===========================================================================
//===========================================================================

