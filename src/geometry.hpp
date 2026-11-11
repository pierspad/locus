#pragma once

#include <print>
#include <vector>
#include <variant>
#include <numbers>
#include <string>

struct Coordinate{
    double x;
    double y;

    void print() const{
        std::println("x: {:<4}\ty: {}", x, y);
    }
};

//TODO
struct Polygon{
    Coordinate center;
    std::vector<Coordinate> cords; 
    
    double getPerimeter() const{
        // to implement
        return 0.0;
    };

    double getArea() const{
        // to implement
        return 0.0;
    }

    void print() const{
        for (int i = 0; i<cords.size(); i++){
            std::print("vertex {} - ",i);
            cords[i].print();
        }
    }
};

//TODO
struct Rectangle{
    Coordinate coordinate; 
    double width, height;
    
    double getPerimeter() const{
        return (width + height) * 2;
    };

    double getArea() const{
        return width * height;
    }

    void print() const{
        std::println("vertex {} - x: {:<4}\ty: {}", 0, coordinate.x,          coordinate.y        );
        std::println("vertex {} - x: {:<4}\ty: {}", 1, coordinate.x + width,  coordinate.y        );
        std::println("vertex {} - x: {:<4}\ty: {}", 2, coordinate.x + width,  coordinate.y + height );
        std::println("vertex {} - x: {:<4}\ty: {}", 3, coordinate.x,          coordinate.y + height );
    }
};

//TODO
struct Ellipse{
    Coordinate center;
    double radius;
    
    double getPerimeter() const{
        return std::numbers::pi * 2 * radius; 
    };

    double getArea() const{
        return std::numbers::pi * radius * radius;
    }

    void print() const{
        std::print("center: ");
        center.print();
        std::println("");
        std::print("radius: {} - ", radius);
        center.print();
    }
};

struct Circle{
    Coordinate center;
    double radius;
    
    double getPerimeter() const{
        return std::numbers::pi * 2 * radius; 
    };

    double getArea() const{
        return std::numbers::pi * radius * radius;
    }

    void print() const{
        std::print("center: ");
        center.print();
        std::println("");
        std::print("radius: {} - ", radius);
        center.print();
    }
};


using Shape = std::variant<Polygon, Rectangle, Ellipse, Circle>;


enum class ShapeCode{
    polygon,
    rectangle,
    square,
    ellipse,
    circle,
    unknown
};

ShapeCode hashString(const std::string& str){
    if(str == "polygon") return ShapeCode::polygon;
    if(str == "rectangle") return ShapeCode::rectangle;
    if(str == "square") return ShapeCode::square;
    if(str == "ellipse") return ShapeCode::ellipse;
    if(str == "circle") return ShapeCode::circle;
    return ShapeCode::unknown;
}