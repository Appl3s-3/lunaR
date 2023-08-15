#if !defined(LUNA_ERROR_HPP)
#define LUNA_ERROR_HPP

#include <string>
#include <iostream>
#include "miniGL.h"

namespace luna {
    class OpenGlErrorCallback {
    public:
        OpenGlErrorCallback(GLenum _source, GLenum _type, GLuint _id, GLenum _severity, const GLchar* _message);

        void log();

        std::string source;
        std::string type;
        GLuint id;
        std::string severity;
        std::string message;

    private:
        void set_source(GLenum _source);
        void set_type(GLenum _type);
        void set_severity(GLenum _severity);
    };
}

#endif // LUNA_ERROR_HPP
