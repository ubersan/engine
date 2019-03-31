#include "vulkan.h"
#include <algorithm>

Vulkan::~Vulkan() {
  if (VALIDATION_LAYERS_ARE_ENABLED) {
    validationLayers.cleanUp(instance);
  }
  vkDestroyInstance(instance, nullptr);
}

void Vulkan::createInstance() {
  validationLayers.request({"VK_LAYER_LUNARG_standard_validation"});

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
    instance_create_info.enabledLayerCount = validationLayers.count();
    instance_create_info.ppEnabledLayerNames = validationLayers.layerNames.data();
  }

  if (vkCreateInstance(&instance_create_info, nullptr, &instance) != VK_SUCCESS) {
    throw runtime_error("Could not create instance.");
  }

  validationLayers.setupDebugMessenger(instance);
}
