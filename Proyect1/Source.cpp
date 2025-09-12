//--------------------------------------------------------------------------------------
// File: Tutorial07.cpp
//
// This application demonstrates texturing
//
// http://msdn.microsoft.com/en-us/library/windows/apps/ff729724.aspx
//
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Copyright (c) Microsoft Corporation.
// Licensed under the MIT License (MIT).
//--------------------------------------------------------------------------------------
#include <windows.h>
#include <d3d11_1.h>
#include <d3dcompiler.h>
#include <directxmath.h>
#include <directxcolors.h>

#include <iostream>

//#include "DDSTextureLoader.h"
#include "resource.h"

#include "GraphicsAPI.h"
#include "ConstantBuffer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Shader.h"

#include <imgui.h>
#include <imgui_impl_win32.h>
#include <imgui_impl_dx11.h>

#include "Camera.h"

using namespace DirectX;

//--------------------------------------------------------------------------------------
// Structures
//--------------------------------------------------------------------------------------
struct SimpleVertex
{
    XMFLOAT3 Pos;
    XMFLOAT2 Tex;
};

struct CBNeverChanges
{
    XMMATRIX mView;
};

struct CBChangeOnResize
{
    XMMATRIX mProjection;
};

struct CBChangesEveryFrame
{
    XMMATRIX mWorld;
    XMFLOAT4 vMeshColor;
};


//--------------------------------------------------------------------------------------
// Global Variables
//--------------------------------------------------------------------------------------

//____IMGUI camera variables ____
XMVECTOR g_Eye = XMVectorSet(0.0f, 3.0f, -6.0f, 0.0f);
static float g_cameraEye[3] = { 0.0f, 3.0f,-6.0f };
static float g_cameraAt[3] = { 0.0f, 1.0f , 0.0f };
//___ Camera ___
Camera g_Camera;
Camera ShadowCamera;
//___ GAPI___

std::shared_ptr<Dx11GraphicsAPI> GAPI = nullptr;

std::weak_ptr<ConstantBuffer> ConstBuffer;

std::weak_ptr <IndexBuffer>INDXBuffer;

std::weak_ptr<VertexBuffer> VrtxBuffer;

std::weak_ptr<ConstantBuffer>GA_changeEveryFrame;

std::weak_ptr<ConstantBuffer> GAPI_ChangeonResize;

std::weak_ptr<PixelShader> GAPI_pixelShader;

//std::weak_ptr<VertexShader> GAPI_vertexShader;

HINSTANCE                           g_hInst = nullptr;
HWND                                g_hWnd = nullptr;
D3D_DRIVER_TYPE                     g_driverType = D3D_DRIVER_TYPE_NULL;
D3D_FEATURE_LEVEL                   g_featureLevel = D3D_FEATURE_LEVEL_11_0;
ID3D11RenderTargetView* g_pRenderTargetView = nullptr;
ID3D11Texture2D* g_pDepthStencil = nullptr;
ID3D11DepthStencilView* g_pDepthStencilView = nullptr;
ID3D11VertexShader* g_pVertexShader = nullptr;
//ID3D11PixelShader* g_pPixelShader = nullptr;
ID3D11InputLayout* g_pVertexLayout = nullptr;
ID3D11ShaderResourceView* g_pTextureRV = nullptr;
ID3D11SamplerState* g_pSamplerLinear = nullptr;
XMMATRIX                            g_World;
XMMATRIX                            g_View;
XMMATRIX                            g_Projection;
XMFLOAT4                            g_vMeshColor(0.7f, 0.7f, 0.7f, 1.0f);

static const int meshes = 10000;
XMMATRIX                            MeshWoldTransform[meshes];

//--------------------------------------------------------------------------------------
// Forward declarations
//--------------------------------------------------------------------------------------
HRESULT InitWindow(HINSTANCE hInstance, int nCmdShow);
HRESULT InitDevice();
void CleanupDevice();
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
void Render();

// Forward declare message handler from imgui_impl_win32.cpp
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

