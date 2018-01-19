//---------------------------------------------------------------------------


//===========================================================================
//#include <vcl.h>
#include "NLTK_common.h"
#include "dbf.h"
#include "dbEngine.h"
#pragma hdrstop
//---------------------------------------------------------------------------
#include "wMain.h"
//---------------------------------------------------------------------------
//===========================================================================


//===========================================================================
//===========================================================================

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"


//===========================================================================
TMainForm *MainForm;
//===========================================================================


//===========================================================================
//===========================================================================
//===========================================================================
//===========================================================================
//===========================================================================
//===========================================================================
// CLASSE TWnMain
//---------------------------------------------------------------------------
__fastcall TMainForm::TMainForm(TComponent* Owner)
	: TForm(Owner)
{
	this->zero();
	this->init();
}
//---------------------------------------------------------------------------
__fastcall TMainForm::~TMainForm()
{
	this->deinit();
	this->zero();
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::zero()
{
	this->_t = NULL;
	this->_f = NULL;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::init()
{

	if ( !this->_t )
	{
		AnsiString tableFileName = AnsiString( "D:\\PERSO ND\\Dev\\NLTK\\res\\db\\100\\Players.dbf" );
		this->_t = new CDBTable( tableFileName  );

		this->_t->open();
	}

	if ( !this->_f )
	{
		this->_f = new TStringList();

		this->_t->loadFieldNames( this->_f );
    }
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::deinit()
{
	if ( this->_t )
	{
		this->_t->close();

		delete this->_t;
		this->_t = NULL;
    }
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::formInit()
{
	this->Caption = Application->Title;

	this->updateRecordIndex();
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::formDeinit()
{

}
//---------------------------------------------------------------------------
void __fastcall TMainForm::updateRecordIndex()
{
	AnsiString recordIndex;

	if ( this->_t )
	{
		recordIndex = IntToStr( (int)this->_t->recordIndex ) + AnsiString( " / " ) + IntToStr( (int)this->_t->recordCount-1 );

		this->txtLog->Lines->Clear();
		if ( this->_f )
		{
			for ( int i = 0 ; i < this->_f->Count ; i++ )
			{
				AnsiString fieldName = this->_f->Strings[i];
				AnsiString fieldValue;
				if ( !this->_t->getFieldValueString( fieldName , fieldValue ) ) fieldValue = AnsiString( "ERREUR" );

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

void __fastcall TMainForm::FormCreate(TObject *Sender)
{
    this->formInit();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::FormDestroy(TObject *Sender)
{
	this->formDeinit();
}
//---------------------------------------------------------------------------


void __fastcall TMainForm::btnFirstClick(TObject *Sender)
{
	if ( this->_t ) this->_t->first();

	this->updateRecordIndex();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::btnPriorClick(TObject *Sender)
{
	if ( this->_t ) this->_t->prior();

	this->updateRecordIndex();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::btnNextClick(TObject *Sender)
{
	if ( this->_t ) this->_t->next();

	this->updateRecordIndex();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::btnLastClick(TObject *Sender)
{
	if ( this->_t ) this->_t->last();

	this->updateRecordIndex();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::btnTestClick(TObject *Sender)
{
	if ( this->_t )
	{
		if ( this->_t->first() )
		{
			bool ok = this->_t->setFieldValueString( AnsiString("NAME") , AnsiString( "TOTO") );
			if ( ok ) ok = this->_t->post();
			if ( ok ) ShowMessage( "post = OK" );
        }
	}

	this->updateRecordIndex();

}
//---------------------------------------------------------------------------


