#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <psp2/io/fcntl.h>
#include <psp2/rtc.h>

#include "../include/Logger.h"

// ================
// Static Variables
// ================
static Logger logger = -1;

/**
 * Initialize the Logger by accessing the file at DEFAULT_LOG_PATH/tjapvita-dd-mm-yyyy.log.
 * If the operation fails, we exit for now.
 */
void initializeLogger() {
    /* Open file at ux0:/data/tjapvita/log/tjapvita-day-month-year.log for writing */
    /* Note: This magic number (48) works well with the default path. If you change the path,
     * change the number, or face the consequences! */
    static char filePath[48];
    SceDateTime time;
    sceRtcGetCurrentClockLocalTime(&time);
    snprintf(filePath, sizeof(filePath), "%s/tjapvita_%02d-%02d-%04d.log", DEFAULT_LOG_PATH, sceRtcGetDay(&time), sceRtcGetMonth(&time),
             sceRtcGetYear(&time));
    logger = sceIoOpen(filePath, SCE_O_WRONLY | SCE_O_CREAT | SCE_O_APPEND, 0777);
    if (logger < 0) exit(EXIT_FAILURE);
}

/**
 * Writes the parameter message to the log file if the logger has been initialized.
 * @param message The message to write to the log.
 */
void writeToLogger(const char *message) {
    if (logger > 0) {
        writeTimestamp();
        sceIoWrite(logger, message, strlen(message));
        sceIoWrite(logger, "\n", 1);
    }
}

void writeIntToLogger(int value) {
    if (logger > 0) {
        writeTimestamp();
        static char buf[24];
        snprintf(buf, sizeof(buf), "%d", value);
        sceIoWrite(logger, buf, strlen(buf));
        sceIoWrite(logger, "\n", 1);
    }
}

/**
 * Writes the current timestamp to the logger.
 */
void writeTimestamp() {
    static char timestamp[12];
    SceDateTime time;
    sceRtcGetCurrentClockLocalTime(&time);
    snprintf(timestamp, sizeof(timestamp), "[%02d:%02d:%02d]:", sceRtcGetHour(&time), sceRtcGetMinute(&time), sceRtcGetSecond(&time));
    sceIoWrite(logger, timestamp, strlen(timestamp));
}

/**
 * Writes the address of a pointer to the logger. Useful for debugging purposes.
 * @param ptr The pointer whose address will be written to the logger.
 */
void writePointerToLogger(void *ptr) {
    if (logger > 0) {
        writeTimestamp();
        char ptrMessage[128];
        snprintf(ptrMessage, sizeof(ptrMessage), "Logged Pointer Address: %p\n", ptr);
        sceIoWrite(logger, ptrMessage, strlen(ptrMessage));
    }
}

/**
 * Closes the log. Once this has been done, it will be impossible to write
 * to the log unless initializeLogger is called again.
 */
void exitLogger() {
    sceIoClose(logger);
    logger = -1;
}