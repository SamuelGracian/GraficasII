#pragma once
#include <cstdint>
#include <d3d11.h>

class BaseBufer
{
public:
	BaseBufer()
		: m_byteWidth(0)
	{};

	virtual ~BaseBufer() = default;

	uint32_t m_byteWidth;
};