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

/**
 * @brief Manages an OpenGL texture image.
 */
class Texture {
public:

    /**
     * @brief Construct a new Texture object.
     * Generates a texture.
     */
    Texture();

    /**
     * @brief Destroy the Texture object.
     * Deletes the texture.
     */
    ~Texture();

    /**
     * @brief Sets the texture unit that the texture will bind to.
     * @param unit_number The unit to make active before binding.
     */
    void set_texture_unit(const uint32_t unit_number);

    /**
     * @brief Activates the stored texture unit and binds the texture to it.
     */
    void bind() const;

    /**
     * @brief Activates the stored texture unit and unbinds all textures from it.
     */
    void unbind() const;

    /**
     * @brief Returns the reference to the OpenGL texture as a GLuint.
     * @return GLuint: The reference to the OpenGL texture.
     */
    GLuint name() const;

    /**
     * @brief Returns the value of the stored texture unit.
     * @return GLenum: The value of the stored texture unit.
     */
    GLenum unit() const;

    /**
     * @brief Reserves space for a 2D texture.
     * Reserves space for a 2D texture with the given width, height and
     * image format. Relenquishes access to previous texture data.
     * @param width  The width of the texture image.
     * @param height The height of the texture image.
     * @param info   Texture image format information, defaults to {}.
     */
    void reserve(GLsizei width,
                 GLsizei height,
                 const ImageFormat& info = {});

    /**
     * @brief Uploads a sub-image of data to the texture image.
     * Uploads a sub-image of data to the texture image and re-generates
     * the texture mipmaps.
     * @param width    The width of the sub-image.
     * @param height   The height of the sub-image.
     * @param offset_x The x offset of the sub-image.
     * @param offset_y The y offset of the sub-image.
     * @param data     A pointer to the data to upload.
     */
    void upload(GLsizei width,
                GLsizei height,
                GLint offset_x,
                GLint offset_y,
                const void* data);

    /**
     * @brief Sets the minify and magnify filters for the texture mipmap.
     * Sets the minify and magnify filters for the texture mipmap.
     * Filters are one of: GL_NEAREST, GL_LINEAR GL_X_MIPMAP_X,
     * where X is NEAREST or LINEAR.
     * @param minify_filter  The texture minifying filter,
     *                       defaults to GL_NEAREST_MIPMAP_LINEAR.
     * @param magnify_filter The texture magnifying filter,
     *                       defaults to GL_LINEAR.
     */
    void set_mipmap_filter(GLint minify_filter = GL_NEAREST_MIPMAP_LINEAR,
                           GLint magnify_filter = GL_LINEAR) const;

    /**
     * @brief Sets the wrapping used for the texture in the 's' and 't' axis.
     * Sets the wrapping used for the texture in the 's' and 't' axis.
     * Wrapping methods are one of: GL_CLAMP_TO_EDGE, GL_CLAMP_TO_BORDER,
     * GL_MIRRORED_REPEAT, GL_REPEAT, or GL_MIRROR_CLAMP_TO_EDGE.
     * @param wrap_s The wrapping method to use for the 's' axis,
     *               defaults to GL_REPEAT.
     * @param wrap_t The wrapping method to use for the 't' axis,
     *               defaults to GL_REPEAT.
     */
    void set_wrap(GLint wrap_s = GL_REPEAT,
                  GLint wrap_t = GL_REPEAT) const;


private:
    GLenum texture_unit = GL_TEXTURE0;
    GLuint texture_name;

    ImageFormat texture_info;
};

} // namespace luna

#endif // LUNA_TEXTURE_HPP
