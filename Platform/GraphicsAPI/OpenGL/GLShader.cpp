//
// Created by IDKTHIS on 16.02.2025.
//

// GLShader.cpp
#include "GLShader.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>

GLShader::GLShader(const std::string& vertexSrc, const std::string& fragmentSrc) {
    GLuint vertexShader = CompileShader(GL_VERTEX_SHADER, vertexSrc);
    GLuint fragmentShader = CompileShader(GL_FRAGMENT_SHADER, fragmentSrc);

    m_RendererID = glCreateProgram();
    glAttachShader(m_RendererID, vertexShader);
    glAttachShader(m_RendererID, fragmentShader);
    glLinkProgram(m_RendererID);

    GLint isLinked = 0;
    glGetProgramiv(m_RendererID, GL_LINK_STATUS, &isLinked);
    if (isLinked == GL_FALSE) {
        GLint maxLength = 0;
        glGetProgramiv(m_RendererID, GL_INFO_LOG_LENGTH, &maxLength);

        std::vector<GLchar> infoLog(maxLength);
        glGetProgramInfoLog(m_RendererID, maxLength, &maxLength, &infoLog[0]);
        std::cerr << "Shader link error:\n" << infoLog.data() << std::endl;

        glDeleteProgram(m_RendererID);
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
        return;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

GLShader::~GLShader() {
    glDeleteProgram(m_RendererID);
}

GLuint GLShader::CompileShader(GLenum type, const std::string& source) {
    GLuint shader = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(shader, 1, &src, nullptr);
    glCompileShader(shader);

    GLint isCompiled = 0;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
    if (isCompiled == GL_FALSE) {
        GLint maxLength = 0;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

        std::vector<GLchar> infoLog(maxLength);
        glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);
        std::cerr << "Shader compilation error ("
                 << (type == GL_VERTEX_SHADER ? "Vertex" : "Fragment")
                 << "):\n" << infoLog.data() << std::endl;

        glDeleteShader(shader);
        return 0;
    }

    return shader;
}

void GLShader::Bind() const { glUseProgram(m_RendererID); }
void GLShader::Unbind() const { glUseProgram(0); }

void GLShader::DeleteBuffer(unsigned int &VBO) {
    glDeleteBuffers(1, &VBO);
}

void GLShader::BindVertexArray(unsigned int VAO) {
    glBindVertexArray(VAO);
}

void GLShader::DrawArrays(unsigned int mode, int first, size_t count) {
    glDrawArrays(mode, first, count);
}

void GLShader::PrepairModel(const float *buffer, size_t vertices, const int *attrs, unsigned int &VAO,
    unsigned int &VBO) {
    int vertex_size = 0;
    for (int i = 0; attrs[i]; i++){
        vertex_size += attrs[i];
    }

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertex_size * vertices, buffer, GL_STATIC_DRAW);

    int offset = 0;
    for (int i = 0; attrs[i]; i++){
        int size = attrs[i];
        glVertexAttribPointer(i, size, GL_FLOAT, GL_FALSE, vertex_size * sizeof(float), (GLvoid*)(offset * sizeof(float)));
        glEnableVertexAttribArray(i);
        offset += size;
    }

    glBindVertexArray(0);
}

GLint GLShader::GetUniformLocation(const std::string& name) {
    if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
        return m_UniformLocationCache[name];

    GLint location = glGetUniformLocation(m_RendererID, name.c_str());
    if (location == -1)
        std::cerr << "Warning: uniform '" << name << "' doesn't exist!" << std::endl;

    m_UniformLocationCache[name] = location;
    return location;
}

// Uniform setters implementation
void GLShader::SetUniform1i(const std::string& name, int value) {
    glUniform1i(GetUniformLocation(name), value);
}

void GLShader::SetUniform1f(const std::string& name, float value) {
    glUniform1f(GetUniformLocation(name), value);
}

void GLShader::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3) {
    glUniform4f(GetUniformLocation(name), v0, v1, v2, v3);
}

void GLShader::SetUniformMat4f(const std::string& name, const glm::mat4& matrix) {
    glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &matrix[0][0]);
}