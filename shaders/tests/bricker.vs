#version 330 core

layout (location = 0) in vec2 a_position;
layout (location = 1) in vec4 a_colour;

out vec4 vertex_colour;

void main() {
    // Pass-through attributes
    vertex_colour = a_colour;

    gl_Position = vec4(a_position.xy, 0.0, 1.0);
}
