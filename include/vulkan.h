#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <iostream>
#include <vector>
using namespace std;

#ifdef NDEBUG
const bool VALIDATION_LAYERS_ARE_ENABLED = false;
#else
const bool VALIDATION_LAYERS_ARE_ENABLED = true;
#endif

class Vulkan {
public:
  ~Vulkan();

  void createInstance();

private:
  VkInstance instance;
  VkDebugUtilsMessengerEXT debugMessenger;

  vector<const char*> validationLayers{"VK_LAYER_LUNARG_standard_validation"};

  bool allRequestedValidationLayersAreSupported();

  VkResult CreateDebugUtilsMessengerEXT(
    VkInstance instance,
    const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkDebugUtilsMessengerEXT* pDebugMessenger);

  void DestroyDebugUtilsMessengerEXT(
    VkInstance instance,
    VkDebugUtilsMessengerEXT debugMessenger,
    const VkAllocationCallbacks* pAllocator);

  static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
    VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
    VkDebugUtilsMessageTypeFlagsEXT messageType,
    const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
    void* pUserData) {
      cerr << "Validation layer: " << pCallbackData->pMessage << endl;
      return VK_FALSE;
    }
};
