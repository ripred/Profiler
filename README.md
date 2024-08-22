<!-- [![Arduino CI](https://github.com/ripred/Profiler/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci) -->
[![Arduino-lint](https://github.com/ripred/Profiler/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/ripred/Profiler/actions/workflows/arduino-lint.yml)
![code size:](https://img.shields.io/github/languages/code-size/ripred/Profiler)
[![GitHub release](https://img.shields.io/github/release/ripred/Profiler.svg?maxAge=3600)](https://github.com/ripred/Profiler/releases)
[![License: MIT](https://img.shields.io/badge/license-MIT-blue.svg)](https://github.com/ripred/Profiler/blob/master/LICENSE)


# Profiler
Easily profile your Arduino functions (or even just a few lines of code) to see how much time they take, simply by declaring a `profiler_t` variable anywhere in your code. The output can be disabled and enabled at any time. Very lightweight. 

The destination for the output over serial can be optionally specified and you can use any Arduino platform `Stream` subclass. This includes `Serial1` or `Serial2` on boards that have them, and even instances of `SoftwareSerial`, which is also `Stream` compatible. 😄 The default is the standard `Serial` device.

Several useful constructor types define the features that are used at runtime.

Updated: Now includes support for optional custom text 😎

```cpp
/*
 * Profiler.ino
 *
 * Example Arduino sketch for the Arduino Profiler library
 *
 * version 1.0 - August 2023 ++trent m. wyatt
 * version 1.1 - October 2023
 *    added optional debug pin support
 * version 1.6 - August 2024
 *    added optional custom output text support
 *
 * The available constructors are:
 *
 *    profiler_t(Stream &s = Serial);
 *    profiler_t(int pin, Stream &s = Serial);
 *    profiler_t(char const * const msg, Stream &s = Serial);
 *    profiler_t(int pin, char const * const msg, Stream &s = Serial);
 * 
 */

#include <Profiler.h>

#define   DEBUG_LED   13

// forward declarations (function prototypes):
void foo();
void bar();
void baz();

void setup() {
    Serial.begin(115200);
    while (!Serial);

    foo();
    bar();
    baz();
}

void loop() {

}


// Example function that will be profiled including debug pin output:
// (the debug output pin is HIGH for one second in this example usage)
void foo() {
    profiler_t profiler(DEBUG_LED);

    // ... some other code you want profiled
    delay(1000);
}

// Example function where only a smaller part of the code
// will be profiled using a temporary scope. Also makes use 
// of the new custom output text support:
//
void bar() {
    // this code will NOT be profiled.
    // yes the code is pointless heh
    for (int i=0; i < 10; i++) {
        delay(100);
    }

    // create a temporary scope just to contain the instantiation of a profiler_t
    // object in order to time a smaller section of code inside a larger section
    // and customize the output text:
    {
        profiler_t profiler("Partial Scoped Profile");
        
        // ... some other code you want profiled
        delay(500);
    }

    // more pointless code that will NOT be profiled
    for (int i=0; i < 10; i++) {
        delay(100);
    }
}

// Example function that will be profiled and use customized text output
// to automatically include the enclosing function name, so you can reuse 
// this same code in many functions and it will automatically output each
// function's correct name:
//
void baz() {
    profiler_t profiler(
        (String("Time spent in ") + 
        String(__FUNCTION__) + 
        String("()")).c_str());

    // ... some other code you want profiled
    delay(2000);
}
```

output:

```console
Time Spent: 999
Partial Scoped Profile: 500
Time spent in baz(): 1999
```
