#pragma once

// [일감 기술서] 외주 인력들이 뭘 해야할지 기술

namespace mala
{
	class shader
	{
	public:
		void init( const wstring& path );
		void update();

	private:
		void create_shader( const wstring& path, const string& name, const string& version, ComPtr<ID3DBlob>& blob, D3D12_SHADER_BYTECODE& shaderByteCode );
		void create_vertex_shader( const wstring& path, const string& name, const string& version );
		void create_pixel_shader( const wstring& path, const string& name, const string& version );

	private:
		ComPtr<ID3DBlob>					_vsBlob;
		ComPtr<ID3DBlob>					_psBlob;
		ComPtr<ID3DBlob>					_errBlob;

		ComPtr<ID3D12PipelineState>			_pipelineState;
		D3D12_GRAPHICS_PIPELINE_STATE_DESC  _pipelineDesc = {};
	};

}