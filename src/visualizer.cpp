#include <print>
#include <vector>
#include <fstream>
#include <string>
#include <unordered_set>

#include <locus/structs.hpp>
#include <locus/rect.hpp>


constexpr std::string shapePath="./shape_files/";
constexpr std::string fileName="1.shape";


void add_rectangle_to_vector(std::ifstream& ifile, std::vector<Rect>& shapes){
    int rect_width{0};
    int rect_height{0};
    int top{0};
    int left{0};
    ifile >> rect_width;
    ifile >> rect_height;
    ifile >> top;
    ifile >> left;
    shapes.push_back({
        .top_left = {.x = left, .y = top},
        .size = {.width = rect_width, .height = rect_height}
    });
}

void add_shape_to_vector(std::ifstream& ifile, std::vector<Rect>& shapes){
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
            add_rectangle_to_vector(ifile, shapes);
        break;
        default:
            //poligono
        break;
    }
}


Color get_color_by_id(int shape_id){
    Color color_i;
    
    uint8_t div_color = shape_id % 255;
    int module_color = shape_id % 7;

    switch(module_color){
        case(0):
            color_i = {
                .red = div_color,
                .green = 0,
                .blue = 0
            };
        break;
        case(1):
            color_i = {
                .red = 0,
                .green = div_color,
                .blue = 0
            };
        break;
        case(2):
            color_i = {
                .red = 0,
                .green = 0,
                .blue = div_color
            };
        break;
        case(3):
            color_i = {
                .red = 0,
                .green = 0,
                .blue = 0
            };
        break;
        case(4):
            color_i = {
                .red = div_color,
                .green = div_color,
                .blue = 0
            };
        break;
        case(5):
            color_i = {
                .red = div_color,
                .green = 0,
                .blue = div_color
            };
        break;
        case(6):
            color_i = {
                .red = 0,
                .green = div_color,
                .blue = div_color
            };
        break;
        default:
        break;
    }

    return color_i;
}


void find_coordinates_to_draw_line_a_b(std::vector<Color>& pixels, Point a, Point b, int shape_id, std::unordered_map<Point,Color>& points_to_draw){
    int max_x, max_y, min_x, min_y;
    max_x = std::max(a.x,b.x);
    max_y = std::max(a.y,b.y);
    min_x = std::min(a.x,b.x);
    min_y = std::min(a.y,b.y);

    Color color_i = get_color_by_id(shape_id);
    Point p;

    if(a.x==b.x && a.y == b.y){
        std::print("ERRORE: Coordinate uguali.\nA: {}\nB: {}\n", a, b);
    }
    else if(a.x==b.x){
        for(int i=min_y; i<max_y; i++){
            p.x = a.x;
            p.y = i;
            points_to_draw[p] = color_i;
        }
    }
    else if(a.y==b.y){
        for(int i=min_x; i<max_x; i++){
            p.x = i;
            p.y = a.y;
            points_to_draw[p] = color_i;
        }
    }
    else{ // diagonale
        //linea diagonale, da implementare più avanti
    }
    
}

std::unordered_map<Point, Color> refresh_color_pixels_with_shapes(std::vector<Color>& pixels, Rect rect, int shape_id, int screen_widht, int screen_height){
    std::unordered_map<Point, Color> points_to_draw;
    bool rectangle = true;
    
    Point up_left, up_right, bottom_left, bottom_right;
    up_left = {.x = rect.top_left.x, .y = rect.top_left.y};
    up_right = {.x = rect.top_left.x + rect.size.width, .y = rect.top_left.y};
    bottom_left = {.x = rect.top_left.x, .y = rect.top_left.y - rect.size.height};
    bottom_right = {.x = rect.top_left.x + rect.size.width, .y = rect.top_left.y - rect.size.height};
    
    if(rectangle){
        find_coordinates_to_draw_line_a_b(pixels, up_left, up_right, shape_id, points_to_draw);
        find_coordinates_to_draw_line_a_b(pixels, up_right, bottom_right, shape_id, points_to_draw);
        find_coordinates_to_draw_line_a_b(pixels, bottom_right, bottom_left, shape_id, points_to_draw);
        find_coordinates_to_draw_line_a_b(pixels, bottom_left, up_left, shape_id, points_to_draw);
    }

    for(int y = 0; y<screen_height; y++){
        for(int x = 0; x < screen_widht; x++){

        }
    }

    return points_to_draw;
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

    std::unordered_map<Point, Color> points_of_shapes_to_draw;

    std::print("Width: {} - Height: {}\n", width, height);
    std::print("Number of Figures: {}\n\n", number_of_figures);

    //disegna pixel bianchi
    for (int y = 0; y<height; y++){
        for(int x = 0; x<width; x++){
            int index = (y*width) + x;
            pixels[index].red = 0;
            pixels[index].green = 0;
            pixels[index].blue = 0;
        }
    }

    // leggi le forme dal file e mettile nel vettore
    for(int i = 0; i<number_of_figures; i++){
        add_shape_to_vector(ifile, shapes);
    }

    // calcola la posizione e il colore delle linee 
    for(int i  = 0; i<shapes.size(); i++){
        points_of_shapes_to_draw = refresh_color_pixels_with_shapes(pixels,shapes[i], i, width, height);
    }

    // disegna figure geometriche di sopra
     for (const auto& [point, color] : points_of_shapes_to_draw) {
        int index_colors = (point.y * width) + point.x;
        pixels[index_colors].red = color.red;
        pixels[index_colors].green = color.green;
        pixels[index_colors].blue = color.blue;
    }

    // stampa su file
    std::ofstream outFile("visualization.ppm", std::ios::binary);
    std::println(outFile, "P6");
    std::println(outFile, "{} {}", width, height);
    std::println(outFile, "255");
    outFile.write(reinterpret_cast<const char*>(pixels.data()), pixels.size());


    std::print("Immagine salvata in 'visualization.ppm'\n");
    
    return 0;


}