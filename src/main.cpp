#include <iostream>

#include "image.h"
#include "imageprocessing.h"

#define FILE_EXT ".tga"               // Image file extension
#define INPUT_PATH "../data/input/"   // Relative path to input files
#define TEST_PATH "../data/tests/"    // Relative path to test files
#define OUTPUT_PATH "../data/output/" // Relative path to output files

/// @return `true` if the images are identical (all pixel values are the same); `false` otherwise
bool testCase(Image &test, Image &example);

int main()
{
    std::cout << "Loading Files... ";
    Image layer1{INPUT_PATH + std::string{"layer1"} + FILE_EXT};
    Image layer2{INPUT_PATH + std::string{"layer2"} + FILE_EXT};
    Image blue{INPUT_PATH + std::string{"layer_blue"} + FILE_EXT};
    Image green{INPUT_PATH + std::string{"layer_green"} + FILE_EXT};
    Image red{INPUT_PATH + std::string{"layer_red"} + FILE_EXT};
    Image pattern1{INPUT_PATH + std::string{"pattern1"} + FILE_EXT};
    Image pattern2{INPUT_PATH + std::string{"pattern2"} + FILE_EXT};
    Image text1{INPUT_PATH + std::string{"text1"} + FILE_EXT};
    Image text2{INPUT_PATH + std::string{"text2"} + FILE_EXT};
    Image car{INPUT_PATH + std::string{"car"} + FILE_EXT};
    Image circles{INPUT_PATH + std::string{"circles"} + FILE_EXT};
    std::cout << "Done." << std::endl;

    std::cout << "Performing Operations... ";

    // Test 1: Multiply layer1.tga (top) and pattern1.tga (bottom)
    Image output1 = Multiply(layer1, pattern1);
    output1.output(OUTPUT_PATH + std::string{"output1"} + FILE_EXT);

    // Test 2: Subtract layer2.tga (top) with car.tga (bottom)
    Image output2 = Subtract(layer2, car);
    output2.output(OUTPUT_PATH + std::string{"output2"} + FILE_EXT);

    // Test 3: Multiply layer1.tga (top) and pattern2.tga (bottom)
    //         Screen result with text.tga (top)
    Image suboutput3 = Multiply(layer1, pattern2);
    Image output3 = Screen(text1, suboutput3);
    output3.output(OUTPUT_PATH + std::string{"output3"} + FILE_EXT);

    // Test 4: Multiply layer2.tga (top) and circles.tga (bottom)
    //         Subtract result with pattern2.tga (top)
    Image suboutput4 = Multiply(layer2, circles);
    Image output4 = Subtract(pattern2, suboutput4);
    output4.output(OUTPUT_PATH + std::string{"output4"} + FILE_EXT);

    // Test 5: Overlay layer1.tga (top) and pattern1.tga (bottom)
    Image output5 = Overlay(layer1, pattern1);
    output5.output(OUTPUT_PATH + std::string{"output5"} + FILE_EXT);

    // Test 6: Load car.tga and add 200 to the green channel
    Image output6 = Add(car, 0, 200, 0);
    output6.output(OUTPUT_PATH + std::string{"output6"} + FILE_EXT);

    // Test 7: Load car.tga and scale the red channel by 4, the blue channel by 0
    Image output7 = Scale(car, 4, 1, 0);
    output7.output(OUTPUT_PATH + std::string{"output7"} + FILE_EXT);

    // Test 8: Load car.tga and write each channel to a separate file
    Image output8_r = ColorRed(car);
    Image output8_g = ColorGreen(car);
    Image output8_b = ColorBlue(car);
    output8_r.output(OUTPUT_PATH + std::string{"output8_r"} + FILE_EXT);
    output8_g.output(OUTPUT_PATH + std::string{"output8_g"} + FILE_EXT);
    output8_b.output(OUTPUT_PATH + std::string{"output8_b"} + FILE_EXT);

    // Test 9: Combine layer red.tga, green.tga, blue.tga
    Image output9 = Combine(red, green, blue);
    output9.output(OUTPUT_PATH + std::string{"output9"} + FILE_EXT);

    // Test 10: Rotate text2.tga
    Image output10 = Rotate(text2);
    output10.output(OUTPUT_PATH + std::string{"output10"} + FILE_EXT);

    // Test 11: Create a new file that is the combination of car.tga, circles.tga, pattern1.tga, text.tga
    //          Each source image will be in a quadrant of the final image
    Image output11 = CombineQuadrants(car, circles, pattern1, text1);
    output11.output(OUTPUT_PATH + std::string{"output11"} + FILE_EXT);

    std::cout << "Done." << std::endl;

    std::cout << "Loading Test Files... ";
    Image test1(TEST_PATH + std::string{"test1"} + FILE_EXT);
    Image test2(TEST_PATH + std::string{"test2"} + FILE_EXT);
    Image test3(TEST_PATH + std::string{"test3"} + FILE_EXT);
    Image test4(TEST_PATH + std::string{"test4"} + FILE_EXT);
    Image test5(TEST_PATH + std::string{"test5"} + FILE_EXT);
    Image test6(TEST_PATH + std::string{"test6"} + FILE_EXT);
    Image test7(TEST_PATH + std::string{"test7"} + FILE_EXT);
    Image test8_b(TEST_PATH + std::string{"test8_b"} + FILE_EXT);
    Image test8_g(TEST_PATH + std::string{"test8_g"} + FILE_EXT);
    Image test8_r(TEST_PATH + std::string{"test8_r"} + FILE_EXT);
    Image test9(TEST_PATH + std::string{"test9"} + FILE_EXT);
    Image test10(TEST_PATH + std::string{"test10"} + FILE_EXT);
    Image test11(TEST_PATH + std::string{"test11"} + FILE_EXT);

    std::cout << "Done." << std::endl;

    /* ANALYZE TEST CASES */
    std::cout << "\nPerforming Tests... ";
    std::vector<Image> outputs = {output1, output2, output3, output4, output5, output6, output7, output8_b, output8_g, output8_r, output9, output10, output11};
    std::vector<Image> examples = {test1, test2, test3, test4, test5, test6, test7, test8_b, test8_g, test8_r, test9, test10, test11};

    std::string results;
    for (int i = 0; i < outputs.size(); i++)
    {
        bool passed = testCase(outputs[i], examples[i]);
        results += (passed) ? "." : "F";
    }

    std::cout << "Done." << std::endl;
    std::cout << "----------------------------------------" << std::endl;

    if (results.find('F') == std::string::npos)
    {
        std::cout << "All tests passed." << std::endl;
    }
    else
    {
        std::cout << results << std::endl;
        std::cout << "Tests failed." << std::endl;
    }
    return 0;
}

bool testCase(Image &test, Image &example)
{
    for (int i = 0; i < test.pixels.size(); i++)
    {
        if (test.pixels.at(i) != example.pixels.at(i))
        {
            Pixel testPixel = test.pixels.at(i);
            Pixel examplePixel = example.pixels.at(i);
            std::cout << "Error! RGB pixels (" << (int)testPixel.r << ", " << (int)testPixel.g << ", " << (int)testPixel.b << ") != (";
            std::cout << (int)examplePixel.r << ", " << (int)examplePixel.g << ", " << (int)examplePixel.b << ")" << std::endl;
            return false;
        }
    }
    return true;
}