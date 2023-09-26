#ifndef LUNA_BUFFER_MANAGER_HPP
#define LUNA_BUFFER_MANAGER_HPP

#include "luna/miniGL.h"

namespace luna {

// BufferManager
// Manages a generic OpenGL buffer object
class BufferManager {
public:
    // BufferManager Constructor
    // Prepares an OpenGL buffer object for the specified target
    // :: GLenum buffer_target :: The OpenGL target of the buffer object
    // :: GLenum buffer_usage  :: How the buffer should be used in draw calls.
    //                            Default value is GL_STATIC_DRAW
    BufferManager(GLenum buffer_target,
                  GLenum buffer_usage = GL_STATIC_DRAW);

    // BufferManager Destructor
    // Deletes the buffer
    ~BufferManager();

    // bind
    // Binds the OpenGL buffer object to the buffer target
    void bind() const;

    // unbind
    // Unbinds buffers bound to the buffer target
    void unbind() const;

    // name
    // Returns the reference to the OpenGL buffer as a GLuint
    GLuint name() const;

    // target
    // Returns the stored buffer target
    GLenum target() const;

    // reserve
    // Reserves buffer space and relenquishes access to the previous buffer
    // data. Changes the capacity of the buffer.
    // :: GLsizeiptr size :: The new size of the buffer in bytes
    void reserve(GLsizeiptr size);

    // upload
    // Uploads data to the buffer. Fails if offset + size is greater than the
    // capacity of the buffer.
    // ::       GLintptr   offset :: Offset (bytes) from the start of the
    //                               buffer to begin the upload
    // ::       GLsizeiptr size   :: Size (bytes) to upload to the buffer
    // :: const void*      data   :: A pointer to the data to upload
    void upload(GLintptr offset,
                GLsizeiptr size,
                const void* data) const;

private:
    GLenum buffer_target = GL_ARRAY_BUFFER;
    GLuint buffer_name = 0;
    
    GLenum buffer_usage = GL_STATIC_DRAW;

    GLsizeiptr capacity = 0;
};

} // namespace luna

#endif // LUNA_BUFFER_MANAGER_HPP