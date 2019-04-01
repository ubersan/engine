#include "validation_layers.h"

#include <algorithm>

void ValidationLayers::cleanUp(const VkInstance& instance) {
  if (VALIDATION_LAYERS_ARE_ENABLED) {
    DestroyDebugUtilsMessengerEXT(instance, debugMessenger, nullptr);
  }
}

void ValidationLayers::request(const vector<const char*>& requestedValidationLayerNames) {
  layerNames = vector<const char*>{requestedValidationLayerNames};

  if (VALIDATION_LAYERS_ARE_ENABLED && !allRequestedValidationLayersAreSupported()) {
    throw runtime_error("Not all requested validation layers are available");
  }
}

void ValidationLayers::setupDebugMessenger(const VkInstance& instance) {
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

void ValidationLayers::addLayers(VkInstanceCreateInfo& createInfo) {
  if (VALIDATION_LAYERS_ARE_ENABLED) {
    createInfo.enabledLayerCount = static_cast<uint32_t>(layerNames.size());
    createInfo.ppEnabledLayerNames = layerNames.data();
  }
}

void ValidationLayers::addLayers(VkDeviceCreateInfo& createInfo) {
  if (VALIDATION_LAYERS_ARE_ENABLED) {
    createInfo.enabledLayerCount = static_cast<uint32_t>(layerNames.size());
    createInfo.ppEnabledLayerNames = layerNames.data();
  }
}

void ValidationLayers::addExtensions(vector<const char*>& extensions) {
  if (VALIDATION_LAYERS_ARE_ENABLED) {
    extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
  }
}

bool ValidationLayers::allRequestedValidationLayersAreSupported() {
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
    layerNames.begin(),
    layerNames.end(),
    [&](const char* layerName) {
      return find(availableLayerNames.begin(), availableLayerNames.end(), layerName) != availableLayerNames.end();
    }
  );
}

VkResult ValidationLayers::CreateDebugUtilsMessengerEXT(
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

void ValidationLayers::DestroyDebugUtilsMessengerEXT(
  VkInstance instance,
  VkDebugUtilsMessengerEXT debugMessenger,
  const VkAllocationCallbacks* pAllocator) {
    auto func = (PFN_vkDestroyDebugUtilsMessengerEXT) vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");
    if (func != nullptr) {
      func(instance, debugMessenger, pAllocator);
    }
  }
