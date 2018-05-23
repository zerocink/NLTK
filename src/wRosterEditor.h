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
#include <System.ImageList.hpp>
#include <Vcl.ImgList.hpp>
//---------------------------------------------------------------------------
class TRosterEditorDlg : public TForm
{
__published:	// Composants gérés par l'EDI
	TPanel *pnlTeam;
	TButton *btnTeamPrev;
	TButton *btnTeamNext;
	TStringGrid *gridPlayers;
	TPanel *pnlCmd;
	TButton *btnMoveUp;
	TButton *btnMoveDown;
	TButton *btnAccept;
	TComboBox *cbTeamSel;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormDestroy(TObject *Sender);
	void __fastcall cbTeamSelChange(TObject *Sender);
	void __fastcall btnTeamPrevClick(TObject *Sender);
	void __fastcall btnTeamNextClick(TObject *Sender);
	void __fastcall gridPlayersDrawCell(TObject *Sender, int ACol, int ARow, TRect &Rect,
          TGridDrawState State);
	void __fastcall btnMoveUpClick(TObject *Sender);
	void __fastcall btnMoveDownClick(TObject *Sender);
	void __fastcall btnAcceptClick(TObject *Sender);
	void __fastcall cbTeamSelMeasureItem(TWinControl *Control, int Index, int &Height);
	void __fastcall cbTeamSelDrawItem(TWinControl *Control, int Index, TRect &Rect,
          TOwnerDrawState State);
	void __fastcall gridPlayersColumnMoved(TObject *Sender, int FromIndex, int ToIndex);
	void __fastcall gridPlayersDblClick(TObject *Sender);



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
    void __fastcall playerDisplay( CNLPlayer* p , int row );
    void __fastcall playerMoveUp();
    void __fastcall playerMoveDown();
    bool __fastcall playerSwitch( int row1 , int row2 );
    void __fastcall rostersAccept();
    void __fastcall rostersUpdate();

    // méthodes get/set des propriétés :
    //----------------------------------
    void 		__fastcall setSg( CNLSavedGame* sg );
    CNLRoster* 	__fastcall getTeamRoster( WORD teamNum );
    CNLPlayer*  __fastcall getPlayerAtRow( int row );

    // propriétés internes :
    //----------------------
    __property CNLRoster* teamRoster[ WORD teamNum ] = { read = getTeamRoster };
    __property CNLPlayer* playerAtRow[ int row ] = { read = getPlayerAtRow };

    // variables internes :
    //---------------------
    CNLSavedGame* _sg;
    TList*        _rosters;
    TStringList*  _fieldCols;

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
