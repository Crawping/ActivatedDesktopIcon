// DesktopHook.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"

LRESULT WINAPI GetMsgProc(int code, WPARAM wParam, LPARAM lParam);
LRESULT APIENTRY DesktopDefViewSubclassProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

BOOL SetDesktopHook(DWORD threadId)
{
    // ���������DesktopInjecter������ִ��
    BOOL bOk = FALSE;

    if (0 != threadId)
    {
        assert(g_hook == NULL);

        g_desktopThreadId = threadId;
        g_hostThreadId = GetCurrentThreadId();

        g_hook = ::SetWindowsHookEx(WH_GETMESSAGE, GetMsgProc, g_hinstDll, threadId);

        bOk = (NULL != g_hook);

        if (bOk)
        {
            // ��������̷�һ����Ϣ��ʹ֮�ܹ�����GetMsgProc
            bOk = PostThreadMessage(threadId, WM_NULL, 0, 0);
            DbgPrint(_T("SetDesktopHook: Hook successfully"));
        }
    }
    else
    {
        assert(g_hook);

        // ��� g_hookΪNULL����ʾ����Ҫȡ��hook

        // ������ָ� DefView�Ĵ��ڴ�����
        g_shouldUnLoad = true;
        ::PostThreadMessage(g_desktopThreadId, WM_NULL, 0, 0);

        MSG msg;
        ::GetMessage(&msg, NULL, 0, 0);

        // �յ���Ϣ��˵�� DefView �Ĵ��ڴ������Ѿ��ָ�
        bOk = UnhookWindowsHookEx(g_hook);
        g_hook = NULL;
        DbgPrint(_T("SetDesktopHook: unHook successfully"));
    }

    return bOk;
}

HWND GetDesktopDefViewHwnd()
{
    return GetTopWindow(FindWindowW(L"Progman", NULL));
}

LRESULT WINAPI GetMsgProc(int code, WPARAM wParam, LPARAM lParam)
{
    // ��������������������ִ��

    static bool bFirstTime = true;
    if (bFirstTime)
    {
        DbgPrint(_T("DeskHook: Into HookProc"));
        bFirstTime = false;

        // �������ʼ�������Լ��Ķ���
        // �������洰�ڲ��������໯
        g_hwndDefView = GetDesktopDefViewHwnd();

        assert(g_hwndDefView);

        if (g_hwndDefView != NULL)
        {
            g_oldProc = reinterpret_cast<WNDPROC>(::SetWindowLongPtr(g_hwndDefView, GWL_WNDPROC, (long)(DesktopDefViewSubclassProc)));

            assert(g_oldProc);
            DbgPrint(g_oldProc ? _T("DeskHook: SubClass Successfully") : _T("DeskHook: SubClass Failed"));

        }
    }
    else if (g_shouldUnLoad)
    {
        g_shouldUnLoad = false;
        if (g_oldProc)
        {
            ::SetWindowLongPtr(g_hwndDefView, GWL_WNDPROC, (long)(g_oldProc));
            ::PostThreadMessage(g_hostThreadId, WM_NULL, 0, 0);
        }
    }

    return CallNextHookEx(g_hook, code, wParam, lParam);
}

