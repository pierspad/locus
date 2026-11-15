
#include "../include/input.hpp"
#include "../include/geometry.hpp"
#include "../include/display.hpp"


int main(){
    std::string inputFileName="../input.txt";
    std::string outputFileName="./output.ppm";
    std::ifstream input(inputFileName);
    std::ofstream output(outputFileName);

    std::vector<Shape> shapes;

    double docWidth = 0;
    double docHeight = 0;
    double screenWidth = 1920;
    double screenHeight = 1080;

    ingestInput(input, docWidth, docHeight, shapes);

    visualizeShapes(output, docWidth, docHeight, screenWidth, screenHeight, shapes);

    input.close();
    output.close();
}
