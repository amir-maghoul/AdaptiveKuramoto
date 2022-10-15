# AdaptiveKuramoto
This project uses Eigen (https://eigen.tuxfamily.org/index.php?title=Main_Page) template library for linear algebra

The following naming convention is used throughout the project:
* `lower_case` is used for scalar values
* `CamelCase` is used for class objects/references
* `UPPER_CASE` is used for vector values
* `pCamelCase` is used for smart pointers to objects

** How to use the code **
1. Download the Eigen header library in a folder named "Eigen" in the project directory
2. Create a CMakeList.txt file in the Eigen directory
3. Link the Eigen library to the project by adding `AUX_SOURCE_DIRECTORY(${PROJECT_SOURCE_DIR}Eigen CTR_SOURCES)` or something similar to the CMakeLists.txt of the Eigen subfolder.
4. Build the project using `cmake`. If the "build" subdirectory does not exist, create one and then use:
```
>>> cd build
>>> cmake ..
>>> cd ..
```
After first time doing so, you can compile and run the project by
```
>>> cmake --build build
>>> ./build/main
```