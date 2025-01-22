#include <Windows.h>

int main()
{

    HWND hWnd = GetDesktopWindow();

    HDC screen = GetDC(hWnd);

    RECT rect;
    GetWindowRect(hWnd, &rect);

    while(1) {
        TextOut(screen, (rect.right / 2) - 100, (rect.bottom / 2) - 50, "MUAAAAHAHAHAHAHAHA", 19);
        Sleep(100);
    }

    return 0;
}