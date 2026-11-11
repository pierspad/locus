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



void readPolygon(std::stringstream& ss, std::string& line, std::vector<Shape>& shapes){

    Coordinate cords;
    int i=0;
    char comma;

    while(ss >> cords.x >> comma >> cords.y){
        std::println("vertex {} - x: {:<4}\ty: {}", i, cords.x, cords.y);
        i++;
    }
}

void readRectangle(std::stringstream& ss, std::string& line, std::vector<Shape>& shapes){ 

    Coordinate _tmpCords;
    double width, height;
    char comma;
    ss >> width >> height >> _tmpCords.x >> comma >> _tmpCords.y;

    shapes.emplace_back(Rectangle{
        .coordinate = { _tmpCords.x, _tmpCords.y },    
        .width = width,
        .height = height
    });

    std::println("Width: {:<4} \t Height: {}", width, height);
    std::println("");

    std::visit(printShape, shapes.back());
}

void readSquare(std::stringstream& ss, std::string& line, std::vector<Shape>& shapes){
    
    Coordinate _tmpCords;
    double side;
    char comma;
    ss >> side >> _tmpCords.x >> comma >> _tmpCords.y;

    shapes.emplace_back(Rectangle{
        .coordinate = { _tmpCords.x, _tmpCords.y },    
        .width = side,
        .height = side
    });

    std::println("Side length: {}", side);
    std::println("");

    std::visit(printShape, shapes.back());
}



// TODO
void readEllipse(std::stringstream& ss, std::string& line, std::vector<Shape>& shapes){
    
    std::println("This is a circle ---- not implemented yet");
    std::println("");

    Coordinate cords;
    int radius;
    char comma;
    ss >> radius >> cords.x >> comma >> cords.y;

    std::println("radius: {}", radius);
    std::println("");

    cords.print();
}

// TODO
void readCircle(std::stringstream& ss, std::string& line, std::vector<Shape>& shapes){
    
    std::println("This is a circle ---- not implemented yet");
    std::println("");

    Coordinate cords;
    int radius;
    char comma;
    ss >> radius >> cords.x >> comma >> cords.y;

    std::println("radius: {}", radius);
    std::println("");

    cords.print();
}


void readShape( int i, std::string& shapeType, std::ifstream& file, 
                std::string& line, std::stringstream& ss, 
                std::vector<Shape>& shapes){

    std::println("##### {} SHAPE #####", i);

    std::getline(file, line);
    ss.clear();
    ss.str(line);
    std::println("{} - {}\n", shapeType, line);

    switch(hashString(shapeType)){
        case ShapeCode::polygon:
            readPolygon(ss, line, shapes);
            break;
        case ShapeCode::rectangle:
            readRectangle(ss, line, shapes);
            break;
        case ShapeCode::square:
            readSquare(ss, line, shapes);
            break;
        case ShapeCode::ellipse:
            readEllipse(ss, line, shapes);
            break;
        case ShapeCode::circle:
            readCircle(ss, line, shapes);
            break;
        default: 
            // error
            break;
    }

    std::println("##### END SHAPE #####");
    std::println("");
}


void ingestInput(std::string& fileName, std::vector<Shape>& shapes){
    std::ifstream file(fileName);
    std::string line;

    int i = 0;
    while(std::getline(file, line)){
        const auto pos = line.find_first_not_of(" \t\r\n");

        // Skip if comment line
        if (pos == std::string::npos ||
            line.compare(pos, 1, "#") == 0 ||
            line.compare(pos, 2, "//") == 0) {
            continue;
        }

        std::stringstream ss(line);

        std::string shapeType;
        if(!(ss >> shapeType)){
            continue;
        }
        i++;

        readShape(i, shapeType, file, line, ss, shapes);
        
    }
}








