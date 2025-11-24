#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

using std::cout;
using std::endl;

const GLint WIDTH = 800, HEIGHT = 600;

int main()
{
	//Setup Glfw
	if (!glfwInit())
	{
		std::cout << "GLFW Failed to initialize" << "\n"
			<< "Error Code: 1" << std::endl;
		glfwTerminate();
		return 1;
	}

	//Setup window properties
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);

	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	//Create window
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Test window", NULL, NULL);

	if (!window)
	{
		cout << "Failed to create window"  << "\n"
			<< "Error code 2" << endl;
		return 2;
	}

	//Get frame buffer size
	int BufferWidth, BufferHeight;

	glfwGetFramebufferSize(window, &BufferWidth, &BufferHeight);

	//set context
	glfwMakeContextCurrent(window);

	//Init GLEW
	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK)
	{
		cout << "Failed to initialize GLEW" << "\n"
			<< "Error Code: 3" << endl;
		glfwDestroyWindow(window);
		glfwTerminate();
		return 3;
	}

	//Viewport
	glViewport(0, 0, BufferWidth, BufferHeight);

	//Main loop
	while (!glfwWindowShouldClose(window))
	{
		//Get and handleuder input
		glfwPollEvents();

		//render
		///Clear Buffers
		glClearColor(1.f, 0.f, 0.f, 255.f);

		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(window);
	}

	//Clean Up
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}