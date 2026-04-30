#pragma once
#include <string>
#include "ProjectManager.h"

class State;

class CommandManager {
public:

    std::string handle(const std::string& cmd, State& state);

    std::string getPromptPath(const State& state);

private:
    ProjectManager projectManager{};

    std::string handleRoot(const std::string& cmd, State& state);
    std::string handleAbout(const std::string& cmd, State& state);
    std::string handleContact(const std::string& cmd, State& state);
    std::string handleProjects(const std::string& cmd, State& state);
    std::string handleProjectView(const std::string& cmd, State& state);

    std::string header(const std::string& title);
};