#pragma once
#include "Base.h"

#include "Sampler.h"

class Dx11Sampler : public Sampler
{
    friend class Dx11GraphicsAPI;
public:
	Dx11Sampler() = default;

    Dx11Sampler(ID3D11Device* device, const D3D11_SAMPLER_DESC& desc)
        : m_samplerState(nullptr)
    {
        device->CreateSamplerState(&desc, &m_samplerState);
    }

    ~Dx11Sampler() override
    {
        CleanUpResources();
    }

    ID3D11SamplerState* GetSamplerState() const { return m_samplerState; }

private:
    void CleanUpResources() override
    {
        if (m_samplerState) {
            m_samplerState->Release();
            m_samplerState = nullptr;
        }
	}

    ID3D11SamplerState* m_samplerState;
};

