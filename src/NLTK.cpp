//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <tchar.h>
//---------------------------------------------------------------------------
#include <Vcl.Styles.hpp>
#include <Vcl.Themes.hpp>
USEFORM("wDraftReview.cpp", DraftReviewDlg);
USEFORM("wAcceptChanges.cpp", AcceptChangesDlg);
USEFORM("wIconLists.cpp", IconListsDlg);
USEFORM("wRosterEditor.cpp", RosterEditorDlg);
USEFORM("wPlayerDebug.cpp", PlayerDebugDlg);
USEFORM("wMain.cpp", MainDlg);
USEFORM("wMVPReview.cpp", MVPReviewDlg);
//---------------------------------------------------------------------------
int WINAPI _tWinMain(HINSTANCE, HINSTANCE, LPTSTR, int)
{
	try
	{
		Application->Initialize();
		Application->MainFormOnTaskBar = true;
		TStyleManager::TrySetStyle("Windows10 SlateGray");
		Application->CreateForm(__classid(TMainDlg), &MainDlg);
		Application->CreateForm(__classid(TIconListsDlg), &IconListsDlg);
		Application->Run();
	}
	catch (Exception &exception)
	{
		Application->ShowException(&exception);
	}
	catch (...)
	{
		try
		{
			throw Exception("");
		}
		catch (Exception &exception)
		{
			Application->ShowException(&exception);
		}
	}
	return 0;
}
//---------------------------------------------------------------------------
