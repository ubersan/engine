#include "validation_layers.h"


class Vulkan {
public:
  ~Vulkan();

  void createInstance();

private:
  VkInstance instance;
  VkPhysicalDevice physicalDevice;
  ValidationLayers validationLayers;
  

 
};
