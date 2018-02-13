//---------------------------------------------------------------------------

#ifndef wRosterEditorH
#define wRosterEditorH
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
class TRosterEditorDlg : public TForm
{
__published:	// Composants gérés par l'EDI
	TPanel *pnlTeam;
	TButton *btnTeamPrev;
	TButton *btnTeamNext;
	TComboBox *cbTeamSel;
	TStringGrid *gridPlayers;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormDestroy(TObject *Sender);
	void __fastcall cbTeamSelChange(TObject *Sender);
	void __fastcall btnTeamPrevClick(TObject *Sender);
	void __fastcall btnTeamNextClick(TObject *Sender);
	void __fastcall gridPlayersDrawCell(TObject *Sender, int ACol, int ARow, TRect &Rect,
          TGridDrawState State);
private:	// Déclarations utilisateur

    // méthodes internes :
    //--------------------
    void __fastcall zero();
    void __fastcall init();
    void __fastcall deinit();
    void __fastcall formInit();
    void __fastcall formDeinit();
    void __fastcall clearRosters();
    void __fastcall updateTeams();
    void __fastcall updatePlayers();
    void __fastcall autoSizeCol( int col );
    void __fastcall autoSizeRow( int row );

    // méthodes get/set des propriétés :
    //----------------------------------
    void 		__fastcall setSg( CNLSavedGame* sg );
    CNLRoster* 	__fastcall getTeamRoster( WORD teamNum );

    // propriétés internes :
    //----------------------
    __property CNLRoster* teamRoster[ WORD teamNum ] = { read = getTeamRoster };

    // variables internes :
    //---------------------
    CNLSavedGame* _sg;
    TList*        _rosters;


public:		// Déclarations utilisateur

	// propriétés publiques :
    //-----------------------
    __property CNLSavedGame* sg = { read = _sg , write = setSg };

    // constructeurs & destructeur :
    //------------------------------
			__fastcall TRosterEditorDlg(TComponent* Owner);
    virtual __fastcall ~TRosterEditorDlg();
};
//---------------------------------------------------------------------------
extern PACKAGE TRosterEditorDlg *RosterEditorDlg;
//---------------------------------------------------------------------------
#endif
