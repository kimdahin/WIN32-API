#include <windows.h>
#include <tchar.h>

LRESULT CALLBACK WndProc(HWND hWnd,
	UINT message,
	WPARAM wParam,
	LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{
	WNDCLASSEX ws;

	ws.cbSize = sizeof(WNDCLASSEX);
	ws.style = CS_HREDRAW | CS_VREDRAW;
	ws.lpfnWndProc = WndProc;
	ws.cbClsExtra = 0;
	ws.cbWndExtra = 0;
	ws.hInstance = hInstance;
	ws.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
	ws.hCursor = LoadCursor(NULL, IDC_ARROW);
	ws.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	ws.lpszMenuName = NULL;
	ws.lpszClassName = "WindowClass";
	ws.hIconSm = LoadIcon(hInstance, IDI_APPLICATION);
	
	RegisterClassEx(&ws);

	HWND hWnd = CreateWindow(
		"WindowClass",
		"first window program",
		WS_OVERLAPPEDWINDOW,
		300,
		300,
		500,
		400,
		NULL,
		NULL,
		hInstance,
		NULL
	);

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	MSG msg;

	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}

LRESULT CALLBACK WndProc(HWND hWnd,
	UINT message,
	WPARAM wParam,
	LPARAM lParam) {

	HDC hdc;
	PAINTSTRUCT ps;

	switch (message) {
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);

		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

