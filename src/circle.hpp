#pragma once

#include "shape.hpp"
#include "coordinate.hpp"

class Circle : public Shape{
    public:

        Coordinate center;
        double radius;

};