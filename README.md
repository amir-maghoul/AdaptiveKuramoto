# AdaptiveKuramoto
This project uses Eigen (https://eigen.tuxfamily.org/index.php?title=Main_Page) template library for linear algebra

The following naming convention is used throughout the project:
* `lower_case` is used for scalar values
* `CamelCase` is used for class objects/references
* `UPPER_CASE` is used for vector values
* `pCamelCase` is used for smart pointers to objects

** How to prepare the library for personal usage **

1. Download the Eigen header library in a folder named "Eigen" in the project directory
2. Link the Eigen library to the project. This can be done by adding the following commands to the projects CMakeLists.txt:
```
set(EIGEN3_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/<path-to-Eigen-directory-in-project-tree>/" )
add_library(Eigen INTERFACE)
target_link_libraries(Eigen INTERFACE ${EIGEN3_INCLUDE_DIR})

add_executable(<main-project-name>)
target_sources(<main-project-name> PUBLIC "<main-source>.cpp")
target_link_libraries(main ${EIGEN3_INCLUDE_DIR} <other-linked-libraries>)

```
3. Take the similar steps as last step to link `matplotlibcpp.h` to the project.
4. Build the project using `cmake`. If the "build" subdirectory does not exist, create one and then use:
```
$ cd build
$ cmake ..
$ cd ..
```
After first time doing so, you can compile and run the project by
```
$ cmake --build build
$ ./build/main
```
