#pragma once

#include "image.h"

/// @brief Multiply the standardized (based on the domain 0...1) tonal values
///        of the fore- and background's pixels.
/// @note The effect can be compared to two slides put on top of each other and projected together.
///       The light, forced to pass through each of the slides, is weakened twice.
/// @param foreground The foreground image.
/// @param background The background image.
/// @return The multiplied image.
Image multiplyMode(const Image &foreground, const Image &background);

/// @brief The opposite of multiply. Fore- and background are negatively multiplied
///        and lighten each other.
/// @note  The effect can be compared to two slides projected with different projectors onto the same screen.
/// @param foreground The foreground image.
/// @param background The background image.
/// @return The screened image.
Image screenMode(const Image &foreground, const Image &background);

/// @brief A combination of the modes Multiply and Screen, dependent on the background's tonal value.
/// @note If the background is darker than 50% gray, the tonal values get multiplied,
///       otherwise they get screened (and afterwards they are doubled in both cases).
/// @param foreground The foreground image.
/// @param background The background image.
/// @return The overlayed image.
Image overlayMode(const Image &foreground, const Image &background);

/// @brief Subtracts the top layer from the bottom layer.
/// @param topLayer The top layer image.
/// @param bottomLayer The bottom layer image.
/// @return The subtracted image.
Image subtractMode(const Image &topLayer, const Image &bottomLayer);

/// @brief Common mathematical addition. Add to the image the passed in values.
/// @param image The image to add to.
/// @param r The red byte value.
/// @param g The green byte value.
/// @param b The blue byte value.
/// @return The added image.
Image add(const Image &image, double r = 1.0, double g = 1.0, double b = 1.0);

/// @brief Common mathematical multiplication. Scale the image by the passed in values.
/// @param image The image to scale.
/// @param r The red byte value.
/// @param g The green byte value.
/// @param b The blue byte value.
/// @return The scaled image.
Image scale(const Image &image, double r = 1.0, double g = 1.0, double b = 1.0);

/// @brief Extract the red channel from an image.
/// @note Each channel contains the red channel value.
/// @param image The image.
/// @return The red channel image.
Image extractRed(const Image &image);

/// @brief Extract the green channel from an image.
/// @note Each channel contains the green channel value.
/// @param image The image.
/// @return The green channel image.
Image extractGreen(const Image &image);

/// @brief Extract the blue channel from an image.
/// @note Each channel contains the blue channel value.
/// @param image The image.
/// @return The blue channel image.
Image extractBlue(const Image &image);

/// @brief Combine three red, green, and blue channels into one image.
/// @param red The red channel image.
/// @param green The green channel image.
/// @param blue The blue channel image.
/// @return The combined image.
Image combineChannels(const Image &red, const Image &green, const Image &blue);

/// @brief Rotate an image by 180 degrees.
/// @param image The image to rotate.
/// @return The rotated image.
Image rotate180(const Image &image);

/// @brief Combines four images where each is a quadrant in the final image.
/// @param first The first quadrant image (top left).
/// @param second The second quadrant image (top right).
/// @param third The third quadrant image (bottom right).
/// @param fourth The fourth quadrant image (bottom left).
/// @return The combined image.
Image combineQuadrants(const Image &first, const Image &second, const Image &third, const Image &fourth);