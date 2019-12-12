// HexPlotEditor.cpp : Defines the entry point for the application.
//

////////////////////////////////////////////////////////////////////////////////
// include
////////////////////////////////////////////////////////////////////////////////
#include "HexPlotEditor.h"


////////////////////////////////////////////////////////////////////////////////
// function
////////////////////////////////////////////////////////////////////////////////
LRESULT CALLBACK EditProc_Cmd(HWND hEdit, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_KEYDOWN:
	{
		if (VK_RETURN == wParam)
		{
			HWND hParent = GetParent(hEdit);
			SendMessage(hParent, msg, wParam, lParam);
			// SetFocus(GetNextDlgTabItem(hParent, hEdit, FALSE));
			return 0;
		}
	}
	break;


	case WM_CHAR:
		if (VK_RETURN == wParam)
			return 0;
		break;
	}

	return CallWindowProc(oldEditProc, hEdit, msg, wParam, lParam);
}


//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // Store instance handle in our global variable

	return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
BOOL CALLBACK DlgProc_Main(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static char m_edText[256] = "";

    switch (msg)
    {
	case WM_INITDIALOG:
		{
			oldEditProc = (WNDPROC)SetWindowLong(
				GetDlgItem(hDlg, IDC_EDIT_CMD),
				GWL_WNDPROC, (LONG)EditProc_Cmd);
		}
		break;


    case WM_COMMAND:
        {
            //int wmId = LOWORD(wParam);
            //// Parse the menu selections:
            //switch (wmId)
            //{
            //case IDM_ABOUT:
            //    DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
            //    break;

            //case IDM_EXIT:
            //    DestroyWindow(hWnd);
            //    break;
            //default:
            //    return DefWindowProc(hWnd, message, wParam, lParam);
            //}

			if (wParam == IDCANCEL)
				EndDialog(hDlg, 0);
        }

		break;


	case WM_KEYDOWN:
		{
			if (VK_RETURN == wParam)
				GetDlgItemText(hDlg, IDC_EDIT_CMD, (LPWSTR)m_edText, 256);
		}
		break;


    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hDlg, &ps);
            // TODO: Add any drawing code that uses hdc here...
            EndPaint(hDlg, &ps);
        }
        break;


    default:
        return DefWindowProc(hDlg, msg, wParam, lParam);
    }

    return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }

    return (INT_PTR)FALSE;
}

// Main
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{

	// Perform application initialization:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	// show main dialog, proc Main message loop
	DialogBox(hInstance, (LPWSTR)IDD_MAIN, HWND_DESKTOP, (DLGPROC)DlgProc_Main);


	return 0;
}
