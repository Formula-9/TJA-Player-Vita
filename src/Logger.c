#include "Logger.h"

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
    char filePath[48];
    SceDateTime time;
    sceRtcGetCurrentClockLocalTime(&time);
    snprintf(filePath, 48, "%s/tjapvita_%02d-%02d-%04d.log", DEFAULT_LOG_PATH, sceRtcGetDay(&time), sceRtcGetMonth(&time),
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
        /* Get a timestamp for the message */
        char timestamp[12];
        SceDateTime time;
        sceRtcGetCurrentClockLocalTime(&time);
        snprintf(timestamp, 12, "[%02d:%02d:%02d]:", sceRtcGetHour(&time), sceRtcGetMinute(&time), sceRtcGetSecond(&time));
        /* And write it into the file */
        sceIoWrite(logger, timestamp, 12);
        sceIoWrite(logger, message, strlen(message));
        sceIoWrite(logger, "\n", 1);
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