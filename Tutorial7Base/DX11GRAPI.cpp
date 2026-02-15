#include "DX11GRAPI.H"
#include <dxgi1_2.h>
#include <d3d11_1.h> 
#include "dxgiformat.h"
#include <iostream>
#include "Dx11Topology.h"
#include <d3dcompiler.h>
#include "Dx11ViewPort.h"

#define SAFE_RELEASE(x) if (x) {x -> Release(); x = nullptr;}
#define HIGHER_AVAILABLE_SLOT 8

DXGI_FORMAT GetDX11Format_internal (const GAPI_FORMAT::K format)
{ 
    switch (format)
    {
    default:
        return DXGI_FORMAT::DXGI_FORMAT_UNKNOWN;
        break;

    case GAPI_FORMAT::FORMAT_D24_UNORM_S8_UINT:
        return DXGI_FORMAT::DXGI_FORMAT_D24_UNORM_S8_UINT;
        break;
        
    case GAPI_FORMAT::FORMAT_R8G8B8A8_UNORM:
        return DXGI_FORMAT::DXGI_FORMAT_R8G8B8A8_UNORM;
    }
}

uint32_t GetDx11BindFlag_internal(uint32_t bindFlags)
{
    uint32_t ResultFlags = 0;

    if ((bindFlags &  GAPI_BIND_FLAGS::BIND_CONSTANT_BUFFER) != 0)
    {
        ResultFlags += D3D11_BIND_FLAG::D3D11_BIND_CONSTANT_BUFFER;
    }

    if ((bindFlags & GAPI_BIND_FLAGS::BIND_INDEX_BUFFER) != 0)
    {
        ResultFlags += D3D11_BIND_INDEX_BUFFER;
    }

    if ((bindFlags & GAPI_BIND_FLAGS::BIND_VERTEX_BUFFER) != 0)
    {
        ResultFlags += D3D11_BIND_VERTEX_BUFFER;
    }

    if ((bindFlags & GAPI_BIND_FLAGS::DEPTH_STENCIL) != 0)
    {
        ResultFlags += D3D11_BIND_DEPTH_STENCIL;
    }

    if ((bindFlags & GAPI_BIND_FLAGS::RENDER_TARGET) != 0)
    {
        ResultFlags += D3D11_BIND_RENDER_TARGET;
    }

    if ((bindFlags & GAPI_BIND_FLAGS::SHADER_RESOURCE) != 0)
    {
        ResultFlags += D3D11_BIND_SHADER_RESOURCE;
    }

    return ResultFlags;
}


ID3D11RenderTargetView* Dx11GraphicsAPI::CreateBackBufferRT_internal(IDXGISwapChain* swapChain)
{
    ID3D11Texture2D* ResultTextureRt = nullptr;

    ID3D11RenderTargetView* ResultRT = nullptr;

    if ( swapChain != nullptr && m_device != nullptr)
    {
        if (SUCCEEDED(swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&ResultTextureRt))))
        {
            m_device->CreateRenderTargetView(ResultTextureRt, nullptr, &ResultRT);
        }
    }
    SAFE_RELEASE(ResultTextureRt);
   
    return ResultRT;
}

ID3D11DepthStencilView* Dx11GraphicsAPI::CreateDepthStencilView_internal(ID3D11Texture2D* texture)
{
    D3D11_TEXTURE2D_DESC TextureDesc = {};

    ID3D11DepthStencilView* ResultDepthStencilView = nullptr;

    if (texture != nullptr)
    {
        texture->GetDesc(&TextureDesc);

        if ((TextureDesc.BindFlags & D3D11_BIND_FLAG::D3D11_BIND_DEPTH_STENCIL) != 0)
        {
            D3D11_DEPTH_STENCIL_VIEW_DESC descDSV = {};
            descDSV.Format = TextureDesc.Format;
            descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
            descDSV.Texture2D.MipSlice = 0;

            m_device->CreateDepthStencilView(texture, &descDSV, &ResultDepthStencilView);
        }
    }

    // Wrap the raw D3D resource into the Dx11 depth-stencil object (same pattern as buffer creators)
    return ResultDepthStencilView;
}

