#include "DesktopHook.h"

#include <iostream>

int main()
{
    HWND desktopLVHwnd = GetDesktopDefViewHwnd();
    if (0 == desktopLVHwnd)
    {
        std::cerr << "error: GetDesktopLVHwnd";
        return 1;
    }

    BOOL ret = SetDesktopHook(GetWindowThreadProcessId(desktopLVHwnd, NULL));
    if (ret != TRUE)
    {
        std::cerr << "error: SetDesktopHook\n";
    }

    std::cout << "��������˳�...";
    getchar();

    // �˳�ʱ������ȡ��Hook�����������ģ�
    SetDesktopHook(0);
}