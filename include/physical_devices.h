#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <iostream>
#include <vector>
using namespace std;

class PhysicalDevices {
public:
  VkPhysicalDevice findMostSuitableDevice(const VkInstance& instance);

  uint32_t getQueueFamilyIndex(const VkPhysicalDevice& device);

private:
  bool isDeviceSuitable(const VkPhysicalDevice& device);
};