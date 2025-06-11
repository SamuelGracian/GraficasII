#pragma once

#include "Base.h"

class  RenderResource
{
public:
	RenderResource() = default;
	virtual ~RenderResource() = default;


protected:
	virtual void CleanUpResources() = 0;

};