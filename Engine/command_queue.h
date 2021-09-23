#pragma once

namespace mala
{
    class swap_chain;
    class descriptor_heap;
}

namespace mala
{
	// Dx12 ���� �ϰ� ��� ��� ����
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
		// CommandQueue : DX12�� ����
		// ���ָ� ��û�� ��, �ϳ��� ��û�ϸ� ��ȿ����
		// [���� ���]�� �ϰ��� �������� ����ߴٰ� �� �濡 ��û�ϴ� ��
		ComPtr<ID3D12CommandQueue>			_cmdQueue;
		ComPtr<ID3D12CommandAllocator>		_cmdAlloc;
		ComPtr<ID3D12GraphicsCommandList>	_cmdList;
	
		// Fence : ��Ÿ��(?)
		// CPU / GPU ����ȭ�� ���� ������ ����
		ComPtr<ID3D12Fence>					_fence;
		uint32								_fenceValue = 0;
		HANDLE								_fenceEvent = INVALID_HANDLE_VALUE;
	
		shared_ptr<swap_chain>		_swapChain;
	};
}