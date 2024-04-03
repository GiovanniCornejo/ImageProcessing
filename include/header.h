#ifndef HEADER_H
#define HEADER_H

/// @brief TGA file format header which stores pieces of information describing the image content.
struct Header
{
    char idLength;        // Size of the Image ID field
    char colorMapType;    // If color map included
    char dataTypeCode;    // Compressed, True Color, Grayscale
    short colorMapOrigin; // Origin of color map [2 bytes]
    short colorMapLength; // Length of color map [2 bytes]
    char colorMapDepth;   // Depth of color map
    short xOrigin;        // Image x origin [2 bytes]
    short yOrigin;        // Image y origin [2 bytes]
    short width;          // Image Width [2 bytes]
    short height;         // Image Height [2 bytes]
    char bitsPerPixel;    // Pixel depth - typically 8, 16, 24, or 32
    char imageDescriptor; // Image Descriptor
};

#endif