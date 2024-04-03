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
    // Note: The Pixel class has the same order of bytes (BGR) as the .tga file
    int size = header.height * header.width;
    pixels.resize(size);
    imageFile.read(reinterpret_cast<char *>(pixels.data()), size * sizeof(Pixel));
}

void Image::write(const std::string &file)
{
    std::ofstream imageFile(file, std::ios_base::binary);
    if (!imageFile.is_open())
        throw std::runtime_error("ERROR: File \"" + file + "\" not found.");

    // Write image header information field by field
    imageFile.write(&header.idLength, sizeof(header.idLength));
    imageFile.write(&header.colorMapType, sizeof(header.colorMapType));
    imageFile.write(&header.dataTypeCode, sizeof(header.dataTypeCode));
    imageFile.write(reinterpret_cast<const char *>(&header.colorMapOrigin), sizeof(header.colorMapOrigin));
    imageFile.write(reinterpret_cast<const char *>(&header.colorMapLength), sizeof(header.colorMapLength));
    imageFile.write(&header.colorMapDepth, sizeof(header.colorMapDepth));
    imageFile.write(reinterpret_cast<const char *>(&header.xOrigin), sizeof(header.xOrigin));
    imageFile.write(reinterpret_cast<const char *>(&header.yOrigin), sizeof(header.yOrigin));
    imageFile.write(reinterpret_cast<const char *>(&header.width), sizeof(header.width));
    imageFile.write(reinterpret_cast<const char *>(&header.height), sizeof(header.height));
    imageFile.write(&header.bitsPerPixel, sizeof(header.bitsPerPixel));
    imageFile.write(&header.imageDescriptor, sizeof(header.imageDescriptor));

    // Write pixels
    imageFile.write(reinterpret_cast<const char *>(pixels.data()), pixels.size() * sizeof(Pixel));
}