#include "../include/Log.h"

#include <stdio.h>

static FILE *log = NULL;

void openLogFile() {
    log = fopen("ux0:/data/tjapvita/log.txt", "w");
}

void writeStringToFile(const char *str) {
    if (log && str) {
        fprintf(log, str);
    }
}

void printfToFile(const char *fmt, ...) {
    if (log) {
        va_list va;
        va_start(va, fmt);
        fprintf(log, fmt, va);
        va_end(va);
    }
}

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
    }   
}

void closeLogFile() {
    if (log) {
        fclose(log);
    }
}