IDXGISwapChain* Dx11GraphicsAPI::CreateSwapChain_Internal(HWND hwnd, uint32_t width, uint32_t height, GAPI_FORMAT::K format)
{
    IDXGIFactory1* dxgiFactory1 = nullptr;

    IDXGIFactory2* dxgiFactory2 = nullptr;

    IDXGIDevice* dxgiDevice = nullptr;

    IDXGIAdapter* adapter = nullptr;

    IDXGISwapChain1* swapChain1 = nullptr;

    IDXGISwapChain* ResultSwapChain = nullptr;

    if (SUCCEEDED(m_device->QueryInterface(__uuidof(IDXGIDevice), reinterpret_cast<void**>(&dxgiDevice))))
    {
        if (SUCCEEDED(dxgiDevice->GetAdapter(&adapter)))
        {
            if (adapter->GetParent(__uuidof(IDXGIFactory1), reinterpret_cast<void**>(&dxgiFactory1)))
            {
                if (dxgiFactory1->QueryInterface(__uuidof(IDXGIFactory2), reinterpret_cast<void**>(&dxgiFactory2)))
                {

                    DXGI_SWAP_CHAIN_DESC1 sd = {};
                    sd.Width = width;
                    sd.Height = height;
                    sd.Format = GetDX11Format_internal(format);
                    sd.SampleDesc.Count = 1;
                    sd.SampleDesc.Quality = 0;
                    sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
                    sd.BufferCount = 1;


                    if (SUCCEEDED(dxgiFactory2->CreateSwapChainForHwnd(m_device, hwnd, &sd, nullptr, nullptr, &swapChain1)))
                    {
                        swapChain1->QueryInterface(__uuidof(IDXGISwapChain), reinterpret_cast<void**>(&ResultSwapChain));
                    }
                }
                else
                {
                    DXGI_SWAP_CHAIN_DESC sd = {};
                    sd.BufferCount = 1;
                    sd.BufferDesc.Width = width;
                    sd.BufferDesc.Height = height;
                    sd.BufferDesc.Format = GetDX11Format_internal(format);
                    sd.BufferDesc.RefreshRate.Numerator = 60;
                    sd.BufferDesc.RefreshRate.Denominator = 1;
                    sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
                    sd.OutputWindow = hwnd;
                    sd.SampleDesc.Count = 1;
                    sd.SampleDesc.Quality = 0;
                    sd.Windowed = TRUE;


                    dxgiFactory1->CreateSwapChain(m_device, &sd, &ResultSwapChain);
                }

                dxgiFactory1->MakeWindowAssociation(hwnd, DXGI_MWA_NO_ALT_ENTER);
            }
        }
    }

    SAFE_RELEASE(dxgiFactory1);
    SAFE_RELEASE(dxgiFactory2);
    SAFE_RELEASE(dxgiDevice);
    SAFE_RELEASE(adapter);
    SAFE_RELEASE(swapChain1);

    return ResultSwapChain;
}

    const char* GetShaderModel_internal(SHADER_TYPE::K shaderType, uint32_t shaderModel)
    {
        std::string ResultShader;
    
        std::string modelVersion = std::to_string(shaderModel) + "_0";
    
        switch (shaderType)
        {
        case SHADER_TYPE::K::VERTEX_SHADER:
            ResultShader = "vs_" + modelVersion;
            break;
        
        case SHADER_TYPE::K::PIXEL_SHADER:
            ResultShader = "ps_" + modelVersion;
            break;
        
        default:
            ResultShader = "vs_4_0";
            break;
        }
    
        return ResultShader.c_str();
    }


