#pragma once
#include <vector>
#include <memory>


#include "RenderMaterial.h"

class ConstantBuffer;

class Sampler;

class ShaderResourceTexture;

class PixelShader;

class VertexShader;

class IndexBuffer;

class VertexBuffer;

class PrimitiveTopology;

class RenderTarget;

class RenderElement
{
public:
	RenderElement();
	~RenderElement();

	void BindConstantBuffer(std::weak_ptr<ConstantBuffer>& buffer, const uint32_t slot);

	void BindRenderTarget(std::weak_ptr<RenderTarget>& RT, const uint32_t slot);

	void BindShaderTexture(std::weak_ptr<ShaderResourceTexture>& shaderTexture, uint32_t slot);

	void BindSampler(std::weak_ptr<Sampler>& sampler, const  uint32_t slot);

	void BindPixelShader(std::weak_ptr<PixelShader>& pixelShader);

	void BindVertexShader(std::weak_ptr<VertexShader>& vertexShader);

	void BindTpology(std::weak_ptr<PrimitiveTopology>& topology);

	void BindIndexBuffer(std::weak_ptr<IndexBuffer>& indexBuffer);

	void BindVertexbuffers(std::weak_ptr<VertexBuffer>& vertexBuffer);

	void BindRenderMaterial(std::weak_ptr<RenderMaterial>& renderMaterial);

private:
	std::vector<std::weak_ptr<ConstantBuffer>> m_constantbuffers;
	std::vector<std::weak_ptr<RenderTarget>> m_RenderTargets;
	std::vector<std::weak_ptr<ShaderResourceTexture>> m_shaderTextures;
	std::vector<std::weak_ptr<Sampler>> m_samplers;

	std::weak_ptr<PixelShader> m_pixelShader;
	std::weak_ptr<VertexShader> m_vertexShader;
	std::weak_ptr<IndexBuffer> m_indexBuffer;
	std::weak_ptr<VertexBuffer> m_vertexBuffer;
	std::weak_ptr<PrimitiveTopology> m_topology;

	std::weak_ptr<RenderMaterial> m_renderMaterrial;
};

