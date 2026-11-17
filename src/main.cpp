
#include "../include/input.hpp"
#include "../include/geometry.hpp"
#include "../include/display.hpp"


int main(){
    std::string inputFileName="../input.txt";
    std::string outputFileName="../output.ppm";
    std::ifstream input(inputFileName);
    std::ofstream output(outputFileName);

    std::vector<Shape> shapes;

    double docWidth;
    double docHeight;
    double screenWidth = 1920;
    double screenHeight = 1080;

    bool fullShapes = true;

    ingestInput(input, docWidth, docHeight, shapes);

    visualizeShapes(output, docWidth, docHeight, screenWidth, screenHeight, fullShapes, shapes);

    input.close();
    output.close();
}
