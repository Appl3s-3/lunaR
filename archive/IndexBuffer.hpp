#if !defined(LUNA_INDEX_BUFFER_HPP)
#define LUNA_INDEX_BUFFER_HPP

#include <cstddef>
#include <iostream>
#include <vector>
#include "miniGL.h"

namespace luna {
    class IndexBuffer {
    public:
        IndexBuffer(std::size_t triangle_count);
        ~IndexBuffer();

        inline void bind() const { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer_name); }
        inline GLuint name() const { return buffer_name; }
        inline std::size_t count() const { return used_indices; }

        void generate_triangles();
        void generate_rectangles();
        void append(const std::vector<GLuint>& _indices);
        
    private:
        GLuint buffer_name;
        std::vector<GLuint> indices;

        std::size_t index_capacity;
        std::size_t used_indices = 0;

        std::size_t used_space = 0;
    };
}

#endif // LUNA_INDEX_BUFFER_HPP
