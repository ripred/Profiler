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

#define ONE_SECOND 1000
#define ONE_MINUTE 60
#define ONE_HOUR 60
#define ONE_DAY 24

// static class-wide variables to control whether the output is enabled and prints in milliseconds
// 
uint8_t profiler_t::enabled = true;
uint8_t profiler_t::milliseconds = false;

// PROFILER_T
// class constructor
// 
profiler_t::profiler_t(Stream &s) {
    stream = &s;
    enabled = true;
    milliseconds = false;
    pin = -1;
    start = millis();
}


profiler_t::profiler_t(int Pin, Stream &s /* = Serial */) {
    stream = &s;
    enabled = true;
    milliseconds = false;
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
    milliseconds = false;
    start = millis();
    if (nullptr != msg) {
        text = msg;
        text.concat(": ");
    }
}

profiler_t::profiler_t(int Pin, char const * const msg, Stream &s /* = Serial */) {
    stream = &s;
    enabled = true;
    milliseconds = false;
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

        if (!milliseconds)
            ReadableTime(total, stream);
        else
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

// method to enable time printing in human readable time format
//
void profiler_t::inReadableTime() {
    milliseconds = false;
}

// method to enable time printing in milliseconds only
//
void profiler_t::inMilliseconds() {
    milliseconds = true;
}

// READABLETIME
// class constructor
//
ReadableTime::ReadableTime(unsigned long total_time, Stream *s) {
    day = 0;
    hour = 0;
    minute = 0;
    second = 0;
    stream = s;
    
    // max total_time value is 4,294,967,295 (4 bytes), translates to "49d 17h 2m 47s 295ms"
    // https://docs.arduino.cc/language-reference/en/variables/data-types/unsignedLong/
    millisecond = (uint16_t) (total_time % ONE_SECOND);
    total_time = total_time / ONE_SECOND;
    
    if (total_time == 0) {
        goto nomoretime;
    }
    second = (uint8_t) (total_time % ONE_MINUTE);
    total_time = total_time / ONE_MINUTE;

    if (total_time == 0) {
        goto nomoretime;
    }
    minute = (uint8_t) (total_time % ONE_HOUR);
    total_time = total_time / ONE_HOUR;

    if (total_time == 0) {
        goto nomoretime;
    }
    hour = (uint8_t) (total_time % ONE_DAY);
    day = (uint8_t) (total_time / ONE_DAY);
nomoretime:;
}

// class destructor
//
ReadableTime::~ReadableTime() {
    if (day > 0)
        goto day;
    if (hour > 0)
        goto hr;
    if (minute > 0)
        goto min;
    if (second > 0)
        goto sec;
    goto ms;

day:
    (*stream).print(day);
    (*stream).print("d ");
hr:
    (*stream).print(hour);
    (*stream).print("h ");
min:
    (*stream).print(minute);
    (*stream).print("m ");
sec:
    (*stream).print(second);
    (*stream).print("s ");
ms:
    (*stream).print(millisecond);
    (*stream).println("ms");
}