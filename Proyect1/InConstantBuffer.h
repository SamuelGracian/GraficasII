#pragma once
#include <d3d11.h>

#include "GraphicsAPI.h"
#include "GapiBuffer.h"

/// <summary>
/// Interface for constant buffers
/// </summary>
class InterDx11ConstantBuffer : public GapiBuffer
{
	friend GraphicsAPI;

public:
	InterDx11ConstantBuffer() = default;

	virtual ~InterDx11ConstantBuffer();
	
protected:
	virtual void CleanUpResources() override;

private:

	ID3D11Buffer* m_Buffer = nullptr;
};


/// <summary>
/// Constant buffer container class for DirectX 11
/// </summary>
class Dx11ConstantBuffer : public InterDx11ConstantBuffer
{
public:
	Dx11ConstantBuffer() = default;
	~Dx11ConstantBuffer();

private:

	const std::uint32_t GetSlot()
	{
		return m_slot;
	}

protected:
	std::uint32_t m_slot;
};


