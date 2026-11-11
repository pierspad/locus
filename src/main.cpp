
#include "../include/input.hpp"
#include "../include/geometry.hpp"


int main(){
    std::string fileName="../input.txt";
    std::vector<Shape> shapes;

    ingestInput(fileName, shapes);
}
