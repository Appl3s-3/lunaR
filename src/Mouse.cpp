#include "luna/Mouse.hpp"

using namespace luna;

Mouse::Mouse(GLFWwindow *window)
    : window_ref(window) {
}

Mouse::~Mouse() {
}

void Mouse::process() {
    // Mouse Position
    glfwGetCursorPos(window_ref, &position_x, &position_y);

    // Mouse Buttons
    bool was_held = false;
    
    for (int i = 0; i < 8; ++i) {
        was_held = button_held[i] > 0;

        ++button_held[i];
        button_held[i] *= (glfwGetMouseButton(window_ref, i) == GLFW_PRESS);

        button_down[i] = (button_held[i] == 1);
        button_up[i]   = (was_held == true) && (button_held[i] == 0);
    }
}
