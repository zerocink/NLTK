//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

//---------------------------------------------------------------------------
#include "wInjuryCleaner.h"
#include "NLTK_common.h"
#include "wIconLists.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TInjuryCleanerDlg *InjuryCleanerDlg;
//---------------------------------------------------------------------------
__fastcall TInjuryCleanerDlg::TInjuryCleanerDlg(TComponent* Owner)
	: TForm(Owner)
{
	this->zero();
    this->init();
}
//---------------------------------------------------------------------------
__fastcall TInjuryCleanerDlg::~TInjuryCleanerDlg()
{
    this->deinit();
    this->zero();
}
//---------------------------------------------------------------------------
void __fastcall TInjuryCleanerDlg::zero()
{
    this->_sg = NULL;
}
//---------------------------------------------------------------------------
void __fastcall TInjuryCleanerDlg::init()
{

}
//---------------------------------------------------------------------------
void __fastcall TInjuryCleanerDlg::deinit()
{

}
//---------------------------------------------------------------------------
void __fastcall TInjuryCleanerDlg::formInit()
{
    this->Caption = Application->Title;
}
//---------------------------------------------------------------------------
void __fastcall TInjuryCleanerDlg::formDeinit()
{

}
//---------------------------------------------------------------------------
void __fastcall TInjuryCleanerDlg::setSg( CNLSavedGame* sg )
{
    this->_sg = sg;

    if ( sg )
    {
        this->pbPlayers->Min = 0;
        this->pbPlayers->Max = sg->playerCount;
        this->pbPlayers->Position = 0;

        this->btnAccept->Enabled = false;
        this->btnRun->Enabled = true;
    }
}
//---------------------------------------------------------------------------
void __fastcall TInjuryCleanerDlg::run()
{
    if ( this->_sg )
    {
        this->btnAccept->Enabled = false;

        TDate d = this->_sg->dateActive;
        ShowMessage( d );

        for ( int i = 0 ; i < this->_sg->playerCount ; i++ )
        {
            CNLPlayer* p = this->_sg->playerByIndex[ i ];
            if ( p )
            {
                if ( !p->IsPlayable && p->InjuryId != 0 )
                {
                    TDate rd = CDBEngine::stringToDate( p->RecoveryDate );
                    if ( rd < d )
                    {
                        p->IsPlayable = true;
                        p->InjuryDate = TXT_NULL;
                        p->RecoveryDate = TXT_NULL;
                        p->InjuryId = INJURYID_UNDEF;
                    }
                }
            }

            this->pbPlayers->Position = i+1;
        }

        this->btnAccept->Enabled = true;
    }
}
//---------------------------------------------------------------------------
void __fastcall TInjuryCleanerDlg::accept()
{
    if ( this->_sg )
    {
        bool ok = this->sg->playersAccept();
        if ( ok ) ok = this->sg->playersUpdate();
        if ( ok ) this->Close();
    }
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
//===========================================================================
//===========================================================================
//===========================================================================
//===========================================================================
//===========================================================================
//===========================================================================
//===========================================================================
void __fastcall TInjuryCleanerDlg::FormCreate(TObject *Sender)
{
    this->formInit();
}
//---------------------------------------------------------------------------

void __fastcall TInjuryCleanerDlg::FormDestroy(TObject *Sender)
{
    this->formDeinit();
}
//---------------------------------------------------------------------------

void __fastcall TInjuryCleanerDlg::btnRunClick(TObject *Sender)
{
    this->run();
}
//---------------------------------------------------------------------------

void __fastcall TInjuryCleanerDlg::btnAcceptClick(TObject *Sender)
{
    this->accept();
}
//---------------------------------------------------------------------------

