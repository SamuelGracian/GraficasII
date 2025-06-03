
#include <memory>
#include "GraphicsAPI.h"

GraphicsAPI::GraphicsAPI(HWND WinHandler ,UINT width, UINT height)
{
    RECT rc;
    GetClientRect(WinHandler, &rc);

    UINT createDeviceFlags = 0;
#ifdef _DEBUG
    createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

    D3D_DRIVER_TYPE driverTypes[] =
    {
        D3D_DRIVER_TYPE_HARDWARE,
        D3D_DRIVER_TYPE_WARP,
        D3D_DRIVER_TYPE_REFERENCE,
    };
    UINT numDriverTypes = ARRAYSIZE(driverTypes);

    D3D_FEATURE_LEVEL featureLevels[] =
    {
        D3D_FEATURE_LEVEL_11_1,
        D3D_FEATURE_LEVEL_11_0,
        D3D_FEATURE_LEVEL_10_1,
        D3D_FEATURE_LEVEL_10_0,
    };
    UINT numFeatureLevels = ARRAYSIZE(featureLevels);

    HRESULT hr = S_OK;

    for (UINT i = 0; i < numDriverTypes; ++i)
    {
        driverType = driverTypes[i];
        hr = D3D11CreateDevice(
            nullptr,
            driverType,
            nullptr,
            createDeviceFlags,
            featureLevels,
            numFeatureLevels,
            D3D11_SDK_VERSION,
            &device,
            &featureLevel,
            &context
        );

        if (hr == E_INVALIDARG)
        {
            hr = D3D11CreateDevice(
                nullptr,
                driverType,
                nullptr,
                createDeviceFlags,
                &featureLevels[1],
                numFeatureLevels - 1,
                D3D11_SDK_VERSION,
                &device,
                &featureLevel,
                &context
            );
        }

        if (SUCCEEDED(hr))
            break;
    }

    if (FAILED(hr))
    {
        MessageBox(WinHandler, L"Falló la creación del dispositivo Direct3D.", L"Error", MB_OK);
        return;
    }

}



std::weak_ptr<InterDx11ConstantBuffer> GraphicsAPI::CreateConstantBuffer()
{
    auto buffer = std::make_shared<InterDx11ConstantBuffer>();

    return std::weak_ptr<InterDx11ConstantBuffer>(buffer);
}

std::weak_ptr<InterDx11IndexBuffer> GraphicsAPI::CreateIndexBuffer()
{
    auto buffer = std::make_shared<InterDx11IndexBuffer>();

    return std::weak_ptr<InterDx11IndexBuffer>(buffer);
}

std::weak_ptr<InterDx11VertexBuffers> GraphicsAPI::CreateVertexBuffer()
{
    auto buffer = std::make_shared<InterDx11VertexBuffers>();

    return std::weak_ptr<InterDx11VertexBuffers>(buffer);
}

