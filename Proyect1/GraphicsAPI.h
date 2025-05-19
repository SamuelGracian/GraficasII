#pragma once

#include <windows.h>
#include <d3d11_1.h>
#include <directxmath.h>
#include <d3dcompiler.h>
#include <directxcolors.h>
#include <stdexcept>


#include "InConstantBuffer.h"

class GraphicsAPI
{
public:
    GraphicsAPI(HWND hWnd, UINT width, UINT height);
    ~GraphicsAPI();

    void Clear(const FLOAT color[4]);
    

     ConstantBuffer* CreateConstantBuffer();


private:
    ID3D11Device* m_device;
    ID3D11DeviceContext* m_context;
    IDXGISwapChain* m_swapChain;
    ID3D11RenderTargetView* m_renderTargetView;
    ID3D11Texture2D* m_depthStencil;
    ID3D11DepthStencilView* m_depthStencilView;

    void CreateDeviceAndSwapChain(HWND hWnd, UINT width, UINT height);
    void Cleanup();
};

