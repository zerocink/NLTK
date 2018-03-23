//---------------------------------------------------------------------------

#pragma hdrstop

//===========================================================================
#include <vcl.h>
#include "NLTK_common.h"
//---------------------------------------------------------------------------
#include "nlTeam.h"
//---------------------------------------------------------------------------
//===========================================================================
#pragma package(smart_init)

//===========================================================================
// initialisation des variables statiques :
//---------------------------------------------------------------------------
DWORD CNLTeam::_instanceCount = 0;
TStrings* CNLTeam::_fieldNames = NULL;
//===========================================================================

//===========================================================================
// CONSTANTES : liste des noms de champs de la table PLAYERS
//---------------------------------------------------------------------------
#define FIELD_TEAMNUM	      	AnsiString( "TEAMNUM" )
#define FIELD_TEAMNAME          AnsiString( "TEAMNAME" )
#define FIELD_CITYNAME          AnsiString( "CITYNAME" )
#define FIELD_ABREV             AnsiString( "ABBREV" )
#define FIELD_INSEASON          AnsiString( "INSEASON" )
#define FIELD_TEAMCODE          AnsiString( "TEAMCODE" )
#define FIELD_CONFERENCE        AnsiString( "CONFERENCE" )
#define FIELD_DIVISION          AnsiString( "DIVISION" )
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
__fastcall CNLTeam::CNLTeam()
{
    this->zero();
    this->init();

    this->_instanceCount++;
}
//---------------------------------------------------------------------------
__fastcall CNLTeam::CNLTeam( CDBTable* t )
{
    this->zero();
    this->init();

    this->_instanceCount++;

    this->loadFromTable( t );
}
//---------------------------------------------------------------------------
__fastcall CNLTeam::~CNLTeam()
{
    this->_instanceCount--;
    this->deinit();
    this->zero();
}
//---------------------------------------------------------------------------
bool __fastcall CNLTeam::loadFromTable( CDBTable* t )
{
    bool ok = false;


    if ( this->_record && t )
    {
        ok = this->_record->readFromTable( t );
    }

    return ok;
}
//---------------------------------------------------------------------------
void __fastcall CNLTeam::zero()
{
    this->_record = NULL;
}
//---------------------------------------------------------------------------
void __fastcall CNLTeam::init()
{
    if ( this->_instanceCount == 0 ) this->createFieldNames();

    this->_record = new CDBRecord();
    this->_record->createFields( this->_fieldNames );

    this->_instanceCount++;
}
//---------------------------------------------------------------------------
void __fastcall CNLTeam::deinit()
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
void __fastcall CNLTeam::createFieldNames()
{
    if ( !CNLTeam::_fieldNames )
    {
        CNLTeam::_fieldNames = new TStringList();

        CNLTeam::_fieldNames->Add( FIELD_TEAMNUM );
        CNLTeam::_fieldNames->Add( FIELD_TEAMNAME );
        CNLTeam::_fieldNames->Add( FIELD_CITYNAME );
        CNLTeam::_fieldNames->Add( FIELD_ABREV );
        CNLTeam::_fieldNames->Add( FIELD_INSEASON );
        CNLTeam::_fieldNames->Add( FIELD_TEAMCODE );
        CNLTeam::_fieldNames->Add( FIELD_CONFERENCE );
        CNLTeam::_fieldNames->Add( FIELD_DIVISION );
    }
}
//---------------------------------------------------------------------------
void __fastcall CNLTeam::deleteFieldNames()
{
    if ( CNLTeam::_fieldNames )
    {
        CNLTeam::_fieldNames->Clear();
        delete CNLTeam::_fieldNames;
        CNLTeam::_fieldNames = NULL;
    }
}
//---------------------------------------------------------------------------
WORD __fastcall CNLTeam::getTeamNum()
{
    WORD TEAMNUM = 0;

    if ( this->_record )
    {
        TEAMNUM = this->_record->ram[ FIELD_TEAMNUM ].ToIntDef(TEAMNUM_UNDEF);
    }

    return TEAMNUM;
}
//---------------------------------------------------------------------------
AnsiString __fastcall CNLTeam::getTeamName()
{
    AnsiString TEAMNAME = TXT_NULL;

    if ( this->_record )
    {
        TEAMNAME = this->_record->ram[ FIELD_TEAMNAME ];
    }

    return TEAMNAME;
}
//---------------------------------------------------------------------------
AnsiString __fastcall CNLTeam::getCityName()
{
    AnsiString CITYNAME = TXT_NULL;

    if ( this->_record )
    {
        CITYNAME = this->_record->ram[ FIELD_CITYNAME ];
    }

    return CITYNAME;
}
//---------------------------------------------------------------------------
AnsiString __fastcall CNLTeam::getAbrev()
{
    AnsiString ABREV = TXT_NULL;

    if ( this->_record )
    {
        ABREV = this->_record->ram[ FIELD_ABREV ];
    }

    return ABREV;
}
//---------------------------------------------------------------------------
WORD __fastcall CNLTeam::getInSeason()
{
    WORD INSEASON = INSEASON_UNDEF;

    if ( this->_record )
    {
        INSEASON = this->_record->ram[ FIELD_INSEASON ].ToIntDef( INSEASON_UNDEF );
    }

    return INSEASON;
}
//---------------------------------------------------------------------------
WORD __fastcall CNLTeam::getTeamCode()
{
    WORD TEAMCODE = TEAMCODE_UNDEF;

    if ( this->_record )
    {
        TEAMCODE = this->_record->ram[ FIELD_TEAMCODE ].ToIntDef( TEAMCODE_UNDEF );
    }

    return TEAMCODE;
}
//---------------------------------------------------------------------------
WORD __fastcall CNLTeam::getConference()
{
    WORD CONFERENCE = CONFERENCE_UNDEF;

    if ( this->_record )
    {
        CONFERENCE = this->_record->ram[ FIELD_CONFERENCE ].ToIntDef( CONFERENCE_UNDEF );
    }

    return CONFERENCE;
}
//---------------------------------------------------------------------------
WORD __fastcall CNLTeam::getDivision()
{
    WORD DIVISION = DIVISION_UNDEF;

    if ( this->_record )
    {
        DIVISION = this->_record->ram[ FIELD_DIVISION ].ToIntDef( DIVISION_UNDEF );
    }

    return DIVISION;
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
