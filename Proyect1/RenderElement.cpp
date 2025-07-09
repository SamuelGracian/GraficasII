#include "RenderElement.h"

void RenderElement::BindConstantBuffer(std::weak_ptr<ConstantBuffer>& buffer, const uint32_t slot)
{
    if (m_constantbuffers.size() <= slot)
    {
        std::cout << "Slot doesnt fit the vector" << std::endl;
        return;
    }
    m_constantbuffers[slot] = buffer;
}

void RenderElement::BindRenderTarget(std::weak_ptr<RenderTarget>& RT, const uint32_t slot)
{

    if (m_constantbuffers.size() <= slot)
    {
        std::cout << "Slot doesnt fit the vector" << std::endl;
        return;
    }
     m_RenderTargets[slot] = RT;
}

void RenderElement::BindShaderTexture(std::weak_ptr<ShaderResourceTexture>& shaderTexture, uint32_t slot)
{
    if (m_constantbuffers.size() <= slot)
    {
        std::cout << "Slot doesnt fit the vector" << std::endl;
        return;
    }
    m_shaderTextures[slot] = shaderTexture;
}

void RenderElement::BindSampler(std::weak_ptr<Sampler>& sampler, const uint32_t slot)
{
    if (m_samplers.size() <= slot)
    {
        std::cout << "Slot doesnt fit the vector" << std::endl;
        return;
    }
    m_samplers[slot] = sampler;
}

void RenderElement::BindPixelShader(std::weak_ptr<PixelShader>& pixelShader)
{
    m_pixelShader = pixelShader;
}

void RenderElement::BindVertexShader(std::weak_ptr<VertexShader>& vertexShader)
{
    m_vertexShader = vertexShader;
}

void RenderElement::BindTpology(std::weak_ptr<PrimitiveTopology>& topology)
{
    m_topology = topology;
}

void RenderElement::BindIndexBuffer(std::weak_ptr<IndexBuffer>& indexBuffer)
{
    m_indexBuffer = indexBuffer;
}

void RenderElement::BindVertexbuffers(std::weak_ptr<VertexBuffer>& vertexBuffer)
{
    m_vertexBuffer = vertexBuffer;
}
