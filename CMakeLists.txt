cmake_minimum_required(VERSION 3.0.0)
project(gludon VERSION 0.1.0)

# opengl - required library
set(OpenGL_GL_PREFERENCE GLVND)
find_package(OpenGL REQUIRED)

# includes for use
include_directories("lib/glfw/include" "lib/glad/include")

# glfw helps build opengl contexts
add_subdirectory("lib/glfw")
# glad - loads opengl definitions
add_subdirectory("lib/glad")
# glm - gl matrix manipulations
add_subdirectory("lib/glm")
# stb - image loader
include_directories("lib/stb")

# link the glfw libs
link_libraries(glfw ${GLFW_LIBRARIES} glad)

# allow including from the general include directory
include_directories(include)


# configure resources - images and shaders
configure_file(res/img/container.jpg ${CMAKE_CURRENT_BINARY_DIR}/res/img/container.jpg COPYONLY)
configure_file(shaders/simple.frag ${CMAKE_CURRENT_BINARY_DIR}/shaders/simple.frag COPYONLY)
configure_file(shaders/simple.vert ${CMAKE_CURRENT_BINARY_DIR}/shaders/simple.vert COPYONLY)


# these are generated as a separate library in case if needed
add_library(glWindow src/glWindow.cpp)

add_library(glShader src/glShader.cpp)

add_library(glTexture src/glTexture.cpp)

# final executable
add_executable(gludon src/main.cpp src/load_scripts.cpp)
# link our executable with these nice libraries
target_link_libraries(gludon glWindow glShader glTexture)

# documentation stuff
find_package(Doxygen)
if (DOXYGEN_FOUND)
    set(DOXYGEN_GENERATE_HTML YES)
    set(DOXYGEN_JAVADOC_BANNER YES)
    set(DOXYGEN_EXTRACT_ALL YES)
    doxygen_add_docs(
        doc ALL
        ${PROJECT_SOURCE_DIR}/src
        ${PROJECT_SOURCE_DIR}/include
        COMMENT "Generate man pages"
    )
else (DOXYGEN_FOUND)
  message("Doxygen need to be installed to generate the doxygen documentation")
endif()