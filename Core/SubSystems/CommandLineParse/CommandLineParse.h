//
// Created by IDKTHIS on 24.02.2025.
//

#ifndef COMMANDLINEPARSE_H
#define COMMANDLINEPARSE_H
#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>

class CommandLineParser {
public:
    static void parse(int argc, char* argv[]) {
        std::string currentCommand;
        for (int i = 1; i < argc; ++i) {
            std::string arg = argv[i];

            if (arg[0] == '+') {
                currentCommand = arg.substr(1);
                commands[currentCommand] = {};
            } else if (arg[0] == '-') {
                std::string param = arg.substr(1);
                if (i + 1 < argc && argv[i + 1][0] != '+' && argv[i + 1][0] != '-') {
                    params[param] = argv[++i];
                } else {
                    params[param] = "";
                }
            } else {
                if (!currentCommand.empty()) {
                    commands[currentCommand].push_back(arg);
                } else {
                    positionalArgs.push_back(arg);
                }
            }
        }
    }

    static bool hasParam(const std::string& param) {
        return params.find(param) != params.end();
    }

    static std::string getParam(const std::string& param, const std::string& defaultValue = "") {
        auto it = params.find(param);
        return it != params.end() ? it->second : defaultValue;
    }

    static bool hasCommand(const std::string& command) {
        return commands.find(command) != commands.end();
    }

    static const std::vector<std::string>& getCommandArgs(const std::string& command) {
        static const std::vector<std::string> empty;
        auto it = commands.find(command);
        return it != commands.end() ? it->second : empty;
    }

    static const std::vector<std::string>& getPositionalArgs() {
        return positionalArgs;
    }

private:
    static std::unordered_map<std::string, std::vector<std::string>> commands;
    static std::unordered_map<std::string, std::string> params;
    static std::vector<std::string> positionalArgs;
};

std::unordered_map<std::string, std::vector<std::string>> CommandLineParser::commands;
std::unordered_map<std::string, std::string> CommandLineParser::params;
std::vector<std::string> CommandLineParser::positionalArgs;

#endif //COMMANDLINEPARSE_H
