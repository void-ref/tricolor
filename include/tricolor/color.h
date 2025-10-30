/*
 * Copyright 2025 Mitchell Matsumori-Kelly
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */

#pragma once

#include <cstdint>

namespace tricolor {

    inline uint8_t saturating_add(uint8_t lhs, uint8_t rhs) {
        return (lhs + rhs < lhs) ? 0xFF : lhs + rhs;
    }

    inline uint8_t saturating_sub(uint8_t lhs, uint8_t rhs) {
        return (lhs - rhs > lhs) ? 0 : lhs - rhs;
    }

    struct Color {
        uint8_t r;
        uint8_t g;
        uint8_t b;

        constexpr Color() : Color(0x000000) {}

        constexpr Color(uint32_t rgb) :
            r((rgb >> 16) & 0xFF),
            g((rgb >> 8) & 0xFF),
            b(rgb & 0xFF) {}

        constexpr Color(uint8_t r, uint8_t g, uint8_t b) : r(r), g(g), b(b) {}

        constexpr uint32_t rgb() const {
            return ((r << 16) | (g << 8) | b);
        }

        Color operator*(float rhs) {
            return Color(r * rhs, g * rhs, b * rhs);
        }

        Color operator/(float rhs) {
            if (rhs == 0) {
                return Color(0xFF, 0xFF, 0xFF);
            }
            return Color(r / rhs, g / rhs, b / rhs);
        }

        Color operator+(uint8_t rhs) {
            return Color(saturating_add(b, rhs), saturating_add(g, rhs), saturating_add(r, rhs));
        }

        Color operator+(Color rhs) {
            return Color(
                saturating_add(r, rhs.r),
                saturating_add(g, rhs.g),
                saturating_add(b, rhs.b)
            );
        }

        Color operator-(uint8_t rhs) {
            return Color(saturating_sub(b, rhs), saturating_sub(g, rhs), saturating_sub(r, rhs));
        }

        Color operator-(Color rhs) {
            return Color(
                saturating_sub(r, rhs.r),
                saturating_sub(g, rhs.g),
                saturating_sub(b, rhs.b)
            );
        }

        template<typename T>
        Color& operator*=(T&& rhs) {
            return *this = *this * rhs;
        }

        template<typename T>
        Color& operator/=(T&& rhs) {
            return *this = *this / rhs;
        }

        template<typename T>
        Color& operator+=(T&& rhs) {
            return *this = *this + rhs;
        }

