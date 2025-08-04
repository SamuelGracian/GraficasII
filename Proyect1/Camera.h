#pragma once
#include "Base.h"

using namespace DirectX;

class Camera
{
public:
    Camera()
        : m_Eye(XMVectorSet(0.0f, 3.0f, -6.0f, 0.0f)),
        m_At(XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f)),
        m_Up(XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f))
    {
    }

    void SetEye(const XMVECTOR& eye);
    void SetAt(const XMVECTOR& at);
    void SetUp(const XMVECTOR& up);

    XMVECTOR GetEye() const;
    XMVECTOR GetAt()  const;
    XMVECTOR GetUp()  const;

private:
    XMVECTOR m_Eye;
    XMVECTOR m_At;
    XMVECTOR m_Up;
};

