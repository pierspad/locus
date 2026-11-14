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


void cleanLineFromComments(std::string& line){
        if(auto pos = line.find("#"); pos != std::string::npos){
            line.erase(pos);
        }
        
        if(auto pos = line.find("//"); pos != std::string::npos){
            line.erase(pos);
        }
}
                    
void readPolygon(std::stringstream& ss, std::string& line, std::vector<Shape>& shapes){

    Coordinate _tmpCords;
    int i=0;
    char comma;

    while(ss >> _tmpCords.x >> comma >> _tmpCords.y){
        std::println("vertex {} - x: {:<4}\ty: {}", i, _tmpCords.x, _tmpCords.y);
        i++;
    }
}

void readRectangle(std::stringstream& ss, std::string& line, std::vector<Shape>& shapes){ 

    Coordinate _tmpCords;
    double _width, _height;
    char comma;
    ss >> _width >> _height >> _tmpCords.x >> comma >> _tmpCords.y;

    shapes.emplace_back(Rectangle{
        .coordinate = { _tmpCords.x, _tmpCords.y },    
        .width = _width,
        .height = _height
    });

    std::println("Width: {:<4} \t Height: {}", _width, _height);
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

void readEllipse(std::stringstream& ss, std::string& line, std::vector<Shape>& shapes){
    
    Coordinate _tmpCords;
    double _radiusX, _radiusY;
    char comma;
    ss >> _radiusX >> _radiusY >> _tmpCords.x >> comma >> _tmpCords.y;

    shapes.emplace_back(Ellipse{
        .center = { _tmpCords.x, _tmpCords.y },    
        .radiusX = _radiusX,
        .radiusY = _radiusY
    });

    std::print("center - ");
        _tmpCords.print();
    std::println("radiusX: {}", _radiusX);
    std::println("radiusY: {}", _radiusY);
}

void readCircle(std::stringstream& ss, std::string& line, std::vector<Shape>& shapes){
    
    Coordinate _tmpCords;
    int radius;
    char comma;
    ss >> radius >> _tmpCords.x >> comma >> _tmpCords.y;

    std::println("radius: {}", radius);
    _tmpCords.print();
}


void readShape( int i, std::string& shapeType, std::ifstream& file, 
                std::string& line, std::stringstream& ss, 
                std::vector<Shape>& shapes){

    std::println("##### {} SHAPE #####", i);

    std::getline(file, line);
    ss.clear();
    ss.str(line);
    
    cleanLineFromComments(line);
    std::println("{} - {}\n", shapeType, line);

    switch(hashString(shapeType)){
        case ShapeCode::ConvexPolygon:
            readPolygon(ss, line, shapes);
            break;
        case ShapeCode::Rectangle:
            readRectangle(ss, line, shapes);
            break;
        case ShapeCode::Square:
            readSquare(ss, line, shapes);
            break;
        case ShapeCode::Ellipse:
            readEllipse(ss, line, shapes);
            break;
        case ShapeCode::Circle:
            readCircle(ss, line, shapes);
            break;
        default: 
            std::println("Shape does not exist: {}", shapeType);
            break;
    }

    std::println("##### END SHAPE #####");
    std::println("");
}


void ingestInput(std::string& fileName, int& docWidth, int& docHeight, std::vector<Shape>& shapes){
    std::ifstream file(fileName);
    std::string line;

    int i = 0;
    bool canvaSizeRead = false; 
    while(std::getline(file, line)){

        // skip empty lines
        if (line.find_first_not_of(" \t\r\n") == std::string::npos) {
            continue;
        }

        cleanLineFromComments(line);

        std::stringstream ss(line);

        if(!canvaSizeRead){
            ss >> docWidth >> docHeight;
            canvaSizeRead = true;
            std::println("Document - Width: {:<4}\tHeight: {:<4}",docWidth, docHeight);
            std::println("");
            continue;
        }

        std::string shapeType;
        if(!(ss >> shapeType)){
            continue;
        }
        i++;

        readShape(i, shapeType, file, line, ss, shapes);
        
    }
}








