
#include <numbers>
#include <string>
#include <vector>
#include <variant>
#include <print>
#include <ranges>
#include <cmath>


#include "../include/geometry.hpp"

// --- Coordinate ---

bool Coordinate::isEmpty() const {
    return x == -1.0 && y == -1.0;
}

void Coordinate::clear() {
    x = -1.0;
    y = -1.0;
}

void Coordinate::print() const {
    std::println("x: {:<4}\ty: {}", x, y);
}

// --- Other ---
[[nodiscard]]
double distanceBetweenTwoPoints( const Coordinate& c1, 
                                        const Coordinate& c2){
    return std::hypot(c2.x - c1.x, c2.y - c1.y);
}


// --- ConvexPolygon ---

double ConvexPolygon::getPerimeter() const{
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
}

double ConvexPolygon::getArea() const{
    double area = 0.0;
    for(std::size_t i = 0; i<coords.size(); i++){
        const auto j = (i + 1) % coords.size();

        area += coords[i].x * coords[j].y -
                coords[j].x * coords[i].y;
    }
    return abs(area)/2;
}

void ConvexPolygon::print() const{
    for (int i = 0; i<coords.size(); i++){
        std::print("vertex {} - ",i);
        coords[i].print();
    }
}


// --- Rectangle ---

double Rectangle::getPerimeter() const{
    return (width + height) * 2;
}

double Rectangle::getArea() const{
    return width * height;
}

Coordinate Rectangle::getCentroid() const{
    return {
        .x = coordinate.x + width/2,
        .y = coordinate.y + height/2,
    };
}

void Rectangle::print() const{
    std::println("vertex {} - x: {:<4}\ty: {}", 0, coordinate.x,          coordinate.y        );
    std::println("vertex {} - x: {:<4}\ty: {}", 1, coordinate.x + width,  coordinate.y        );
    std::println("vertex {} - x: {:<4}\ty: {}", 2, coordinate.x + width,  coordinate.y + height );
    std::println("vertex {} - x: {:<4}\ty: {}", 3, coordinate.x,          coordinate.y + height );
}


// --- Ellipse ---

double Ellipse::getPerimeter() const {
    const double a = radiusX;
    const double b = radiusY;

    return std::numbers::pi *
        (3 * (a + b) -
        std::sqrt((3*a + b) * (a + 3*b)));
}

double Ellipse::getArea() const {
    return std::numbers::pi * radiusX * radiusY;
}

void Ellipse::print() const {
    std::print("center: ");
    center.print();

    std::println("radiusX: {}", radiusX);
    std::println("radiusY: {}", radiusY);
}

// TODO
Coordinate Ellipse::getCentroid() const{

}


// --- Circle ---

double Circle::getPerimeter() const{
    return std::numbers::pi * 2 * radius; 
};

double Circle::getArea() const{
    return std::numbers::pi * radius * radius;
}

void Circle::print() const{
    std::print("center: ");
    center.print();
    std::println("");
    std::print("radius: {} - ", radius);
    center.print();
}

// TODO
Coordinate Circle::getCentroid() const{
    
}
