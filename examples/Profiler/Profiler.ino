/*
 * Profiler.ino
 * 
 * Example Arduino sketch for the Arduino Profiler library
 * 
 * version 1.0 - August 2023 ++trent m. wyatt
 * 
 */

#include <Profiler.h>

// Example function that will be profiled
// 
void foo() {
    profiler_t profiler;

    delay(1000);
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
        profiler_t profiler;
        
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
}

void loop() {

}
