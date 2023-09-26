#include <cstdint>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <math.h>

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
    float original_position_vertices[] = {
        0.0, 0.0,
        0.5, 0.7,
        0.7, 0.3
    };

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
    position_info.normalized = GL_FALSE;
    position_info.stride = 0;

    luna::VertexAttributeInfo colour_info;
    colour_info.index = 1;
    colour_info.size = 4;
    colour_info.type = luna::DataType::UChar;
    colour_info.normalized = GL_TRUE;

    // initiate luna
    luna::Initiate();
    luna::Window window = luna::Window(800, 800, "Hello Triangle");

    // vbos
    luna::BufferManager position_buffer = luna::BufferManager(GL_ARRAY_BUFFER);
    position_buffer.reserve(sizeof(position_vertices));
    position_buffer.upload(0, sizeof(position_vertices), position_vertices);

    luna::BufferManager colour_buffer = luna::BufferManager(GL_ARRAY_BUFFER);
    colour_buffer.reserve(sizeof(colour_vertices));
    colour_buffer.upload(0, sizeof(colour_vertices), colour_vertices);

    luna::BufferManager indices_buffer = luna::BufferManager(GL_ELEMENT_ARRAY_BUFFER);
    indices_buffer.reserve(sizeof(triangle_indices));
    indices_buffer.upload(0, sizeof(triangle_indices), triangle_indices);

    // vao
    luna::VertexArray triangle_vao = luna::VertexArray();
    triangle_vao.define_attribute(position_buffer, position_info, 0);
    triangle_vao.define_attribute(colour_buffer, colour_info, 0);

    // bind the ibo the the vao
    triangle_vao.bind();
    indices_buffer.bind();
    // triangle_vao.unbind(); // also works
    luna::VertexArray::unbind();

    // shader sources
    std::ifstream vertex_shader_file_stream = std::ifstream("../shaders/tests/triangle.vs");
    std::stringstream vertex_shader_stream;
    vertex_shader_stream << vertex_shader_file_stream.rdbuf();
    std::string vertex_shader_body = vertex_shader_stream.str();

    std::ifstream fragment_shader_file_stream = std::ifstream("../shaders/tests/triangle.fs");
    std::stringstream fragment_shader_stream;
    fragment_shader_stream << fragment_shader_file_stream.rdbuf();
    std::string fragment_shader_body = fragment_shader_stream.str();

    // shaders
    luna::Shader triangle_vs = luna::Shader(luna::ShaderType::VERTEX);
    triangle_vs.append_source(vertex_shader_body);
    triangle_vs.compile();
    
    luna::Shader triangle_fs = luna::Shader(luna::ShaderType::FRAGMENT);
    triangle_fs.append_source(fragment_shader_body);
    triangle_fs.compile();

    luna::Program triangle_shader_program = luna::Program();
    triangle_shader_program.attach_shader(triangle_vs);
    triangle_shader_program.attach_shader(triangle_fs);
    triangle_shader_program.link();

    // pre loop
    triangle_shader_program.use();

    window.clear_colour(0.1, 0.1, 0.1);

    double time = 0.0;
    double period = 0.0;

    // draw the triangle
    while (window.not_closed() == true) {
        time += 0.02;
        window.poll();

        // for (int i = 0; i < 6; ++i) {
        //     position_vertices[i] = original_position_vertices[i] + 0.3 * sin(time);
        // }

        for (int i = 0; i < 3; ++i) {
            period = (double)(i / 3.0) * 2 * 3.1415926;
            position_vertices[2 * i + 0] = 0.7 * cos(time + period);
            position_vertices[2 * i + 1] = 0.7 * sin(time + period);
        }

        position_buffer.bind();
        position_buffer.upload(0, sizeof(position_vertices), position_vertices);
        
        window.clear();

        triangle_vao.bind();
        triangle_shader_program.use();
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);

        window.swap_buffers();
    }

    luna::Terminate();
    
    return 0;
}