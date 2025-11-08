#pragma once
#include <memory>
#include <vector>

#include "ConstantBuffer.h"
#include "RenderElement.h"

#define HIGHER_AVAILABLE_SLOT 8
#define SAFE_RELEASE(x) if (x) {x -> Release(); x = nullptr;}

class ConstantBuffer;
class RenderElement;

class CommandBuffer
{
	friend class Pass;

public:
	CommandBuffer();
	virtual ~CommandBuffer();

	virtual void BeginCommandBuffer() = 0;

	void BindConstBuffer(const std::shared_ptr<ConstantBuffer>& buffer);

	virtual void UpdateConstBuffer(uint32_t Slot = HIGHER_AVAILABLE_SLOT, uint32_t bytewidt = 0, const void* data = nullptr) = 0;

	virtual void DispatchCommandBufer(std::weak_ptr<CommandBuffer> buffer) = 0;

	virtual void CleanState () = 0;

	const bool IsBufferReady() const;

	virtual void BindRenderElement(const std::shared_ptr<RenderElement>& element = nullptr);

	void ClearRenderElement();


protected:

	virtual void RecordCommandList() = 0;

	bool m_isBufferReady;
	std::vector<std::shared_ptr<ConstantBuffer>> m_constantBufferList;
	std::vector<std::shared_ptr<RenderElement>> m_renderElementList;
};

