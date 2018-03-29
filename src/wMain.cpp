//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

//---------------------------------------------------------------------------
#include "wRosterEditor.h"
#include "wDraftReview.h"
//---------------------------------------------------------------------------
#include "wMain.h"
//---------------------------------------------------------------------------
#include "nlSavedGame.h"
#include "wPlayerDebug.h"
#include "wIconLists.h"
#include "dbEngine.h"
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TMainDlg *MainDlg;
//---------------------------------------------------------------------------
__fastcall TMainDlg::TMainDlg(TComponent* Owner)
	: TForm(Owner)
{
    this->zero();
    this->init();
}
//---------------------------------------------------------------------------
__fastcall TMainDlg::~TMainDlg()
{
    this->deinit();
    this->zero();
}
//---------------------------------------------------------------------------
void __fastcall TMainDlg::zero()
{
    this->_rosterEditor = NULL;
    this->_draftReview = NULL;
}
//---------------------------------------------------------------------------
void __fastcall TMainDlg::init()
{
    if ( !this->_rosterEditor ) this->_rosterEditor = new TRosterEditorDlg(NULL );
    if ( !this->_draftReview ) this->_draftReview = new TDraftReviewDlg( NULL );
}
//---------------------------------------------------------------------------
void __fastcall TMainDlg::deinit()
{
    if ( this->_draftReview )
    {
        delete this->_draftReview;
        this->_draftReview = NULL;

    }
    if ( this->_rosterEditor )
    {
    	delete this->_rosterEditor;
        this->_rosterEditor = NULL;
    }

}
//---------------------------------------------------------------------------
void __fastcall TMainDlg::formInit()
{
    this->Caption = Application->Title;

    this->loadSavedGamesPaths();
}
//---------------------------------------------------------------------------
void __fastcall TMainDlg::formDeinit()
{

}
//---------------------------------------------------------------------------
void __fastcall TMainDlg::loadSavedGamesPaths()
{
    bool ok = false;

    if ( this->cbSavedGamesPaths->Items->Count == 0 )
    {
        AnsiString root = System::Sysutils::ExtractFilePath( Application->ExeName ) + AnsiString( "\\saves" );
        if ( System::Sysutils::DirectoryExists( root , false  ) )
        {
            for ( int i = 0 ; i <= 999 ; i++ )
            {
                AnsiString savePath;
                savePath.sprintf( "%s\\%03d" , root , i );
                if ( System::Sysutils::DirectoryExists( savePath , false ) )
                {
                    this->cbSavedGamesPaths->Items->Add( savePath );
                }
            }
        }
    }

    this->cbSavedGamesPaths->ItemIndex = -1;
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
//===========================================================================
//===========================================================================
//===========================================================================
//===========================================================================
//===========================================================================
//===========================================================================
//===========================================================================
//===========================================================================
//===========================================================================
//===========================================================================
void __fastcall TMainDlg::FormCreate(TObject *Sender)
{
    this->formInit();
}
//---------------------------------------------------------------------------
void __fastcall TMainDlg::FormDestroy(TObject *Sender)
{
    this->formDeinit();
}
//---------------------------------------------------------------------------
void __fastcall TMainDlg::btnPlayerDebugClick(TObject *Sender)
{
    TDate dt = CDBEngine::stringToDate( AnsiString("20150331") );

    AnsiString s = CDBEngine::dateToString( dt );
    ShowMessage( s );

/*    TPlayerDebugDlg* pdebug = new TPlayerDebugDlg( NULL );


    pdebug->ShowModal();


    delete pdebug;
    pdebug = NULL;*/
}
//---------------------------------------------------------------------------
void __fastcall TMainDlg::btnRostersClick(TObject *Sender)
{
 	AnsiString path = this->cbSavedGamesPaths->Items->Strings[ this->cbSavedGamesPaths->ItemIndex ];

    CNLSavedGame* sg = new CNLSavedGame( path );
    bool ok = sg->open();

    if ( this->_rosterEditor )
    {
    	this->_rosterEditor->sg = sg;
        this->_rosterEditor->ShowModal();
    }

    sg->close();
    delete sg;
    sg = NULL;
}
//---------------------------------------------------------------------------

void __fastcall TMainDlg::btnDraftsClick(TObject *Sender)
{
 	AnsiString path = this->cbSavedGamesPaths->Items->Strings[ this->cbSavedGamesPaths->ItemIndex ];

    CNLSavedGame* sg = new CNLSavedGame( path );
    bool ok = sg->open();

    if ( this->_draftReview )
    {
    	this->_draftReview->sg = sg;
        this->_draftReview->ShowModal();
    }

    sg->close();
    delete sg;
    sg = NULL;
}
//---------------------------------------------------------------------------

void __fastcall TMainDlg::btnMVPClick(TObject *Sender)
{
    //;
}
//---------------------------------------------------------------------------

