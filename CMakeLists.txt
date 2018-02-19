cmake_minimum_required(VERSION 3.9)
project(icingaGUI)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES sources/main.cpp sources/service.cpp sources/menubar.cpp sources/json.hpp sources/hosts.cpp sources/Services.cpp sources/Services.h sources/CheckUnit.cpp sources/CheckUnit.h sources/Utilities.cpp sources/Utilities.h sources/fastAckWindow.cpp sources/fastAckWindow.h)

add_executable(icingaGUI ${SOURCE_FILES})

set(CMAKE_MODULE_PATH "C:/icingaGUI/cmake/Modules")

find_package(SFML REQUIRED system window graphics network )
find_package(TGUI REQUIRED)
include_directories(${SFML_INCLUDE_DIR} ${TGUI_INCLUDE_DIR})
target_link_libraries(icingaGUI ${SFML_LIBRARIES} ${TGUI_LIBRARY})



