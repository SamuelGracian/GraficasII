#include "RenderElement.h"

RenderElement :: RenderElement()
{ }

RenderElement :: ~RenderElement()
{
}

void RenderElement :: BindConstBuffer(std::shared_ptr<ConstantBuffer>& buffer)
{
}
void RenderElement::BindVertexBuffer(std::shared_ptr<VertexBuffer>& buffer)
{
}

void RenderElement::BindIndexBuffer(std::shared_ptr<IndexBuffer>& buffer)
{
}

void RenderElement::BindVertexShader(std::shared_ptr<VertexShader>& shader)
{
}

void RenderElement::BindPixelShader(std::shared_ptr<PixelShader>& shader)
{
}

