
#include "IndexBuffer.h"

Dx11IndexBuffer::Dx11IndexBuffer(ID3D11Device* device, const void* data, size_t size)
{
    D3D11_BUFFER_DESC desc = {};
    desc.Usage = D3D11_USAGE_DEFAULT;
    desc.ByteWidth = static_cast<UINT>(size);
    desc.BindFlags = D3D11_BIND_INDEX_BUFFER;

    D3D11_SUBRESOURCE_DATA initData = {};
    initData.pSysMem = data;

    ID3D11Buffer* raw = nullptr;
    if (SUCCEEDED(device->CreateBuffer(&desc, &initData, &raw))) {
        m_buffer = std::shared_ptr<ID3D11Buffer>(raw, BufferDeleter());
    }
}
