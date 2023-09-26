#version 330 core

out vec2 vertex_uv;

layout (location = 0) in vec2 a_position;
layout (location = 1) in vec2 a_uv;

void main() {
    // Pass-through attributes
    vertex_uv = a_uv;

    gl_Position = vec4(a_position.xy, 0.0, 1.0);
}
