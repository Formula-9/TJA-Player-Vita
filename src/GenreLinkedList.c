#include "../include/GenreLinkedList.h"

#include <stdlib.h>
#include <string.h>

#include "../include/Genre.h"

static GenreNode *head = NULL;
static GenreNode *tail = NULL;

GenreNode *new_GenreNode(Genre *data) {
    GenreNode *node = NULL;
    if (data) {
        node = malloc(sizeof(GenreNode));
        node->next = NULL;
        node->data = data;
    }
    return node;
}

void appendGenreNodeToTail(Genre *data) {
    GenreNode *nextNode = new_GenreNode(data);
    if (nextNode) {
        if (tail) {
            tail->next = nextNode;
        } else {
            head = nextNode;
        }
        tail = nextNode;
    }
}

void removeGenreNode(GenreNode *nodeToRemove) {
    if (nodeToRemove) {
        GenreNode *prev = getPreviousGenreNode(nodeToRemove);
        if (nodeToRemove->next) prev->next = nodeToRemove->next;
        freeGenreNode(nodeToRemove);
    }
}

GenreNode *getPreviousGenreNode(GenreNode *node) {
    GenreNode *prev = NULL;
    if (node) {
        GenreNode *curr = head;
        while (curr != node) {
            prev = curr;
            curr = curr->next;
        }
    }
    return prev;
}

void removeGenreNodeFromHead() {
    if (head) {
        GenreNode *nodeToRemove = head;
        if (head->next) { head = head->next; }
        else { head = tail = NULL; }
        freeGenreNode(nodeToRemove);
    }
}

GenreNode *getGenreLinkedListHead() {
    return head;
}

GenreNode *getGenreLinkedListTail() {
    return tail;
}

int getGenreLinkedListLength() {
    int length = 0;
    GenreNode *currentNode = head;
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

void freeGenreNode(GenreNode *node) {
    if (node) {
        freeGenre(node->data);
        memset(node, 0, sizeof(GenreNode));
        free(node);
        node = NULL;
    }  
}

void freeGenreLinkedList() {
    while (head) { removeGenreNodeFromHead(); }
}