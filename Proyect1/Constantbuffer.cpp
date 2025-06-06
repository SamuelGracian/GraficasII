#include "ConstantBuffer.h"

Dx11ConstantBuffer::Dx11ConstantBuffer(ID3D11Device* device, size_t size)
{
    D3D11_BUFFER_DESC desc = {};
    desc.Usage = D3D11_USAGE_DEFAULT;
    desc.ByteWidth = static_cast<UINT>(size);
    desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

    ID3D11Buffer* raw = nullptr;
    if (SUCCEEDED(device->CreateBuffer(&desc, nullptr, &raw))) {
        m_buffer = std::shared_ptr<ID3D11Buffer>(raw, BufferDeleter());
    }
}
