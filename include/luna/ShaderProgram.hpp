#ifndef LUNA_SHADER_PROGRAM_HPP
#define LUNA_SHADER_PROGRAM_HPP

#include <iostream>
#include <string>

#include "luna/miniGL.h"
#include "luna/Shader.hpp"
#include "luna/ShaderUniforms.hpp"
// #include "luna/Texture.hpp"
#include "luna/LunaDefines.hpp"

namespace luna {

class ShaderProgram {
public:
    ShaderProgram();
    ShaderProgram(const Shader& vertex_shader, const Shader& fragment_shader);
    ~ShaderProgram();

    void attach_shader(const Shader& shader) const;

    void link() const;

    void bind() const;
    void unbind() const;

    GLuint name() const;

    // ShaderUniforms uniforms;

private:
    GLuint program_name;
    // std::vector<Texture*> textures;
};

} // namespace luna

#endif // LUNA_SHADER_PROGRAM_HPP
