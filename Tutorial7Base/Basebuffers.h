#pragma once
#include <cstdint>
//#include <d3d11.h>
#include <cassert>

class BaseBuffer
{
public:
	BaseBuffer();

	virtual ~BaseBuffer();

	void SetByteWidth(const uint32_t bytewidth);

	const uint32_t GetByteWidth()const;

private:
	uint32_t m_byteWidth;
};