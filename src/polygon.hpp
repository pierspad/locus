#pragma once

#include "shape.hpp"
#include "coordinate.hpp"

class Polygon : public Shape{
    public:

        std::vector<Coordinate> cords;

};

// coordinates are assumed to be sequential
// if the Polygon is a square
// an arc can be assumed among
// cords[0] -> cords[1]
// cords[1] -> cords[2]
// cords[2] -> cords[3]
// cords[3] -> cords[0]