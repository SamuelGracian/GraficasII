#pragma once
#include <vector>
#include <memory>
#include<iostream>

class ConstantBuffer;

class Sampler;

class Texture;

class RenderMaterial
{
public:
	RenderMaterial() = default;
	~RenderMaterial();

	void BindConstantbuffer(std::weak_ptr<ConstantBuffer>& buffer, const uint32_t slot);

	void BindSampler(std::weak_ptr<Sampler>& sampler, const uint32_t slot);

	void BindTexture(std::weak_ptr<Texture> texture, const uint32_t slot);

private:
	std::vector<std::weak_ptr<ConstantBuffer>> m_constantbuffers;
	std::vector<std::weak_ptr<Sampler>> m_samplers;
	std::vector<std::weak_ptr<Texture>> m_textures;
};

