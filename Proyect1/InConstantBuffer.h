#pragma once
#include <d3d11.h>

class InConstantBuffer
{
    /// <summary>
    /// Constructor
    /// </summary>
    /// <param name="device"></param>
    /// <param name="bufferSize"></param>
    InConstantBuffer(ID3D11Device* device, size_t bufferSize)
        : m_bufferSize(bufferSize)
    {
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

private:

	// Size of the buffer
    size_t m_bufferSize;
};