        template<typename T>
        Color& operator-=(T&& rhs) {
            return *this = *this - rhs;
        }

#define COLOR_DECL(_name_) static Color const _name_
        COLOR_DECL(ALICE_BLUE);
        COLOR_DECL(ANTIQUE_WHITE);
        COLOR_DECL(AQUA);
        COLOR_DECL(AQUAMARINE);
        COLOR_DECL(AZURE);
        COLOR_DECL(BEIGE);
        COLOR_DECL(BISQUE);
        COLOR_DECL(BLACK);
        COLOR_DECL(BLANCHED_ALMOND);
        COLOR_DECL(BLUE);
        COLOR_DECL(BLUE_VIOLET);
        COLOR_DECL(BROWN);
        COLOR_DECL(BURLY_WOOD);
        COLOR_DECL(CADET_BLUE);
        COLOR_DECL(CHARTREUSE);
        COLOR_DECL(CHOCOLATE);
        COLOR_DECL(CORAL);
        COLOR_DECL(CORNFLOWER_BLUE);
        COLOR_DECL(CORNSILK);
        COLOR_DECL(CRIMSON);
        COLOR_DECL(CYAN);
        COLOR_DECL(DARK_BLUE);
        COLOR_DECL(DARK_CYAN);
        COLOR_DECL(DARK_GOLDEN_ROD);
        COLOR_DECL(DARK_GRAY);
        COLOR_DECL(DARK_GREEN);
        COLOR_DECL(DARK_KHAKI);
        COLOR_DECL(DARK_MAGENTA);
        COLOR_DECL(DARK_OLIVE_GREEN);
        COLOR_DECL(DARK_ORANGE);
        COLOR_DECL(DARK_ORCHID);
        COLOR_DECL(DARK_RED);
        COLOR_DECL(DARK_SALMON);
        COLOR_DECL(DARK_SEA_GREEN);
        COLOR_DECL(DARK_SLATE_BLUE);
        COLOR_DECL(DARK_SLATE_GRAY);
        COLOR_DECL(DARK_TURQUOISE);
        COLOR_DECL(DARK_VIOLET);
        COLOR_DECL(DEEP_PINK);
        COLOR_DECL(DEEP_SKY_BLUE);
        COLOR_DECL(DIM_GRAY);
        COLOR_DECL(DODGER_BLUE);
        COLOR_DECL(FIRE_BRICK);
        COLOR_DECL(FLORAL_WHITE);
        COLOR_DECL(FOREST_GREEN);
        COLOR_DECL(FUCHSIA);
        COLOR_DECL(GAINSBORO);
        COLOR_DECL(GHOST_WHITE);
        COLOR_DECL(GOLD);
        COLOR_DECL(GOLDEN_ROD);
        COLOR_DECL(GRAY);
        COLOR_DECL(GREEN);
        COLOR_DECL(GREEN_YELLOW);
        COLOR_DECL(HONEY_DEW);
        COLOR_DECL(HOT_PINK);
        COLOR_DECL(INDIAN_RED);
        COLOR_DECL(INDIGO);
        COLOR_DECL(IVORY);
        COLOR_DECL(KHAKI);
        COLOR_DECL(LAVENDER);
        COLOR_DECL(LAVENDER_BLUSH);
        COLOR_DECL(LAWN_GREEN);
        COLOR_DECL(LEMON_CHIFFON);
        COLOR_DECL(LIGHT_BLUE);
        COLOR_DECL(LIGHT_CORAL);
        COLOR_DECL(LIGHT_CYAN);
        COLOR_DECL(LIGHT_GOLDEN_ROD_YELLOW);
        COLOR_DECL(LIGHT_GRAY);
        COLOR_DECL(LIGHT_GREEN);
        COLOR_DECL(LIGHT_PINK);
        COLOR_DECL(LIGHT_SALMON);
        COLOR_DECL(LIGHT_SEA_GREEN);
        COLOR_DECL(LIGHT_SKY_BLUE);
        COLOR_DECL(LIGHT_SLATE_GRAY);
        COLOR_DECL(LIGHT_STEEL_BLUE);
        COLOR_DECL(LIGHT_YELLOW);
        COLOR_DECL(LIME);
        COLOR_DECL(LIME_GREEN);
        COLOR_DECL(LINEN);
        COLOR_DECL(MAGENTA);
        COLOR_DECL(MAROON);
        COLOR_DECL(MEDIUM_AQUAMARINE);
        COLOR_DECL(MEDIUM_BLUE);
        COLOR_DECL(MEDIUM_ORCHID);
        COLOR_DECL(MEDIUM_PURPLE);
        COLOR_DECL(MEDIUM_SEA_GREEN);
        COLOR_DECL(MEDIUM_SLATE_BLUE);
        COLOR_DECL(MEDIUM_SPRING_GREEN);
        COLOR_DECL(MEDIUM_TURQUOISE);
        COLOR_DECL(MEDIUM_VIOLET_RED);
        COLOR_DECL(MIDNIGHT_BLUE);
        COLOR_DECL(MINT_CREAM);
        COLOR_DECL(MISTY_ROSE);
        COLOR_DECL(MOCCASIN);
        COLOR_DECL(NAVAJO_WHITE);
        COLOR_DECL(NAVY);
        COLOR_DECL(OLD_LACE);
        COLOR_DECL(OLIVE);
        COLOR_DECL(OLIVE_DRAB);
        COLOR_DECL(ORANGE);
        COLOR_DECL(ORANGE_RED);
        COLOR_DECL(ORCHID);
        COLOR_DECL(PALE_GOLDEN_ROD);
        COLOR_DECL(PALE_GREEN);
        COLOR_DECL(PALE_TURQUOISE);
        COLOR_DECL(PALE_VIOLET_RED);
        COLOR_DECL(PAPAYA_WHIP);
        COLOR_DECL(PEACH_PUFF);
        COLOR_DECL(PERU);
        COLOR_DECL(PINK);
        COLOR_DECL(PLUM);
        COLOR_DECL(POWDER_BLUE);
        COLOR_DECL(PURPLE);
        COLOR_DECL(REBECCA_PURPLE);
        COLOR_DECL(RED);
        COLOR_DECL(ROSY_BROWN);
        COLOR_DECL(ROYAL_BLUE);
        COLOR_DECL(SADDLE_BROWN);
        COLOR_DECL(SALMON);
        COLOR_DECL(SANDY_BROWN);
        COLOR_DECL(SEA_GREEN);
        COLOR_DECL(SEA_SHELL);
        COLOR_DECL(SIENNA);
        COLOR_DECL(SILVER);
        COLOR_DECL(SKY_BLUE);
        COLOR_DECL(SLATE_BLUE);
        COLOR_DECL(SLATE_GRAY);
        COLOR_DECL(SNOW);
        COLOR_DECL(SPRING_GREEN);
        COLOR_DECL(STEEL_BLUE);
        COLOR_DECL(TAN);
        COLOR_DECL(TEAL);
        COLOR_DECL(THISTLE);
        COLOR_DECL(TOMATO);
        COLOR_DECL(TURQUOISE);
        COLOR_DECL(VIOLET);
        COLOR_DECL(WHEAT);
        COLOR_DECL(WHITE);
        COLOR_DECL(WHITE_SMOKE);
        COLOR_DECL(YELLOW);
        COLOR_DECL(YELLOW_GREEN);
#undef COLOR_DECL
    };

