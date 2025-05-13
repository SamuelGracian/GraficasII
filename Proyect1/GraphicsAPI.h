#pragma once

#include <windows.h>
#include <d3d11_1.h>
#include <directxmath.h>
#include <d3dcompiler.h>
#include <directxcolors.h>
#include <stdexcept>


class GraphicsAPI
{
public:
    GraphicsAPI(HWND hWnd, UINT width, UINT height);
    ~GraphicsAPI();

    void Clear(const FLOAT color[4]);
    void Present();


private:
    ID3D11Device* m_device = nullptr;
    ID3D11DeviceContext* m_context = nullptr;
    IDXGISwapChain* m_swapChain = nullptr;
    ID3D11RenderTargetView* m_renderTargetView = nullptr;
    ID3D11Texture2D* m_depthStencil = nullptr;
    ID3D11DepthStencilView* m_depthStencilView = nullptr;

    void CreateDeviceAndSwapChain(HWND hWnd, UINT width, UINT height);
    void Cleanup();
};

