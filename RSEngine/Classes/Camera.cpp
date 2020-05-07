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

File name: Camera.cpp

*/

#include <Classes/Camera.h>
#include <Renderer/RSRender.h>

using namespace DirectX;
using namespace rs::Renderer;

namespace rs {
    INITIALIZE_INSTANCE_SOURCE(Camera);

    XMVECTOR Vector3ToXmVector(Vector3 vec) {
        return XMVectorSet(vec.X, vec.Y, vec.Z, 0);
    }

	void Camera::render() {

        if (UpVector.Y == 0) {
            UpVector.Y = 1;
        }

        static XMVECTOR eyePos = XMVectorSet(0.0f, 0.0f, -2.0f, 0.0f);
        XMFLOAT3 eyePosFloat3 = XMFLOAT3(EyePos.X, EyePos.Y, EyePos.Z);
        XMStoreFloat3(&eyePosFloat3, eyePos);
        eyePosFloat3.y = EyePos.Y + .05;
        eyePosFloat3.x = EyePos.X + .05;
        eyePosFloat3.z = EyePos.Z;
        eyePos = XMLoadFloat3(&eyePosFloat3);
        XMVECTOR lookAtPos = Vector3ToXmVector(LookAtPos);
        XMVECTOR upVector = Vector3ToXmVector(UpVector);

        g_cameraMatrix.mView = XMMatrixLookAtLH(eyePos, lookAtPos, upVector);
        g_cameraMatrix.mProjection = XMMatrixPerspectiveFovLH(XMConvertToRadians(FieldOfView), (renderResolution.X / renderResolution.Y), 0.1f, 1000.0f);

		ViewportSize = Vector2(renderResolution.X, renderResolution.Y);

		renderChildren();
	}
	
} // namespace rs
