#ifndef _GENRE_LINKED_LIST_H_
#define _GENRE_LINKED_LIST_H_

#include "Genre.h"

//Forward Declaration
typedef struct GenreLinkedList GenreLinkedList;

struct GenreLinkedList {
    GenreLinkedList *next;
    Genre *data;
};

typedef struct GenreLinkedList GenreNode;

GenreNode *new_GenreLinkedList(Genre *data);
void appendGenreNodeToTail(Genre *data);
void removeGenreNode(GenreNode *nodeToRemove);
void removeGenreNodeFromHead();
GenreNode *getPreviousGenreNode(GenreNode *node);
GenreNode *getGenreLinkedListHead();
GenreNode *getGenreLinkedListTail();
int getGenreLinkedListLength();
void freeGenreNode(GenreNode *currentNode);
void freeGenreLinkedList();

#endif //_CHART_LINKED_LIST_H_