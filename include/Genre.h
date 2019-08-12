#ifndef _GENRE_H_
#define _GENRE_H_

#define GENRE_BUFFER_SIZE 512

#define GENRENAME_HEADER "GenreName="
#define GENRECOLOR_HEADER "GenreColor=#"
#define FONTCOLOR_HEADER "FontColor=#"

typedef struct RGBColor {
    char r;
    char g;
    char b;
} RGBColor;

typedef struct Genre {
    char *name;
    RGBColor  genreColor;
    RGBColor  fontColor; 
} Genre;

Genre *newGenre(char *name, RGBColor genreColor, RGBColor fontColor);
Genre *createGenreStructFromFile(const char *path);
char* getLine(const char *bufferPosition);
RGBColor fromString(const char *string);
void freeGenre(Genre *genre);

#endif