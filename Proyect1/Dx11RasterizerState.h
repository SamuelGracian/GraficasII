#pragma once
#include "RasterizerState.h"
#include "GraphicsAPI.h"

class Dx11RasterizerState : public RasterizerState 
{
	friend class Dx11GraphicsAPI;
public:
	
	Dx11RasterizerState(ID3D11Device* device, D3D11_RASTERIZER_DESC& desc);

	virtual ~Dx11RasterizerState() { CleanUpResources(); }

	const D3D11_RASTERIZER_DESC & GetDesc() const;

	void SetDesc(const D3D11_RASTERIZER_DESC& desc);

	void Bind(ID3D11DeviceContext* device);

	virtual void CleanUpResources() override;

	D3D11_RASTERIZER_DESC m_Desc;
	ID3D11RasterizerState* m_state;
};

