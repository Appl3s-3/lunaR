#ifndef LUNA_DEFINES_HPP
#define LUNA_DEFINES_HPP

#include <string>

#define LUNA_FATAL_ERROR "Luna Fatal: "
#define LUNA_FILE_ERROR "Luna File: "
#define LUNA_MEMORY_ERROR "Luna Memory: "
#define LUNA_CREATION_ERROR "Luna Creation: "
#define LUNA_BUFFER_ERROR "Luna Buffer: "
#define LUNA_FONT_ERROR "Luna Font: "
#define LUNA_DRAW_ERROR "Luna Draw: "

#define LUNA_WARNING "Luna Warning: "

#define LUNA_RANDOM_SEED 10378

namespace luna {
    namespace err {
        const std::string FATAL    = "Luna Fatal: ";
        const std::string FILE     = "Luna File: ";
        const std::string MEMORY   = "Luna Memory: ";
        const std::string CREATION = "Luna Creation: ";
        const std::string BUFFER   = "Luna Buffer: ";
        const std::string FONT     = "Luna Font: ";
        const std::string DRAW     = "Luna Draw: ";
    };

    size_t const RANDOM_SEED = 10378;

    enum class SourceText {
        string = 0,
        file = 1
    };
    
    enum class Alignment {
           top_left,    top,    top_right,
               left, centre,        right,
        bottom_left, bottom, bottom_right
    };

    enum class DataType {
        Unknown, Bool, Char, UChar,

        Int16, Int32, //Int64,
        UInt16, UInt32, //UInt64,

        Float16, Float32, Double,

        // Float32 Vectors
        Vec2, Vec3, Vec4,

        // Int32 Vectors
        IVec2,  IVec3,  IVec4,
        UVec2,  UVec3,  UVec4,
                       UCVec4,

        Mat2, Mat3, Mat4
    };
};

#endif // LUNA_DEFINES_HPP
