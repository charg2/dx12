#pragma once

// [��༭ / ����]

// CPU [        ]    GPU [        ]
// �ѱ� [        ]   ��Ʈ�� [       ]

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