ID3D11Texture2D* Dx11GraphicsAPI::CreateTexture2D_internal(uint32_t width, uint32_t height, const GAPI_FORMAT::K format, uint32_t bindFlags)
{
    assert(width != 0 && height != 0 && format != GAPI_FORMAT::FORMAT_UNKNOWN);

    // Describe the depth-stencil texture
    D3D11_TEXTURE2D_DESC descTexture = {};
    descTexture.Width = width;
    descTexture.Height = height;
    descTexture.MipLevels = 1;
    descTexture.ArraySize = 1;
    descTexture.Format = GetDX11Format_internal(format);
    descTexture.SampleDesc.Count = 1;
    descTexture.SampleDesc.Quality = 0;
    descTexture.Usage = D3D11_USAGE_DEFAULT;
    descTexture.BindFlags = GetDx11BindFlag_internal(bindFlags);
    descTexture.CPUAccessFlags = 0;
    descTexture.MiscFlags = 0;

    ID3D11Texture2D* ResultTexture = nullptr;
    m_device->CreateTexture2D(&descTexture, nullptr, &ResultTexture);

    return ResultTexture;
}

ID3DBlob* Dx11GraphicsAPI:: CompileShader_internal(const std::string & shaderCode, const std::string & entrypoint, std::vector<std::string> Defines, SHADER_TYPE::K shaderType)
{
    if (!shaderCode.empty() && !entrypoint.empty())
    {

        std::string FinalShaderCode;

        ID3DBlob* ErrorBlob = nullptr;
        ID3DBlob* BinaryBlob = nullptr;

        uint32_t dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
#ifdef _DEBUG
        // Set the D3DCOMPILE_DEBUG flag to embed debug information in the shaders.
        // Setting this flag improves the shader debugging experience, but still allows 
        // the shaders to be optimized and to run exactly the way they will run in 
        // the release configuration of this program.
        dwShaderFlags |= D3DCOMPILE_DEBUG;

        // Disable optimizations to further improve shader debugging
        dwShaderFlags |= D3DCOMPILE_SKIP_OPTIMIZATION;
#endif

        for (auto& macro : Defines)
        {
            FinalShaderCode += (macro + "/n");
        }

        FinalShaderCode += shaderCode;

        if (D3DCompile(FinalShaderCode.c_str(), sizeof(char) * FinalShaderCode.length(), nullptr, nullptr, nullptr,
            entrypoint.c_str(), GetShaderModel_internal(SHADER_TYPE::K::VERTEX_SHADER , m_shaderModel), dwShaderFlags, 0, &BinaryBlob, &ErrorBlob))
        {
            return BinaryBlob;
        }
        std::cout << reinterpret_cast<const char*>(ErrorBlob->GetBufferPointer()) << std::endl;
        SAFE_RELEASE(ErrorBlob);
    }
}

Dx11GraphicsAPI::Dx11GraphicsAPI()
	:m_device(nullptr),m_immediateContext(nullptr)
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
    IDXGIFactory1* dxgiFactory1 = nullptr;
    {
        IDXGIDevice* dxgiDevice = nullptr;
        hr = m_device->QueryInterface(__uuidof(IDXGIDevice), reinterpret_cast<void**>(&dxgiDevice));
        if (SUCCEEDED(hr))
        {
            IDXGIAdapter* adapter = nullptr;
            hr = dxgiDevice->GetAdapter(&adapter);
            if (SUCCEEDED(hr))
            {
                hr = adapter->GetParent(__uuidof(IDXGIFactory1), reinterpret_cast<void**>(&dxgiFactory1));
                adapter->Release();
            }
            dxgiDevice->Release();
        }
    }
   assert (!FAILED(hr));

   m_shaderModel = 4;

}

Dx11GraphicsAPI::~Dx11GraphicsAPI()
{
	CleanUpResources();
}

void Dx11GraphicsAPI::CleanUpResources()
{
    
    SAFE_RELEASE(m_immediateContext);
    SAFE_RELEASE(m_device);
}

