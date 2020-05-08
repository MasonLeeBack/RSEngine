/*

RSEngine
Copyright (c) 2020 Mason Lee Back

File name: LevelRoot.h

*/

#ifndef _LEVELROOT_H_
#define _LEVELROOT_H_

#include "Instance.h"

namespace rs {
    class LevelRoot : public Instance {
    public:
        INITIALIZE_INSTANCE_HEADER(LevelRoot);

        std::string LevelName;
    };

} // namespace rs

#endif // _LEVELROOT_H_
