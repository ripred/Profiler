/*
 * Profiler.cpp
 * 
 * implementation file for the Arduino Profiler library
 * 
 * version 1.0 - August 2023 ++trent m. wyatt
 * version 1.1 - October 2023
 *    added optional debug pin support
 * version 1.6 - August 2024
 *    added text support
 * 
 */

#include "Profiler.h"

// static class-wide variable to control whether the output is enabled
// 
uint8_t profiler_t::enabled = true;

// class constructor
// 
profiler_t::profiler_t(Stream &s) {
    stream = &s;
    enabled = true;
    pin = -1;
    start = millis();
}


profiler_t::profiler_t(int Pin, Stream &s /* = Serial */) {
    stream = &s;
    enabled = true;
    start = millis();
    pin = Pin;
    if (pin >= 0) {
        pinMode(pin, OUTPUT);
        digitalWrite(pin, HIGH);
    }
}


profiler_t::profiler_t(char const * const msg, Stream &s /* = Serial */) {
    stream = &s;
    enabled = true;
    start = millis();
    pin = -1;
    if (nullptr != msg) {
        text = msg;
        text.concat(": ");
    }
}

profiler_t::profiler_t(int Pin, char const * const msg, Stream &s /* = Serial */) {
    stream = &s;
    enabled = true;
    start = millis();
    pin = Pin;
    if (nullptr != msg) {
        text = msg;
        text.concat(": ");
    }
    if (pin >= 0) {
        pinMode(pin, OUTPUT);
        digitalWrite(pin, HIGH);
    }
}

// class destructor
// 
profiler_t::~profiler_t() {
    if (pin >= 0) {
        digitalWrite(pin, LOW);
    }

    if (enabled) {
        unsigned long now = millis();
        total = now - start;
        if (text.length() == 0) {
            text = "Time Spent: ";
        }
        (*stream).print(text);
        (*stream).println(total);
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
