#include "validation_layers.h"
#include "physical_devices.h"

class Vulkan {
public:
  ~Vulkan();

  void createInstance(const vector<const char*>& glfwRequiredExtensions);
  void pickPhysicalDevice();
  void createLogicalDevice();
  
private:
  VkInstance instance;
  VkPhysicalDevice physicalDevice{VK_NULL_HANDLE};
  ValidationLayers validationLayers;
  PhysicalDevices physicalDevices;
  
  VkDevice device;
  VkQueue graphicsQueue;
};
