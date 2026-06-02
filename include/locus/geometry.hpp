#pragma once

#include <algorithm>


namespace locus {

struct Point{
    int x{0};
    int y{0};
};

struct Size{
    int width{0};
    int height{0};
};

struct Rect{
    Point top_left;
    Size size;
};

inline int left(Rect const& rect){
    return rect.top_left.x;
}

inline int right(Rect const& rect){
    return rect.top_left.x + rect.size.width;
}

inline int top(Rect const& rect){
    return rect.top_left.y;
}

inline int bottom(Rect const& rect){    
    return rect.top_left.y + rect.size.height;
}

inline int area(Rect const& a){
    return a.size.width * a.size.height;
}


inline int overlap_width(Rect const& a, Rect const& b){
    return std::max(0, std::min(right(a), right(b)) - std::max(left(a), left(b)));
}

inline int overlap_height(Rect const& a, Rect const& b){
    return std::max(0, std::min(bottom(a), bottom(b)) - std::max(top(a), top(b)));
}

inline int overlap_area(Rect const& a, Rect const& b){
    return overlap_width(a,b) * overlap_height(a,b);
}

} 