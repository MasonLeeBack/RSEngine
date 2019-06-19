/*

RSEngine
Copyright (c) 2019 Mason Lee Back

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

File name: Gamepad.h

*/

#pragma once
#ifndef _Gamepad_h_
#define _Gamepad_h_

namespace rs {
    enum class InputMap {
        INPUT_XBOX,
        INPUT_DS,
        INPUT_UNIQUE
    };

    enum class GamepadControls {
        GPD_BTN_ACTION1,
        GPD_BTN_ACTION2,
        GPD_BTN_ACTION3,
        GPD_BTN_ACTION4,
        GPD_BTN_START,
        GPD_BTN_SELECT,
        GPD_BTN_TRIGGER1,
        GPD_BTN_TRIGGER2,
        GPD_BTN_BUMPER1,
        GPD_BTN_BUMPER2,
        GPD_BTN_DPADUP,
        GPD_BTN_DPADDOWN,
        GPD_BTN_DPADLEFT,
        GPD_BTN_DPADRIGHT,
        GPD_JOY_JSTICK1,
        GPD_BTN_JSTICK1,
        GPD_JOY_JSTICK2,
        GPD_BTN_JSTICK2,
        GPD_BTN_UNIQUE
    };

} // namespace rs

#endif // _Gamepad_h_
