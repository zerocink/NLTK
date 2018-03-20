//---------------------------------------------------------------------------

#ifndef wDraftReviewH
#define wDraftReviewH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
//---------------------------------------------------------------------------
#include "nlSavedGame.h"
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Grids.hpp>
//---------------------------------------------------------------------------
class TDraftReviewDlg : public TForm
{
__published:	// Composants gérés par l'EDI
	TPanel *pnlDrafts;
	TComboBox *cbDraftSel;
	TStringGrid *gridPlayers;
	void __fastcall cbDraftSelChange(TObject *Sender);
private:	// Déclarations utilisateur

    // méthodes internes :
    //--------------------
    void __fastcall zero();
    void __fastcall init();
    void __fastcall deinit();
    void __fastcall formInit();
    void __fastcall formDeinit();
    void __fastcall clearDrafts();
    void __fastcall updateDrafts();
    void __fastcall updatePlayers();
    void __fastcall playerDisplay( CNLPlayer* p , int row );
    void __fastcall autoSizeCol( int col );
    void __fastcall autoSizeRow( int row );

    // méthodes get/set des propriétés :
    //----------------------------------
    void 		__fastcall setSg( CNLSavedGame* sg );
    CNLDraft*   __fastcall getDraftByYear( WORD year );
    CNLDraft*   __fastcall getDraftByIndex( int index );
    int         __fastcall getDraftCount();

    // propriétés internes :
    //----------------------
    __property CNLDraft* draftByYear[ WORD year ]   = { read = getDraftByYear	};
    __property CNLDraft* draftByIndex[ int index ]  = { read = getDraftByIndex  };
    __property int       draftCount                 = { read = getDraftCount    };

    // variables internes :
    //---------------------
    CNLSavedGame* _sg;
    TList*        _drafts;

public:		// Déclarations utilisateur

	// propriétés publiques :
    //-----------------------
    __property CNLSavedGame* sg = { read = _sg , write = setSg };

    // constructeurs & destructeur :
    //------------------------------
			__fastcall TDraftReviewDlg(TComponent* Owner);
    virtual __fastcall ~TDraftReviewDlg();
};
//---------------------------------------------------------------------------
extern PACKAGE TDraftReviewDlg *DraftReviewDlg;
//---------------------------------------------------------------------------
#endif
