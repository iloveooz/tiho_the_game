cmake_minimum_required(VERSION 3.10)
project(tiho)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_COMPILER /usr/bin/g++)

set(SOURCE_FILES main.cpp Car.cpp Car.h Tank.cpp Tank.h Entity.cpp Entity.h Animation.cpp Animation.h IObject/IObject.hpp)
add_executable(tiho ${SOURCE_FILES})

set(EXECUTABLE_NAME ${PROJECT_NAME})

# If you want to link SFML statically
# set(SFML_STATIC_LIBRARIES TRUE)

## In most cases better set in the CMake cache
# set(SFML_DIR "<sfml root prefix>/lib/cmake/SFML")

# detect and add SFML to the project
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
find_package(SFML 2 REQUIRED system window graphics network audio)

if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARIES})
endif()










