/*

ArkEngine
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

File name: BasePart.h

*/

#ifndef _BasePart_h_
#define _BasePart_h_

#include "Instance.h"

namespace rs {
    class BasePart : public Instance {
    public:
        INITIALIZE_INSTANCE_HEADER(BasePart);

        Vector3 Position = { 0.0f, 0.0f, 0.0f };
        Vector3 Size = { 0.0f, 0.0f, 0.0f };
        Vector3 Rotation = { 0.0f, 0.0f, 0.0f };

        bool PhysicsEnabled;
        Vector3 Velocity = { 0.0f, 0.0f, 0.0f };
        int physicsID = 0;

        float Opacity = 0.0f;

        virtual void tick() override;

        // Recommend using these in order to update the physics system
        // at the same time.
        virtual void setPhysicsEnabled(bool);

        virtual void setSize(Vector3);
        virtual void setPosition(Vector3);
        virtual void setRotation(Vector3);
        virtual void setVelocity(Vector3);
    };

} // namespace rs

#endif // _BasePart_h_
