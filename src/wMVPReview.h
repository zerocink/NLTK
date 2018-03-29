//---------------------------------------------------------------------------

#ifndef wMVPReviewH
#define wMVPReviewH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
//---------------------------------------------------------------------------
class TMVPReviewDlg : public TForm
{
__published:	// Composants gérés par l'EDI
private:	// Déclarations utilisateur
public:		// Déclarations utilisateur
	__fastcall TMVPReviewDlg(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TMVPReviewDlg *MVPReviewDlg;
//---------------------------------------------------------------------------
#endif
