//---------------------------------------------------------------------------

#ifndef wDraftReviewH
#define wDraftReviewH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
//---------------------------------------------------------------------------
class TDraftReviewDlg : public TForm
{
__published:	// Composants gérés par l'EDI
private:	// Déclarations utilisateur
public:		// Déclarations utilisateur
	__fastcall TDraftReviewDlg(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TDraftReviewDlg *DraftReviewDlg;
//---------------------------------------------------------------------------
#endif
