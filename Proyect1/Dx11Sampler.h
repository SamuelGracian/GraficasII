#pragma once
#include "Base.h"

class Dx11Sampler
{
public:
    Dx11Sampler(ID3D11Device* device, const D3D11_SAMPLER_DESC& desc)
        : m_samplerState(nullptr)
    {
        device->CreateSamplerState(&desc, &m_samplerState);
    }

    ~Dx11Sampler() override
    {
        if (m_samplerState) m_samplerState->Release();
    }

    ID3D11SamplerState* GetSamplerState() const { return m_samplerState; }

private:
    ID3D11SamplerState* m_samplerState;
};

