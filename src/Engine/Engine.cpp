#include "Engine.h"
#include "../Commands/CommandManager.h"

std::string Engine::processCommand(const std::string& input) {
    CommandManager router;
    return router.handle(input, state);
}
