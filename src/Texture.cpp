#include "Texture.hpp"

using namespace luna;

Texture::Texture() {
    glGenTextures(1, &texture_name);
}

Texture::Texture(const uint32_t unit_number)
    : texture_unit(GL_TEXTURE0 + unit_number) {
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

/*
void Texture::allocate(GLsizei width, GLsizei height, uint32_t channels) const {
    bind();

    GLint internalformat;
    GLenum format;

    switch (channels) {
    case 3:
        internalformat = GL_RGB;
        format = GL_RGB;
        break;
    case 4:
        internalformat = GL_RGBA;
        format = GL_RGBA;
        break;
    default:
    // TODO: fix error msg
        std::cout << "Invalid amount of channels to allocate, defaulting to 3." << std::endl;
        internalformat = GL_RGB;
        format = GL_RGB;
    }

    glTexImage2D(GL_TEXTURE_2D,
                 0,
                 GL_RGB,
                 800,
                 600,
                 0,
                 GL_RGB,
                 GL_UNSIGNED_BYTE,
                 NULL);
    
    unbind();
}
*/

// void Texture::from_qoi(std::string filename) const {
//     bind();

//     qoi_desc image_desc;
//     void* image_bytes = qoi_read(filename.c_str(), &image_desc, 0);
//     if (image_bytes == NULL) {
//         std::cout << "Failed to load image from the location: " << filename << std::endl;
//     }

//     GLint internal_format;
//     GLenum format;

//     switch (image_desc.channels) {
//     case 3:
//         internal_format = GL_RGB;
//         format = GL_RGB;
//         break;
//     case 4:
//         internal_format = GL_RGBA;
//         format = GL_RGBA;
//         break;
//     default:
//         std::cout << "Unknown amount of channels in QOI file while reading texture. Channels: " << image_desc.channels << std::endl;
//         internal_format = GL_RGBA;
//         format = GL_RGBA;
//     }

//     /* void glTexImage2D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const void * data);
//     * level:          Level-of-detail, specifying the 'n'th mipmap reduction.
//     * internalformat: View documentation for all avaliable types. Base types {DEPTH_COMPONENT, DEPTH_STENCIL, RED, RG, RGB, RGBA} 
//     * border:         Must be 0.
//     * format:         ({RED, RG, RGB, BGR, RGBA} - []_INTEGER) or {STENCIL_INDEX, DEPTH_COMPONENT, DEPTH_STENCIL}
//     * type:           View documentation for avaliable types. Typical types (UNSIGNED_[] - {BYTE, SHORT, INT}) or {HALF_FLOAT, FLOAT}
//     * data:           A pointer to the data.
//     */

//     glTexImage2D(GL_TEXTURE_2D,
//                  0,
//                  internal_format,
//                  image_desc.width,
//                  image_desc.height,
//                  0,
//                  format,
//                  GL_UNSIGNED_BYTE,
//                  image_bytes);
//     free(image_bytes);
//     unbind();
// }

// void Texture::set_unit_from_file(const char *filename, int32_t width, int32_t height, const uint32_t texture_unit, const GLint internalformat, const GLenum format, const GLenum type, int32_t channels) {  
//     if (texture_unit < total_units) {
//         glActiveTexture(texture_unit + GL_TEXTURE0);
//         bind(texture_unit);
//         // stbi_uc *stbi_load(char const *filename, int *x, int *y, int *channels_in_file, int desired_channels);
//         // channels_in_file: Force the number of channels in the file. 0 will auto detect.
//         stbi_uc *image = stbi_load(filename, &width, &height, &channels, 0);
//         if (image == NULL) {
//             printf(LUNA_FILE_ERROR "Failed to load image in the location: %s\n", filename);
//         }
//         /* void glTexImage2D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const void * data);
//          * level:          Level-of-detail, specifying the 'n'th mipmap reduction.
//          * internalformat: View documentation for all avaliable types. Base types {DEPTH_COMPONENT, DEPTH_STENCIL, RED, RG, RGB, RGBA} 
//          * border:         Must be 0.
//          * format:         ({RED, RG, RGB, BGR, RGBA} - []_INTEGER) or {STENCIL_INDEX, DEPTH_COMPONENT, DEPTH_STENCIL}
//          * type:           View documentation for avaliable types. Typical types (UNSIGNED_[] - {BYTE, SHORT, INT}) or {HALF_FLOAT, FLOAT}
//          * data:           A pointer to the data.
//          */
//         glTexImage2D(texture_type[texture_unit], 0, internalformat, width, height, 0, format, type, image);
//         glGenerateMipmap(texture_type[texture_unit]);
//         stbi_image_free(image);
//         unbind(texture_unit);
//     }
//     // TODO: When total units are exceeded
// }

// void Texture::set_unit_from_buffer(void* buffer, int32_t width, int32_t height, const uint32_t texture_unit, const GLint internalformat, const GLenum format, const GLenum type, int32_t channels) {  
//     if (texture_unit < total_units) {
//         glActiveTexture(texture_unit + GL_TEXTURE0);
//         bind(texture_unit);
//         glTexImage2D(texture_type[texture_unit], 0, internalformat, width, height, 0, format, type, buffer);
//         glGenerateMipmap(texture_type[texture_unit]);
//         unbind(texture_unit);
//     }
//     // TODO: When total units are exceeded
// }

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