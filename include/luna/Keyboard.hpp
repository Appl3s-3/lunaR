#ifndef LUNA_KEYBOARD_HPP
#define LUNA_KEYBOARD_HPP

#include <unordered_map>
#include <string>
#include <array>
#include "luna/miniGL.h"

//uint32_t id ## _held; // Keys can be held down for ~200 days given that the program is running at 240 fps
//uint8_t id ## _down; // Be wary of padding

#define TESTKEY8(window, id1, id2, id3, id4, id5, id6, id7, id8)\
    key_ ## id1 ## _held = (++key_ ## id1 ## _held * (glfwGetKey(window, GLFW_KEY_ ## id1 ) == GLFW_PRESS));\
    key_ ## id2 ## _held = (++key_ ## id2 ## _held * (glfwGetKey(window, GLFW_KEY_ ## id2 ) == GLFW_PRESS));\
    key_ ## id3 ## _held = (++key_ ## id3 ## _held * (glfwGetKey(window, GLFW_KEY_ ## id3 ) == GLFW_PRESS));\
    key_ ## id4 ## _held = (++key_ ## id4 ## _held * (glfwGetKey(window, GLFW_KEY_ ## id4 ) == GLFW_PRESS));\
    key_ ## id5 ## _held = (++key_ ## id5 ## _held * (glfwGetKey(window, GLFW_KEY_ ## id5 ) == GLFW_PRESS));\
    key_ ## id6 ## _held = (++key_ ## id6 ## _held * (glfwGetKey(window, GLFW_KEY_ ## id6 ) == GLFW_PRESS));\
    key_ ## id7 ## _held = (++key_ ## id7 ## _held * (glfwGetKey(window, GLFW_KEY_ ## id7 ) == GLFW_PRESS));\
    key_ ## id8 ## _held = (++key_ ## id8 ## _held * (glfwGetKey(window, GLFW_KEY_ ## id8 ) == GLFW_PRESS));\
    key_ ## id1 ## _down = (key_ ## id1 ## _held == 1 );\
    key_ ## id2 ## _down = (key_ ## id2 ## _held == 1 );\
    key_ ## id3 ## _down = (key_ ## id3 ## _held == 1 );\
    key_ ## id4 ## _down = (key_ ## id4 ## _held == 1 );\
    key_ ## id5 ## _down = (key_ ## id5 ## _held == 1 );\
    key_ ## id6 ## _down = (key_ ## id6 ## _held == 1 );\
    key_ ## id7 ## _down = (key_ ## id7 ## _held == 1 );\
    key_ ## id8 ## _down = (key_ ## id8 ## _held == 1 );

#define IDENTIFYKEY8(id1, id2, id3, id4, id5, id6, id7, id8)\
    uint32_t key_ ## id1 ## _held;\
    uint32_t key_ ## id2 ## _held;\
    uint32_t key_ ## id3 ## _held;\
    uint32_t key_ ## id4 ## _held;\
    uint32_t key_ ## id5 ## _held;\
    uint32_t key_ ## id6 ## _held;\
    uint32_t key_ ## id7 ## _held;\
    uint32_t key_ ## id8 ## _held;\
    uint8_t key_ ## id1 ## _down;\
    uint8_t key_ ## id2 ## _down;\
    uint8_t key_ ## id3 ## _down;\
    uint8_t key_ ## id4 ## _down;\
    uint8_t key_ ## id5 ## _down;\
    uint8_t key_ ## id6 ## _down;\
    uint8_t key_ ## id7 ## _down;\
    uint8_t key_ ## id8 ## _down;

namespace luna {

class Keyboard {
public:
    Keyboard(GLFWwindow *window);
    ~Keyboard();

    void process();

    std::unordered_map<char, uint32_t> key_held = {
        {'A', 0}, {'B', 0}, {'C', 0}, {'D', 0}, {'E', 0}, {'F', 0}, {'G', 0}, {'H', 0}, {'I', 0}, {'J', 0},
        {'K', 0}, {'L', 0}, {'M', 0}, {'N', 0}, {'O', 0}, {'P', 0}, {'Q', 0}, {'R', 0}, {'S', 0}, {'T', 0},
        {'U', 0}, {'V', 0}, {'W', 0}, {'X', 0}, {'Y', 0}, {'Z', 0},
        {'0', 0}, {'1', 0}, {'2', 0}, {'3', 0}, {'4', 0}, {'5', 0}, {'6', 0}, {'7', 0}, {'8', 0}, {'9', 0},

        {' ', 0}, {'\'', 0}, {',', 0}, {'-', 0}, {'.', 0}, {'/', 0}, {';', 0}, {'=', 0}, {'[', 0}, {'\\', 0}, {']', 0}, {'`', 0}
    };

