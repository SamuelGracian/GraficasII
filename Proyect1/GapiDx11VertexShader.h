#pragma once
#include <d3dcommon.h>
#include <d3d11.h>

#include "GraphicsAPI.h"
#include "GapiRenderResources.h"


/// <summary>
/// Base class for vertex shaders
/// </summary>
class GapiVertexShader
{
protected:
	GapiVertexShader() = default;
	virtual ~GapiVertexShader() = default;

};


/// <summary>
/// Interface for DirectX 11 vertex shaders
/// </summary>
class InterDx11VertexShader : public GapiVertexShader, public GapiRenderResources
{
	friend GraphicsAPI;
{


public:
	GapiDx11VertexShader() = default;
	virtual ~GapiDx11VertexShader() = default;

protected:
	virtual void CleanUpResources() override
	{
	}


private:
    ID3DBlob* m_Blob = nullptr;
	ID3D11VertexShader* m_VertexShader = nullptr;
	ID3D11InputLayout* m_InputLayout = nullptr;
};
