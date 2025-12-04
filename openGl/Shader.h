#pragma once

#include <string>
#include <iostream>
#include <GL/glew.h>

class Shader
{
public:
	Shader(const char* vertexSrc, const char* fragmentSrc);
	~Shader();

	void UseShader() const;

	void SetMat4(const std::string& name, const float* matrix) const;

	GLuint ID() const;

private:
	GLuint CompileShader(GLenum type, const char* source) const;

	GLuint programID{ 0 };
};