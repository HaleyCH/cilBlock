//
// Created by 16173 on 2022/3/24.
//

#include "Debug.h"
#include "iostream"

void Debug::init() {
    Debug::init("./runtime.log");
}

void Debug::init(const char *fp, const char *mode, DEBUG_LEVEL level) {
    freopen_s(&_outputStream, fp, mode, stderr);
    Debug::depth = 0;
    Debug::debugLevel = level;
}

void Debug::_outputOrIgnore(const char *msg, DEBUG_LEVEL level) {
    if (level < Debug::debugLevel) {
        return;
    }
    _format();
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
    std::clog << msg << std::endl;
}

void Debug::_format() {
    for (int i = 0; i < Debug::depth; ++i) {
        std::clog << " ";
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
    if (level < Debug::debugLevel) {
        return;
    }
    _format();
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
    f();
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

void Debug::dive(int i) {
    _format();
    std::clog<<"[+]Dive in."<<std::endl;
    Debug::depth += i;
}

void Debug::surface(int i) {
    _format();
    std::clog<<"[-]Surface out."<<std::endl;
    Debug::depth -= i;
}

