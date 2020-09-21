/*

RSEngine
Copyright (c) 2020 Mason Lee Back

File name: Vector2.cpp

*/

#include <Types/Vector2.h>

namespace rs {

    Vector2::Vector2() {
        X = 0.0f;
        Y = 0.0f;
    }
    
    Vector2::Vector2(float x, float y) {
        X = x;
        Y = y;
    }

    bool Vector2::operator==(const Vector2& rhs)
    {
        if (X == rhs.X && Y == rhs.Y)
            return true;

        return false;
    }
    
} // namespace rs
