#pragma once
#include <string>
#include <vector>
#include <iostream>

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
	/// Initialize GLFW, GLEW, and scene,
	/// </summary>
	/// <returns>
	/// false if initialization failed, true if successful
	/// </returns>
	bool InitializeGL();

	/// <summary>
	/// executes main loop
	/// </summary>
	/// <returns>
	/// returns 0 in case of success, error code otherwise
	/// </returns>
	int Run();

	/// <summary>
	/// Cleans up and shuts down OpenGL
	/// </summary>
	void ShutdownGL();

private:

	bool InitGLFW();

	bool InitGLEW();

	void SetupScene();

	void RenderFrame();

	GLint m_width;

	GLint m_height;

	std::string m_title;

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