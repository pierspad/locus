#pragma once

#include <fstream>
#include <sstream>
#include <print>

#include "./geometry.hpp"


// ####################
// we assume vertices for Polygons given in clockwise order e.g. for a square:
//  cords[0]         cords[1]
//          +-------+
//          |       |
//          |       |
//          +-------+
//  cords[3]         cords[2]
// ####################


auto printShape =   [](const auto& shape) {
                        shape.print();
                    };

void readSquare(std::stringstream& ss, std::string& line, std::vector<Shape>& shapes){
    
    std::println("This is a square");
    std::println("");

    Coordinate _tmpCords;
    int side;
    char comma;
    ss >> side >> _tmpCords.x >> comma >> _tmpCords.y;

    shapes.emplace_back(Polygon{
        .cords = {
            {_tmpCords.x,           _tmpCords.y        },
            {_tmpCords.x + side,    _tmpCords.y        },
            {_tmpCords.x + side,    _tmpCords.y + side },
            {_tmpCords.x,           _tmpCords.y + side }
        }
    });

    std::println("Side length: {}", side);
    std::println("");

    std::visit(printShape, shapes.back());
}

// TODO
void readRectangle(std::stringstream& ss, std::string& line, std::vector<Shape>& shapes){
    
    std::println("This is a rectangle");
    std::println("");


    Coordinate cords;
    int width, height;
    char comma;
    ss >> width >> height >> cords.x >> comma >> cords.y;

    std::println("{}", width);
    std::println("width");
    std::println("");

    std::println("{}", height);
    std::println("height");
    std::println("");

    cords.print();
}

// TODO
void readPolygon(std::stringstream& ss, std::string& line, std::vector<Shape>& shapes){
    
    std::println("This is an n-gon");
    std::println("");

    Coordinate cords;
    int i=0;
    char comma;

    while(ss >> cords.x >> comma >> cords.y){
        std::println("{}-vertex", i);
        cords.print();
        i++;
    }
}

// TODO
void readCircle(std::stringstream& ss, std::string& line, std::vector<Shape>& shapes){
    
    std::println("This is a circle ---- not implemented yet");
    std::println("");

    Coordinate cords;
    int radius;
    char comma;
    ss >> radius >> cords.x >> comma >> cords.y;

    std::println("{}", radius);
    std::println("radius");
    std::println("");

    cords.print();
}


// TODO
void ingestInput(std::string& fileName, std::vector<Shape>& shapes){
    std::ifstream file(fileName);
    std::string line;

    int i = 0;
    while(std::getline(file, line)){
        std::stringstream ss (line);

        int shapeType;
        if(!(ss >> shapeType)){
            continue;
        }
        i++;
        std::println("##### {} SHAPE #####", i);

        switch(shapeType){
            case 0: // circle
                readCircle(ss, line, shapes);
                break;
            case 1: // square
                readSquare(ss, line, shapes);
                break;
            case 2: // rectangle
                readRectangle(ss, line, shapes);
                break;
            default: // n-gon
                readPolygon(ss, line, shapes);
                break;
        }

        std::println("##### END SHAPE #####");
        std::println("");
    }
}








