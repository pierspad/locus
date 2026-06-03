#include <print>
#include <vector>
#include <iostream> 
#include <fstream>
#include <string>

constexpr std::string shapePath="./shape_files";
constexpr std::string fileName="1.shape";


void readFigures(){
    
}

int main(){

    constexpr int width = 800;
    constexpr int height = 600;

    std::vector<std::uint8_t> pixels(width*height*3,0);

    for (int y = 0; y<height; y++){
        for(int x = 0; x<width; x++){
            int index = ((y*width) + x) * 3;

            pixels[index]     = static_cast<std::uint8_t>((x * 255) / width);  // Rosso
            pixels[index + 1] = static_cast<std::uint8_t>((y * 255) / height); // Verde
            pixels[index + 2] = 128;
        }
    }

    std::ofstream outFile("visualization.ppm", std::ios::binary);
    
    std::print(outFile, "P6\n{} {}\n255\n", width, height);
    outFile.write(reinterpret_cast<const char*>(pixels.data()), pixels.size());

    std::print("Immagine salvata in 'visualization.ppm'\n");
    
    return 0;

}