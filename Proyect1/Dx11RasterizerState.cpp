#include "Dx11RasterizerState.h"


Dx11RasterizerState::Dx11RasterizerState(ID3D11Device* device, D3D11_RASTERIZER_DESC& desc)
	:m_Desc(desc), m_state(nullptr)
{
	device->CreateRasterizerState(&desc, &m_state);
}

const D3D11_RASTERIZER_DESC& Dx11RasterizerState::GetDesc() const
{
	return m_Desc;
}

void Dx11RasterizerState::SetDesc(const D3D11_RASTERIZER_DESC& desc)
{
	m_Desc = desc;
}

void Dx11RasterizerState::Bind(ID3D11DeviceContext* device)
{
	device->RSSetState(m_state);
}

void Dx11RasterizerState::CleanUpResources()
{
	if (m_state)
	{
		m_state->Release();
		m_state = nullptr;
	}
}
