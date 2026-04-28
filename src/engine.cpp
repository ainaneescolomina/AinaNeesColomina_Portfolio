#include <iostream>
#include <string>

extern "C" {
    const char* process_command(const char* input);
}

static std::string result;
static std::string currentContext = "ROOT";

static std::string header(const std::string& ctx) {
    return "\n=== " + ctx + " ===\n";
}

const char* process_command(const char* input) {
    std::string cmd(input);

    // ================= ROOT =================
    if (currentContext == "ROOT") {

        if (cmd == "help") {
            result =
                header("ROOT HELP") +
                "Available commands:\n"
                "- about\n"
                "- contact\n"
                "- projects\n"
                "- help";
        }

        else if (cmd == "about") {
            currentContext = "ABOUT";
            result =
                header("ABOUT") +
                "Welcome to my portfolio\n"
                "I'm a DAE student bla bla bla\n"
                "---------------------------------------------------\n"
                "Type 'help' for options\n"
                "Type 'back' to return";
        }

        else if (cmd == "contact") {
            currentContext = "CONTACT";
            result =
                header("CONTACT") +
                "Email: example@mail.com\n"
                "GitHub: github.com/you\n"
                "Type 'back' to return";
        }

        else if (cmd == "projects") {
            currentContext = "PROJECTS";
            result =
                header("PROJECTS") +
                "Available projects:\n"
                "- engine\n"
                "- project1\n"
                "- consoleSystem\n\n"
                "Type 'open <name>' or 'back'";
        }

        else {
            result = "Unknown command. Type 'help'";
        }
    }

    // ================= ABOUT =================
    else if (currentContext == "ABOUT") {

        if (cmd == "help") {
            result =
                header("ABOUT HELP") +
                "Commands:\n"
                "- back (return to root)\n"
                "- experience\n"
                "- skills";
        }

        else if (cmd == "experience") {
            result =
                header("EXPERIENCE") +
                "- Game dev student\n"
                "- C++ / SDL / WebAssembly\n"
                "- Engine development focus";
        }

        else if (cmd == "back") {
            currentContext = "ROOT";
            result = "Returning to ROOT...";
        }

        else {
            result = "Unknown command in ABOUT";
        }
    }

    // ================= CONTACT =================
    else if (currentContext == "CONTACT") {

        if (cmd == "help") {
            result =
                header("CONTACT HELP") +
                "- email\n"
                "- github\n"
                "- back";
        }

        else if (cmd == "back") {
            currentContext = "ROOT";
            result = "Returning to ROOT...";
        }

        else {
            result = "Unknown command in CONTACT";
        }
    }

    // ================= PROJECTS =================
    else if (currentContext == "PROJECTS") {

        if (cmd == "help") {
            result =
                header("PROJECTS HELP") +
                "- open <name>\n"
                "- list\n"
                "- back";
        }

        else if (cmd == "list") {
            result =
                header("PROJECT LIST") +
                "1. engine\n"
                "2. project1\n"
                "3. consoleSystem";
        }

        else if (cmd == "back") {
            currentContext = "ROOT";
            result = "Returning to ROOT...";
        }

        else if (cmd.rfind("open", 0) == 0) {
            result =
                header("PROJECT") +
                "Opening project...\n"
                "Loading assets...\n"
                "Done.\n"
                "(simulated project view)\n\n"
                "Type 'back' to exit project";
            currentContext = "PROJECT_VIEW";
        }

        else {
            result = "Unknown command in PROJECTS";
        }
    }

    // ================= PROJECT VIEW =================
    else if (currentContext == "PROJECT_VIEW") {

        if (cmd == "back") {
            currentContext = "PROJECTS";
            result = "Returning to PROJECTS...";
        }
        else if (cmd == "help") {
            result =
                header("PROJECT VIEW") +
                "- back (return to projects)\n"
                "- info (project details)";
        }
        else {
            result = "You are inside a project. Type 'back'.";
        }
    }

    return result.c_str();
}

#ifndef __EMSCRIPTEN__
int main() {
    std::cout << process_command("help") << std::endl;
    return 0;
}
#endif