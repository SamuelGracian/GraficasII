// Dx11Shader.h
#pragma once
#include "Shader.h"
#include "Base.h"
#include <d3dcompiler.h>
#include <wrl/client.h>

class Dx11VertexShader : public Shader
{
public:
    Dx11VertexShader(ID3D11VertexShader* shader, ID3D11InputLayout* layout)
        : Shader(ShaderType::Vertex), m_shader(shader), m_inputLayout(layout) {
    }

    ~Dx11VertexShader() override {
        CleanUpResources();
    }

    void CleanUpResources() override {
        if (m_shader) { m_shader->Release(); m_shader = nullptr; }
        if (m_inputLayout) { m_inputLayout->Release(); m_inputLayout = nullptr; }
    }

    ID3D11VertexShader* GetNativeShader() const { return m_shader; }
    ID3D11InputLayout* GetInputLayout() const { return m_inputLayout; }

private:
    ID3D11VertexShader* m_shader = nullptr;
    ID3D11InputLayout* m_inputLayout = nullptr;
};


class Dx11PixelShader : public Shader
{
public:
    Dx11PixelShader(ID3D11PixelShader* shader)
        : Shader(ShaderType::Pixel), m_shader(shader) {
    }

    ~Dx11PixelShader() override {
        CleanUpResources();
    }

    void CleanUpResources() override {
        if (m_shader) { m_shader->Release(); m_shader = nullptr; }
    }

    ID3D11PixelShader* GetNativeShader() const { return m_shader; }

private:
    ID3D11PixelShader* m_shader = nullptr;
};