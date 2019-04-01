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

  VkInstanceCreateInfo instanceCreateInfo = {
    .sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
    .pApplicationInfo = &application_info,
    .enabledExtensionCount = static_cast<uint32_t>(extensions.size()),
    .ppEnabledExtensionNames = extensions.data(),
  };
  validationLayers.addLayers(instanceCreateInfo);

  if (vkCreateInstance(&instanceCreateInfo, nullptr, &instance) != VK_SUCCESS) {
    throw runtime_error("Could not create instance.");
  }

  validationLayers.setupDebugMessenger(instance);
}

void Vulkan::pickPhysicalDevice() {
  physicalDevice = physicalDevices.findMostSuitableDevice(instance);
}

void Vulkan::createLogicalDevice() {
  float queuePriority = 1.0f;
  auto queueFamilyIndex = physicalDevices.getQueueFamilyIndex(physicalDevice);
  VkDeviceQueueCreateInfo queueCreateInfo{
    .sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,
    .queueFamilyIndex = queueFamilyIndex,
    .queueCount = 1,
    .pQueuePriorities = &queuePriority
  };

  VkPhysicalDeviceFeatures deviceFeatures{};
  VkDeviceCreateInfo deviceCreateInfo{
    .sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,
    .queueCreateInfoCount = 1,
    .pQueueCreateInfos = &queueCreateInfo,
    .pEnabledFeatures = &deviceFeatures
  };
  validationLayers.addLayers(deviceCreateInfo);

  if (vkCreateDevice(physicalDevice, &deviceCreateInfo, nullptr, &device) != VK_SUCCESS) {
    throw runtime_error("Failed to create logical device");
  }

  vkGetDeviceQueue(device, queueFamilyIndex, 0, &graphicsQueue);
}
