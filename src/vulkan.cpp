#include "vulkan.h"
#include <algorithm>

Vulkan::~Vulkan() {
  validationLayers.cleanUp(instance);
  vkDestroyInstance(instance, nullptr);
}

void Vulkan::createInstance(const vector<const char*>& glfwRequiredExtensions) {
  validationLayers.request({"VK_LAYER_LUNARG_standard_validation"});

  VkApplicationInfo application_info = {
    .sType = VK_STRUCTURE_TYPE_APPLICATION_INFO,
    .pApplicationName = "Engine",
    .applicationVersion = 1,
    .pEngineName = "Engine",
    .engineVersion = 1,
    .apiVersion = VK_API_VERSION_1_1,
  };

  vector<const char*> extensions{glfwRequiredExtensions};
  validationLayers.addExtensions(extensions);

  VkInstanceCreateInfo instance_create_info = {
    .sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
    .pApplicationInfo = &application_info,
    .enabledExtensionCount = static_cast<uint32_t>(extensions.size()),
    .ppEnabledExtensionNames = extensions.data(),
  };

  validationLayers.addLayers(instance_create_info);

  if (vkCreateInstance(&instance_create_info, nullptr, &instance) != VK_SUCCESS) {
    throw runtime_error("Could not create instance.");
  }

  validationLayers.setupDebugMessenger(instance);
}

void Vulkan::pickPhysicalDevice() {
  uint32_t deviceCount = 0;
  vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);

  if (deviceCount == 0) {
    throw runtime_error("No GPUs with Vulkan support found");
  }

  vector<VkPhysicalDevice> physicalDevices(deviceCount);
  vkEnumeratePhysicalDevices(instance, &deviceCount, physicalDevices.data());
}
