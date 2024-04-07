#pragma once

#include "iot-tp/iot-tp-consts.h"

#ifdef CXX
#define START_NAMESPACE(name) namespace name {
#define END_NAMESPACE(name) }

#define USE_NAMESPACE(name) using namespace name;
#else
#define START_NAMESPACE(name)
#define END_NAMESPACE(name)

#define USE_NAMESPACE(name) 
#endif

#define START_FULL_NAMESPACE(name) \
    START_NAMESPACE(nordli) \
    START_NAMESPACE(iottp) \
    START_NAMESPACE(name)
#define END_FULL_NAMESPACE(name) \
    END_NAMESPACE(nordli) \
    END_NAMESPACE(iottp) \
    END_NAMESPACE(name)

#define START_SIMPLE_NAMESPACE \
    START_NAMESPACE(nordli) \
    START_NAMESPACE(iottp)
#define END_SIMPLE_NAMESPACE \
    END_NAMESPACE(nordli) \
    END_NAMESPACE(iottp)
