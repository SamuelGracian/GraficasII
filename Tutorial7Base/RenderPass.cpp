#include "RenderPass.h"

RenderPass::RenderPass()
	:m_commandBuffer (nullptr)
{
}

RenderPass::~RenderPass()
{
}

void RenderPass::BindRenderElement(const std::shared_ptr<RenderElement>& element)
{
	m_commandBuffer->BindRenderElement(element);
}

void RenderPass::BindConstantBufer(const std::shared_ptr<ConstantBuffer>& buffer)
{
	m_commandBuffer->BindConstBuffer(buffer);
}
