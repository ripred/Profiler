/*
 * Profiler.h
 * 
 * header file for the Arduino Profiler library
 * 
 * version 1.0 - August 2023 ++trent m. wyatt
 * 
 */
#ifndef   PROFILER_H_INCL
#define   PROFILER_H_INCL

#include <Arduino.h>
#include <Stream.h>

struct profiler_t {
    Stream *stream;
    unsigned long start;
    static bool enabled;

    profiler_t(Stream &s = Serial);
    ~profiler_t();

    static void enable();
    static void disable();
};

#endif // PROFILER_H_INCL
