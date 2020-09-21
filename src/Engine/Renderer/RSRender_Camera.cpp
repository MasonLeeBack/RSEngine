/*

RSEngine
Copyright (c) 2020 Mason Lee Back

File name: RSRender_Camera.cpp

*/

#include <Renderer/RSRender.h>
using namespace DirectX;

namespace rs::Renderer {
    XMVECTOR Vector3ToXmVector(Vector3 vec) {
        return XMVectorSet(vec.X, vec.Y, vec.Z, 0);
    }

    void RenderClass::UpdateCamera(RSRender_Camera camera) {
        RSRender_Camera tCamera = camera;

        if (tCamera.upVector.Y == 0) {
            tCamera.upVector.Y = 1;
        }

        static XMVECTOR eyePos = XMVectorSet(0.0f, 0.0f, -2.0f, 0.0f);
        XMFLOAT3 eyePosFloat3 = XMFLOAT3(tCamera.eyePos.X +.055f, tCamera.eyePos.Y +.05f, tCamera.eyePos.Z);
        eyePos = XMLoadFloat3(&eyePosFloat3);
        XMVECTOR lookAtPos = Vector3ToXmVector(tCamera.lookAtPos);
        XMVECTOR upVector = Vector3ToXmVector(tCamera.upVector);

        cb_Camera.view = XMMatrixLookAtLH(eyePos, lookAtPos, upVector);
        cb_Camera.projection = XMMatrixPerspectiveFovLH(XMConvertToRadians(tCamera.fieldOfView), (renderResolution.X / renderResolution.Y), 0.1f, 1000.0f);

        cb_Camera.view = DirectX::XMMatrixTranspose(cb_Camera.view);
        cb_Camera.projection = DirectX::XMMatrixTranspose(cb_Camera.projection);

        // to do: use cameraConstBuf->Update later
        g_RSRender->l_DeviceContext->UpdateSubresource(cameraConstBuf->mpGPUData, 0, NULL, &cb_Camera, 0, 0);
        
        g_RSRender->l_DeviceContext->VSSetConstantBuffers(0, 1, &cameraConstBuf->mpGPUData);
    }

} // namespace rs::Renderer
