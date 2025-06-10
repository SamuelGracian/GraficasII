#pragma once
#include "GraphicsAPI.h"

class Dx11GraphicsAPI : public GraphicsAPI
{
public:
	Dx11GraphicsAPI() = default;

	virtual ~Dx11GraphicsAPI() = default;

	void CleanUpResources() override
	{
		// Implement resource cleanup logic specific to DirectX 11
		if (m_device)
		{
			m_device->Release();
			m_device = nullptr;
		}
		if (m_context)
		{
			m_context->Release();
			m_context = nullptr;
		}
		if (m_swapChain)
		{
			m_swapChain->Release();
			m_swapChain = nullptr;
		}
	}

	void SetVertexBuffer() override;

	void SetIndexBuffer() override;

	void SetConstantBuffer() override;

	void Draw() override;

private:
	ID3D11Device* m_device = nullptr;
	ID3D11DeviceContext* m_context = nullptr;
	IDXGISwapChain* m_swapChain = nullptr;
};

