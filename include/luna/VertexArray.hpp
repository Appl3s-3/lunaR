#ifndef LUNA_VERTEX_ARRAY_HPP
#define LUNA_VERTEX_ARRAY_HPP

#include <iostream>
#include <cstddef>
#include <unordered_map>

#include "luna/miniGL.h"
#include "luna/BufferManager.hpp"
// #include "IndexBuffer.hpp"
#include "luna/LunaDefines.hpp"

namespace luna {

struct AttributeInfo {
    GLuint bindingindex = 0;
    DataType type = DataType::Unknown;
    GLsizei stride = 0;
};

struct VertexAttributeInfo {
    GLuint index = 0;
    GLint size = 1;
    DataType type = DataType::Unknown;
    GLboolean normalized = GL_FALSE;
    GLsizei stride = 0;
};

/*
 * VertexArray
 */
class VertexArray {
public:
    VertexArray();
    ~VertexArray();

    void bind();
    void unbind();

    void define_attribute(BufferManager buffer,
                          VertexAttributeInfo info,
                          uint64_t offset);
    
    // Draw using DrawArrays
    void draw_arrays(GLenum mode, GLint first, GLsizei count) const;

    // Draw the whole vertex array
    // void draw() const;
    
    // Draw a portion of the vertex array
    void draw(uint64_t start_index, GLsizei count) const;

    // Draw a portion of the vertex array and offset indices by basevertex
    void draw(uint64_t start_index, GLsizei count, GLint basevertex) const;

    // void specify_attribute(GLuint attribindex, DataType type);

    // void vbo_binding(GLuint bindingindex, VertexBuffer vbo_manager, std::size_t attribute_location) const;

private:
    GLint datatype_size(DataType attribute_type) const;
    GLenum datatype_type(DataType attribute_type) const;
    GLsizei datatype_type_size(DataType attribute_type) const;
    GLboolean datatype_normalized(DataType attribute_type) const;

    GLuint array_name;
    // IndexBuffer* element_buffer = NULL;

    std::unordered_map<GLuint, AttributeInfo> attribute_info;
};

} // namespace luna

#endif // LUNA_VERTEX_ARRAY_HPP