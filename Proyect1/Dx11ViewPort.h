#pragma once

#include "ViewPort.h"

#include "Dx11ViewPort.h"
#include "GraphicsAPI.h" 

class Dx11ViewPort : public ViewPort
{
	friend class Dx11GraphicsAPI;
public:
    Dx11ViewPort() = default;

    virtual ~Dx11ViewPort() {CleanUpResources();}

protected:

    void CleanUpResources() override{}

};
