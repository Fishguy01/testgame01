cmake_minimum_required(VERSION 3.15)
project(injectionstart)

set(CMAKE_CXX_STANDARD 17)


#trova il file raylib
find_package(raylib REQUIRED)

#crea il gioco questo
add_executable(initialgame initialtest.cpp)

#collega il raylib al eseguibile
target_link_libraries(initialgame raylib)