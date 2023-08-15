#version 330 core

out vec4 final;

in vec4 vertex_colour;

void main() {
    final = vec4(vertex_colour.xyz, 1.0);
}
