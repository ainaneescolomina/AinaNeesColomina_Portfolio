#include <string>
#include "Commands/CommandManager.h"
#include "Engine/Engine.h"

static CommandManager commandManager;
static State state;

extern "C" {

    const char* process_command(const char* input) {
        static std::string result;

        std::string cmd(input);

        result = commandManager.handle(cmd, state);

        return result.c_str();
    }

}