//--------------------------------------------------------------------------------------
// Entry point to the program. Initializes everything and goes into a message processing 
// loop. Idle time is used to render the scene.
//--------------------------------------------------------------------------------------
int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    if (FAILED(InitWindow(hInstance, nCmdShow)))
        return 0;

    if (FAILED(InitDevice()))
    {
        CleanupDevice();
        return 0;
    }

    // Main message loop
    MSG msg = { 0 };
    while (WM_QUIT != msg.message)
    {
        if (ImGui_ImplWin32_WndProcHandler(g_hWnd, msg.message, msg.wParam, msg.lParam))
            return true;

        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else
        {
            Render();
        }
    }

    CleanupDevice();

    return (int)msg.wParam;
}


//--------------------------------------------------------------------------------------
// Register class and create window
//--------------------------------------------------------------------------------------
HRESULT InitWindow(HINSTANCE hInstance, int nCmdShow)
{
    // Register class
    WNDCLASSEX wcex;
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, (LPCTSTR)IDI_TUTORIAL1);
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = nullptr;
    wcex.lpszClassName = L"TutorialWindowClass";
    wcex.hIconSm = LoadIcon(wcex.hInstance, (LPCTSTR)IDI_TUTORIAL1);
    if (!RegisterClassEx(&wcex))
        return E_FAIL;

    // Create window
    g_hInst = hInstance;
    RECT rc = { 0, 0, 800, 600 };
    AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);
    g_hWnd = CreateWindow(L"TutorialWindowClass", L"Direct3D 11 Tutorial 7",
        WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
        CW_USEDEFAULT, CW_USEDEFAULT, rc.right - rc.left, rc.bottom - rc.top, nullptr, nullptr, hInstance,
        nullptr);
    if (!g_hWnd)
        return E_FAIL;

    ShowWindow(g_hWnd, nCmdShow);

    return S_OK;
}


//--------------------------------------------------------------------------------------
// Helper for compiling shaders with D3DCompile
//
// With VS 11, we could load up prebuilt .cso files instead...
//--------------------------------------------------------------------------------------
HRESULT CompileShaderFromFile(const WCHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut)
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



