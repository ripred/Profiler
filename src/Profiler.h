/*
 * Profiler.h
 * 
 * header file for the Arduino Profiler library
 * 
 * version 1.0 - August 2023 ++trent m. wyatt
 * version 1.1 - October 2023
 *    added optional debug pin support
 * 
 */
#ifndef   PROFILER_H_INCL
#define   PROFILER_H_INCL

#include <Arduino.h>
#include <Stream.h>

struct profiler_t {
    static uint8_t  enabled;
    Stream         *stream;
    unsigned long   start;
    int8_t          pin;

    profiler_t(Stream &s = Serial);
    profiler_t(int pin, Stream &s = Serial);
    ~profiler_t();

    static void enable();
    static void disable();
};

#endif // PROFILER_H_INCL
