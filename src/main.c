#pragma data_seg(".name1")
#pragma code_seg(".name2")

#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include <glext.h>
#include <wglext.h>

//int _fltused = 0;

#define USE_SHADERS

#define SCREEN_X 640
#define SCREEN_Y 480

void WinMainCRTStartup();
void setup_shaders(void);

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

#ifdef USE_SHADERS
#ifndef NO_VERTEX_SHADER
static char const* vertex_shader = \
"void main(void)"
"{"
    "gl_Position=gl_Vertex;"
"}";
#endif // NO_VERTEX_SHADER
static char const* frag_shader = \
"void main()"
"{"
	"gl_FragColor=vec4(0.0f,0.3f,0.0f,1.0f);"
"}";
#endif

//GLfloat light_pos[]= { 5.0f, 10.0f, -20.0f, 1.0f };

static HDC device_context;

void WinMainCRTStartup()
{
    device_context = GetDC(CreateWindow("static", 0, WS_POPUP|WS_VISIBLE, 0, 0, SCREEN_X, SCREEN_Y, 0, 0, 0, 0));
    SetPixelFormat(device_context, ChoosePixelFormat(device_context, &pfd), &pfd);
    wglMakeCurrent(device_context, wglCreateContext(device_context));

#ifdef USE_SHADERS
    setup_shaders();
#else
    glClearColor(0.0f, 0.0f, 0.3f, 0.0f);
#endif

    while(!GetAsyncKeyState(VK_ESCAPE))
    {
#ifdef USE_SHADERS
        glRects(-1, -1, 1, 1);
#else
        glClear(GL_COLOR_BUFFER_BIT);
#endif
        wglSwapLayerBuffers(device_context, WGL_SWAP_MAIN_PLANE);
    }

    ExitProcess(0);
}

#ifdef USE_SHADERS
void setup_shaders(void)
{
#ifdef DEBUG
    int		result;
    char    info[1536];
#endif

    GLuint p, s;
    p = ((PFNGLCREATEPROGRAMPROC)wglGetProcAddress("glCreateProgram")) ();

#ifndef NO_VERTEX_SHADER
    s = ((PFNGLCREATESHADERPROC) (wglGetProcAddress("glCreateShader"))) (GL_VERTEX_SHADER);
    ((PFNGLSHADERSOURCEPROC)wglGetProcAddress("glShaderSource")) (s, 1, &vertex_shader, NULL);
    ((PFNGLCOMPILESHADERPROC)wglGetProcAddress("glCompileShader")) (s);
    ((PFNGLATTACHSHADERPROC)wglGetProcAddress("glAttachShader")) (p, s);
#ifdef DEBUG
    ((PFNGLGETOBJECTPARAMETERIVARBPROC)wglGetProcAddress("glGetObjectParameterivARB"))( s,   GL_OBJECT_COMPILE_STATUS_ARB, &result );
    ((PFNGLGETINFOLOGARBPROC)wglGetProcAddress("glGetInfoLogARB"))( s,   1024, NULL, (char *)info );
    if(!result)
        MessageBox(0, info, 0, 0);
#endif // DEBUG
#endif // NO_VERTEX_SHADER

    s = ((PFNGLCREATESHADERPROC)wglGetProcAddress("glCreateShader")) (GL_FRAGMENT_SHADER);
    ((PFNGLSHADERSOURCEPROC)wglGetProcAddress("glShaderSource")) (s, 1, &frag_shader, NULL);
    ((PFNGLCOMPILESHADERPROC)wglGetProcAddress("glCompileShader")) (s);
    ((PFNGLATTACHSHADERPROC)wglGetProcAddress("glAttachShader")) (p, s);
#ifdef DEBUG
    ((PFNGLGETOBJECTPARAMETERIVARBPROC)wglGetProcAddress("glGetObjectParameterivARB"))( s,   GL_OBJECT_COMPILE_STATUS_ARB, &result );
        MessageBox(0, "glGetObjectParameterivARB", 0, 0); 
    ((PFNGLGETINFOLOGARBPROC)wglGetProcAddress("glGetInfoLogARB"))( s,   1024, NULL, (char *)info );
        MessageBox(0, "glGetInfoLogARB", 0, 0);
    if(!result)
        MessageBox(0, info, 0, 0);
#endif

    ((PFNGLLINKPROGRAMARBPROC)wglGetProcAddress("glLinkProgramARB")) (p);
    ((PFNGLUSEPROGRAMPROC)wglGetProcAddress("glUseProgram")) (p);
#ifdef DEBUG
    ((PFNGLGETOBJECTPARAMETERIVARBPROC)wglGetProcAddress("glGetObjectParameterivARB"))( p,   GL_OBJECT_LINK_STATUS_ARB, &result );
    ((PFNGLGETINFOLOGARBPROC)wglGetProcAddress("glGetInfoLogARB"))( p,   1024, NULL, (char *)info );
    if(!result)
        MessageBox(0, info, 0, 0);
#endif
}
#endif
