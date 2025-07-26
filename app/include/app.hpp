#ifndef APP_H
#define APP_H

#define GLFW_INCLUDE_NONE
#define GLAD_GL_IMPLEMENTATION

#include <GLFW/glfw3.h>
#include <glad/gl.h>
#include <iostream>

#include "settings_parser.hpp"

using namespace std;

int initalMonitorIndex = 0; // Default monitor index

int initalWindowWidth = 1920;  // Desired inital window width
int initalWindowHeight = 1080; // Desired inital window height

void error_callback(int error, const char *description);

void framebuffer_size_callback(GLFWwindow *window, int width, int height);

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);

#endif // APP_H