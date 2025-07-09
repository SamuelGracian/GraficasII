#include "pase.h"

void Pase::BindConstantBuffer(std::weak_ptr<ConstantBuffer>& buffer, const uint32_t slot)
{
    if (m_ConstantBuffers.size() <= slot)
    {
        m_ConstantBuffers.resize(slot + 1);
    }
    m_ConstantBuffers[slot] = buffer;
}

void Pase::BindRenderTarget(std::weak_ptr<RenderTarget>& RT, const uint32_t slot)
{
    if (m_RenderTargets.size() <= slot)
    {
        m_RenderTargets.resize(slot + 1);
    }
    m_RenderTargets[slot] = RT;
}

void Pase::BindSampler(std::weak_ptr<Sampler>& sampler, const uint32_t slot)
{
    if (m_Samplers.size() <= slot)
    {
        m_Samplers.resize(slot + 1);
    }
    m_Samplers[slot] = sampler;
}

void Pase::BindShaderTexture(std::weak_ptr<ShaderResourceTexture>& shaderTexture, uint32_t slot)
{
    if (m_ShaderResourceTextures.size() <= slot)
    {
        m_ShaderResourceTextures.resize(slot + 1);
    }
    m_ShaderResourceTextures[slot] = shaderTexture;
}

void Pase::BindDepthStencil(std::weak_ptr<DepthStencil>& depthStencil)
{
    m_DepthStencils = depthStencil;
}

void Pase::BindViewPort(std::weak_ptr<ViewPort>& viewport)
{
    m_ViewPorts = viewport;
}

void Pase::BindPixelShader(std::weak_ptr<PixelShader>& pixelShader)
{
    m_pixelShader = pixelShader;
}

void Pase::BindVertexShader(std::weak_ptr<VertexShader>& vertexShader)
{
    m_vertexShader = vertexShader;
}
