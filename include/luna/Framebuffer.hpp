#if !defined(LUNA_FRAMEBUFFER_HPP)
#define LUNA_FRAMEBUFFER_HPP

#include "miniGL.h"
#include "Texture.hpp"

namespace luna {
    class Framebuffer {
    public:
        Framebuffer(GLsizei width, GLsizei height);
        ~Framebuffer();

        inline void bind() const { glBindFramebuffer(GL_FRAMEBUFFER, name); }
        inline void bind_texture() const { buffer.bind(); }
        
        inline void unbind() const {
            glBindFramebuffer(GL_FRAMEBUFFER, 0);
            buffer.unbind();
        }

    private:
        GLuint name;
        Texture buffer;
    };
}

#endif // LUNA_FRAMEBUFFER_HPP