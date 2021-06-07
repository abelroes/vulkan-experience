using namespace std;

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <imgui>
#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <vector>
#include <cstring>

class HelloTriangleApplication {
public:
    void run() {
        initWindow();
        initVulkan();
        mainLoop();
        cleanup();
    }

private:
    GLFWwindow* window;
    const uint32_t WIDTH = 800;
    const uint32_t HEIGHT = 600;
    VkInstance instance;

    void initWindow() {
        glfwInit();
        // Prevent OpenGL from being used
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
        window = glfwCreateWindow(WIDTH, HEIGHT, "Vulkan", nullptr, nullptr);
    }

    void initVulkan() {
        createInstance();
    }
    
    void createInstance() {
        // Vulkan Optional struct
        VkApplicationInfo appInfo{};
        appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        appInfo.pApplicationName = "Hello Triangle";
        appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.pEngineName = "No Engine";
        appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.apiVersion = VK_API_VERSION_1_0;

        // Vulkan Not-Optional struct!!!
        VkInstanceCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        createInfo.pApplicationInfo = &appInfo;

        vector<VkExtensionProperties> extensions = getSupportedExtensions();

        uint32_t glfwExtensionCount = 0;
        const char** glfwExtensions;
        glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

        verifyRequirements(glfwExtensionCount, glfwExtensions, extensions);

        createInfo.enabledExtensionCount = glfwExtensionCount;
        createInfo.ppEnabledExtensionNames = glfwExtensions;
        createInfo.enabledLayerCount = 0;

        VkResult result = vkCreateInstance(&createInfo, nullptr, &instance);
        if (result != VK_SUCCESS) {
            throw std::runtime_error("Failed to create instance!");
        }
    }

    vector<VkExtensionProperties> getSupportedExtensions() {
        uint32_t extensionCount = 0;
        vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
        vector<VkExtensionProperties> extensions(extensionCount);
        vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data());
        cout << "available extensions:\n";

        for (const auto& extension : extensions) {
            cout << '\t' << extension.extensionName << '\n';
        }
        return extensions;
    }

    void verifyRequirements(uint32_t requiredExtensionCount, const char** requiredExtensions, vector<VkExtensionProperties> availableExtensions) {
        int requiredCount = 0;
        for (unsigned int i = 0; i < requiredExtensionCount; i++){
            for (const auto& extension : availableExtensions) {
                if (strcmp(extension.extensionName, requiredExtensions[i]) == 0)
                    requiredCount++;
            }
        }

        bool hasAllRequiredExtensions = requiredCount == requiredExtensionCount;
        if (!hasAllRequiredExtensions) {
            throw std::runtime_error("Failed to find all required extensions!");
        } else {
            cout << "All required extentions were found!\n";
        }
    }

    void mainLoop() {
        while (!glfwWindowShouldClose(window)) {
            glfwPollEvents();
        }
    }

    void cleanup() {
        vkDestroyInstance(instance, nullptr);
        glfwDestroyWindow(window);
        glfwTerminate();
    }
};

int main() {
    HelloTriangleApplication app;

    try {
        app.run();
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}