std::shared_ptr<SwapChain> Dx11GraphicsAPI::CreateSwapChain(HWND hwnd, uint32_t width , uint32_t height, GAPI_FORMAT::K format)
{
    std::shared_ptr <Dx11SwapChain> SChain = nullptr;

    if (auto* ResultSwapChain = CreateSwapChain_Internal(hwnd, width, height, format))
    {
        if (auto * ResultRT = CreateBackBufferRT_internal(ResultSwapChain))
        {
            SChain = std::make_shared<Dx11SwapChain>();

            SChain->m_BackBUfferRT = ResultRT;

            SChain->m_swapChain = ResultSwapChain;
        }
    }
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

    auto buffer = std::make_shared<Dx11ConstantBuffer>();
    buffer->m_buffer = Rawbuffer;
    buffer->SetByteWidth(bytewidth);
    buffer->SetSlot(slot); /// Cambio mas restrictivo el uso de info

    ASSIGN_DEBUG_NAME(buffer.get(), Rawbuffer);
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

void Dx11GraphicsAPI::SetConstantBuffer(std::weak_ptr<ConstantBuffer> buffer)
{
    if (m_immediateContext == nullptr || buffer.expired())
    {
        return;
    }
    auto pbuffer = std::static_pointer_cast<Dx11ConstantBuffer>(buffer.lock());

    if (pbuffer == nullptr || pbuffer->m_buffer == nullptr || pbuffer->GetSlot() >= HIGHER_AVAILABLE_SLOT)
    {
        return;
    }

    m_immediateContext->VSSetConstantBuffers(pbuffer->GetSlot(), 1, &pbuffer->m_buffer);
    m_immediateContext->PSSetConstantBuffers(pbuffer->GetSlot(), 1, &pbuffer->m_buffer);
}

void Dx11GraphicsAPI::UpdateConstantBuffer(std::weak_ptr<ConstantBuffer> buffer, const uint32_t bytewidth, void* Data)
{

    if (m_immediateContext == nullptr || buffer.expired() || Data == nullptr)
    {
        return;
    }
    auto pbuffer = std::static_pointer_cast<Dx11ConstantBuffer> (buffer.lock());

    if (pbuffer == nullptr || pbuffer->m_buffer == nullptr || pbuffer->GetByteWidth() != bytewidth)
    {
        return;
    }

    m_immediateContext->UpdateSubresource(pbuffer->m_buffer, 0, nullptr, Data, 0, 0);
}

std::shared_ptr<Topology> Dx11GraphicsAPI::CreateTopology(Topology::Type type)
{
    auto topo = std::make_shared<Dx11Topology>();
    // set base type and DX primitive accordingly
    topo->SetType(type);

    switch (type)
    {
    case Topology::Type::TriangleList:
        topo-> m_dx11Topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
        break;
    case Topology::Type::TriangleStrip:
        topo-> m_dx11Topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP;
        break;
    case Topology::Type::LineList:
        topo->m_dx11Topology = D3D11_PRIMITIVE_TOPOLOGY_LINELIST;
        break;
    case Topology::Type::PointList:
        topo->m_dx11Topology = D3D11_PRIMITIVE_TOPOLOGY_POINTLIST;
        break;
    default:
        topo->m_dx11Topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
        break;
    }

    return topo;
}

void Dx11GraphicsAPI::SetTopology(std::weak_ptr<Topology> topology)
{
    if (m_immediateContext == nullptr || topology.expired())
    {
        return;
    }

    auto ptopo = std::static_pointer_cast<Dx11Topology>(topology.lock());
    if (ptopo == nullptr)
    {
        return;
    }

    m_immediateContext->IASetPrimitiveTopology(ptopo->m_dx11Topology);
}

std::shared_ptr<CommandBuffer> Dx11GraphicsAPI::CreateCommandBuffer()
{
    assert(m_device != nullptr);

    ID3D11DeviceContext* context = nullptr;

    if (FAILED(m_device->CreateDeferredContext(0, &context)))
    {
        return nullptr;
    }
    auto Buffer = std::make_shared<Dx11CommandBuffer>();

    Buffer->m_context = context;

    return Buffer;
}

void Dx11GraphicsAPI::DispatchCommandBufer(std::weak_ptr<CommandBuffer> buffer)
{
    if (m_immediateContext == nullptr || buffer.expired())
    {
        return;
    }
    auto cmdBuffer = std::static_pointer_cast<Dx11CommandBuffer>(buffer.lock());
    if (cmdBuffer == nullptr || cmdBuffer->m_commandList == nullptr)
    {
        return;
    }
	m_immediateContext->ExecuteCommandList(cmdBuffer->m_commandList, FALSE);
}

void Dx11GraphicsAPI::RenderPass(std::weak_ptr<Pass> pase)
{
    if (m_immediateContext == nullptr || pase.expired())
    {
        return;
	}

    auto pPass = pase.lock();

    if (pPass->m_commandBuffer == nullptr)
    {
        return;
	}

	auto pBuffer = std::static_pointer_cast<Dx11CommandBuffer>(pPass->m_commandBuffer);

    if (pBuffer == nullptr)
    {
        return;
    }

    pBuffer->RecordCommandList();

    if (pBuffer->m_commandList == nullptr)
    {
        return;
	}

	m_immediateContext->ExecuteCommandList(pBuffer->m_commandList, FALSE);
}

std::shared_ptr<Pass> Dx11GraphicsAPI::CreatePass()
{
    auto pass = std::make_shared<Pass>();

    auto cmdBuffer = CreateCommandBuffer();
    if (cmdBuffer)
    {
        cmdBuffer->BeginCommandBuffer();
        pass->m_commandBuffer = cmdBuffer;
    }

    return pass;
}


std::shared_ptr<VertexShader> Dx11GraphicsAPI::CreateVertexShader(const std::string& shaderCode, const std::string& entrypoint, std::vector<std::string> Defines)
{
    ID3DBlob* BinaryBlob = nullptr;

    ID3D11VertexShader* ResultShader = nullptr;

   BinaryBlob = CompileShader_internal(shaderCode, entrypoint, Defines, SHADER_TYPE::K::VERTEX_SHADER);
        
   if (BinaryBlob != nullptr)
   {
       ID3D11VertexShader* shader = nullptr;
       HRESULT hr = m_device->CreateVertexShader(BinaryBlob, BinaryBlob->GetBufferSize(), nullptr, &ResultShader);
       assert(SUCCEEDED(hr));

       auto shaderPtr = std::make_shared<Dx11VertexShader>();
       shaderPtr->m_shader = ResultShader;
    
       return shaderPtr;
   }
}

std::shared_ptr<PixelShader> Dx11GraphicsAPI::CreatePixelShader(const std::string& shaderCode, const std::string& entrypoint, std::vector<std::string> Defines)
{
    ID3DBlob* BinaryBlob = nullptr;

    ID3D11PixelShader* ResultShader = nullptr;

    BinaryBlob = CompileShader_internal(shaderCode, entrypoint, Defines, SHADER_TYPE::K::PIXEL_SHADER);

    if (BinaryBlob != nullptr)
    {
        ID3D11PixelShader* shader = nullptr;
        HRESULT hr = m_device->CreatePixelShader(BinaryBlob, BinaryBlob->GetBufferSize(), nullptr, &ResultShader);
        assert(SUCCEEDED(hr));

        auto shaderPtr = std::make_shared<Dx11PixelShader>();
        shaderPtr->m_shader = ResultShader;

        return shaderPtr;
    }
}

void Dx11GraphicsAPI::SetVertexShader(std::weak_ptr<VertexShader> shader)
{
}


std::shared_ptr<DepthStencilView> Dx11GraphicsAPI::CreateDepthStencil(uint32_t width, uint32_t height, const GAPI_FORMAT::K format)
{
    
    std::shared_ptr<Dx11DepthStencilView> ResultStencil = nullptr;

    if (width != 0 && height != 0 && format != GAPI_FORMAT::FORMAT_UNKNOWN)
    {
        if (auto* Texture2D = CreateTexture2D_internal(width, height, format, GAPI_BIND_FLAGS::DEPTH_STENCIL))
        {
            if (auto * DepthStencilView = CreateDepthStencilView_internal(Texture2D))
            { 
                SAFE_RELEASE(Texture2D);

                ResultStencil = std::make_shared<Dx11DepthStencilView>();

                ResultStencil->m_depthStencilView = DepthStencilView;
            }
        }
    }
    return ResultStencil;
}

void Dx11GraphicsAPI::CreateRenderTarget()
{
    //m_immediateContext->OMSetRenderTargets(1, &g_pRenderTargetView, nullptr);


    //DXGI_SWAP_CHAIN_DESC scDesc = {};
    //if (SUCCEEDED(m_swapChain->GetDesc(&scDesc)))
    //{
    //    D3D11_VIEWPORT vp = {};
    //    vp.TopLeftX = 0.0f;
    //    vp.TopLeftY = 0.0f;
    //    vp.Width = static_cast<FLOAT>(scDesc.BufferDesc.Width);
    //    vp.Height = static_cast<FLOAT>(scDesc.BufferDesc.Height);
    //    vp.MinDepth = 0.0f;
    //    vp.MaxDepth = 1.0f;
    //    m_immediateContext->RSSetViewports(1, &vp);
    //}
}

void Dx11GraphicsAPI::SetRenderTarget(const std::weak_ptr<DepthStencilView>& depthStencil)
{

}

std::shared_ptr<ViewPort> Dx11GraphicsAPI::CreateViewPort(float width, float height, float minDepth, float maxDepth, float topLeftX, float topLeftY)
{
    std::shared_ptr<Dx11ViewPort> ResultVP = nullptr;

    ResultVP->m_ViewPort->Width = width;
    ResultVP->m_ViewPort->Height = height;
    ResultVP->m_ViewPort->MinDepth = minDepth;
    ResultVP->m_ViewPort->MaxDepth = maxDepth;
    ResultVP->m_ViewPort->TopLeftX = topLeftX;
    ResultVP->m_ViewPort->TopLeftY = topLeftY;

    return ResultVP;

}


HRESULT Dx11GraphicsAPI::CompileShaderFromFile(const WCHAR* szFileName, const char* szEntryPoint, const char* szShaderModel, ID3DBlob** ppBlobOut)
{
    HRESULT hr = S_OK;

    DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
#ifdef _DEBUG
    // Set the D3DCOMPILE_DEBUG flag to embed debug information in the shaders.
    // Setting this flag improves the shader debugging experience, but still allows 
    // the shaders to be optimized and to run exactly the way they will run in 
    // the release configuration of this program.
    dwShaderFlags |= D3DCOMPILE_DEBUG;

    // Disable optimizations to further improve shader debugging
    dwShaderFlags |= D3DCOMPILE_SKIP_OPTIMIZATION;
#endif

    ID3DBlob* pErrorBlob = nullptr;
    hr = D3DCompileFromFile(szFileName, nullptr, nullptr, szEntryPoint, szShaderModel,
        dwShaderFlags, 0, ppBlobOut, &pErrorBlob);
    if (FAILED(hr))
    {
        if (pErrorBlob)
        {
            OutputDebugStringA(reinterpret_cast<const char*>(pErrorBlob->GetBufferPointer()));
            pErrorBlob->Release();
        }
        return hr;
    }
    if (pErrorBlob) pErrorBlob->Release();

    return S_OK;
}
