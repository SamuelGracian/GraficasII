#pragma once

#include "RenderResource.h"


/// <summary>
/// Base class for buffer resources in the graphics API.
/// </summary>
class  BufferResource : public RenderResource
{
public:
	BufferResource()
		: m_byteWidth (0)
	{};

	virtual ~BufferResource() = default;

	 uint32_t GetByteWidth() const { return m_byteWidth; }

protected:
	uint32_t m_byteWidth;
	
};