#include "vulkan.h"

#include <iostream>
using namespace std;

class Viewer {
public:
  ~Viewer();

  void launch(int width, int height);

private:
  GLFWwindow* window;
  Vulkan vulkan;

  vector<const char*> getRequiredExtensions();
  static void exitCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
};