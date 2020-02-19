# Logc
A simple and small plug in and play logging library in C.
Modified version of [rxi/log.c](https://github.com/rxi/log.c)

## Getting Started
Copy log.c and log.h into your project and have fun.

## Usage
The following [example](example.c) shows how to use log.h:
```c

#define LOGC_LEADING_TEXT "[CustomTextInThisFile] "
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
    log_set_log_file(logfile);

    log_info("also in file");

    log_set_quiet(true);

    log_info("only in file");

    log_set_min_level(LOG_WARN);

    log_info("this log will be discarded");

    fclose(logfile);
}
```

## Author

* **René Horstmann**
* **[rxi](https://github.com/rxi)**

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details
