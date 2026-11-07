
#include <vector>
#include <print>
#include <fstream>
#include <sstream>

void test(std::vector<int>& vec1){
    int size = vec1.size();

    //should print 5
    std::println("{}", vec1[size-1]);
}

int main(){

    std::string fileName="../prova.txt";

    std::ifstream file(fileName);
    std::string line;

    std::getline(file, line);

    const auto pos = line.find_first_not_of(" \t\r\n");

    if (pos == std::string::npos) {
        std::println("pos {}: not found", pos);
    }
    if (line.compare(pos, 1, "#") == 0 ) {
        std::println("pos {}: #", pos);
    }
    if (line.compare(pos, 2, "//") == 0) {
        std::println("pos {}: //", pos);
    }


}
