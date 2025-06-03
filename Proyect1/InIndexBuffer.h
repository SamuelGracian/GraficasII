#pragma once
#include <d3d11.h>

#include "GraphicsAPI.h"
#include "GapiRenderResources.h"

/// <summary>
/// Interface for DirectX 11 index buffers
/// </summary>
class InterDx11IndexBuffer : public GapiRenderResources
{
	friend class GraphicsAPI;

public:
	InterDx11IndexBuffer() = default;

	virtual ~InterDx11IndexBuffer() = default;

protected:

	virtual void CleanUpResources() override;

	const std::uint32_t GetSlot()
	{
		return m_slot;
	}

	std::uint32_t m_slot;

private:
	ID3D11Buffer* m_buffer = nullptr;

};

