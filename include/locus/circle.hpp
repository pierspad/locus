#pragma once

#include <algorithm>
#include <cmath>
#include "structs.hpp"

struct Circle{
    Point center;
    int radius{0};
};

inline int radius(Circle& c){
    return c.radius;
}

inline int overlap_circle(Circle& c1, Circle& c2){
    int distance_x1x2 = pow((c1.center.x-c2.center.x),2);
    int distance_y1y2 = pow((c1.center.y-c2.center.y),2);
    int distance_ab = sqrt(distance_x1x2-distance_y1y2); 

    return distance_ab - c1.radius - c2.radius;
}