// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

// Windows Header Files:
#include <windows.h>



// TODO: reference additional headers your program requires here
#include <cassert>
#include <tchar.h>
#include "DesktopHook.h"
#include "dbgprint.h"


extern HINSTANCE g_hinstDll;        // �����Լ��Ľ�����ʹ��
extern DWORD     g_desktopThreadId; //

extern HHOOK     g_hook;         // ������̺����ǵĽ��̹���
extern bool      g_shouldUnLoad; // ������̺����ǵĽ��̹���
extern DWORD     g_hostThreadId;  // ������̺����ǵĽ��̹���

extern WNDPROC   g_oldDefViewProc;      // ���������ʹ�ã�����ListView�ĸ����ھ���Ϣ������
extern HWND      g_hwndDefView;         // ���������ʹ�ã�����ListView�ĸ����ھ��

extern WNDPROC   g_oldLVProc;      // ���������ʹ�ã�����ListView�ľ���Ϣ������
extern HWND      g_hwndLV;         // ���������ʹ�ã�����ListView�ľ��