#pragma once
#include <memory>
#include <vector>

#include "CommandBuffer.h"
#include "RenderElement.h"

class RenderPass
{
public:
	RenderPass();
	~RenderPass();
	
	void BindConstantBufer(const std::shared_ptr<ConstantBuffer> & buffer = nullptr);

	void BindRenderElement(const std::shared_ptr<RenderElement>& element = nullptr);

private:
	std::shared_ptr<CommandBuffer> m_commandBuffer;
};