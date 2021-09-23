#pragma once

// [계약서 / 결재]

// CPU [        ]    GPU [        ]
// 한국 [        ]   베트남 [       ]

namespace mala
{
	class root_signature
	{
	public:
		void init( ComPtr<ID3D12Device> device );

		ComPtr<ID3D12RootSignature>	get_signature()
		{
			return _signature;
		}

	private:
		ComPtr<ID3D12RootSignature>	_signature;
	};
}
