#include <string>
#include <emscripten/emscripten.h>

extern "C" {

static std::string result;

EMSCRIPTEN_KEEPALIVE
const char* process_command(const char* input) {
    std::string cmd(input);

    if (cmd == "help") {
        result = "Commands: help, about";
    }
    else if (cmd == "about") {
        result = "Handled by C++ engine";
    }
    else {
        result = "Unknown command";
    }

    return result.c_str();
}

}