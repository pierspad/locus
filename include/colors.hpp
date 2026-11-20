#pragma once

#include <random>

struct Color {
    std::uint8_t r;
    std::uint8_t g;
    std::uint8_t b;

    bool operator==(const Color&) const = default;
};

[[nodiscard]]
Color newColor();

inline constexpr Color color_cyan = {
    .r = 0,
    .g = 255,
    .b = 255,
};

inline constexpr Color color_magenta = {
    .r = 255,
    .g = 0,
    .b = 255,
};

inline constexpr Color color_yellow = {
    .r = 255,
    .g = 255,
    .b = 0,
};

inline constexpr Color color_black = {
    .r = 0,
    .g = 0,
    .b = 0,
};

inline constexpr Color color_white = {
    .r = 255,
    .g = 255,
    .b = 255,
};


