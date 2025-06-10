#pragma once
#include <cstdint>

#include "GraphicsAPI.h"

/// <summary>
/// Base class for buffer resources in the graphics API.
/// </summary>
class  BufferResource
{
public:
	virtual ~BufferResource() = default;
	
	virtual ID3D11Buffer* GetRawBuffer() = 0;

	virtual void CleanUpResources() = 0;

	virtual void UpdateBuffer() = 0;

	virtual UINT GetByteWidth() const = 0;

	virtual UINT GetBindFlags() const = 0;

protected:
	UINT m_byteWidth = 0;
	UINT m_bindFlags = 0; 
};