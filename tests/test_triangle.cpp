#include <cstdint>

#include "luna/miniGL.h"
#include "luna/Window.hpp"
#include "luna/BufferManager.hpp"
#include "luna/VertexArray.hpp"

#include "luna/Shader.hpp"
#include "luna/Program.hpp"

// void GLAPIENTRY open_gl_error_callback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam) {
//     luna::OpenGlErrorCallback error = luna::OpenGlErrorCallback(source, type, id, severity, message);
//     error.log();
// }
int main(int argc, char** argv) {
    return 0;
}
/*
int main(int argc, char** argv) {
    // Position vertices for an isoceles triangle
    float position_vertices[] = {
        0.0, 0.0,
        0.5, 0.7,
        0.7, 0.3
    };

    // Colour vertices (RGBA) for an isoceles triangle
    uint8_t colour_vertices[] = {
          0,   0, 255, 255,
        255,   0, 0,   255,
        0,   255, 0,   255
    };

    uint32_t triangle_indices[] = {
        0, 1, 2
    };

    // data info
    luna::VertexAttributeInfo position_info;
    position_info.index = 0;
    position_info.size = 2;
    position_info.type = luna::DataType::Float32;

    luna::VertexAttributeInfo colour_info;
    colour_info.index = 1;
    colour_info.size = 4;
    colour_info.type = luna::DataType::UChar;
    colour_info.normalized = GL_TRUE;


    luna::Initiate();
    luna::Window window = luna::Window(1280, 720, "Hello Triangle");

    // vbos
    luna::BufferManager position_buffer = luna::BufferManager(GL_ARRAY_BUFFER);
    position_buffer.reserve(6 * sizeof(float));
    position_buffer.upload(0, sizeof(position_vertices), position_vertices);

    luna::BufferManager colour_buffer = luna::BufferManager(GL_ARRAY_BUFFER);
    colour_buffer.reserve(12 * sizeof(uint8_t));
    colour_buffer.upload(0, sizeof(colour_vertices), colour_vertices);

    luna::BufferManager indices_buffer = luna::BufferManager(GL_ELEMENT_ARRAY_BUFFER);
    indices_buffer.reserve(3 * sizeof(uint32_t));
    indices_buffer.upload(0, sizeof(triangle_indices), triangle_indices);

    // vao
    luna::VertexArray triangle_vao = luna::VertexArray();
    triangle_vao.define_attribute(position_buffer, position_info, 0);
    triangle_vao.define_attribute(colour_buffer, colour_info, 0);

    // use the ibo the the vao
    triangle_vao.use();
    indices_buffer.use();
    triangle_vao.unbind();

    // shaders
    luna::Shader triangle_vs = luna::Shader(GL_VERTEX_SHADER, "../shaders/tests/triangle.vs");
    luna::Shader triangle_fs = luna::Shader(GL_FRAGMENT_SHADER, "../shaders/tests/triangle.fs");

    luna::Program traingle_shader_program = luna::Program(triangle_vs, triangle_fs);
    traingle_shader_program.use();

    window.clear_colour(0.1, 0.1, 0.1);

    // draw the triangle
    while (window.not_closed() == true) {
        window.poll();
        
        window.clear();
        triangle_vao.use();
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
        window.swap_buffers();
    }

    luna::Terminate();
    
    return 0;
}

*/