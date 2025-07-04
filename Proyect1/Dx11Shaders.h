// Dx11Shader.h
#pragma once
#include "Shader.h"
#include "Base.h"
#include <d3dcompiler.h>
#include <wrl/client.h>

class Dx11VertexShader : public Shader
{
public:
    Dx11VertexShader() : Shader(ShaderType::Vertex), m_shader(nullptr), m_blob(nullptr) {}
    ~Dx11VertexShader() override { CleanUpResources(); }
    void CleanUpResources() override
    {
        if (m_shader) m_shader->Release();
        if (m_blob) m_blob->Release();
        m_shader = nullptr;
        m_blob = nullptr;
    }
    ID3D11VertexShader* m_shader;
    ID3DBlob* m_blob; // Para el input layout
};

class Dx11PixelShader : public Shader 
{
public:
    Dx11PixelShader() : Shader(ShaderType::Pixel), m_shader(nullptr) {}
    ~Dx11PixelShader() override { CleanUpResources(); }
    void CleanUpResources() override 
    {
        if (m_shader) m_shader->Release();
        m_shader = nullptr;
    }
    ID3D11PixelShader* m_shader;
};
