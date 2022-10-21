cmake_minimum_required(VERSION 3.20)
project(KuramotoModel)

set(PYTHON_HEADERS /usr/include/python3.10 ) # path to header
set(PYTHON_STATIC  /usr/lib64/x86_64-linux-gnu) # path to where windows stores dlls
set(PYTHON_LIBS    /home/amir/.local/lib/python3.10/site-packages/numpy/core/include/numpy)

add_library(pNumpy INTERFACE)
find_package(Python3 COMPONENTS Interpreter Development REQUIRED)
target_link_libraries(pNumpy INTERFACE
  Python3::Python
  Python3::Module
)
find_package(Python3 COMPONENTS NumPy)
if(Python3_NumPy_FOUND)
    message(STATUS "Numpy Found")
else()
    message(STATUS "Numpy not found")
endif()
target_link_libraries(pNumpy INTERFACE
    Python3::NumPy
)
add_definitions(-DWITHOUT_NUMPY)

set(EIGEN3_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Eigen/" )
if(NOT EIGEN3_INCLUDE_DIR )
    message(FATAL_ERROR "Please point the variable EIGEN3_INCLUDE_DIR to the include directory of your Eigen3 installation.")
endif()
message(STATUS "    Eigen3 directory: ${EIGEN3_INCLUDE_DIR}")

set(MATPLOTLIB_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Matplotlib/" )


add_executable(main)
target_sources(main PUBLIC "main.cpp")
target_link_libraries(main pNumpy ${EIGEN3_INCLUDE_DIR} ${MATPLOTLIB_INCLUDE_DIR})
target_include_directories(main PUBLIC ${PROJECT_SOURCE_DIR})
add_subdirectory("include")
# add_subdirectory("Eigen")
add_subdirectory("visualization")
install(TARGETS main)
set(CMAKE_C_FLAGS_DEBUG "-g -DDEBUG")
set(CMAKE_CXX_FLAGS_DEBUG "-g -DDEBUG")
