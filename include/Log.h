#ifndef _LOG_H_
#define _LOG_H_

#include <stdarg.h>

#include "ChartLinkedList.h"

void openLogFile();
void writeStringToFile(const char *str);
void printfToFile(const char *fmt, ...);
void writeChartLinkedListToFile();
void closeLogFile();

#endif //_LOG_H_