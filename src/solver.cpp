


#include <vector>           // std::vector
#include <unordered_set>    // std::unordered_set

#include "../include/geometry.hpp"

// TODO
namespace{
    // CBB stands for Circle Bounding Boxes
    // Exact stands for Exact Bounding Boxes

    bool areOverlappingCBB(const Shape& s1, const Shape& s2){
        return false;
    }    
    
    bool areOverlappingEBB(const Shape& s1, const Shape& s2){
        return false;
    }

    bool fixedByCBB(std::vector<Shape>& _shapes, std::unordered_set<size_t>& _toFix){
        return false;
    }

    bool fixedByEBB(std::vector<Shape>& _shapes, std::unordered_set<size_t>& _toFix){
        return false;
    }


}


void unoverlapShapesCBB(std::vector<Shape>& _shapes){
    std::unordered_set<size_t> toFix;

    int i = 0;

    do{
        toFix.clear();
        for(size_t i = 0; i < _shapes.size()-1; i++){
            for(size_t j = i+1; j < _shapes.size(); j++){
                if(areOverlappingCBB(_shapes[i], _shapes[j])){
                    toFix.insert(i);
                    toFix.insert(j);
                }
            }    
        }
        fixedByCBB(_shapes, toFix);
        i++;
    }
    while(!toFix.empty() || i>10); // avoid impossible configuration stopping after 10 trials

}


void unoverlapShapesEBB(std::vector<Shape>& _shapes){
    std::unordered_set<size_t> toFix;

    int i = 0;

    do{
        toFix.clear();
        for(size_t i = 0; i < _shapes.size()-1; i++){
            for(size_t j = i+1; j < _shapes.size(); j++){
                if(areOverlappingEBB(_shapes[i], _shapes[j])){
                    toFix.insert(i);
                    toFix.insert(j);
                }
            }    
        }
        fixedByEBB(_shapes, toFix);
        i++;
    }
    while(!toFix.empty() || i>10); // avoid impossible configuration stopping after 10 trials

}