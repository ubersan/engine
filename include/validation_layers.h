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

class ValidationLayers {
public:
  void request(const vector<const char*>& requestedValidationLayerNames);
  void setupDebugMessenger(const VkInstance& instance);
  void cleanUp(const VkInstance& instance);

  void addLayers(VkInstanceCreateInfo& createInfo);
  void addLayers(VkDeviceCreateInfo& createInfo);
  void addExtensions(vector<const char*>& extensions);

private:
  VkDebugUtilsMessengerEXT debugMessenger;

  vector<const char*> layerNames;

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