/*
* Copyright (c) 2007 SlimDX Group
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
#pragma once

using namespace System;

namespace SlimDX
{
	namespace XInput
	{
		/// <summary>
		/// Specifies keystroke data returned by Controller.GetKeystroke
		/// </summary>
		public value class KeyStroke
		{
		private:
			GamepadKeyCode virtualKey;
            KeyStrokeFlags flags;
            UserIndex userIndex;
            int hidCode;

		public:
			/// <summary>
			/// Virtual-key code of the key, button, or stick movement.
			/// </summary>
			property GamepadKeyCode VirtualKey
            {
                GamepadKeyCode get() { return virtualKey; }
			internal:
                void set( GamepadKeyCode value ) { virtualKey = value; }
            }

			/// <summary>
			/// Combination of flags that indicate the keyboard state at the time of the input event.
			/// </summary>
            property KeyStrokeFlags Flags
            {
                KeyStrokeFlags get() { return flags; }
			internal:
                void set( KeyStrokeFlags value ) { flags = value; }
            }

			/// <summary>
			/// Index of the signed-in gamer associated with the device. Can be a value in the range 0�3.
			/// </summary>
			property SlimDX::XInput::UserIndex UserIndex
            {
                SlimDX::XInput::UserIndex get() { return userIndex; }
			internal:
                void set( SlimDX::XInput::UserIndex value ) { userIndex = value; }
            }

			/// <summary>
			/// HID code corresponding to the input. If there is no corresponding HID code, this value is zero.
			/// </summary>
            property int HidCode
            {
                int get() { return hidCode; }
                void set( int value ) { hidCode = value; }
            }
		};
	}
}