#pragma once

struct Color {
    std::uint8_t r;
    std::uint8_t g;
    std::uint8_t b;

    bool operator==(const Color& color1){
        return (r == color1.r) && (g == color1.g) && (b == color1.b);
    }

    bool operator!=(const Color& color1){
        return (r != color1.r) || (g != color1.g) || (b != color1.b);
    }
};



const Color color_cyan = {
    .r = 0,
    .g = 255,
    .b = 255,
};

const Color color_magenta = {
    .r = 255,
    .g = 0,
    .b = 255,
};

const Color color_yellow = {
    .r = 255,
    .g = 255,
    .b = 0,
};

const Color color_black = {
    .r = 0,
    .g = 0,
    .b = 0,
};

const Color color_white = {
    .r = 255,
    .g = 255,
    .b = 255,
};


