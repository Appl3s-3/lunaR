#if !defined(LUNA_VERTEX_ATTRIBUTE_HPP)
#define LUNA_VERTEX_ATTRIBUTE_HPP

#include <cstddef>
#include <vector>

#include "miniGL.h"

namespace luna {
    template <class AttributeType>
    class VertexAttribute {
    public:
        inline VertexAttribute() { }
        inline VertexAttribute(const std::vector<AttributeType>& data) { append(data); }
        
        inline void append(const std::vector<AttributeType>& data) { vertices.insert(vertices.end(), data.begin(), data.end()); }
        template <std::size_t N>
        inline void append(const std::array<AttributeType, N>& data) { vertices.insert(vertices.end(), data.begin(), data.end()); }
        
        inline void replace(const std::vector<AttributeType>& data) { vertices = data; }
        inline void clear() { vertices.clear(); }
 
        inline std::size_t count() const { return vertices.size(); }
        inline std::size_t size() const { return count() * sizeof(AttributeType); }
        inline const AttributeType* data() const { return vertices.data(); }

        void update_buffer() const {
            if (vbo == 0) {
                std::cout << "Warning: No vbo is currently available for the vertex attribute to bind to." << std::endl;
                return;
            }

            glBindBuffer(GL_ARRAY_BUFFER, vbo);

            if (expected_size < size()) {
                std::cout << "Warning: Vertex attribute's current size " << size() << " is greater than expected_size " << expected_size << ". Using expected_size to avoid overflow." << std::endl;
                glBufferSubData(GL_ARRAY_BUFFER, start_offset, expected_size, data());
            }
            else {
                glBufferSubData(GL_ARRAY_BUFFER, start_offset, size(), data());
            }
        }

        GLuint vbo = 0;
        std::size_t start_offset = 0;
        std::size_t expected_size = 0;

    private:
        std::vector<AttributeType> vertices;
    };
}

#endif // LUNA_VERTEX_ATTRIBUTE_HPP