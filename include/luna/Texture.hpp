#if !defined(LUNA_TEXTURE_HPP)
#define LUNA_TEXTURE_HPP

#include <iostream>
#include <cstdint>
#include <vector>

#include "qoi.h"
#include "stb_image.h"
#include "miniGL.h"
#include "LunaDefines.hpp"

namespace luna {
    class Texture {
    public:
        Texture(const uint32_t unit_number);
        ~Texture();

        inline void bind() const { 
            glActiveTexture(unit);
            glBindTexture(GL_TEXTURE_2D, name);
        }

        inline void unbind() const {
            glActiveTexture(unit);
            glBindTexture(GL_TEXTURE_2D, 0);
        }

        void allocate(GLsizei width, GLsizei height, uint32_t channels = 3) const;
        void from_qoi(std::string filename) const;

        void mipmap(const GLint minify_filter = GL_NEAREST_MIPMAP_NEAREST, const GLint magnify_filter = GL_LINEAR) const;
        void wrap(const GLint wrap_s = GL_CLAMP_TO_EDGE, const GLint wrap_t = GL_CLAMP_TO_EDGE) const;

        GLuint name;
    private:
        GLenum unit;
    };

    // class Texture {
    // public:
    //     Texture(const uint32_t units = 1);
    //     ~Texture();

    //     void bind(const uint32_t texture_unit = 0);
    //     void unbind(const uint32_t texture_unit = 0);

    //     void set_unit_from_file(const char *filename, int32_t width, int32_t height, const uint32_t texture_unit = 0, const GLint internalformat = GL_RGBA, const GLenum format = GL_RGBA, const GLenum type = GL_UNSIGNED_BYTE, int32_t channels = 0);
    //     void set_unit_from_buffer(void* buffer, int32_t width, int32_t height, const uint32_t texture_unit = 0, const GLint internalformat = GL_RGBA, const GLenum format = GL_RGBA, const GLenum type = GL_UNSIGNED_BYTE, int32_t channels = 0);

    //     void set_filters(const GLint minify_filter = GL_NEAREST_MIPMAP_LINEAR, const GLint magnify_filter = GL_LINEAR, const uint32_t texture_unit = 0);
    //     void set_wrapping(const GLint wrap_s = GL_REPEAT, const GLint wrap_t = GL_REPEAT, const GLint wrap_r = GL_REPEAT, const uint32_t texture_unit = 0);

    // private:
    //     GLuint texture_id;
    //     std::vector<GLenum> texture_type;
    //     uint32_t total_units;
    // };
}

#endif // LUNA_TEXTURE_HPP
