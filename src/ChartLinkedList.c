#include "../include/ChartLinkedList.h"

#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "../include/Genre.h"

static ChartNode *head = NULL;
static ChartNode *tail = NULL;

/**
 * Creates a new node and return it.
 * @param data The data the new node must point to.
 * @return A pointer to the newly created node. Returns NULL if data is NULL.
 */
ChartNode *new_ChartNode(ChartFile *data) {
    ChartNode *node = NULL;
    if (data) {
        node = malloc(sizeof(ChartNode));
        node->next = NULL;
        node->data = data;
    }
    return node;
}

void appendChartNodeToTail(ChartFile *data) {
    ChartNode *nextNode = new_ChartNode(data);
    if (nextNode) {
        if (tail) {
            tail->next = nextNode;
        } else {
            head = nextNode;
        }
        tail = nextNode;
    }
}

void removeChartNode(ChartNode *nodeToRemove) {
    if (nodeToRemove) {
        ChartNode *prev = getPreviousChartNode(nodeToRemove);
        if (nodeToRemove->next) prev->next = nodeToRemove->next;
        freeChartNode(nodeToRemove);
    }
}

void removeChartNodeFromHead() {
    if (head) {
        ChartNode *nodeToRemove = head;
        if (head->next) { head = head->next; }
        else { head = tail = NULL; }
        freeChartNode(nodeToRemove);
    }
}

ChartNode *getChartLinkedListHead() {
    return head;
}

ChartNode *getChartLinkedListTail() {
    return tail;
}

ChartNode *getPreviousChartNode(ChartNode *node) {
    ChartNode *prev = NULL;
    if (node) {
        ChartNode *curr = head;
        while (curr != node) {
            prev = curr;
            curr = curr->next;
        }
    }
    return prev;
}

int getChartLinkedListLength() {
    int length = 0;
    ChartNode *currentNode = head;
    if (!currentNode) { 
        length = 0;
    } else {
        while (currentNode) {
            currentNode = currentNode->next;
            length++;
        }
    }
    return length;
}

void freeChartNode(ChartNode *node) {
    if (node) {
        freeChartFile(node->data);
        memset(node, 0, sizeof(ChartNode));
        free(node);
        node = NULL;
    }  
}

void freeChartLinkedList() {
    while (head) { removeChartNodeFromHead(); }
}