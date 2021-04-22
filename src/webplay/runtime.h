#ifndef RUNTIME_H
#define RUNTIME_H

#include "configure.h"
#include "log.h"

class Runtime
{
public:
    Runtime();
public:
    static void initialize();
    /* 全局配置 ... */
    static Configure *m_configure;
};
#endif // RUNTIME_H
