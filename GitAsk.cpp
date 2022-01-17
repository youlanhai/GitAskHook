// GitAsk.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "GitAsk.h"
#include <shellapi.h>
#include <Uxtheme.h>

#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

#define MAX_LOADSTRING 100

const int RET_RETRY = 1;
const int RET_ABORT = 0;

// Global Variables:

// Forward declarations of functions included in this code module:
INT_PTR CALLBACK    OnDlgProc(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    int ret = (int)DialogBox(hInstance, MAKEINTRESOURCE(IDD_ABOUTBOX), nullptr, OnDlgProc);
    if (ret == TRUE)
    {
        return RET_RETRY;
    }
    
    ret = MessageBox(nullptr, TEXT("强行终止，会导致工作目录文件损坏。请先备份文件后，再点击确定！"), TEXT("确定要终止吗?"), MB_OKCANCEL | MB_ICONWARNING);
    return ret == TRUE ? RET_ABORT : RET_RETRY;
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

        LPCWSTR szMessage = nullptr;
        int nNumArgs = 0;
        LPWSTR *szArgList = CommandLineToArgvW(szCmdLines, &nNumArgs);
        if (szArgList != nullptr && nNumArgs > 1)
        {
            szMessage = szArgList[1];
        }
        else
        {
            szMessage = TEXT("未知错误");
        }
        //HWND hText = GetDlgItem(hDlg, IDC_CONTENT);
        //SetWindowText(hText, szMessage);
        SetDlgItemText(hDlg, IDC_CONTENT, szMessage);

        if (szArgList != nullptr)
        {
            //LocalFree(szArgList);
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
            ShellExecute(nullptr, TEXT("open"), TEXT(""), nullptr, nullptr, SW_SHOWNORMAL);
        }
        break;
    }
    return (INT_PTR)FALSE;
}
