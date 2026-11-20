#pragma once

#include <fstream>  // std::ifstream

#include "../include/geometry.hpp"
#include "../include/canvas.hpp"


// ####################
// we assume vertices for Polygons given in clockwise order e.g. for a square:
//  cords[0]         cords[1]
//          +-------+
//          |       |
//          |       |
//          +-------+
//  cords[3]         cords[2]
// ####################


void ingestInput(
            std::ifstream& file, 
            Canvas& _canvas, 
            std::vector<Shape>& shapes);








