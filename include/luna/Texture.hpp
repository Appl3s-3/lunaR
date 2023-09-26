#ifndef LUNA_TEXTURE_HPP
#define LUNA_TEXTURE_HPP

#include <cstdint>

#include "luna/miniGL.h"
#include "luna/LunaDefines.hpp"

namespace luna {

struct ImageFormat {
    GLint level_of_detail = 0;

    GLenum type = GL_UNSIGNED_BYTE;

    GLint internal_format = GL_RGBA;
    GLenum format = GL_RGBA;
};

// Texture
// Manages an OpenGL texture image
class Texture {
public:
    // Texture Constructor
    // Generates a texture
    Texture();

    // archive
    Texture(const uint32_t unit_number);

    // Texture Destructor
    // Deletes the texture
    ~Texture();

    // set_texture_unit
    // Sets the texture unit that the texture will bind to
    // :: const uint32_t unit_number :: The unit to make active before binding
    void set_texture_unit(const uint32_t unit_number);

    // bind
    // Activates the stored texture unit and binds the texture to it
    void bind() const;

    // unbind
    // Activates the stored texture unit and unbinds all textures from it
    void unbind() const;

    // name
    // Returns the reference to the OpenGL texture as a GLuint
    GLuint name() const;

    // unit
    // Returns the value of the stored texture unit
    GLenum unit() const;

    // reserve
    // Reserves space for a 2D texture with the given width, height and
    // image format. Relenquishes access to previous texture data.
    // ::       GLsizei      width  :: The width of the texture image
    // ::       GLsizei      height :: The height of the texture image
    // :: const ImageFormat& info   :: Texture image format information
    //                                 Default value is {}
    void reserve(GLsizei width,
                 GLsizei height,
                 const ImageFormat& info = {});

    // upload
    // Uploads a sub-image of data to the texture image and re-generates the
    // texture mipmaps
    // ::       GLsizei width    :: The width of the sub-image
    // ::       GLsizei height   :: The height of the sub-image
    // ::       GLint   offset_x :: The x offset of the sub-image
    // ::       GLint   offset_y :: The y offset of the sub-image
    // :: const void*   data     :: A pointer to the data to upload
    void upload(GLsizei width,
                GLsizei height,
                GLint offset_x,
                GLint offset_y,
                const void* data);

    // archive
    // void allocate(GLsizei width,
    //               GLsizei height,
    //               uint32_t channels = 3) const;

    // // archive
    // void from_qoi(std::string filename) const;

    // set_mipmap_filter
    // Sets the minify and magnify filters for the texture mipmap. Filters
    // are one of: GL_NEAREST, GL_LINEAR, GL_X_MIPMAP_X, where X is
    // NEAREST or LINEAR.
    // :: GLint minify_filter  :: The texture minifying filter.
    //                            Default value is GL_NEAREST_MIPMAP_LINEAR
    // :: GLint magnify_filter :: The texture magnifying filter.
    //                            Default value is GL_LINEAR
    void set_mipmap_filter(GLint minify_filter = GL_NEAREST_MIPMAP_LINEAR,
                           GLint magnify_filter = GL_LINEAR) const;

    // set_wrap
    // Sets the wrapping used for the texture in the 's' and 't' axis.
    // Wrapping methods are one of: GL_CLAMP_TO_EDGE, GL_CLAMP_TO_BORDER,
    // GL_MIRRORED_REPEAT, GL_REPEAT, or GL_MIRROR_CLAMP_TO_EDGE.
    // :: GLint wrap_s  :: The wrapping method to use for the 's' axis.
    //                     Default value is GL_REPEAT
    // :: GLint wrap_t :: The wrapping method to use for the 't' axis.
    //                     Default value is GL_REPEAT
    void set_wrap(GLint wrap_s = GL_REPEAT,
                  GLint wrap_t = GL_REPEAT) const;


private:
    GLenum texture_unit = GL_TEXTURE0;
    GLuint texture_name;

    ImageFormat texture_info;
};

// class Texture {
// public:
//     Texture(const uint32_t units = 1);
//     ~Texture();

//     void bind(const uint32_t texture_unit = 0);
//     void unbind(const uint32_t texture_unit = 0);

//     void set_unit_from_file(const char *filename, int32_t width, int32_t height, const uint32_t texture_unit = 0, const GLint internalformat = GL_RGBA, const GLenum format = GL_RGBA, const GLenum type = GL_UNSIGNED_BYTE, int32_t channels = 0);
//     void set_unit_from_buffer(void* buffer, int32_t width, int32_t height, const uint32_t texture_unit = 0, const GLint internalformat = GL_RGBA, const GLenum format = GL_RGBA, const GLenum type = GL_UNSIGNED_BYTE, int32_t channels = 0);

//     void set_filters(const GLint minify_filter = GL_NEAREST_MIPMAP_LINEAR, const GLint magnify_filter = GL_LINEAR, const uint32_t texture_unit = 0);
//     void set_wrapping(const GLint wrap_s = GL_REPEAT, const GLint wrap_t = GL_REPEAT, const GLint wrap_r = GL_REPEAT, const uint32_t texture_unit = 0);

// private:
//     GLuint texture_id;
//     std::vector<GLenum> texture_type;
//     uint32_t total_units;
// };

} // namespace luna

#endif // LUNA_TEXTURE_HPP
