#pragma once
#include <cstdint>

#include "GapiRenderResources.h"
#include "GraphicsAPI.h"

class GapiBufferResource
{
public:
	virtual ~GapiBufferResource() = default;
	
	virtual ID3D11Buffer* GetRawBuffer() = 0;
};