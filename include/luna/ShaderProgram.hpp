#if !defined(LUNA_SHADER_PROGRAM_HPP)
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
        ShaderProgram(const Shader& vertex_shader, const Shader& fragment_shader);
        ~ShaderProgram();

        inline void bind() const { glUseProgram(name); }

        // ShaderUniforms uniforms;

    private:
        GLuint name;
        // std::vector<Texture*> textures;
    };
}

#endif // LUNA_SHADER_PROGRAM_HPP
