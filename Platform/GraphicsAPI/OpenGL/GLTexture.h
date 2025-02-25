//
// Created by IDKTHIS on 16.02.2025.
//

#pragma once


#include "Engine/Platform/GraphicsAPI/APIContext.h"
#define GLEW_STATIC
#include <GL/glew.h>

class GLTexture : public ITexture {
public:
    GLTexture(const std::string& path);
    GLTexture(int width, int height, GLenum format = GL_RGBA);
    ~GLTexture();

    void Bind(unsigned int slot = 0) const override;
    void Unbind() const override;

    int GetWidth() const override { return m_Width; }
    int GetHeight() const override { return m_Height; }

    void SetData(void* data, unsigned int size);

private:
    GLuint m_RendererID;
    int m_Width, m_Height;
    GLenum m_InternalFormat, m_DataFormat;
};