project(SGF)
cmake_minimum_required(VERSION 2.8)
set(CMAKE_BUILD_TYPE "Release")
#set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

#include_directories(${CMAKE_CURRENT_SOURCE_DIR})   

find_package( OpenCV REQUIRED )
if( OpenCV_FOUND )
list( APPEND ThirdParty_LIBS ${OpenCV_LIBS} )
    include_directories( ${OpenCV_INCLUDE_DIRS} )
endif( OpenCV_FOUND )

FIND_PACKAGE(OpenMP REQUIRED)  
if(OPENMP_FOUND)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif()

#this is for c++11 support
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(${PROJECT_NAME}_SRC src/main.cpp src/SGF.cpp src/Image.cpp src/SLIC.cpp)
set(${PROJECT_NAME}_HDR src/Image.h src/SLIC.cpp)

add_executable(${PROJECT_NAME} ${${PROJECT_NAME}_SRC} ${${PROJECT_NAME}_HDR})
target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})
