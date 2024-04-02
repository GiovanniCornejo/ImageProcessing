#include "pixel.h"

/**
 * @brief Construct a new Pixel:: Pixel object
 * 
 * @param r The r value
 * @param g The g value
 * @param b The b value
 */
Pixel::Pixel(unsigned char r, unsigned char g, unsigned char b)
{
    this->r = r;
    this->g = g;
    this->b = b;
}

/// @brief Update the RGB values for the pixel
/// @param r The r value
/// @param g The g value
/// @param b The b value
void Pixel::update(unsigned char r, unsigned char g, unsigned char b)
{
    this->r = r;
	this->g = g;
	this->b = b;
}

/// @brief Inequality operator to compare two pixels
/// @param rhs The righthand side pixel
/// @return True if both pixels have the same RGB values, false otherwise
bool Pixel::operator!=(const Pixel& rhs)
{
    return (this->r != rhs.r || this->g != rhs.g || this->b != rhs.b) ? true : false;
}