# Profiler
Easily profile your Arduino functions to see how much time they take. The output can be disabled and enabled at runtime. Very lightweight.

```
/*
 * Profiler.ino
 * 
 * Example Arduino sketch for the Arduino Profiler library
 * 
 */
#include <Profiler.h>

// Example function that will be fully profiled
void foo() {
    profiler_t profiler;
    delay(1000);
}

// Example function where only part of the code
// will be profiled using a temporary scope
void bar() {
    // this code will not be profiled. yes the code is pointless heh
    for (int i=0; i < 10; i++) {
        delay(100);
    }

    // create a temporary scope just to contain the instantiation of a profiler_t
    // object in order to time a few lines of code inside a larger section:
    {
        profiler_t timing;
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

void loop() { }
```

output:

```
Time spent: 999
Time spent: 500
```
