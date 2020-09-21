/*

RSEngine
Copyright (c) 2020 Mason Lee Back

File name: UIScale.cpp

*/

#include <Types/UIScale.h>

namespace rs {
    UIScale::UIScale()
    {
        Scale_X = 0;
        Scale_Y = 0;
        Offset_X = 0;
        Offset_Y = 0;
    }

    UIScale::UIScale(float xScale, float xOffset, float yScale, float yOffset)
    {
        Scale_X = xScale;
        Scale_Y = yScale;
        Offset_X = xOffset;
        Offset_Y = yOffset;
    }

} // namespace rs
