#include "GraphicsAPI.h"
#include <stdexcept>

using namespace DirectX;

GraphicsAPI::GraphicsAPI(HWND hWnd, UINT width, UINT height)
{
    CreateDeviceAndSwapChain(hWnd, width, height);
}

GraphicsAPI::~GraphicsAPI()
{
    Cleanup();
}

void GraphicsAPI::Clear(const FLOAT color[4])
{
    m_context->ClearRenderTargetView(m_renderTargetView, color);
    m_context->ClearDepthStencilView(m_depthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);
}

void GraphicsAPI::Present()
{
    m_swapChain->Present(0, 0);
}

void GraphicsAPI::CreateDeviceAndSwapChain(HWND hWnd, UINT width, UINT height)
{
    DXGI_SWAP_CHAIN_DESC scd = {};
    scd.BufferCount = 1;
    scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    scd.BufferDesc.Width = width;
    scd.BufferDesc.Height = height;
    scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    scd.OutputWindow = hWnd;
    scd.SampleDesc.Count = 1;
    scd.Windowed = TRUE;
    scd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

    UINT createDeviceFlags = 0;
#if defined(_DEBUG)
    createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

    D3D_FEATURE_LEVEL featureLevel;
    const D3D_FEATURE_LEVEL featureLevels[] = {
        D3D_FEATURE_LEVEL_11_0,
        D3D_FEATURE_LEVEL_10_1,
        D3D_FEATURE_LEVEL_10_0,
    };

    HRESULT hr = D3D11CreateDeviceAndSwapChain(
        nullptr,
        D3D_DRIVER_TYPE_HARDWARE,
        nullptr,
        createDeviceFlags,
        featureLevels,
        ARRAYSIZE(featureLevels),
        D3D11_SDK_VERSION,
        &scd,
        &m_swapChain,
        &m_device,
        &featureLevel,
        &m_context
    );

    if (FAILED(hr))
        throw std::runtime_error("Failed to create device and swap chain");

    ID3D11Texture2D* backBuffer = nullptr;
    hr = m_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&backBuffer);
    if (FAILED(hr))
        throw std::runtime_error("Failed to get back buffer");

    hr = m_device->CreateRenderTargetView(backBuffer, nullptr, &m_renderTargetView);
    backBuffer->Release();
    if (FAILED(hr))
        throw std::runtime_error("Failed to create render target view");

    D3D11_TEXTURE2D_DESC depthDesc = {};
    depthDesc.Width = width;
    depthDesc.Height = height;
    depthDesc.MipLevels = 1;
    depthDesc.ArraySize = 1;
    depthDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
    depthDesc.SampleDesc.Count = 1;
    depthDesc.Usage = D3D11_USAGE_DEFAULT;
    depthDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;

    hr = m_device->CreateTexture2D(&depthDesc, nullptr, &m_depthStencil);
    if (FAILED(hr))
        throw std::runtime_error("Failed to create depth stencil texture");

    hr = m_device->CreateDepthStencilView(m_depthStencil, nullptr, &m_depthStencilView);
    if (FAILED(hr))
        throw std::runtime_error("Failed to create depth stencil view");

    m_context->OMSetRenderTargets(1, &m_renderTargetView, m_depthStencilView);

    D3D11_VIEWPORT vp = {};
    vp.Width = static_cast<FLOAT>(width);
    vp.Height = static_cast<FLOAT>(height);
    vp.MinDepth = 0.0f;
    vp.MaxDepth = 1.0f;
    vp.TopLeftX = 0;
    vp.TopLeftY = 0;
    m_context->RSSetViewports(1, &vp);
}

void GraphicsAPI::Cleanup()
{
    if (m_context) m_context->ClearState();
    if (m_renderTargetView) m_renderTargetView->Release();
    if (m_depthStencilView) m_depthStencilView->Release();
    if (m_depthStencil) m_depthStencil->Release();
    if (m_swapChain) m_swapChain->Release();
    if (m_context) m_context->Release();
    if (m_device) m_device->Release();
}
