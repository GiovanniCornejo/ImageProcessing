# ImageProcessing

## Description

A C++ project for processing images.

- Read in a number .TGA files in a binary format
- Process the image data store within those files in a variety of ways
- Write out new .TGA files in the same binary format

## Dependencies

- CMake (minimum version 3.5)

## Installation

1. Clone the repository:
   ```bash
   git clone https://github.com/GiovanniCornejo/ImageProcessing.git
   cd ImageProcessing
   ```
2. Create an output directory to hold the output image files:
   ```bash
   mkdir data/output
   ```
3. Create a build directory to hold the project:
   ```bash
   mkdir build
   cd build
   ```
4. Generate the build files using CMake and compile:
   ```bash
   cmake ..
   make
   ```
5. Run the executable to test:
   ```bash
   ./ImageProcessing.exe
   ```

## License

This project is licensed under the [MIT License](LICENSE).
