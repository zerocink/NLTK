//---------------------------------------------------------------------------

#ifndef wPrepareNewSeasonH
#define wPrepareNewSeasonH
//---------------------------------------------------------------------------
#include "nlSavedGame.h"
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TPrepareNewSeasonDlg : public TForm
{
__published:	// Composants g�r�s par l'EDI
	TLabel *lblPlayer;
	TProgressBar *pbPlayers;
	TButton *btnRun;
	TButton *btnAccept;
	TPanel *Panel1;
	TLabel *lblExpChangeFace;
	TTrackBar *tbExpChangeFace;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormDestroy(TObject *Sender);
	void __fastcall btnRunClick(TObject *Sender);
	void __fastcall btnAcceptClick(TObject *Sender);
	void __fastcall tbExpChangeFaceChange(TObject *Sender);
private:	// D�clarations utilisateur

 // m�thodes internes :
    //--------------------
    void __fastcall zero();
    void __fastcall init();
    void __fastcall deinit();
    void __fastcall formInit();
	void __fastcall formDeinit();
	void __fastcall run();
	void __fastcall accept();

    // m�thodes get/set des propri�t�s :
	//----------------------------------
    void 		__fastcall setSg( CNLSavedGame* sg );

	// variables internes :
    //---------------------
	CNLSavedGame* _sg;


public:		// D�clarations utilisateur

	// propri�t�s publiques :
    //-----------------------
    __property CNLSavedGame* sg = { read = _sg , write = setSg };

    // constructeurs & destructeur :
	//------------------------------
			__fastcall TPrepareNewSeasonDlg(TComponent* Owner);
	virtual __fastcall ~TPrepareNewSeasonDlg();
};
//---------------------------------------------------------------------------
extern PACKAGE TPrepareNewSeasonDlg *PrepareNewSeasonDlg;
//---------------------------------------------------------------------------
#endif
