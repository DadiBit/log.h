#include "log.h"

int main () {

    log("error", "%s", "abc");
    debug("%s", "abc");

    return 0;
}