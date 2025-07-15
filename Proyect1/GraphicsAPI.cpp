#include "GraphicsAPI.h"
#include<d3dcompiler.h>
#include <d3d11_1.h>

#include "ConstantBuffer.h"
#include "IndexBuffer.h"
#include "VertexBuffer.h"
#include "texture.h"
#include "Sampler.h"

#include "Dx11texture.h"
#include "Dx11Shaders.h"
#include "Dx11Sampler.h"
#include "Dx11ViewPort.h"

HRESULT CompileShaderFromFile(const WCHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut);

Dx11GraphicsAPI::Dx11GraphicsAPI(HWND windowHandler):
    m_wWnd(windowHandler),
    m_device(nullptr),
    m_immediateContext(nullptr),
    m_swapChain(nullptr)

{
    HRESULT hr = S_OK;
    IDXGISwapChain1* m_swapChain1 = nullptr;
    ID3D11DeviceContext1* m_pImmediateContext1 = nullptr;
    ID3D11Device1* g_pd3dDevice1 = nullptr;
    ID3D11DeviceContext* g_pImmediateContext = nullptr;
    D3D_FEATURE_LEVEL                   m_featureLevel = D3D_FEATURE_LEVEL_11_0;

    RECT rc;
    GetClientRect(m_wWnd, &rc);
    UINT width = rc.right - rc.left;
    UINT height = rc.bottom - rc.top;

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

    for (UINT driverTypeIndex = 0; driverTypeIndex < numDriverTypes; driverTypeIndex++)
    {
        
       auto m_driverType = driverTypes[driverTypeIndex];
        hr = D3D11CreateDevice(nullptr, m_driverType, nullptr, createDeviceFlags, featureLevels, numFeatureLevels,
            D3D11_SDK_VERSION, &m_device, &m_featureLevel, &m_immediateContext);

        if (hr == E_INVALIDARG)
        {
            // DirectX 11.0 platforms will not recognize D3D_FEATURE_LEVEL_11_1 so we need to retry without it
            hr = D3D11CreateDevice(nullptr, m_driverType, nullptr, createDeviceFlags, &featureLevels[1], numFeatureLevels - 1,
                D3D11_SDK_VERSION, &m_device, &m_featureLevel, &m_immediateContext);
        }

        if (SUCCEEDED(hr))
            break;
    }
    if (FAILED(hr))
        MessageBox(nullptr,
            L"Failed to create the Direct3D device and swap chain.",
            L"Error", MB_OK | MB_ICONERROR);

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
    if (FAILED(hr))
        MessageBox(nullptr,
            L"Failed to create the Direct3D device and swap chain.",
            L"Error", MB_OK | MB_ICONERROR);

    // Create swap chain
    IDXGIFactory2* dxgiFactory2 = nullptr;
    hr = dxgiFactory->QueryInterface(__uuidof(IDXGIFactory2), reinterpret_cast<void**>(&dxgiFactory2));
    if (dxgiFactory2)
    {
        // DirectX 11.1 or later
        hr = m_device->QueryInterface(__uuidof(ID3D11Device1), reinterpret_cast<void**>(&g_pd3dDevice1));
        if (SUCCEEDED(hr))
        {
            (void)m_immediateContext->QueryInterface(__uuidof(ID3D11DeviceContext1), reinterpret_cast<void**>(&m_pImmediateContext1));
        }

        DXGI_SWAP_CHAIN_DESC1 sd = {};
        sd.Width = width;
        sd.Height = height;
        sd.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        sd.SampleDesc.Count = 1;
        sd.SampleDesc.Quality = 0;
        sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
        sd.BufferCount = 1;

        hr = dxgiFactory2->CreateSwapChainForHwnd(m_device, m_wWnd, &sd, nullptr, nullptr, & m_swapChain1);
        if (SUCCEEDED(hr))
        {
            hr = m_swapChain1->QueryInterface(__uuidof(IDXGISwapChain), reinterpret_cast<void**>(&m_swapChain));
        }

        dxgiFactory2->Release();
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
        sd.OutputWindow = m_wWnd;
        sd.SampleDesc.Count = 1;
        sd.SampleDesc.Quality = 0;
        sd.Windowed = TRUE;

        hr = dxgiFactory->CreateSwapChain(m_device, &sd, &m_swapChain);
    }

    // Note this tutorial doesn't handle full-screen swapchains so we block the ALT+ENTER shortcut
    dxgiFactory->MakeWindowAssociation(windowHandler, DXGI_MWA_NO_ALT_ENTER);

    dxgiFactory->Release();

    if (FAILED(hr))
        MessageBox(nullptr,
            L"Failed to create the Direct3D device and swap chain.",
            L"Error", MB_OK | MB_ICONERROR);
    //  return hr;

    RELEASE(m_swapChain1);
    RELEASE(m_pImmediateContext1);
    RELEASE(g_pd3dDevice1);
}