//--------------------------------------------------------------------------------------
// Create Direct3D device and swap chain
//--------------------------------------------------------------------------------------
HRESULT InitDevice()
{
    HRESULT hr = S_OK;

    RECT rc;
    GetClientRect(g_hWnd, &rc);
    UINT width = rc.right - rc.left;
    UINT height = rc.bottom - rc.top;
    
GAPI = std::make_shared <Dx11GraphicsAPI>(g_hWnd);

    // Create a render target view
    ID3D11Texture2D* pBackBuffer = nullptr;
    hr = GAPI->m_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&pBackBuffer));
    if (FAILED(hr))
        return hr;

    hr = GAPI->m_device->CreateRenderTargetView(pBackBuffer, nullptr, &g_pRenderTargetView);
    pBackBuffer->Release();
    if (FAILED(hr))
        return hr;


    ///create texture
    // Create depth stencil texture
    D3D11_TEXTURE2D_DESC descDepth = {};
    descDepth.Width = width;
    descDepth.Height = height;
    descDepth.MipLevels = 1;
    descDepth.ArraySize = 1;
    descDepth.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
    descDepth.SampleDesc.Count = 1;
    descDepth.SampleDesc.Quality = 0;
    descDepth.Usage = D3D11_USAGE_DEFAULT;
    descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;
    descDepth.CPUAccessFlags = 0;
    descDepth.MiscFlags = 0;
    hr = GAPI->m_device->CreateTexture2D(&descDepth, nullptr, &g_pDepthStencil);
    if (FAILED(hr))
        return hr;

    // Create the depth stencil view
    D3D11_DEPTH_STENCIL_VIEW_DESC descDSV = {};
    descDSV.Format = descDepth.Format;
    descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
    descDSV.Texture2D.MipSlice = 0;
    hr = GAPI->m_device->CreateDepthStencilView(g_pDepthStencil, &descDSV, &g_pDepthStencilView);
    if (FAILED(hr))
        return hr;

    GAPI->m_immediateContext->OMSetRenderTargets(1, &g_pRenderTargetView, g_pDepthStencilView);

    // Setup the viewport
    D3D11_VIEWPORT vp;
    vp.Width = (FLOAT)width;
    vp.Height = (FLOAT)height;
    vp.MinDepth = 0.0f;
    vp.MaxDepth = 1.0f;
    vp.TopLeftX = 0;
    vp.TopLeftY = 0;
    GAPI->m_immediateContext ->RSSetViewports(1, &vp);

    // Compile the vertex shader
    ID3DBlob* pVSBlob = nullptr;
    hr = CompileShaderFromFile(L"Tutorial07.fxh", "VS", "vs_4_0", &pVSBlob);
    if (FAILED(hr))
    {
        MessageBox(nullptr,
            L"The FX file cannot be compiled.  Please run this executable from the directory that contains the FX file.", L"Error", MB_OK);
        return hr;
    }

	//GAPI_vertexShader = GAPI->CreateVertexShader(static_cast<uint32_t>(pVSBlob->GetBufferSize()), pVSBlob->GetBufferPointer(), nullptr, 0, 0);
    //// Create the vertex shader
    hr = GAPI->m_device->CreateVertexShader(pVSBlob->GetBufferPointer(), pVSBlob->GetBufferSize(), nullptr, &g_pVertexShader);
    if (FAILED(hr))
    {
        pVSBlob->Release();
        return hr;
    }

    // Define the input layout
    D3D11_INPUT_ELEMENT_DESC layout[] =
    {
        { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
    };
    UINT numElements = ARRAYSIZE(layout);

    // Create the input layout
    hr = GAPI->m_device->CreateInputLayout(layout, numElements, pVSBlob->GetBufferPointer(),
        pVSBlob->GetBufferSize(), &g_pVertexLayout);
    pVSBlob->Release();
    if (FAILED(hr))
        return hr;

    // Set the input layout
    GAPI->m_immediateContext->IASetInputLayout(g_pVertexLayout);

    // Compile the pixel shader
    ID3DBlob* pPSBlob = nullptr;
    hr = CompileShaderFromFile(L"Tutorial07.fxh", "PS", "ps_4_0", &pPSBlob);
    if (FAILED(hr))
    {
        MessageBox(nullptr,
            L"The FX file cannot be compiled.  Please run this executable from the directory that contains the FX file.", L"Error", MB_OK);
        return hr;
    }

    // Create the pixel shader
	GAPI_pixelShader = GAPI->CreatePixelShader(static_cast<uint32_t>(pPSBlob->GetBufferSize()), 0, 0);

    //hr = GAPI->m_device->CreatePixelShader(pPSBlob->GetBufferPointer(), pPSBlob->GetBufferSize(), nullptr, &g_pPixelShader);
    pPSBlob->Release();
    if (FAILED(hr))
        return hr;

    // Create vertex buffer
    SimpleVertex vertices[] =
    {
        { XMFLOAT3(-1.0f, 1.0f, -1.0f), XMFLOAT2(1.0f, 0.0f) },
        { XMFLOAT3(1.0f, 1.0f, -1.0f), XMFLOAT2(0.0f, 0.0f) },
        { XMFLOAT3(1.0f, 1.0f, 1.0f), XMFLOAT2(0.0f, 1.0f) },
        { XMFLOAT3(-1.0f, 1.0f, 1.0f), XMFLOAT2(1.0f, 1.0f) },

        { XMFLOAT3(-1.0f, -1.0f, -1.0f), XMFLOAT2(0.0f, 0.0f) },
        { XMFLOAT3(1.0f, -1.0f, -1.0f), XMFLOAT2(1.0f, 0.0f) },
        { XMFLOAT3(1.0f, -1.0f, 1.0f), XMFLOAT2(1.0f, 1.0f) },
        { XMFLOAT3(-1.0f, -1.0f, 1.0f), XMFLOAT2(0.0f, 1.0f) },

        { XMFLOAT3(-1.0f, -1.0f, 1.0f), XMFLOAT2(0.0f, 1.0f) },
        { XMFLOAT3(-1.0f, -1.0f, -1.0f), XMFLOAT2(1.0f, 1.0f) },
        { XMFLOAT3(-1.0f, 1.0f, -1.0f), XMFLOAT2(1.0f, 0.0f) },
        { XMFLOAT3(-1.0f, 1.0f, 1.0f), XMFLOAT2(0.0f, 0.0f) },

        { XMFLOAT3(1.0f, -1.0f, 1.0f), XMFLOAT2(1.0f, 1.0f) },
        { XMFLOAT3(1.0f, -1.0f, -1.0f), XMFLOAT2(0.0f, 1.0f) },
        { XMFLOAT3(1.0f, 1.0f, -1.0f), XMFLOAT2(0.0f, 0.0f) },
        { XMFLOAT3(1.0f, 1.0f, 1.0f), XMFLOAT2(1.0f, 0.0f) },

        { XMFLOAT3(-1.0f, -1.0f, -1.0f), XMFLOAT2(0.0f, 1.0f) },
        { XMFLOAT3(1.0f, -1.0f, -1.0f), XMFLOAT2(1.0f, 1.0f) },
        { XMFLOAT3(1.0f, 1.0f, -1.0f), XMFLOAT2(1.0f, 0.0f) },
        { XMFLOAT3(-1.0f, 1.0f, -1.0f), XMFLOAT2(0.0f, 0.0f) },

        { XMFLOAT3(-1.0f, -1.0f, 1.0f), XMFLOAT2(1.0f, 1.0f) },
        { XMFLOAT3(1.0f, -1.0f, 1.0f), XMFLOAT2(0.0f, 1.0f) },
        { XMFLOAT3(1.0f, 1.0f, 1.0f), XMFLOAT2(0.0f, 0.0f) },
        { XMFLOAT3(-1.0f, 1.0f, 1.0f), XMFLOAT2(1.0f, 0.0f) },
    };

    D3D11_BUFFER_DESC bd = {};
    bd.Usage = D3D11_USAGE_DEFAULT;
    bd.ByteWidth = sizeof(SimpleVertex) * 24;
    bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    bd.CPUAccessFlags = 0;

    D3D11_SUBRESOURCE_DATA InitData = {};
    InitData.pSysMem = vertices;
    //hr = GAPI->m_device->CreateBuffer(&bd, &InitData, &g_pVertexBuffer);

    VrtxBuffer = GAPI->CreateVertexBuffer(sizeof(SimpleVertex) * 24, vertices, sizeof(SimpleVertex));
    if (VrtxBuffer.expired()) {
        std::cout << "Error: VertexBuffer no creado correctamente" << std::endl;
        return E_FAIL;
    }

    ///Create vertex buffer


    // Set vertex buffer
    UINT stride = sizeof(SimpleVertex);
    UINT offset = 0;
    std::shared_ptr<VertexBuffer> sharedVrtxBuffer = VrtxBuffer.lock();
    if (sharedVrtxBuffer)
    {
        auto dx11VrtxBuffer = std::static_pointer_cast<Dx11VertexBuffer>(sharedVrtxBuffer);
        ID3D11Buffer* buffer = dx11VrtxBuffer->m_buffer;

        GAPI->m_immediateContext->IASetVertexBuffers(0, 1, &buffer, &stride, &offset);
    }


    //GAPI->m_immediateContext->IASetVertexBuffers(0, 1, &g_pVertexBuffer, &stride, &offset);

    // Create index buffer
    // Create vertex buffer
    WORD indices[] =
    {
        3,1,0,
        2,1,3,

        6,4,5,
        7,4,6,

        11,9,8,
        10,9,11,

        14,12,13,
        15,12,14,

        19,17,16,
        18,17,19,

        22,20,21,
        23,20,22
    };
    //D3D11_BUFFER_DESC bd = {};
    bd.Usage = D3D11_USAGE_DEFAULT;
    bd.ByteWidth = sizeof(WORD) * 36;
    bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
    bd.CPUAccessFlags = 0;
    InitData.pSysMem = indices;
    //hr = GAPI->m_device->CreateBuffer(&bd, &InitData, & g_pIndexBuffer);
    INDXBuffer = GAPI->CreateIndexBuffer(sizeof(WORD)* 36 , indices, 36);
    if (FAILED(hr))
        return hr;

    // Set index buffer
    //GAPI->m_immediateContext->IASetIndexBuffer(g_pIndexBuffer, DXGI_FORMAT_R16_UINT, 0);
    auto SharedINDXBuffer = INDXBuffer.lock();
    if (!SharedINDXBuffer) {
        std::cout << "Error: IndexBuffer no creado correctamente" << std::endl;
        return E_FAIL;
    }
    auto dx11IndexBuffer = std::dynamic_pointer_cast<Dx11IndexBuffer>(SharedINDXBuffer);
    if (!dx11IndexBuffer) {
        std::cout << "Error: No se pudo castear a Dx11IndexBuffer" << std::endl;
        return E_FAIL;
    }
    GAPI->m_immediateContext->IASetIndexBuffer(dx11IndexBuffer->m_buffer, DXGI_FORMAT_R16_UINT, 0);



    // Set primitive topology
    GAPI->m_immediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

      ConstBuffer = GAPI->CreateConstanBuffer(sizeof(CBNeverChanges), nullptr, 0);

    GAPI_ChangeonResize = GAPI->CreateConstanBuffer(sizeof(CBChangeOnResize), nullptr, 0);

    GA_changeEveryFrame = GAPI->CreateConstanBuffer(sizeof(CBChangesEveryFrame), nullptr, 0);

    // Create the sample state
    D3D11_SAMPLER_DESC sampDesc = {};
    sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
    sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
    sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
    sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
    sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
    sampDesc.MinLOD = 0;
    sampDesc.MaxLOD = D3D11_FLOAT32_MAX;
    hr = GAPI->m_device->CreateSamplerState(&sampDesc, &g_pSamplerLinear);
    if (FAILED(hr))
        return hr;

    // Initialize the world matrices
    g_World = XMMatrixIdentity();

    // Initialize the view matrix
    //g_Eye = XMVectorSet(0.0f, 3.0f, -6.0f, 0.0f);
    //XMVECTOR At = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
    //XMVECTOR Up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
    //g_View = XMMatrixLookAtLH(g_Eye, At, Up);

      g_View = XMMatrixLookAtLH(g_Camera.GetEye(),g_Camera.GetAt(),g_Camera.GetUp());


    CBNeverChanges cbNeverChanges;
    cbNeverChanges.mView = XMMatrixTranspose(g_View);

    if (!ConstBuffer.expired())
    {
        auto pConstanBuffer = std::static_pointer_cast<Dx11ConstantBuffer> (ConstBuffer.lock());
    GAPI->m_immediateContext->UpdateSubresource(pConstanBuffer->m_buffer, 0, nullptr, &cbNeverChanges, 0, 0);
    }

    // Initialize the projection matrix
    g_Projection = XMMatrixPerspectiveFovLH(XM_PIDIV4, width / (FLOAT)height, 0.01f, 100.0f);

    CBChangeOnResize cbChangesOnResize;
    cbChangesOnResize.mProjection = XMMatrixTranspose(g_Projection);
    if (!GAPI_ChangeonResize.expired())
    {
        auto AutochangeonREsize = std::static_pointer_cast<Dx11ConstantBuffer>(GAPI_ChangeonResize.lock());
        GAPI->m_immediateContext->UpdateSubresource(AutochangeonREsize->m_buffer, 0, nullptr, &cbChangesOnResize, 0, 0);
    }

    ImGui_ImplWin32_EnableDpiAwareness();
    float main_scale = ImGui_ImplWin32_GetDpiScaleForMonitor(::MonitorFromPoint(POINT{ 0, 0 }, MONITOR_DEFAULTTOPRIMARY));


    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsLight();

    // Setup scaling
    ImGuiStyle& style = ImGui::GetStyle();
    style.ScaleAllSizes(main_scale);        // Bake a fixed style scale. (until we have a solution for dynamic style scaling, changing this requires resetting Style + calling this again)
    style.FontScaleDpi = main_scale;        // Set initial font scale. (using io.ConfigDpiScaleFonts=true makes this unnecessary. We leave both here for documentation purpose)

    for (int i = 0; i < meshes; ++i)
    {
        int randX = (rand() % 100) - 50;
        int randY = (rand() % 50) - 25;
        int randZ = (rand() % 100) - 50;

        int randW = (rand() % 5) + 1;
        MeshWoldTransform[i] = XMMatrixTranslation(randX, randY, randZ) * XMMatrixScaling(randW, randW, randW);
    }

    // Setup Platform/Renderer backends
    ImGui_ImplWin32_Init(g_hWnd);
    ImGui_ImplDX11_Init(GAPI->m_device, GAPI->m_immediateContext);

    return S_OK;
}


