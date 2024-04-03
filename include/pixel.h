#ifndef PIXEL_H
#define PIXEL_H

/// @brief Represents the RGB values of a single pixel in an image.
struct Pixel
{
    unsigned char r, g, b;

    /// @brief Constructs a Pixel object from the provided RGB values.
    /// @param red The red byte value.
    /// @param green The green byte value.
    /// @param blue The blue byte value.
    Pixel(unsigned char red = 0, unsigned char green = 0, unsigned char blue = 0);

    /// @brief Updates the RGB values for the pixel.
    /// @param red The red byte value.
    /// @param green The green byte value.
    /// @param blue The blue byte value.
    void update(unsigned char red, unsigned char green, unsigned char blue);

    /// @return `true` if two pixels do not share the same RGB values; otherwise `false`.
    bool operator!=(const Pixel &rhs);
};

#endif