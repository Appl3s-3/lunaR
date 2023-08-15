#if !defined(LUNA_WINDOW_HPP)
#define LUNA_WINDOW_HPP

#include <string>
#include <cstdint>
#include <iostream>

#include "glm/glm.hpp"
#include "luna/miniGL.h"
#include "luna/LunaDefines.hpp"

namespace luna {

void Initiate();

void Terminate();

class Window {
public:
    Window(uint32_t width, uint32_t height, std::string title, uint32_t major_version = 3, uint32_t minor_version = 3);
    ~Window();

    inline void make_context_current() { glfwMakeContextCurrent(window); }
    inline void poll()                 { glfwPollEvents(); }
    inline bool not_closed()           { return !glfwWindowShouldClose(window); }
    inline void swap_buffers()         { glfwSwapBuffers(window); }
    inline GLFWwindow* get()           { return window; }

    inline void clear(GLenum buffer = GL_COLOR_BUFFER_BIT) { glClear(buffer); }
    inline void clear_colour(double r = 0.0, double g = 0.0, double b = 0.0, double a = 1.0) { glClearColor(r, g, b, a); }

    glm::ivec2 dimensions;

private:
    std::string title;
    GLFWwindow* window;
};

} // namespace luna

#endif // LUNA_WINDOW_HPP
