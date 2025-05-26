#include <d3d11.h>
#include "GraphicsAPI.h"

class InterDx11IndexBuffer : public GapiRenderResources
{
	friend GraphicsAPI;

public:
	InterDx11IndexBuffer() = default;

	virtual ~InterDx11IndexBuffer() = default;

protected:

	virtual void CleanUpResources() override;

private:
	ID3D11Buffer* m_buffer = nullptr;

};


class Dx11IndexBuffer : public InterDx11IndexBuffer
{

public:

	Dx11IndexBuffer() = default;
	~Dx11IndexBuffer();

private:
	const std::uint32_t GetSlot() const
	{
		return m_slot;
	}

protected:
	std::uint32_t m_slot = 0;

};