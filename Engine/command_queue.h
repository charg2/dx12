#pragma once

namespace mala
{
    class swap_chain;
    class descriptor_heap;
}

namespace mala
{
	// Dx12 이후 일감 배분 방식 복잡
	class command_queue
	{
	
	public:
		~command_queue();
	
		void init( ComPtr<ID3D12Device> device, shared_ptr<mala::swap_chain> swapChain );
		void wait_sync();
	
		void render_begin( const D3D12_VIEWPORT* vp, const D3D12_RECT* rect );
		void render_end();
	
		ComPtr<ID3D12CommandQueue> get_cmd_queue()
		{
			return _cmdQueue;
		}
		ComPtr<ID3D12GraphicsCommandList> get_cmd_list()
		{
			return	_cmdList;
		}
	
	private:
		// CommandQueue : DX12에 등장
		// 외주를 요청할 때, 하나씩 요청하면 비효율적
		// [외주 목록]에 일감을 차곡차곡 기록했다가 한 방에 요청하는 것
		ComPtr<ID3D12CommandQueue>			_cmdQueue;
		ComPtr<ID3D12CommandAllocator>		_cmdAlloc;
		ComPtr<ID3D12GraphicsCommandList>	_cmdList;
	
		// Fence : 울타리(?)
		// CPU / GPU 동기화를 위한 간단한 도구
		ComPtr<ID3D12Fence>					_fence;
		uint32								_fenceValue = 0;
		HANDLE								_fenceEvent = INVALID_HANDLE_VALUE;
	
		shared_ptr<swap_chain>		_swapChain;
	};
}