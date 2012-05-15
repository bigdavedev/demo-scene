#include <windows.h>
#include <gl/gl.h>
#include <glext.h>
#include <wglext.h>

#define FULLSCREEN 1
#define USE_SHADERS
#define NO_VERTEX_SHADER
//#define DEBUG

void WinMainCRTStartup();

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

#pragma data_seg(".shader")
char* frag_shader = \
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

        "if((x*x+y*y)>4)"
            "break;"
        "z.x=x;"
        "z.y=y;"
    "}"
    "gl_FragColor=(i==s.z)?vec4(0.0,0.0,0.0,1.0):vec4(float(i)/s.z,(float(i)/s.z)*0.55,(float(i)/s.z)*0.2,1.0);"
"}";

#pragma data_seg(".globals")
HDC device_context;
//char texture[256];
#if FULLSCREEN
float data[3] = {-0.835f, 0.2321f, 100.0f};
#else
float data[3] = {-0.835f, 0.2321f, 100.0f};
#endif
GLuint p;
//char change = 0;
//unsigned int m_w = 521288629;
//#define MZ ((36969 * (362436069 & 65535) + (362436069 >> 16)) << 16)

//#pragma code_seg(".randint")
//__forceinline unsigned int get_uint()
//{
      //m_w = 36969 * (m_w & 65535) + (m_w >> 16);
      //return (MZ) + m_w;
//}
//#define randf (get_uint() * 2.328306435454494e-10)

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

    p = ((PFNGLCREATEPROGRAMPROC)wglGetProcAddress("glCreateProgram")) ();
    GLuint s = ((PFNGLCREATESHADERPROC)wglGetProcAddress("glCreateShader")) (GL_FRAGMENT_SHADER);
    ((PFNGLSHADERSOURCEPROC)wglGetProcAddress("glShaderSource")) (s, 1, &frag_shader, NULL);
    ((PFNGLCOMPILESHADERPROC)wglGetProcAddress("glCompileShader")) (s);
    ((PFNGLATTACHSHADERPROC)wglGetProcAddress("glAttachShader")) (p, s);

    ((PFNGLLINKPROGRAMARBPROC)wglGetProcAddress("glLinkProgram")) (p);
    ((PFNGLUSEPROGRAMPROC)wglGetProcAddress("glUseProgram")) (p);

    ((PFNGLUNIFORM3FPROC)wglGetProcAddress("glUniform3f"))
        (((PFNGLGETUNIFORMLOCATIONPROC)wglGetProcAddress("glGetUniformLocation"))(p, "s"), data[0], data[1], data[2]);
    ((PFNGLUNIFORM2FPROC)wglGetProcAddress("glUniform2f"))
        (((PFNGLGETUNIFORMLOCATIONPROC)wglGetProcAddress("glGetUniformLocation"))(p, "d"), GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN));

    do
    {
        glRects(-1, -1, 1, 1);
        wglSwapLayerBuffers(device_context, WGL_SWAP_MAIN_PLANE);
    }while(!GetAsyncKeyState(VK_ESCAPE));

    ExitProcess(0);
}