Dx11GraphicsAPI::~Dx11GraphicsAPI()
{
    CleanUpResources();
}


void Dx11GraphicsAPI::CleanUpResources()
{
    for (auto &element : m_renderResourceList)
    {
        element.reset();
    }
    m_renderResourceList.clear();
    RELEASE(m_swapChain);
    RELEASE(m_immediateContext);
    RELEASE(m_device);
}

std::weak_ptr<ConstantBuffer> Dx11GraphicsAPI::CreateConstanBuffer(const uint32_t byteWidth, 
    const void* initData, 
    const uint32_t slot)
{
    auto buffer = std::make_shared<Dx11ConstantBuffer>();
    buffer->m_byteWidth = byteWidth;
    buffer->m_slot = slot;
    buffer->m_buffer = BuildBuffer(byteWidth, initData, D3D11_BIND_CONSTANT_BUFFER);

    m_renderResourceList.push_back(buffer);

    return buffer;
}

std::weak_ptr <IndexBuffer> Dx11GraphicsAPI::CreateIndexBuffer(const uint32_t byteWidth,
    const void* initData,
    uint32_t indexCount)
{

    auto buffer = std::make_shared<Dx11IndexBuffer>();

    buffer->m_indexCount = indexCount;
    buffer->m_byteWidth = byteWidth;
    buffer->m_buffer = BuildBuffer(byteWidth, initData, D3D11_BIND_INDEX_BUFFER);
     
    m_renderResourceList.push_back(buffer);
    return buffer;
}
std::weak_ptr<VertexBuffer> Dx11GraphicsAPI::CreateVertexBuffer(const uint32_t byteWidth,
    const void* vertices,
    const uint32_t stride,
    const uint32_t offset)
{
    auto buffer = std::make_shared<Dx11VertexBuffer>();

    buffer->m_byteWidth = byteWidth;
    buffer->m_offset = offset;
    buffer->m_stride = stride;
    buffer->m_buffer = (BuildBuffer(byteWidth,vertices, D3D11_BIND_VERTEX_BUFFER));

    m_renderResourceList.push_back(buffer);
    return buffer;

}

std::weak_ptr<ShaderResourceTexture> Dx11GraphicsAPI::CreateShaderResource(
    const uint32_t width,
    const uint32_t height,
    const uint32_t mipLevels,
    const void* initData)
{
    auto texture = std::make_shared<Dx11ShaderResourceTexture>();
    texture->m_width = width;
    texture->m_height = height;
    texture->m_mipLevels = mipLevels;

    D3D11_TEXTURE2D_DESC desc = {};
    desc.Width = width;
    desc.Height = height;
    desc.MipLevels = mipLevels;
    desc.ArraySize = 1;
    desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    desc.SampleDesc.Count = 1;
    desc.SampleDesc.Quality = 0;
    desc.Usage = D3D11_USAGE_DEFAULT;
    desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
    desc.CPUAccessFlags = 0;
    desc.MiscFlags = 0;

    D3D11_SUBRESOURCE_DATA initDataDesc = {};
    initDataDesc.pSysMem = initData;

    ID3D11Texture2D* d3dTexture = nullptr;
    HRESULT hr = m_device->CreateTexture2D(
        &desc,
        initData ? &initDataDesc : nullptr,
        &d3dTexture);


    texture->m_texture = d3dTexture; 

    m_renderResourceList.push_back(texture);
    return texture;
}

std::weak_ptr<DepthStencilTexture> Dx11GraphicsAPI::CreateDepthStencil(const uint32_t width, const uint32_t height, const uint32_t mipLevels, const void* initData)
{
    return std::weak_ptr<DepthStencilTexture>();
}


std::weak_ptr<RenderTarget> Dx11GraphicsAPI::CreateRenderTarget(const uint32_t width, const uint32_t height, const uint32_t mipLevels, const void* initData)
{
    return std::weak_ptr<RenderTarget>();
}

