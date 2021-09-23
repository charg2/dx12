#pragma once

// ���� include
#include <Windows.h>
#include <tchar.h>
#include <memory>
#include <string>
#include <vector>
#include <array>
#include <list>
#include <map>
using namespace std;

#include "d3dx12.h"
#include <d3d12.h>
#include <wrl.h>
#include <d3dcompiler.h>
#include <dxgi.h>
#include <DirectXMath.h>
#include <DirectXPackedVector.h>
#include <DirectXColors.h>
using namespace DirectX;
using namespace DirectX::PackedVector;
using namespace Microsoft::WRL;

// ���� lib
#pragma comment(lib, "d3d12")
#pragma comment(lib, "dxgi")
#pragma comment(lib, "dxguid")
#pragma comment(lib, "d3dcompiler")

// ���� typedef
using int8 = __int8;
using int16 = __int16;
using int32 = __int32;
using int64 = __int64;
using uint8 = unsigned __int8;
using uint16 = unsigned __int16;
using uint32 = unsigned __int32;
using uint64 = unsigned __int64;
using Vec2 = XMFLOAT2;
using Vec3 = XMFLOAT3;
using Vec4 = XMFLOAT4;
using Matrix = XMMATRIX;

enum
{
    SWAP_CHAIN_BUFFER_COUNT = 2
};

struct window_info
{
    HWND   hwnd;
    int32  width;
    int32  height;
    bool   windowed;

};

struct Vertex
{
    Vec3 pos;
    Vec4 color;
};

#define DEVICE			g_engine->get_device()->get_device()
#define CMD_LIST		g_engine->get_cmd_queue()->get_cmd_list()
#define ROOT_SIGNATURE	g_engine->get_root_signature()->get_signature()


// forward declaration
namespace mala
{
    class engine;
}

extern std::unique_ptr< mala::engine > g_engine;

