#pragma once

namespace mala
{
	class swap_chain
	{
	public:
		void init( const window_info& info, ComPtr<ID3D12Device> device, ComPtr<IDXGIFactory> dxgi, ComPtr<ID3D12CommandQueue> cmdQueue );
		void present();
		void swap_index();

		ComPtr<IDXGISwapChain> get_swap_chain()
		{
			return _swapChain;
		}
		ComPtr<ID3D12Resource> get_render_target( int32 index )
		{
			return _rtvBuffer[ index ];
		}

		ComPtr<ID3D12Resource> get_back_rtv_buffer()
		{
			return _rtvBuffer[ _backBufferIndex ];
		}
		D3D12_CPU_DESCRIPTOR_HANDLE get_back_rtv()
		{
			return _rtvHandle[ _backBufferIndex ];
		}

	private:
		void create_swap_chain( const window_info& info, ComPtr<IDXGIFactory> dxgi, ComPtr<ID3D12CommandQueue> cmdQueue );
		void create_rtv( ComPtr<ID3D12Device> device );

	private:
		ComPtr<IDXGISwapChain>	_swapChain;

		ComPtr<ID3D12Resource>			_rtvBuffer[ SWAP_CHAIN_BUFFER_COUNT ];
		ComPtr<ID3D12DescriptorHeap>	_rtvHeap;
		D3D12_CPU_DESCRIPTOR_HANDLE		_rtvHandle[ SWAP_CHAIN_BUFFER_COUNT ];

		uint32					_backBufferIndex = 0;
	};
}