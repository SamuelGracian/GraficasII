#include "Dx11texture.h"

//_________________ShaderResourceTexture class_____________________
Dx11ShaderResourceTexture::Dx11ShaderResourceTexture() 
    : m_texture(nullptr), m_srv(nullptr)
{
}

void Dx11ShaderResourceTexture::CleanUpResources()
{
    {
        if (m_srv) { m_srv->Release(); m_srv = nullptr; }
        if (m_texture) { m_texture->Release(); m_texture = nullptr; }

    }
}

//____________________DepthStencilTexture class_____________________
Dx11DepthStencilTexture::Dx11DepthStencilTexture() 
    : m_texture(nullptr), m_depthStencilView(nullptr)
{
}

void Dx11DepthStencilTexture::CleanUpResources()
{
    if (m_depthStencilView) { m_depthStencilView->Release(); m_depthStencilView = nullptr; }
    if (m_texture) { m_texture->Release(); m_texture = nullptr; }
}

//_____________RenderTarget class___________________

Dx11RenderTarget::Dx11RenderTarget() 
    : m_texture(nullptr), m_rtv(nullptr)
{
}

void Dx11RenderTarget::CleanUpResources()
{
    if (m_rtv) { m_rtv->Release(); m_rtv = nullptr; }
    if (m_texture) { m_texture->Release(); m_texture = nullptr; }
}

