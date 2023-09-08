#ifndef LUNA_INPUT_HPP
#define LUNA_INPUT_HPP

#include "luna/Window.hpp"
#include "luna/Keyboard.hpp"
#include "luna/Mouse.hpp"

namespace luna {
class Input {
public:
    Input(luna::Window &window);
    ~Input();

    void process();

    Keyboard keyboard;
    Mouse mouse;
};
} // namespace luna

#endif // LUNA_INPUT_HPP
