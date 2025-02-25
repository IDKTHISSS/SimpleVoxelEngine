//
// Created by IDKTHIS on 16.02.2025.
//

#include "Application.h"

#include <iostream>
#include <backends/imgui_impl_opengl3.h>

#include "Platform/GraphicsAPI/OpenGL/GLContext.h"
#include "Core/SubSystems/WindowInput/WindowInputComponent.h"
#include "Platform/Window/SDLWindow/Window_SDL.h"
#include "imgui.h"
#include "Core/SubSystems/Console/SimpleConsole.h"

bool Core::Application::Initialize() {
    m_console = new SimpleConsole();
    m_console->subscribe([this](LogLevel log_level,const std::string& logMessage) {
        std::cout << logMessage << std::endl;
    });

    m_console->AddLog(LogLevel::INFO, "Engine initialized!");
    return true;
}

void Core::Application::Run() {
    IsRunning = true;
    Core::WindowProps props;
    props.title = std::string("Simple Voxel Engine | ") + ENGINE_VERSION;
    props.width = 1920;
    props.height = 1080;
    props.vsync = false;
    m_window = Window_SDL::Create(props);

    m_window->Init(EWindowMode::OpenGL);


     m_console->AddLog(LogLevel::INFO, "Running...");
    MainLoop();
}
bool show_another_window = true;
void Core::Application::MainLoop() {
    bool wasKeyPressed = false;
    while (IsRunning) {
        m_window->GetGraphicsContext()->BeginFrame();
        IsRunning = !m_window->ShouldClose;
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL3_NewFrame();
        ImGui::NewFrame();
        m_console->Draw();


        if (m_window->InputComponent->IsKeyPressed(SDLK_GRAVE)) {
            if (!wasKeyPressed) {
                m_console->ToggleShow();
                wasKeyPressed = true;
            }
        } else {
            wasKeyPressed = false;
        }

        m_window->Update();
        RenderFrame();
        ImGui::Render();
        m_window->GetGraphicsContext()->SetClearColor( 0.2f, 0.3f, 0.3f, 1.0f);
        m_window->GetGraphicsContext()->EndFrame();
    }
}

void Core::Application::RenderFrame() {
}

bool Core::Application::UnInitialize() {
     m_console->AddLog(LogLevel::INFO, "Engine uninitialized!");
    return true;
}
