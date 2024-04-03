#include "imageprocessing.h"

Image multiplyMode(const Image &foreground, const Image &background)
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

Image screenMode(const Image &foreground, const Image &background)
{
    Image result = foreground;

    for (int i = 0; i < foreground.pixels.size(); ++i)
    {
        const Pixel &currTop = foreground.pixels[i];
        const Pixel &currBottom = background.pixels[i];

        // Pixel-wise negative multiplication (cast to double to prevent overflow)
        double r_mult = static_cast<double>(0xFF - currTop.r) * (0xFF - currBottom.r);
        double g_mult = static_cast<double>(0xFF - currTop.g) * (0xFF - currBottom.g);
        double b_mult = static_cast<double>(0xFF - currTop.b) * (0xFF - currBottom.b);

        // Normalize values (add 0.5 to fix rounding issues)
        result.pixels[i].update(
            static_cast<unsigned char>(0xFF - r_mult / 0xFF + 0.5),
            static_cast<unsigned char>(0xFF - g_mult / 0xFF + 0.5),
            static_cast<unsigned char>(0xFF - b_mult / 0xFF + 0.5));
    }

    return result;
}

Image overlayMode(const Image &foreground, const Image &background)
{
    Image result = foreground;

    // Lambda function for pixel-wise multiplication
    auto multiply = [](unsigned char a, double b)
    {
        return (2 * a * b) / 0xFF + 0.5;
    };

    // Lambda function for pixel-wise screen
    auto screen = [](unsigned char a, double b)
    {
        return 0xFF - (2 * (0xFF - a) * (0xFF - b) / 0xFF) + 0.5;
    };

    for (int i = 0; i < foreground.pixels.size(); ++i)
    {
        const Pixel &currTop = foreground.pixels[i];
        const Pixel &currBottom = background.pixels[i];

        // Get background color components to determine mode applied (cast to double to prevent overflow)
        double r_back = static_cast<double>(currBottom.r);
        double g_back = static_cast<double>(currBottom.g);
        double b_back = static_cast<double>(currBottom.b);

        // Pixel-wise multiplication/screen and normalization
        double r_overlay = (r_back / 0xFF <= 0.5f) ? multiply(currTop.r, r_back) : screen(currTop.r, r_back);
        double g_overlay = (g_back / 0xFF <= 0.5f) ? multiply(currTop.g, g_back) : screen(currTop.g, g_back);
        double b_overlay = (b_back / 0xFF <= 0.5f) ? multiply(currTop.b, b_back) : screen(currTop.b, b_back);

        result.pixels[i].update(r_overlay, g_overlay, b_overlay);
    }

    return result;
}

Image subtractMode(const Image &topLayer, const Image &bottomLayer)
{
    Image result = topLayer;

    for (int i = 0; i < topLayer.pixels.size(); ++i)
    {
        const Pixel &currTop = topLayer.pixels[i];
        const Pixel &currBottom = bottomLayer.pixels[i];

        // Pixel-wise subtraction (clamp to 0 to prevent underflow)
        unsigned char r_sub = (currBottom.r < currTop.r) ? 0 : currBottom.r - currTop.r;
        unsigned char g_sub = (currBottom.g < currTop.g) ? 0 : currBottom.g - currTop.g;
        unsigned char b_sub = (currBottom.b < currTop.b) ? 0 : currBottom.b - currTop.b;

        result.pixels[i].update(r_sub, g_sub, b_sub);
    }

    return result;
}

Image add(const Image &image, double r, double g, double b)
{
    Image result = image;

    for (int i = 0; i < image.pixels.size(); ++i)
    {
        const Pixel &currTop = image.pixels[i];

        // Pixel-wise addition (clamp to 255 to prevent overflow)
        unsigned char r_add = (0xFF - r < currTop.r) ? 0xFF : r + currTop.r;
        unsigned char g_add = (0xFF - g < currTop.g) ? 0xFF : g + currTop.g;
        unsigned char b_add = (0xFF - b < currTop.b) ? 0xFF : b + currTop.b;

        result.pixels[i].update(r_add, g_add, b_add);
    }

    return result;
}

Image scale(const Image &image, double r, double g, double b)
{
    Image result = image;

    for (int i = 0; i < image.pixels.size(); ++i)
    {
        const Pixel &currTop = image.pixels[i];

        // Pixel-wise scaling (clamp to 255 to prevent overflow)
        unsigned char r_scale = (currTop.r * r > 0xFF) ? 0xFF : currTop.r * r;
        unsigned char g_scale = (currTop.g * g > 0xFF) ? 0xFF : currTop.g * g;
        unsigned char b_scale = (currTop.b * b > 0xFF) ? 0xFF : currTop.b * b;

        result.pixels[i].update(r_scale, g_scale, b_scale);
    }

    return result;
}

Image extractRed(const Image &image)
{
    Image result = image;
    for (int i = 0; i < image.pixels.size(); ++i)
    {
        const Pixel &currTop = image.pixels[i];
        result.pixels[i].update(currTop.r, currTop.r, currTop.r);
    }

    return result;
}

Image extractGreen(const Image &image)
{
    Image result = image;
    for (int i = 0; i < image.pixels.size(); ++i)
    {
        const Pixel &currTop = image.pixels[i];
        result.pixels[i].update(currTop.g, currTop.g, currTop.g);
    }

    return result;
}

Image extractBlue(const Image &image)
{
    Image result = image;
    for (int i = 0; i < image.pixels.size(); ++i)
    {
        const Pixel &currTop = image.pixels[i];
        result.pixels[i].update(currTop.b, currTop.b, currTop.b);
    }

    return result;
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
