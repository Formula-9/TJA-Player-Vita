#include "../include/Log.h"

#include <stdio.h>
#include <string.h>

static FILE *log = NULL;

/**
 * Tries to open the log file for writing.
 */
void openLogFile() {
    log = fopen("ux0:/data/tjapvita/log.txt", "w");
}

/**
 * Write a simple string to the file.
 */
void writeStringToFile(const char *str) {
    if (log && str) {
        printfToFile(str);
    }
}

/**
 * Write a message to the file, using fprintf.
 */
void printfToFile(const char *fmt, ...) {
    if (log) {
        va_list va;
        va_start(va, fmt);
        fprintf(log, fmt, va);
        va_end(va);
        fflush(log);
    }
}

/**
 * Write to the file data about all found charts.
 */
void writeChartLinkedListToFile() {
    if (log) {
        ChartNode *chartList = getChartLinkedListHead();
        fprintf(log, "==== Found %d charts ====\n", getChartLinkedListLength(chartList));
        fprintf(log, "Format: Name / Subtitle [E/N/H/O/E]\n");
        while (chartList && chartList->data) {
            ChartFile *chart = chartList->data;
            fprintf(log, "%s / %s [%d/%d/%d/%d/%d]\n", chart->title, chart->subtitle, chart->diffEasy, chart->diffNormal,
                                                       chart->diffHard, chart->diffOni, chart->diffEdit);
            chartList = chartList->next;
        }
        fflush(log);
    }   
}

/**
 * Close the log file.
 */
void closeLogFile() {
    if (log) {
        fclose(log);
    }
}