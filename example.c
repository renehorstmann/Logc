#include "log.h"

int main() {

    // log modes:
    log_trace("trace msg");
    log_debug("debug msg");
    log_info("info msg");
    log_warn("warn msg");
    log_error("error msg");
    log_wtf("wtf msg");

    // turn on leading text
    log_set_leading_text("[LOG_LIB]");
    log_info("log msg with leading text");

    // turn off leading text
    log_set_leading_text(NULL);

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