    std::unordered_map<char, bool> key_down = {
        {'A', false}, {'B', false}, {'C', false}, {'D', false}, {'E', false}, {'F', false}, {'G', false}, {'H', false}, {'I', false}, {'J', false},
        {'K', false}, {'L', false}, {'M', false}, {'N', false}, {'O', false}, {'P', false}, {'Q', false}, {'R', false}, {'S', false}, {'T', false},
        {'U', false}, {'V', false}, {'W', false}, {'X', false}, {'Y', false}, {'Z', false},
        {'0', false}, {'1', false}, {'2', false}, {'3', false}, {'4', false}, {'5', false}, {'6', false}, {'7', false}, {'8', false}, {'9', false},

        {' ', false}, {'\'', false}, {',', false}, {'-', false}, {'.', false}, {'/', false}, {';', false}, {'=', false}, {'[', false}, {'\\', false}, {']', false}, {'`', false}
    };

    std::unordered_map<std::string, uint32_t> special_key_held = {
        {"ESCAPE",    0}, {"ENTER",       0}, {"TAB",      0}, {"BACKSPACE",    0},
        {"INSERT",    0}, {"DELETE",      0},
        {"RIGHT",     0}, {"LEFT",        0}, {"DOWN",     0}, {"UP",           0},
        {"PAGE_UP",   0}, {"PAGE_DOWN",   0}, {"HOME",     0}, {"END",          0},
        {"CAPS_LOCK", 0}, {"SCROLL_LOCK", 0}, {"NUM_LOCK", 0}, {"PRINT_SCREEN", 0}, {"PAUSE", 0},
    };

    std::unordered_map<std::string, bool> special_key_down = {
        {"ESCAPE",    false}, {"ENTER",       false}, {"TAB",      false}, {"BACKSPACE",    false},
        {"INSERT",    false}, {"DELETE",      false},
        {"RIGHT",     false}, {"LEFT",        false}, {"DOWN",     false}, {"UP",           false},
        {"PAGE_UP",   false}, {"PAGE_DOWN",   false}, {"HOME",     false}, {"END",          false},
        {"CAPS_LOCK", false}, {"SCROLL_LOCK", false}, {"NUM_LOCK", false}, {"PRINT_SCREEN", false}, {"PAUSE", false},
    };

    std::array<uint32_t, 25> function_key_held = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    std::array<bool, 25> function_key_down = { false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false };

    std::array<uint32_t, 10> keypad_key_held = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    std::array<bool, 10> keypad_key_down = { false, false, false, false, false, false, false, false, false, false };

    std::unordered_map<std::string, uint32_t> special_keypad_key_held = {
        {"DECIMAL", 0}, {"DIVIDE", 0}, {"MULTIPLY", 0}, {"SUBTRACT", 0}, {"ADD", 0}, {"ENTER", 0}, {"EQUAL", 0}
    };

    std::unordered_map<std::string, bool> special_keypad_key_down = {
        {"DECIMAL", false}, {"DIVIDE", false}, {"MULTIPLY", false}, {"SUBTRACT", false}, {"ADD", false}, {"ENTER", false}, {"EQUAL", false}
    };

    std::unordered_map<std::string, uint32_t> control_keys_held = {
        {"LEFT_SHIFT",  0}, {"LEFT_CONTROL",  0},  {"LEFT_ALT",  0}, {"LEFT_SUPER",  0},
        {"RIGHT_SHIFT", 0}, {"RIGHT_CONTROL", 0},  {"RIGHT_ALT", 0}, {"RIGHT_SUPER", 0},
        {"MENU",        0}
    };

    std::unordered_map<std::string, bool> control_keys_down = {
        {"LEFT_SHIFT",  false}, {"LEFT_CONTROL",  false},  {"LEFT_ALT",  false}, {"LEFT_SUPER",  false},
        {"RIGHT_SHIFT", false}, {"RIGHT_CONTROL", false},  {"RIGHT_ALT", false}, {"RIGHT_SUPER", false},
        {"MENU",        false}
    };

    IDENTIFYKEY8(A, B, C, D, E, F, G, H)
    IDENTIFYKEY8(I, J, K, L, M, N, O, P)
    IDENTIFYKEY8(Q, R, S, T, U, V, W, X)
    IDENTIFYKEY8(Y, Z, 0, 1, 2, 3, 4, 5)
    IDENTIFYKEY8(6, 7, 8, 9, RIGHT, LEFT, DOWN, UP)
    IDENTIFYKEY8(ESCAPE, ENTER, TAB, BACKSPACE, COMMA, PERIOD, SPACE, SLASH)
private:
    GLFWwindow *window_ref;
};
} // namespace luna

#endif // LUNA_KEYBOARD_HPP
