//
// Created by IDKTHIS on 23.02.2025.
//

#ifndef WINDOW_SDL_H
#define WINDOW_SDL_H
#include "imgui.h"
#include "backends/imgui_impl_sdl3.h"

#include <SDL3/SDL.h>
#include <SDL3/SDL_events.h>

#include "Engine/Platform/GraphicsAPI/OpenGL/GLContext.h"
#include "Engine/Platform/Window/Window.h"



class Window_SDL : public Core::Window {
public:
    explicit Window_SDL(const Core::WindowProps& props);
    ~Window_SDL() override;

    void Update() override;
    void SetWindowTitle(const char *NewTitle) override;
    bool IsFocused() override;
    void PullEvents() override;

    uint32_t GetWidth() const override { return m_props.width; };
    uint32_t GetHeight() const override { return m_props.height; };
    bool IsVSync() const override { return m_props.vsync; }

    void Init(EWindowMode mode) override;
    void SwapBuffers();

    static Core::Window* Create(const Core::WindowProps& props);
private:
    void InitImGui() override;
private:
    SDL_Window* m_window = nullptr;
    SDL_GLContext m_glContext = nullptr;

    Core::WindowProps m_props;
};



#endif //WINDOW_SDL_H
