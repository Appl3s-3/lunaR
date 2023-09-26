#ifndef LUNA_BUFFER_MANAGER_HPP
#define LUNA_BUFFER_MANAGER_HPP

#include "luna/miniGL.h"

namespace luna {

/**
 * @brief Manages a generic OpenGL buffer object.
 */
class BufferManager {
public:
    /**
     * @brief Construct a new Buffer Manager object.
     * Prepares an OpenGL buffer object for the specified target.
     * @param buffer_target The OpenGL target of the buffer object.
     * @param buffer_usage  How the buffer should be used in draw calls,
     *                      defaults to GL_STATIC_DRAW.
     */
    BufferManager(GLenum buffer_target,
                  GLenum buffer_usage = GL_STATIC_DRAW);

    /**
     * @brief Destroy the Buffer Manager object.
     * Deletes the buffer.
     */
    ~BufferManager();

    /**
     * @brief Binds the OpenGL buffer object to the buffer target.
     */
    void bind() const;

    /**
     * @brief Unbinds buffers bound to the buffer target.
     */
    void unbind() const;

    /**
     * @brief Returns the reference to the OpenGL buffer as a GLuint.
     * @return GLuint: The reference to the OpenGL buffer.
     */
    GLuint name() const;

    /**
     * @brief Returns the stored buffer target.
     * @return GLenum: The stored buffer target.
     */
    GLenum target() const;

    /**
     * @brief Reserves buffer space.
     * Reserves buffer space and relenquishes access to the previous buffer
     * data. Changes the capacity of the buffer.
     * @param size The new size of the buffer in bytes.
     */
    void reserve(GLsizeiptr size);

    /**
     * @brief Uploads data to the buffer.
     * Uploads data to the buffer. Fails if (offset + size) is greater than
     * the capacity of the buffer.
     * @param offset Offset (bytes) from the start of the buffer to begin
     *               the upload.
     * @param size   Size (bytes) to upload to the buffer.
     * @param data   A pointer to the data to upload.
     */
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