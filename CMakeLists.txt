cmake_minimum_required(VERSION 3.10)

project(rendering_app)

set(CMAKE_CXX_STANDARD 17)
set(EXECUTABLE_NAME "rendering_app")

# Add the executable
add_executable(${EXECUTABLE_NAME} app/app.cpp)

# Set source directories for third-party libraries
set(GLAD_ROOT "${CMAKE_SOURCE_DIR}/third_party/glad")
set(GLFW_ROOT "${CMAKE_SOURCE_DIR}/third_party/glfw-3.4")

# Include directories for third-party libraries
include_directories(${GLFW_ROOT}/include) # GLFW
include_directories(${GLAD_ROOT}/include) # glad


## Include directories for the application
include_directories(${CMAKE_SOURCE_DIR}/app/include)

# Set the GLFW library directory based on the platform
if(APPLE)
    # Detect architecture and set library path
    if(CMAKE_OSX_ARCHITECTURES MATCHES "arm64")
        set(GLFW_LIB_DIR "${GLFW_ROOT}/lib-arm64")
    elseif(CMAKE_OSX_ARCHITECTURES MATCHES "x86_64")
        set(GLFW_LIB_DIR "${GLFW_ROOT}/lib-x86_64")
    else()
        set(GLFW_LIB_DIR "${GLFW_ROOT}/lib-universal")
    endif()
endif()

# Set the glad source file
set(GLAD_SRC ${GLAD_ROOT}/src/gl.c)

# Link GLFW
find_library(GLFW_LIB glfw3 PATHS ${GLFW_LIB_DIR} NO_DEFAULT_PATH)
target_link_libraries(${EXECUTABLE_NAME} ${GLFW_LIB})

# Add glad source to the executable
target_sources(${EXECUTABLE_NAME} PRIVATE ${GLAD_SRC})

# Add the settings parser source file to the executable
target_sources(${EXECUTABLE_NAME} PRIVATE app/settings_parser.cpp)

# Link system frameworks (for macOS)
if(APPLE)
    target_link_libraries(${EXECUTABLE_NAME}
        "-framework Cocoa"
        "-framework OpenGL"
        "-framework IOKit"
    )
endif()
