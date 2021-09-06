cmake_minimum_required(VERSION 3.0.0)
project(gludon VERSION 0.1.0)

# opengl - required library
# glfw helps build opengl contexts
# glad - loads opengl definitions
# stb - image loader
find_package(OpenGL REQUIRED)
include_directories("lib/glfw/include" "lib/glad/include")
add_subdirectory("lib/glfw")
add_subdirectory("lib/glad")
include_directories("lib/stb")

# link the glfw libs
link_libraries(glfw ${GLFW_LIBRARIES} glad)

# allow including from the general include directory
include_directories(include)

# black magic to create a string out of a shader in the shaders/ folder
function(make_includable input_file output_file)
    file(READ ${input_file} content)
    set(delim "for_c++_include")
    set(content "R\"${delim}(\n${content})${delim}\"")
    file(WRITE ${output_file} "${content}")
endfunction(make_includable)



# generate these shader files
make_includable(shaders/simple.frag gen/shaders/simple.frag)
make_includable(shaders/simple.vert gen/shaders/simple.vert)

# configure resources
configure_file(res/img/container.jpg ${CMAKE_CURRENT_BINARY_DIR}/res/img/container.jpg COPYONLY)
# add them for including
include_directories(gen)


# this file is generated as a separate library in case if needed
add_library(glWindow src/glWindow.cpp)

add_library(glShader src/glShader.cpp)

add_library(glTexture src/glTexture.cpp)

add_executable(gludon src/main.cpp src/load_scripts.cpp)

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