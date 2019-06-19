/*

RSEngine
Copyright (c) 2019 Mason Lee Back

File name: RSD3D11_TypeConv.h

*/

#ifndef _RSD3D11_TypeConv_h_
#define _RSD3D11_TypeConv_h_

namespace rs::Render {
    class RSD3D11_TypeConv {
    public:
        D3D11_PRIMITIVE_TOPOLOGY getTopology(RSPrimitiveTopology topology);

    };

} // namespace rs::Render

#endif // _RSD3D11_TypeConv_h_
