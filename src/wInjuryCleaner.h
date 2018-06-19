//---------------------------------------------------------------------------

#ifndef wInjuryCleanerH
#define wInjuryCleanerH
//---------------------------------------------------------------------------
#include "nlSavedGame.h"
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ComCtrls.hpp>
//---------------------------------------------------------------------------
class TInjuryCleanerDlg : public TForm
{
__published:	// Composants gérés par l'EDI
	TProgressBar *pbPlayers;
	TLabel *lblPlayer;
	TButton *btnRun;
	TButton *btnAccept;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormDestroy(TObject *Sender);
	void __fastcall btnRunClick(TObject *Sender);
	void __fastcall btnAcceptClick(TObject *Sender);
private:	// Déclarations utilisateur

   // méthodes internes :
    //--------------------
    void __fastcall zero();
    void __fastcall init();
    void __fastcall deinit();
    void __fastcall formInit();
    void __fastcall formDeinit();
    void __fastcall run();
    void __fastcall accept();

    // méthodes get/set des propriétés :
    //----------------------------------
    void 		__fastcall setSg( CNLSavedGame* sg );

    // variables internes :
    //---------------------
    CNLSavedGame* _sg;



public:		// Déclarations utilisateur

	// propriétés publiques :
    //-----------------------
    __property CNLSavedGame* sg = { read = _sg , write = setSg };

    // constructeurs & destructeur :
    //------------------------------
			__fastcall TInjuryCleanerDlg(TComponent* Owner);
    virtual __fastcall ~TInjuryCleanerDlg();
};
//---------------------------------------------------------------------------
extern PACKAGE TInjuryCleanerDlg *InjuryCleanerDlg;
//---------------------------------------------------------------------------
#endif
