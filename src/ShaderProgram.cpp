#include "luna/ShaderProgram.hpp"

using namespace luna;

ShaderProgram::ShaderProgram(const Shader& vertex_shader, const Shader& fragment_shader) {
    name = glCreateProgram();
    // uniforms = ShaderUniforms(name);

    glAttachShader(name, vertex_shader.shader_id);
    glAttachShader(name, fragment_shader.shader_id);
    glLinkProgram(name);

    int32_t success;
    char infoLog[512];
    glGetProgramiv(name, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(name, 512, NULL, infoLog);
        std::cout << LUNA_CREATION_ERROR "Failed to link shader program.\n" << infoLog << std::endl;
    }
}

ShaderProgram::~ShaderProgram() {
    glDeleteProgram(name);
}