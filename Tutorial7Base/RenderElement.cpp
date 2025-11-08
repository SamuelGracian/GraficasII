#include "RenderElement.h"

RenderElement :: RenderElement()
{ }

RenderElement :: ~RenderElement()
{
}

void RenderElement :: BindConstBuffer(std::shared_ptr<ConstantBuffer>& buffer)
{
	if (buffer == nullptr || buffer->GetSlot() >= HIGHER_AVAILABLE_SLOT || buffer->GetByteWidth() == 0)
	{
		return;
	}
	m_constantBufferList[buffer->GetSlot()] = buffer;
}
