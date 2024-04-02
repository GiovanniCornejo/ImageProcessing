#include "image.h"

/**
 * @brief Construct a new Image:: Image object
 * 
 * @param filename The .vga file name to read an image from
 */
Image::Image(std::string filename)
{
    // Open file
    std::ifstream imageFile(filename, std::ios_base::binary);

    // Check if file is open
    if (!imageFile.is_open())
        throw std::runtime_error("File \"" + filename + "\" not found\n");

    // Read in header data
    imageFile.read(&this->header.idLength, sizeof(char));
    imageFile.read(&this->header.colorMapType, sizeof(char));
    imageFile.read(&this->header.dataTypeCode, sizeof(char));
    imageFile.read((char*) &this->header.colorMapOrigin, sizeof(short));
    imageFile.read((char*) &this->header.colorMapLength, sizeof(short));
    imageFile.read(&this->header.colorMapDepth, sizeof(char));
    imageFile.read((char*) &this->header.xOrigin, sizeof(short));
    imageFile.read((char*) &this->header.yOrigin, sizeof(short));
    imageFile.read((char*) &this->header.width, sizeof(short));
    imageFile.read((char*) &this->header.height, sizeof(short));
    imageFile.read(&this->header.bitsPerPixel, sizeof(char));
    imageFile.read(&this->header.imageDescriptor, sizeof(char));

    // Read in RGB pixel data (.tga files store this in reverse order)
    int size = this->header.height * this->header.width;
    unsigned char r, g, b;
    for(int i = 0; i< size; i++)
    {
        imageFile.read((char*) &b, sizeof(unsigned char));
        imageFile.read((char*) &g, sizeof(unsigned char));
        imageFile.read((char*) &r, sizeof(unsigned char));
        this->pixels.push_back(Pixel(r, g, b));
    }

    // Close file
    imageFile.close();
}

/// @brief Write an image to a file
/// @param filename The .vga file name to write an image to
void Image::output(std::string filename)
{
    // Open file
    std::ofstream imageFile(filename, std::ios_base::binary);

    // Check if file is open
    if (!imageFile.is_open())
        throw std::runtime_error("File \"" + filename + "\" not found\n");


    // Write out header data
    imageFile.write(&this->header.idLength, sizeof(char));
    imageFile.write(&this->header.colorMapType, sizeof(char));
    imageFile.write(&this->header.dataTypeCode, sizeof(char));
    imageFile.write((char*) &this->header.colorMapOrigin, sizeof(short));
    imageFile.write((char*) &this->header.colorMapLength, sizeof(short));
    imageFile.write(&this->header.colorMapDepth, sizeof(char));
    imageFile.write((char*) &this->header.xOrigin, sizeof(short));
    imageFile.write((char*) &this->header.yOrigin, sizeof(short));
    imageFile.write((char*) &this->header.width, sizeof(short));
    imageFile.write((char*) &this->header.height, sizeof(short));
    imageFile.write(&this->header.bitsPerPixel, sizeof(char));
    imageFile.write(&this->header.imageDescriptor, sizeof(char));

    // Write out RGB pixel data (.tga files store this in reverse order)
    for(Pixel p : this->pixels)
    {
        imageFile.write((char*) &p.b, sizeof(unsigned char));
        imageFile.write((char*) &p.g, sizeof(unsigned char));
        imageFile.write((char*) &p.r, sizeof(unsigned char));
    }

    // Close file
    imageFile.close();
}