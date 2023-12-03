#ifndef LUNA_SHADER_HPP
#define LUNA_SHADER_HPP

#include <iostream>
#include <vector>

#include "luna/miniGL.h"
#include "luna/LunaDefines.hpp"

namespace luna {

enum class ShaderType {
    VERTEX = 0,
    GEOMETRY,
    FRAGMENT
};

/**
 * @brief Manages an OpenGL shader.
 */
class Shader {
public:
    /**
     * @brief Construct a new Shader object.
     * Creates an OpenGL shader object of the given type.
     * @param type The type of shader to create.
     */
    Shader(const ShaderType type);

    /**
     * @brief Destroy the Shader object.
     * Deletes the shader.
     */
    ~Shader();

    /**
     * @brief Append a shader source to the shader.
     * @param source The source to append.
     */
    void append_source(const std::string& source);

    /**
     * @brief Compiles the shader sources and clears the list of sources.
     * @return true  on success.
     * @return false otherwise.
     */
    bool compile();
    
    GLuint shader_name = 0;
    ShaderType shader_type = ShaderType::VERTEX;
    GLenum shader_internal_type = GL_VERTEX_SHADER;
    std::vector<const GLchar*> shader_sources;
};

} // namespace luna

#endif // LUNA_SHADER_HPP
