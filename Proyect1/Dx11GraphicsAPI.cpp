#include "Dx11GraphicsAPI.h"

void Dx11GraphicsAPI::CleanUpResources()
{
	if (m_device)
	{
		m_device->Release();
		m_device = nullptr;
	}
	if (m_immediateContext)
	{
		m_immediateContext->Release();
		m_immediateContext = nullptr;
	}
	if (m_swapChain)
	{
		m_swapChain->Release();
		m_swapChain = nullptr;
	}
}

std::shared_ptr<ConstanBuffer> Dx11GraphicsAPI::CreateConstanBuffer()
{



	return m_constanBuffer;
}
