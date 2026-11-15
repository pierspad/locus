#pragma once

#include <vector>
#include <print>
#include <fstream>

#include "../include/geometry.hpp"
#include "../include/colors.hpp"


std::vector<Color> canvas;

void dye(Color& surface, const Color& pigment){
    surface.r = pigment.r;
    surface.g = pigment.g;
    surface.b = pigment.b;
}



// TODO implementa anche la modalità rettangolo pieno
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
    

    // Upper horizontal line
    for (double i = 0; i < recWidth; i++) {
        double index = docWidth * TLy + TLx + i;
        dye(_canvas[index], pigment);
    }

    // Bottom horizontal line
    for (double i = 0; i < recWidth; i++) {
        double index = docWidth * (TLy + recHeight - 1) + TLx + i;
        dye(_canvas[index], pigment);
    }

    // Left vertical line
    for (double i = 0; i < recHeight; i++) {
        double index = docWidth * (TLy + i) + TLx;
        dye(_canvas[index], pigment);
    }

    // Right vertical line
    for (double i = 0; i < recHeight; i++) {
        double index = docWidth * (TLy + i) + TLx + recWidth - 1;
        dye(_canvas[index], pigment);
    }

    // Filling
    if(full){

    }

}

void printColorOnFile(std::ofstream& out, const Color& color) {
    out << std::format("{} {} {} ",
        color.r,
        color.g,
        color.b
    );
}

//TODO
void drawOnCanvas(
                const double docWidth, 
                const double docHeight,
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

            /*
            if constexpr (std::is_same_v<T, Rectangle>) {
                bool full = false;
                drawRectangle(full, docWidth, docHeight, black, _canvas, concreteShape);
            }
                */
            if constexpr (std::is_same_v<T, Rectangle>) {
                bool full = false;
                drawRectangle(full, docWidth, docHeight, black, _canvas, concreteShape);
            }
           /*   
            if constexpr (std::is_same_v<T, Rectangle>) {
                bool full = false;
                drawRectangle(full, docWidth, docHeight, black, _canvas, concreteShape);
            }
            if constexpr (std::is_same_v<T, Rectangle>) {
                bool full = false;
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
    out << "P3\n";
    out << screenWidth << ' ' << screenHeight << '\n';
    out << "255\n";
}

// TODO
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
        out << '\n';
    }

}

void visualizeShapes(
                std::ofstream& out,
                const double docWidth, 
                const double docHeight, 
                const double screenWidth, 
                const double screenHeight, 
                const std::vector<Shape>& shapes){

    drawOnCanvas(docWidth, docHeight, canvas, shapes);

    writePPMHeader(out, screenWidth, screenHeight);

    drawCanvasOnFile(out, docWidth, docHeight, screenWidth, screenHeight,  canvas);
    
    return;
}