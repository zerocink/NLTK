//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <tchar.h>
//---------------------------------------------------------------------------
USEFORM("wIconLists.cpp", IconListsDlg);
USEFORM("wRosterEditor.cpp", RosterEditorDlg);
USEFORM("wPlayerDebug.cpp", PlayerDebugDlg);
USEFORM("wMain.cpp", MainDlg);
USEFORM("wAcceptChanges.cpp", AcceptChangesDlg);
//---------------------------------------------------------------------------
int WINAPI _tWinMain(HINSTANCE, HINSTANCE, LPTSTR, int)
{
	try
	{
		Application->Initialize();
		Application->MainFormOnTaskBar = true;
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
