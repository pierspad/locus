
#include <random>

#include "../include/colors.hpp"

std::random_device rd;
std::mt19937 generator(rd()); 


[[nodiscard]]
Color newColor(){
    std::uniform_int_distribution<> range(0, 255);

    return {
        .r = static_cast<uint8_t>(range(generator)),
        .g = static_cast<uint8_t>(range(generator)),
        .b = static_cast<uint8_t>(range(generator)),
    };
}



