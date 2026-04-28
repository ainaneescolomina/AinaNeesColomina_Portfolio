#include "CommandManager.h"
#include "../Engine/Engine.h"

std::string CommandManager::handle(const std::string& cmd, State& state) {

    switch (state.context) {

    case Context::ROOT:
        return handleRoot(cmd, state);

    case Context::ABOUT:
        return handleAbout(cmd, state);

    case Context::PROJECTS:
        return handleProjects(cmd, state);

    case Context::PROJECT_VIEW:
        return handleProjectView(cmd, state);

    default:
        return "Invalid state";
    }
}

std::string CommandManager::handleRoot(const std::string& cmd, State& state)
{
    if (cmd == "help") {
        return header("ROOT HELP") +
            "Available commands:\n"
            "- about\n"
            "- contact\n"
            "- projects\n"
            "- help";
    }

    else if (cmd == "about") {
        state.context = Context::ABOUT;

        return header("ABOUT") +
            "Welcome to my portfolio\n"
            "I'm a DAE student\n"
            "----------------------\n"
            "Type 'help' or 'back'";
    }

    else if (cmd == "contact") {
        state.context = Context::CONTACT;

        return header("CONTACT") +
            "Email: example@mail.com\n"
            "GitHub: github.com/you\n"
            "Type 'back'";
    }

    else if (cmd == "projects") {
        state.context = Context::PROJECTS;

        return header("PROJECTS") +
            "Available projects:\n"
            "- engine\n"
            "- project1\n"
            "- consoleSystem\n\n"
            "Type 'open <name>' or 'back'";
    }

    return "Unknown command. Type 'help'";
}

std::string CommandManager::handleAbout(const std::string& cmd, State& state)
{
    if (cmd == "help") {
        return header("ABOUT") +
            "Commands:\n"
            "- experience\n"
            "- skills\n"
            "- back";
    }

    if (cmd == "experience") {
        return header("EXPERIENCE") +
            "- Game dev student\n"
            "- C++ / SDL / WebAssembly\n"
            "- Engine development focus";
    }

    if (cmd == "skills") {
        return header("SKILLS") +
            "- C++\n"
            "- Engine architecture\n"
            "- WebAssembly (Emscripten)\n"
            "- SDL / graphics systems";
    }

    if (cmd == "back") {
        state.context = Context::ROOT;
        return "Returning to ROOT...";
    }

    return "Unknown command in ABOUT. Type 'help'";
}

std::string CommandManager::handleContact(const std::string& cmd, State& state)
{
    if (cmd == "help") {
        return header("CONTACT") +
            "Commands:\n"
            "- email\n"
            "- github\n"
            "- back";
    }

    if (cmd == "email") {
        return header("EMAIL") +
            "example@mail.com";
    }

    if (cmd == "github") {
        return header("GITHUB") +
            "github.com/yourname";
    }

    if (cmd == "back") {
        state.context = Context::ROOT;
        return "Returning to ROOT...";
    }

    return "Unknown command in CONTACT. Type 'help'";
}

std::string CommandManager::handleProjects(const std::string& cmd, State& state)
{
    if (cmd == "help") {
        return header("PROJECTS") +
            "Commands:\n"
            "- list\n"
            "- open <name>\n"
            "- back";
    }

    if (cmd == "list") {
        return header("PROJECT LIST") +
            "1. engine\n"
            "2. dungeonCrawler\n"
            "3. consoleSystem";
    }

    if (cmd.rfind("open", 0) == 0) {
        state.context = Context::PROJECT_VIEW;

        return header("PROJECT") +
            "Opening project...\n"
            "Loading assets...\n"
            "Done.\n\n"
            "Type 'back' to exit project view";
    }

    if (cmd == "back") {
        state.context = Context::ROOT;
        return "Returning to ROOT...";
    }

    return "Unknown command in PROJECTS. Type 'help'";
}

std::string CommandManager::handleProjectView(const std::string& cmd, State& state)
{
    if (cmd == "help") {
        return header("PROJECT VIEW") +
            "Commands:\n"
            "- info\n"
            "- back";
    }

    if (cmd == "info") {
        return header("PROJECT INFO") +
            "This is a simulated project window\n"
            "In a real version this would show:\n"
            "- screenshots\n"
            "- github link\n"
            "- description";
    }

    if (cmd == "back") {
        state.context = Context::PROJECTS;
        return "Returning to PROJECTS...";
    }

    return "You are inside a project. Type 'help' or 'back'.";
}

std::string CommandManager::header(const std::string& title) {
    return "\n=== " + title + " ===\n";
}
