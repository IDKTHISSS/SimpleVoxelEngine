//
// Created by IDKTHIS on 16.02.2025.
//

#pragma once

#include "Engine/Platform/GraphicsAPI/APIContext.h"



class GLContext : public IGraphicsContext {
public:
     bool Init(Core::Window* windowHandle) override;
     void InitImGui() override;

     void BeginFrame() override;
     void EndFrame() override;

     IShader* CreateShader(nlohmann::json &shader) override;
     ITexture* CreateTexture(const std::string& path) override;

     void SetViewport(int width, int height) override;
     void SetClearColor(float r, float g, float b, float a) override;

     void DrawIndexed(uint32_t indexCount) override;
     static IGraphicsContext* Create();

private:
     Core::Window* m_window;
};
