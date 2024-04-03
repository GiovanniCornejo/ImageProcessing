#include "pixel.h"

Pixel::Pixel(unsigned char red, unsigned char green, unsigned char blue) : r{red}, g{green}, b{blue} {}

void Pixel::update(unsigned char red, unsigned char green, unsigned char blue)
{
    r = red;
    g = green;
    b = blue;
}

bool Pixel::operator!=(const Pixel &rhs)
{
    return (r != rhs.r || g != rhs.g || b != rhs.b);
}