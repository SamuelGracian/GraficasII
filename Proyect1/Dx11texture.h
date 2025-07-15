#pragma once
#include "texture.h"
#include "Base.h"


//__________________ShaderResourceTexture class_____________________
class Dx11ShaderResourceTexture : public ShaderResourceTexture 
{
    friend class Dx11GraphicsAPI;
public:
    Dx11ShaderResourceTexture();

    virtual ~Dx11ShaderResourceTexture() { CleanUpResources();}

    virtual void CleanUpResources() override;

protected:
    ID3D11Texture2D* m_texture;
    ID3D11ShaderResourceView* m_srv;
};


//____________________DepthStencilTexture class_____________________
class Dx11DepthStencilTexture : public DepthStencilTexture
{
    friend class Dx11GraphicsAPI;
public:
    Dx11DepthStencilTexture();

    virtual ~Dx11DepthStencilTexture() { CleanUpResources(); }

    virtual void CleanUpResources() override;

protected:
    ID3D11Texture2D* m_texture;
    ID3D11DepthStencilView* m_dsv;
};


//_____________RenderTarget class___________________
class Dx11RenderTarget : public RenderTarget
{
    friend class Dx11GraphicsAPI;
public:
    Dx11RenderTarget();
	virtual ~Dx11RenderTarget() { CleanUpResources(); }

    virtual void CleanUpResources() override;

protected:
	ID3D11Texture2D* m_texture;
	ID3D11RenderTargetView* m_rtv;
};