#include <print>
#include <vector>
#include <fstream>
#include <string>

constexpr std::string shapePath="./shape_files/";
constexpr std::string fileName="1.shape";


struct Color{
    uint8_t red{0};
    uint8_t green{0};
    uint8_t blue{0};
};

void readScreenSize(std::ifstream& ifile, int& width, int& height){

}

int main(){

    int width{0};
    int height{0};
    int number_of_figures{0};

    std::ifstream ifile(shapePath+fileName);
    ifile >> width;
    ifile >> height;
    ifile >> number_of_figures;

    std::vector<Color> pixels(width*height);

    std::println("Width: {} - Height: {} \n", width, height);
    std::println("Number of Figures: {}\n");
   
    




    /*
    for (int y = 0; y<height; y++){
        for(int x = 0; x<width; x++){
            int index = (y*width) + x;
            pixels[index].red = 0;
            pixels[index].green = 0;
            pixels[index].blue = 0;
        }
    }

    std::ofstream outFile("visualization.ppm", std::ios::binary);
    
    std::print(outFile, "P6\n{} {}\n255\n", width, height);
    outFile.write(reinterpret_cast<const char*>(pixels.data()), pixels.size());

    std::print("Immagine salvata in 'visualization.ppm'\n");
    
    return 0;

    */

}