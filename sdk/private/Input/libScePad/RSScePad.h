/*

RSEngine
Copyright (c) 2019 Mason Lee Back



File name: RSScePad.h

*/

#ifndef _RSScePad_h_
#define _RSScePad_h_

namespace rs {
    namespace Input {
        class RSScePad {
        public:
            bool Initialize();
            void Shutdown();

            void setDeadzone(float deadzone);

            bool getControllerConnection();

            bool getInput(GamepadControls button);
            JoystickInput getJoystick(GamepadControls joy);
        private:
            float inDeadzoneRange(float val);

            int padHandle;
            bool padOpen;

            float Deadzone = 3.0f;
        };

    } // namespace Input

} // namespace rs

#endif // _RSScePad_h_
