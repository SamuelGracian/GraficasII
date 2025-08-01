#pragma once

#include "RenderResource.h"
#include <d3d11.h>

class DepthStencil : public RenderResource
{
public:
    DepthStencil();
    virtual ~DepthStencil();

    bool Create(ID3D11Device* device, int width, int height, DXGI_FORMAT format);
    virtual void CleanUpResources() override;

    ID3D11DepthStencilView* GetView() const { return m_depthStencilView; }
    ID3D11Texture2D* GetTexture() const { return m_depthStencilBuffer; }

    void Resize(ID3D11Device* device, int newWidth, int newHeight);

private:
    ID3D11Texture2D* m_depthStencilBuffer = nullptr;
    ID3D11DepthStencilView* m_depthStencilView = nullptr;
    int m_width = 0;
    int m_height = 0;
    DXGI_FORMAT m_format = DXGI_FORMAT_D24_UNORM_S8_UINT;
};