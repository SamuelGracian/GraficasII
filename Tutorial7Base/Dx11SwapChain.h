#pragma once
#include "SwapChain.h"
#include <d3d11_1.h>

class Dx11SwapChain : public SwapChain
{
public:
	Dx11SwapChain();

	~Dx11SwapChain() = default;

	IDXGISwapChain* GetSwapChain() const;

private:

	IDXGISwapChain* m_swapChain;
};