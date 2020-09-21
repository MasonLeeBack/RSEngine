/*

RSEngine
Copyright (c) 2020 Mason Lee Back

File name: UIScale.h

*/

#ifndef _UISCALE_H_
#define _UISCALE_H_

namespace rs {
    class UIScale {
    public:
        float Scale_X;
        float Offset_X;
        float Scale_Y;
        float Offset_Y;

        UIScale();
        UIScale(float xScale, float xOffset, float yScale, float yOffset);

        // todo: operators
    };

} // namespace rs

#endif // _UISCALE_H_
