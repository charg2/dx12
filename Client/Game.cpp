#include "pch.h"
#include "Game.h"
#include "Engine.h"

shared_ptr<mala::mesh> mesh = make_shared<mala::mesh>();
shared_ptr<mala::shader> shader = make_shared<mala::shader>();

namespace mala
{
    void game::initialize( window_info& info )
    {
		g_engine->initialize( info );

		vector<Vertex> vec( 3 );
		vec[ 0 ].pos = Vec3( 0.f, 0.5f, 0.5f );
		vec[ 0 ].color = Vec4( 1.f, 0.f, 0.f, 1.f );
		vec[ 1 ].pos = Vec3( 0.5f, -0.5f, 0.5f );
		vec[ 1 ].color = Vec4( 0.f, 1.0f, 0.f, 1.f );
		vec[ 2 ].pos = Vec3( -0.5f, -0.5f, 0.5f );
		vec[ 2 ].color = Vec4( 0.f, 0.f, 1.f, 1.f );
		::mesh->init( vec );

		::shader->init( L"..\\Resources\\Shader\\default.hlsli" );

		g_engine->get_cmd_queue()->wait_sync();
    }


    void game::update()
    {
		g_engine->render_begin();

		::shader->update();
		::mesh->render();

		g_engine->render_end();
    }
}

