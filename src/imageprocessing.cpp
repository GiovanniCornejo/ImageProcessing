#include "imageprocessing.h"

Image multiply(const Image &foreground, const Image &background)
{
    Image result = foreground;

    for (int i = 0; i < foreground.pixels.size(); ++i)
    {
        const Pixel &currTop = foreground.pixels[i];
        const Pixel &currBottom = background.pixels[i];

        // Pixel-wise multiplication (cast to double to prevent overflow)
        double r_mult = static_cast<double>(currTop.r) * currBottom.r;
        double g_mult = static_cast<double>(currTop.g) * currBottom.g;
        double b_mult = static_cast<double>(currTop.b) * currBottom.b;

        // Normalize values (add 0.5 to fix rounding issues)
        result.pixels[i].update(
            static_cast<unsigned char>(r_mult / 0xFF + 0.5),
            static_cast<unsigned char>(g_mult / 0xFF + 0.5),
            static_cast<unsigned char>(b_mult / 0xFF + 0.5));
    }

    return result;
}

Image subtract(const Image &topLayer, const Image &bottomLayer)
{
    Image image = topLayer;

    for (int i = 0; i < topLayer.pixels.size(); ++i)
    {
        const Pixel &currTop = topLayer.pixels[i];
        const Pixel &currBottom = bottomLayer.pixels[i];

        // Pixel-wise subtraction, (clamp to 0 to prevent underflow)
        unsigned char r_sub = (currBottom.r < currTop.r) ? 0 : currBottom.r - currTop.r;
        unsigned char g_sub = (currBottom.g < currTop.g) ? 0 : currBottom.g - currTop.g;
        unsigned char b_sub = (currBottom.b < currTop.b) ? 0 : currBottom.b - currTop.b;

        image.pixels[i].update(r_sub, g_sub, b_sub);
    }

    return image;
}

/**
 * @brief The opposite of multiply. Fore- and background are >>negatively multiplied<<
 * @note C = 1 - (1-A)*(1-B)
 * @param topLayer The top layer image
 * @param bottomLayer The bottom layer image
 * @return Image
 */
Image Screen(Image &topLayer, Image &bottomLayer)
{
    Image image = topLayer;
    for (int i = 0; i < topLayer.pixels.size(); ++i)
    {
        // Get current pixels
        Pixel currTop = topLayer.pixels.at(i);
        Pixel currBottom = bottomLayer.pixels.at(i);

        // Negatively multiply values, first convert to doubles to prevent overflow of unsigned char
        double r_mult = (double)(0xFF - currTop.r) * (0xFF - currBottom.r);
        double g_mult = (double)(0xFF - currTop.g) * (0xFF - currBottom.g);
        double b_mult = (double)(0xFF - currTop.b) * (0xFF - currBottom.b);

        // Normalize values by dividing by max unsigned char value (0xFF) and add 0.5f to fix rounding issues
        image.pixels.at(i).update(0xFF - (r_mult / 0xFF) + 0.5f, 0xFF - (g_mult / 0xFF) + 0.5f, 0xFF - (b_mult / 0xFF) + 0.5f);
    }

    return image;
}

/**
 * @brief A combination of the modes Multiply and Screen. If the background is darker than 50% gray,
 * the tonal values get multiplied, otherwise they get >>screened<<. Afterwards they are
 * doubled in both cases
 * @note B ≤ 0.5: C = 2*A*B, B > 0.5: C = 1 - 2*(1-A)*(1-B)
 * @param topLayer
 * @param bottomLayer
 * @return Image
 */
Image Overlay(Image &topLayer, Image &bottomLayer)
{
    Image image = topLayer;
    for (int i = 0; i < topLayer.pixels.size(); ++i)
    {
        // Get current pixels
        Pixel currTop = topLayer.pixels.at(i);
        Pixel currBottom = bottomLayer.pixels.at(i);

        // Get background check values
        double r_check = (double)currBottom.r;
        double g_check = (double)currBottom.g;
        double b_check = (double)currBottom.b;

        // Perform multiply or screen depending on background, account for overflow by using doubles and add 0.5f to final result to fix rounding issues
        //                    If background ≤ 50%:                Multiply                      :                             Screen
        double r_overlay = (r_check / 0xFF <= 0.5f) ? ((2 * currTop.r * r_check) / 0xFF) + 0.5f : 0xFF - (2 * (0xFF - currTop.r) * (0xFF - r_check) / 0xFF) + 0.5f;
        double g_overlay = (g_check / 0xFF <= 0.5f) ? ((2 * currTop.g * g_check) / 0xFF) + 0.5f : 0xFF - (2 * (0xFF - currTop.g) * (0xFF - g_check) / 0xFF) + 0.5f;
        double b_overlay = (b_check / 0xFF <= 0.5f) ? ((2 * currTop.b * b_check) / 0xFF) + 0.5f : 0xFF - (2 * (0xFF - currTop.b) * (0xFF - b_check) / 0xFF) + 0.5f;
        image.pixels.at(i).update(r_overlay, g_overlay, b_overlay);
    }

    return image;
}

/**
 * @brief Common mathematical addition. Add to the top layer the passed in values
 *
 * @param topLayer The top layer image
 * @param r The red channel value
 * @param g The green channel value
 * @param b The blue channel value
 * @return Image
 */
