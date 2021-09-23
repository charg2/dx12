#include "pch.h"
#include "engine.h"

void mala::engine::initialize( const window_info& info )
{
    _window = info;
    resize_window( info.width, info.height );

    // �׷��� ȭ�� ũ�� ����
    _viewport = { 0, 0, static_cast<FLOAT>( info.width ), static_cast<FLOAT>( info.height ), 0.0f, 1.0f };
    _scissor_rect = CD3DX12_RECT( 0, 0, info.width, info.height );

    _device         = make_shared< device          >();
    _cmd_queue      = make_shared< command_queue   >();
    _swap_chain     = make_shared< swap_chain      >();
    _root_signature = make_shared< root_signature  >();


    _device->initialize();
    _cmd_queue->init( _device->get_device(), _swap_chain );
    _swap_chain->init( info, _device->get_device(), _device->get_dxgi(), _cmd_queue->get_cmd_queue() );
    _root_signature->init( _device->get_device() );
}

void mala::engine::render()
{
    render_begin();

    // TODO : ������ ��ü�� �׷��ش�

    render_end();
}

void mala::engine::render_begin()
{
    _cmd_queue->render_begin( &_viewport, &_scissor_rect );
}

void mala::engine::render_end()
{
    _cmd_queue->render_end();
}


void mala::engine::resize_window( int32 width, int32 heigth )
{
    _window.height = heigth;
    _window.width  = width;

    RECT rect = { 0, 0, width, heigth };
    // windows ũ�� ����
    ::AdjustWindowRect( &rect, WS_OVERLAPPEDWINDOW, false );
    // ������ ���ϴ� ��ġ ����
    ::SetWindowPos( _window.hwnd, 0, 100, 100, width, heigth, 0 );
}
