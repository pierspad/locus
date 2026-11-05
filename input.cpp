#include <fstream>
#include <sstream>

#include <print>


struct Coordinate{
    int x;
    int y;
};


void printCoords(int x, int y){
    std::println("x: {}\t\ty: {}", x,y);
}


void readCircle(std::stringstream& ss, std::string& line){
    
    std::println("This is a circle");
    std::println("");

    int radius, x, y;
    char comma;
    ss >> radius >> x >> comma >> y;

    std::println("{}", radius);
    std::println("radius");
    std::println("");

    printCoords(x, y);
}

void readRectangle(std::stringstream& ss, std::string& line){
    
    std::println("This is a rectangle");
    std::println("");

    int width, height, x, y;
    char comma;
    ss >> width >> height >> x >> comma >> y;

    std::println("{}", width);
    std::println("width");
    std::println("");

    std::println("{}", height);
    std::println("height");
    std::println("");

    printCoords(x, y);
}

void readSquare(std::stringstream& ss, std::string& line){
    
    std::println("This is a square");
    std::println("");

    int side, x, y;
    char comma;
    ss >> side >> x >> comma >> y;

    std::println("{}", side);
    std::println("side");
    std::println("");

    printCoords(x, y);
}

void readNGon(std::stringstream& ss, std::string& line){
    
    std::println("This is an n-gon");
    std::println("");

    int x, y, i=0;
    char comma;

    while(ss >> x >> comma >> y){
        std::println("{}-vertex", i);
        printCoords(x, y);
        i++;
    }
}



int main(){

    std::ifstream file("input.txt");
    std::string line;

    int i = 0;
    while(std::getline(file, line)){
        std::stringstream ss (line);

        int shapeType;
        if(!(ss >> shapeType)){
            continue;
        }
        i++;
        std::println("##### {} SHAPE #####", i);
        std::println("{}", shapeType);

        switch(shapeType){
            case 0: // circle
                readCircle(ss, line);
                break;
            case 1: // square
                readSquare(ss, line);
                break;
            case 2: // rectangle
                readRectangle(ss, line);
                break;
            default: // n-gon
                readNGon(ss, line);
                break;
        }

        std::println("##### END SHAPE #####");
        std::println("");

    }





}

