#pragma data_seg(".name1")
#pragma code_seg(".name2")

#include <windows.h>
#include <gl/gl.h>
#include <glext.h>
#include <wglext.h>

//int _fltused = 0;

#define FULLSCREEN 1
#define USE_SHADERS
#define NO_VERTEX_SHADER

//#define DEBUG

void WinMainCRTStartup();
void setup_shaders(void);

#pragma data_seg(".pfd")
PIXELFORMATDESCRIPTOR pfd =
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
#pragma data_seg(".shader")
char const* frag_shader = \
"uniform vec3 s;"
"uniform vec2 d;"
"void main()"
"{"
    "vec2 z=vec2(3.0*((gl_FragCoord.x/d.x)-0.5),2.0*((gl_FragCoord.y/d.y)-0.5));"
    "int i;"
    "for(i=0;i<int(s.z);i++)"
    "{"
        "float x=(z.x*z.x-z.y*z.y)+s.x;"
        "float y=(z.y*z.x+z.x*z.y)+s.y;"

        "if((x*x+y*y)>s.z)"
            "break;"
        "z.x=x;"
        "z.y=y;"
    "}"
    "gl_FragColor=(i==s.z)?vec4(0.0,0.0,0.0,1.0):vec4(float(i)/s.z,0.15,0.3,1.0);"
"}";
#endif

#pragma data_seg(".globals")
HDC device_context;
//char texture[256];
#if FULLSCREEN
float data[3] = {-0.835f, 0.2321f, 100.0f};
#else
float data[3] = {0.5f, 0.05f, 50.0f};
#endif
GLuint p;

#pragma code_seg(".main")
void WinMainCRTStartup()
{
#if FULLSCREEN
    device_context = GetDC(CreateWindow("edit", 0, WS_POPUP|WS_VISIBLE|WS_MAXIMIZE, 0, 0, 0, 0, 0, 0, 0, 0));
    ShowCursor(FALSE);
#else
    device_context = GetDC(CreateWindow("static", "Julia fractal in 1k - BigDaveDev(c)2012", WS_OVERLAPPED | WS_CAPTION | WS_THICKFRAME | WS_POPUP| WS_VISIBLE, 0, 0, 800, 600, 0, 0, 0, 0));
#endif
    SetPixelFormat(device_context, ChoosePixelFormat(device_context, &pfd), &pfd);
    wglMakeCurrent(device_context, wglCreateContext(device_context));

    setup_shaders();
    ((PFNGLUNIFORM3FPROC)wglGetProcAddress("glUniform3f"))
        (((PFNGLGETUNIFORMLOCATIONPROC)wglGetProcAddress("glGetUniformLocation"))(p, "s"), data[0], data[1], data[2]);
    ((PFNGLUNIFORM2FPROC)wglGetProcAddress("glUniform2f"))
        (((PFNGLGETUNIFORMLOCATIONPROC)wglGetProcAddress("glGetUniformLocation"))(p, "d"), GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN));

    do
    {
        //data[0] += 0.0003f;
        //data[1] -= 0.0003f;
        //((PFNGLUNIFORM3FPROC)wglGetProcAddress("glUniform3f"))
            //(((PFNGLGETUNIFORMLOCATIONPROC)wglGetProcAddress("glGetUniformLocation"))(p, "s"), data[0], data[1], data[2]); 
        glRects(-1, -1, 1, 1);
        wglSwapLayerBuffers(device_context, WGL_SWAP_MAIN_PLANE);
    }while(!GetAsyncKeyState(VK_ESCAPE));

    ExitProcess(0);
}

#pragma code_seg(".setup")
#ifdef USE_SHADERS
__forceinline void setup_shaders(void)
{
#ifdef DEBUG
    int		result;
    char    info[1536];
#endif

    GLuint s;
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
    ((PFNGLGETINFOLOGARBPROC)wglGetProcAddress("glGetInfoLogARB"))( s,   1024, NULL, (char *)info );
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
