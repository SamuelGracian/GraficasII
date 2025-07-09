#include "RenderMaterial.h"

void RenderMaterial::BindConstantbuffer(std::weak_ptr<ConstantBuffer>& buffer, const uint32_t slot)
{
    if (m_constantbuffers.size() <= slot)
    {
        std::cout << "Slot doesnt fit the vector" << std::endl;
        return;
    }
    m_constantbuffers[slot] = buffer;
}

void RenderMaterial::BindSampler(std::weak_ptr<Sampler>& sampler, const uint32_t slot)
{
    if (m_samplers.size() <= slot)
    {
        std::cout << "Slot doesnt fit the vector" << std::endl;
        return;
    }
    m_samplers[slot] = sampler;
}

void RenderMaterial::BindTexture(std::weak_ptr<Texture> texture, const uint32_t slot)
{
    if (m_textures.size() <= slot)
    {
        std::cout << "Slot doesnt fit the vector" << std::endl;
        return;
    }
    m_textures[slot] = texture;
}
