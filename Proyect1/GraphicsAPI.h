#pragma once
#include <memory>
#include <dxgi1_2.h>
#include <d3d11_1.h>

#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "ConstantBuffer.h"


/// <summary>
/// Base class for graphics API.
/// </summary>
class GraphicsAPI 
{
public:
	GraphicsAPI(HWND windowhandler);
	virtual ~GraphicsAPI() = 0;

private:
	HWND								m_wWnd = nullptr;
	
	ID3D11Device*						m_device = nullptr;
	ID3D11DeviceContext*				m_immediateContext = nullptr;
	IDXGISwapChain*						m_swapChain = nullptr;
	IDXGISwapChain*						m_SwapChain1 = nullptr;

	D3D_DRIVER_TYPE						m_driverType = D3D_DRIVER_TYPE_NULL;
	D3D_FEATURE_LEVEL					m_featureLvel = D3D_FEATURE_LEVEL_11_0;

	ID3D11Device1*						g_pd3dDevice1 = nullptr;

	ID3D11DeviceContext1*				g_pImmediateContext1 = nullptr;
};



