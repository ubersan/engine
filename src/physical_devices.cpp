#include "physical_devices.h"

VkPhysicalDevice PhysicalDevices::findMostSuitableDevice(const VkInstance& instance) {
  uint32_t deviceCount = 0;
  vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);

  if (deviceCount == 0) {
    throw runtime_error("No GPUs with Vulkan support found");
  }

  vector<VkPhysicalDevice> physicalDevices(deviceCount);
  vkEnumeratePhysicalDevices(instance, &deviceCount, physicalDevices.data());

  for (const auto& device: physicalDevices) {
    if (isDeviceSuitable(device)) {
      return device;
    }
  }
  
  throw runtime_error("Failed to find a suitable GPU");
}

bool PhysicalDevices::isDeviceSuitable(const VkPhysicalDevice& device) {
  uint32_t queueFamilyCount = 0;
  vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);

  vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
  vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());

  for (const auto& queueFamily : queueFamilies) {
    if (queueFamily.queueCount > 0 && (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT)) {
      return true;
    }
  }

  return false;
}