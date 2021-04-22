#include "runtime.h"

Configure *Runtime::m_configure;

Runtime::Runtime()
{
}

void Runtime::initialize()
{
    Runtime::m_configure = new Configure();
}
