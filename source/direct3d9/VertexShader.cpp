/*
* Copyright (c) 2007-2008 SlimDX Group
* 
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
* 
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
* 
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
* THE SOFTWARE.
*/
#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <vcclr.h>
#include <memory>

#include "../ComObject.h"
#include "../Utilities.h"
#include "../StackAlloc.h"
#include "../DataStream.h"

#include "Direct3D9Exception.h"

#include "Device.h"
#include "VertexShader.h"

using namespace System;

namespace SlimDX
{
namespace Direct3D9
{
	VertexShader::VertexShader( IDirect3DVertexShader9* pointer )
	{
		Construct( pointer );
	}

	VertexShader::VertexShader( IntPtr pointer )
	{
		Construct( pointer, NativeInterface );
	}

	VertexShader::VertexShader( SlimDX::Direct3D9::Device^ device, ShaderBytecode^ function )
	{
		IDirect3DVertexShader9 *result;

		HRESULT hr = device->InternalPointer->CreateVertexShader( reinterpret_cast<const DWORD*>( function->Data->RawPointer ), &result );
		if( RECORD_D3D9( hr ).IsFailure )
			throw gcnew Direct3D9Exception( Result::Last );

		Construct( result );

		m_function = function;
	}

	VertexShader^ VertexShader::FromPointer( IDirect3DVertexShader9* pointer )
	{
		if( pointer == 0 )
			return nullptr;

		VertexShader^ tableEntry = safe_cast<VertexShader^>( ObjectTable::Find( static_cast<IntPtr>( pointer ) ) );
		if( tableEntry != nullptr )
		{
			pointer->Release();
			return tableEntry;
		}

		return gcnew VertexShader( pointer );
	}

	VertexShader^ VertexShader::FromPointer( IntPtr pointer )
	{
		if( pointer == IntPtr::Zero )
			throw gcnew ArgumentNullException( "pointer" );

		VertexShader^ tableEntry = safe_cast<VertexShader^>( ObjectTable::Find( static_cast<IntPtr>( pointer ) ) );
		if( tableEntry != nullptr )
		{
			return tableEntry;
		}

		return gcnew VertexShader( pointer );
	}

	SlimDX::Direct3D9::Device^ VertexShader::Device::get()
	{
		IDirect3DDevice9* device;

		HRESULT hr = InternalPointer->GetDevice( &device );
		
		if( RECORD_D3D9( hr ).IsFailure )
			return nullptr;

		return SlimDX::Direct3D9::Device::FromPointer( device );
	}

	ShaderBytecode^ VertexShader::Function::get()
	{
		if( m_function != nullptr )
			return m_function;

		UINT size;
		HRESULT hr = InternalPointer->GetFunction( NULL, &size );
		if( RECORD_D3D9( hr ).IsFailure )
			return nullptr;

		ID3DXBuffer *functionMemory;
		hr = D3DXCreateBuffer( size, &functionMemory );
		if( RECORD_D3D9( hr ).IsFailure )
			return nullptr;

		hr = InternalPointer->GetFunction( functionMemory->GetBufferPointer(), &size );
		if( FAILED( hr ) )
			functionMemory->Release();

		if( RECORD_D3D9( hr ).IsFailure )
			return nullptr;

		m_function = ShaderBytecode::FromPointer( functionMemory );

		return m_function;
	}
}
}