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
    if (!glfwInit())
    {
        cout << "GLFW Failed to initialize\n";
        return 1;
    }

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // open gl mayor version 3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); // open gl minor version 3
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // ask for the core profile of opengl
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // makes context forward compatible

    GLFWwindow* window = glfwCreateWindow(800, 600, "Cube OPENGL", nullptr, nullptr);
    if (!window)
    {
        cout << "Failed to create window\n";
        glfwTerminate();
        return 2;
    }

    glfwMakeContextCurrent(window); // create current context before initiliaze open gl api

    GRAPIOpenGL app(800, 600, "Cube OPENGL");
    if (!app.InitializeGL(window))
    {
        glfwDestroyWindow(window);
        glfwTerminate();
        return -1;
    }

    int exitCode = app.Run();

    glfwDestroyWindow(window);
    glfwTerminate();
    return exitCode;
}

#endif