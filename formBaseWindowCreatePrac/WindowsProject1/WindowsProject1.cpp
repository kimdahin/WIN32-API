// WindowsProject1.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "WindowsProject1.h"

#define MAX_LOADSTRING 100

//자동코드에서 위의 코드와 About 다이얼로그와 관련된 코드들을 모두 빼고 지워줍니다.
//그리고 아래와 같이 작성하면 폼 기반의 윈도우를 생성할 수 있습니다.

INT_PTR CALLBACK    DlgProc(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    //윈도우 프로그램을 실행하자마자 모달형 다이얼로그를 만들어줍니다.
    //부모 윈도우가 없기때문에 3번째인자에는 NULL 또는 0을 줍니다.
    DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DlgProc);
    return 0;
}

//메시지 처리기입니다.
INT_PTR CALLBACK DlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        //다이얼로그 리소스의 속성에서 캡션을 바꾸어서 할 수도 있지만 그것은 중간에 바꿀 수 없다. 그래서 이것을 많이 사용한다.
        SetWindowText(hDlg, "이미지");
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
