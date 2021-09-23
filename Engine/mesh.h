#pragma once

// [����Ƽ¯]�� ���� �������� �̷���� ��ü
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