/*

RSEngine
Copyright (c) 2020 Mason Lee Back

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
        RSRender_Camera localCam;

        localCam.eyePos = EyePos;
        localCam.lookAtPos = LookAtPos;
        localCam.upVector = UpVector;
        localCam.fieldOfView = FieldOfView;

        g_RSRender->UpdateCamera(localCam);

		ViewportSize = Vector2(renderResolution.X, renderResolution.Y);

		renderChildren();
	}
	
} // namespace rs
