#include "luna/Program.hpp"

using namespace luna;

Program::Program() {
    program_name = glCreateProgram();
}

Program::~Program() {
    glDeleteProgram(program_name);
}

void Program::use() const {
    glUseProgram(program_name);
}

void Program::uninstall() {
    glUseProgram(0);
}

GLuint Program::name() const {
    return program_name;
}

void Program::attach_shader(const Shader& shader) const {
    use();

    glAttachShader(program_name, shader.shader_name);
    
    uninstall();
}

GLint Program::link() const {
    use();

    glLinkProgram(program_name);

    GLint success = GL_FALSE;
    glGetProgramiv(program_name, GL_LINK_STATUS, &success);

    uninstall();

    return success;
}

std::string Program::info_log() const {
    use();

    // Get the length of the info log
    GLint log_length = 0;
    glGetProgramiv(program_name, GL_INFO_LOG_LENGTH, &log_length);

    // Load the info log into a buffer
    char* info_log = new char[log_length]();
    glGetProgramInfoLog(program_name,
                        log_length,
                        NULL,
                        info_log);
    
    uninstall();

    // Copy the info log into a string
    std::string info_log_string = std::string(info_log);

    // Delete the info log buffer
    delete info_log;


    // Return the info log string
    return info_log_string;
}