//---------------------------------------------------------------------------

#pragma hdrstop

//===========================================================================
#include <vcl.h>
#include "NLTK_common.h"
//---------------------------------------------------------------------------
#include "nlPlayer.h"
//---------------------------------------------------------------------------
//===========================================================================

#pragma package(smart_init)

//===========================================================================
// initialisation des variables statiques :
//---------------------------------------------------------------------------
DWORD CNLPlayer::_instanceCount = 0;
TStrings* CNLPlayer::_fieldNames = NULL;
//===========================================================================


//===========================================================================
// CONSTANTES : liste des noms de champs de la table PLAYERS
//---------------------------------------------------------------------------
#define FIELD_ID	      	AnsiString( "PLAYERID" )
#define FIELD_NAME        	AnsiString( "NAME" )
#define FIELD_FNAME       	AnsiString( "FNAME" )
#define FIELD_POSITION1    	AnsiString( "POSITION" )
#define FIELD_POSITION2     AnsiString( "POSITION2" )
#define FIELD_NUMBER        AnsiString( "NUMBER" )
#define FIELD_HEIGHT        AnsiString( "HEIGHT" )
#define FIELD_WEIGHT        AnsiString( "WEIGHT" )
//===========================================================================
// CONSTANTES : liste des positions
//---------------------------------------------------------------------------
#define POS_PG_DW           4
#define POS_SG_DW           3
#define POS_SF_DW           2
#define POS_PF_DW           1
#define POS_C_DW            0
#define POS_NONE_DW     	-1
//---------------------------------------------------------------------------
#define POS_PG_TXT          AnsiString( "PG" )
#define POS_SG_TXT          AnsiString( "SG" )
#define POS_SF_TXT          AnsiString( "SF" )
#define POS_PF_TXT          AnsiString( "PF" )
#define POS_C_TXT           AnsiString( "C"  )
#define POS_NONE_TXT        AnsiString( "-"  )
//===========================================================================



//===========================================================================
//===========================================================================
//===========================================================================
//===========================================================================
//===========================================================================
//---------------------------------------------------------------------------
__fastcall CNLPlayer::CNLPlayer()
{
    this->zero();
    this->init();

    this->_instanceCount++;
}
//---------------------------------------------------------------------------
__fastcall CNLPlayer::CNLPlayer( CDBTable* t )
{
    this->zero();
    this->init();

    this->_instanceCount++;

    this->loadFromTable( t );
}
//---------------------------------------------------------------------------
__fastcall CNLPlayer::~CNLPlayer()
{
    this->_instanceCount--;
    this->deinit();
    this->zero();
}
//---------------------------------------------------------------------------
bool __fastcall CNLPlayer::loadFromTable( CDBTable* t )
{
    bool ok = false;


    if ( this->_record && t )
    {
        ok = this->_record->readFromTable( t );
    }

    return ok;
}
//---------------------------------------------------------------------------
void __fastcall CNLPlayer::zero()
{
    this->_record = NULL;
}
//---------------------------------------------------------------------------
void __fastcall CNLPlayer::init()
{
    if ( this->_instanceCount == 0 ) this->createFieldNames();

    this->_record = new CDBRecord();
    this->_record->createFields( this->_fieldNames );
}
//---------------------------------------------------------------------------
void __fastcall CNLPlayer::deinit()
{
    if ( this->_record )
    {
        this->_record->deleteFields( this->_fieldNames );
        delete this->_record;
        this->_record = NULL;
    }

    if ( this->_instanceCount != 0 ) this->deleteFieldNames();
}
//---------------------------------------------------------------------------
void __fastcall CNLPlayer::createFieldNames()
{
    if ( !CNLPlayer::_fieldNames )
    {
        CNLPlayer::_fieldNames = new TStringList();

        CNLPlayer::_fieldNames->Add( FIELD_ID );
        CNLPlayer::_fieldNames->Add( FIELD_NAME );
        CNLPlayer::_fieldNames->Add( FIELD_FNAME );
        CNLPlayer::_fieldNames->Add( FIELD_HEIGHT );
        CNLPlayer::_fieldNames->Add( FIELD_WEIGHT );
        CNLPlayer::_fieldNames->Add( FIELD_POSITION1 );
        CNLPlayer::_fieldNames->Add( FIELD_POSITION2 );
        CNLPlayer::_fieldNames->Add( FIELD_NUMBER );
    }
}
//---------------------------------------------------------------------------
void __fastcall CNLPlayer::deleteFieldNames()
{
    if ( CNLPlayer::_fieldNames )
    {
        CNLPlayer::_fieldNames->Clear();
        delete CNLPlayer::_fieldNames;
        CNLPlayer::_fieldNames = NULL;
    }
}
//---------------------------------------------------------------------------
DWORD __fastcall CNLPlayer::getID()
{
    DWORD ID = 0;

    if ( this->_record )
    {
        AnsiString ID_asString = this->_record->ram[ FIELD_ID ];
        ID = ID_asString.ToIntDef( 0 );
    }
    return ID;
}
//---------------------------------------------------------------------------
AnsiString __fastcall CNLPlayer::getName()
{
    AnsiString NAME = TXT_NULL;
    if ( this->_record )
    {
        NAME = this->_record->ram[ FIELD_NAME ];
    }
    return NAME;
}
//---------------------------------------------------------------------------
AnsiString __fastcall CNLPlayer::getFName()
{
    AnsiString FNAME = TXT_NULL;
    if ( this->_record )
    {
        FNAME = this->_record->ram[ FIELD_FNAME ];
    }
    return FNAME;
}
//---------------------------------------------------------------------------
AnsiString __fastcall CNLPlayer::getNumber()
{
    AnsiString NUMBER = TXT_NULL;
    if ( this->_record )
    {
        int NUMBER_asInt = this->_record->ram[ FIELD_NUMBER ].ToIntDef(-2);
        if ( NUMBER_asInt >= 0 ) NUMBER = IntToStr( NUMBER_asInt );
        else if ( NUMBER_asInt == -1 ) NUMBER = AnsiString( "00" );
    }
    return NUMBER;
}
//---------------------------------------------------------------------------
DWORD __fastcall CNLPlayer::getWeight()
{
    return 0;
}
//---------------------------------------------------------------------------
DWORD __fastcall CNLPlayer::getHeight()
{
    return 0;
}
//---------------------------------------------------------------------------
AnsiString __fastcall CNLPlayer::getPosition1()
{
    return TXT_NULL;
}
//---------------------------------------------------------------------------
AnsiString __fastcall CNLPlayer::getPosition2()
{
    return TXT_NULL;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//===========================================================================
//===========================================================================
//===========================================================================
//===========================================================================
//===========================================================================

