#pragma once
#include "SwapChain.h"

class Dx11SwapChain : public SwapChain
{
public:
	Dx11SwapChain()
		: m_swapChain(nullptr) 
	{};
	~Dx11SwapChain() = default;

	IDXGISwapChain* m_swapChain;
};