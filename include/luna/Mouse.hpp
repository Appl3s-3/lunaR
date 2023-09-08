#ifndef LUNA_MOUSE_HPP
#define LUNA_MOUSE_HPP

#include <array>
#include "luna/miniGL.h"
#include "glm/glm.hpp"

namespace luna {
class Mouse {
public:
    Mouse(GLFWwindow *window);
    ~Mouse();

    void process();

    double position_x = 0.0;
    double position_y = 0.0;

    std::array<uint32_t, 8> button_held = { 0, 0, 0, 0, 0, 0, 0, 0 };
    std::array<bool, 8>     button_down = { false, false, false, false, false, false, false, false };
    std::array<bool, 8>     button_up   = { false, false, false, false, false, false, false, false };

private:
    GLFWwindow *window_ref;
};
} // namespace luna

#endif // LUNA_MOUSE_HPP
