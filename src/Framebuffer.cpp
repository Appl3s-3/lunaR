#include "Framebuffer.hpp"

using namespace luna;

Framebuffer::Framebuffer(GLsizei width, GLsizei height)
    : buffer(Texture(0)) {
    // Generate a framebuffer object
    glGenFramebuffers(1, &name);

    // Allocate storage for the framebuffer's texture
    buffer.allocate(width, height);
    buffer.mipmap(GL_LINEAR, GL_LINEAR);

    // Bind the texture and framebuffer
    bind();

    // Attach the texture to the framebuffer
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, buffer.name, 0);

    // Renderbuffer object code, unused
    
    // unsigned int rbo;
    // glGenRenderbuffers(1, &rbo);
    // glBindRenderbuffer(GL_RENDERBUFFER, rbo);
    // glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
    // glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);

    // TODO: fix this error msg
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
	    std::cout << "Framebuffer incomplete" << std::endl;
    }
}

Framebuffer::~Framebuffer() {
    glDeleteFramebuffers(1, &name);
}