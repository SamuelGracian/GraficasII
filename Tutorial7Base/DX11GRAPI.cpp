#include "DX11GRAPI.H"
#include <dxgi1_2.h>
#include <d3d11_1.h> 
#include "dxgiformat.h"
#include <iostream>

#define SAFE_RELEASE(x) if (x) {x -> Release(); x = nullptr;}
#define HIGHER_AVAILABLE_SLOT 8

//namespace GRAPIFormat
//{
//    enum Frmt
//    {
//        FORMAT_R8G8B8A8_UNORM = 28,
//    };
//}
//uint32_t  GEtFormat(const GRAPIFormat::Frmt = GRAPIFormat::FORMAT_R8G8B8A8_UNORM)
//{
//    switch (GRAPIFormat::Frmt)
//    {
//        case GRAPIFormat::FORMAT_R8G8B8A8_UNORM;
//            return;  DXGI_FORMAT::
//    default:
//        break;
//    }
//}


Dx11GraphicsAPI::Dx11GraphicsAPI()
	:m_device(nullptr),m_immediateContext(nullptr),m_swapChain(nullptr)
{
    UINT createDeviceFlags = 0;
#ifdef _DEBUG
    createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

    D3D_DRIVER_TYPE driverTypes[] =
    {
        D3D_DRIVER_TYPE_HARDWARE,
        D3D_DRIVER_TYPE_WARP,
        D3D_DRIVER_TYPE_REFERENCE,
    };
    UINT numDriverTypes = ARRAYSIZE(driverTypes);

    D3D_FEATURE_LEVEL featureLevels[] =
    {
        D3D_FEATURE_LEVEL_11_1,
        D3D_FEATURE_LEVEL_11_0,
        D3D_FEATURE_LEVEL_10_1,
        D3D_FEATURE_LEVEL_10_0,
    };
    UINT numFeatureLevels = ARRAYSIZE(featureLevels);

    HRESULT hr = S_OK;
    for (UINT driverTypeIndex = 0; driverTypeIndex < numDriverTypes; driverTypeIndex++)
    {
        D3D_DRIVER_TYPE  g_driverType = driverTypes[driverTypeIndex];
        ///DELETE THIS 
        D3D_FEATURE_LEVEL g_featureLevel = D3D_FEATURE_LEVEL_11_0;

        hr = D3D11CreateDevice(nullptr, g_driverType, nullptr, createDeviceFlags, featureLevels, numFeatureLevels,
            D3D11_SDK_VERSION, &m_device, &g_featureLevel, &m_immediateContext);

        if (hr == E_INVALIDARG)
        {
            // DirectX 11.0 platforms will not recognize D3D_FEATURE_LEVEL_11_1 so we need to retry without it
            hr = D3D11CreateDevice(nullptr, g_driverType, nullptr, createDeviceFlags, &featureLevels[1], numFeatureLevels - 1,
                D3D11_SDK_VERSION, &m_device, &g_featureLevel, &m_immediateContext);
        }

        if (SUCCEEDED(hr))
            break;
    }
    assert (!FAILED(hr));

    // Obtain DXGI factory from device (since we used nullptr for pAdapter above)
    IDXGIFactory1* dxgiFactory = nullptr;
    {
        IDXGIDevice* dxgiDevice = nullptr;
        hr = m_device->QueryInterface(__uuidof(IDXGIDevice), reinterpret_cast<void**>(&dxgiDevice));
        if (SUCCEEDED(hr))
        {
            IDXGIAdapter* adapter = nullptr;
            hr = dxgiDevice->GetAdapter(&adapter);
            if (SUCCEEDED(hr))
            {
                hr = adapter->GetParent(__uuidof(IDXGIFactory1), reinterpret_cast<void**>(&dxgiFactory));
                adapter->Release();
            }
            dxgiDevice->Release();
        }
    }
   assert (!FAILED(hr));

}

Dx11GraphicsAPI::~Dx11GraphicsAPI()
{
	CleanUpResources();
}

void Dx11GraphicsAPI::CleanUpResources()
{
    SAFE_RELEASE(m_swapChain);
    SAFE_RELEASE(m_immediateContext);
    SAFE_RELEASE(m_device);
}

