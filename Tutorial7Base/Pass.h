#pragma once
#include <memory>

#include "CommandBuffer.h"

class Pass
{
public:
	Pass();
	~Pass();

	std::shared_ptr<CommandBuffer> m_commandBuffer;
};

