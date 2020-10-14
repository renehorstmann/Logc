# Logc
A simple and small plug in and play logging library in C.
Modified version of [rxi/log.c](https://github.com/rxi/log.c)

## Getting Started
### Option 1
Copy log.h into your project and choose exactly 1 source file, in which 
LOGC_SOURCE should be defined before including log.h (see the example below).
### Option 2
Copy log.h and log.c into your project and add log.c to your source files.


## Usage
The following [example](example.c) shows how to use log.h:
```c
#define LOGC_LEADING_TEXT "[CustomTextInThisFile] "
#define LOGC_SOURCE // only 1 source file should set this! (or add log.c to your source files)
#include "log.h"

int main() {

    // log modes:
    log_trace("trace msg");
    log_debug("debug msg");
    log_info("info msg");
    log_warn("warn msg");
    log_error("error msg");
    log_wtf("wtf msg");

    // if the macro LOGC_LEADING_TEXT is set, a custom string is placed before each log
    //      see above
    //      or the comment in CMakeLists.txt: add_definitions(-DLOGC_LEADING_TEXT="[CustomText] ")

    // all log macros are in printf style:
    log_debug("value: %d", 34);

    // also print fo file:
    FILE *logfile = fopen("log.txt", "a");
    logc_set_log_file(logfile);

    log_info("also in file");

    logc_set_quiet(true);

    log_info("only in file");

    logc_set_min_level(LOG_WARN);

    log_info("this log will be discarded");

    fclose(logfile);
}

```
Its also possible to change the namespace logc_ with LOGC_NAMESPACE

## Python bindings:
If you use Logc in a C Library, that will be exposed to python, a binding to logc is in log.py.
Just change some lines at the top and have fun.

## Author

* **René Horstmann**
* **[rxi](https://github.com/rxi)**

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details
