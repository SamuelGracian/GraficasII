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
#define DIRECTX11

#include <windows.h>
#include "resource.h"
#include "ObjLoader.h"
#include <iostream>
#include <sstream> 
#include <fstream> 

#ifdef DIRECTX11
#include <directxmath.h>


/// TO DO
    // bajar compilar mathfoo
	// hacer matrices

/// Buffers
#include "ConstantBuffer.h"
#include "IndexBuffer.h"
#include "VertexBuffer.h"
/// Shaders
#include "VertexShader.h"
#include "PixelShader.h"

/// DepthStencil
#include "DepthStencilView.h"

///SwapChain
#include "SwapChain.h"

///GRAPI
#include "DX11GRAPI.h"
using namespace DirectX;

//-------------------------------------------------------------------------------------
// Graphics API
//-------------------------------------------------------------------------------------

//DepthStencilView Gapi_dpStencilView;

// NOTE: Removed duplicate `struct SimpleVertex` here. Use the one from ObjLoader.h
//--------------------------------------------------------------------------------------
// Structures
//--------------------------------------------------------------------------------------
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
HINSTANCE                           g_hInst = nullptr;
HWND                                g_hWnd = nullptr;
D3D_DRIVER_TYPE                     g_driverType = D3D_DRIVER_TYPE_NULL;
D3D_FEATURE_LEVEL                   g_featureLevel = D3D_FEATURE_LEVEL_11_0;
ID3D11Device* g_pd3dDevice = nullptr;
ID3D11Device1* g_pd3dDevice1 = nullptr;
ID3D11DeviceContext* g_pImmediateContext = nullptr;
ID3D11DeviceContext1* g_pImmediateContext1 = nullptr;
IDXGISwapChain1* g_pSwapChain1 = nullptr;
ID3D11RenderTargetView* g_pRenderTargetView = nullptr;
ID3D11Buffer* g_pCBNeverChanges = nullptr;

ID3D11InputLayout* g_pVertexLayout = nullptr;

ID3D11Buffer* g_pCBChangeOnResize = nullptr;
ID3D11Buffer* g_pCBChangesEveryFrame = nullptr;
ID3D11ShaderResourceView* g_pTextureRV = nullptr;
ID3D11SamplerState* g_pSamplerLinear = nullptr;
XMMATRIX                            g_World;
XMMATRIX                            g_View;
XMMATRIX                            g_Projection;
XMFLOAT4                            g_vMeshColor(0.7f, 0.7f, 0.7f, 1.0f);

// Number of indices loaded from the OBJ; used by Render()
UINT g_IndexCount = 0;

//--------------------------------------------------------------------------------------
//Interface GRAPI
//--------------------------------------------------------------------------------------

std::shared_ptr<Dx11GraphicsAPI> GAPI = nullptr;
std::shared_ptr<Dx11ConstantBuffer> Gapi_constbuffer = nullptr;
std::shared_ptr<Dx11IndexBuffer> Gapi_indxBuffer = nullptr;
std::shared_ptr<Dx11VertexBuffer> Gapi_vrtxBuffer = nullptr;
std::shared_ptr<SwapChain> Gapi_swpChain = nullptr;
std::shared_ptr<VertexShader> Gapi_vrtxShader = nullptr;
std::shared_ptr<PixelShader> Gapi_pxlShader = nullptr;
std::shared_ptr<DepthStencilView> Gapi_depthStencil = nullptr;
std::shared_ptr<CommandBuffer> Gapi_CommandBuffer = nullptr;
std::shared_ptr<Topology> Gapi_topology = nullptr;


//--------------------------------------------------------------------------------------
// Forward declarations
//--------------------------------------------------------------------------------------
HRESULT InitWindow(HINSTANCE hInstance, int nCmdShow);
HRESULT InitDevice();
//void CleanupDevice();
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
void Render();


