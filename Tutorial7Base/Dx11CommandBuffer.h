#pragma once
#include <d3d11.h>
#include <vector>

#include "CommandBuffer.h"
#include "Dx11ConstantBuffer.h"
#include "DX11GRAPI.H"

class Dx11CommandBuffer : public CommandBuffer
{
	friend class Dx11GraphicsAPI;
public:
	Dx11CommandBuffer();
	~Dx11CommandBuffer();

	virtual void BeginCommandBuffer() override;

	virtual void UpdateConstBuffer(uint32_t Slot = HIGHER_AVAILABLE_SLOT, uint32_t bytewidt = 0, const void* data = nullptr) override;

	virtual void DispatchCommandBufer(std::weak_ptr<CommandBuffer> buffer) override;

	virtual void CleanState() override;

	void BindRenderElement(const std::shared_ptr<RenderElement>& element);

	virtual void Execute() override;

protected:

	virtual void RecordCommandList() override;

private:
	ID3D11DeviceContext* m_context; 
	ID3D11CommandList* m_commandList;
	std::vector<ID3D11Buffer*> m_bufferList;
};

