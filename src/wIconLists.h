//---------------------------------------------------------------------------

#ifndef wIconListsH
#define wIconListsH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <System.ImageList.hpp>
#include <Vcl.ImgList.hpp>
//---------------------------------------------------------------------------
class TIconListsDlg : public TForm
{
__published:	// Composants g�r�s par l'EDI
	TImageList *ilIconSet48x48_blue;
	TImageList *ilIconSet48x48_red;
	TImageList *ilIconSet48x48_green;
	TImageList *ilIconSet48x48_yellow;
	TImageList *ilLogos187x49;
private:	// D�clarations utilisateur
public:		// D�clarations utilisateur
	__fastcall TIconListsDlg(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TIconListsDlg *IconListsDlg;
//---------------------------------------------------------------------------
#endif
