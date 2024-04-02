#pragma once

/// @brief Pixel [3 bytes in length] which
/// stores the red, green, and blue values of an RGB color
struct Pixel
{
    unsigned char r, g, b;
    Pixel(unsigned char r=0, unsigned char g=0, unsigned char b=0);
    void update(unsigned char r, unsigned char g, unsigned char b);

    bool operator!=(const Pixel& rhs);
};