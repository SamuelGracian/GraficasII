#pragma once
#include <memory>
#include <vector>

#include "ConstantBuffer.h"
#include "Vertexbuffer.h"
#include "IndexBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"


class RenderElement
{
public:
	RenderElement();
	virtual ~RenderElement();

	void BindConstBuffer(std::shared_ptr<ConstantBuffer>& buffer);

	void BindVertexBuffer(std::shared_ptr<VertexBuffer>& buffer);

	void BindIndexBuffer(std::shared_ptr<IndexBuffer>& buffer);

	void BindVertexShader(std::shared_ptr<VertexShader>& shader);

	void BindPixelShader(std::shared_ptr<PixelShader>& shader);

private:
	std::vector<std::shared_ptr<ConstantBuffer>> m_constantBufferList;

	std::shared_ptr<VertexBuffer> m_vertexBuffer;

	std::shared_ptr<IndexBuffer> m_indexBuffer;

	std::shared_ptr<VertexShader> m_vertexShader;

	std::shared_ptr<PixelShader> m_pixelShader;
};

//no render target ni depth stencil for now