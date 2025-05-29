#pragma once

class GapiRenderResources
{
protected:
	GapiRenderResources() = default;
	virtual ~GapiRenderResources() = default;
	virtual void CleanUpResources() = 0;
};