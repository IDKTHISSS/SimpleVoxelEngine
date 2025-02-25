//
// Created by IDKTHIS on 16.02.2025.
//

#pragma once
#include <cstdint>
#include <mutex>
#include <unordered_map>

enum class EventType {
    WindowResized,
    KeyPressed,
    KeyReleased,
    MouseButtonPressed,
    MouseButtonReleased,
    MouseMoved
};

struct Event {
    EventType type;
    union {
        struct { int width, height; } resize;
        struct { int key; } key;
        struct { float x, y; } mouse;
    };
};

class WindowInputComponent {
public:
    float deltaX;
    float deltaY;

    WindowInputComponent();
    ~WindowInputComponent();
    bool IsKeyPressed(int32_t key) const;
    bool IsMouseButtonPressed(uint8_t button) const;
    void SetMousePosition(int x, int y);
    void GetMousePosition(int& x, int& y) const;
    void EventHandler(Event event);
private:
    void OnKeyDown(int32_t key);
    void OnKeyUp(int32_t key);
    void OnMouseButtonDown(uint8_t button);
    void OnMouseButtonUp(uint8_t button);
    void Clear();
private:
    std::unordered_map<uint32_t, bool> _keyStates;
    mutable std::mutex _keyMutex;

    std::unordered_map<uint8_t, bool> _mouseButtonStates;
    mutable std::mutex _mouseMutex;

    int _mouseX, _mouseY;

    mutable std::mutex _mousePositionMutex;
};
