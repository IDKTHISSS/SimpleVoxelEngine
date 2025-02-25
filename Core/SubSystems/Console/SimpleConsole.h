//
// Created by IDKTHIS on 24.02.2025.
//

#ifndef SIMPLECONSOLE_H
#define SIMPLECONSOLE_H

#include "imgui.h"
#include <vector>
#include <string>
#include <unordered_map>
#include <functional>
enum class LogLevel {
    INFO,
    WARNING,
    ERROR,
    DEBUG
};

class SimpleConsole {
    public:
    using LogCallback = std::function<void(const LogLevel&, const std::string&)>;
    SimpleConsole();
    using CommandFunc = std::function<void(const std::string&)>;
    void Clear() { Buffer.clear(); }
    void AddLog(LogLevel log_level, const std::string& fmt, ...);
    void RegisterCommand(const std::string& command, CommandFunc func) {
        Commands[command] = std::move(func);
    }
    void subscribe(LogCallback callback) {
        subscribers.push_back(std::move(callback));
    }
    void SetShow(bool show) { m_show = show;};
    void ToggleShow() { m_show = !m_show; };
    void Draw();

private:
    bool m_show = true;
    void RegisterCommands();
    void ExecuteCommand(const std::string& input);

    std::vector<std::string> Buffer;
    std::unordered_map<std::string, CommandFunc> Commands;
    char InputBuf[256] = {};
    bool ScrollToBottom = false;
    std::vector<LogCallback> subscribers;
};



#endif //SIMPLECONSOLE_H
