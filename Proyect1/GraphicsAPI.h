#pragma once

#include "Base.h"

class ConstanBuffer;

/// <summary>
/// Base class for graphics API.
/// </summary>
class GraphicsAPI 
{
public:
	GraphicsAPI() = default;

	virtual ~GraphicsAPI() = default;

	virtual void CleanUpResources() = 0;

	virtual std::shared_ptr<ConstanBuffer> CreateConstanBuffer() = 0;

};


class Dx11GraphicsAPI : public GraphicsAPI
{
public:
	Dx11GraphicsAPI(HWND windowHandler);

	virtual ~Dx11GraphicsAPI() = default;

	void CleanUpResources() override;

private:
	HWND								m_wWnd;

	ID3D11Device* m_device = nullptr;
	ID3D11DeviceContext* m_context = nullptr;
	IDXGISwapChain* m_swapChain = nullptr;
};
