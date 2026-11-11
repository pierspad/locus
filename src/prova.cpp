
#include <vector>
#include <print>
#include <fstream>
#include <sstream>

#include "../include/input.hpp"
#include "../include/geometry.hpp"


int main(){
    std::string fileName="../input.txt";
    std::vector<Shape> shapes;

    ingestInput(fileName, shapes);
}

