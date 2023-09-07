#ifndef LUNA_SHADER_HPP
#define LUNA_SHADER_HPP

#include <iostream>
#include <vector>

#include "luna/miniGL.h"
#include "luna/LunaDefines.hpp"

namespace luna {

enum class ShaderType {
    VERTEX = 0,
    FRAGMENT
};

class Shader {
public:
    Shader(const ShaderType type);
    Shader(const GLenum type, const char* source, const SourceText source_type = SourceText::file);
    ~Shader();

    void append_source(const std::string& source);
    bool compile();
    
    char *read_file(const char *filepath);
    GLuint create_shader(const GLenum type, const char *source);

    GLuint shader_name = 0;
    ShaderType shader_type = ShaderType::VERTEX;
    GLenum shader_internal_type = GL_VERTEX_SHADER;
    std::vector<const GLchar*> shader_sources;
};

} // namespace luna

#endif // LUNA_SHADER_HPP
