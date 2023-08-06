/*
 * Profiler.cpp
 * 
 * implementation file for the Arduino Profiler library
 * 
 * version 1.0 - August 2023 ++trent m. wyatt
 * 
 */

#include "Profiler.h"

// static class-wide variable to control whether the output is enabled
// 
bool profiler_t::enabled = true;

// class constructor
// 
profiler_t::profiler_t(Stream &s) {
    stream = &s;enabled = true;
    start = millis();
}

// class destructor
// 
profiler_t::~profiler_t() {
    if (enabled) {
        unsigned long now = millis();
        (*stream).print(F("Time spent: "));
        (*stream).println(now - start);
    }
}

// method to enable the output
// 
void profiler_t::enable() {
    enabled = true;
}

// method to disable the output
// 
void profiler_t::disable() {
    enabled = false;
}
