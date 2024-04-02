#pragma once

#include <vector>
#include <string>
#include <fstream>

#include "header.h"
#include "pixel.h"

struct Image
{
    Header header;
    std::vector<Pixel> pixels;

    Image(std::string filename="");
    void output(std::string filename);
};