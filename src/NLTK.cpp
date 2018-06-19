//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <tchar.h>
//---------------------------------------------------------------------------
#include <Vcl.Styles.hpp>
#include <Vcl.Themes.hpp>
USEFORM("wMain.cpp", MainDlg);
USEFORM("wIconLists.cpp", IconListsDlg);
USEFORM("wDraftReview.cpp", DraftReviewDlg);
USEFORM("wAcceptChanges.cpp", AcceptChangesDlg);
USEFORM("wRosterEditor.cpp", RosterEditorDlg);
USEFORM("wPlayerSkills.cpp", PlayerSkillsDlg);
USEFORM("wPlayerDebug.cpp", PlayerDebugDlg);
USEFORM("wMVPReview.cpp", MVPReviewDlg);
USEFORM("wInjuryCleaner.cpp", InjuryCleanerDlg);
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