std::weak_ptr<VertexShader> Dx11GraphicsAPI::CreateVertexShader(const uint32_t byteWidth, const void* shaderBytecode, const void* vertices, const uint32_t stride, const uint32_t offset)
{
    ID3DBlob* pVSBlob = nullptr;
    if (!shaderBytecode) {
        HRESULT hr = CompileShaderFromFile(L"Tutorial07.fxh", "VS", "vs_4_0", &pVSBlob);
        if (FAILED(hr)) {
            return std::weak_ptr<VertexShader>();
        }
    }
    else {
        pVSBlob = (ID3DBlob*)shaderBytecode;
    }

    ID3D11VertexShader* vertexShader = nullptr;
    HRESULT hr = m_device->CreateVertexShader(
        pVSBlob->GetBufferPointer(),
        pVSBlob->GetBufferSize(),
        nullptr,
        &vertexShader);
    if (FAILED(hr)) {
        if (!shaderBytecode && pVSBlob) pVSBlob->Release();
        return std::weak_ptr<VertexShader>();
    }

    D3D11_INPUT_ELEMENT_DESC layout[] = {
        { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
    };
    UINT numElements = ARRAYSIZE(layout);

    ID3D11InputLayout* inputLayout = nullptr;
    hr = m_device->CreateInputLayout(
        layout, numElements,
        pVSBlob->GetBufferPointer(),
        pVSBlob->GetBufferSize(),
        &inputLayout);
    if (FAILED(hr)) {
        vertexShader->Release();
        if (!shaderBytecode && pVSBlob) pVSBlob->Release();
        return std::weak_ptr<VertexShader>();
    }

    if (!shaderBytecode && pVSBlob) pVSBlob->Release();
}

std::weak_ptr<PixelShader> Dx11GraphicsAPI::CreatePixelShader(
    const uint32_t byteWidth,
    const uint32_t stride,
    const uint32_t offset)
{
    ID3DBlob* pPSBlob = nullptr;
    HRESULT hr = S_OK;

    ID3D11PixelShader* pixelShader = nullptr;
    hr = m_device->CreatePixelShader(
        pPSBlob->GetBufferPointer(),
        pPSBlob->GetBufferSize(),
        nullptr,
        &pixelShader
    );

    if (FAILED(hr)) {
        if (pixelShader) pixelShader->Release();
        return std::weak_ptr<PixelShader>();
    }

    auto shaderPtr = std::make_shared<Dx11PixelShader>();

    shaderPtr->m_shader = pixelShader;

    m_renderResourceList.push_back(shaderPtr);
    return shaderPtr;
}

std::weak_ptr<Sampler> Dx11GraphicsAPI::CreateSampler()
{

    D3D11_SAMPLER_DESC sampDesc = {};
    sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
    sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
    sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
    sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
    sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
    sampDesc.MinLOD = 0;
    sampDesc.MaxLOD = D3D11_FLOAT32_MAX;

    auto samplerPtr = std::make_shared<Dx11Sampler>();

    m_device->CreateSamplerState(&sampDesc, &samplerPtr->m_samplerState);

    m_renderResourceList.push_back(samplerPtr);

	return samplerPtr;
}

ID3D11Buffer* Dx11GraphicsAPI::BuildBuffer(uint32_t byteWidth, const void* initData, uint32_t bindFlag)
{
    if (byteWidth == 0 || bindFlag == 0)
    {
        return nullptr;
    }

    HRESULT hr = S_OK;
    D3D11_BUFFER_DESC bd = {};
    bd.Usage = D3D11_USAGE_DEFAULT;
    bd.ByteWidth = byteWidth;
    bd.BindFlags = bindFlag;
    bd.CPUAccessFlags = 0;

    D3D11_SUBRESOURCE_DATA InitData = {};
    InitData.pSysMem = initData;

    ID3D11Buffer* pBuffer = nullptr;
    hr = m_device->CreateBuffer(&bd, initData == nullptr ? nullptr : &InitData, &pBuffer);
    if (FAILED(hr))
        return nullptr;

    return pBuffer;
}

void Dx11GraphicsAPI::RenderPase()
{
}


HRESULT CompileShaderFromFile(const WCHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut)
{
    HRESULT hr = S_OK;

    // Open the file
    std::ifstream shaderFile(szFileName);
    if (!shaderFile.is_open())
    {
        return E_FAIL;
    }
 
    std::string shaderCode((std::istreambuf_iterator<char>(shaderFile)), std::istreambuf_iterator<char>());
    shaderFile.close();

    ID3DBlob* pErrorBlob = nullptr;
    hr = D3DCompile(shaderCode.c_str(), shaderCode.size(), nullptr, nullptr, nullptr, szEntryPoint, szShaderModel, 0, 0, ppBlobOut, &pErrorBlob);
    if (FAILED(hr))
    {
        if (pErrorBlob)
        {
            OutputDebugStringA((char*)pErrorBlob->GetBufferPointer());
            pErrorBlob->Release();
        }
        return hr;
    }
    if (pErrorBlob) pErrorBlob->Release();

    return S_OK;
}

std::weak_ptr<ViewPort> Dx11GraphicsAPI::CreateViewPort(int x, int y, int width, int height) {
    auto viewport = std::make_shared<Dx11ViewPort>();

    m_renderResourceList.push_back(viewport);

    return viewport;
}

void Dx11GraphicsAPI::SetViewPort(const std::shared_ptr<ViewPort>& viewport) {
    if (!viewport) return;
    D3D11_VIEWPORT vp;
    vp.TopLeftX = static_cast<FLOAT>(viewport->m_x);
    vp.TopLeftY = static_cast<FLOAT>(viewport->m_y);
    vp.Width = static_cast<FLOAT>(viewport->m_width);
    vp.Height = static_cast<FLOAT>(viewport->m_height);
    vp.MinDepth = 0.0f;
    vp.MaxDepth = 1.0f;
    m_immediateContext->RSSetViewports(1, &vp);
}