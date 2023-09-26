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

// Shader
// Manages an OpenGL shader
class Shader {
public:
    // Shader Constructor
    // Creates an OpenGL shader object of the given type
    // :: const ShaderType type :: The type of shader to create
    Shader(const ShaderType type);

    // archive
    Shader(const GLenum type, const char* source, const SourceText source_type = SourceText::file);

    // Shader Destructor
    // Deletes the shader
    ~Shader();

    // append_source
    // Append a shader source to the shader
    // :: const std::string& source :: The source to append
    void append_source(const std::string& source);

    // compile
    // Compiles the shader sources and clears the list of sources
    // Returns true on success and false otherwise
    bool compile();
    
    // archive
    char *read_file(const char *filepath);

    // archive
    GLuint create_shader(const GLenum type, const char *source);

    GLuint shader_name = 0;
    ShaderType shader_type = ShaderType::VERTEX;
    GLenum shader_internal_type = GL_VERTEX_SHADER;
    std::vector<const GLchar*> shader_sources;
};

} // namespace luna

#endif // LUNA_SHADER_HPP
