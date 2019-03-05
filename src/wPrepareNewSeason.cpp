//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "wPrepareNewSeason.h"
#include "NLTK_common.h"
#include "wIconLists.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TPrepareNewSeasonDlg *PrepareNewSeasonDlg;
//---------------------------------------------------------------------------
__fastcall TPrepareNewSeasonDlg::TPrepareNewSeasonDlg(TComponent* Owner)
	: TForm(Owner)
{
	this->zero();
	this->init();
}
//---------------------------------------------------------------------------
__fastcall TPrepareNewSeasonDlg::~TPrepareNewSeasonDlg()
{
	this->deinit();
    this->zero();
}
//---------------------------------------------------------------------------
void __fastcall TPrepareNewSeasonDlg::zero()
{
    this->_sg = NULL;
}
//---------------------------------------------------------------------------
void __fastcall TPrepareNewSeasonDlg::init()
{

}
//---------------------------------------------------------------------------
void __fastcall TPrepareNewSeasonDlg::deinit()
{

}
//---------------------------------------------------------------------------
void __fastcall TPrepareNewSeasonDlg::formInit()
{
	this->Caption = Application->Title;
	this->tbExpChangeFace->Position = 0;
}
//---------------------------------------------------------------------------
void __fastcall TPrepareNewSeasonDlg::formDeinit()
{

}
//---------------------------------------------------------------------------
void __fastcall TPrepareNewSeasonDlg::setSg( CNLSavedGame* sg )
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
void __fastcall TPrepareNewSeasonDlg::run()
{
    if ( this->_sg )
    {
		this->btnAccept->Enabled = false;

		System::Randomize();

		for ( int i = 0 ; i < this->_sg->playerCount ; i++ )
		{
            CNLPlayer* p = this->_sg->playerByIndex[ i ];
			if ( p )
			{
				if ( p->IsPlayable )
				{

					// on rend éditable le joueur généré automatiquement :
					//----------------------------------------------------------
					if ( p->IsCreated && p->IsGenerate )
					{
						p->IsGenerate = false;
					}

					// on random le visage dans l'uns des 4 variantes d'une couleur :
					//--------------------------------------------------------------
					if ( p->YearsExp <= this->tbExpChangeFace->Position )
					{
						WORD random = System::Random( 4 );
						WORD newFace = COLORED_FACE(p->Color,random);
						AnsiString playerPkg = p->PlayerPkg;
						if ( playerPkg.Length() == 4 )
						{
							playerPkg[4] = ('A'+newFace);

							p->Face = newFace;
							p->PlayerPkg = playerPkg;
						}
					}

				}
            }

			this->pbPlayers->Position = i+1;
        }

        this->btnAccept->Enabled = true;
    }
}
//---------------------------------------------------------------------------
void __fastcall TPrepareNewSeasonDlg::accept()
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
void __fastcall TPrepareNewSeasonDlg::FormCreate(TObject *Sender)
{
	this->formInit();
}
//---------------------------------------------------------------------------
void __fastcall TPrepareNewSeasonDlg::FormDestroy(TObject *Sender)
{
	this->formDeinit();
}
//---------------------------------------------------------------------------
void __fastcall TPrepareNewSeasonDlg::btnRunClick(TObject *Sender)
{
    this->run();
}
//---------------------------------------------------------------------------
void __fastcall TPrepareNewSeasonDlg::btnAcceptClick(TObject *Sender)
{
	this->accept();
}
//---------------------------------------------------------------------------
void __fastcall TPrepareNewSeasonDlg::tbExpChangeFaceChange(TObject *Sender)
{
	this->lblExpChangeFace->Caption = this->lblExpChangeFace->Caption.sprintf(L"Expérience maxi changement de visage = %d",this->tbExpChangeFace->Position );
}
//---------------------------------------------------------------------------
