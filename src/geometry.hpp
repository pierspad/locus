#pragma once

#include <print>
#include <vector>
#include <variant>
#include <numbers>

struct Coordinate{
    double x;
    double y;

    void print() const{
        std::println("x: {}\ty: {}", x, y);
    }
};


struct Polygon{
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
            std::print("vertice {} - ",i);
            cords[i].print();
        }
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
        std::print("radius: {} - ",radius);
        center.print();
    }
};



using Shape = std::variant<Circle, Polygon>;