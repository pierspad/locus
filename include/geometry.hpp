#pragma once

#include <compare>
#include <string>
#include <vector>
#include <variant>

struct Coordinate{
    double x;
    double y;

    [[nodiscard]] bool isEmpty() const;
    [[nodiscard]] auto operator<=>(const Coordinate&) const = default;

    void clear();
    void print() const;
};


[[nodiscard]]
double distanceBetweenTwoPoints( 
                            const Coordinate& c1, 
                            const Coordinate& c2);


struct ConvexPolygon{
    std::vector<Coordinate> coords; 
    
    [[nodiscard]] double getPerimeter() const;
    [[nodiscard]] double getArea() const;
    [[nodiscard]] Coordinate getCentroid() const;

    void print() const;
};

struct Rectangle{
    Coordinate coordinate; 
    double width, height;
    
    [[nodiscard]] double getPerimeter() const;
    [[nodiscard]] double getArea() const;
    [[nodiscard]] Coordinate getCentroid() const;

    void print() const;
};

struct Ellipse{
    Coordinate center;
    double radiusX, radiusY;
    
    [[nodiscard]] double getPerimeter() const;
    [[nodiscard]] double getArea() const;
    [[nodiscard]] Coordinate getCentroid() const;

    void print() const;
};

struct Circle{
    Coordinate center;
    double radius;

    [[nodiscard]] double getPerimeter() const;
    [[nodiscard]] double getArea() const;
    [[nodiscard]] Coordinate getCentroid() const;

    void print() const;
};


using Shape = std::variant< 
                            ConvexPolygon, 
                            Rectangle, 
                            Ellipse, 
                            Circle
                        >;


enum class ShapeCode{
    ConvexPolygon,
    Rectangle,
    Square,
    Ellipse,
    Circle,
    Unknown
};


[[nodiscard]]
constexpr ShapeCode hashString(const std::string& str){
    if(str == "ConvexPolygon") return ShapeCode::ConvexPolygon;
    if(str == "Rectangle") return ShapeCode::Rectangle;
    if(str == "Square") return ShapeCode::Square;
    if(str == "Ellipse") return ShapeCode::Ellipse;
    if(str == "Circle") return ShapeCode::Circle;
    return ShapeCode::Unknown;
}