#pragma once
#include <d3d11.h>

#include "GraphicsAPI.h"
#include "GapiBuffer.h"
#include "GapiRenderResources.h"

/// <summary>
/// Interface for constant buffers
/// </summary>
class InterDx11ConstantBuffer : public GapiBuffer , public GapiRenderResources
{
	friend GraphicsAPI;

public:
	InterDx11ConstantBuffer() = default;

	virtual ~InterDx11ConstantBuffer() = default;
	
protected:
	virtual void CleanUpResources() override;

	const std::uint32_t GetSlot()
	{
		return m_slot;
	}

	std::uint32_t m_slot;

private:

	ID3D11Buffer* m_Buffer = nullptr;
};





