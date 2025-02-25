//
// Created by IDKTHIS on 16.02.2025.
//

#include "WindowInputComponent.h"

WindowInputComponent::WindowInputComponent() : _mouseX(0), _mouseY(0) {
}

WindowInputComponent::~WindowInputComponent() {
}

bool WindowInputComponent::IsKeyPressed(int32_t key) const {
    std::lock_guard<std::mutex> lock(_keyMutex);
    auto it = _keyStates.find(key);
    return (it != _keyStates.end()) ? it->second : false;
}

bool WindowInputComponent::IsMouseButtonPressed(uint8_t button) const {
    std::lock_guard<std::mutex> lock(_mouseMutex);
    auto it = _mouseButtonStates.find(button);
    return (it != _mouseButtonStates.end()) ? it->second : false;
}

void WindowInputComponent::SetMousePosition(int x, int y) {
    std::lock_guard<std::mutex> lock(_mousePositionMutex);
        deltaX = x;
        deltaY = y;
}



void WindowInputComponent::GetMousePosition(int &x, int &y) const {
    std::lock_guard<std::mutex> lock(_mousePositionMutex);
    x = _mouseX;
    y = _mouseY;
}

void WindowInputComponent::EventHandler(Event event) {
    if (event.type == EventType::KeyPressed) {
        OnKeyDown(event.key.key);
    }
    if (event.type == EventType::KeyReleased) {
        OnKeyUp(event.key.key);
    }
    if (event.type == EventType::MouseButtonPressed) {
        OnMouseButtonDown(event.key.key);
    }
    if (event.type == EventType::MouseButtonReleased) {
        OnMouseButtonUp(event.key.key);
    }
    if (event.type == EventType::MouseMoved) {
        SetMousePosition(event.mouse.x, event.mouse.y);
    }
}

void WindowInputComponent::OnKeyDown(int32_t key) {
    std::lock_guard<std::mutex> lock(_keyMutex);
    _keyStates[key] = true;
}

void WindowInputComponent::OnKeyUp(int32_t key) {
    std::lock_guard<std::mutex> lock(_keyMutex);
    _keyStates[key] = false;
}

void WindowInputComponent::OnMouseButtonDown(uint8_t button) {
    std::lock_guard<std::mutex> lock(_mouseMutex);
    _mouseButtonStates[button] = true;
}

void WindowInputComponent::OnMouseButtonUp(uint8_t button) {
    std::lock_guard<std::mutex> lock(_mouseMutex);
    _mouseButtonStates[button] = false;
}

void WindowInputComponent::Clear() {
    std::lock_guard<std::mutex> lock1(_keyMutex);
    std::lock_guard<std::mutex> lock2(_mouseMutex);
    _keyStates.clear();
    _mouseButtonStates.clear();
}