#pragma once
#include <string>

class State;

class CommandManager {
public:
    std::string handle(const std::string& cmd, State& state);

private:
    std::string handleRoot(const std::string& cmd, State& state);
    std::string handleAbout(const std::string& cmd, State& state);
    std::string handleContact(const std::string& cmd, State& state);
    std::string handleProjects(const std::string& cmd, State& state);
    std::string handleProjectView(const std::string& cmd, State& state);

    std::string header(const std::string& title);
};