/*

RSEngine
Copyright (c) 2019 Mason Lee Back

File name: RSD3D11_TypeConv.cpp

*/

#include <Render/D3D11/RSD3D11.h>

#ifdef _WIN32

namespace rs::Render {
    D3D11_PRIMITIVE_TOPOLOGY RSD3D11_TypeConv::getTopology(RSPrimitiveTopology topology) {
        switch (topology) {
        case RS_PRIMITIVE_TOPOLOGY_LINELIST:
            return D3D11_PRIMITIVE_TOPOLOGY_LINELIST;
        case RS_PRIMITIVE_TOPOLOGY_LINESTRIP:
            return D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP;
        case RS_PRIMITIVE_TOPOLOGY_POINTLIST:
            return D3D11_PRIMITIVE_TOPOLOGY_POINTLIST;
        case RS_PRIMITIVE_TOPOLOGY_TRIANGLELIST:
            return D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
        case RS_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP:
            return D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP;
        }   

        return D3D11_PRIMITIVE_TOPOLOGY_UNDEFINED;
    }


} // namespace rs::Render

#endif _WIN32
