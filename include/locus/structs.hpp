#pragma once

#include <cstdint>
#include <functional>
#include <string_view>

struct Point{
    int x{0};
    int y{0};

    bool operator==(Point const&) const = default;
};

struct Color{
    uint8_t red{0};
    uint8_t green{0};
    uint8_t blue{0};
    
    bool operator==(Color const&) const = default;
};


namespace std {
    template<>
    struct hash<Point>{
        size_t operator()(Point const& p) const noexcept{
            size_t h1 = hash<int>{}(p.x);
            size_t h2 = hash<int>{}(p.y);
            return h1 ^ (h2 <<1);
        }
    };

    template<>
    struct hash<Color>{
        size_t operator()(Color const& c) const noexcept{
            size_t h1 = hash<uint8_t>{}(c.red);
            size_t h2 = hash<uint8_t>{}(c.green);
            size_t h3 = hash<uint8_t>{}(c.blue);
            return h1 ^ (h2 <<1) ^ (h3 << 2);
        }
    };


    
    template<>
    struct formatter<Point> : formatter<string_view> {
        auto format(const Point& p, format_context& ctx) const {
            
            auto str = std::format("({}, {})", p.x, p.y);
            return formatter<string_view>::format(str, ctx);
        }
    };


}