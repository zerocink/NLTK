//---------------------------------------------------------------------------

#pragma hdrstop

//===========================================================================
#include <vcl.h>
#include "NLTK_common.h"
//---------------------------------------------------------------------------
#include "nlCareer.h"
//===========================================================================
#pragma package(smart_init)

//===========================================================================
// initialisation des variables statiques :
//---------------------------------------------------------------------------
DWORD CNLCareer::_instanceCount = 0;
TStrings* CNLCareer::_fieldNames = NULL;
//===========================================================================

//===========================================================================
// CONSTANTES : liste des noms de champs de la table PLAYERS
//---------------------------------------------------------------------------
#define FIELD_YEAR              AnsiString( "YEAR" )
#define FIELD_TEAMNUM	      	AnsiString( "TEAMNUM" )
#define FIELD_TEAM	            AnsiString( "TEAM" )
#define FIELD_PLAYERID          AnsiString( "PLAYERID" )
//---------------------------------------------------------------------------
#define FIELD_SGM        		AnsiString( "SGAMES" )
#define FIELD_SGMS		    	AnsiString( "SSTART" )
#define FIELD_SFGA  	 		AnsiString( "SFGATTEMPT" )
#define FIELD_SFGM	       		AnsiString( "SFGMADE" )
#define FIELD_S3PA				AnsiString( "STHREEPTAT" )
#define FIELD_S3PM				AnsiString( "STHREEPTMA" )
#define FIELD_SFTA		    	AnsiString( "SFTATTEMPT" )
#define FIELD_SFTM	        	AnsiString( "SFTMADE" )
#define FIELD_SBLK		    	AnsiString( "SBLOCKS" )
#define FIELD_SORB		    	AnsiString( "SOFFREB" )
#define FIELD_SAST	        	AnsiString( "SASSISTS" )
#define FIELD_SFLS	        	AnsiString( "SPERFOUL" )
#define FIELD_SSTL	        	AnsiString( "SSTEALS" )
#define FIELD_SDRB	        	AnsiString( "SDEFREB" )
#define FIELD_STO		    	AnsiString( "STURNOVERS" )
#define FIELD_SMIN	        	AnsiString( "SMINUTES" )
#define FIELD_SEJT	        	AnsiString( "SEJECTS" )
//===========================================================================
// CONSTANTES : liste des valeurs pour le champ TEAMNUM
//---------------------------------------------------------------------------
#define TEAMNUM_UNDEF          	((WORD)-1)



