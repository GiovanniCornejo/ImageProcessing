#ifndef IMAGE_H
#define IMAGE_H

#include <vector>
#include <string>

#include "header.h"
#include "pixel.h"

/// @brief Manages the header and pixel data of an image.
struct Image
{
    Header header;             // The header data for the image
    std::vector<Pixel> pixels; // The pixels in the image

    /// @brief Constructs an Image object from from a .vga image file.
    /// @param file The path to the .vga file to read an image from.
    Image(const std::string &file);

    /// @brief Write an image to a .vga file.
    /// @param file The path to the .vga file to write an image to.
    void write(const std::string &file);
};

#endif // IMAGE_H