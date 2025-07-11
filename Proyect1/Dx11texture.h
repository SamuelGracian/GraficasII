#pragma once
#include "texture.h"
#include "Base.h"


class Dx11ShaderResourceTexture : public ShaderResourceTexture 
{
public:
    Dx11ShaderResourceTexture() : m_texture(nullptr), m_srv(nullptr) {}

    virtual ~Dx11ShaderResourceTexture() { CleanUpResources();}

    virtual void CleanUpResources() override
    {
        if (m_srv) { m_srv->Release(); m_srv = nullptr; }
        if (m_texture) { m_texture->Release(); m_texture = nullptr; }
    }

public:
    ID3D11Texture2D* m_texture;
    ID3D11ShaderResourceView* m_srv;
};

class Dx11DepthStencilTexture : public DepthStencilTexture
{
public:
    Dx11DepthStencilTexture() : m_texture(nullptr), m_dsv(nullptr) {}
    virtual ~Dx11DepthStencilTexture() { CleanUpResources(); }

    virtual void CleanUpResources() override 
    {
        if (m_dsv) { m_dsv->Release(); m_dsv = nullptr; }
        if (m_texture) { m_texture->Release(); m_texture = nullptr; }
    }

    ID3D11Texture2D* m_texture;
    ID3D11DepthStencilView* m_dsv;
};

class Dx11RenderTarget : public RenderTarget
{
public:
	Dx11RenderTarget() : m_texture(nullptr), m_rtv(nullptr) {}
	virtual ~Dx11RenderTarget() { CleanUpResources(); }
	virtual void CleanUpResources() override
	{
		if (m_rtv) { m_rtv->Release(); m_rtv = nullptr; }
		if (m_texture) { m_texture->Release(); m_texture = nullptr; }
	}
	ID3D11Texture2D* m_texture;
	ID3D11RenderTargetView* m_rtv;
};