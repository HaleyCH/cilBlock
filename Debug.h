//
// Created by 16173 on 2022/3/24.
//

#ifndef CILBLOCK_DEBUG_H
#define CILBLOCK_DEBUG_H

#include "string"

enum class DEBUG_LEVEL{
    INFO=0,
    LOG,
    MESSAGE,
    DEBUG,
    ERROR,
    PUBLISH,
    CRITICAL
};

class Debug{
private:
    static FILE *_outputStream;
    static DEBUG_LEVEL debugLevel;
    void _outputOrIgnore(const char *msg, DEBUG_LEVEL level);
    static void _runFunctionOrIgnore(bool (*f)(), DEBUG_LEVEL level);
    static void _format();
public:
    static int depth;
    Debug()=default;
    ~Debug()=default;
    static void init();
    static void init(const char *fp, const char *mode="w", DEBUG_LEVEL level=DEBUG_LEVEL::PUBLISH);
    void info(const char *msg);
    void log(const char *msg);
    void msg(const char *msg);
    void debug(const char *msg);
    void error(const char *msg);
    void critical(const char *msg);

    static void info(bool (*f)());
    static void log(bool (*f)());
    static void msg(bool (*f)());
    static void debug(bool (*f)());
    static void error(bool (*f)());
    static void critical(bool (*f)());

    static void dive(int i=0);
    static void surface(int i=0);
};


#endif //CILBLOCK_DEBUG_H
