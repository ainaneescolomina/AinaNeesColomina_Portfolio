#include <iostream>
#include <string>

extern "C" {
    const char* process_command(const char* input);
}

static std::string result;

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

#ifndef __EMSCRIPTEN__
int main() {
    std::cout << process_command("help") << std::endl;
    return 0;
}
#endif