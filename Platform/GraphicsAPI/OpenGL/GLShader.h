//
// Created by IDKTHIS on 16.02.2025.
//

#pragma once


#include "Engine/Platform/GraphicsAPI/APIContext.h"
#define GLEW_STATIC
#include <GL/glew.h>
#include <unordered_map>

class GLShader : public IShader {
public:
    GLShader(const std::string& vertexSrc, const std::string& fragmentSrc);
    ~GLShader() override;

    void Bind() const override;
    void Unbind() const override;
    void DeleteBuffer(unsigned int &VBO) override;
    void BindVertexArray(unsigned int VAO) override;
    void DrawArrays(unsigned int mode, int first, size_t count) override;
    void PrepairModel(const float* buffer, size_t vertices, const int* attrs,
                            unsigned int& VAO, unsigned int& VBO) override;
    void SetUniform1i(const std::string& name, int value) override;
    void SetUniform1f(const std::string& name, float value) override;
    void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3) override;
    void SetUniformMat4f(const std::string& name, const glm::mat4& matrix) override;

private:
    GLuint m_RendererID;
    std::unordered_map<std::string, GLint> m_UniformLocationCache;

    GLint GetUniformLocation(const std::string& name);
    GLuint CompileShader(GLenum type, const std::string& source);
};