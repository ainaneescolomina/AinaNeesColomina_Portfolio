#include <string>
#include "Commands/CommandManager.h"
#include "Utils/Utils.h"
#include <iostream>

static CommandManager commandManager{};
static State state;

extern "C" {

    const char* process_command(const char* input) {
        static std::string result;

        if (!input)
            return "Invalid input";

        std::string cmd(input);

        if (cmd == "reset") {
            state = State();
            return "System reset.";
        }

        result = commandManager.handle(cmd, state);

        return result.c_str();
    }

}

int main() {
    std::cout << "Portfolio console running...\n";
}