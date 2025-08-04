#include "Camera.h"

void Camera::SetEye(const XMVECTOR& eye)
{
	m_Eye = eye;
}

void Camera::SetAt(const XMVECTOR& at)
{
	m_At = at;
}

void Camera::SetUp(const XMVECTOR& up)
{
	m_Up = up;
}

XMVECTOR Camera::GetEye() const
{
	return m_Eye;
}

XMVECTOR Camera::GetAt() const
{
	return m_At;
}

XMVECTOR Camera::GetUp() const
{
	return m_Up;
}
