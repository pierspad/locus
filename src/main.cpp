
#include "../include/input.hpp"
#include "../include/geometry.hpp"
#include "../include/display.hpp"
#include "../include/canvas.hpp"
#include "../include/colors.hpp"


int main(){
    std::string inputFileName="../input.txt";
    std::string outputFileName="../output.ppm";
    std::ifstream input(inputFileName);
    std::ofstream output(outputFileName);

    std::vector<Shape> shapes;
    std::vector<Color> pixels;

    double _screenWidth = 1920;
    double _screenHeight = 1080;

    bool fullShapes = true;

    Canvas canvas {};

    ingestInput(input, canvas, shapes);

    canvas.pixels.assign(
        static_cast<std::size_t>(canvas.docWidth * canvas.docHeight),
        color_white
    );

    visualizeShapes(output, canvas, _screenWidth, _screenHeight, fullShapes, shapes);

    input.close();
    output.close();
}
