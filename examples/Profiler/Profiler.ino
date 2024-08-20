/*
 * Profiler.ino
 *
 * Example Arduino sketch for the Arduino Profiler library
 *
 * version 1.0 -  August 2023 ++trent m. wyatt
 * version 1.1 - October 2023
 *    added optional debug pin support
 * version 1.5 - August 2024
 *    added optional custom text support
 *
 */

#include <Profiler.h>

#define   DEBUG_LED   13

// Example function that will be profiled including debug pin output:
//
void foo() {
    profiler_t profiler(DEBUG_LED);

    delay(1000);
}

// Example function that will be profiled without debug pin output, but including the function name:
//
void baz() {
    profiler_t profiler(
        (String("Time spent in ") + 
        String(__FUNCTION__) + 
        String("()")).c_str());

    delay(2000);
}

// Example function where only part of the code
// will be profiled using a temporary scope
//
void bar() {
    // this code will not be profiled.
    // yes the code is pointless heh
    for (int i=0; i < 10; i++) {
        delay(100);
    }

    // create a temporary scope just to contain the instantiation of a profiler_t
    // object in order to time a smaller section of code inside a larger section
    {
        profiler_t profiler("Partial Scoped Profile");

        delay(500);
    }

    // more pointless code that will not be profiled
    for (int i=0; i < 10; i++) {
        delay(100);
    }
}

void setup() {
    Serial.begin(115200);
    while (!Serial);

    foo();

    bar();

    baz();
}

void loop() {

}
