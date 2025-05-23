#pragma once
#include <d3d11.h>

#include "GraphicsAPI.h"



/// <summary>
/// Interface for constant buffers
/// </summary>
class ConstantBuffer
{
public:
	ConstantBuffer() = default;

	virtual void CleanUp() = 0;
	virtual void UpdateBuffer() = 0;

private:
	unsigned int m_byteWidth;
};

/// <summary>
/// Constant buffer class for DirectX 11
/// </summary>
class Dx11ConstantBuffer : public ConstantBuffer
{
	friend class GraphicsAPI;
public:
    /// <summary>
    /// Constructor
    /// </summary>
    /// <param name="device"></param>
    /// <param name="bufferSize"></param>
    Dx11ConstantBuffer(ID3D11Device* device, size_t bufferSize)
        : m_byteWidth(bufferSize)
    {
        // Initialize the buffer pointer to null
		m_bufer = nullptr;
		// Create the constant buffer description
        D3D11_BUFFER_DESC cbd = {};
		// Set the buffer description parameters
        cbd.Usage = D3D11_USAGE_DYNAMIC;
		// Set the CPU binding flags
        cbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		// Set the CPU access flags
        cbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		// Set the resource usage
        cbd.MiscFlags = 0;
		// Set the structure size
        cbd.ByteWidth = static_cast<UINT>(bufferSize);
		// Set the structure byte stride
        cbd.StructureByteStride = 0;
    }

    ~Dx11ConstantBuffer();
	
protected:

    virtual void UpdateBuffer() override;

	virtual void CleanUp() override
	{
		// Release the buffer if it exists
		if (m_bufer)
		{
			m_bufer->Release();
			m_bufer = nullptr;
		}
	};

private:
	// Pointer to the constant buffer
    ID3D11Buffer* m_bufer; 
	// Size of the buffer
    size_t m_byteWidth;
};
