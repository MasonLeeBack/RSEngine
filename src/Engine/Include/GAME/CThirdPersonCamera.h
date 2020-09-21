/*

RSEngine
Copyright (c) 2020 Mason Lee Back

File name: CThirdPersonCamera.h

*/

#ifndef _CTHIRDPERSONCAMERA_H_
#define _CTHIRDPERSONCAMERA_H_

#include <Classes/Instance.h>
#include <Classes/Camera.h>

// non-namespaced, game independent
class CThirdPersonCamera : public rs::Instance {
public:
	void assignRootCamera(rs::Camera* rootCamera);

	void tick() override;
private:
	rs::Camera* rootCamera;
};

#endif // _CTHIRDPERSONCAMERA_H_
