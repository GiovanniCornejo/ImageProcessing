#pragma once

#include "image.h"

/* Image Manipulate from Image */

Image Multiply(Image& topLayer, Image& bottomLayer);
Image Subtract(Image& topLayer, Image& bottomLayer);
Image Screen(Image& topLayer, Image& bottomLayer);
Image Overlay(Image& topLayer, Image& bottomLayer);

/* Image Manipulate from Variables */

Image Add(Image& topLayer, double r=1.0, double g=1.0, double b=1.0);
Image Scale(Image& topLayer, double r=1.0, double g=1.0, double b=1.0);

/* Image Accessors and Setters */

Image ColorRed(Image& topLayer);
Image ColorGreen(Image& topLayer);
Image ColorBlue(Image& topLayer);
Image Combine(Image& red, Image& green, Image& blue);

/* Misc */

Image Rotate(Image& topLayer);

Image CombineQuadrants(Image& first, Image& second, Image& third, Image& fourth);