#include "validation_layers.h"
#include "physical_devices.h"

class Vulkan {
public:
  ~Vulkan();

  void createInstance(const vector<const char*>& glfwRequiredExtensions);
  void pickPhysicalDevice();
  
private:
  VkInstance instance;
  VkPhysicalDevice physicalDevice{VK_NULL_HANDLE};
  ValidationLayers validationLayers;
  PhysicalDevices physicalDevices;
};
