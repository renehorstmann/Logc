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
    logc_set_log_file(logfile);

    log_info("also in file");

    logc_set_quiet(true);

    log_info("only in file");

    logc_set_min_level(LOG_WARN);

    log_info("this log will be discarded");

    fclose(logfile);
}
