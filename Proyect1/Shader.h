// Shader.h
#pragma once
#include "RenderResource.h"

enum class ShaderType 
{
    Vertex,
    Pixel
};

class Shader : public RenderResource 
{
public:
    Shader(ShaderType type) : m_type(type) {}
    virtual ~Shader() {}
    ShaderType GetType() const { return m_type; }
protected:
    ShaderType m_type;
};
