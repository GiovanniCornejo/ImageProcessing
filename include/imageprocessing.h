#pragma once

#include "image.h"

/// @brief Multiply the standardized (based on the domain 0...1) tonal values
///        of the fore- and background's pixels.
/// @note The effect can be compared to two slides put on top of each other and projected together.
///       The light, forced to pass through each of the slides, is weakened twice.
/// @param foreground The foreground image.
/// @param background The background image.
/// @return The multiplied image.
Image multiply(const Image &foreground, const Image &background);

/// @brief Subtracts the top layer from the bottom layer.
/// @param topLayer The top layer image.
/// @param bottomLayer The bottom layer image.
/// @return The subtracted image.
Image subtract(const Image &topLayer, const Image &bottomLayer);

Image Screen(Image &topLayer, Image &bottomLayer);
Image Overlay(Image &topLayer, Image &bottomLayer);

Image Add(Image &topLayer, double r = 1.0, double g = 1.0, double b = 1.0);
Image Scale(Image &topLayer, double r = 1.0, double g = 1.0, double b = 1.0);

Image ColorRed(Image &topLayer);
Image ColorGreen(Image &topLayer);
Image ColorBlue(Image &topLayer);
Image Combine(Image &red, Image &green, Image &blue);

Image Rotate(Image &topLayer);
Image CombineQuadrants(Image &first, Image &second, Image &third, Image &fourth);