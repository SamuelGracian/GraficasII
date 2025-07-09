#pragma once
#include <memory>
#include <vector>

#include "Base.h"
#include "RenderElement.h"

class ViewPort;

class DepthStencil;

class RenderTarget;

class PixelShader;

class VertexShader;

class Sampler;

class ShaderResourceTexture;

class ConstantBuffer;

class Pase final
{
    friend class GraphicsAPI;
public:
    Pase();
    ~Pase();

    void BindConstantBuffer(std::weak_ptr<ConstantBuffer>& buffer, const uint32_t sslot);

    void BindRenderTarget(std::weak_ptr<RenderTarget>& RT, const uint32_t slot);

    void BindSampler(std::weak_ptr<Sampler>& sampler, const uint32_t slot);

    void BindShaderTexture(std::weak_ptr<ShaderResourceTexture>& shaderTexture, uint32_t slot);

    void BindDepthStencil(std::weak_ptr<DepthStencil>& depthStencil);

    void BindViewPort(std::weak_ptr<ViewPort>& viewport);

    void BindPixelShader(std::weak_ptr<PixelShader>& pixelShader);

    void BindVertexShader(std::weak_ptr<VertexShader>& vertexShader);

    void AddRenderElement(std::weak_ptr<RenderElement>element);

private:
    std::vector<std::weak_ptr<ConstantBuffer>> m_ConstantBuffers;
    std::vector<std::weak_ptr<RenderTarget>> m_RenderTargets;
    std::vector<std::weak_ptr<Sampler>> m_Samplers;
    std::vector<std::weak_ptr<ShaderResourceTexture>> m_ShaderResourceTextures;

    std::weak_ptr<DepthStencil> m_DepthStencils;
    std::weak_ptr<ViewPort> m_ViewPorts;
    std::weak_ptr<PixelShader> m_pixelShader;
    std::weak_ptr<VertexShader> m_vertexShader;

    std::vector<std::weak_ptr<RenderElement>> m_renderElement;
};