#pragma once

#include "Base.h"

class ConstantBuffer;


struct CBNeverChanges
{
	DirectX::XMMATRIX mView;
};

/// <summary>
/// Base class for graphics API.
/// </summary>
class GraphicsAPI 
{
public:
	GraphicsAPI() = default;

	virtual ~GraphicsAPI() = default;

	virtual void CleanUpResources() = 0;

	virtual std::shared_ptr<ConstantBuffer> CreateConstanBuffer() = 0;

};

/// <summary>
/// API for Dx11
/// </summary>
class Dx11GraphicsAPI : public GraphicsAPI
{
public:
	Dx11GraphicsAPI(HWND windowHandler);

	virtual ~Dx11GraphicsAPI() = default;

	void CleanUpResources() override;

	std::shared_ptr<ConstantBuffer> CreateConstanBuffer() override;

private:

	std::shared_ptr <ConstantBuffer> m_constanBuffer;

	HWND							m_wWnd;

	ID3D11Device*					m_device;
	ID3D11DeviceContext*			m_immediateContext;
	IDXGISwapChain*					m_swapChain;
	IDXGISwapChain*					_SwapChain1;
};