Image Add(Image &topLayer, double r, double g, double b)
{
    Image image = topLayer;
    for (int i = 0; i < topLayer.pixels.size(); ++i)
    {
        // Get current pixels
        Pixel currTop = topLayer.pixels.at(i);

        // Add values, if overflow occurs clamp to 255 (sum > 255)
        unsigned char r_add = (0xFF - r < currTop.r) ? 0xFF : r + currTop.r;
        unsigned char g_add = (0xFF - g < currTop.g) ? 0xFF : g + currTop.g;
        unsigned char b_add = (0xFF - b < currTop.b) ? 0xFF : b + currTop.b;
        image.pixels.at(i).update(r_add, g_add, b_add);
    }

    return image;
}

/**
 * @brief Common mathematical multiplication. Multipliy the top layer by the passed in values
 *
 * @param topLayer The top layer image
 * @param r The red channel value
 * @param g The green channel value
 * @param b The blue channel value
 * @return Image
 */
Image Scale(Image &topLayer, double r, double g, double b)
{
    Image image = topLayer;
    for (int i = 0; i < topLayer.pixels.size(); ++i)
    {
        // Get current pixels
        Pixel currTop = topLayer.pixels.at(i);

        // Multiply values, if overflow occurs clamp to 255 (product > 255)
        unsigned char r_mult = (currTop.r * r > 0xFF) ? 0xFF : currTop.r * r;
        unsigned char g_mult = (currTop.g * g > 0xFF) ? 0xFF : currTop.g * g;
        unsigned char b_mult = (currTop.b * b > 0xFF) ? 0xFF : currTop.b * b;
        image.pixels.at(i).update(r_mult, g_mult, b_mult);
    }

    return image;
}

/**
 * @brief Extract the red channel from an image
 *
 * @param topLayer The top layer image
 * @return Image
 */
Image ColorRed(Image &topLayer)
{
    Image image = topLayer;
    for (int i = 0; i < topLayer.pixels.size(); ++i)
    {
        Pixel currTop = topLayer.pixels.at(i);
        image.pixels.at(i).update(currTop.r, currTop.r, currTop.r);
    }

    return image;
}

/**
 * @brief Extract the blue channel from an image
 *
 * @param topLayer The top layer image
 * @return Image
 */
Image ColorGreen(Image &topLayer)
{
    Image image = topLayer;
    for (int i = 0; i < topLayer.pixels.size(); ++i)
    {
        Pixel currTop = topLayer.pixels.at(i);
        image.pixels.at(i).update(currTop.g, currTop.g, currTop.g);
    }

    return image;
}

/**
 * @brief Extract the green channel from an image
 *
 * @param topLayer The top layer image
 * @return Image
 */
Image ColorBlue(Image &topLayer)
{
    Image image = topLayer;
    for (int i = 0; i < topLayer.pixels.size(); ++i)
    {
        Pixel currTop = topLayer.pixels.at(i);
        image.pixels.at(i).update(currTop.b, currTop.b, currTop.b);
    }

    return image;
}

/**
 * @brief Combine three R, G, and B channel images into one
 *
 * @param red The red channel image
 * @param green The green channel image
 * @param blue The blue channel image
 * @return Image
 */
Image Combine(Image &red, Image &green, Image &blue)
{
    Image image = red;
    for (int i = 0; i < red.pixels.size(); ++i)
        image.pixels.at(i).update(red.pixels.at(i).r, green.pixels.at(i).g, blue.pixels.at(i).b);
    return image;
}

/**
 * @brief Rotate an image by 180 degrees
 *
 * @param topLayer The top layer image
 * @return Image
 */
Image Rotate(Image &topLayer)
{
    Image image = topLayer;
    for (int i = topLayer.pixels.size() - 1; i >= 0; i--)
    {
        // Get current pixels
        Pixel currTop = topLayer.pixels.at(i);

        // Store pixels backwards (bottom right corner [begin] becomes top left corner [end])
        image.pixels.at(image.pixels.size() - 1 - i) = currTop;
    }

    return image;
}

/**
 * @brief Combines four images into one where each is a quadrant in the final image
 * @note All images have the same size (width and height)
 * @param first The first quadrant image (top left)
 * @param second The second quadrant image (top right)
 * @param third The third quadrant image (bottom right)
 * @param fourth The fourth quadrant image (bottom left)
 * @return Image
 */
Image CombineQuadrants(Image &first, Image &second, Image &third, Image &fourth)
{
    Image image = first;

    // Update size of image in header and clear the pixels
    image.header.width *= 2;
    image.header.height *= 2;
    image.pixels.clear();

    // Traverse the width of the image (i == column)
    for (int i = 0; i < image.header.width; ++i)
    {
        // Traverse half the height of the image (j == row)
        for (int j = 0; j < image.header.height; j++)
        {
            // If adding fourth quadrant (row is safe, column is safe)
            if (i < image.header.width / 2 && j < image.header.height / 2)
                image.pixels.push_back(fourth.pixels.at(j + i * (image.header.width / 2)));
            // If adding first quadrant (row is safe, column must be subtracted for correct access)
            else if (i >= image.header.width / 2 && j < image.header.height / 2)
                image.pixels.push_back(first.pixels.at(j + (i - image.header.width / 2) * (image.header.width / 2)));
            // If adding second quadrant (row and column must be subtracted for correct access)
            else if (i >= image.header.width / 2 && j >= image.header.height / 2)
                image.pixels.push_back(second.pixels.at((j - image.header.height / 2) + (i - image.header.width / 2) * (image.header.width / 2)));
            // If adding third quadrant (row must be subtracted for correct access, column is safe)
            else
                image.pixels.push_back(third.pixels.at((j - image.header.height / 2) + i * (image.header.width / 2)));
        }
    }

    return image;
}
