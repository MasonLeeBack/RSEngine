/*

RSEngine
Copyright (c) 2020 Mason Lee Back

File name: LoadModel_OBJ.h

*/

#pragma once
#ifndef _LoadModel_OBJ_h_
#define _LoadModel_OBJ_h_

#include <Types/MeshData.h>

namespace rs {
    class ObjLoader {
    public:
        bool LoadModel(MeshData* mesh, const char* filename);
    };

} // namespace rs

#endif // _LoadModel_OBJ_h_
