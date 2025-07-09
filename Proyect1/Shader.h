// Shader.h
#pragma once
#include "RenderResource.h"

enum class ShaderType
{
	Vertex = 0,
	Pixel = 1
};

class Shader : public RenderResource
{
public:
	Shader(ShaderType type) : m_type(type) {}
	virtual ~Shader() {}

	ShaderType GetType() const { return m_type; }

protected :
	ShaderType m_type;
};