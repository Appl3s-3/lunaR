#include "luna/VertexArray.hpp"

using namespace luna;

VertexArray::VertexArray() {
    glGenVertexArrays(1, &array_name);
}

VertexArray::~VertexArray() {
    glDeleteVertexArrays(1, &array_name);
}

void VertexArray::bind() const {
    glBindVertexArray(array_name);
}

void VertexArray::unbind() {
    glBindVertexArray(0);
}

void VertexArray::define_attribute(const BufferManager& buffer,
                                   const VertexAttributeInfo& info,
                                   uint64_t offset) const {
    // The buffer target is not vertex attributes
    if (buffer.target() != GL_ARRAY_BUFFER) {
        return;
    }

    bind();
    buffer.bind();

    glEnableVertexAttribArray(info.index);
    glVertexAttribPointer(info.index,
                          info.size,
                          datatype_type(info.type),
                          info.normalized,
                          info.stride,
                          (const void*)(offset));

    unbind();
    buffer.unbind();
}

// void VertexArray::do_this_one_thing(const VertexAttributeInfo& info,
//                                     uint64_t offset) {
//     bind();

//     glEnableVertexAttribArray(info.index);
//     // TODO: change stride to offset in vertex attrib info and replace 0
//     glVertexAttribFormat(info.index,
//                          info.size,
//                          datatype_type(info.type),
//                          info.normalized,
//                          0);
//     glVertexAttribBinding(info.index,
//   	                      info.index);
//     // glVertexAttribPointer(info.index,
//     //                       info.size,
//     //                       datatype_type(info.type),
//     //                       info.normalized,
//     //                       info.stride,
//     //                       (const void*)(offset));

//     unbind();
// }

// void VertexArray::bind_vbo(const BufferManager& buffer,
//                            GLuint binding_index,
//                            GLintptr offset,
//                            GLsizei stride) {
//     // The buffer target is not vertex attributes
//     if (buffer.target() != GL_ARRAY_BUFFER) {
//         return;
//     }

//     glBindVertexBuffer(binding_index,
//                        buffer.name(),
//                        offset,
//                        stride);
// }

void VertexArray::draw_arrays(GLenum mode, GLint first, GLsizei count) const {
    glDrawArrays(mode, first, count);
}

// Draw the whole vertex array
// void VertexArray::draw() const {
//     glDrawElements(GL_TRIANGLES, element_buffer->count(), GL_UNSIGNED_INT, 0);
// }

// Draw a portion of the vertex array
void VertexArray::draw(uint64_t start_index, GLsizei count) const {
    glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, (const void*)start_index);
}

// Draw a portion of the vertex array and offset indices by basevertex
void VertexArray::draw(uint64_t start_index, GLsizei count, GLint basevertex) const {
    glDrawElementsBaseVertex(GL_TRIANGLES, count, GL_UNSIGNED_INT, (const void*)start_index, basevertex);
}

// void VertexArray::specify_attribute(GLuint attribindex, DataType attribute_type) {
//     GLint size           = datatype_size(attribute_type);
//     GLenum type          = datatype_type(attribute_type);
//     GLsizei type_size    = datatype_type_size(attribute_type);
//     GLboolean normalized = datatype_normalized(attribute_type);

//     attribute_info[attribindex] = {attribindex, attribute_type, size * type_size};

//     bind();
//     glVertexAttribFormat(attribindex, size, type, normalized, 0);
//     glVertexAttribBinding(attribindex, attribindex);
//     glEnableVertexAttribArray(attribindex);
// }

// void VertexArray::vbo_binding(GLuint bindingindex, VertexBuffer vbo_manager, std::size_t attribute_location) const {
//     GLuint buffer = vbo_manager.name();
//     GLintptr offset = vbo_manager.attribute_offsets.at(attribute_location);
//     GLsizei stride = attribute_info.at(bindingindex).stride;
//     std::cout << offset << " " << stride << std::endl;

//     bind();
//     glBindVertexBuffer(bindingindex, buffer, offset, stride);
// }

GLint VertexArray::datatype_size(DataType attribute_type) const {
    switch (attribute_type) {
    case DataType::Vec2: case DataType::IVec2: case DataType::UVec2:
        return 2;

    case DataType::Vec3: case DataType::IVec3: case DataType::UVec3:
        return 3;

    case DataType::Vec4: case DataType::IVec4: case DataType::UVec4: case DataType::UCVec4:
        return 4;
    }

    return 1;
}

GLenum VertexArray::datatype_type(DataType attribute_type) const {
    switch (attribute_type) {
    case DataType::Char:
        return GL_BYTE;

    case DataType::UChar: case DataType::UCVec4:
        return GL_UNSIGNED_BYTE;

    case DataType::Int16:
        return GL_SHORT;

    case DataType::Int32: case DataType::IVec2: case DataType::IVec3: case DataType::IVec4:
        return GL_INT;

    case DataType::UInt16: case DataType::UVec2: case DataType::UVec3: case DataType::UVec4:
        return GL_UNSIGNED_SHORT;

    case DataType::UInt32:
        return GL_UNSIGNED_INT;

    case DataType::Float16:
        return GL_HALF_FLOAT;

    case DataType::Float32: case DataType::Vec2: case DataType::Vec3: case DataType::Vec4:
        return GL_FLOAT;

    case DataType::Double:
        return GL_DOUBLE;
    }

    return -1;
}

GLsizei VertexArray::datatype_type_size(DataType attribute_type) const {
    switch (attribute_type) {
    case DataType::Char:
        return sizeof(GLbyte);

    case DataType::UChar: case DataType::UCVec4:
        return sizeof(GLubyte);

    case DataType::Int16:
        return sizeof(GLshort);

    case DataType::Int32: case DataType::IVec2: case DataType::IVec3: case DataType::IVec4:
        return sizeof(GLint);

    case DataType::UInt16: case DataType::UVec2: case DataType::UVec3: case DataType::UVec4:
        return sizeof(GLushort);

    case DataType::UInt32:
        return sizeof(GLuint);

    case DataType::Float16:
        return sizeof(GLhalf);

    case DataType::Float32: case DataType::Vec2: case DataType::Vec3: case DataType::Vec4:
        return sizeof(GLfloat);

    case DataType::Double:
        return sizeof(GLdouble);
    }

    return -1;
}

GLboolean VertexArray::datatype_normalized(DataType attribute_type) const {
    switch (attribute_type) {
    case DataType::Char:
    case DataType::UChar:
    case DataType::Int16:
    case DataType::Int32:
    case DataType::UInt16:
    case DataType::UInt32:
    case DataType::IVec2:
    case DataType::IVec3:
    case DataType::IVec4:
    case DataType::UVec2:
    case DataType::UVec3:
    case DataType::UVec4:
    case DataType::UCVec4:
        return GL_TRUE;
    }

    return GL_FALSE;
}