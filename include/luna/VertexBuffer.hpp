#if !defined(LUNA_VERTEX_BUFFER_HPP)
#define LUNA_VERTEX_BUFFER_HPP

#include <cstddef>
#include <iostream>

#include "VertexAttribute.hpp"
#include "miniGL.h"

namespace luna {

/*
 * VertexBuffer
 */
class VertexBuffer {
public:
    VertexBuffer(GLsizeiptr size, GLenum _usage = GL_STATIC_DRAW);
    ~VertexBuffer();

    void bind() const;
    GLuint name() const;

    template <class GLDataType>
    void append(VertexAttribute<GLDataType>& attribute) {
        const std::size_t attribute_size = attribute.size();
        const std::size_t new_used_bytes = used_bytes + attribute_size;

        if (new_used_bytes > byte_capacity) {
            std::cout << "Error: void VertexBuffer::append(const AttributeContainer<GLDataType>& attribute) has not implemented resizing. new_used_bytes: " << new_used_bytes << ", byte_capacity: " << byte_capacity << std::endl;
            return;
        }

        attribute.vbo = name();
        attribute.start_offset = used_bytes;
        attribute.expected_size = attribute_size;

        bind();
        glBufferSubData(GL_ARRAY_BUFFER, used_bytes, attribute_size, attribute.data());

        used_bytes = new_used_bytes;
        attribute_offsets.push_back(used_bytes);
    }

    template <class GLDataType>
    void modify(const VertexAttribute<GLDataType>& attribute) {
        if (attribute.vbo != name()) {
            std::cout << "Error: Failed to modify vbo. attribute.vbo " << attribute.vbo << " does not match buffer_name " << name() << "." << std::endl;
            return;
        }

        if (attribute.expected_size != attribute.size()) {
            std::cout << "Warning: attribute.expected_size " << attribute.expected_size << " is not equal to the attribute's current size " << attribute.size() << ". Using expected size to avoid overflow." << std::endl;
        }

        bind();
        glBufferSubData(GL_ARRAY_BUFFER, attribute.start_offset, attribute.expected_size, attribute.data());
    }

    // TODO: move into vertex attributes
    std::vector<GLintptr> attribute_offsets;

private:
    GLuint buffer_name;
    GLenum usage; // used to be const

    std::size_t byte_capacity;
    std::size_t used_bytes = 0;
};

} // namespace luna

#endif // LUNA_VERTEX_BUFFER_HPP