//
// Created by IDKTHIS on 16.02.2025.
//

#include "GLContext.h"
#define GLEW_STATIC

#include <backends/imgui_impl_opengl3.h>

#include "GLShader.h"
#include "GLTexture.h"
#include "GL/glew.h"
#include <backends/imgui_impl_opengl3.h>

#include "Engine/Application.h"


bool GLContext::Init(Core::Window *windowHandle) {
    m_window = windowHandle;
    glewExperimental = GL_TRUE;
    GLenum err = glewInit();
    if(err != GLEW_OK) {
        SimpleConsole::Get()->AddLog(LogLevel::ERROR, "GLEW init failed: " + std::string((const char*)glewGetErrorString(err)));
        return false;
    }

    if(!GLEW_VERSION_3_3) {
        SimpleConsole::Get()->AddLog(LogLevel::ERROR, "GLEW version 3.3 not supported");
        return false;
    }

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);

    glDebugMessageCallback(
        [](GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam) {
           SimpleConsole::Get()->AddLog(LogLevel::DEBUG, "OpenGL Debug Message (", id, "): ", message);
        },
        nullptr
    );

    //SDL_GL_SetSwapInterval(window->IsVSync());
    GLenum glError = glGetError();
    if(glError != GL_NO_ERROR) {
        SimpleConsole::Get()->AddLog(LogLevel::ERROR, "OpenGL Error: " + std::string((const char*)glError));
        return false;
    }
    return true;
}

void GLContext::InitImGui() {
    ImGui_ImplOpenGL3_Init("#version 130");
}

void GLContext::BeginFrame() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void GLContext::EndFrame() {
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    m_window->SwapBuffers();
}

IShader* GLContext::CreateShader(nlohmann::json &shader) {
    if (!shader.contains("GLSL") && !shader["GLSL"].contains("VortexShader") && !shader["GLSL"].contains("FragmentShader")) {
        SimpleConsole::Get()->AddLog(LogLevel::ERROR, "GLSL or VortexShader or FragmentShader not found");
        return nullptr;
    }
    return new GLShader(shader["GLSL"]["VortexShader"], shader["GLSL"]["FragmentShader"]);
}

ITexture* GLContext::CreateTexture(const std::string &path) {
    return new GLTexture(path);
}

void GLContext::SetViewport(int width, int height) {
}

void GLContext::SetClearColor(float r, float g, float b, float a) {
    glClearColor( r, g, b, a);
}

void GLContext::DrawIndexed(uint32_t indexCount) {
}

IGraphicsContext * GLContext::Create() {
    return new GLContext();
}
