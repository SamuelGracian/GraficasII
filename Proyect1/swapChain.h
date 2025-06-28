#pragma once
#include "Base.h"

class  SwapChain
{
public:
	~SwapChain() = default;
	virtual void Present(uint32_t sync = 1, uint32_t flags = 0) = 0;
};

class Dx11SwapChain : public SwapChain
{
    Dx11SwapChain(IDXGISwapChain* swapChain)
        : m_swapChain(swapChain) {
    }

    ~Dx11SwapChain()
    {
        if (m_swapChain) m_swapChain->Release();
    }

    void Present(UINT syncInterval = 1, UINT flags = 0) override {
        if (m_swapChain) m_swapChain->Present(syncInterval, flags);
    }

    IDXGISwapChain* GetSwapChain() const { return m_swapChain; }

private:
    IDXGISwapChain* m_swapChain;
};