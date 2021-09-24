#include "pch.h"
#include "constant_buffer.h"
#include "engine_pch.h"
#include "engine.h"

mala::constant_buffer::constant_buffer()
{
}

mala::constant_buffer::~constant_buffer()
{
}

void mala::constant_buffer::init( uint32 size, uint32 count )
{
    _element_size = ( size + 255 ) & ~255;
    _element_count = count;

    _create_buffer();
}

void mala::constant_buffer::clear()
{
    _current_index = 0;
}

void mala::constant_buffer::push_data( int32 root_param_idx, void* buffer, uint32 size )
{
    assert( _current_index < _element_size );


    ::memcpy( &_mapped_buffer[ _current_index * _element_size ], buffer, size );

    D3D12_GPU_VIRTUAL_ADDRESS address = get_gpu_virtual_address( _current_index );
}

void mala::constant_buffer::_create_buffer()
{
    uint32 buffer_size = _element_size * _element_count;
    D3D12_HEAP_PROPERTIES heap_property = CD3DX12_HEAP_PROPERTIES( D3D12_HEAP_TYPE_UPLOAD );
    D3D12_RESOURCE_DESC   desc = CD3DX12_RESOURCE_DESC::Buffer( buffer_size );

    DEVICE->CreateCommittedResource(
    &heap_property,
    D3D12_HEAP_FLAG_NONE,
    &desc,
    D3D12_RESOURCE_STATE_GENERIC_READ,
    nullptr,
    IID_PPV_ARGS(&_cbv_buffer) );
}

D3D12_GPU_VIRTUAL_ADDRESS mala::constant_buffer::get_gpu_virtual_address( uint32 index )
{
    return D3D12_GPU_VIRTUAL_ADDRESS();
}

