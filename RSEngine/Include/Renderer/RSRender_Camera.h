/*

RSEngine
Copyright (c) 2020 Mason Lee Back

File name: RSRender_Camera.h

*/

#ifndef _RSRENDER_CAMERA_H_
#define _RSRENDER_CAMERA_H_

namespace rs::Renderer {
    class RSRender_Camera {
    public:
        Vector3 eyePos;
        Vector3 lookAtPos;
        Vector3 upVector;
        float fieldOfView;
    };

} // namespace rs::Renderer

#endif // _RSRENDER_CAMERA_H_
