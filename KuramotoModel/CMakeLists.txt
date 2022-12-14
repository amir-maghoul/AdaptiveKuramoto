cmake_minimum_required(VERSION 3.20)
project(KuramotoModel)
option (USE_OpenMP "Use OpenMP" ON)
if(USE_OpenMP)
find_package(OpenMP)
  if(OPENMP_FOUND)
    message(STATUS "OpenMP Found")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    message(STATUS ${CMAKE_CXX_FLAGS})
  endif()
endif()


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


set(EIGEN3_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/eigen/" )
add_library(Eigen INTERFACE)
target_link_libraries(Eigen INTERFACE ${EIGEN3_INCLUDE_DIR})

set(MATPLOTLIB_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/matplotlibcpp/" )
add_library(Matplotlib INTERFACE)
target_link_libraries(Eigen INTERFACE ${MATPLOTLIB_INCLUDE_DIR})

add_executable(main)
target_sources(main PUBLIC "main.cpp")
target_link_libraries(main pNumpy Eigen Matplotlib)
target_include_directories(main PUBLIC ${PROJECT_SOURCE_DIR})
add_subdirectory("include")
add_subdirectory("examples")
add_subdirectory("visualization")
install(TARGETS main)
set(CMAKE_C_FLAGS_DEBUG "-g -DDEBUG")
set(CMAKE_CXX_FLAGS_DEBUG "-g -DDEBUG")
