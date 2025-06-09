#pragma once
#include <cstdint>

#include "GapiRenderResources.h"
#include "GraphicsAPI.h"

/// <summary>
/// Base class for buffer resources in the graphics API.
/// </summary>
class BufferResource 
{
public:
	virtual ~BufferResource() = default;
	
	virtual ID3D11Buffer* GetRawBuffer() = 0;

	virtual void CleanUpResources() = 0;

	UINT byteWidth() const { return m_byteWidth; }
protected:
	UINT m_byteWidth = 0;
};