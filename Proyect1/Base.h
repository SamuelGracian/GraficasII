#pragma once

#include <memory>
#include <cstdint>

#include <d3d11.h>
#include <dxgi1_2.h>
#include <d3d11_1.h>
#include <directxmath.h>

#include <vector>
//#define RELEASE (A) if(A!=nullptr) {A->Release(); A=nullptr;}

#ifndef RELEASE
# define RELEASE(x) if(x) { x->Release(); x = nullptr; }
#endif