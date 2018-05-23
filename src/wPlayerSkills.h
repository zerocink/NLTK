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
__published:	// Composants g�r�s par l'EDI
	TPanel *pnlGeneral;
	TStringGrid *gridSkills;
	TPanel *pnlCmd;
	TStringGrid *gridStats;
	TPanel *pnlBio;
	TImage *imgTeamLogo;
	TPanel *pnlPos1;
	TPanel *pnlPos2;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormDestroy(TObject *Sender);
private:	// D�clarations utilisateur


    // m�thodes internes :
    //--------------------
    void __fastcall zero();
    void __fastcall init();
    void __fastcall deinit();
    void __fastcall formInit();
    void __fastcall formDeinit();
    void __fastcall playerDisplay();
    void __fastcall gridAutoSizeCol( TStringGrid* grid , int col );

    // variables internes :
    //---------------------
    CNLPlayer* _p;


public:		// D�clarations utilisateur


	// m�thodes publiques :
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
