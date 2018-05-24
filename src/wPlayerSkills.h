//---------------------------------------------------------------------------

#ifndef wPlayerSkillsH
#define wPlayerSkillsH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Grids.hpp>
//---------------------------------------------------------------------------
class TPlayerSkillsDlg : public TForm
{
__published:	// Composants gérés par l'EDI
	TPanel *pnlGeneral;
	TStringGrid *gridSkills;
	TPanel *pnlCmd;
	TStringGrid *gridStats;
	TPanel *pnlBio;
	TImage *imgTeamLogo;
	TPanel *pnlPos1;
	TPanel *pnlPos2;
	TComboBox *cbChangePosition2;
	TButton *btnAccept;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormDestroy(TObject *Sender);
	void __fastcall gridSkillsDrawCell(TObject *Sender, int ACol, int ARow, TRect &Rect,
          TGridDrawState State);
private:	// Déclarations utilisateur


    // méthodes internes :
    //--------------------
    void __fastcall zero();
    void __fastcall init();
    void __fastcall deinit();
    void __fastcall formInit();
    void __fastcall formDeinit();
    void __fastcall playerDisplay();
    void __fastcall gridAutoSizeCol( TStringGrid* grid , int col );

    // méthodes get / set des propriétés :
    //------------------------------------
    bool __fastcall getChangePos2();
    AnsiString __fastcall getNewPos2();

    // variables internes :
    //---------------------
    CNLPlayer* _p;


public:		// Déclarations utilisateur

    __property bool changePos2 = { read = getChangePos2 };
    __property AnsiString newPos2    = { read = getNewPos2    };


	// méthodes publiques :
    //---------------------
    bool __fastcall showPlayerSkills( CNLPlayer* p );

    // constructeurs & destructeur :
    //------------------------------
			__fastcall TPlayerSkillsDlg(TComponent* Owner);
    virtual __fastcall ~TPlayerSkillsDlg();
};
//---------------------------------------------------------------------------
extern PACKAGE TPlayerSkillsDlg *PlayerSkillsDlg;
//---------------------------------------------------------------------------
#endif