//--------------------------------------------------------------------------------------
// Clean up the objects we've created
//--------------------------------------------------------------------------------------
void CleanupDevice()
{

    if (g_pSamplerLinear) g_pSamplerLinear->Release();
    if (g_pTextureRV) g_pTextureRV->Release();
    if (GAPI->m_immediateContext) GAPI->m_immediateContext->ClearState();
    if (g_pVertexLayout) g_pVertexLayout->Release();
    if (g_pVertexShader) g_pVertexShader->Release();
    if (GAPI->m_immediateContext) GAPI->m_immediateContext->ClearState();
   // if (g_pPixelShader) g_pPixelShader->Release();
    if (GAPI->m_immediateContext) GAPI->m_immediateContext->ClearState();
    if (g_pDepthStencil) g_pDepthStencil->Release();
    if (g_pDepthStencilView) g_pDepthStencilView->Release();
    if (g_pRenderTargetView) g_pRenderTargetView->Release();
    //if (g_pSwapChain1) g_pSwapChain1->Release();
    //if (g_pSwapChain) g_pSwapChain->Release();
    if (GAPI->m_immediateContext) GAPI->m_immediateContext->Release();
    //if (GAPI->m_device) g_pd3dDevice1->Release();
    //if (g_pd3dDevice) g_pd3dDevice->Release();
    GAPI.reset();
}


