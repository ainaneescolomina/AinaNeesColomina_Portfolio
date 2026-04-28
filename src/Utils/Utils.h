#pragma once
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
    std::string currentProject;
};