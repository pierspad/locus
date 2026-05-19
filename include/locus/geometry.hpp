#include <algorithm>


struct Point{
    int x;
    int y;
};

struct Size{
    int width;
    int height;
};

struct Rectangle{
    Point top_left;
    Size size;
};



int left(Rectangle rect){
    return rect.top_left.x;
}

int right(Rectangle rect){
    
    return rect.top_left.x + rect.size.width;
}

int top(Rectangle rect){
    return rect.top_left.y;
}

int bottom(Rectangle rect){    
    return rect.top_left.y + rect.size.height;
}


int overlap_width(Rectangle a, Rectangle b){
    return std::max(0, std::min(right(a), right(b)) - std::max(left(a), left(b)));
}

int overlap_height(Rectangle a, Rectangle b){
    return std::max(0, std::min(bottom(a), bottom(b)) - std::max(top(a), top(b)));
}