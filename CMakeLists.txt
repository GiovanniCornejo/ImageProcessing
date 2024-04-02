# Specify minimum version of cmake
cmake_minimum_required(VERSION 3.5)

# Add project
project(ImageProcessing
        VERSION 1.0.0
        DESCRIPTION "Image processing"
        LANGUAGES CXX)

# CREATE AN EXECUTABLE #
add_executable(ImageProcessing src/main.cpp src/image.cpp src/pixel.cpp src/imageprocessing.cpp)

# Add include files
target_include_directories(ImageProcessing PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Set compilation features for the project
target_compile_features(ImageProcessing PRIVATE cxx_std_17)