//
// Created by 16173 on 2022/3/24.
//

#ifndef CILBLOCK_DEBUG_H
#define CILBLOCK_DEBUG_H

#include "string"

enum class DEBUG_LEVEL{
    CRITICAL=0,
    PUBLISH,
    INFO,
    LOG,
    MESSAGE,
    DEBUG,
    ERROR,
};

class Debug{
private:
    static void _setStyle(DEBUG_LEVEL level);
    static void _outputOrIgnore(const char *msg, DEBUG_LEVEL level);
    static void _runFunctionOrIgnore(bool (*f)(), DEBUG_LEVEL level);
    static void _format();
public:
    static DEBUG_LEVEL debugLevel;
    static int depth;
    Debug()=default;
    ~Debug()=default;
    static void init();
    static void init(const char *fp, const char *mode="w", DEBUG_LEVEL level=DEBUG_LEVEL::PUBLISH);
    static void info(const char *msg);
    static void log(const char *msg);
    static void msg(const char *msg);
    static void debug(const char *msg);
    static void error(const char *msg);
    static void critical(const char *msg);

    static void info(bool (*f)());
    static void log(bool (*f)());
    static void msg(bool (*f)());
    static void debug(bool (*f)());
    static void error(bool (*f)());
    static void critical(bool (*f)());

    static void dive();
    static void dive(const char *msg,DEBUG_LEVEL level=Debug::debugLevel);
    static void surface();
    static void surface(const char *msg,DEBUG_LEVEL level=Debug::debugLevel);
};


#endif //CILBLOCK_DEBUG_H
