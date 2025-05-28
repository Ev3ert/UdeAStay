#ifndef METRICS_H
#define METRICS_H

#include "ConUtils.h"
#include <cstddef>
#include <iostream>

namespace Metrics
{
    inline unsigned long long iterationCount = 0;
    inline size_t memoryUsage = 0;

    inline void reset()
    {
        iterationCount = 0;
        memoryUsage = 0;
    }

    inline void addIteration(unsigned long long count = 1)
    {
        iterationCount += count;
    }

    inline void addMemory(size_t bytes)
    {
        memoryUsage += bytes;
    }

    inline void removeMemory(size_t bytes)
    {
        memoryUsage -= bytes;
    }

    inline void report()
    {
        printTitle(">>> MÉTRICAS DEL SISTEMA <<<", '=');
        printInfo("Iteraciones totales: ", iterationCount);
        printInfo("Memoria consumida (bytes): ", memoryUsage);
    }
}

#endif
