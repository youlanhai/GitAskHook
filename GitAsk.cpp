// GitAsk.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "GitAsk.h"
#include <shellapi.h>
#include <Uxtheme.h>
#include <string>

#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

#define MAX_LOADSTRING 100

const int RET_RETRY = 0;
const int RET_ABORT = 1;
HINSTANCE gInstance = 0;

// Global Variables:

static std::wstring loadString(int id)
{
    LPTSTR ret;
    int length = LoadStringW(gInstance, id, (LPTSTR)&ret, 0);
    return std::wstring(ret, length);
}


// Forward declarations of functions included in this code module:
INT_PTR CALLBACK    OnDlgProc(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    gInstance = hInstance;
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    int ret = (int)DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_ABOUTBOX), nullptr, OnDlgProc, 0);
    if (ret == IDOK)
    {
        return RET_RETRY;
    }
    
    std::wstring abortContent = loadString(IDS_ABORT_HINT);
    std::wstring abortTitle = loadString(IDS_ABORT_TITLE);
    ret = MessageBox(nullptr, abortContent.c_str(), abortTitle.c_str(), MB_OKCANCEL | MB_ICONWARNING);
    return ret == IDOK ? RET_ABORT : RET_RETRY;
}

// Message handler for about box.
INT_PTR CALLBACK OnDlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
    {
        //SetWindowTheme(hDlg, TEXT("Explorer"), TEXT(""));
        LPCWSTR szCmdLines = GetCommandLineW();

        int nNumArgs = 0;
        LPWSTR *szArgList = CommandLineToArgvW(szCmdLines, &nNumArgs);
        
        if (szArgList != nullptr && nNumArgs > 1)
        {
            LPCTSTR szMessage = szArgList[1];
            SetDlgItemText(hDlg, IDC_CONTENT, szMessage);
        }
        else
        {
            std::wstring message = loadString(IDS_UNKNOWN);
            SetDlgItemText(hDlg, IDC_CONTENT, message.c_str());
        }

        if (szArgList != nullptr)
        {
            LocalFree(szArgList);
        }
        return (INT_PTR)TRUE;
    }

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        else if (LOWORD(wParam) == IDC_UNLINK_HELP)
        {
            std::wstring url = loadString(IDS_UNLINK_HELP);
            ShellExecute(nullptr, TEXT("open"), url.c_str(), nullptr, nullptr, SW_SHOWNORMAL);
        }
        break;
    }
    return (INT_PTR)FALSE;
}
