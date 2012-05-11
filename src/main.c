#pragma data_seg(".name1")
#pragma code_seg(".name2")

#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include <glext.h>
#include <wglext.h>

//int _fltused = 0;

#define USE_SHADERS
#define NO_VERTEX_SHADER

#define SCREEN_X 640
#define SCREEN_Y 480

//#define DEBUG

void WinMainCRTStartup();
void setup_shaders(void);

#pragma data_seg(".pfd")
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
#pragma data_seg(".shader")
char* frag_shader = \
"vec2 d = vec2(0.7,0.0);"
"uniform float s;"
"void main()"
"{"
    "vec2 c=vec2(1.3*((gl_FragCoord.x/640.0)-0.5)*s-d.x, ((gl_FragCoord.y/480.0)-0.5)*s-d.y);"
    "vec2 z=c;"
    "int i;"
    "for(i=0;i<70;i++)"
    "{"
        "float x=(z.x*z.x-z.y*z.y)+c.x;"
        "float y=(z.y*z.x+z.x*z.y)+c.y;"

        "if((x*x+y*y)>4.0)"
            "break;"
        "z.x=x;"
        "z.y=y;"
    "}"
	"gl_FragColor=vec4((i==20?0.0:i)/100.0,0.0,0.0,1.0);"
"}";
#endif

#pragma data_seg(".globals")
HDC device_context;
char texture[256*3];
float scale = 5.0f;
GLuint p;

#pragma code_seg(".main")
void WinMainCRTStartup()
{
    device_context = GetDC(CreateWindow("static", 0, WS_POPUP|WS_VISIBLE, 0, 0, SCREEN_X, SCREEN_Y, 0, 0, 0, 0));
    SetPixelFormat(device_context, ChoosePixelFormat(device_context, &pfd), &pfd);
    wglMakeCurrent(device_context, wglCreateContext(device_context));

    for(int i = 0; i < 256*3; i++)
    {
        texture[i] = 0;
        texture[++i] = 1;
        texture[++i] = 2;
    }

    setup_shaders();

    do
    {
        //((PFNGLUSEPROGRAMPROC)wglGetProcAddress("glUseProgram")) (p);
        if(GetAsyncKeyState(VK_F1))
            scale += 0.005f;
        if(GetAsyncKeyState(VK_F2))
            scale -= 0.005f;
        ((PFNGLUNIFORM1FPROC)wglGetProcAddress("glUniform1f"))
            (((PFNGLGETUNIFORMLOCATIONPROC)wglGetProcAddress("glGetUniformLocation"))(p, "s"), scale);
        glRects(-1, -1, 1, 1);
        wglSwapLayerBuffers(device_context, WGL_SWAP_MAIN_PLANE);
    }while(!GetAsyncKeyState(VK_ESCAPE));

    ExitProcess(0);
}

#pragma code_seg(".setup")
#ifdef USE_SHADERS
void setup_shaders(void)
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
