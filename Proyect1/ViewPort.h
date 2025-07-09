#pragma once 
#include "RenderResource.h"
class ViewPort : public RenderResource
{
	ViewPort();
	virtual ~ViewPort();

    virtual void Set(int x, int y, int width, int height) = 0;
    virtual int GetX() const = 0;
    virtual int GetY() const = 0;
    virtual int GetWidth() const = 0;
    virtual int GetHeight() const = 0;
};