#include "luna/ShaderUniforms.hpp"

using namespace luna;

ShaderUniforms::ShaderUniforms(GLuint _program_name) : program_name(_program_name) { }

void ShaderUniforms::add_uniform(std::string name) {
    GLint location = glGetUniformLocation(program_name, name.c_str());
    if (location == -1) {
        std::cout << LUNA_CREATION_ERROR "Failed to get uniform location for program [" << program_name << "] name [" + name << std::endl;
        return;
    }

    uniform_locations[name] = location;
}