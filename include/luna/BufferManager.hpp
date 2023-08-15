#ifndef LUNA_BUFFER_MANAGER_HPP
#define LUNA_BUFFER_MANAGER_HPP

#include "luna/miniGL.h"

namespace luna {

class BufferManager {
public:
    BufferManager(GLenum buffer_target,
                  GLenum buffer_usage = GL_STATIC_DRAW);
    ~BufferManager();

    void bind();
    void unbind();

    GLuint name() const;
    GLenum target() const;

    void reserve(GLsizeiptr size);
    void upload(GLintptr offset,
                GLsizeiptr size,
                const void* data);

private:
    GLuint buffer_name = 0;
    GLenum buffer_target = GL_ARRAY_BUFFER;
    GLenum buffer_usage = GL_STATIC_DRAW;

    GLsizeiptr capacity = 0;
};

} // namespace luna

#endif // LUNA_BUFFER_MANAGER_HPP