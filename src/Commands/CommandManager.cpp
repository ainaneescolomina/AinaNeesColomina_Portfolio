#include "CommandManager.h"
#include "../Utils/Utils.h"

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

std::string CommandManager::getPromptPath(const State& state)
{
    switch (state.context) {
    case Context::ROOT:         return "Root";
    case Context::ABOUT:        return "About";
    case Context::CONTACT:      return "Contact";
    case Context::PROJECTS:     return "Projects";
    case Context::PROJECT_VIEW: return "Projects/" + state.currentProject;
    default:                    return "Unknown";
    }
}

std::string CommandManager::handleRoot(const std::string& cmd, State& state)
{
    if (cmd == "help" || cmd == "ls") {
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
            "Hi i'm Aina, welcome to my portfolio!\n"
            "I'm a DAE student with a mix of C++ programming, 3D representation, and graphic design.\n"
            "I like the intersection of tech and creativity, building things that not only work well but feel engaging and immersive.\n"
            "----------------------\n"
            "Type 'help' or 'back'";
    }

    else if (cmd == "contact") {
        state.context = Context::CONTACT;

        return header("CONTACT") +
            "Email: ainaneescolomina@gmail.com\n"
            "GitHub: https://github.com/ainaneescolomina\n"
            "Type 'back'";
    }

    else if (cmd == "projects") {
        state.context = Context::PROJECTS;

        return header("PROJECTS") +
            "Available projects:\n"
            "- Galaga Engine\n"
            "- Roberto el lagarto\n"
            "- Personal Proj\n\n"
            "Type 'open <name>' or 'back'";
    }

    return "Unknown command. Type 'help'";
}

std::string CommandManager::handleAbout(const std::string& cmd, State& state)
{
    if (cmd == "help" || cmd == "ls") {
        return header("ABOUT") +
            "Commands:\n"
            "- experience\n"
            "- education\n"
            "- back";
    }

    if (cmd == "experience") {
        return header("EXPERIENCE") +
            "- Programming Intern\n"
            "       at Space4Earth (2023 – 2024)\n"
            "       Programming in C++ and Unity. 3D data representation.\n"
            "- Content Editor\n"
            "       at CLIJ magazine (2022 – 2023)\n"
            "       Contributor to the bi-monthly youth magazine CLIJ. Personal column for video game recommendations.\n"
            "- Graphic Design Intern\n"
            "       at ACV Global (2022)\n"
            "       Creation of social media content and graphic design work for the publisher's website and external clients.";
    }

    if (cmd == "education") {
        return header("EDUCATION") +
            "- Digital Arts and Entertainment, Game Development\n"
            "       Howest DAE - (2024 – 2027)\n"
            "- 3D Animation, Games and Interactive Environments, Professional Profile in Virtual Worlds,\n"
            "Augmented Reality and Gamification (Advanced Vocational Training)\n"
            "       Escola Sant Marc - (2022 – 2024)\n"
            "- Interactive Graphic Product Assistance (Intermediate Vocational Training)\n"
            "       CIC-Elisava - (2020 – 2022)";
    }

    if (cmd == "back") {
        state.context = Context::ROOT;
        return "Returning to ROOT...";
    }

    return "Unknown command in ABOUT. Type 'help'";
}

std::string CommandManager::handleContact(const std::string& cmd, State& state)
{
    if (cmd == "help" || cmd == "ls") {
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
    if (cmd == "help" || cmd == "ls") {
        return header("PROJECTS") +
            "Commands:\n"
            "  list          -> Show all project names\n"
            "  open <name>   -> View specific project details\n"
            "  back          -> Return to main menu\n";
    }

    if (cmd == "list") {
        std::string out = header("PROJECT LIST");
        out += "Discover my latest work:\n\n"; // Added spacing

        for (const auto& p : projectManager.getProjects()) {
            // Added indentation and a bullet point style
            out += "  [+] " + p.name + "\n";
        }

        out += "\nType 'open <project name>' to see more.";
        return out;
    }

    if (cmd.rfind("open", 0) == 0)
    {
        std::string name = cmd.substr(5);

        const Project* project = projectManager.findProject(name);

        if (!project)
            return "Project not found.";

        state.context = Context::PROJECT_VIEW;
        state.currentProject = name;

        return header("PROJECT OPENED") +
            "Name: " + project->name + "\n" +
            "Description: " + project->description + "\n" +
            "GitHub: " + project->githubLink +
            "\n[OPEN_WINDOW:" + project->name + "]";
    }

    if (cmd == "back") {
        state.context = Context::ROOT;
        return "Returning to ROOT...";
    }

    return "Unknown command in PROJECTS. Type 'help'";
}

std::string CommandManager::handleProjectView(const std::string& cmd, State& state)
{
    const Project* project = projectManager.findProject(state.currentProject);

    if (!project)
        return "No project selected.";

    if (cmd == "help") {
        return header("PROJECT VIEW") +
            "- info\n"
            "- back";
    }

    if (cmd == "info") {
        return header("PROJECT: " + project->name) +
            "  > Status:      Completed\n" +
            "  > Description: " + project->description + "\n" +
            "  > Link:        " + project->githubLink + "\n" +
            "\n  (Generating preview window...)\n" +
            "[OPEN_WINDOW:" + project->name + "]";
    }

    if (cmd == "back") {
        state.context = Context::PROJECTS;
        state.currentProject.clear();
        return "Returning to PROJECTS...";
    }

    return "Unknown command in PROJECT VIEW.";
}

std::string CommandManager::header(const std::string& title) {
    return "\n=== " + title + " ===\n";
}
