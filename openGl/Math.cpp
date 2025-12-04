#pragma once
#include <array>
#include <cmath>

struct Vec3 { float x, y, z; };

using Mat4 = std::array<float, 16>; // column-major

inline Mat4 Identity()
{
    Mat4 m = { 0 };
    m[0] = m[5] = m[10] = m[15] = 1.0f;
    return m;
}

inline Vec3 Sub(const Vec3& a, const Vec3& b) { return { a.x - b.x, a.y - b.y, a.z - b.z }; }

inline Vec3 Normalize(const Vec3& v)
{
    float n = std::sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
    if (n == 0.0f) return { 0,0,0 };
    return { v.x / n, v.y / n, v.z / n };
}

inline Vec3 Cross(const Vec3& a, const Vec3& b)
{
    return { a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x };
}
inline float Dot(const Vec3& a, const Vec3& b) { return a.x * b.x + a.y * b.y + a.z * b.z; }

inline Mat4 Multiply(const Mat4& A, const Mat4& B)
{
    Mat4 R;
    for (int col = 0; col < 4; ++col)
    {
        for (int row = 0; row < 4; ++row)
        {
            float sum = 0.0f;
            for (int k = 0; k < 4; ++k)
            {
                sum += A[k * 4 + row] * B[col * 4 + k];
            }
            R[col * 4 + row] = sum;
        }
    }
    return R;
}

inline Mat4 Perspective(float fovyRadians, float aspect, float znear, float zfar)
{
    float f = 1.0f / std::tan(fovyRadians * 0.5f);
    Mat4 m = { 0 };
    m[0] = f / aspect;
    m[5] = f;
    m[10] = (zfar + znear) / (znear - zfar);
    m[11] = -1.0f;
    m[14] = (2.0f * zfar * znear) / (znear - zfar);
    m[15] = 0.0f;
    return m;
}

inline Mat4 LookAt(const Vec3& eye, const Vec3& center, const Vec3& up)
{
    Vec3 f = Normalize(Sub(center, eye));
    Vec3 s = Normalize(Cross(f, up));
    Vec3 u = Cross(s, f);

    Mat4 m = Identity();

    // first column = s
    m[0] = s.x; m[1] = s.y; m[2] = s.z; m[3] = 0.0f;
    // second column = u
    m[4] = u.x; m[5] = u.y; m[6] = u.z; m[7] = 0.0f;
    // third column = -f
    m[8] = -f.x; m[9] = -f.y; m[10] = -f.z; m[11] = 0.0f;
    // translation
    m[12] = -Dot(s, eye);
    m[13] = -Dot(u, eye);
    m[14] = Dot(f, eye);
    m[15] = 1.0f;

    return m;
}

inline Mat4 Rotate(float angleRadians, const Vec3& axis)
{
    Vec3 a = Normalize(axis);
    float c = std::cos(angleRadians);
    float s = std::sin(angleRadians);
    float t = 1.0f - c;

    Mat4 m = Identity();

    // column-major assignment
    m[0] = c + a.x * a.x * t;
    m[1] = a.x * a.y * t + a.z * s;
    m[2] = a.x * a.z * t - a.y * s;
    m[3] = 0.0f;

    m[4] = a.x * a.y * t - a.z * s;
    m[5] = c + a.y * a.y * t;
    m[6] = a.y * a.z * t + a.x * s;
    m[7] = 0.0f;

    m[8] = a.x * a.z * t + a.y * s;
    m[9] = a.y * a.z * t - a.x * s;
    m[10] = c + a.z * a.z * t;
    m[11] = 0.0f;

    m[12] = m[13] = m[14] = 0.0f;
    m[15] = 1.0f;

    return m;
}