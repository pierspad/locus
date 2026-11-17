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



Color cyan = {
    .r = 0,
    .g = 255,
    .b = 255,
};

Color magenta = {
    .r = 255,
    .g = 0,
    .b = 255,
};

Color yellow = {
    .r = 255,
    .g = 255,
    .b = 0,
};

Color black = {
    .r = 0,
    .g = 0,
    .b = 0,
};


