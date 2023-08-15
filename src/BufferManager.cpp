#include "luna/BufferManager.hpp"

using namespace luna;

BufferManager::BufferManager(GLenum buffer_target,
                             GLenum buffer_usage)
    :   buffer_target(buffer_target),
        buffer_usage(buffer_usage) {
    glGenBuffers(1, &buffer_name);
}

BufferManager::~BufferManager() {
    glDeleteBuffers(1, &buffer_name); // TODO
}

void BufferManager::bind() {
    glBindBuffer(buffer_target, buffer_name);
}

void BufferManager::unbind() {
    glBindBuffer(buffer_target, 0);
}

GLuint BufferManager::name() const {
    return buffer_name;
}

GLenum BufferManager::target() const {
    return buffer_target;
}

void BufferManager::reserve(GLsizeiptr size) {
    bind();
    glBufferData(buffer_target,
                 size,
                 NULL,
                 buffer_usage);
    unbind();

    capacity = size;
}

void BufferManager::upload(GLintptr offset, GLsizeiptr size, const void* data) {
    if ((offset + size) > capacity) {
        return;
    }

    bind();
    glBufferSubData(buffer_target,
                    offset,
                    size,
                    data);
    unbind();
}