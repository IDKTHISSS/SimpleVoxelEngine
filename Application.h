//
// Created by IDKTHIS on 16.02.2025.
//

#pragma once
#include <memory>

#include "Core/SubSystems/Console/SimpleConsole.h"
#include "Platform/GraphicsAPI/APIContext.h"

namespace Core {
    class Window;

    class Application {
    public:
        bool IsRunning;

    public:
        static std::shared_ptr<Application> Get() {
            static std::shared_ptr<Application> _instance = std::make_shared<Application>();
            return _instance;
        }
        bool Initialize();
        void Run();
        void MainLoop();
        void RenderFrame();
        bool UnInitialize();
        Window* GetWindow() const { return m_window; }
        SimpleConsole* GetConsole() { return m_console; }
        /*Render::RenderContext* GetRenderContext() const { return m_context; }

        std::shared_ptr<UShader> GetMainShader() const {return m_mainShader; }*/
    private:
        Window* m_window = nullptr;
        SimpleConsole* m_console;

        /*Render::RenderContext* m_context = nullptr;
        std::shared_ptr<UShader> m_mainShader = nullptr;*/
    };
}
