#include <stdio.h>

static FILE* logFile = NULL;
static char* filename = "traceLog";

void traceLogger(char* user, char* operand) {
    if (!logFile) {
        logFile = fopen(filename, "w");
    }
    fprintf(logFile, "%s <- %s\n", user, operand);
    fflush(logFile);
}