#ifndef _CHART_LINKED_LIST_H_
#define _CHART_LINKED_LIST_H_

#include "ChartFile.h"

typedef struct ChartLinkedList ChartLinkedList;

struct ChartLinkedList {
    ChartFile *data;
    ChartLinkedList *next;
};

typedef struct ChartLinkedList ChartNode;

ChartNode *new_ChartNode(ChartFile *data);
void appendChartNodeToTail(ChartFile *data);
void removeChartNode(ChartNode *nodeToRemove);
void removeChartNodeFromHead();
ChartNode *getChartLinkedListHead();
ChartNode *getChartLinkedListTail();
ChartNode *getPreviousChartNode(ChartNode *node);
int getChartLinkedListLength();
void freeChartNode(ChartNode *node);
void freeChartLinkedList();

#endif //_CHART_LINKED_LIST_H_