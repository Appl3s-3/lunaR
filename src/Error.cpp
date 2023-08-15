#include "Error.hpp"

using namespace luna;

OpenGlErrorCallback::OpenGlErrorCallback(GLenum _source, GLenum _type, GLuint _id, GLenum _severity, const GLchar* _message)
    :   id(_id), message(_message) {
    set_source(_source);
    set_type(_type);
    set_severity(_severity);
}

void OpenGlErrorCallback::log() {
    std::cerr << "Source: " + source + ", Type: " + type + ", Id: " << id << ", Severity: " + severity
            + "\nMessage: " + message << std::endl;
}

void OpenGlErrorCallback::set_source(GLenum _source) {
    switch (_source) {
    case GL_DEBUG_SOURCE_API:
        source = "API";
        break;
    case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
        source = "WINDOW_SYSTEM";
        break;
    case GL_DEBUG_SOURCE_SHADER_COMPILER:
        source = "SHADER_COMPILER";
        break;
    case GL_DEBUG_SOURCE_THIRD_PARTY:
        source = "THIRD_PARTY";
        break;
    case GL_DEBUG_SOURCE_APPLICATION:
        source = "APPLICATION";
        break;
    case GL_DEBUG_SOURCE_OTHER:
        source = "OTHER";
        break;
    }
}

void OpenGlErrorCallback::set_type(GLenum _type) {
    switch (_type) {
    case GL_DEBUG_TYPE_ERROR:
        type = "ERROR";
        break;
    case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
        type = "DEPRECATED_BEHAVIOR";
        break;
    case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
        type = "UNDEFINED_BEHAVIOR";
        break;
    case GL_DEBUG_TYPE_PORTABILITY:
        type = "PORTABILITY";
        break;
    case GL_DEBUG_TYPE_PERFORMANCE:
        type = "PERFORMANCE";
        break;
    case GL_DEBUG_TYPE_MARKER:
        type = "MARKER";
        break;
    case GL_DEBUG_TYPE_PUSH_GROUP:
        type = "PUSH_GROUP";
        break;
    case GL_DEBUG_TYPE_POP_GROUP:
        type = "POP_GROUP";
        break;
    case GL_DEBUG_TYPE_OTHER:
        type = "OTHER";
        break;
    }
}

void OpenGlErrorCallback::set_severity(GLenum _severity) {
    switch (_severity) {
    case GL_DEBUG_SEVERITY_HIGH:
        severity = "HIGH";
        break;
    case GL_DEBUG_SEVERITY_MEDIUM:
        severity = "MEDIUM";
        break;
    case GL_DEBUG_SEVERITY_LOW:
        severity = "LOW";
        break;
    case GL_DEBUG_SEVERITY_NOTIFICATION:
        severity = "NOTIFICATION";
        break;
    }
}