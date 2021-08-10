//기본 윈도우 헤더 파일 포함
#include <windows.h> 
//#include <windowsx.h> 

// WindowProc 함수 프로토 타입 
LRESULT CALLBACK WindowProc(HWND hWnd,
    UINT message,
    WPARAM wParam,
    LPARAM lParam);

// 모든 Windows 프로그램의 진입 점 
int WINAPI WinMain(HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPSTR lpCmdLine,
    int nCmdShow)
{
    // 함수로 채워진 창 핸들 
    HWND hWnd;
    //이 구조체는 창 클래스에 대한 정보를 보유합니다 
    WNDCLASSEX wc;

    // 사용을 위해 창 클래스를 지 웁니다. 
    ZeroMemory(&wc, sizeof(WNDCLASSEX));

    // 필요한 정보로 구조체를 채 웁니다. 
    wc.cbSize = sizeof(WNDCLASSEX); //구조체 크기를 설정. 
    wc.style = CS_HREDRAW | CS_VREDRAW; //윈도우가 이동하거나 크기가 변할 때 윈도우를 다시 그리겠다는 뜻. 모두 픽셀로 이루어져있기 때문에 다시 그림
    wc.lpfnWndProc = WindowProc;//사용하려는 윈도우 프로시저의 함수명(함수의 메모리 주소)을 설정해서 윈도우 프로시저 함수를 연결시켜준다.
    //그래서 포인터 변수이다.
    wc.hInstance = hInstance;//WinMain의 매개변수 hInstance를 넘겨준다.
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    //IDC_ARROW도 운영체제에 설정되어있다. 가장 기본적인 화살표 커서이다. 이렇게 쓰겠다는 뜻

    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
    //핸들이기 때문에 양의 정수값으로 설정. 
    //배경 색을 흰색으로 설정해준다.

    wc.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_APPLICATION));
    //바탕화면에 생길 아이콘(더블클릭하여 실행하는)을 설정. 운영체제에서 사용하는 기본 아이콘으로 설정
//MAKEINTRESOURCE는 매크로 함수이다.id를 양의 정수로 바꾸어 준다. IDI_APPLICATION는 기본 아이콘.
    
    wc.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_APPLICATION));
    //아이콘의 크기..?가 작게

    //h가 붙어있는 것은 모두 핸들이며 각각을 나누며 os의 자원을 빌려서 쓴다.

    wc.lpszMenuName = nullptr;
    //메뉴에 대한 것을 지정해 줄 수 있다.

    wc.lpszClassName = L"WindowClass1";
    //레지스터 클래스로 해당하는 구조체를 os에 등록한다.등록을 할 때 이름이다.

    // 창 클래스 
    RegisterClassEx(&wc);//구조체를 등록한다.

    //윈도우 생성
    // 창을 만들고 결과를 핸들로 사용 
    hWnd = CreateWindow(
        L"WindowClass1", // 창 클래스의 이름
        L"Our First Windowed Program", // 윈도우 제목 
        WS_OVERLAPPEDWINDOW, // 윈도우 스타일. 윈도우 스타일은 WS_OVERLAPPEDWINDOW가 가장 기본적인 형태 
        300, // 윈도우의 x- 위치 
        300, // 윈도우의 y- 위치 
        500, // 윈도우의 너비 
        400, // 창 높이 
        NULL, // 부모 창 없음, NULL 
        NULL, // 메뉴를 사용하지 않음, NULL 
        hInstance, // 응용 프로그램 핸들 
        NULL); // 여러 창에 사용, NULL 

   /* HWND WINAPI CreateWindow(
        LPCSTR lpClassName,
        LPCSTR lpWindowName,
        DWORD dwStyle,
        int x, int y,
        int nWidth, int nHeight,
        HWND hWndParent,
        HMENU hMenu,
        HINSTANCE hInstance,
        LPVOID lpPAram);*/

// 화면에 창 표시
    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    // 메인 루프에 들어갑니다. 

    //이 구조체는 Windows 이벤트 메시지를 보유합니다. 
    MSG msg;

    // 대기열에서 다음 메시지를 기다렸다가 결과를 'msg'에 저장 
    while (GetMessage(&msg, NULL, 0, 0))
    {
        // 키 입력 메시지를 올바른 형식으로 
        TranslateMessage(&msg);

        // WindowProc에 메시지를 보냅니다. function 
        DispatchMessage(&msg);
    }

    // WM_QUIT 메시지의이 부분을 Windows에 
    return msg.wParam;
}

char buffer[100] = { 0, };
int idx = 0;
// 이것은 프로그램의 기본 메시지 처리기입니다.
LRESULT CALLBACK WindowProc(HWND hWnd,
    UINT message,
    WPARAM wParam,
    LPARAM lParam) 
{
    HDC hdc;
    PAINTSTRUCT ps;
    // 정렬하고 주어진 메시지에 대해 실행할 코드 찾기 
    switch (message)
    {
        // 창이 닫힐 때이 메시지를 읽습니다. 
    case WM_CHAR:
        idx = strlen(buffer);
        buffer[idx] = wParam;
        InvalidateRect(hWnd, NULL, TRUE);
        break;
    case WM_PAINT:
        hdc = BeginPaint(hWnd, &ps);
        //BeginPaint함수는 화면을 그리기 위한 모든 설정값을 ps에 넣어준다. 그리고 핸들을 리턴해줌

        TextOut(hdc, 5, 5, (LPCWSTR)buffer, strlen(buffer));
        EndPaint(hWnd, &ps);
        break;
    case WM_DESTROY:
    {
        // 응용 프로그램을 완전히 닫습니다 
        PostQuitMessage(0);
        return 0;
    } break;
    }

    // switch 문이 
    //반환 하지 않은 모든 메시지를 처리합니다.
    DefWindowProc(hWnd, message, wParam, lParam);
}