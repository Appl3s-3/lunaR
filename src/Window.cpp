#include "luna/Window.hpp"

using namespace luna;

void luna::Initiate() {
    glfwInit();
}

void luna::Terminate() {
    glfwTerminate();
}

Window::Window(uint32_t width, uint32_t height, std::string _title, uint32_t major_version, uint32_t minor_version)
    :   dimensions{width, height}, title{_title} {

    std::cout << "Creating window: " + title + ", with dimensions: (" << width << ", " << height << ")" << std::endl;
    
    // Version
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major_version);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor_version);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Remove deprecated functions
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);

    // Enable debug context
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);

    // TODO: remove
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    window = glfwCreateWindow(dimensions.x, dimensions.y, title.c_str(), NULL, NULL);
    if (window == NULL) {
        std::cout << LUNA_FATAL_ERROR "Failed to instantiate GLFW3 window." << std::endl;
    }
    
    make_context_current();

    // Load GLAD2
    const int version = gladLoadGL(glfwGetProcAddress);
    if (version == 0) {
        std::cout << LUNA_FATAL_ERROR "Failed to find OpenGL context." << std::endl;
    }

}

Window::~Window() {
    glfwDestroyWindow(window);
}