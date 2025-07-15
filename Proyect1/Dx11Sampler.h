#pragma once
#include "Base.h"

#include "Sampler.h"

class Dx11Sampler : public Sampler
{
    friend class Dx11GraphicsAPI;
public:

    Dx11Sampler()
        : m_samplerState(nullptr)
    {
    }

    ~Dx11Sampler() override
    {
        CleanUpResources();
    }

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