//===========================================================================
//===========================================================================
//===========================================================================
//===========================================================================
//===========================================================================
//---------------------------------------------------------------------------
__fastcall CNLCareer::CNLCareer()
{
    this->zero();
    this->init();

    this->_instanceCount++;
}
//---------------------------------------------------------------------------
__fastcall CNLCareer::CNLCareer( CDBTable* t )
{
    this->zero();
    this->init();

    this->_instanceCount++;

	this->loadFromTable( t );
}
//---------------------------------------------------------------------------
__fastcall CNLCareer::~CNLCareer()
{
    this->_instanceCount--;
    this->deinit();
    this->zero();
}
//---------------------------------------------------------------------------
bool __fastcall CNLCareer::loadFromTable( CDBTable* t )
{
    bool ok = false;


	if ( this->_record && t )
    {
        ok = this->_record->readFromTable( t );
    }

    return ok;
}
//---------------------------------------------------------------------------
void __fastcall CNLCareer::loadSeasonStats( CNLPlayerStats& ps )
{
	ps.GM = this->SeasonGM;
	ps.GMS = this->SeasonGMS;
	ps.FGM = this->SeasonFGM;
	ps.FGA = this->SeasonFGA;
	ps.TPM = this->Season3PM;
	ps.TPA = this->Season3PA;
	ps.FTM = this->SeasonFTM;
	ps.FTA = this->SeasonFTA;
	ps.ORB = this->SeasonORB;
	ps.DRB = this->SeasonDRB;
	ps.AST = this->SeasonAST;
	ps.STL = this->SeasonSTL;
	ps.BLK = this->SeasonBLK;
	ps.TO = this->SeasonTO;
	ps.FLS = this->SeasonFLS;
	ps.MIN = this->SeasonMIN;
    ps.EJT = this->SeasonEJT;
}
//---------------------------------------------------------------------------
void __fastcall CNLCareer::zero()
{
    this->_record = NULL;
}
//---------------------------------------------------------------------------
void __fastcall CNLCareer::init()
{
    if ( this->_instanceCount == 0 ) this->createFieldNames();

    this->_record = new CDBRecord();
    this->_record->createFields( this->_fieldNames );

    this->_instanceCount++;
}
//---------------------------------------------------------------------------
void __fastcall CNLCareer::deinit()
{
    this->_instanceCount--;

    if ( this->_record )
    {
        this->_record->deleteFields( this->_fieldNames );
        delete this->_record;
        this->_record = NULL;
    }

    if ( this->_instanceCount == 0 ) this->deleteFieldNames();
}
//---------------------------------------------------------------------------
void __fastcall CNLCareer::createFieldNames()
{
	if ( !CNLCareer::_fieldNames )
    {
		CNLCareer::_fieldNames = new TStringList();

		CNLCareer::_fieldNames->Add( FIELD_YEAR );
		CNLCareer::_fieldNames->Add( FIELD_TEAMNUM );
		CNLCareer::_fieldNames->Add( FIELD_TEAM );
		CNLCareer::_fieldNames->Add( FIELD_PLAYERID );
		CNLCareer::_fieldNames->Add( FIELD_SGM );
		CNLCareer::_fieldNames->Add( FIELD_SGMS );
		CNLCareer::_fieldNames->Add( FIELD_SFGA );
		CNLCareer::_fieldNames->Add( FIELD_SFGM );
		CNLCareer::_fieldNames->Add( FIELD_S3PA );
		CNLCareer::_fieldNames->Add( FIELD_S3PM );
		CNLCareer::_fieldNames->Add( FIELD_SFTA );
		CNLCareer::_fieldNames->Add( FIELD_SFTM );
		CNLCareer::_fieldNames->Add( FIELD_SBLK );
		CNLCareer::_fieldNames->Add( FIELD_SORB );
		CNLCareer::_fieldNames->Add( FIELD_SAST );
		CNLCareer::_fieldNames->Add( FIELD_SFLS );
		CNLCareer::_fieldNames->Add( FIELD_SSTL );
		CNLCareer::_fieldNames->Add( FIELD_SDRB );
		CNLCareer::_fieldNames->Add( FIELD_STO );
		CNLCareer::_fieldNames->Add( FIELD_SMIN );
		CNLCareer::_fieldNames->Add( FIELD_SEJT );

	}
}
//---------------------------------------------------------------------------
void __fastcall CNLCareer::deleteFieldNames()
{
	if ( CNLCareer::_fieldNames )
    {
		CNLCareer::_fieldNames->Clear();
		delete CNLCareer::_fieldNames;
		CNLCareer::_fieldNames = NULL;
    }
}
//---------------------------------------------------------------------------
WORD __fastcall CNLCareer::getYear()
{
	WORD YEAR = 0;

	if ( this->_record )
	{
		YEAR = this->_record->ram[ FIELD_YEAR ].ToIntDef(0);
	}

	return YEAR;
}
//---------------------------------------------------------------------------
WORD __fastcall CNLCareer::getTeamNum()
{
    WORD TEAMNUM = 0;

    if ( this->_record )
    {
        TEAMNUM = this->_record->ram[ FIELD_TEAMNUM ].ToIntDef(TEAMNUM_UNDEF);
    }

    return TEAMNUM;
}
//---------------------------------------------------------------------------
AnsiString __fastcall CNLCareer::getTeam()
{
	AnsiString TEAM = TXT_NULL;

	if ( this->_record )
	{
		TEAM = this->_record->ram[ FIELD_TEAM ];
	}

	return TEAM;
}
//---------------------------------------------------------------------------
WORD __fastcall CNLCareer::getPlayerId()
{
	WORD PLAYERID = 0;

	if ( this->_record )
	{
		PLAYERID = this->_record->ram[ FIELD_PLAYERID ].ToIntDef(0);
	}

	return PLAYERID;
}
//---------------------------------------------------------------------------
WORD __fastcall CNLCareer::getSeasonGM()
{
    WORD SGM = 0;

    if ( this->_record )
    {
        SGM = this->_record->ram[ FIELD_SGM ].ToIntDef(0);
    }

    return SGM;
}
//---------------------------------------------------------------------------
WORD __fastcall CNLCareer::getSeasonGMS()
{
    WORD SGMS = 0;

    if ( this->_record )
    {
        SGMS = this->_record->ram[ FIELD_SGMS ].ToIntDef(0);
    }

    return SGMS;
}
//---------------------------------------------------------------------------
WORD __fastcall CNLCareer::getSeasonFGM()
{
    WORD SFGM = 0;

    if ( this->_record )
    {
        SFGM = this->_record->ram[ FIELD_SFGM ].ToIntDef(0);
    }

    return SFGM;
}
//---------------------------------------------------------------------------
WORD __fastcall CNLCareer::getSeasonFGA()
{
    WORD SFGA = 0;

    if ( this->_record )
    {
        SFGA = this->_record->ram[ FIELD_SFGA ].ToIntDef(0);
    }

    return SFGA;
}
//---------------------------------------------------------------------------
WORD __fastcall CNLCareer::getSeason3PM()
{
    WORD S3PM = 0;

    if ( this->_record )
    {
        S3PM = this->_record->ram[ FIELD_S3PM ].ToIntDef(0);
    }

    return S3PM;
}
//---------------------------------------------------------------------------
WORD __fastcall CNLCareer::getSeason3PA()
{
    WORD S3PA = 0;

    if ( this->_record )
    {
        S3PA = this->_record->ram[ FIELD_S3PA ].ToIntDef(0);
    }

    return S3PA;
}
//---------------------------------------------------------------------------
WORD __fastcall CNLCareer::getSeasonFTM()
{
    WORD SFTM = 0;

    if ( this->_record )
    {
        SFTM = this->_record->ram[ FIELD_SFTM ].ToIntDef(0);
    }

    return SFTM;
}
//---------------------------------------------------------------------------
WORD __fastcall CNLCareer::getSeasonFTA()
{
    WORD SFTA = 0;

    if ( this->_record )
    {
        SFTA = this->_record->ram[ FIELD_SFTA ].ToIntDef(0);
    }

    return SFTA;
}
//---------------------------------------------------------------------------
WORD __fastcall CNLCareer::getSeasonORB()
{
    WORD SORB = 0;

    if ( this->_record )
    {
        SORB = this->_record->ram[ FIELD_SORB ].ToIntDef(0);
    }

    return SORB;
}
//---------------------------------------------------------------------------
WORD __fastcall CNLCareer::getSeasonDRB()
{
    WORD SDRB = 0;

    if ( this->_record )
    {
        SDRB = this->_record->ram[ FIELD_SDRB ].ToIntDef(0);
    }

    return SDRB;
}
//---------------------------------------------------------------------------
WORD __fastcall CNLCareer::getSeasonAST()
{
    WORD SAST = 0;

    if ( this->_record )
    {
        SAST = this->_record->ram[ FIELD_SAST ].ToIntDef(0);
    }

    return SAST;
}
//---------------------------------------------------------------------------
WORD __fastcall CNLCareer::getSeasonSTL()
{
    WORD SSTL = 0;

    if ( this->_record )
    {
        SSTL = this->_record->ram[ FIELD_SSTL ].ToIntDef(0);
    }

    return SSTL;
}
//---------------------------------------------------------------------------
WORD __fastcall CNLCareer::getSeasonBLK()
{
    WORD SBLK = 0;

    if ( this->_record )
    {
        SBLK = this->_record->ram[ FIELD_SBLK ].ToIntDef(0);
    }

    return SBLK;
}
//---------------------------------------------------------------------------
WORD __fastcall CNLCareer::getSeasonTO()
{
    WORD STO = 0;

    if ( this->_record )
    {
        STO = this->_record->ram[ FIELD_STO ].ToIntDef(0);
    }

    return STO;
}
//---------------------------------------------------------------------------
WORD __fastcall CNLCareer::getSeasonFLS()
{
    WORD SFLS = 0;

    if ( this->_record )
    {
        SFLS = this->_record->ram[ FIELD_SFLS ].ToIntDef(0);
    }

    return SFLS;
}
//---------------------------------------------------------------------------
WORD __fastcall CNLCareer::getSeasonMIN()
{
    WORD SMIN = 0;

    if ( this->_record )
    {
        SMIN = this->_record->ram[ FIELD_SMIN ].ToIntDef(0);
    }

    return SMIN;
}
//---------------------------------------------------------------------------
WORD __fastcall CNLCareer::getSeasonEJT()
{
    WORD SEJT = 0;

    if ( this->_record )
    {
        SEJT = this->_record->ram[ FIELD_SEJT ].ToIntDef(0);
    }

    return SEJT;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//===========================================================================
//===========================================================================
//===========================================================================
//===========================================================================
//===========================================================================