std::string ReadFileToString(const std::wstring& filePath)
{
    std::ifstream file(filePath, std::ios::in | std::ios::binary);

    if (!file.is_open())
    {
        MessageBox(nullptr, L"Unable to open file", L"File Read Error", MB_OK);
        return "";
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    file.close();

    return buffer.str();
}

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
       // CleanupDevice();
        return 0;
    }

    // Main message loop
    MSG msg = { 0 };
    while (WM_QUIT != msg.message)
    {
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

   // CleanupDevice();

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
// Create Direct3D device and swap chain
//--------------------------------------------------------------------------------------
HRESULT InitDevice()
{
    HRESULT hr = S_OK;

    RECT rc;
    GetClientRect(g_hWnd, &rc);
    UINT width = rc.right - rc.left;
    UINT height = rc.bottom - rc.top;

    GAPI = std::make_shared<Dx11GraphicsAPI>();

    //Create swap chain with grapi
    if (GAPI)
    {
        Gapi_swpChain =  GAPI->CreateSwapChain(g_hWnd, width, height, GAPI_FORMAT::FORMAT_R8G8B8A8_UNORM);
    }
  
    // Setup the viewport


    // Compile the vertex shader
    ID3DBlob* pVSBlob = nullptr;
	hr = GAPI->CompileShaderFromFile(L"Resources/RawData/Shaders/Tutorial07.fxh", "VS", "vs_4_0", &pVSBlob);
    if (FAILED(hr))
    {
        MessageBox(nullptr,
            L"The FX file cannot be compiled.  Please run this executable from the directory that contains the FX file.", L"Error", MB_OK);
        return hr;
    }

    ///-----------------------------------------------------------------

    std::vector<std::string> defines  {"#define TEST"};

	Gapi_vrtxShader = std::static_pointer_cast<Dx11VertexShader>( GAPI->CreateVertexShader(ReadFileToString(L"Resources/RawData/Shaders/Tutorial07.fxh"), "VS",defines));

    // Set the input layout
    GAPI->m_immediateContext->IASetInputLayout(g_pVertexLayout);

    // Compile the pixel shader
    ID3DBlob* pPSBlob = nullptr;
    
    
    //hr = GAPI->CompileShaderFromFile(L"Resources/RawData/Shaders/Tutorial07.fxh", "PS", "ps_4_0", &pPSBlob);
    
    GAPI->CreatePixelShader(ReadFileToString(L"Resources/RawData/Shaders/Tutorial07.fxh"), "PS");

    if (FAILED(hr))
    {
        MessageBox(nullptr,
            L"The FX file cannot be compiled.  Please run this executable from the directory that contains the FX file.", L"Error", MB_OK);
        return hr;
    }


	//Gapi_pxlShader = std::static_pointer_cast<Dx11PixelShader>(GAPI->CreatePixelShader(pPSBlob->GetBufferPointer(), pPSBlob->GetBufferSize()));


    D3D11_BUFFER_DESC bd = {};

    ///Replace with OBJ loading
    {
        std::vector<SimpleVertex> meshVertices;
        std::vector<uint16_t> meshIndices;
        std::string loadErr;
        // path is relative to executable working directory; use full path if necessary
        if (!LoadOBJSimple("Resources/RawData/3DModels/drakefire-pistol/drakefire_pistol_low.obj", meshVertices, meshIndices, loadErr))
        {
            // show error and fallback or fail
            MessageBoxA(nullptr, loadErr.c_str(), "OBJ load error", MB_OK);
            return E_FAIL;
        }

        // Create vertex buffer using your GRAPI
        Gapi_vrtxBuffer = std::static_pointer_cast<Dx11VertexBuffer>(
            GAPI->CreateVertexBuffer(sizeof(SimpleVertex) * meshVertices.size(), meshVertices.data()));

        // Set vertex buffer (same as before)
        UINT stride = sizeof(SimpleVertex);
        UINT offset = 0;
        GAPI->m_immediateContext->IASetVertexBuffers(0, 1, &Gapi_vrtxBuffer->m_buffer, &stride, &offset);

        // Create index buffer using your GRAPI (16-bit)
        Gapi_indxBuffer = std::static_pointer_cast<Dx11IndexBuffer>(
            GAPI->CreateIndexBuffer(sizeof(uint16_t) * meshIndices.size(), meshIndices.data(), static_cast<uint32_t>(meshIndices.size()))
        );

        // Set index buffer (same format used in Source.cpp)
        GAPI->m_immediateContext->IASetIndexBuffer(Gapi_indxBuffer->m_buffer, DXGI_FORMAT_R16_UINT, 0);

        // store index count for Render()
        g_IndexCount = static_cast<UINT>(meshIndices.size());
    }

    // Create the constant buffers
    bd.Usage = D3D11_USAGE_DEFAULT;
    bd.ByteWidth = sizeof(CBNeverChanges);
    bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    bd.CPUAccessFlags = 0;

    ///-----------------------------------------------------------------------------
    ///Create constant buffer with GRAPI
    ///-----------------------------------------------------------------------------
    Gapi_constbuffer = std::static_pointer_cast<Dx11ConstantBuffer>(GAPI->CreateConstantBuffer(sizeof(CBNeverChanges),0,nullptr));

    ///----------------------------------------------------------------------------
    ///Command buffer
    ///----------------------------------------------------------------------------
    Gapi_CommandBuffer = GAPI->CreateCommandBuffer();

    auto pCommand = std::static_pointer_cast<Dx11CommandBuffer>(Gapi_CommandBuffer);

    // Initialize the view matrix
    XMVECTOR Eye = XMVectorSet(6.0f, 3.0f, 0.0f, 0.0f);
    XMVECTOR At   = XMVectorSet(0.0f, 1.0f,  0.0f, 0.0f);
    XMVECTOR Up   = XMVectorSet(0.0f, 1.0f,  0.0f, 0.0f);
    g_View = XMMatrixLookAtLH(Eye, At, Up);


    if (pCommand)
    {
        pCommand->BeginCommandBuffer();
        //pCommand->UpdateConstantBuffer(Gapi_constbuffer, sizeof(CBNeverChanges),&CbNeverChanges) ;
    }

    bd.ByteWidth = sizeof(CBChangeOnResize);
    hr = GAPI->m_device->CreateBuffer(&bd, nullptr, &g_pCBChangeOnResize);
    if (FAILED(hr))
        return hr;

    bd.ByteWidth = sizeof(CBChangesEveryFrame);
    hr = GAPI->m_device->CreateBuffer(&bd, nullptr, &g_pCBChangesEveryFrame);
    if (FAILED(hr))
        return hr;


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


    CBNeverChanges cbNeverChanges;
    cbNeverChanges.mView = XMMatrixTranspose(g_View);

    ///Update constant buffer
    GAPI->UpdateConstantBuffer(Gapi_constbuffer, sizeof(cbNeverChanges), &cbNeverChanges);


    // Initialize the projection matrix
    g_Projection = XMMatrixPerspectiveFovLH(XM_PIDIV4, width / (FLOAT)height, 0.01f, 100.0f);

    CBChangeOnResize cbChangesOnResize;
    cbChangesOnResize.mProjection = XMMatrixTranspose(g_Projection);
    GAPI->m_immediateContext->UpdateSubresource(g_pCBChangeOnResize, 0, nullptr, &cbChangesOnResize, 0, 0);

    return S_OK;
}


//--------------------------------------------------------------------------------------
// Clean up the objects we've created
//--------------------------------------------------------------------------------------
//void CleanupDevice()
//{
//    if (GAPI->m_immediateContext) GAPI->m_immediateContext->ClearState();
//
//    if (g_pSamplerLinear) g_pSamplerLinear->Release();
//    if (g_pTextureRV) g_pTextureRV->Release();
//    //if (g_pCBNeverChanges) g_pCBNeverChanges->Release();
//    //if (Gapi_constbuffer -> m_buffer) Gapi_constbuffer -> m_buffer->Release();
//    if (g_pCBChangeOnResize) g_pCBChangeOnResize->Release();
//    if (g_pCBChangesEveryFrame) g_pCBChangesEveryFrame->Release();
//    //if (g_pVertexBuffer) g_pVertexBuffer->Release();
//    if (Gapi_vrtxBuffer->m_buffer) Gapi_vrtxBuffer->m_buffer->Release();
//    //if (g_pIndexBuffer) g_pIndexBuffer->Release();
//    if (Gapi_indxBuffer->m_buffer) Gapi_indxBuffer->m_buffer->Release();
//    if (g_pVertexLayout) g_pVertexLayout->Release();
//    //if (g_pVertexShader) g_pVertexShader->Release();
//    if (Gapi_vrtxShader->GetShader()) Gapi_vrtxShader->m_shader->Release();
//    //if (g_pPixelShader) g_pPixelShader->Release();
//    if (Gapi_pxlShader->GetShader()) Gapi_pxlShader->GetShader()->Release();
//    //if (g_pDepthStencil) g_pDepthStencil->Release();
//    if (GAPI->m_backBufferDS)GAPI->m_backBufferDS->Release();
//    //if (g_pDepthStencilView) g_pDepthStencilView->Release();
//    if (GAPI->m_backBufferDS)GAPI->m_backBufferDS->Release();
//    if (g_pRenderTargetView) g_pRenderTargetView->Release();
//    if (g_pSwapChain1) g_pSwapChain1->Release();
//    //if (g_pSwapChain) g_pSwapChain->Release();
//    if (Gapi_swpChain->GetSwapChain()) Gapi_swpChain->GetSwapChain()->Release();
//    if (g_pImmediateContext1) g_pImmediateContext1->Release();
//    if (g_pImmediateContext) g_pImmediateContext->Release();
//    if (g_pd3dDevice1) g_pd3dDevice1->Release();
//    if (g_pd3dDevice) g_pd3dDevice->Release();
//}


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

    //GAPI->m_immediateContext->OMSetRenderTargets(1, &GAPI->m_backBufferRT, GAPI->m_backBufferDS);

    //// Update our time
    //static float t = 0.0f;
    //if (g_driverType == D3D_DRIVER_TYPE_REFERENCE)
    //{
    //    t += (float)XM_PI * 0.0125f;
    //}
    //else
    //{
    //    static ULONGLONG timeStart = 0;
    //    ULONGLONG timeCur = GetTickCount64();
    //    if (timeStart == 0)
    //        timeStart = timeCur;
    //    t = (timeCur - timeStart) / 1000.0f;
    //}

    //// Reset world / color
    //g_World = XMMatrixIdentity();
    //g_vMeshColor.x = (sinf(t * 1.0f) + 1.0f) * 0.5f;
    //g_vMeshColor.y = (cosf(t * 3.0f) + 1.0f) * 0.5f;
    //g_vMeshColor.z = (sinf(t * 5.0f) + 1.0f) * 0.5f;

    //float Color[] = { 0.0f, 1.0f, 0.0f, 1.0f };

    //// Clear targets
    //GAPI->m_immediateContext->ClearRenderTargetView(g_pRenderTargetView, Color);
    ////GAPI->m_immediateContext->ClearDepthStencilView(GAPI->m_backBufferDS, D3D11_CLEAR_DEPTH, 1.0f, 0);

    //// Update per-frame CB
    //CBChangesEveryFrame cb;
    //cb.mWorld = XMMatrixTranspose(g_World);
    //cb.vMeshColor = g_vMeshColor;
    //GAPI->m_immediateContext->UpdateSubresource(g_pCBChangesEveryFrame, 0, nullptr, &cb, 0, 0);

    //// If command buffer exists, execute only if it's ready. Otherwise perform direct draw.
    //if (Gapi_CommandBuffer && Gapi_CommandBuffer->IsBufferReady())
    //{
    //    Gapi_CommandBuffer->Execute();
    //}
    //else
    //{
    //    // Use only GAPI objects (avoid raw/uninitialized globals)
    //    if (Gapi_vrtxShader && Gapi_vrtxShader->m_shader)
    //        GAPI->m_immediateContext->VSSetShader(Gapi_vrtxShader->m_shader, nullptr, 0);

    //    // Bind constant buffers (slot 0 = never-changes, slot1 = projection, slot2 = per-frame)
    //    ID3D11Buffer* cb0 = (Gapi_constbuffer && Gapi_constbuffer->m_buffer) ? Gapi_constbuffer->m_buffer : nullptr;
    //    GAPI->m_immediateContext->VSSetConstantBuffers(0, 1, &cb0);
    //    GAPI->m_immediateContext->VSSetConstantBuffers(1, 1, &g_pCBChangeOnResize);
    //    GAPI->m_immediateContext->VSSetConstantBuffers(2, 1, &g_pCBChangesEveryFrame);

    //    if (Gapi_pxlShader && Gapi_pxlShader->m_shader)
    //        GAPI->m_immediateContext->PSSetShader(Gapi_pxlShader->m_shader, nullptr, 0);


    //    GAPI->m_immediateContext->PSSetConstantBuffers(2, 1, &g_pCBChangesEveryFrame);
    //    GAPI->m_immediateContext->PSSetShaderResources(0, 1, &g_pTextureRV);
    //    GAPI->m_immediateContext->PSSetSamplers(0, 1, &g_pSamplerLinear);

    //    // Ensure topology and vertex/index buffers already set in InitDevice()
    //    GAPI->m_immediateContext->DrawIndexed(g_IndexCount, 0, 0);
    //}

    //// Present
    //if (Gapi_swpChain && Gapi_swpChain->m_swapChain)
    //    Gapi_swpChain->m_swapChain->Present(0, 0);
}

#endif