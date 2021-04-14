#include <windows.h>
#include <string>
#include <sstream>
#include "Window.h"


LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

int CALLBACK WINAPI WinMain
(
	_In_ HINSTANCE hInstance,
	_In_opt_  HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine,
	_In_ int nShowCmd
)
{
	Window wnd(800, 300, "é©çÏÉGÉìÉWÉì1çÜ");

	
	MSG msg;
	BOOL gResult;
	msg.message = NULL;

	while (msg.message != WM_QUIT) {
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else {

		}
	}
	
	return 0;
}



	

	


