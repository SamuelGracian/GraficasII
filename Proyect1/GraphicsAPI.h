#pragma once

#include <windows.h>
#include <d3d11_1.h>
#include <directxmath.h>
#include <d3dcompiler.h>
#include <directxcolors.h>
#include <stdexcept>
#include <memory> 

#include "InConstantBuffer.h"
#include "InIndexBuffer.h"
#include "VertexBuffers.h"

class GraphicsAPI
{
public:
    GraphicsAPI(HWND Winhandler);
    ~GraphicsAPI();

    //______Functions_______________________
    
    // Buffer creation functions returning weak pointers to their interfaces
    std::weak_ptr<InterDx11ConstantBuffer> CreateConstantBuffer();
    std::weak_ptr<InterDx11IndexBuffer> CreateIndexBuffer();
    std::weak_ptr<InterDx11VertexBuffers> CreateVertexBuffer();

	//DirectX 11 device and context accessors
	ID3D11Device* device = nullptr;
	ID3D11DeviceContext* context = nullptr;
	IDXGISwapChain* swapChain = nullptr;

private:
    D3D_DRIVER_TYPE driverType = D3D_DRIVER_TYPE_UNKNOWN;
    D3D_FEATURE_LEVEL featureLevel = D3D_FEATURE_LEVEL_11_0;

};


