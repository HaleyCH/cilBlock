//
// Created by 16173 on 2022/3/24.
//

#include "Debug.h"
#include "iostream"

void Debug::init() {
    Debug::init("./runtime.log");
}

void Debug::init(const char *fp, const char *mode, DEBUG_LEVEL level) {
    FILE *_outputStream;
    freopen_s(&_outputStream, fp, mode, stderr);
//    Debug::depth = 0;
//    Debug::debugLevel = level;
}

void Debug::_outputOrIgnore(const char *msg, DEBUG_LEVEL level) {
    if (level > Debug::debugLevel) {
        return;
    }
    _format();
    _setStyle(level);
    std::clog << msg << std::endl;
}

void Debug::_format() {
    for (int i = 0; i < Debug::depth; ++i) {
        std::clog << "   ";
    }
}

void Debug::info(const char *msg) {
    _outputOrIgnore(msg, DEBUG_LEVEL::INFO);
}

void Debug::log(const char *msg) {
    _outputOrIgnore(msg, DEBUG_LEVEL::LOG);
}

void Debug::msg(const char *msg) {
    _outputOrIgnore(msg, DEBUG_LEVEL::MESSAGE);
}

void Debug::debug(const char *msg) {
    _outputOrIgnore(msg, DEBUG_LEVEL::DEBUG);
}

void Debug::error(const char *msg) {
    _outputOrIgnore(msg, DEBUG_LEVEL::ERROR);
}

void Debug::critical(const char *msg) {
    _outputOrIgnore(msg, DEBUG_LEVEL::CRITICAL);
}

void Debug::_runFunctionOrIgnore(bool (*f)(), DEBUG_LEVEL level) {
    if (level > Debug::debugLevel) {
        return;
    }
    _format();
    _setStyle(level);
    dive("Call function.");
    bool stat = f();

    surface();

    if (stat) {
        surface("Successfully call function.");
        return;
    }
    surface("Failed to call function.");
}

void Debug::info(bool (*f)()) {
    _runFunctionOrIgnore(f, DEBUG_LEVEL::INFO);
}

void Debug::log(bool (*f)()) {
    _runFunctionOrIgnore(f, DEBUG_LEVEL::LOG);
}

void Debug::msg(bool (*f)()) {
    _runFunctionOrIgnore(f, DEBUG_LEVEL::MESSAGE);
}

void Debug::debug(bool (*f)()) {
    _runFunctionOrIgnore(f, DEBUG_LEVEL::DEBUG);
}

void Debug::error(bool (*f)()) {
    _runFunctionOrIgnore(f, DEBUG_LEVEL::ERROR);
}

void Debug::critical(bool (*f)()) {
    _runFunctionOrIgnore(f, DEBUG_LEVEL::CRITICAL);
}

void Debug::dive() {
    dive("Dive in.");
}

void Debug::dive(const char *msg, DEBUG_LEVEL level) {
    if (level > Debug::debugLevel) {
        Debug::depth += 1;
        return;
    }
    _format();
    std::clog << "[+]" << msg << std::endl;
    Debug::depth += 1;
}

void Debug::surface() {
    surface("Surface out.");
}

void Debug::surface(const char *msg, DEBUG_LEVEL level) {
    if (level > Debug::debugLevel) {
        Debug::depth -= 1;
        return;
    }
    _format();
    std::clog << "[-]" << msg << std::endl;
    Debug::depth -= 1;
}


void Debug::_setStyle(DEBUG_LEVEL level) {
    switch (level) {
        case DEBUG_LEVEL::INFO:
            std::clog << "[-]";
            break;
        case DEBUG_LEVEL::LOG:
            std::clog << "[=]";
            break;
        case DEBUG_LEVEL::MESSAGE:
            std::clog << "[*]";
            break;
        case DEBUG_LEVEL::DEBUG:
            std::clog << "[#]";
            break;
        case DEBUG_LEVEL::ERROR:
            std::clog << "[!]";
            break;
        case DEBUG_LEVEL::PUBLISH:
            std::clog << "[?]";
            break;
        case DEBUG_LEVEL::CRITICAL:
            std::clog << "[@]";
            break;
    }
}

