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

File name: RareInput.cpp

Notes: Right now, we only explicitly support ScePad until further notice.

*/

#include <Input/RareInput.h>
#include <Input/libScePad/RSScePad.h>

namespace rs {
    CInput* g_Input;
    Input::RSScePad g_scePad;

    bool CInput::Init() {
        if (g_scePad.Initialize()) {
            if (g_scePad.getControllerConnection()) {

            }
            currentGamepad = InputMap::INPUT_DS;
        }

        return true;
    }

    InputMap CInput::getInputType()
    {
        return currentGamepad;
    }

    void CInput::Update() {

    }

    void CInput::Shutdown() {
        g_scePad.Shutdown();
    }

    bool CInput::getControllerInput(GamepadControls btn) {
        bool l_btnInput = false;
        switch (currentGamepad) {
        case InputMap::INPUT_DS:
            l_btnInput = g_scePad.getInput(btn);
            break;
        case InputMap::INPUT_XBOX:
        case InputMap::INPUT_UNIQUE:
        default:
            break;
        }

        return l_btnInput;
    }

    JoystickInput CInput::getControllerJoystick(GamepadControls joy) {
        JoystickInput l_joyInput = { 0.0f, 0.0f };
        switch (currentGamepad) {
        case InputMap::INPUT_DS:
            l_joyInput = g_scePad.getJoystick(joy);
            break;
        case InputMap::INPUT_XBOX:
        case InputMap::INPUT_UNIQUE:
        default:
            break;
        }

        return l_joyInput;
    }

} // namespace rs
