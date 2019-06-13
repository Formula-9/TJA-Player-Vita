#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "../include/Constants.h"

// ================
// Static Variables
// ================
static FILE *logger = NULL;

/**
 * Initialize the Logger by accessing the file at DEFAULT_LOG_PATH/tjapvita-dd-mm-yyyy.log.
 * If the operation fails, we exit for now.
 */
void initializeLogger() {
    /* Open file at ux0:/data/tjapvita/log/tjapvita-day-month-year.log for writing */
    /* Note: This magic number (48) works well with the default path. If you change the path,
     * change the number, or face the consequences! */
    static char filePath[48];
    time_t t = time(NULL);
    struct tm time = *localtime(&t);
    snprintf(filePath, sizeof(filePath), "%s/tjapvita_%02d-%02d-%04d.log", DEFAULT_LOG_PATH, time.tm_mday, time.tm_mon + 1, time.tm_year + 1900);
    logger = fopen(filePath, "a");
    if (!logger) exit(EXIT_FAILURE);
}

/**
 * Writes the parameter message to the log file if the logger has been initialized.
 * @param message The message to write to the log.
 */
void writeToLogger(const char *message) {
    if (logger) {
        writeTimestamp();
        fwrite(message, 1, strlen(message), logger);
        fwrite("\n", 1, 1, logger);
    }
}

void writeIntToLogger(int value) {
    if (logger) {
        writeTimestamp();
        static char buf[24];
        snprintf(buf, sizeof(buf), "%d", value);
        fwrite(buf, 1, strlen(buf), logger);
        fwrite("\n", 1, 1, logger);
    }
}

/**
 * Writes the current timestamp to the logger.
 */
void writeTimestamp() {
    static char timestamp[12];
    time_t t = time(NULL);
    struct tm time = *localtime(&t);
    snprintf(timestamp, sizeof(timestamp), "[%02d:%02d:%02d]:", time.tm_hour, time.tm_min, time.tm_sec);
    fwrite(timestamp, 1, strlen(timestamp), logger);
}

/**
 * Writes the address of a pointer to the logger. Useful for debugging purposes.
 * @param ptr The pointer whose address will be written to the logger.
 */
void writePointerToLogger(void *ptr) {
    if (logger) {
        writeTimestamp();
        char ptrMessage[128];
        snprintf(ptrMessage, sizeof(ptrMessage), "Logged Pointer Address: %p\n", ptr);
        fwrite(ptrMessage, 1, strlen(ptrMessage), logger);
    }
}

/**
 * Closes the log. Once this has been done, it will be impossible to write
 * to the log unless initializeLogger is called again.
 */
void exitLogger() {
    fclose(logger);
    logger = NULL;
}