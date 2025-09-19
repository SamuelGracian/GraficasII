#pragma once

#include "GRAPI.h"

class Dx11GraphicsAPI : public GraphicsAPI
{
	Dx11GraphicsAPI();
	~Dx11GraphicsAPI() = 0;

	//Buffer functions


	//Clean up function
	void CleanUpResources() override;
};