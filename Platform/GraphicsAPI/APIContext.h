//
// Created by IDKTHIS on 16.02.2025.
//

#pragma once

#include <glm/glm.hpp>
#include <memory>
#include <nlohmann/json.hpp>

#include "Engine/Platform/Window/Window.h"


class IShader {
public:
    virtual ~IShader() = default;
    virtual void Bind() const = 0;
    virtual void Unbind() const = 0;
    virtual void DeleteBuffer(unsigned int &VBO) = 0;
    virtual void BindVertexArray(unsigned int VAO) = 0;
    virtual void DrawArrays(unsigned int mode, int first, size_t count) = 0;
    virtual void PrepairModel(const float* buffer, size_t vertices, const int* attrs,
                            unsigned int& VAO, unsigned int& VBO) = 0;
    virtual void SetUniform1i(const std::string& name, int value) = 0;
    virtual void SetUniform1f(const std::string& name, float value) = 0;
    virtual void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3) = 0;
    virtual void SetUniformMat4f(const std::string& name, const glm::mat4& matrix) = 0;
};

class ITexture {
public:
    virtual ~ITexture() = default;
    virtual void Bind(unsigned int slot = 0) const = 0;
    virtual void Unbind() const = 0;

    virtual int GetWidth() const = 0;
    virtual int GetHeight() const = 0;
};

class IGraphicsContext {
public:
    virtual ~IGraphicsContext() = default;

    virtual bool Init(Core::Window* windowHandle) = 0;
    virtual void InitImGui() = 0;

    virtual void BeginFrame() = 0;
    virtual void EndFrame() = 0;

    virtual IShader* CreateShader(nlohmann::json &shader) = 0;
    virtual ITexture* CreateTexture(const std::string& path) = 0;

    virtual void SetViewport(int width, int height) = 0;
    virtual void SetClearColor(float r, float g, float b, float a) = 0;


    virtual void DrawIndexed(uint32_t indexCount) = 0;
    static IGraphicsContext* Create();
};
