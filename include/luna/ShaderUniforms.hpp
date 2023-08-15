#if !defined(LUNA_SHADER_UNIFORMS_HPP)
#define LUNA_SHADER_UNIFORMS_HPP

#include <iostream>
#include <string>
#include <unordered_map>

#include "glm/glm.hpp"
#include "LunaDefines.hpp"
#include "miniGL.h"

namespace luna {
    class ShaderUniforms {
    public:
        ShaderUniforms(GLuint _program_name = 0);

        void add_uniform(std::string name);
        inline GLint location(std::string name) const { return uniform_locations.at(name); }

        inline void set_f1(std::string name, GLfloat data)   const { glUniform1f(location(name), data); }
        inline void set_f2(std::string name, glm::vec2 data) const { glUniform2f(location(name), data.x, data.y); }
        inline void set_f3(std::string name, glm::vec3 data) const { glUniform3f(location(name), data.x, data.y, data.z); }
        inline void set_f4(std::string name, glm::vec4 data) const { glUniform4f(location(name), data.x, data.y, data.z, data.w); }

        inline void set_i1(std::string name, GLint data)      const { glUniform1i(location(name), data); }
        inline void set_i2(std::string name, glm::ivec2 data) const { glUniform2i(location(name), data.x, data.y); }
        inline void set_i3(std::string name, glm::ivec3 data) const { glUniform3i(location(name), data.x, data.y, data.z); }
        inline void set_i4(std::string name, glm::ivec4 data) const { glUniform4i(location(name), data.x, data.y, data.z, data.w); }

        inline void set_u1(std::string name, GLuint data)     const { glUniform1ui(location(name), data); }
        inline void set_u2(std::string name, glm::uvec2 data) const { glUniform2ui(location(name), data.x, data.y); }
        inline void set_u3(std::string name, glm::uvec3 data) const { glUniform3ui(location(name), data.x, data.y, data.z); }
        inline void set_u4(std::string name, glm::uvec4 data) const { glUniform4ui(location(name), data.x, data.y, data.z, data.w); }

        inline void set_mat2(std::string name, glm::mat2 data, GLsizei count = 1, GLboolean transpose = false) const { glUniformMatrix2fv(location(name), count, transpose, &data[0][0]); }
        inline void set_mat3(std::string name, glm::mat3 data, GLsizei count = 1, GLboolean transpose = false) const { glUniformMatrix3fv(location(name), count, transpose, &data[0][0]); }
        inline void set_mat4(std::string name, glm::mat4 data, GLsizei count = 1, GLboolean transpose = false) const { glUniformMatrix4fv(location(name), count, transpose, &data[0][0]); }
    
    private:
        GLuint program_name;
        std::unordered_map<std::string, GLint> uniform_locations;
    };
}

#endif // LUNA_SHADER_UNIFORMS_HPP