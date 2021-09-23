#pragma once

// [유니티짱]과 같이 정점으로 이루어진 물체
namespace mala
{
	class mesh
	{
	public:
		void init( vector<Vertex>& vec );
		void render();

	private:
		ComPtr<ID3D12Resource>		_vertexBuffer;
		D3D12_VERTEX_BUFFER_VIEW	_vertexBufferView = {};
		uint32						_vertexCount = 0;
	};
}