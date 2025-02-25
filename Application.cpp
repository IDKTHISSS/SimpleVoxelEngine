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

bool Core::BaseApplication::Initialize() {
    SimpleConsole::Get()->subscribe([this](LogLevel log_level,const std::string& logMessage) {
        std::cout << logMessage << std::endl;
    });

    SimpleConsole::Get()->AddLog(LogLevel::INFO, "Engine initialized!");
    return true;
}

void Core::BaseApplication::Run() {
    IsRunning = true;
    Core::WindowProps props;
    props.title = std::string("Simple Voxel Engine | ") + ENGINE_VERSION;
    props.width = 1920;
    props.height = 1080;
    props.vsync = false;
    m_window = Window_SDL::Create(props);

    m_window->Init(EWindowMode::OpenGL);


    SimpleConsole::Get()->AddLog(LogLevel::INFO, "Running...");
    MainLoop();
}

void Core::BaseApplication::MainLoop() {
    bool ConsoleWindowKeyPressed = false;
    while (IsRunning) {
        m_window->GetGraphicsContext()->BeginFrame();
        IsRunning = !m_window->ShouldClose;
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL3_NewFrame();
        ImGui::NewFrame();
        SimpleConsole::Get()->Draw();


        if (m_window->InputComponent->IsKeyPressed(SDLK_GRAVE)) {
            if (!ConsoleWindowKeyPressed) {
                SimpleConsole::Get()->ToggleShow();
                ConsoleWindowKeyPressed = true;
            }
        } else {
            ConsoleWindowKeyPressed = false;
        }

        m_window->Update();
        RenderFrame();
        ImGui::Render();
        m_window->GetGraphicsContext()->SetClearColor( 0.2f, 0.3f, 0.3f, 1.0f);
        m_window->GetGraphicsContext()->EndFrame();
    }
}

void Core::BaseApplication::RenderFrame() {
}

bool Core::BaseApplication::UnInitialize() {
    SimpleConsole::Get()->AddLog(LogLevel::INFO, "Engine uninitialized!");
    return true;
}
