#pragma once

#include <vector>

#include "coordinate.hpp"

class Shape{
    public:
        
        virtual double getPerimeter() const = 0;
        virtual double getArea() const = 0;

};