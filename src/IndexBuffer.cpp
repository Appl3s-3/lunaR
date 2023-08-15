#include "IndexBuffer.hpp"

using namespace luna;

IndexBuffer::IndexBuffer(std::size_t triangle_count)
    :   index_capacity(triangle_count * 3) {
    glGenBuffers(1, &buffer_name);
    bind();
    
    GLsizeiptr size = index_capacity * sizeof(GLuint);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, NULL, GL_STATIC_DRAW);
}

IndexBuffer::~IndexBuffer() {
    glDeleteBuffers(1, &buffer_name);
}

void IndexBuffer::generate_triangles() {
    std::size_t total_triangles = (index_capacity - used_indices) / 3;
    std::size_t offset = indices.empty() ? 0 : indices[used_indices - 1];

    std::vector<GLuint> triangles;
    for (std::size_t i = used_indices; i < total_triangles; ++i) {
        triangles.push_back(offset + 0);
        triangles.push_back(offset + 1);
        triangles.push_back(offset + 2);

        ++offset;
    }

    append(triangles);
}

void IndexBuffer::generate_rectangles() {
    std::size_t total_rectangles = (index_capacity - used_indices) / 6;
    std::size_t offset = indices.empty() ? 0 : indices[used_indices - 1];

    std::vector<GLuint> triangles;
    for (std::size_t i = used_indices; i < total_rectangles; ++i) {
        triangles.push_back(offset + 0);
        triangles.push_back(offset + 1);
        triangles.push_back(offset + 2);

        triangles.push_back(offset + 1);
        triangles.push_back(offset + 2);
        triangles.push_back(offset + 3);

        offset += 4;
    }

    append(triangles);
}

void IndexBuffer::append(const std::vector<GLuint>& _indices) {
    const std::size_t new_used_indices = used_indices + _indices.size();

    if (new_used_indices > index_capacity) {
        std::cout << "Error: void IndexBuffer::append(const std::vector<GLuint>& _indices) has not implemented resizing. new_used_indices: " << new_used_indices << ", index_capacity: " << index_capacity << std::endl;
        return;
    }

    const std::size_t indices_size = _indices.size() * sizeof(GLuint);
    const std::size_t new_used_space = used_space + indices_size;

    bind();
    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, used_space, indices_size, _indices.data());

    used_indices = new_used_indices;
    used_space = new_used_space;
}
