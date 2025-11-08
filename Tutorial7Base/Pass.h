#pragma once
#include <memory>
#include <vector>

#include "CommandBuffer.h"
#include "RenderElement.h"

#define SAFE_RELEASE(x) if (x) {x -> Release(); x = nullptr;}

class CommandBuffer;
class RenderElement;

class Pass
{
public:
	Pass();
	~Pass() = default;

	void BindRenderElement(std::shared_ptr<RenderElement>& element);

	void DrawRenderElement();

	std::shared_ptr<CommandBuffer> m_commandBuffer;
	std::shared_ptr<RenderElement> m_renderElement;
	std::vector <std::shared_ptr<RenderElement>> m_renderElementList; // render element list for the pass
};

