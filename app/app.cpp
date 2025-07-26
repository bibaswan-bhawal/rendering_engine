#include "include/app.hpp"

int main(int argc, char *argv[]) {

  // Initialize default settings
  try {
    parseSettings(argc, argv, initalMonitorIndex, initalWindowWidth, initalWindowHeight);
  } catch (const std::invalid_argument &e) {
    cerr << "Error parsing settings: " << e.what() << endl;
    return -1;
  } catch (...) {
    cerr << "An unexpected error occurred while parsing settings." << endl;
    return -1;
  }

  // Set up callback for GLFW errors
  glfwSetErrorCallback(error_callback);

  // Attempt to initialize GLFW
  if (!glfwInit())
    return -1;

  // Set GLFW window hints
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  // To be able to show the window on a specific monitor we must first a
  // list of all the monitors. Then check if the requested monitor index is valid.
  // If it is, we can create the window on that monitor.

  // Get the primary monitor because if the window will be created on
  // on the primary monitor we want to the window to be focused.
  int monitorCount;
  GLFWmonitor **monitors = glfwGetMonitors(&monitorCount);

  if (monitorCount < initalMonitorIndex) {
    cerr << "Requested Monitor Index out of range." << endl;
    return -1;
  }

  // To create the window on the specified monitor, we need to get the position of the monitor
  // and the video mode of the monitor to set the initial window size.
  // The video mode will give us the width and height of the monitor.
  // We will also scale the initial window size based on the monitor's content scale.
  int xpos, ypos;
  glfwGetMonitorPos(monitors[initalMonitorIndex], &xpos, &ypos);

  const GLFWvidmode *mode = glfwGetVideoMode(monitors[initalMonitorIndex]);

  // Ensure the initial window size does not exceed the monitor's video mode dimensions
  initalWindowWidth = std::min(initalWindowWidth, mode->width);
  initalWindowHeight = std::min(initalWindowHeight, mode->height);

  // Get the content scale of the monitor to adjust the initial window size
  float xscale, yscale;
  glfwGetMonitorContentScale(monitors[initalMonitorIndex], &xscale, &yscale);

  // Adjust the initial window size based on the content scale
  initalWindowWidth = initalWindowWidth / xscale;
  initalWindowHeight = initalWindowHeight / yscale;

  // If the window is created on a secondary monitor, we do not want it to be focused
  GLFWmonitor *primaryMonitor = glfwGetPrimaryMonitor();

  if (monitors[initalMonitorIndex] != primaryMonitor) {
    glfwWindowHint(GLFW_FOCUSED, GLFW_FALSE);
  }

  // Create the GLFW window
  GLFWwindow *window = glfwCreateWindow(initalWindowWidth, initalWindowHeight, "Hello World", NULL, NULL);

  if (!window) {
    glfwTerminate();
    return -1;
  }

  // Position the window on the monitor
  glfwSetWindowPos(window, xpos + (mode->width - initalWindowWidth) / 2, ypos + (mode->height - initalWindowHeight) / 2);

  glfwSetKeyCallback(window, key_callback);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

  glfwMakeContextCurrent(window);

  if (!gladLoadGL(glfwGetProcAddress)) {
    cerr << "Failed to initialize GLAD" << endl;
    return -1;
  }

  // This is the main loop where we will render
  while (!glfwWindowShouldClose(window)) {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    glClear(GL_COLOR_BUFFER_BIT);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwTerminate();

  return 0;
}

void error_callback(int error, const char *description) { cerr << "Error " << error << ": " << description << endl; }

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
    cout << "Escape key pressed." << endl;
  }
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
  glViewport(0, 0, width, height);

  cout << "Window size: " << width << "x" << height << endl;
}