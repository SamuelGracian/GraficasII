#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <memory>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Shader.h"
#include "Mesh.h"
#include "Math.cpp"

class GRAPIOpenGL
{
public:
	GRAPIOpenGL(GLint width = 0, GLint height = 0, const char* title = nullptr);
	~GRAPIOpenGL();

	/// <summary>
	/// Initialize GLEW and scene using an existing GLFWwindow.
	/// The application is responsible for creating/destroying the window.
	/// </summary>
	/// <returns>false if initialization failed, true if successful</returns>
	bool InitializeGL(GLFWwindow* window);

	/// <summary>
	/// executes main loop
	/// </summary>
	int Run();

	/// <summary>
	/// Cleans up OpenGL resources (does NOT destroy the window)
	/// </summary>
	void ShutdownGL();

private:
	bool InitGLEW();
	void SetupScene();
	void RenderFrame();

	GLFWwindow* m_window = nullptr;
	int m_bufferWidth = 0;
	int m_bufferHeight = 0;

	//Scene resources
	std::unique_ptr<Shader> m_shader;
	std::unique_ptr<Mesh> m_mesh;

	//Camera params
	Vec3 m_eye = { 0.0f, 0.0f, 0.0f };
	Vec3 m_center = { 0.0f, 0.0f, 0.0f };
	Vec3 m_up = { 0.0f, 0.0f, 0.0f };

	static const char* vertexSrc;
	static const char* fragmentSrc;
};