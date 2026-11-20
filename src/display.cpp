
#include <algorithm>    // std::sort
#include <variant>      // std::visit
#include <cmath>        // std::abs
#include <variant>      // std::decay_t, std::is_same_v

#include <print>

#include "../include/display.hpp"
#include "../include/colors.hpp"


namespace {
    void dye(
                Color& surface, 
                const Color& pigment){
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
                double _canvasWidth,
                std::vector<Coordinate>& _linesBetweenVertices,
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

            double index = (_canvasWidth* y0) + x0;
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
                Canvas& _canvas, 
                const Coordinate a,
                const Coordinate b,
                const Color& pigment,
                std::vector<Coordinate>& _linesBetweenVertices
    ) { 
        obtainPointsBetweenAB(_canvas.docWidth, _linesBetweenVertices, a, b);

        for(Coordinate c : _linesBetweenVertices){
            double index = (_canvas.docWidth * c.y) + c.x;
            dye(_canvas.pixels[index], pigment);
        }
    }


    void drawConvexPolygon(
                    bool full,
                    Canvas& _canvas, 
                    const Color& pigment,
                    const ConvexPolygon& _convPol){

        
        const auto& coords = _convPol.coords;
        Coordinate _temp1, _temp2;
        int _curridx;
        bool foundFirstPoint = false, foundSecondPoint = false;
        std::vector<Coordinate> linesBetweenVertices;

        for(int i = 0; i<_convPol.coords.size() ; i++){
            Coordinate point1 = _convPol.coords[i];
            Coordinate point2 = _convPol.coords[(i+1) % _convPol.coords.size() ];
            drawLineAB(_canvas, point1, point2, pigment, linesBetweenVertices);
        }
        if(full){

            std::ranges::sort(linesBetweenVertices);

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
                    drawLineAB(_canvas, _temp1, _temp2, pigment, linesBetweenVertices);
                    foundSecondPoint = false;
                    _temp1 = c;
                }
                
            }
        }
    }


    void drawRectangle(
                    bool full,
                    Canvas& _canvas, 
                    const Color& pigment,
                    const Rectangle& _rect){


        double TLx,TLy,recWidth,recHeight;
        TLx = _rect.coordinate.x;
        TLy = _rect.coordinate.y;
        recWidth = _rect.width;
        recHeight = _rect.height;
        

        for (double i = 0; i < recHeight; i++) {
            for (double j = 0; j < recWidth; j++) {

                double index = (_canvas.docWidth * (TLy + i)) + TLx + j;

                if(!full && i!=0 && i != recHeight-1 && j!=0 && j!=recWidth-1){
                    continue;
                }

                dye(_canvas.pixels[index], pigment);
            }
        }
    }


    //TODO
    void drawOnCanvas(
                    bool full,
                    Canvas& _canvas, 
                    std::vector<Color>& _colorsUsed,
                    const std::vector<Shape>& _shapes){

        bool generateNewColors = false;
        if(_colorsUsed.empty()){
            generateNewColors = true;
            std::println("isEmpty");
        }


        for(size_t i = 0 ; i<_shapes.size(); i++){
            std::visit([&](const auto& concreteShape) {
                using T = std::decay_t<decltype(concreteShape)>;

                Color _pigment = generateNewColors ? _colorsUsed.emplace_back(newColor()) : _colorsUsed[i];

                if constexpr (std::is_same_v<T, ConvexPolygon>) {
                    drawConvexPolygon(full, _canvas, _pigment, concreteShape);
                }
                
                if constexpr (std::is_same_v<T, Rectangle>) {
                    drawRectangle(full, _canvas, _pigment, concreteShape);
                }
                /*   
                if constexpr (std::is_same_v<T, Ellipse>) {
                    drawRectangle(full, _canvas, _pigment, concreteShape);
                }
                if constexpr (std::is_same_v<T, Circle>) {
                    drawRectangle(full, _canvas, _pigment, concreteShape);
                }
                */
            }, _shapes[i]);
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
                    Canvas& _canvas, 
                    const int screenWidth, 
                    const int screenHeight){
        
        for (int y = 0; y < screenHeight; y++) {
            for (int x = 0; x < screenWidth; x++) {
                const int _tempx = x * _canvas.docWidth / screenWidth;
                const int _tempy = y * _canvas.docHeight / screenHeight;
                
                const Color _tempColor = _canvas.pixels[(_tempy * _canvas.docWidth) + _tempx];
                printColorOnFile(out, _tempColor);
            }
        }

    }
}

void visualizeShapes(
                std::ofstream& out,
                Canvas& _canvas, 
                const double screenWidth, 
                const double screenHeight, 
                const bool fullShapes,
                std::vector<Color>& _colorsUsed,
                const std::vector<Shape>& shapes){

                    
    drawOnCanvas(fullShapes, _canvas, _colorsUsed, shapes);

    writePPMHeader(out, screenWidth, screenHeight);

    drawCanvasOnFile(out, _canvas, screenWidth, screenHeight);
    
    return;
}