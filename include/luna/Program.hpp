#ifndef LUNA_SHADER_PROGRAM_HPP
#define LUNA_SHADER_PROGRAM_HPP

#include <string>

#include "luna/miniGL.h"
#include "luna/Shader.hpp"
#include "luna/ShaderUniforms.hpp"
// #include "luna/Texture.hpp"
#include "luna/LunaDefines.hpp"

namespace luna {

// Program
// Manages an OpenGL program object
class Program {
public:
    // Program Constructor
    // Creates an OpenGL program object
    Program();

    // archive
    // Program(const Shader& vertex_shader, const Shader& fragment_shader);

    // Program Destructor
    // Deletes the program object
    ~Program();

    // use
    // Installs the program object
    void use() const;

    // uninstall
    // Uninstalls all programs
    static void uninstall() const;

    // name
    // Returns the reference to the OpenGL program as a GLuint
    GLuint name() const;

    // attach_shader
    // Attaches a shader object to the program object
    // :: const Shader& shader :: The shader to attach
    void attach_shader(const Shader& shader) const;

    // link
    // Links the shaders attached to the program object
    // Returns GL_TRUE on success and GL_FALSE on failure
    bool link() const;

    // info_log
    // Returns a string of the program info log
    std::string info_log();

    // ShaderUniforms uniforms;

private:
    GLuint program_name;
    // std::vector<Texture*> textures;
};

} // namespace luna

#endif // LUNA_SHADER_PROGRAM_HPP
