#include "stdafx.h"

#include "DXGIApi.h"

namespace SlimDX
{
	namespace DXGI
	{
		DXGIApi::DXGIApi()
		{
		}
		
		IFactoryDXGI^ DXGIApi::CreateFactory() {
			return nullptr;// gcnew FactoryDXGI( this, 0 );
		}
	}
}