cmake_minimum_required(VERSION 3.14)
project(MP)
set(CMAKE_CXX_STANDARD 17)
set(SOURCE_FILES main.cpp MPEngine.cpp MPEngine.hpp Car.cpp Car.hpp the_warrior/TheWarrior.cpp the_warrior/TheWarrior.hpp ShaderLocations.hpp Eeyore/eeyore.cpp Eeyore/eeyore.hpp HeroType.hpp HeroVirtual.hpp john_Reimann/JohnReimann.cpp john_Reimann/JohnReimann.hpp Tree.cpp Tree.hpp)
add_executable(${PROJECT_NAME} ${SOURCE_FILES})
include_directories("${CMAKE_SOURCE_DIR}/include")

# Windows with MinGW Installations
if( ${CMAKE_SYSTEM_NAME} MATCHES "Windows" AND MINGW )
    # if working on Windows but not in the lab
    # update the include directory location
    # update the lib directory location
    if ($ENV{USERPROFILE} MATCHES "C:/Users/johan")
        include_directories("C:/Users/johan/Desktop/CSCI441/include")
        # update the lib directory location
        target_link_directories(${PROJECT_NAME} PUBLIC "C:/Users/johan/Desktop/CSCI441/lib")
    else()
        include_directories("D:/CSCI441/include")
        target_link_libraries(${PROJECT_NAME} opengl32 glfw3 glew32.dll gdi32)
        target_link_directories(${PROJECT_NAME} PUBLIC "D:/CSCI441/lib")
    endif()

    # OS X Installations
elseif( APPLE AND ${CMAKE_SYSTEM_NAME} MATCHES "Darwin" )
    # update the include directory location
    include_directories("/usr/local/include")
    # update the lib directory location
    target_link_directories(${PROJECT_NAME} PUBLIC "/usr/local/lib")
    target_link_libraries(${PROJECT_NAME} "-framework OpenGL" "-framework Cocoa" "-framework IOKit" "-framework CoreVideo" glfw glew)
    # Blanket *nix Installations
elseif( UNIX AND ${CMAKE_SYSTEM_NAME} MATCHES "Linux" )
    # update the include directory location
    include_directories("/usr/local/include")
    # update the lib directory location
    target_link_directories(${PROJECT_NAME} PUBLIC "/usr/local/lib")
    target_link_libraries(${PROJECT_NAME} opengl glfw GLEW)
endif()