    // Copyright (c) 2018 - present, Victor Zverovich and fmt contributors
    // https://github.com/fmtlib/fmt

#define COLOR_DEF(_name_, _value_) constexpr Color const Color::_name_ = Color(_value_)
    COLOR_DEF(ALICE_BLUE, 0xF0F8FF);              // rgb(240,248,255)
    COLOR_DEF(ANTIQUE_WHITE, 0xFAEBD7);           // rgb(250,235,215)
    COLOR_DEF(AQUA, 0x00FFFF);                    // rgb(0,255,255)
    COLOR_DEF(AQUAMARINE, 0x7FFFD4);              // rgb(127,255,212)
    COLOR_DEF(AZURE, 0xF0FFFF);                   // rgb(240,255,255)
    COLOR_DEF(BEIGE, 0xF5F5DC);                   // rgb(245,245,220)
    COLOR_DEF(BISQUE, 0xFFE4C4);                  // rgb(255,228,196)
    COLOR_DEF(BLACK, 0x000000);                   // rgb(0,0,0)
    COLOR_DEF(BLANCHED_ALMOND, 0xFFEBCD);         // rgb(255,235,205)
    COLOR_DEF(BLUE, 0x0000FF);                    // rgb(0,0,255)
    COLOR_DEF(BLUE_VIOLET, 0x8A2BE2);             // rgb(138,43,226)
    COLOR_DEF(BROWN, 0xA52A2A);                   // rgb(165,42,42)
    COLOR_DEF(BURLY_WOOD, 0xDEB887);              // rgb(222,184,135)
    COLOR_DEF(CADET_BLUE, 0x5F9EA0);              // rgb(95,158,160)
    COLOR_DEF(CHARTREUSE, 0x7FFF00);              // rgb(127,255,0)
    COLOR_DEF(CHOCOLATE, 0xD2691E);               // rgb(210,105,30)
    COLOR_DEF(CORAL, 0xFF7F50);                   // rgb(255,127,80)
    COLOR_DEF(CORNFLOWER_BLUE, 0x6495ED);         // rgb(100,149,237)
    COLOR_DEF(CORNSILK, 0xFFF8DC);                // rgb(255,248,220)
    COLOR_DEF(CRIMSON, 0xDC143C);                 // rgb(220,20,60)
    COLOR_DEF(CYAN, 0x00FFFF);                    // rgb(0,255,255)
    COLOR_DEF(DARK_BLUE, 0x00008B);               // rgb(0,0,139)
    COLOR_DEF(DARK_CYAN, 0x008B8B);               // rgb(0,139,139)
    COLOR_DEF(DARK_GOLDEN_ROD, 0xB8860B);         // rgb(184,134,11)
    COLOR_DEF(DARK_GRAY, 0xA9A9A9);               // rgb(169,169,169)
    COLOR_DEF(DARK_GREEN, 0x006400);              // rgb(0,100,0)
    COLOR_DEF(DARK_KHAKI, 0xBDB76B);              // rgb(189,183,107)
    COLOR_DEF(DARK_MAGENTA, 0x8B008B);            // rgb(139,0,139)
    COLOR_DEF(DARK_OLIVE_GREEN, 0x556B2F);        // rgb(85,107,47)
    COLOR_DEF(DARK_ORANGE, 0xFF8C00);             // rgb(255,140,0)
    COLOR_DEF(DARK_ORCHID, 0x9932CC);             // rgb(153,50,204)
    COLOR_DEF(DARK_RED, 0x8B0000);                // rgb(139,0,0)
    COLOR_DEF(DARK_SALMON, 0xE9967A);             // rgb(233,150,122)
    COLOR_DEF(DARK_SEA_GREEN, 0x8FBC8F);          // rgb(143,188,143)
    COLOR_DEF(DARK_SLATE_BLUE, 0x483D8B);         // rgb(72,61,139)
    COLOR_DEF(DARK_SLATE_GRAY, 0x2F4F4F);         // rgb(47,79,79)
    COLOR_DEF(DARK_TURQUOISE, 0x00CED1);          // rgb(0,206,209)
    COLOR_DEF(DARK_VIOLET, 0x9400D3);             // rgb(148,0,211)
    COLOR_DEF(DEEP_PINK, 0xFF1493);               // rgb(255,20,147)
    COLOR_DEF(DEEP_SKY_BLUE, 0x00BFFF);           // rgb(0,191,255)
    COLOR_DEF(DIM_GRAY, 0x696969);                // rgb(105,105,105)
    COLOR_DEF(DODGER_BLUE, 0x1E90FF);             // rgb(30,144,255)
    COLOR_DEF(FIRE_BRICK, 0xB22222);              // rgb(178,34,34)
    COLOR_DEF(FLORAL_WHITE, 0xFFFAF0);            // rgb(255,250,240)
    COLOR_DEF(FOREST_GREEN, 0x228B22);            // rgb(34,139,34)
    COLOR_DEF(FUCHSIA, 0xFF00FF);                 // rgb(255,0,255)
    COLOR_DEF(GAINSBORO, 0xDCDCDC);               // rgb(220,220,220)
    COLOR_DEF(GHOST_WHITE, 0xF8F8FF);             // rgb(248,248,255)
    COLOR_DEF(GOLD, 0xFFD700);                    // rgb(255,215,0)
    COLOR_DEF(GOLDEN_ROD, 0xDAA520);              // rgb(218,165,32)
    COLOR_DEF(GRAY, 0x808080);                    // rgb(128,128,128)
    COLOR_DEF(GREEN, 0x008000);                   // rgb(0,128,0)
    COLOR_DEF(GREEN_YELLOW, 0xADFF2F);            // rgb(173,255,47)
    COLOR_DEF(HONEY_DEW, 0xF0FFF0);               // rgb(240,255,240)
    COLOR_DEF(HOT_PINK, 0xFF69B4);                // rgb(255,105,180)
    COLOR_DEF(INDIAN_RED, 0xCD5C5C);              // rgb(205,92,92)
    COLOR_DEF(INDIGO, 0x4B0082);                  // rgb(75,0,130)
    COLOR_DEF(IVORY, 0xFFFFF0);                   // rgb(255,255,240)
    COLOR_DEF(KHAKI, 0xF0E68C);                   // rgb(240,230,140)
    COLOR_DEF(LAVENDER, 0xE6E6FA);                // rgb(230,230,250)
    COLOR_DEF(LAVENDER_BLUSH, 0xFFF0F5);          // rgb(255,240,245)
    COLOR_DEF(LAWN_GREEN, 0x7CFC00);              // rgb(124,252,0)
    COLOR_DEF(LEMON_CHIFFON, 0xFFFACD);           // rgb(255,250,205)
    COLOR_DEF(LIGHT_BLUE, 0xADD8E6);              // rgb(173,216,230)
    COLOR_DEF(LIGHT_CORAL, 0xF08080);             // rgb(240,128,128)
    COLOR_DEF(LIGHT_CYAN, 0xE0FFFF);              // rgb(224,255,255)
    COLOR_DEF(LIGHT_GOLDEN_ROD_YELLOW, 0xFAFAD2); // rgb(250,250,210)
    COLOR_DEF(LIGHT_GRAY, 0xD3D3D3);              // rgb(211,211,211)
    COLOR_DEF(LIGHT_GREEN, 0x90EE90);             // rgb(144,238,144)
    COLOR_DEF(LIGHT_PINK, 0xFFB6C1);              // rgb(255,182,193)
    COLOR_DEF(LIGHT_SALMON, 0xFFA07A);            // rgb(255,160,122)
    COLOR_DEF(LIGHT_SEA_GREEN, 0x20B2AA);         // rgb(32,178,170)
    COLOR_DEF(LIGHT_SKY_BLUE, 0x87CEFA);          // rgb(135,206,250)
    COLOR_DEF(LIGHT_SLATE_GRAY, 0x778899);        // rgb(119,136,153)
    COLOR_DEF(LIGHT_STEEL_BLUE, 0xB0C4DE);        // rgb(176,196,222)
    COLOR_DEF(LIGHT_YELLOW, 0xFFFFE0);            // rgb(255,255,224)
    COLOR_DEF(LIME, 0x00FF00);                    // rgb(0,255,0)
    COLOR_DEF(LIME_GREEN, 0x32CD32);              // rgb(50,205,50)
    COLOR_DEF(LINEN, 0xFAF0E6);                   // rgb(250,240,230)
    COLOR_DEF(MAGENTA, 0xFF00FF);                 // rgb(255,0,255)
    COLOR_DEF(MAROON, 0x800000);                  // rgb(128,0,0)
    COLOR_DEF(MEDIUM_AQUAMARINE, 0x66CDAA);       // rgb(102,205,170)
    COLOR_DEF(MEDIUM_BLUE, 0x0000CD);             // rgb(0,0,205)
    COLOR_DEF(MEDIUM_ORCHID, 0xBA55D3);           // rgb(186,85,211)
    COLOR_DEF(MEDIUM_PURPLE, 0x9370DB);           // rgb(147,112,219)
    COLOR_DEF(MEDIUM_SEA_GREEN, 0x3CB371);        // rgb(60,179,113)
    COLOR_DEF(MEDIUM_SLATE_BLUE, 0x7B68EE);       // rgb(123,104,238)
    COLOR_DEF(MEDIUM_SPRING_GREEN, 0x00FA9A);     // rgb(0,250,154)
    COLOR_DEF(MEDIUM_TURQUOISE, 0x48D1CC);        // rgb(72,209,204)
    COLOR_DEF(MEDIUM_VIOLET_RED, 0xC71585);       // rgb(199,21,133)
    COLOR_DEF(MIDNIGHT_BLUE, 0x191970);           // rgb(25,25,112)
    COLOR_DEF(MINT_CREAM, 0xF5FFFA);              // rgb(245,255,250)
    COLOR_DEF(MISTY_ROSE, 0xFFE4E1);              // rgb(255,228,225)
    COLOR_DEF(MOCCASIN, 0xFFE4B5);                // rgb(255,228,181)
    COLOR_DEF(NAVAJO_WHITE, 0xFFDEAD);            // rgb(255,222,173)
    COLOR_DEF(NAVY, 0x000080);                    // rgb(0,0,128)
    COLOR_DEF(OLD_LACE, 0xFDF5E6);                // rgb(253,245,230)
    COLOR_DEF(OLIVE, 0x808000);                   // rgb(128,128,0)
    COLOR_DEF(OLIVE_DRAB, 0x6B8E23);              // rgb(107,142,35)
    COLOR_DEF(ORANGE, 0xFFA500);                  // rgb(255,165,0)
    COLOR_DEF(ORANGE_RED, 0xFF4500);              // rgb(255,69,0)
    COLOR_DEF(ORCHID, 0xDA70D6);                  // rgb(218,112,214)
    COLOR_DEF(PALE_GOLDEN_ROD, 0xEEE8AA);         // rgb(238,232,170)
    COLOR_DEF(PALE_GREEN, 0x98FB98);              // rgb(152,251,152)
    COLOR_DEF(PALE_TURQUOISE, 0xAFEEEE);          // rgb(175,238,238)
    COLOR_DEF(PALE_VIOLET_RED, 0xDB7093);         // rgb(219,112,147)
    COLOR_DEF(PAPAYA_WHIP, 0xFFEFD5);             // rgb(255,239,213)
    COLOR_DEF(PEACH_PUFF, 0xFFDAB9);              // rgb(255,218,185)
    COLOR_DEF(PERU, 0xCD853F);                    // rgb(205,133,63)
    COLOR_DEF(PINK, 0xFFC0CB);                    // rgb(255,192,203)
    COLOR_DEF(PLUM, 0xDDA0DD);                    // rgb(221,160,221)
    COLOR_DEF(POWDER_BLUE, 0xB0E0E6);             // rgb(176,224,230)
    COLOR_DEF(PURPLE, 0x800080);                  // rgb(128,0,128)
    COLOR_DEF(REBECCA_PURPLE, 0x663399);          // rgb(102,51,153)
    COLOR_DEF(RED, 0xFF0000);                     // rgb(255,0,0)
    COLOR_DEF(ROSY_BROWN, 0xBC8F8F);              // rgb(188,143,143)
    COLOR_DEF(ROYAL_BLUE, 0x4169E1);              // rgb(65,105,225)
    COLOR_DEF(SADDLE_BROWN, 0x8B4513);            // rgb(139,69,19)
    COLOR_DEF(SALMON, 0xFA8072);                  // rgb(250,128,114)
    COLOR_DEF(SANDY_BROWN, 0xF4A460);             // rgb(244,164,96)
    COLOR_DEF(SEA_GREEN, 0x2E8B57);               // rgb(46,139,87)
    COLOR_DEF(SEA_SHELL, 0xFFF5EE);               // rgb(255,245,238)
    COLOR_DEF(SIENNA, 0xA0522D);                  // rgb(160,82,45)
    COLOR_DEF(SILVER, 0xC0C0C0);                  // rgb(192,192,192)
    COLOR_DEF(SKY_BLUE, 0x87CEEB);                // rgb(135,206,235)
    COLOR_DEF(SLATE_BLUE, 0x6A5ACD);              // rgb(106,90,205)
    COLOR_DEF(SLATE_GRAY, 0x708090);              // rgb(112,128,144)
    COLOR_DEF(SNOW, 0xFFFAFA);                    // rgb(255,250,250)
    COLOR_DEF(SPRING_GREEN, 0x00FF7F);            // rgb(0,255,127)
    COLOR_DEF(STEEL_BLUE, 0x4682B4);              // rgb(70,130,180)
    COLOR_DEF(TAN, 0xD2B48C);                     // rgb(210,180,140)
    COLOR_DEF(TEAL, 0x008080);                    // rgb(0,128,128)
    COLOR_DEF(THISTLE, 0xD8BFD8);                 // rgb(216,191,216)
    COLOR_DEF(TOMATO, 0xFF6347);                  // rgb(255,99,71)
    COLOR_DEF(TURQUOISE, 0x40E0D0);               // rgb(64,224,208)
    COLOR_DEF(VIOLET, 0xEE82EE);                  // rgb(238,130,238)
    COLOR_DEF(WHEAT, 0xF5DEB3);                   // rgb(245,222,179)
    COLOR_DEF(WHITE, 0xFFFFFF);                   // rgb(255,255,255)
    COLOR_DEF(WHITE_SMOKE, 0xF5F5F5);             // rgb(245,245,245)
    COLOR_DEF(YELLOW, 0xFFFF00);                  // rgb(255,255,0)
    COLOR_DEF(YELLOW_GREEN, 0x9ACD32);            // rgb(154,205,50)
#undef COLOR_DEF
} // namespace tricolor

inline tricolor::Color operator+(uint8_t lhs, tricolor::Color rhs) {
    return rhs + lhs;
}

inline tricolor::Color operator-(uint8_t lhs, tricolor::Color rhs) {
    return tricolor::Color(
        tricolor::saturating_sub(lhs, rhs.r),
        tricolor::saturating_sub(lhs, rhs.g),
        tricolor::saturating_sub(lhs, rhs.b)
    );
}

inline tricolor::Color operator*(uint8_t lhs, tricolor::Color rhs) {
    return rhs * lhs;
}

inline tricolor::Color operator*(float lhs, tricolor::Color rhs) {
    return rhs * lhs;
}
