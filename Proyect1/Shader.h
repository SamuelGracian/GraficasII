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

    virtual void* GetShaderPointer() const = 0;

protected:
    ShaderType m_type;
};

class Dx11PixelShader : public Shader
{
public:
    Dx11PixelShader(ID3D11PixelShader* shader)
        : Shader(ShaderType::Pixel), m_shader(shader) {}

    ~Dx11PixelShader() { if (m_shader) m_shader->Release(); }
    void* GetShaderPointer() const override { return m_shader; }

private:
    ID3D11PixelShader* m_shader;
};