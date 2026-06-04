#include <print>
#include <vector>
#include <fstream>
#include <string>
#include "rect.hpp"

constexpr std::string shapePath="./shape_files/";
constexpr std::string fileName="1.shape";

struct Color{
    uint8_t red{0};
    uint8_t green{0};
    uint8_t blue{0};
};

void addRectangle(std::ifstream& ifile, std::vector<Rect>& shapes){
    int width{0};
    int height{0};
    int top{0};
    int left{0};
    ifile >> width;
    ifile >> height;
    ifile >> top;
    ifile >> left;
    shapes.push_back({
        .top_left = {.x = left, .y = top},
        .size = {.width = width, .height = height}
    });
}

void addFigure(std::ifstream& ifile, std::vector<Rect>& shapes){
    int figure_type{0};
    ifile >> figure_type;

    switch(figure_type){
        case(0):
            //addCircle()
        break;
        case(1):
            //quadrato
        break;
        case(2):
            addRectangle(ifile, shapes);
        break;
        default:
            //poligono
        
    }
}


std::vector<Point> draw_line_a_b(std::vector<Color>& pixels, Point a, Point b){

}

void color_pixels_with_shape(std::vector<Color>& pixels, Rect rect, int shape_id, int screen_widht, int screen_height){
    
    
    std::vector<Point> points_to_draw;
    bool rectangle = true;
    
    Point up_left, up_right, bottom_left, bottom_right;
    up_left = {.x = rect.top_left.x, .y = rect.top_left.y};
    up_right = {.x = rect.top_left.x, .y = rect.top_left.y};
    bottom_left = {.x = rect.top_left.x, .y = rect.top_left.y};
    bottom_right = {.x = rect.top_left.x, .y = rect.top_left.y};
    
    if(rectangle){
        points_to_draw.push_back(draw_line_a_b(pixels, up_left, up_right));
        points_to_draw.push_back(draw_line_a_b(pixels, up_right, bottom_right));
        points_to_draw.push_back(draw_line_a_b(pixels, bottom_right, bottom_left);
        points_to_draw.push_back(draw_line_a_b(pixels, bottom_left, up_left));
    }

    for(int y = 0; y<screen_height; y++){
        for(int x = 0; x < screen_widht; x++){

        }
    }
}


int main(){

    int width{0};
    int height{0};
    int number_of_figures{0};

    std::ifstream ifile(shapePath + fileName);
    ifile >> width;
    ifile >> height;
    ifile >> number_of_figures;

    std::vector<Rect> shapes;

    std::vector<Color> pixels(width*height);

    std::println("Width: {} - Height: {} \n", width, height);
    std::println("Number of Figures: {}\n");

    for(int i = 0; i<number_of_figures; i++){
        addFigure(ifile, shapes);
    }

    for(int i  = 0; i<shapes.size(); i++){
        color_pixels_with_shape(pixels,shapes[i], i);
    }
   





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