
#include <vector>
#include <print>



struct Color {
    std::uint8_t r;
    std::uint8_t g;
    std::uint8_t b;
};

std::vector<Color> canvas;


void drawRectangle(
                const int docWidth, 
                const int docHeight,
                std::vector<Color>& _canvas, 
                const Shape& _concreteShape){
    
}

void colorCanvas(
                const int docWidth, 
                const int docHeight,
                std::vector<Color>& _canvas, 
                const std::vector<Shape>& _shapes){

    for(int x = 0; x<docWidth; x++){
        for(int y = 0; y<docHeight; y++){
            _canvas.emplace_back(Color{
                .r = 0,
                .g = 0,
                .b = 0
            });
        }
    }

    for (const Shape& shape : _shapes) {
        std::visit([&](const auto& concreteShape) {
            using T = std::decay_t<decltype(concreteShape)>;

            if constexpr (std::is_same_v<T, ConvexPolygon>) {
                drawRectangle( docWidth, docHeight, _canvas, concreteShape);
            }
            if constexpr (std::is_same_v<T, Rectangle>) {
                drawRectangle( docWidth, docHeight, _canvas, concreteShape);
            }
            if constexpr (std::is_same_v<T, Ellipse>) {
                drawRectangle( docWidth, docHeight, _canvas, concreteShape);
            }
            if constexpr (std::is_same_v<T, Circle>) {
                drawRectangle( docWidth, docHeight, _canvas, concreteShape);
            }
        }, shape);
    }
}


void visualizeShapes(
                const int docWidth, 
                const int docHeight, 
                const std::vector<Shape>& shapes){

    int adaptConstWidth = 1920/docWidth;
    int adaptConstHeight = 1080/docHeight;

    colorCanvas(canvas, shapes);


    // prints will use x and y starting from the topleftmost
    for(int x = 0; x<1920; x++){
        for(int y = 0; y<1080; y++){

        }
    }
    
    return;
}