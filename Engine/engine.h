#pragma once

#include "device.h"
#include "command_queue.h"
#include "swap_chain.h"
#include "root_signature.h"
#include "mesh.h"
#include "shader.h"

namespace mala
{
    //class device;
    //class command_queue;
    //class swap_chain;
    //class descriptor_heap;

    class engine
    {
    public:
        void initialize( const window_info& info );
        void render();

    public:
        shared_ptr<device> get_device()
        {
            return _device;
        }
        shared_ptr<command_queue> get_cmd_queue()
        {
            return _cmd_queue;
        }
        shared_ptr<swap_chain> GetSwapChain()
        {
            return _swap_chain;
        }
        shared_ptr<root_signature> get_root_signature()
        {
            return _root_signature;
        }
    public:
        void render_begin();
        void render_end();

        void resize_window( int32 width, int32 hegith );

    private:
        // 그렺리 화면 크기 과녈ㄴ
        window_info     _window;
        D3D12_VIEWPORT  _viewport{};
        D3D12_RECT      _scissor_rect{};

        shared_ptr< device         > _device;
        shared_ptr< command_queue  > _cmd_queue;
        shared_ptr< swap_chain     > _swap_chain;
        shared_ptr< root_signature > _root_signature;
    };
}

