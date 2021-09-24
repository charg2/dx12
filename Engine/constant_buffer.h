#pragma once

namespace mala
{
    class constant_buffer
    {
    public:
        constant_buffer();
        ~constant_buffer();

        void init( uint32 size, uint32 conunt );

        void clear();
        void push_data( int32 root_param_idx, void* buffer, uint32 size );

    private:
        void _create_buffer();
        D3D12_GPU_VIRTUAL_ADDRESS get_gpu_virtual_address( uint32 index );

    private:

        ComPtr<ID3D12Resource> _cbv_buffer;
        BYTE*                  _mapped_buffer = nullptr;
        uint32                 _element_size = 0;
        uint32                 _element_count = 0;
        uint32                 _current_index = 0;


    };
}

