/*

RSEngine
Copyright (c) 2020 Mason Lee Back

File name: RSScePad.cpp

*/

#include <Input/libScePad/RSScePad.h>

#if USE_LIBSCEPAD == 1
#include <pad.h>
#endif // USE_LIBSCEPAD == 1

namespace rs {
    namespace Input {

#if USE_LIBSCEPAD == 1

        bool RSScePad::Initialize() {
            if (scePadInit() == SCE_OK) {
                scePadSetParticularMode(true); // Enable use of SHARE and PS buttons
                int lPadHandle = scePadOpen(SCE_USER_SERVICE_STATIC_USER_ID_1, SCE_PAD_PORT_TYPE_STANDARD, 0, NULL);
                if (lPadHandle >= 0) {
                    padHandle = lPadHandle;
                    return true;
                }
                else {
                    return false;
                }
            }
            else {
                return false;
            }
        }

        void RSScePad::Shutdown() {
            scePadClose(padHandle);
        }

        void RSScePad::setDeadzone(float deadzone) {
            Deadzone = deadzone;
        }

        bool RSScePad::getControllerConnection() {
            ScePadData pData;
            if (scePadReadState(padHandle, &pData) == SCE_OK) {
                return pData.connected;
            }
            return false;
        }

        bool RSScePad::getInput(GamepadControls btn) {
            bool input = false;

            if (getControllerConnection()) {
                ScePadData pData;
                if (scePadReadState(padHandle, &pData) == SCE_OK) {
                    switch (btn) {
                    case GamepadControls::GPD_BTN_ACTION1:
                        input = pData.buttons & SCE_PAD_BUTTON_CROSS;
                        break;
                    case GamepadControls::GPD_BTN_ACTION2:
                        input = pData.buttons & SCE_PAD_BUTTON_CIRCLE;
                        break;
                    case GamepadControls::GPD_BTN_ACTION3:
                        input = pData.buttons & SCE_PAD_BUTTON_SQUARE;
                        break;
                    case GamepadControls::GPD_BTN_ACTION4:
                        input = pData.buttons & SCE_PAD_BUTTON_TRIANGLE;
                        break;
                    case GamepadControls::GPD_BTN_BUMPER1:
                        input = pData.buttons & SCE_PAD_BUTTON_L1;
                        break;
                    case GamepadControls::GPD_BTN_BUMPER2:
                        input = pData.buttons & SCE_PAD_BUTTON_R1;
                        break;
                    case GamepadControls::GPD_BTN_DPADUP:
                        input = pData.buttons & SCE_PAD_BUTTON_UP;
                        break;
                    case GamepadControls::GPD_BTN_DPADDOWN:
                        input = pData.buttons & SCE_PAD_BUTTON_DOWN;
                        break;
                    case GamepadControls::GPD_BTN_DPADLEFT:
                        input = pData.buttons & SCE_PAD_BUTTON_LEFT;
                        break;
                    case GamepadControls::GPD_BTN_DPADRIGHT:
                        input = pData.buttons & SCE_PAD_BUTTON_RIGHT;
                        break;
                    case GamepadControls::GPD_BTN_SELECT:
                        input = pData.buttons & SCE_PAD_BUTTON_SHARE;
                        break;
                    case GamepadControls::GPD_BTN_START:
                        input = pData.buttons & SCE_PAD_BUTTON_OPTIONS;
                        break;
                    case GamepadControls::GPD_BTN_TRIGGER1:
                        input = pData.buttons & SCE_PAD_BUTTON_L2;
                        break;
                    case GamepadControls::GPD_BTN_TRIGGER2:
                        input = pData.buttons & SCE_PAD_BUTTON_R2;
                        break;
                    case GamepadControls::GPD_BTN_JSTICK1:
                        input = pData.buttons & SCE_PAD_BUTTON_L3;
                        break;
                    case GamepadControls::GPD_BTN_JSTICK2:
                        input = pData.buttons & SCE_PAD_BUTTON_R3;
                        break;
                    default:
                        break;
                    }
                }
            }

            return input;
        }

        JoystickInput RSScePad::getJoystick(GamepadControls joy) {
            JoystickInput input = { 0.0f, 0.0f };
            
            if (getControllerConnection()) {
                ScePadData pData;
                if (scePadReadState(padHandle, &pData) == SCE_OK) {
                    switch (joy) {
                    case GamepadControls::GPD_JOY_JSTICK1:
                        input = { inDeadzoneRange(static_cast<float>(pData.leftStick.x) - 128.0f), inDeadzoneRange(static_cast<float>(pData.leftStick.y) - 128.0f) };
                        break;
                    case GamepadControls::GPD_JOY_JSTICK2:
                        input = { inDeadzoneRange(static_cast<float>(pData.rightStick.x) - 128.0f), inDeadzoneRange(static_cast<float>(pData.rightStick.y) - 128.0f) };
                        break;
                    default:
                        break;
                    }
                }
            }

            return input;
        }

        float RSScePad::inDeadzoneRange(float val) {
            if (val > Deadzone) {
                return val;
            }
            if (Deadzone*-1 > val) {
                return val;
            }

            return 0.0f;
        }

#else

        bool RSScePad::Initialize() {
            return true;
        }

        void RSScePad::Shutdown() {
            
        }

        void RSScePad::setDeadzone(float deadzone) {

        }

        bool RSScePad::getControllerConnection() {
            return false;
        }

        bool RSScePad::getInput(GamepadControls btn) {
            return false;
        }

        JoystickInput RSScePad::getJoystick(GamepadControls joy) {
            return { 0.0f, 0.0f };
        }

#endif // USE_LIBSCEPAD == 1

    } // namespace Input

} // namespace rs
