#include "validation_layers.h"

class Vulkan {
public:
  ~Vulkan();

  void createInstance(const vector<const char*>& glfwRequiredExtensions);

private:
  VkInstance instance;
  VkPhysicalDevice physicalDevice;
  ValidationLayers validationLayers;
};
