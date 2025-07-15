#include "Shader.h"

void Dx11PixelShader::CleanUpResources()
{
    if (m_shader) {
        m_shader->Release();
        m_shader = nullptr;
    }
}

Dx11VertexShader::Dx11VertexShader() : 
    m_shader(nullptr),
    m_inputLayout(nullptr)
{
}

void Dx11VertexShader::CleanUpResources()
{
    if (m_shader)
    {
        m_shader->Release();
        m_shader = nullptr;
    }
    if (m_inputLayout)
    {
        m_inputLayout->Release();

        m_inputLayout = nullptr;
    }
}
