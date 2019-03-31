#include "viewer.h"

Viewer::~Viewer() {
  glfwDestroyWindow(window);
  glfwTerminate();
}

void Viewer::launch(int width, int height) {
  glfwInit();
  glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
  glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

  window = glfwCreateWindow(width, height, "Engine", nullptr, nullptr);
  glfwSetKeyCallback(window, exitCallback);

  auto requiredExtensions = getRequiredExtensions();
  vulkan.createInstance(requiredExtensions);

  while (!glfwWindowShouldClose(window)) {
    glfwPollEvents();
  }
}

void Viewer::exitCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, GLFW_TRUE);
  }
}

vector<const char*> Viewer::getRequiredExtensions() {
  uint32_t extensionCount = 0;
  auto extensions = glfwGetRequiredInstanceExtensions(&extensionCount);

  return vector<const char*>{extensions, extensions + extensionCount};
}