#include <filesystem>
#include <print>

#include "../include/input.hpp"
#include "../include/geometry.hpp"
#include "../include/display.hpp"
#include "../include/canvas.hpp"
#include "../include/colors.hpp"
#include "../include/solver.hpp"

namespace fs = std::filesystem;

int main(int argc, char* argv[]) {
    const std::span args(argv,argc);

    fs::path inputPath  = (args.size() > 1) ? args[1] : "input.txt";
    fs::path outputPath = (args.size() > 2) ? args[2] : "output.ppm";
    fs::path fixedOutputPath  = (args.size() > 3) ? args[3] : "output_fixed.ppm";

    if (!fs::exists(inputPath)) {
        std::println(stderr, "Errore: il file '{}' non esiste.", inputPath.string());
        return 1;
    }

    std::ifstream input(inputPath);
    std::ofstream output(outputPath);
    std::ofstream fixed(fixedOutputPath);

    std::vector<Shape> shapes;
    std::vector<Color> pixels;

    std::vector<Color> _colorsUsed;

    double _screenWidth = 1920;
    double _screenHeight = 1080;

    bool printFullShapes = true;

    Canvas canvas {};

    ingestInput(input, canvas, shapes);

    canvas.pixels.assign(
        static_cast<std::size_t>(canvas.docWidth * canvas.docHeight),
        color_white
    );

    visualizeShapes(output, canvas, _screenWidth, _screenHeight, printFullShapes, _colorsUsed, shapes);

    //unoverlapShapes(shapes);

    visualizeShapes(fixed, canvas, _screenWidth, _screenHeight, printFullShapes,  _colorsUsed, shapes);

    input.close();
    output.close();
}
