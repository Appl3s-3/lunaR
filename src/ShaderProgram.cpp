#include "luna/ShaderProgram.hpp"

using namespace luna;

ShaderProgram::ShaderProgram() {
    program_name = glCreateProgram();
}

ShaderProgram::ShaderProgram(const Shader& vertex_shader, const Shader& fragment_shader) {
    program_name = glCreateProgram();
    // uniforms = ShaderUniforms(name);

    glAttachShader(program_name, fragment_shader.shader_name);
    glLinkProgram(program_name);

    int32_t success;
    char infoLog[512];
    glGetProgramiv(program_name, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(program_name, 512, NULL, infoLog);
        std::cout << LUNA_CREATION_ERROR "Failed to link shader program.\n" << infoLog << std::endl;
    }
}

ShaderProgram::~ShaderProgram() {
    glDeleteProgram(program_name);
}

void ShaderProgram::attach_shader(const Shader& shader) const {
    bind();

    glAttachShader(program_name, shader.shader_name);
    
    unbind();
}

void ShaderProgram::link() const {
    bind();

    glLinkProgram(program_name);

    int32_t success = 0;
    char info_log[512];
    glGetProgramiv(program_name, GL_LINK_STATUS, &success);
    if (success == false) {
        glGetProgramInfoLog(program_name, 512, NULL, info_log);
        std::cout << LUNA_CREATION_ERROR "Failed to link shader program.\n" << info_log << std::endl;
    }

    unbind();
}

void ShaderProgram::bind() const {
    glUseProgram(program_name);
}

void ShaderProgram::unbind() const {
    glUseProgram(0);
}

GLuint ShaderProgram::name() const {
    return program_name;
}

