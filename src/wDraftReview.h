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
__published:	// Composants g�r�s par l'EDI
private:	// D�clarations utilisateur
public:		// D�clarations utilisateur
	__fastcall TDraftReviewDlg(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TDraftReviewDlg *DraftReviewDlg;
//---------------------------------------------------------------------------
#endif
