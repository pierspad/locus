#pragma once

#include <vector>
#include <print>
#include <algorithm>
#include <fstream>

#include "../include/geometry.hpp"
#include "../include/colors.hpp"


std::vector<Color> canvas;

void dye(Color& surface, const Color& pigment){
    surface.r = pigment.r;
    surface.g = pigment.g;
    surface.b = pigment.b;
}

void printColorOnFile(
    std::ofstream& out, 
    const Color& color) {
    out.put(char(color.r));
    out.put(char(color.g));
    out.put(char(color.b));
}

void obtainPointsBetweenAB(
            const double docWidth,
            const double docHeight,
            std::vector<Coordinate>& _linesBetweenVertices,
            std::vector<Color>& _canvas,
            Coordinate a,
            Coordinate b
) { // Bresenham method
    double x0 = a.x;
    double y0 = a.y;
    double x1 = b.x;
    double y1 = b.y;

    double dx = std::abs(x1 - x0);
    double dy = std::abs(y1 - y0);

    double sx = x0 < x1 ? 1 : -1;
    double sy = y0 < y1 ? 1 : -1;

    double error = dx - dy;

    while (true) {

        double index = (docWidth * y0) + x0;
        _linesBetweenVertices.emplace_back(Coordinate{
            .x = x0,
            .y = y0
        });
        if (x0 == x1 && y0 == y1)
            break;

        int e2 = 2 * error;

        if (e2 > -dy) {
            error -= dy;
            x0 += sx;
        }

        if (e2 < dx) {
            error += dx;
            y0 += sy;
        }
    }
}

void drawLineAB( 
            const double docWidth,
            const double docHeight,
            const Coordinate a,
            const Coordinate b,
            const Color& pigment,
            std::vector<Coordinate>& _linesBetweenVertices,
            std::vector<Color>& _canvas
) { 
    obtainPointsBetweenAB(docWidth, docHeight, _linesBetweenVertices, _canvas, a, b);

    for(Coordinate c : _linesBetweenVertices){
        double index = (docWidth * c.y) + c.x;
        dye(_canvas[index], pigment);
    }
}


void drawConvexPolygon(
                bool full,
                const double docWidth, 
                const double docHeight,
                const Color& pigment,
                std::vector<Color>& _canvas, 
                const ConvexPolygon& _convPol){

    
    const auto& coords = _convPol.coords;
    Coordinate _temp1, _temp2;
    int _curridx;
    bool foundFirstPoint = false, foundSecondPoint = false;
    std::vector<Coordinate> linesBetweenVertices;

    for(int i = 0; i<_convPol.coords.size() ; i++){
        Coordinate point1 = _convPol.coords[i];
        Coordinate point2 = _convPol.coords[(i+1) % _convPol.coords.size() ];
        drawLineAB(docWidth, docHeight, point1, point2, pigment, linesBetweenVertices, _canvas);
    }
    if(full){

        std::sort(linesBetweenVertices.begin(), linesBetweenVertices.end(), Coordinate::compare);

        for(Coordinate c : linesBetweenVertices){
            if(!foundFirstPoint){
                _temp1 = c;
                foundFirstPoint = true;
                continue;
            }
            if(!foundSecondPoint){
                _temp2 = c;
                foundSecondPoint = true;
                continue;
            }
            if(_temp2.x == c.x){
                _temp2 = c;
                continue;
            }
            if(_temp1.x == _temp2.x ){
                drawLineAB(docWidth, docHeight, _temp1, _temp2, pigment, linesBetweenVertices, _canvas);
                foundSecondPoint = false;
                _temp1 = c;
            }
            
        }
    }
}


void drawRectangle(
                bool full,
                const double docWidth, 
                const double docHeight,
                const Color& pigment,
                std::vector<Color>& _canvas, 
                const Rectangle& _rect){


    double TLx,TLy,recWidth,recHeight;
    TLx = _rect.coordinate.x;
    TLy = _rect.coordinate.y;
    recWidth = _rect.width;
    recHeight = _rect.height;
    

    for (double i = 0; i < recHeight; i++) {
        for (double j = 0; j < recWidth; j++) {

            double index = (docWidth * (TLy + i)) + TLx + j;

            if(!full && i!=0 && i != recHeight-1 && j!=0 && j!=recWidth-1){
                continue;
            }

            dye(_canvas[index], pigment);
        }
    }
}


//TODO
void drawOnCanvas(
                const double docWidth, 
                const double docHeight,
                bool full,
                std::vector<Color>& _canvas, 
                const std::vector<Shape>& _shapes){

    _canvas.assign(
        docWidth * docHeight,
        Color{255, 255, 255}
    );

    // fare un vector di colori e cercare di selezionare un colore diverso per ogni figura
    for (const Shape& shape : _shapes) {
        std::visit([&](const auto& concreteShape) {
            using T = std::decay_t<decltype(concreteShape)>;

            
            if constexpr (std::is_same_v<T, ConvexPolygon>) {
                drawConvexPolygon(full, docWidth, docHeight, black, _canvas, concreteShape);
            }
            
            if constexpr (std::is_same_v<T, Rectangle>) {
                drawRectangle(full, docWidth, docHeight, black, _canvas, concreteShape);
            }
            /*   
            if constexpr (std::is_same_v<T, Ellipse>) {
                drawRectangle(full, docWidth, docHeight, black, _canvas, concreteShape);
            }
            if constexpr (std::is_same_v<T, Circle>) {
                drawRectangle(full, docWidth, docHeight, black, _canvas, concreteShape);
            }
            */
        }, shape);
    }
}

void writePPMHeader(
                std::ofstream& out,
                const int screenWidth, 
                const int screenHeight){
    out << "P6\n";
    out << screenWidth << ' ' << screenHeight << '\n';
    out << "255\n";
}

void drawCanvasOnFile(
                std::ofstream& out, 
                const int docWidth, 
                const int docHeight,
                const int screenWidth, 
                const int screenHeight, 
                std::vector<Color>& _canvas){
    
    int _tempx, _tempy;
    Color _tempColor;

    for (int y = 0; y < screenHeight; y++) {
        for (int x = 0; x < screenWidth; x++) {
            _tempx = x * docWidth / screenWidth;
            _tempy = y * docHeight / screenHeight;
            
            _tempColor = _canvas[(_tempy * docWidth) + _tempx];
            printColorOnFile(out, _tempColor);
            
        }
    }

}

void visualizeShapes(
                std::ofstream& out,
                const double docWidth, 
                const double docHeight, 
                const double screenWidth, 
                const double screenHeight, 
                const bool fullShapes,
                const std::vector<Shape>& shapes){

    drawOnCanvas(docWidth, docHeight, fullShapes, canvas, shapes);

    writePPMHeader(out, screenWidth, screenHeight);

    drawCanvasOnFile(out, docWidth, docHeight, screenWidth, screenHeight,  canvas);
    
    return;
}