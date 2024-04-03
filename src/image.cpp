#include "image.h"

#include <fstream>
#include <string>

Image::Image(const std::string &file)
{
    std::ifstream imageFile{file, std::ios_base::binary};
    if (!imageFile.is_open())
        throw std::runtime_error("ERROR: File \"" + file + "\" not found.");

    // Read in header data (.tga files in little-endian byte order)
    imageFile.read(&header.idLength, sizeof(header.idLength));
    imageFile.read(&header.colorMapType, sizeof(header.colorMapType));
    imageFile.read(&header.dataTypeCode, sizeof(header.dataTypeCode));
    imageFile.read(reinterpret_cast<char *>(&header.colorMapOrigin), sizeof(header.colorMapOrigin));
    imageFile.read(reinterpret_cast<char *>(&header.colorMapLength), sizeof(header.colorMapLength));
    imageFile.read(&header.colorMapDepth, sizeof(header.colorMapDepth));
    imageFile.read(reinterpret_cast<char *>(&header.xOrigin), sizeof(header.xOrigin));
    imageFile.read(reinterpret_cast<char *>(&header.yOrigin), sizeof(header.yOrigin));
    imageFile.read(reinterpret_cast<char *>(&header.width), sizeof(header.width));
    imageFile.read(reinterpret_cast<char *>(&header.height), sizeof(header.height));
    imageFile.read(&header.bitsPerPixel, sizeof(header.bitsPerPixel));
    imageFile.read(&header.imageDescriptor, sizeof(header.imageDescriptor));

    // Read in RGB pixel data
    int size = header.height * header.width;
    pixels.reserve(size);

    unsigned char rgb[3];
    for (int i = 0; i < size; ++i)
    {
        imageFile.read(reinterpret_cast<char *>(rgb), sizeof(rgb));
        pixels.push_back(Pixel{rgb[2], rgb[1], rgb[0]}); // .tga files store RGB bytes in reverse order
    }
}

void Image::write(const std::string &file)
{
    std::ofstream imageFile(file, std::ios_base::binary);
    if (!imageFile.is_open())
        throw std::runtime_error("ERROR: File \"" + file + "\" not found.");

    // Write image header information
    imageFile.write(reinterpret_cast<char *>(&header), sizeof(header));

    // Write pixels
    imageFile.write(reinterpret_cast<const char *>(pixels.data()), pixels.size() * sizeof(Pixel));
}