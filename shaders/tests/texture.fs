#version 330 core

out vec4 final;

in vec2 vertex_uv;

uniform sampler2D quad_texture;

void main() {
    final = texture(quad_texture, vertex_uv);
}
