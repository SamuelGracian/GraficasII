#pragma once

#include "ConstantBuffer.h"
#include "Vertexbuffer.h"
#include "Indexbuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"

//Interface for graphics Api

class GraphicsAPI
{
public:
	GraphicsAPI();
	virtual ~GraphicsAPI() = 0;

	//Buffers functions
	virtual ConstanBuffer* CreateConstantBuffer() = 0;
	virtual VertexBuffer* CreateVertexBuffer() = 0;
	virtual IndexBuffer* CreateIndexBuffer() = 0;

	//Shader Functions
	virtual VertexShader CreateVertexShader() = 0; 
	virtual PixelShader* CreatePixelShader() = 0;
};