/*

RSEngine
Copyright (c) 2020 Mason Lee Back

File name: RareInput.cpp

Notes: Right now, we only explicitly support ScePad until further notice.
    We'll have to add a virtual analog type for mobile platforms (iOS/Android)
    as well as native touch buttons.

*/

#include <Input/RareInput.h>

// Rewrite XInput library
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
