#pragma once

/// @brief Header [18 bytes in length] which
/// stores pieces of information describing the image content
struct Header
{
    char idLength; // Size of the Image ID field [1 byte]
    char colorMapType; // If color map included [1 byte]
    char dataTypeCode; // Copmressed, True Color, Grayscale [1 byte]
    short colorMapOrigin; // Origin of color map [2 bytes]
    short colorMapLength; // Length of color map [2 bytes]
    char colorMapDepth; // Depth of color map [1 byte]
    short xOrigin; // Image x origin [2 bytes]
    short yOrigin; // Image y origin [2 bytes]
    short width; // Image Width [2 bytes]
    short height; // Image Height [2 bytes]
    char bitsPerPixel; // Pixel depth - typically 8, 16, 24, or 32 [1 byte]
    char imageDescriptor; // Image Descriptor [1 byte]
};