//--------------------------------------------------------------------------------------
// Called every time the application receives a message
//--------------------------------------------------------------------------------------
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    PAINTSTRUCT ps;
    HDC hdc;

    switch (message)
    {
    case WM_PAINT:
        hdc = BeginPaint(hWnd, &ps);
        EndPaint(hWnd, &ps);
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;

        // Note that this tutorial does not handle resizing (WM_SIZE) requests,
        // so we created the window without the resize border.

    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }

    return 0;
}


//--------------------------------------------------------------------------------------
// Render a frame
//--------------------------------------------------------------------------------------
void Render()
{
    // Update our time
    static float t = 0.0f;
    if (g_driverType == D3D_DRIVER_TYPE_REFERENCE)
    {
        t += (float)XM_PI * 0.0125f;
    }
    else
    {
        static ULONGLONG timeStart = 0;
        ULONGLONG timeCur = GetTickCount64();
        if (timeStart == 0)
            timeStart = timeCur;
        t = (timeCur - timeStart) / 1000.0f;
    }

    // Rotate cube around the origin
    g_World = XMMatrixRotationY(t);

    // Modify the color
    g_vMeshColor.x = (sinf(t * 1.0f) + 1.0f) * 0.5f;
    g_vMeshColor.y = (cosf(t * 3.0f) + 1.0f) * 0.5f;
    g_vMeshColor.z = (sinf(t * 5.0f) + 1.0f) * 0.5f;


    UINT stride = sizeof(SimpleVertex);
    UINT offset = 0;
    std::shared_ptr<VertexBuffer> sharedVrtxBuffer = VrtxBuffer.lock();
    if (sharedVrtxBuffer)
    {
        auto dx11VrtxBuffer = std::static_pointer_cast<Dx11VertexBuffer>(sharedVrtxBuffer);
        ID3D11Buffer* buffer = dx11VrtxBuffer->m_buffer;
        GAPI->m_immediateContext->IASetVertexBuffers(0, 1, &buffer, &stride, &offset);
    }

    //
    // Clear the back buffer
    //
    GAPI->m_immediateContext->ClearRenderTargetView(g_pRenderTargetView, Colors::MidnightBlue);

    //
    // Clear the depth buffer to 1.0 (max depth)
    //
    GAPI->m_immediateContext->ClearDepthStencilView(g_pDepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);

    static bool DrawTest = false;
    int CurrentMeshes = DrawTest ? meshes : 1;


    if (!ConstBuffer.expired())
    {
        auto testbuffer = std::static_pointer_cast<Dx11ConstantBuffer> (ConstBuffer.lock());
        GAPI->m_immediateContext->VSSetConstantBuffers(0, 1, &testbuffer->m_buffer);

    }

    if (!GAPI_ChangeonResize.expired());
    {
        auto AUTOChangeonResize = std::static_pointer_cast<Dx11ConstantBuffer>(GAPI_ChangeonResize.lock());
        GAPI->m_immediateContext->VSSetConstantBuffers(1, 1, &AUTOChangeonResize->m_buffer);
    }

    std::shared_ptr<ConstantBuffer> SharedChangeeveryFrame = GA_changeEveryFrame.lock();

    if (SharedChangeeveryFrame)
    {
        auto AutoFrame = std::static_pointer_cast<Dx11ConstantBuffer>(SharedChangeeveryFrame);
        ID3D11Buffer* CHNGBufferP = AutoFrame->m_buffer;
        GAPI->m_immediateContext->VSSetConstantBuffers(2, 1, &CHNGBufferP);
    }
	

	auto sharedPixelShader = std::static_pointer_cast<Dx11PixelShader> ( GAPI_pixelShader.lock());

	if (sharedPixelShader)
    {
		ID3D11PixelShader* pixelShaderPtr = static_cast<ID3D11PixelShader*>(sharedPixelShader->m_shader);
		GAPI->m_immediateContext->PSSetShader(pixelShaderPtr, nullptr, 0);
	}

    GAPI->m_immediateContext->PSSetShaderResources(0, 1, &g_pTextureRV);
    GAPI->m_immediateContext->PSSetSamplers(0, 1, &g_pSamplerLinear);

    for (int i = 0; i < CurrentMeshes; ++i)
    {

        //
        // Update variables that change once per frame
        //
        CBChangesEveryFrame cb;
        cb.mWorld = XMMatrixTranspose(DrawTest ? MeshWoldTransform[i]: g_World);
        cb.vMeshColor = g_vMeshColor;
        if (SharedChangeeveryFrame)
        {
            auto changeEFrame = std::static_pointer_cast<Dx11ConstantBuffer>(SharedChangeeveryFrame);
            ID3D11Buffer* chngEveryFrame = changeEFrame->m_buffer;
            GAPI->m_immediateContext->UpdateSubresource(chngEveryFrame, 0, nullptr, &cb, 0, 0);
        }
        //
        // Render the cube
        //
        
        GAPI->m_immediateContext->DrawIndexed(36, 0, 0);
        GAPI->m_immediateContext->VSSetShader(g_pVertexShader, nullptr, 0);
    }

    // Start the Dear ImGui frame
    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();

    ImGuiIO& io = ImGui::GetIO();
    // 3. Show another simple window.
        ImGui::Begin("Another Window");   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
        ImGui::Checkbox("Draw test.", &DrawTest);
        ImGui::End();

    //Camera controls
    XMVECTOR eye = g_Camera.GetEye();
    XMVECTOR at = g_Camera.GetAt();
    XMVECTOR up = g_Camera.GetUp();

    XMFLOAT3 eyeF, atF, upF;
    XMStoreFloat3(&eyeF, eye);
    XMStoreFloat3(&atF, at);
    XMStoreFloat3(&upF, up);

    // Sliders for camera
    ImGui::Begin("Camera controls");
    if (ImGui::SliderFloat3("Eye", (float*)&eyeF, -1000.0f, 10.0f))
        g_Camera.SetEye(XMLoadFloat3(&eyeF));
    if (ImGui::SliderFloat3("At", (float*)&atF, -10.0f, 10.0f))
        g_Camera.SetAt(XMLoadFloat3(&atF));
    if (ImGui::SliderFloat3("Up", (float*)&upF, -1.0f, 1.0f))
        g_Camera.SetUp(XMLoadFloat3(&upF));
    ImGui::End();


        g_Eye = XMVectorSet(g_cameraEye[0], g_cameraEye[1], g_cameraEye[2], 0.0f);
        XMVECTOR At = XMVectorSet(g_cameraAt[0], g_cameraAt[1], g_cameraAt[2], 0.0f);
        XMVECTOR Up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
        g_View = XMMatrixLookAtLH(g_Eye, At, Up);

        CBNeverChanges cbNeverChanges;
        cbNeverChanges.mView = XMMatrixTranspose(g_View);
        if (!ConstBuffer.expired())
        {
            auto pConstanBuffer = std::static_pointer_cast<Dx11ConstantBuffer>(ConstBuffer.lock());
            GAPI->m_immediateContext->UpdateSubresource(pConstanBuffer->m_buffer, 0, nullptr, &cbNeverChanges, 0, 0);
        }

        // Rendering
        ImGui::Render();
        ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

    //
    // Present our back buffer to our front buffer
    //
    GAPI->m_swapChain->Present(0, 0);
}