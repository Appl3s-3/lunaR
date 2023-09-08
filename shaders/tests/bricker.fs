#version 330 core

uniform vec3 cell_colour;

out vec4 final;

in vec4 vertex_colour;

void main() {
    final = vec4(cell_colour.xyz, 1.0);
}
