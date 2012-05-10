#include <dave_stdlib.h>
#include <dave_gl.h>

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

void WinMainCRTStartup()
{
    ExitProcess(WinMain(GetModuleHandle(NULL), NULL, NULL, 0));
}

BOOL keys[256];

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    MSG msg = {0};
    WNDCLASS wc = {0};
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.hbrBackground = (HBRUSH) (COLOR_BACKGROUND);
    wc.lpszClassName = "a";
    if (FAILED(RegisterClass(&wc)))
        return 1;

    HWND window = CreateWindow(wc.lpszClassName, "BigDaveDev Demo-Skeleton (c)2012", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 0, 0, 640, 480, 0, 0, wc.hInstance, NULL);
    if (window == NULL)
        MessageBox(0, "Could not create the window!", 0, 0);

    GL_init();

    glViewport(0, 0, 640, 480);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // Calculate The Aspect Ratio Of The Window
    gluPerspective(45.0f, (GLfloat)640 / (GLfloat)480, 0.1f, 100.0f);
    glShadeModel(GL_SMOOTH);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glClearColor(1.0f, 0.0f, 0.0f, 0.0f);

    while (1)
    {
        if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
        {
            if (msg.message == WM_QUIT)
                break;
            else
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }
        else
        {
            if (keys[VK_ESCAPE])
                break;
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glLoadIdentity();

            SwapBuffers(GL_get_device());
        }
    }

    return 0;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

    switch (message)
    {
        case WM_CLOSE:
            PostQuitMessage(0);
            break;
        case WM_KEYUP:
            keys[wParam] = FALSE;
            break;
        case WM_KEYDOWN:
            keys[wParam] = TRUE;
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;

}
