#pragma once
#include <memory>
#include <vector>

#include "ConstantBuffer.h"
#include "Vertexbuffer.h"
#include "IndexBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"

class ConstantBuffer;

class RenderElement
{
	friend class CommandBuffer;
public:

	RenderElement();
	virtual ~RenderElement();

	void BindConstBuffer(std::shared_ptr<ConstantBuffer>& buffer);

	std::vector<std::shared_ptr<ConstantBuffer>> m_constantBufferList;

};

//no render target ni depth stencil for now