#pragma once

namespace mala
{
    class device
    {
    public:
        void initialize();

        ComPtr<IDXGIFactory> get_dxgi()
        {
            return _dxgi;
        }
        ComPtr<ID3D12Device> get_device()
        {
            return _device;
        }

    private:
        ComPtr<ID3D12Debug>		_debugController;
        ComPtr<IDXGIFactory>	_dxgi;		// 화면 관련 기능들
        ComPtr<ID3D12Device>	_device;	// 각종 객체 생성
    };
}
