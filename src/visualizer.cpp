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
    
    uint8_t div_color = (shape_id*163) % 255;
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

void swap_Points(Point& v1, Point& v2){
    Point _tmp{
        .x = v1.x,
        .y = v1.y
    };

    v1.x = v2.x;
    v1.y = v2.y;

    v2.x = _tmp.x;
    v2.y = _tmp.y;
}

void draw_line_between_v1_v2(Point& v1, Point& v2, const Color& color, std::unordered_map<Point,Color>& points_to_draw){
    
    Point p;

    if(v1==v2){
        std::print("ERRORE: Coordinate uguali.\nA: {}\nB: {}\n", v1, v2);
    }

    // il v1 è sempre quello con la x inferiore
    if(v1.x < v2.x){
        swap_Points(v1,v2);
    }
    
    int horizontal_dir = 1;
    int vertical_dir = 1;
    if(v1.y > v2.y){
        vertical_dir = -1;
    }
    
    float n_segmenti, len_segmento;
    int x_diff, y_diff;
    
    x_diff = abs(v1.x-v2.x);
    y_diff = abs(v1.y-v2.y);

    bool rect_vert = false;

    if(x_diff < y_diff){
        int _tmp = x_diff;
        x_diff = y_diff;
        y_diff = _tmp;
        rect_vert = true;
    }

    len_segmento = x_diff/y_diff;
    n_segmenti = y_diff; 
    int n_segmentip1 = 0;

    int _tmp = x_diff;

    while((_tmp % y_diff) != 0){
        n_segmentip1 += 1;
        _tmp -=1;
    }

    int n_segmenti_norm = n_segmenti - n_segmentip1;


    if(rect_vert){
        for(int i = 0; i<n_segmentip1; i++){
            for(int j = 0; j<len_segmento+1; j++){
                p.x = v1.x + (i * vertical_dir);
                p.y = v1.y + (i * (len_segmento + 1)) + j;
                points_to_draw[p] = color;
            }
        }
        for(int i = 0; i<n_segmenti_norm; i++){
            for(int j = 0; j<len_segmento; j++){
                p.x = v1.x + (n_segmentip1 * (len_segmento+1))  + (i * vertical_dir);
                p.y = v1.y + (n_segmentip1)                     + (i * len_segmento) + j;
                points_to_draw[p] = color;
            }
        }
    }
    else{
        for(int i = 0; i<n_segmentip1; i++){
            for(int j = 0; j<len_segmento+1; j++){
                p.x = v1.x + (i * (len_segmento + 1)) + j;
                p.y = v1.y + (i * vertical_dir);
                points_to_draw[p] = color;
            }
        }
        for(int i = 0; i<n_segmenti_norm; i++){
            for(int j = 0; j<len_segmento; j++){
                p.x = v1.x + (n_segmentip1)                     + (i * len_segmento) + j;
                p.y = v1.y + (n_segmentip1 * (len_segmento+1))  + (i * vertical_dir);
                points_to_draw[p] = color;
            }
        }
    }

}

void annotate_lines_between_vertices(std::vector<Point>& vertices, int shape_id, std::unordered_map<Point,Color>& points_to_draw){
    
    int size = vertices.size();
    if(size <2){
        std::print("Servono almeno 2 vertici da disegnare");
        return;
    }

    Color color_i = get_color_by_id(shape_id);

    for(int i = 0; i<vertices.size()-1; i++){
        draw_line_between_v1_v2(vertices[i], vertices[i+1], color_i, points_to_draw);
    }   
}

void refresh_color_pixels_with_shapes(Rect rect, int shape_id, int screen_widht, int screen_height, std::unordered_map<Point, Color>& points_to_draw){
    
    bool rectangle = true;
    std::vector<Point> vertices;
    
    if(rectangle){
        Point up_left, up_right, bottom_left, bottom_right;
        up_left = {.x = rect.top_left.x, .y = rect.top_left.y};
        up_right = {.x = rect.top_left.x + rect.size.width, .y = rect.top_left.y};
        bottom_left = {.x = rect.top_left.x, .y = rect.top_left.y + rect.size.height};
        bottom_right = {.x = rect.top_left.x + rect.size.width, .y = rect.top_left.y + rect.size.height};

        vertices.push_back(up_left);
        vertices.push_back(up_right);
        vertices.push_back(bottom_left);
        vertices.push_back(bottom_right);
    }

    annotate_lines_between_vertices(vertices, shape_id, points_to_draw);
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

    // leggi le forme dal file e mettile nel vettore
    for(int i = 0; i<number_of_figures; i++){
        add_shape_to_vector(ifile, shapes);
    }

    // calcola la posizione e il colore delle linee 
    for(int i  = 0; i<shapes.size(); i++){
        refresh_color_pixels_with_shapes(shapes[i], i, width, height, points_of_shapes_to_draw);
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
    outFile.write(reinterpret_cast<const char*>(pixels.data()), pixels.size() * sizeof(Color));


    std::print("Immagine salvata in 'visualization.ppm'\n");
    
    return 0;


}