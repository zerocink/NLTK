//---------------------------------------------------------------------------

#ifndef wAcceptChangesH
#define wAcceptChangesH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Grids.hpp>
//---------------------------------------------------------------------------
class TAcceptChangesDlg : public TForm
{
__published:	// Composants gérés par l'EDI
	TPanel *pnlCmd;
	TButton *btnAccept;
	TButton *btnCancel;
	TMemo *txtChanges;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormDestroy(TObject *Sender);
private:	// Déclarations utilisateur

	// variables internes :
    //---------------------
    void __fastcall zero();
    void __fastcall init();
    void __fastcall deinit();
    void __fastcall formInit();
    void __fastcall formDeinit();

public:		// Déclarations utilisateur

    // méthodes publiques :
    //---------------------
    bool __fastcall execute( TStrings* changes );

    // constructeurs & destructeur :
    //------------------------------
			__fastcall TAcceptChangesDlg(TComponent* Owner);
    virtual __fastcall ~TAcceptChangesDlg();
};
//---------------------------------------------------------------------------
extern PACKAGE TAcceptChangesDlg *AcceptChangesDlg;
//---------------------------------------------------------------------------
#endif
