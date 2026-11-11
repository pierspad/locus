#pragma once

#include <print>
#include <vector>
#include <variant>
#include <numbers>
#include <string>
#include <cmath>

struct Coordinate{
    double x;
    double y;

    void print() const{
        std::println("x: {:<4}\ty: {}", x, y);
    }
};

[[nodiscard]]
inline double distanceBetweenTwoPoints( const Coordinate& c1, 
                                        const Coordinate& c2){
    return std::hypot(c2.x - c1.x, c2.y - c1.y);
}

struct ConvexPolygon{
    std::vector<Coordinate> coords; 
    
    [[nodiscard]]
    double getPerimeter() const{
        double perim = 0.0;
        if(coords.size()<2){
            std::println("ERROR - NOT ENOUGH VERTICES");
        }
        
        for(std::size_t i = 0; i<coords.size(); i++){
            perim += distanceBetweenTwoPoints(
                        coords[i], 
                        coords[(i + 1) % coords.size()]
                    );
        }
        return perim;
    };

    [[nodiscard]]
    double getArea() const{
        double area = 0.0;
        for(std::size_t i = 0; i<coords.size(); i++){
            const auto j = (i + 1) % coords.size();

            area += coords[i].x * coords[j].y -
                    coords[j].x * coords[i].y;
        }
        return abs(area)/2;
    }

    void print() const{
        for (int i = 0; i<coords.size(); i++){
            std::print("vertex {} - ",i);
            coords[i].print();
        }
    }
};

struct Rectangle{
    Coordinate coordinate; 
    double width, height;
    
    [[nodiscard]]
    double getPerimeter() const{
        return (width + height) * 2;
    };

    [[nodiscard]]
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
    
    [[nodiscard]]
    double getPerimeter() const{
        return std::numbers::pi * 2 * radius; 
    };

    [[nodiscard]]
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

    [[nodiscard]]
    double getPerimeter() const{
        return std::numbers::pi * 2 * radius; 
    };
    
    [[nodiscard]]
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


using Shape = std::variant<ConvexPolygon, Rectangle, Ellipse, Circle>;


enum class ShapeCode{
    ConvexPolygon,
    Rectangle,
    Square,
    Ellipse,
    Circle,
    Unknown
};

inline ShapeCode hashString(const std::string& str){
    if(str == "ConvexPolygon") return ShapeCode::ConvexPolygon;
    if(str == "Rectangle") return ShapeCode::Rectangle;
    if(str == "Square") return ShapeCode::Square;
    if(str == "Ellipse") return ShapeCode::Ellipse;
    if(str == "Circle") return ShapeCode::Circle;
    return ShapeCode::Unknown;
}