#include "Texture.hpp"

using namespace luna;

Texture::Texture() {
    glGenTextures(1, &texture_name);
}

Texture::~Texture() {
    glDeleteTextures(1, &texture_name);
}

void Texture::set_texture_unit(const uint32_t unit_number) {
    texture_unit = GL_TEXTURE0 + unit_number;
}

void Texture::bind() const { 
    glActiveTexture(texture_unit);
    glBindTexture(GL_TEXTURE_2D, texture_name);
}

void Texture::unbind() const {
    glActiveTexture(texture_unit);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::reserve(GLsizei width,
                      GLsizei height,
                      const ImageFormat& info) {
    bind();

    glTexImage2D(GL_TEXTURE_2D,
                 info.level_of_detail,
                 info.internal_format,
                 width,
                 height,
                 0,
                 info.format,
                 info.type,
                 NULL);

    texture_info = info;

    unbind();
}

void Texture::upload(GLsizei width,
            GLsizei height,
            GLint offset_x,
            GLint offset_y,
            const void* data) {
    bind();

    glTexSubImage2D(GL_TEXTURE_2D,
                    texture_info.level_of_detail,
                    offset_x,
                    offset_y,
                    texture_info.internal_format,
                    width,
                    height,
                    0,
                    texture_info.format,
                    texture_info.type,
                    data);

    glGenerateMipmap(GL_TEXTURE_2D);

    unbind();
}

//     /* void glTexImage2D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const void * data);
//     * level:          Level-of-detail, specifying the 'n'th mipmap reduction.
//     * internalformat: View documentation for all avaliable types. Base types {DEPTH_COMPONENT, DEPTH_STENCIL, RED, RG, RGB, RGBA} 
//     * border:         Must be 0.
//     * format:         ({RED, RG, RGB, BGR, RGBA} - []_INTEGER) or {STENCIL_INDEX, DEPTH_COMPONENT, DEPTH_STENCIL}
//     * type:           View documentation for avaliable types. Typical types (UNSIGNED_[] - {BYTE, SHORT, INT}) or {HALF_FLOAT, FLOAT}
//     * data:           A pointer to the data.
//     */

void Texture::set_mipmap_filter(GLint minify_filter,
                                GLint magnify_filter) const {
    /* GL_NEAREST:           Value/Texture element nearest to the specified coordinate.
     * GL_LINEAR:            Weighted average of four closest values/texture elements.
     * GL_[]_MIPMAP_NEAREST: Chooses the mipmap that most closely matches the size of the pixel.
     * GL_[]_MIPMAP_LINEAR:  Chooses two mipmaps that most closely matches the size of the pixel. Final value is the weighted average of both values.
     * MIN_FILTER is capable of all six options.                             Default: GL_NEAREST_MIPMAP_LINEAR
     * MAG_FILTER is unable to produce mipmaps and can only use two options. Default: LINEAR
     * In terms of best performance, the order is:
     * {NEAREST, LINEAR} - {[]_MIPMAP_NEAREST, []_MIPMAP_LINEAR}
     */
    bind();
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minify_filter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magnify_filter);
    glGenerateMipmap(GL_TEXTURE_2D);
    unbind();
}

void Texture::set_wrap(const GLint wrap_s,
                       const GLint wrap_t) const {
    /* Default: GL_REPEAT
     * {GL_CLAMP_TO_EDGE, GL_CLAMP_TO_BORDER, GL_MIRRORED_REPEAT, GL_REPEAT, or GL_MIRROR_CLAMP_TO_EDGE}
     */
    bind();
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap_s);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap_t);
    unbind();
}