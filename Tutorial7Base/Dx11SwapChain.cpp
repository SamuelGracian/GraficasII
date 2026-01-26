#pragma once

#include "Dx11SwapChain.h"

Dx11SwapChain::Dx11SwapChain()
	: m_swapChain(nullptr)
{}

IDXGISwapChain* Dx11SwapChain::GetSwapChain() const
{
	return m_swapChain;
}
