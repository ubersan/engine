#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <iostream>
using namespace std;

int main() {
  VkApplicationInfo application_info = {
    .sType = VK_STRUCTURE_TYPE_APPLICATION_INFO,
    .pApplicationName = "Engine",
    .applicationVersion = 1,
    .pEngineName = "Engine",
    .engineVersion = 1,
    .apiVersion = VK_API_VERSION_1_1,
  };

  VkInstanceCreateInfo instance_create_info = {
    .sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
    .pApplicationInfo = &application_info,
  };

  VkInstance instance;
  if (vkCreateInstance(&instance_create_info, nullptr, &instance) != VK_SUCCESS) {
    cout << "Could not create instance." << endl;
  }

  vkDestroyInstance(instance, nullptr);

  cout << "Done" << endl;
  return 0;
}