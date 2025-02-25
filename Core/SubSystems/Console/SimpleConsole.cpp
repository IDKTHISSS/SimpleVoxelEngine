//
// Created by IDKTHIS on 24.02.2025.
//

#include "SimpleConsole.h"

#include <chrono>
#include <ctime>

SimpleConsole::SimpleConsole() {
    RegisterCommands();
}
std::string LogLevelToString(LogLevel log_level) {
    switch (log_level) {
        case LogLevel::INFO: return "INFO";
        case LogLevel::WARNING: return "WARNING";
        case LogLevel::ERROR: return "ERROR";
        case LogLevel::DEBUG: return "DEBUG";
        default: return "UNKNOWN";
    }
}
std::string GetCurrentTime() {
    auto now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    std::tm tm_buf = {};
    std::tm* tm_ptr = std::localtime(&now);
    if (tm_ptr) {
        tm_buf = *tm_ptr;
    }

    std::ostringstream oss;
    oss << std::put_time(&tm_buf, "[%Y-%m-%d %H:%M:%S]");
    return oss.str();
}
void SimpleConsole::AddLog(LogLevel log_level, const std::string& fmt, ...) {
    va_list args;
    va_start(args, fmt);
    char buf[1024];
    vsnprintf(buf, sizeof(buf), fmt.c_str(), args);
    va_end(args);

    std::string timestamp = GetCurrentTime();
    std::string log_msg = timestamp + "[" + LogLevelToString(log_level) + "] " + buf;

    Buffer.push_back(log_msg);
    for (auto& subscriber : subscribers) {
        subscriber(log_level, log_msg);
    }
}



void SimpleConsole::Draw()  {
    if (!m_show) return;
    ImGui::SetNextWindowSize(ImVec2(800, 400), ImGuiCond_FirstUseEver);
    ImGui::Begin("Simple Voxel Console", nullptr, ImGuiWindowFlags_NoCollapse);


    ImGui::BeginChild("ScrollingRegion", ImVec2(0, -ImGui::GetFrameHeightWithSpacing() - 5), false, ImGuiWindowFlags_HorizontalScrollbar);
    for (const auto& line : Buffer) {
        if (line.rfind("> ", 0) == 0) // Команда пользователя
            ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.6f, 1.0f), "%s", line.c_str());
        else // Ответ системы
            ImGui::TextUnformatted(line.c_str());
    }
    if (ScrollToBottom)
        ImGui::SetScrollHereY(1.0f);
    ImGui::EndChild();

    ImGui::Separator();

    ImGui::SetNextItemWidth(-1);
    if (ImGui::InputText("##input", InputBuf, IM_ARRAYSIZE(InputBuf), ImGuiInputTextFlags_EnterReturnsTrue)) {
        ExecuteCommand(InputBuf);
        memset(InputBuf, 0, sizeof(InputBuf));
    }

    ImGui::End();
}

void SimpleConsole::RegisterCommands() {
    RegisterCommand("clear", [this](const std::string& args) { Clear();});
}


void SimpleConsole::ExecuteCommand( const std::string &input) {
    //AddLog("> %s", input.c_str());
    auto spacePos = input.find(' ');
    std::string cmd = spacePos == std::string::npos ? input : input.substr(0, spacePos);
    std::transform(cmd.begin(), cmd.end(), cmd.begin(), ::tolower);
    std::string args = spacePos == std::string::npos ? "" : input.substr(spacePos + 1);

    auto it = Commands.find(cmd);
    if (it != Commands.end()) {
        it->second(args);
    } else {
        AddLog(LogLevel::ERROR, "Unknown command: %s", cmd.c_str());
    }

    ScrollToBottom = true;
}
