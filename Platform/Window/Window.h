//
// Created by IDKTHIS on 16.02.2025.
//

#pragma once
#include <cstdint>
#include <string>


class IGraphicsContext;
class WindowInputComponent;
enum EWindowMode {
    OpenGL
};
namespace Core {
    struct WindowProps {
        std::string title;
        uint32_t width;
        uint32_t height;
        bool vsync = true;
    };

    class Window {
    public:
        bool ShouldClose = false;
        WindowInputComponent* InputComponent = nullptr;
        virtual ~Window() = default;

        virtual void Update() = 0;
        virtual void PullEvents() = 0;
        virtual void Init(EWindowMode mode) = 0;
        virtual uint32_t GetWidth() const = 0;
        virtual uint32_t GetHeight() const = 0;
        virtual bool IsVSync() const = 0;
        virtual void SetWindowTitle(const char *NewTitle) = 0;
        virtual bool IsFocused() = 0;
        virtual void SwapBuffers() = 0;
        virtual IGraphicsContext* GetGraphicsContext() { return m_renderContext;};
        static Window* Create(const WindowProps& props);
    protected:
        IGraphicsContext* m_renderContext = nullptr;
        virtual void InitImGui() = 0;
    };
}
