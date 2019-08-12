#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "../include/Genre.h"
#include "../include/SjisToUtf8.h"

Genre *newGenre(char *name, RGBColor genreColor, RGBColor fontColor) {
    Genre *genre = malloc(sizeof(Genre));
    if (genre) {
        memset(genre, 0, sizeof(Genre));
        genre->name = name;
        genre->genreColor = genreColor;
        genre->fontColor = fontColor;
    }
    return genre;
}

Genre *createGenreStructFromFile(const char *path) {
    FILE *file = fopen(path, "r");
    RGBColor fontColor, genreColor;
    char *name = NULL;
    char filebuffer[GENRE_BUFFER_SIZE];
    if (file) {
        memset(filebuffer, 0, GENRE_BUFFER_SIZE - 1);
        fread(filebuffer, sizeof(char), GENRE_BUFFER_SIZE - 1, file);
        char *genreNamePos = strstr(filebuffer, GENRENAME_HEADER);
        char *genreColorPos = strstr(filebuffer, GENRECOLOR_HEADER);
        char *fontColorPos = strstr(filebuffer, FONTCOLOR_HEADER);
        if (genreNamePos) {
            name = getLine(genreNamePos+strlen(GENRENAME_HEADER));
        }
        if (genreColorPos) {
            char genreColorHex[7];
            strncpy(genreColorHex, genreColorPos+strlen(GENRECOLOR_HEADER), 6);
            genreColorHex[6] = '\0';
            genreColor = fromString(genreColorHex);
        } 
        if (fontColorPos) {
            char fontColorHex[7];
            strncpy(fontColorHex, fontColorPos+strlen(FONTCOLOR_HEADER), 6);
            fontColorHex[6] = '\0';
            fontColor = fromString(fontColorHex);
        }
        fclose(file);
    }
    return newGenre(name, genreColor, fontColor);
}

char* getLine(const char *bufferPosition) {
    size_t stringSizeLineFeed = strcspn(bufferPosition, "\n");
    size_t stringSizeCarriageReturn = strcspn(bufferPosition, "\r");
    size_t stringSize = stringSizeCarriageReturn < stringSizeLineFeed ? stringSizeCarriageReturn : stringSizeLineFeed;
    char *string = malloc(stringSize + 1);
    char *result = NULL;
    if (string) {
        strncpy(string, bufferPosition, stringSize);
        string[stringSize] = '\0';
        result = shiftJisToUtf8(string);
        free(string);
    }
    return result;
}

RGBColor fromString(const char *string) {
    RGBColor color = { .r = 0, .g = 0, .b = 0 };
    if (string && strlen(string) == 6) {
        char red[3] = { string[0], string[1], '\0'};
        char green[3] = { string[2], string[3], '\0'};
        char blue[3] = { string[4], string[5], '\0'};
        color.r = (int)strtol(red, NULL, 16);
        color.g = (int)strtol(green, NULL, 16);
        color.b = (int)strtol(blue, NULL, 16);
    }
    return color;
}

void freeGenre(Genre *genre) {
    if (genre) {
        if (genre->name) free(genre->name);
        memset(genre, 0, sizeof(Genre));
        free(genre);
        genre = NULL;
    }
}