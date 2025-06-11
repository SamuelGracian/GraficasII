#pragma once
#include "GraphicsAPI.h"

class Dx11GraphicsAPI : public GraphicsAPI
{
public:
	Dx11GraphicsAPI() :
		 m_constanBuffer(nullptr)
		,m_device(nullptr)
		,m_immediateContext(nullptr)
		,m_swapChain(nullptr)
	{};

	virtual ~Dx11GraphicsAPI() = default;

	void CleanUpResources() override;

	std::shared_ptr<ConstanBuffer> CreateConstanBuffer() override;

private:
	std::shared_ptr <ConstanBuffer> m_constanBuffer;

	//*-------------------------------------------------------------//*
	ID3D11Device* m_device;
	ID3D11DeviceContext* m_immediateContext;
	IDXGISwapChain* m_swapChain;
	IDXGISwapChain* m_SwapChain1;

	D3D_DRIVER_TYPE						m_driverType = D3D_DRIVER_TYPE_NULL;
	D3D_FEATURE_LEVEL					m_featureLvel = D3D_FEATURE_LEVEL_11_0;

	ID3D11Device1* g_pd3dDevice1 = nullptr;

	ID3D11DeviceContext1* g_pImmediateContext1 = nullptr;
};

