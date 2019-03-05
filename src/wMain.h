//---------------------------------------------------------------------------

#ifndef wMainH
#define wMainH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ComCtrls.hpp>
#include <System.ImageList.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.ImgList.hpp>
//---------------------------------------------------------------------------
class TMainDlg : public TForm
{
__published:	// Composants g�r�s par l'EDI
	TButton *btnPlayerDebug;
	TButton *btnRosters;
	TComboBox *cbSavedGamesPaths;
	TButton *btnDrafts;
	TButton *btnMVP;
	TButton *btnInjuryCleaner;
	TButton *btnPrepareNewSeason;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormDestroy(TObject *Sender);
	void __fastcall btnPlayerDebugClick(TObject *Sender);
	void __fastcall btnRostersClick(TObject *Sender);
	void __fastcall btnDraftsClick(TObject *Sender);
	void __fastcall btnMVPClick(TObject *Sender);
	void __fastcall btnInjuryCleanerClick(TObject *Sender);
	void __fastcall btnPrepareNewSeasonClick(TObject *Sender);
private:	// D�clarations utilisateur


    // m�thodes internes :
    //--------------------
    void __fastcall zero();
    void __fastcall init();
    void __fastcall deinit();
	void __fastcall formInit();
    void __fastcall formDeinit();
    void __fastcall loadSavedGamesPaths();

    // variables internes :
	//---------------------
	TRosterEditorDlg* 		_rosterEditor;
	TDraftReviewDlg*    	_draftReview;
	TInjuryCleanerDlg*  	_injuryCleaner;
	TPrepareNewSeasonDlg* 	_prepareNewSeason;
    //TStrings* 			_savedGamesPaths;

public:		// D�clarations utilisateur

    // constructeurs & destructeur :
    //------------------------------
			__fastcall TMainDlg(TComponent* Owner);
    virtual __fastcall ~TMainDlg();
};
//---------------------------------------------------------------------------
extern PACKAGE TMainDlg *MainDlg;
//---------------------------------------------------------------------------
#endif
