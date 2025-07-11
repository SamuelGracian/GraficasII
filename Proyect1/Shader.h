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
    Shader(ShaderType type)
		: m_type(type)
    {}

    virtual ~Shader() = default;

    virtual ShaderType GetType() const = 0;

    virtual void* GetShaderPointer() const = 0;

protected:
    ShaderType m_type;
};

class Dx11PixelShader : public Shader
{
public:
    Dx11PixelShader(ID3D11PixelShader* shader)
        : Shader(ShaderType::Pixel), m_shader(shader) {}

    ~Dx11PixelShader() { CleanUpResources(); }

	ShaderType GetType() const override { return m_type; }

    void* GetShaderPointer() const override { return m_shader; }

protected:

    void CleanUpResources() override
    {
        if (m_shader) {
            m_shader->Release();
            m_shader = nullptr;
        }
	}

    ID3D11PixelShader* m_shader;
};