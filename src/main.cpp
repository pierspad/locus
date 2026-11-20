
#include "../include/input.hpp"
#include "../include/geometry.hpp"
#include "../include/display.hpp"
#include "../include/canvas.hpp"
#include "../include/colors.hpp"
#include "../include/solver.hpp"


int main(){
    std::string inputFileName="../input.txt";
    std::ifstream input(inputFileName);

    std::string outputFileName="../output.ppm";
    std::ofstream output(outputFileName);

    std::string fixedFileName="../output_fixed.ppm";
    std::ofstream fixed(fixedFileName);

    std::vector<Shape> shapes;
    std::vector<Color> pixels;

    double _screenWidth = 1920;
    double _screenHeight = 1080;

    bool printFullShapes = true;

    Canvas canvas {};

    ingestInput(input, canvas, shapes);

    canvas.pixels.assign(
        static_cast<std::size_t>(canvas.docWidth * canvas.docHeight),
        color_white
    );

    visualizeShapes(output, canvas, _screenWidth, _screenHeight, printFullShapes, shapes);

    unoverlapShapes(shapes);

    

    visualizeShapes(fixed, canvas, _screenWidth, _screenHeight, printFullShapes, shapes);

    input.close();
    output.close();
}
