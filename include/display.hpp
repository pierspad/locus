#pragma once

#include <vector>   // std::vector
#include <fstream>  // std::ofstream

#include "../include/geometry.hpp"
#include "../include/canvas.hpp"


void visualizeShapes(
                std::ofstream& out,
                Canvas& _canvas, 
                const double screenWidth, 
                const double screenHeight, 
                const bool fullShapes,
                std::vector<Color>& _colorsUsed,
                const std::vector<Shape>& shapes);
