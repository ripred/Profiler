/*
 * Profiler.h
 * 
 * header file for the Arduino Profiler library
 * 
 * version 1.0 - August 2023 ++trent m. wyatt
 * version 1.1 - October 2023
 *    added optional debug pin support
 * version 1.6 - August 2024
 *    added text support
 * 
 */
#ifndef   PROFILER_H_INCL
#define   PROFILER_H_INCL

#include <Arduino.h>
#include <String.h>
#include <Stream.h>

struct profiler_t {
    static uint8_t  enabled;
    Stream         *stream;
    String          text;
    unsigned long   start;
    unsigned long   total;
    int8_t          pin;

    profiler_t(Stream &s = Serial);
    profiler_t(int pin, Stream &s = Serial);
    profiler_t(char const * const msg, Stream &s = Serial);
    profiler_t(int pin, char const * const msg, Stream &s = Serial);
    ~profiler_t();

    static void enable();
    static void disable();
};

#endif // PROFILER_H_INCL
