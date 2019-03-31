#include "vulkan.h"
#include <algorithm>

Vulkan::~Vulkan() {
  if (VALIDATION_LAYERS_ARE_ENABLED) {
    DestroyDebugUtilsMessengerEXT(instance, debugMessenger, nullptr);
  }

  vkDestroyInstance(instance, nullptr);
}

void Vulkan::createInstance() {
  if (VALIDATION_LAYERS_ARE_ENABLED && !allRequestedValidationLayersAreSupported()) {
    throw runtime_error("Not all requested validation layers are available");
  }

  VkApplicationInfo application_info = {
    .sType = VK_STRUCTURE_TYPE_APPLICATION_INFO,
    .pApplicationName = "Engine",
    .applicationVersion = 1,
    .pEngineName = "Engine",
    .engineVersion = 1,
    .apiVersion = VK_API_VERSION_1_1,
  };

  uint32_t glfwRequiredInstanceExtensionsCount = 0;
  auto glfwRequiredInstanceExtensions = glfwGetRequiredInstanceExtensions(&glfwRequiredInstanceExtensionsCount);

  vector<const char*> extensions(glfwRequiredInstanceExtensions, glfwRequiredInstanceExtensions + glfwRequiredInstanceExtensionsCount);
  if (VALIDATION_LAYERS_ARE_ENABLED) {
    extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
  }

  VkInstanceCreateInfo instance_create_info = {
    .sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
    .pApplicationInfo = &application_info,
    .enabledExtensionCount = static_cast<uint32_t>(extensions.size()),
    .ppEnabledExtensionNames = extensions.data(),
  };

  if (VALIDATION_LAYERS_ARE_ENABLED) {
    instance_create_info.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
    instance_create_info.ppEnabledLayerNames = validationLayers.data();
  }

  if (vkCreateInstance(&instance_create_info, nullptr, &instance) != VK_SUCCESS) {
    throw runtime_error("Could not create instance.");
  }

  // debug messenger
  if (VALIDATION_LAYERS_ARE_ENABLED) {
    VkDebugUtilsMessengerCreateInfoEXT createDebugUtilsMessengerInfo{
      .sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT,
      .messageSeverity =
        VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT
        | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT
        | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT,
      .messageType =
        VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT
        | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT
        | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT,
      .pfnUserCallback = debugCallback,
    };

    if (CreateDebugUtilsMessengerEXT(instance, &createDebugUtilsMessengerInfo, nullptr, &debugMessenger) != VK_SUCCESS) {
      throw runtime_error("Could not set up debug messenger");
    }
  }
}

bool Vulkan::allRequestedValidationLayersAreSupported() {
  uint32_t layerCount;
  vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

  vector<VkLayerProperties> availableLayers(layerCount);
  vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

  vector<string> availableLayerNames(layerCount);
  transform(
    availableLayers.begin(),
    availableLayers.end(),
    availableLayerNames.begin(),
    [&](VkLayerProperties layer) -> string {return layer.layerName;}
  );

  return all_of(
    validationLayers.begin(),
    validationLayers.end(),
    [&](const char* layerName) {
      return find(availableLayerNames.begin(), availableLayerNames.end(), layerName) != availableLayerNames.end();
    }
  );
}

/*VKAPI_ATTR VkBool32 VKAPI_CALL Vulkan::debugCallback(
  VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
  VkDebugUtilsMessageTypeFlagsEXT messageType,
  const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
  void* pUserData) {
    cerr << "Validation layer: " << pCallbackData->pMessage << endl;
    return VK_FALSE;
  }
*/

VkResult Vulkan::CreateDebugUtilsMessengerEXT(
  VkInstance instance,
  const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo,
  const VkAllocationCallbacks* pAllocator,
  VkDebugUtilsMessengerEXT* pDebugMessenger) {
    auto func = (PFN_vkCreateDebugUtilsMessengerEXT) vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");
    if (func != nullptr) {
      return func(instance, pCreateInfo, pAllocator, pDebugMessenger);
    } else {
      return VK_ERROR_EXTENSION_NOT_PRESENT;
    }
  }

void Vulkan::DestroyDebugUtilsMessengerEXT(
  VkInstance instance,
  VkDebugUtilsMessengerEXT debugMessenger,
  const VkAllocationCallbacks* pAllocator) {
    auto func = (PFN_vkDestroyDebugUtilsMessengerEXT) vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");
    if (func != nullptr) {
      func(instance, debugMessenger, pAllocator);
    }
  }