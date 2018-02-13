//---------------------------------------------------------------------------


//===========================================================================
//#include <vcl.h>
#include "NLTK_common.h"
#include "dbf.h"
#include "dbEngine.h"
#pragma hdrstop
//---------------------------------------------------------------------------
#include "wPlayerDebug.h"
//---------------------------------------------------------------------------
#include "nlPlayer.h"
#include "nlTeam.h"
//===========================================================================


//===========================================================================
//===========================================================================

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"


//===========================================================================
TPlayerDebugDlg *PlayerDebugDlg;
//===========================================================================


//===========================================================================
//===========================================================================
//===========================================================================
//===========================================================================
//===========================================================================
//===========================================================================
// CLASSE TWnMain
//---------------------------------------------------------------------------
__fastcall TPlayerDebugDlg::TPlayerDebugDlg(TComponent* Owner)
	: TForm(Owner)
{
	this->zero();
	this->init();
}
//---------------------------------------------------------------------------
__fastcall TPlayerDebugDlg::~TPlayerDebugDlg()
{
	this->deinit();
	this->zero();
}
//---------------------------------------------------------------------------
void __fastcall TPlayerDebugDlg::zero()
{
	this->_tPlayers = NULL;
	this->_fPlayers = NULL;
    this->_tTeams = NULL;
    this->_fTeams = NULL;
}
//---------------------------------------------------------------------------
void __fastcall TPlayerDebugDlg::init()
{
    AnsiString dbPath		= AnsiString( "D:\\PERSO ND\\Dev\\NLTK\\res\\db\\100\\" );
    AnsiString playersPath 	= dbPath + AnsiString( "Players.dbf" );
    AnsiString teamsPath    = dbPath + AnsiString( "Teams.dbf" );


	if ( !this->_tPlayers )
	{
		this->_tPlayers = new CDBTable( playersPath  );
		this->_tPlayers->open();
	}

	if ( !this->_fPlayers )
	{
		this->_fPlayers = new TStringList();
		this->_tPlayers->loadFieldNames( this->_fPlayers );
    }

    if ( ! this->_tTeams )
    {
        this->_tTeams = new CDBTable( teamsPath );
        this->_tTeams->open();
    }

    if ( !this->_fTeams )
    {
        this->_fTeams = new TStringList();
        this->_tTeams->loadFieldNames( this->_fTeams );
    }
}
//---------------------------------------------------------------------------
void __fastcall TPlayerDebugDlg::deinit()
{
	if ( this->_tPlayers )
	{
		this->_tPlayers->close();

		delete this->_tPlayers;
		this->_tPlayers = NULL;
    }

    if ( this->_fPlayers )
    {
        this->_fPlayers->Clear();
        delete this->_fPlayers;
        this->_fPlayers = NULL;
    }
	if ( this->_tTeams )
	{
		this->_tTeams->close();

		delete this->_tTeams;
		this->_tTeams = NULL;
    }

    if ( this->_fTeams )
    {
        this->_fTeams->Clear();
        delete this->_fPlayers;
        this->_fPlayers = NULL;
    }
}
//---------------------------------------------------------------------------
void __fastcall TPlayerDebugDlg::formInit()
{
	this->Caption = Application->Title;

	this->updateRecordIndex();
}
//---------------------------------------------------------------------------
void __fastcall TPlayerDebugDlg::formDeinit()
{

}
//---------------------------------------------------------------------------
void __fastcall TPlayerDebugDlg::updateRecordIndex()
{
	AnsiString recordIndex;

	if ( this->_tPlayers )
	{
		recordIndex = IntToStr( (int)this->_tPlayers->recordIndex ) + AnsiString( " / " ) + IntToStr( (int)this->_tPlayers->recordCount-1 );

		this->txtLog->Lines->Clear();
		if ( this->_fPlayers )
		{
			for ( int i = 0 ; i < this->_fPlayers->Count ; i++ )
			{
				AnsiString fieldName = this->_fPlayers->Strings[i];
				AnsiString fieldValue;
				if ( !this->_tPlayers->getFieldValueString( fieldName , fieldValue ) ) fieldValue = AnsiString( "ERREUR" );

				this->txtLog->Lines->Add( fieldName + AnsiString( " = " ) + fieldValue );
			}
		}
	}
	else
	{
		recordIndex = AnsiString( "? / ?" );
		this->txtLog->Lines->Clear();
	}

	this->edtRecordIndex->Text = recordIndex;
}
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
//===========================================================================

void __fastcall TPlayerDebugDlg::FormCreate(TObject *Sender)
{
    this->formInit();
}
//---------------------------------------------------------------------------

void __fastcall TPlayerDebugDlg::FormDestroy(TObject *Sender)
{
	this->formDeinit();
}
//---------------------------------------------------------------------------


void __fastcall TPlayerDebugDlg::btnFirstClick(TObject *Sender)
{
	if ( this->_tPlayers ) this->_tPlayers->first();

	this->updateRecordIndex();
}
//---------------------------------------------------------------------------

void __fastcall TPlayerDebugDlg::btnPriorClick(TObject *Sender)
{
	if ( this->_tPlayers ) this->_tPlayers->prior();

	this->updateRecordIndex();
}
//---------------------------------------------------------------------------

void __fastcall TPlayerDebugDlg::btnNextClick(TObject *Sender)
{
	if ( this->_tPlayers ) this->_tPlayers->next();

	this->updateRecordIndex();
}
//---------------------------------------------------------------------------

void __fastcall TPlayerDebugDlg::btnLastClick(TObject *Sender)
{
	if ( this->_tPlayers ) this->_tPlayers->last();

	this->updateRecordIndex();
}
//---------------------------------------------------------------------------

void __fastcall TPlayerDebugDlg::btnTestClick(TObject *Sender)
{
    this->txtLog->Clear();

    TList* list = new TList();

    if ( this->_tPlayers )
    {
        this->_tPlayers->first();

        AnsiString line = TXT_NULL;
        for ( int i = 0 ; i < this->_tPlayers->recordCount ; i++ )
        {
            CNLPlayer* p = new CNLPlayer( this->_tPlayers );

            //line.sprintf( "[ %04d ] id = %04d ; number = %s; name = %s ; fname = %s " , i , p->ID , p->Number , p->Name.c_str() , p->FName.c_str() );

            line.sprintf( "%s : %02s %s %s (%s %s) %d kg %d cm" , p->RosterPosText ,p->Number , p->FName , p->Name , p->Position1 , p->Position2 , p->Weight , p->Height );

			this->txtLog->Lines->Add( line );

            delete p;
            p = NULL;

            this->_tPlayers->next();
        }

    }

    delete list;
    list = NULL;
/*
	if ( this->_tPlayers )
	{
		if ( this->_tPlayers->first() )
		{
			bool ok = this->_tPlayers->setFieldValueString( AnsiString("NAME") , AnsiString( "TOTO") );
			if ( ok ) ok = this->_tPlayers->post();
			if ( ok ) ShowMessage( "post = OK" );
        }
	}

	this->updateRecordIndex();
*/
}
//---------------------------------------------------------------------------


