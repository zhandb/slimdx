#include "stdafx.h"

#include "Device10.h"
#include "Direct3D10Recorder.h"

#include "../Common/Utilities.h"
#include "RenderTargetView10.h"
#include "Buffer10.h"

using namespace System;

namespace SlimDX
{
	namespace Direct3D10
	{
		Device10::Device10( ID3D10Device* native )
		: ComObject( native )
		{
		}
		
		Device10::Device10( IntPtr native )
		: ComObject( native )
		{
		}
		
		IRenderTargetView10^ Device10::CreateRenderTargetView( IResource10^ resource ) {
			if( resource == nullptr )
				throw gcnew ArgumentNullException( "resource" );
			
			//TODO: Hack.
			ID3D10Resource* nativeResource = reinterpret_cast<ID3D10Resource*>(Utilities::ToUnknown( resource ));
			ID3D10RenderTargetView* nativeView = 0;
			if( RecordResult( NativePointer->CreateRenderTargetView( nativeResource, NULL, &nativeView ) ).IsSuccess )
				return gcnew RenderTargetView10( nativeView );
			return nullptr;
		}

		IBuffer10^ Device10::CreateEmptyBuffer(BufferDescription10 bufferDescription) {
			return CreateBuffer<char>(bufferDescription, nullptr);
		}

		generic<typename T> where T : value class
		IBuffer10^ Device10::CreateBuffer(BufferDescription10 bufferDescription, array<T>^ bufferData) {
			D3D10_BUFFER_DESC desc = {
				bufferDescription.SizeInBytes,
				(D3D10_USAGE)bufferDescription.Usage,
				(UINT)bufferDescription.BindFlags,
				(UINT)bufferDescription.CpuAccessFlags,
				(UINT)bufferDescription.OptionFlags
			};

			ID3D10Buffer* buffer;

			if(bufferData != nullptr) {
				pin_ptr<T> bufferPtr = &bufferData[0];
				D3D10_SUBRESOURCE_DATA bufferDataRs = {  bufferPtr };

				if(RecordResult(NativePointer->CreateBuffer(&desc, &bufferDataRs, &buffer)).IsSuccess)
					return gcnew Buffer10(buffer);
			} else {
				if(RecordResult(NativePointer->CreateBuffer(&desc, nullptr, &buffer)).IsSuccess)
					return gcnew Buffer10(buffer);
			}
			return nullptr;
		}

		void Device10::ClearRenderTargetView(IRenderTargetView10^ renderTargetView, System::Drawing::Color clearColor) {
			float clearColorFloats[4] = {(float)clearColor.R / 255, (float)clearColor.G / 255, (float)clearColor.B / 255, (float)clearColor.A / 255 };
			ID3D10RenderTargetView* nativeView = reinterpret_cast<ID3D10RenderTargetView*>(Utilities::ToUnknown(renderTargetView));
			NativePointer->ClearRenderTargetView(nativeView, clearColorFloats);
		}

		void Device10::IASetPrimitiveTopology(PrimitiveTopology10 primitiveTopology) {
			NativePointer->IASetPrimitiveTopology(static_cast<D3D10_PRIMITIVE_TOPOLOGY>(primitiveTopology));
		}

		void Device10::IASetVertexBuffer(int startSlot, VertexBufferBinding10 vertexBufferBinding) {
			ID3D10Buffer* buffer = reinterpret_cast<ID3D10Buffer*>(Utilities::ToUnknown(vertexBufferBinding.VertexBuffer));
			NativePointer->IASetVertexBuffers(startSlot, 1, &buffer, reinterpret_cast<UINT*>(&vertexBufferBinding.Stride), reinterpret_cast<UINT*>(&vertexBufferBinding.Offset));
		}

		void Device10::IASetVertexBuffers(int startSlot, array<VertexBufferBinding10>^ vertexBufferBindings) {
			ID3D10Buffer* buffers[16];
			UINT strides[16];
			UINT offsets[16];
			
			for(int i = 0; i < vertexBufferBindings->Length; ++i) {
				buffers[i] = reinterpret_cast<ID3D10Buffer*>(Utilities::ToUnknown(vertexBufferBindings[i].VertexBuffer));
				strides[i] = vertexBufferBindings[i].Stride;
				offsets[i] = vertexBufferBindings[i].Offset;
			}

			NativePointer->IASetVertexBuffers(startSlot, vertexBufferBindings->Length, buffers, strides, offsets);
		}

		void Device10::RSSetViewport(Viewport10 viewport) {
			NativePointer->RSSetViewports(1, reinterpret_cast<D3D10_VIEWPORT*>(&viewport));
		}

		void Device10::RSSetViewports(array<Viewport10>^ viewports) {
			pin_ptr<Viewport10> vps = &viewports[0];
			NativePointer->RSSetViewports(viewports->Length, reinterpret_cast<D3D10_VIEWPORT*>(vps));
		}

		void Device10::OMSetRenderTargets(array<IRenderTargetView10^>^ renderTargetViews, IDepthStencilView10^ depthStencilView) {
			ID3D10RenderTargetView* renderTargetViewsArray[D3D10_SIMULTANEOUS_RENDER_TARGET_COUNT];
			for(int i = 0; i < renderTargetViews->Length; ++i) {
				renderTargetViewsArray[i] = reinterpret_cast<ID3D10RenderTargetView*>(Utilities::ToUnknown( renderTargetViews[i] ));
			}

			ID3D10DepthStencilView* depthStencilViewPtr = NULL;
			if(depthStencilView != nullptr)
				depthStencilViewPtr = (ID3D10DepthStencilView*)Utilities::ToUnknown( depthStencilView );

			NativePointer->OMSetRenderTargets(renderTargetViews->Length, renderTargetViewsArray, depthStencilViewPtr);
		}

		void Device10::OMSetRenderTarget(IRenderTargetView10^ renderTargetView, IDepthStencilView10^ depthStencilView) {
			ID3D10RenderTargetView* renderTargetViewsArray[1] = { (ID3D10RenderTargetView*)Utilities::ToUnknown( renderTargetView ) };

			ID3D10DepthStencilView* depthStencilViewPtr = NULL;
			if(depthStencilView != nullptr)
				depthStencilViewPtr = reinterpret_cast<ID3D10DepthStencilView*>(Utilities::ToUnknown( depthStencilView ));

			NativePointer->OMSetRenderTargets(1, renderTargetViewsArray, depthStencilViewPtr);
		}
	}
}