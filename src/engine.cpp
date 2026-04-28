#include <iostream>
#include <string>

extern "C" {
    const char* process_command(const char* input);
}

static std::string result;

const char* process_command(const char* input) {
    std::string cmd(input);

    if (cmd == "help") {
        result =
            "HELP:\n"
            "- help : show commands\n"
            "- about : engine info\n"
            "- projects : list projects";
    }

    else if (cmd == "about") {
        result =
            "ABOUT:\n"
            "Retro Console Engine\n"
            "C++ + WebAssembly + JS UI\n"
            "Portfolio project";
    }

    else if (cmd == "projects") {
        result =
            "PROJECTS:\n"
            "1. DungeonCrawler\n"
            "2. SpaceShooter\n"
            "3. DevConsoleSystem";
    }

    else {
        result = "Unknown command. Type 'help'";
    }

    return result.c_str();
}

#ifndef __EMSCRIPTEN__
int main() {
    std::cout << process_command("help") << std::endl;
    return 0;
}
#endif