void Dx11GraphicsAPI::CreateSwapChain(HWND hwnd, uint32_t width , uint32_t height )
{
    HRESULT hr = S_OK;

    IDXGIFactory1* dxgiFactory = nullptr;
    {
        IDXGIDevice* dxgiDevice = nullptr;
        hr = m_device->QueryInterface(__uuidof(IDXGIDevice), reinterpret_cast<void**>(&dxgiDevice));
        if (SUCCEEDED(hr))
        {
            IDXGIAdapter* adapter = nullptr;
            hr = dxgiDevice->GetAdapter(&adapter);
            if (SUCCEEDED(hr))
            {
                hr = adapter->GetParent(__uuidof(IDXGIFactory1), reinterpret_cast<void**>(&dxgiFactory));
                SAFE_RELEASE(adapter);
            }
            SAFE_RELEASE(dxgiDevice);
        }
    }
    assert (!FAILED(hr));

    // Create swap chain
    ID3D11Device* m_device1 = nullptr;
    ID3D11DeviceContext1* m_immediateContext1 = nullptr;
    IDXGISwapChain1* m_swapChain1 =  nullptr;
    IDXGIFactory2* dxgiFactory2 = nullptr;
    hr = dxgiFactory->QueryInterface(__uuidof(IDXGIFactory2), reinterpret_cast<void**>(&dxgiFactory2));
    if (dxgiFactory2)
    {
        // DirectX 11.1 or later
        hr = m_device->QueryInterface(__uuidof(ID3D11Device1), reinterpret_cast<void**>(&m_device1));
        if (SUCCEEDED(hr))
        {
            (void)m_immediateContext->QueryInterface(__uuidof(ID3D11DeviceContext1), reinterpret_cast<void**>(&m_immediateContext1));
        }

        DXGI_SWAP_CHAIN_DESC1 sd = {};
        sd.Width = width;
        sd.Height = height;
        sd.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        sd.SampleDesc.Count = 1;
        sd.SampleDesc.Quality = 0;
        sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
        sd.BufferCount = 1;

        hr = dxgiFactory2->CreateSwapChainForHwnd(m_device,hwnd, &sd, nullptr, nullptr, &m_swapChain1);
        if (SUCCEEDED(hr))
        {
            hr = m_swapChain1->QueryInterface(__uuidof(IDXGISwapChain), reinterpret_cast<void**>(&m_swapChain));
        }

        SAFE_RELEASE(dxgiFactory2);
    }
    else
    {
        // DirectX 11.0 systems
        DXGI_SWAP_CHAIN_DESC sd = {};
        sd.BufferCount = 1;
        sd.BufferDesc.Width = width;
        sd.BufferDesc.Height = height;
        sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        sd.BufferDesc.RefreshRate.Numerator = 60;
        sd.BufferDesc.RefreshRate.Denominator = 1;
        sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
        sd.OutputWindow = hwnd;
        sd.SampleDesc.Count = 1;
        sd.SampleDesc.Quality = 0;
        sd.Windowed = TRUE;
        

        hr = dxgiFactory->CreateSwapChain(m_device, &sd, &m_swapChain);
    }

    dxgiFactory->MakeWindowAssociation(hwnd, DXGI_MWA_NO_ALT_ENTER);

    SAFE_RELEASE(dxgiFactory);
    SAFE_RELEASE(m_swapChain1);
    SAFE_RELEASE(m_immediateContext1);  
    SAFE_RELEASE(m_device1);

    assert (!FAILED(hr));
}

std::shared_ptr<Dx11SwapChain> Dx11GraphicsAPI::GetSwapChain()
{
    auto SChain = std::make_shared<Dx11SwapChain>();
    SChain->m_swapChain = m_swapChain;
    return SChain;
}

std::shared_ptr<ConstantBuffer> Dx11GraphicsAPI::CreateConstantBuffer(const uint32_t bytewidth, const uint32_t slot, void* data)
{
    assert(bytewidth != 0);
    ID3D11Buffer* Rawbuffer= nullptr;
    D3D11_BUFFER_DESC bd = {};
    bd.Usage = D3D11_USAGE_DEFAULT;
    bd.ByteWidth = bytewidth;
    bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    bd.CPUAccessFlags = 0;

    assert(!FAILED(m_device->CreateBuffer(&bd, nullptr, &Rawbuffer)));

    auto buffer = std::make_shared<Dx11ConstatBuffer>();
    buffer->m_buffer = Rawbuffer;

    return buffer;
}

