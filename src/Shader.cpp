#include "luna/Shader.hpp"

using namespace luna;

Shader::Shader(const ShaderType type)
    :   shader_type(type) {
    switch (shader_type) {
    case ShaderType::VERTEX:
        shader_internal_type = GL_VERTEX_SHADER;
        break;

    case ShaderType::GEOMETRY:
        shader_internal_type = GL_GEOMETRY_SHADER;
        break;

    case ShaderType::FRAGMENT:
        shader_internal_type = GL_FRAGMENT_SHADER;
        break;
    }

    shader_name = glCreateShader(shader_internal_type);
}

Shader::~Shader() {
    glDeleteShader(shader_name);
}

void Shader::append_source(const std::string& source) {
    shader_sources.push_back(source.c_str());
}

bool Shader::compile() {
    // There are no shader sources to compile
    if (shader_sources.size() == 0) {
        std::cout << "Error, no shader sources to compile." << std::endl;
    }

    // Add the sources
    glShaderSource(shader_name,
                   shader_sources.size(),
                   shader_sources.data(),
                   NULL);
    
    // Compile the shader
    glCompileShader(shader_name);

    // Error Handling
    int32_t success = 0;
    glGetShaderiv(shader_name, GL_COMPILE_STATUS, &success);

    if (success == false) {
        GLchar info_log[512];
        glGetShaderInfoLog(shader_name, 512, NULL, info_log);

        printf(LUNA_CREATION_ERROR "Failed to compile %d shader.\n%s\n", (int)shader_type, info_log);
        return false;
    }

    // Compilation was successful, clear the sources
    shader_sources.clear();

    return true;
}
