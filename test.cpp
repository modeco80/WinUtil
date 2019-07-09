#include <winutil.hpp>

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch(msg)
    {
        case WM_CLOSE:
            DestroyWindow(hwnd);
        break;
        case WM_DESTROY:
            PostQuitMessage(0);
        break;
        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

winutil::Window window;

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrev, LPSTR CmdLine, int cmdShow) {
	window = winutil::Window(WndProc, "winutil test", 640, 480, "winutil_test", hInst); // setup the object
	
	// create the actual window & begin processing messages
	window.Initalize();
	window.BeginMessageLoop();
	return 0;
}