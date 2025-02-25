//
// Created by IDKTHIS on 17.02.2025.
//

#pragma once


class IShader;

class World {
public:
    virtual void RenderWorld() = 0;

protected:
    unsigned int m_vao = 0;
    unsigned int m_vbo = 0;
    unsigned long long m_vertices = 0;
    float* m_buffer = nullptr;
    IShader* m_shader = nullptr;
};
