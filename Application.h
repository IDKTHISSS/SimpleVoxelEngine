//
// Created by IDKTHIS on 16.02.2025.
//

#pragma once
#include <memory>

#include "Core/SubSystems/Console/SimpleConsole.h"
#include "Platform/GraphicsAPI/APIContext.h"

namespace Core {
    class Window;

    class BaseApplication {
    public:
        bool IsRunning;

    public:

        virtual bool Initialize();
        virtual void Run();

        virtual void RenderFrame();
        virtual bool UnInitialize();
        Window* GetWindow() const { return m_window; }

    protected:
        Window* m_window = nullptr;
    private:
        void MainLoop();
    };
}
