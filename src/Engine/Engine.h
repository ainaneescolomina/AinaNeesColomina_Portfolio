#pragma once
#include <iostream>
#include <string>

enum class Context {
    ROOT,
    ABOUT,
    CONTACT,
    PROJECTS,
    PROJECT_VIEW
};

struct State {
    Context context = Context::ROOT;
};

class Engine {
public:
    std::string processCommand(const std::string& input);

private:
    State state;
};
