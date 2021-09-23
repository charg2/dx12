#include "pch.h"
#include "command_queue.h"
#include "swap_chain.h"


mala::command_queue::~command_queue()
{
	::CloseHandle( _fenceEvent );
}

void mala::command_queue::init( ComPtr<ID3D12Device> device, shared_ptr<swap_chain> swapChain )
{
	_swapChain = swapChain;

	D3D12_COMMAND_QUEUE_DESC queueDesc = {};
	queueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
	queueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;

	device->CreateCommandQueue( &queueDesc, IID_PPV_ARGS( &_cmdQueue ) );

	// - D3D12_COMMAND_LIST_TYPE_DIRECT : GPU�� ���� �����ϴ� ���� ���
	device->CreateCommandAllocator( D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS( &_cmdAlloc ) );

	// GPU�� �ϳ��� �ý��ۿ����� 0����
	// DIRECT or BUNDLE
	// Allocator
	// �ʱ� ���� (�׸��� ������ nullptr ����)
	device->CreateCommandList( 0, D3D12_COMMAND_LIST_TYPE_DIRECT, _cmdAlloc.Get(), nullptr, IID_PPV_ARGS( &_cmdList ) );

	// CommandList�� Close / Open ���°� �ִµ�
	// Open ���¿��� Command�� �ִٰ� Close�� ���� �����ϴ� ����
	_cmdList->Close();

	// CreateFence
	// - CPU�� GPU�� ����ȭ �������� ���δ�
	device->CreateFence( 0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS( &_fence ) );
	_fenceEvent = ::CreateEvent( nullptr, FALSE, FALSE, nullptr );
}

void mala::command_queue::wait_sync()
{
	// Advance the fence value to mark commands up to this fence point.
	_fenceValue++;

	// Add an instruction to the command queue to set a new fence point.  Because we 
	// are on the GPU timeline, the new fence point won't be set until the GPU finishes
	// processing all the commands prior to this Signal().
	_cmdQueue->Signal( _fence.Get(), _fenceValue );

	// Wait until the GPU has completed commands up to this fence point.
	if ( _fence->GetCompletedValue() < _fenceValue )
	{
		// Fire event when GPU hits current fence.  
		_fence->SetEventOnCompletion( _fenceValue, _fenceEvent );

		// Wait until the GPU hits current fence event is fired.
		::WaitForSingleObject( _fenceEvent, INFINITE );
	}
}


void mala::command_queue::render_begin( const D3D12_VIEWPORT* vp, const D3D12_RECT* rect )
{
	_cmdAlloc->Reset();
	_cmdList->Reset( _cmdAlloc.Get(), nullptr );

	D3D12_RESOURCE_BARRIER barrier = CD3DX12_RESOURCE_BARRIER::Transition(
		_swapChain->get_back_rtv_buffer().Get(),
		D3D12_RESOURCE_STATE_PRESENT, // ȭ�� ���
		D3D12_RESOURCE_STATE_RENDER_TARGET ); // ���� �����

	_cmdList->ResourceBarrier( 1, &barrier );

	// Set the viewport and scissor rect.  This needs to be reset whenever the command list is reset.
	_cmdList->RSSetViewports( 1, vp );
	_cmdList->RSSetScissorRects( 1, rect );

	// Specify the buffers we are going to render to.
	D3D12_CPU_DESCRIPTOR_HANDLE backBufferView = _swapChain->get_back_rtv();
	_cmdList->ClearRenderTargetView( backBufferView, Colors::LightSteelBlue, 0, nullptr );
	_cmdList->OMSetRenderTargets( 1, &backBufferView, FALSE, nullptr );
}

void mala::command_queue::render_end()
{
	D3D12_RESOURCE_BARRIER barrier = CD3DX12_RESOURCE_BARRIER::Transition(
		_swapChain->get_back_rtv_buffer().Get(),
		D3D12_RESOURCE_STATE_RENDER_TARGET, // ���� �����
		D3D12_RESOURCE_STATE_PRESENT ); // ȭ�� ���

	_cmdList->ResourceBarrier( 1, &barrier );
	_cmdList->Close();

	// Ŀ�ǵ� ����Ʈ ����
	ID3D12CommandList* cmdListArr[] = { _cmdList.Get() };
	_cmdQueue->ExecuteCommandLists( _countof( cmdListArr ), cmdListArr );

	_swapChain->present();

	// Wait until frame commands are complete.  This waiting is inefficient and is
	// done for simplicity.  Later we will show how to organize our rendering code
	// so we do not have to wait per frame.
	wait_sync();

	_swapChain->swap_index();
}