#include "VertexBuffer.hpp"

using namespace luna;

VertexBuffer::VertexBuffer(GLsizeiptr size, GLenum _usage)
    :   byte_capacity(size), usage(_usage) {
    glGenBuffers(1, &buffer_name);
    bind();
    
    attribute_offsets.push_back(0);
    glBufferData(GL_ARRAY_BUFFER, byte_capacity, NULL, usage);
}

VertexBuffer::~VertexBuffer() {
    glDeleteBuffers(1, &buffer_name);
}

void VertexBuffer::bind() const {
    glBindBuffer(GL_ARRAY_BUFFER, buffer_name);
}

GLuint VertexBuffer::name() const {
    return buffer_name;
}