

#include <iostream>
#include <vector>
#include <cmath>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Shader.h"
#include "Mesh.h"
#include "Math.cpp"

using std::cout;
using std::endl;

const GLint WIDTH = 800, HEIGHT = 600;

///Main test
//int main()
//{
//	//Setup Glfw
//	if (!glfwInit())
//	{
//		std::cout << "GLFW Failed to initialize" << "\n"
//			<< "Error Code: 1" << std::endl;
//		glfwTerminate();
//		return 1;
//	}
//
//	//Setup window properties
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//
//	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//
//	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
//
//	//Create window
//	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Test window", NULL, NULL);
//
//	if (!window)
//	{
//		cout << "Failed to create window"  << "\n"
//			<< "Error code 2" << endl;
//		return 2;
//	}
//
//	//Get frame buffer size
//	int BufferWidth, BufferHeight;
//
//	glfwGetFramebufferSize(window, &BufferWidth, &BufferHeight);
//
//	//set context
//	glfwMakeContextCurrent(window);
//
//	//Init GLEW
//	glewExperimental = GL_TRUE;
//
//	if (glewInit() != GLEW_OK)
//	{
//		cout << "Failed to initialize GLEW" << "\n"
//			<< "Error Code: 3" << endl;
//		glfwDestroyWindow(window);
//		glfwTerminate();
//		return 3;
//	}
//
//	//Viewport
//	glViewport(0, 0, BufferWidth, BufferHeight);
//
//	//Main loop
//	while (!glfwWindowShouldClose(window))
//	{
//		//Get and handleuder input
//		glfwPollEvents();
//
//		//render
//		///Clear Buffers
//		glClearColor(1.f, 0.f, 0.f, 255.f);
//
//		glClear(GL_COLOR_BUFFER_BIT);
//
//		glfwSwapBuffers(window);
//	}
//
//	//Clean Up
//	glfwDestroyWindow(window);
//	glfwTerminate();
//	return 0;
//}


const char* vertexSrc = R"(
#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aColor;

uniform mat4 uMVP;

out vec3 vColor;

void main()
{
    vColor = aColor;
    gl_Position = uMVP * vec4(aPos, 1.0);
}
)";

const char* fragmentSrc = R"(
#version 330 core
in vec3 vColor;
out vec4 FragColor;
void main()
{
    FragColor = vec4(vColor, 1.0);
}
)";

int main()
{
    if (!glfwInit())
    {
        cout << "GLFW Failed to initialize\n";
        glfwTerminate();
        return 1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Cube - OOP pipeline (no GLM)", NULL, NULL);
    if (!window)
    {
        cout << "Failed to create window\n";
        glfwTerminate();
        return 2;
    }

    int BufferWidth, BufferHeight;
    glfwGetFramebufferSize(window, &BufferWidth, &BufferHeight);
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
    {
        cout << "Failed to initialize GLEW\n";
        glfwDestroyWindow(window);
        glfwTerminate();
        return 3;
    }

    glViewport(0, 0, BufferWidth, BufferHeight);

    // Cube: pos.xyz, color.rgb
    std::vector<float> vertices = {
        -0.5f,-0.5f,-0.5f,  1,0,0,
         0.5f,-0.5f,-0.5f,  0,1,0,
         0.5f, 0.5f,-0.5f,  0,0,1,
        -0.5f, 0.5f,-0.5f,  1,1,0,
        -0.5f,-0.5f, 0.5f,  1,0,1,
         0.5f,-0.5f, 0.5f,  0,1,1,
         0.5f, 0.5f, 0.5f,  1,1,1,
        -0.5f, 0.5f, 0.5f,  0.2f,0.8f,0.2f
    };

    std::vector<unsigned int> indices = {
        0,1,2, 2,3,0,
        4,5,6, 6,7,4,
        4,0,3, 3,7,4,
        1,5,6, 6,2,1,
        4,5,1, 1,0,4,
        3,2,6, 6,7,3
    };

    Shader shader(vertexSrc, fragmentSrc);
    Mesh cube(vertices, indices);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    // camera params
    Vec3 eye = { 2.0f, 2.0f, 2.0f };
    Vec3 center = { 0.0f, 0.0f, 0.0f };
    Vec3 up = { 0.0f, 1.0f, 0.0f };

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        glClearColor(0.12f, 0.14f, 0.18f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        float t = (float)glfwGetTime();
        Mat4 model = Rotate(t * 0.5f, { 0.5f, 1.0f, 0.0f });
        Mat4 view = LookAt(eye, center, up);
        Mat4 proj = Perspective(45.0f * 3.14159265f / 180.0f, (float)BufferWidth / (float)BufferHeight, 0.1f, 100.0f);

        Mat4 mv = Multiply(view, model);          // view * model
        Mat4 mvp = Multiply(proj, mv);            // proj * (view * model)

        shader.UseShader();
        shader.SetMat4("uMVP", mvp.data());

        cube.Draw();

        glfwSwapBuffers(window);
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
