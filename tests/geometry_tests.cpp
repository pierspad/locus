#include <cassert>
#include <locus/geometry.hpp>



bool test_adjacent_borders(){
    locus::Rect a,b;
    a.top_left.x =  0;
    a.top_left.y =  0;

    b.top_left.x = 10;
    b.top_left.y = 10;

    return overlap_area(a,b) <=0
}

int main(){
    return 0;
}