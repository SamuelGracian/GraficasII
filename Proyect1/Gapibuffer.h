#pragma once
#include <cstdint>

#include "GapiRenderResources.h"


static const std::uint32_t AvailableBufferSlots = 8;


/// <summary>
/// Base class for GAPI buffers
/// </summary>
class GapiBuffer : public  GapiRenderResources
{
public:

	/// <summary>
	/// Gets the byte width of the buffer
	/// <summary>
	std::uint32_t GetByteWidth() const
	{
		return m_byteWidth;
	};

protected:
	GapiBuffer()
		: m_byteWidth(0)
	{
	};

	virtual ~GapiBuffer() = default;

private:
	std::uint32_t m_byteWidth;

};