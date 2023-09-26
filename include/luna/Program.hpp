#ifndef LUNA_SHADER_PROGRAM_HPP
#define LUNA_SHADER_PROGRAM_HPP

#include <string>

#include "luna/miniGL.h"
#include "luna/Shader.hpp"
#include "luna/ShaderUniforms.hpp"
// #include "luna/Texture.hpp"
#include "luna/LunaDefines.hpp"

namespace luna {

/**
 * @brief Manages an OpenGL program object.
 */
class Program {
public:
    /**
     * @brief Construct a new Program object.
     * Creates an OpenGL program object.
     */
    Program();
    
    /**
     * @brief Destroy the Program object.
     * Deletes the program object.
     */
    ~Program();

    /**
     * @brief Installs the program object.
     */
    void use() const;

    /**
     * @brief Uninstalls all programs.
     */
    static void uninstall();

    /**
     * @brief Returns the reference to the OpenGL program as a GLuint.
     * @return GLuint: The reference to the OpenGL program.
     */
    GLuint name() const;

    /**
     * @brief Attaches a shader object to the program object.
     * @param shader The shader to attach.
     */
    void attach_shader(const Shader& shader) const;

    /**
     * @brief Links the shaders attached to the program object.
     * @return GL_TRUE  on success.
     * @return GL_FALSE on failure.
     */
    GLint link() const;

    /**
     * @brief Returns a string of the program info log.
     * @return std::string: The program info log.
     */
    std::string info_log() const;

    // ShaderUniforms uniforms;

private:
    GLuint program_name;
    // std::vector<Texture*> textures;
};

} // namespace luna

#endif // LUNA_SHADER_PROGRAM_HPP