std::shared_ptr<IndexBuffer> Dx11GraphicsAPI::CreateIndexBuffer(const uint32_t bytewidth, void* data, uint32_t indexcount)
{
    assert(bytewidth != 0);
    D3D11_BUFFER_DESC bd = {};
    ID3D11Buffer* Rawbuffer = nullptr;
    D3D11_SUBRESOURCE_DATA InitData = {};

    bd.Usage = D3D11_USAGE_DEFAULT;
    bd.ByteWidth = bytewidth;
    bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
    bd.CPUAccessFlags = 0;
    InitData.pSysMem = data;

    assert(!FAILED(m_device->CreateBuffer(&bd, &InitData, &Rawbuffer)));

    auto buffer = std::make_shared<Dx11IndexBuffer>();
    buffer->m_buffer = Rawbuffer;
    return buffer;
}

std::shared_ptr<VertexBuffer> Dx11GraphicsAPI::CreateVertexBuffer(const uint32_t bytewidth, const void* vertices)
{
    ID3D11Buffer* Rawbuffer = nullptr;

    D3D11_BUFFER_DESC bd = {};
    bd.Usage = D3D11_USAGE_DEFAULT;
    bd.ByteWidth = bytewidth;
    bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    bd.CPUAccessFlags = 0;

    D3D11_SUBRESOURCE_DATA InitData = {};
    InitData.pSysMem = vertices;

    assert(!FAILED( m_device->CreateBuffer(&bd, &InitData, &Rawbuffer)));

    auto buffer = std::make_shared<Dx11VertexBuffer>();
    buffer->m_buffer = Rawbuffer;
    return buffer;
}

std::shared_ptr<VertexShader> Dx11GraphicsAPI::CreateVertexShader(const void* shaderBytecode, uint32_t bytecodeLenght, ID3D11ClassLinkage* classLink, ID3D11VertexShader* shader)
{
    ID3D11VertexShader* vertexShader = nullptr;
    HRESULT hr = m_device->CreateVertexShader(shaderBytecode, bytecodeLenght, classLink, &vertexShader);
    assert(SUCCEEDED(hr));

    auto shaderPtr = std::make_shared<VertexShader>();
  
    return shaderPtr;
}

std::shared_ptr<PixelShader> Dx11GraphicsAPI::CreatePixelShader(const void* shaderBytecode, uint32_t bytecodeLength, ID3D11ClassLinkage* classLink, ID3D11PixelShader* shader)
{
    ID3D11PixelShader* pixelShader = nullptr;
    HRESULT hr = m_device->CreatePixelShader(shaderBytecode, bytecodeLength, classLink, &pixelShader);
    assert(SUCCEEDED(hr));

    auto shaderPtr = std::make_shared<Dx11PixelShader>();
    shaderPtr->m_shader = pixelShader;
    return shaderPtr;
}

std::shared_ptr<DepthStencil> Dx11GraphicsAPI::CreateDepthStencil(uint32_t width, uint32_t height)
{
    return std::shared_ptr<DepthStencil>();
}

//std::shared_ptr<DepthStencil> Dx11GraphicsAPI::CreateDepthStencil(uint32_t width, uint32_t height)
//{
//    //D3D11_TEXTURE2D_DESC descDepth = {};
//    //descDepth.Width = width;
//    //descDepth.Height = height;
//    //descDepth.MipLevels = 1;
//    //descDepth.ArraySize = 1;
//    //descDepth.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
//    //descDepth.SampleDesc.Count = 1;
//    //descDepth.SampleDesc.Quality = 0;
//    //descDepth.Usage = D3D11_USAGE_DEFAULT;
//    //descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;
//    //descDepth.CPUAccessFlags = 0;
//    //descDepth.MiscFlags = 0;
//
//    //ID3D11Texture2D* depthStencil = nullptr;
//    //HRESULT hr = m_device->CreateTexture2D(&descDepth, nullptr, &depthStencil);
//    //assert(SUCCEEDED(hr));
//
//    //auto ds = std::make_shared<Dx11DepthStencil>();
//
//    //ds->m_depthStencil = depthStencil;
//    //return ds;
//    return;
//}
