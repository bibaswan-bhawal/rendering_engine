#include <iostream>
#include <stdexcept>

#include "include/settings_parser.hpp"

using namespace std;

/// Function to parse command line arguments for settings.
///
/// @param argc Number of command line arguments
/// @param argv Array of command line arguments
/// @param monitorIndex Reference to store the monitor index
/// @param windowWidth Reference to store the initial window width
/// @param windowHeight Reference to store the initial window height
///
/// @note Should probably create a settings object to encapsulate these settings
///       instead of passing multiple references. This would also allow for easier
///       extension in the future.
void parseSettings(int argc, char *argv[], int &monitorIndex, int &windowWidth, int &windowHeight) {
  for (int i = 0; i < argc; i++) {
    if (argv[i] == std::string("--monitor")) { // monitor index argument
      if (i + 1 >= argc) {
        throw invalid_argument("No monitor index provided.");
      }

      try {
        monitorIndex = stoi(argv[i + 1]);
      } catch (const std::invalid_argument &e) {
        throw invalid_argument("Invalid monitor index provided.");
      }
    } else if (argv[i] == std::string("--size")) { // size argument is expected to be in the format --size <width>x<height>
      if (i + 1 >= argc) {
        throw invalid_argument("No window size provided.");
      }

      try {
        string sizeArg = argv[i + 1];
        size_t xPos = sizeArg.find('x');

        if (xPos == string::npos || xPos == 0 || xPos == sizeArg.length() - 1) {
          throw invalid_argument("Invalid window size format. Use <width>x<height>.");
        }

        windowWidth = stoi(sizeArg.substr(0, xPos));
        windowHeight = stoi(sizeArg.substr(xPos + 1));
      } catch (const std::invalid_argument &e) {
        throw invalid_argument("Invalid window size provided.");
      }
    }
  }
}
