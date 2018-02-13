//---------------------------------------------------------------------------

#ifndef wndMainH
#define wndMainH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TPlayerDebugDlg : public TForm
{
__published:	// Composants gérés par l'EDI
	TPanel *pnlCmds;
	TButton *btnFirst;
	TButton *btnPrior;
	TButton *btnNext;
	TButton *btnLast;
	TEdit *edtRecordIndex;
	TMemo *txtLog;
	TButton *btnTest;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormDestroy(TObject *Sender);
	void __fastcall btnFirstClick(TObject *Sender);
	void __fastcall btnPriorClick(TObject *Sender);
	void __fastcall btnNextClick(TObject *Sender);
	void __fastcall btnLastClick(TObject *Sender);
	void __fastcall btnTestClick(TObject *Sender);
private:	// Déclarations utilisateur

	// méthodes internes :
	//--------------------
	void __fastcall zero();
	void __fastcall init();
	void __fastcall deinit();

	void __fastcall formInit();
	void __fastcall formDeinit();

	void __fastcall updateRecordIndex();

	// variables internes :
	//---------------------
	CDBTable* _tPlayers;
    TStrings* _fPlayers;
    CDBTable* _tTeams;
    TStrings* _fTeams;


public:		// Déclarations utilisateur

	// constructeurs & destructeur :
	//------------------------------
			__fastcall TPlayerDebugDlg(TComponent* Owner);
	virtual __fastcall ~TPlayerDebugDlg();
};
//---------------------------------------------------------------------------
extern PACKAGE TPlayerDebugDlg *PlayerDebugDlg;
//---------------------------------------------------------------------------
#endif

