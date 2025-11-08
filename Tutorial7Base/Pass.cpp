#include "Pass.h"

#define SAFE_RELEASE(x) if (x) {x -> Release(); x = nullptr;}

Pass::Pass()
	:m_commandBuffer(nullptr),
	m_renderElement(nullptr)
{
}


void Pass::BindRenderElement(std::shared_ptr<RenderElement>& element)
{
	if (element == nullptr)
	{
		return;
	}

	m_renderElement = element;

	auto it = std::find(m_renderElementList.begin(), m_renderElementList.end(), element);
	if (it == m_renderElementList.end())
	{
		m_renderElementList.push_back(element);
	}

	if (m_commandBuffer)
	{
		m_commandBuffer->BindRenderElement(element);
	}
}

void Pass::DrawRenderElement()
{
}
