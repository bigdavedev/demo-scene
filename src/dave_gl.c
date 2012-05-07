#include <windows.h>
#include <dave_gl.h>

static HDC device_context;
static HGLRC rendering_context;

static const PIXELFORMATDESCRIPTOR pfd =
{
    sizeof(pfd),
    0,
    PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
    PFD_TYPE_RGBA,
    32,
    0,0,0,0,0,0,
    0,
    0,
    0,
    0,0,0,0,
    24,
    8,
    0,
    PFD_MAIN_PLANE,
    0,
    0,0,0
};

static const int gl_attribs[] = 
{
    WGL_CONTEXT_MAJOR_VERSION_ARB, 3,
    WGL_CONTEXT_MINOR_VERSION_ARB, 0,
    WGL_CONTEXT_FLAGS_ARB, 0,
    0
};

void GL_init()
{
    device_context = GetDC(GetActiveWindow());
    SetPixelFormat(device_context, ChoosePixelFormat(device_context, &pfd), &pfd);
    HGLRC temp_rc = wglCreateContext(device_context);
    wglMakeCurrent(device_context, temp_rc);

    rendering_context = ((PFNWGLCREATECONTEXTATTRIBSARBPROC)wglGetProcAddress("wglCreateContextAttribsARB")) (device_context, 0, gl_attribs);
    wglMakeCurrent(NULL, NULL);
    wglDeleteContext(temp_rc);
    wglMakeCurrent(device_context, rendering_context);
}

void GL_kill()
{
    wglMakeCurrent(NULL, NULL);
    wglDeleteContext(rendering_context);
    ReleaseDC(GetActiveWindow(), device_context);
}

HDC GL_get_device()
{
    return device_context;
}
