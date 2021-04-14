#include "Window.h"


Window::WindowClass Window::WindowClass::wndClass;

Window::WindowClass::WindowClass() noexcept :
	hInst(GetModuleHandle(nullptr)) {
	WNDCLASSEX wcex;

	//ウィンドウクラスを登録
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = 0;
	wcex.lpfnWndProc = HandleMsgSetup;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = GetInstance();
	wcex.hIcon = (HICON)LoadImage(
		NULL, "eagle.ico", IMAGE_ICON,
		0, 0, LR_SHARED | LR_LOADFROMFILE
	);
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_BACKGROUND + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = GetName();
	wcex.hIconSm = NULL;
	if (!RegisterClassEx(&wcex)) {
		MessageBox(NULL, "RegisterClassEx関数　失敗、", "", MB_OK);
		
	}
}

Window::WindowClass::~WindowClass() {
	UnregisterClass(wndClassName, GetInstance());
}

const char* Window::WindowClass::GetName() noexcept {
	return wndClassName;
}

HINSTANCE Window::WindowClass::GetInstance() noexcept {
	return wndClass.hInst;
}

Window::Window(int width, int height, const char* name) noexcept {
	RECT wr;
	wr.left = 100;
	wr.right = width + wr.left;
	wr.top = 100;
	wr.bottom = height + wr.top;
	AdjustWindowRect(&wr, WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU, FALSE);

	hWnd = CreateWindowEx(
		WS_EX_ACCEPTFILES | WS_EX_CONTROLPARENT,
		WindowClass::GetName(),
		name,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,CW_USEDEFAULT,
		wr.right - wr.left,
		wr.bottom - wr.top,
		NULL, NULL, WindowClass::GetInstance(), this
	);
	if (!hWnd) {
		MessageBox(NULL, "CreateWindow関数　失敗、", "", MB_OK);
		
	}

	//ウィンドウ表示
	ShowWindow(hWnd, SW_SHOWDEFAULT);
	//UpdateWindow(hWnd);
}
Window::~Window() {
	DestroyWindow(hWnd);
}

LRESULT WINAPI Window::HandleMsgSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	if (msg == WM_NCCREATE) {
		const CREATESTRUCTW* const pCreate = reinterpret_cast<CREATESTRUCTW*>(lParam);
		Window* const pWnd = static_cast<Window*>(pCreate->lpCreateParams);

		SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWnd));

		SetWindowLongPtr(hWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(&Window::HandleMsgThunk));

		return pWnd->HandleMsg(hWnd, msg, wParam, lParam);
	}


}

LRESULT WINAPI Window::HandleMsgThunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	Window* const pWnd = reinterpret_cast<Window*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));

		return pWnd->HandleMsg(hWnd, msg, wParam, lParam);
}

LRESULT Window::HandleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept {
	switch (msg) {
	case WM_CLOSE:
		PostQuitMessage(0);
		return 0;
	case WM_KEYDOWN:
		if (wParam == 'E') {
			PostQuitMessage(0);
			}
		
	}
	

	return DefWindowProc(hWnd, msg, wParam, lParam);
}