#pragma once
#include "RasterizerDesc.h"

class RasterizerState
{
public:
    virtual ~RasterizerState() = default;

    virtual void Bind() = 0;


    const D3D11_RasterizerDesc& GetDesc() const { return m_Desc; }
    void SetDesc(const D3D11_RasterizerDesc& desc) { m_Desc = desc; }

protected:
    RasterizerState() = default;
    D3D11_RasterizerDesc m_Desc;
};

