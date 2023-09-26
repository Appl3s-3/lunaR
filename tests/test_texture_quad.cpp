#include <cstdint>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <limits>
#include <math.h>

#include "luna/miniGL.h"
#include "luna/Window.hpp"
#include "luna/BufferManager.hpp"
#include "luna/VertexArray.hpp"

#include "luna/Texture.hpp"
#include "luna/Shader.hpp"
#include "luna/Program.hpp"

// void GLAPIENTRY open_gl_error_callback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam) {
//     luna::OpenGlErrorCallback error = luna::OpenGlErrorCallback(source, type, id, severity, message);
//     error.log();
// }

int main(int argc, char** argv) {
    // Position vertices for a quad
    float position_vertices[] = {
        -0.5,  0.5,
         0.5,  0.5,
        -0.5, -0.5,
         0.5, -0.5
    };


    // UV vertices for a quad
    uint16_t uv_max = std::numeric_limits<uint16_t>::max();
    uint16_t uv_vertices[] = {
             0,      0,
        uv_max,      0,
             0, uv_max,
        uv_max, uv_max
    };

    uint32_t quad_indices[] = {
        0, 1, 2,
        1, 2, 3
    };

    // data info
    luna::VertexAttributeInfo position_info;
    position_info.index = 0;
    position_info.size = 2;
    position_info.type = luna::DataType::Float32;
    position_info.normalized = GL_FALSE;
    position_info.stride = 0;

    luna::VertexAttributeInfo uv_info;
    uv_info.index = 1;
    uv_info.size = 2;
    uv_info.type = luna::DataType::UInt16;
    uv_info.normalized = GL_TRUE;

    // initiate luna
    luna::Initiate();
    luna::Window window = luna::Window(800, 800, "Hello Texture");

    // vbos
    luna::BufferManager position_buffer = luna::BufferManager(GL_ARRAY_BUFFER);
    position_buffer.reserve(sizeof(position_vertices));
    position_buffer.upload(0, sizeof(position_vertices), position_vertices);

    luna::BufferManager uv_buffer = luna::BufferManager(GL_ARRAY_BUFFER);
    uv_buffer.reserve(sizeof(uv_vertices));
    uv_buffer.upload(0, sizeof(uv_vertices), uv_vertices);

    luna::BufferManager indices_buffer = luna::BufferManager(GL_ELEMENT_ARRAY_BUFFER);
    indices_buffer.reserve(sizeof(quad_indices));
    indices_buffer.upload(0, sizeof(quad_indices), quad_indices);

    // vao
    luna::VertexArray triangle_vao = luna::VertexArray();
    triangle_vao.define_attribute(position_buffer, position_info, 0);
    triangle_vao.define_attribute(uv_buffer, uv_info, 0);

    // bind the ibo the the vao
    triangle_vao.bind();
    indices_buffer.bind();
    // triangle_vao.unbind(); // also works
    luna::VertexArray::unbind();

    // shader sources
    std::ifstream vertex_shader_file_stream = std::ifstream("../shaders/tests/texture.vs");
    std::stringstream vertex_shader_stream;
    vertex_shader_stream << vertex_shader_file_stream.rdbuf();
    std::string vertex_shader_body = vertex_shader_stream.str();

    std::ifstream fragment_shader_file_stream = std::ifstream("../shaders/tests/texture.fs");
    std::stringstream fragment_shader_stream;
    fragment_shader_stream << fragment_shader_file_stream.rdbuf();
    std::string fragment_shader_body = fragment_shader_stream.str();

    // shaders
    luna::Shader texture_vs = luna::Shader(luna::ShaderType::VERTEX);
    texture_vs.append_source(vertex_shader_body);
    texture_vs.compile();
    
    luna::Shader texture_fs = luna::Shader(luna::ShaderType::FRAGMENT);
    texture_fs.append_source(fragment_shader_body);
    texture_fs.compile();

    luna::Program texture_shader_program = luna::Program();
    texture_shader_program.attach_shader(texture_vs);
    texture_shader_program.attach_shader(texture_fs);
    texture_shader_program.link();

    // textures
    uint8_t texture_buffer[100 * 100 * 4];

    luna::ImageFormat texture_info;
    texture_info.format = GL_RGBA;
    texture_info.internal_format = GL_RGBA;

    luna::Texture texture = luna::Texture();
    texture.reserve(100, 100, texture_info);
    texture.upload(100, 100, 0, 0, texture_buffer);

    // pre loop
    texture_shader_program.use();

    window.clear_colour(0.1, 0.1, 0.1);

    // draw the quad
    while (window.not_closed() == true) {
        window.poll();
        
        window.clear();

        triangle_vao.bind();
        texture_shader_program.use();
        texture.bind();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        window.swap_buffers();
    }

    luna::Terminate();
    
    return 0;
}