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

// VertexArray
// Manages an OpenGL Vertex Array Object (VAO)
class VertexArray {
public:
    // VertexArray Constructor
    // Generates an OpenGL vertex array object
    VertexArray();
    
    // VertexArray Destructor
    // Deletes the vertex array object
    ~VertexArray();

    // bind
    // Binds the vertex array object
    void bind() const;

    // unbind
    // Unbinds all vertex array objects
    static void unbind();

    // name
    // Returns the reference to the OpenGL vertex array as a GLuint
    GLuint name() const;

    // define_attribute
    // Enables a vertex attribute for the vertex array object and binds a
    // GL_ARRAY_BUFFER to the attribute.
    // :: const BufferManager&       buffer :: The GL_ARRAY_BUFFER to source
    //                                         vertex data from
    // :: const VertexAttributeInfo& info   :: Vertex format information
    // ::       uint64_t             offset :: Offset (bytes) from...
    //                                         Defaults to 0
    void define_attribute(const BufferManager& buffer,
                          const VertexAttributeInfo& info,
                          uint64_t offset = 0) const;

    // void do_this_one_thing(const VertexAttributeInfo& info,
    //                        uint64_t offset = 0);

    // void bind_vbo(const BufferManager& buffer,
    //               GLuint binding_index,
    //               GLintptr offset,
    //               GLsizei stride);
    
    // draw_arrays
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
    GLuint array_name;

    // semi-archive
    GLint datatype_size(DataType attribute_type) const;
    GLenum datatype_type(DataType attribute_type) const;
    GLsizei datatype_type_size(DataType attribute_type) const;
    GLboolean datatype_normalized(DataType attribute_type) const;

    // IndexBuffer* element_buffer = NULL;

    // std::unordered_map<GLuint, AttributeInfo> attribute_info;
};

} // namespace luna

#endif // LUNA_VERTEX_ARRAY_HPP