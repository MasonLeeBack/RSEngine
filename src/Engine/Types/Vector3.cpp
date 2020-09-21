/*

RSEngine
Copyright (c) 2020 Mason Lee Back

File name: Vector3.cpp

*/

#include <Types/Vector3.h>

namespace rs {
    Vector3::Vector3() {
        X = 0.0f;
        Y = 0.0f;
        Z = 0.0f;
    }
    
    Vector3::Vector3(float x, float y, float z) {
        X = x;
        Y = y;
        Z = z;
    }

    Vector3& Vector3::operator+=(const Vector3& rhs) {
        this->X += rhs.X;
        this->Y += rhs.Y;
        this->Z += rhs.Z;

        return *this;
    }

    bool Vector3::operator!=(const Vector3& rhs)
    {
        if (rhs.X != this->X || rhs.Y != this->Y || rhs.Z != this->Z) {
            return true;
        }
        return false;
    }

} // namespace rs
