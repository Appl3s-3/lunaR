#include "luna/Input.hpp"

using namespace luna;

Input::Input(luna::Window &window)
    : keyboard(window.get()),
      mouse(window.get()) {
}

Input::~Input() {

}

void Input::process() {
    keyboard.process();
    mouse.process();
}
