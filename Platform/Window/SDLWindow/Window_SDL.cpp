//
// Created by IDKTHIS on 23.02.2025.
//

#include "Window_SDL.h"


#include <backends/imgui_impl_sdl3.h>

#include "Engine/Application.h"
#include "Engine/Core/SubSystems/Console/SimpleConsole.h"
#include "Engine/Core/SubSystems/WindowInput/WindowInputComponent.h"

Window_SDL::Window_SDL(const Core::WindowProps &props) {
    InputComponent = new WindowInputComponent();
    m_props = props;
}

Window_SDL::~Window_SDL() {
    SDL_DestroyWindow(m_window);
    SDL_Quit();
}

void Window_SDL::Update() {
    PullEvents();
}

void Window_SDL::InitImGui() {
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    ImGui::StyleColorsDark();

    // Setup Platform/Renderer backends
    ImGui_ImplSDL3_InitForOpenGL(m_window, m_glContext);
    m_renderContext->InitImGui();
}

void Window_SDL::SetWindowTitle(const char *NewTitle) {
    SDL_SetWindowTitle(m_window, NewTitle);
}

bool Window_SDL::IsFocused() {
    return SDL_GetWindowFlags(m_window) & SDL_WINDOW_INPUT_FOCUS;
}

void Window_SDL::PullEvents() {
    SDL_Event event;

    while(SDL_PollEvent(&event)) {

        if(event.type == SDL_EVENT_QUIT) {
            ShouldClose = true;
        }
        Event WindowEvent;
        if (event.type == SDL_EVENT_KEY_DOWN) {
            WindowEvent.type = EventType::KeyPressed;
            WindowEvent.key.key = event.key.key;
            InputComponent->EventHandler(WindowEvent);
        }
        if (event.type == SDL_EVENT_KEY_UP) {
            WindowEvent.type = EventType::KeyReleased;
            WindowEvent.key.key = event.key.key;
            InputComponent->EventHandler(WindowEvent);
        }
        if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
            WindowEvent.type = EventType::MouseButtonPressed;
            WindowEvent.key.key = event.button.button;
            InputComponent->EventHandler(WindowEvent);
        }
        if (event.type == SDL_EVENT_MOUSE_BUTTON_UP) {
            WindowEvent.type = EventType::MouseButtonReleased;
            WindowEvent.key.key = event.button.button;
            InputComponent->EventHandler(WindowEvent);
        }
        if (event.type == SDL_EVENT_MOUSE_MOTION) {
            WindowEvent.type = EventType::MouseMoved;
            WindowEvent.mouse.x = event.motion.xrel;
            WindowEvent.mouse.y = event.motion.yrel;
            InputComponent->EventHandler(WindowEvent);
            InputComponent->deltaX += event.motion.xrel;
            InputComponent->deltaY += event.motion.yrel;
        }
        ImGui_ImplSDL3_ProcessEvent(&event);
    }
}

void Window_SDL::Init(EWindowMode mode) {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_WindowFlags window_flags;
    if (mode == EWindowMode::OpenGL) {
        window_flags = SDL_WINDOW_OPENGL;
    }
    window_flags |= SDL_WINDOW_RESIZABLE;
    m_window = SDL_CreateWindow(
        m_props.title.c_str(),
        m_props.width,
        m_props.height,
        window_flags
    );

    if (mode == EWindowMode::OpenGL) {
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_DEBUG_FLAG);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
        SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
        SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
        m_glContext = SDL_GL_CreateContext(m_window);
        if(!m_glContext) {
            //Core::Application::Get()->GetConsole()->AddLog(LogLevel::ERROR, "Failed to create OpenGL context");
        }
        SDL_GL_MakeCurrent(m_window, m_glContext);
        SDL_SetWindowPosition(m_window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
        SDL_GL_SetSwapInterval(false);
        //  SDL_SetWindowMouseGrab(m_window, true);
        //   SDL_SetWindowRelativeMouseMode(m_window, true);
        m_renderContext = new GLContext();
        m_renderContext->Init(this);
    }
    InitImGui();
}

void Window_SDL::SwapBuffers() {
    SDL_GL_SwapWindow(m_window);
}

Core::Window * Window_SDL::Create(const Core::WindowProps &props) {
    return new Window_SDL(props);
}
