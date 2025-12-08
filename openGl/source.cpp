#define OPENGL

#include <iostream>
#include <vector>
#include <cmath>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "GRAPIOpenGL.h"

using std::cout;
using std::endl;

//const GLint WIDTH = 800, HEIGHT = 600;

//const char* vertexSrc = R"(
//#version 330 core
//layout(location = 0) in vec3 aPos;
//layout(location = 1) in vec3 aColor;
//
//uniform mat4 uMVP;
//
//out vec3 vColor;
//
//void main()
//{
//    vColor = aColor;
//    gl_Position = uMVP * vec4(aPos, 1.0);
//}
//)";
//
//const char* fragmentSrc = R"(
//#version 330 core
//in vec3 vColor;
//out vec4 FragColor;
//void main()
//{
//    FragColor = vec4(vColor, 1.0);
//}
//)";
#if defined (OPENGL)
int main()
{
    GRAPIOpenGL app(800, 600, "Cube OPENGL");
    if (!app.InitializeGL())
        return -1;

    int exitCode = app.Run();
    app.ShutdownGL();
    return exitCode;
}

#endif