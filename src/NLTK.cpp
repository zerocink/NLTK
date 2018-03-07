//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <tchar.h>
//---------------------------------------------------------------------------
USEFORM("wRosterEditor.cpp", RosterEditorDlg);
USEFORM("wPlayerDebug.cpp", PlayerDebugDlg);
USEFORM("wMain.cpp", MainDlg);
USEFORM("wIconLists.cpp", IconListsDlg);
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
