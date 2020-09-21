/*

RSEngine
Copyright (c) 2020 Mason Lee Back

File name: LevelRoot.h

*/

#ifndef _LEVELROOT_H_
#define _LEVELROOT_H_

#include "Instance.h"

namespace rs {
    class Camera;

    // Core level instance - contains a lot, so make sure not to break
    // anything!
    class LevelRoot : public Instance {
    public:
        INITIALIZE_INSTANCE_HEADER(LevelRoot);

        std::string LevelName;

        void assignLocalCamera(std::shared_ptr<Camera> camera);
        std::shared_ptr<Camera> getLocalCamera();

    public:
        std::shared_ptr<Camera> localCamera;
    };

} // namespace rs

#endif // _LEVELROOT_H_
