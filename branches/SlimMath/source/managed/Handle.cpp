/*
* Copyright (c) 2007-2009 SlimDX Group
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
#include "Handle.h"
#include <memory>

using namespace System;

namespace SlimMath
{
	generic<typename T>
	Handle<T>::Handle()
	{
		data = new float[sizeof(T)];
	}

	generic<typename T>
	Handle<T>::Handle(T value)
	{
		data = new float[sizeof(T)];
		memcpy(data, &value, sizeof(T));
	}

	generic<typename T>
	IntPtr Handle<T>::RawData::get()
	{
		return IntPtr(data);
	}

	generic<typename T>
	Handle<T>::operator SlimMath::Handle<T>^ (T value)
	{
		return gcnew Handle<T>(value);
	}

	generic<typename T>
	T Handle<T>::GetData()
	{
		T t;
		memcpy(&t, data, sizeof(T));
		return t;
	}

	CompoundHandle::CompoundHandle(array<IHandle^>^ handles)
	{
		Handles = handles;
	}

	generic<typename T>
	T CompoundHandle::GetResult(int resultIndex)
	{
		return safe_cast<Handle<T>^>(Handles[resultIndex])->GetData();
	}

	/*generic<typename T>
	T Handle::GetResult(int resultIndex)
	{
		T t;
		memcpy(&t, Results[resultIndex].Data, sizeof(T));
		return t;
	}*/
}