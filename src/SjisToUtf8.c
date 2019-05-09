#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>

#include "../include/Logger.h"
#include "../include/SjisTable.h"
#include "../include/SjisToUtf8.h"

/**
 * This function takes a Shift-JIS encoded string and returns its UTF-8 representation.
 * @param shiftJisString A pointer to the Shift-JIS encoded string.
 * @return A pointer to an UTF-8 encoded string that have been malloc'd.
 */
char *shiftJisToUtf8(char *shiftJisString) {
    size_t shiftJisStringLength = strlen(shiftJisString);
    size_t indexInput = 0, indexOutput = 0;
    size_t arrayOffset;
    uint16_t unicodeValue;
    char arraySection;

    char *output = NULL;
    char *tmp = malloc(3 * shiftJisStringLength * sizeof(char));
    if (tmp) {
        while (indexInput < shiftJisStringLength) {
            arraySection = ((uint8_t) shiftJisString[indexInput]) >> 4;

            if (arraySection == 0x8) arrayOffset = 0x100; //these are two-byte shiftjis
            else if (arraySection == 0x9) arrayOffset = 0x1100;
            else if (arraySection == 0xE) arrayOffset = 0x2100;
            else arrayOffset = 0; //this is one byte shiftjis

            //determining real array offset
            if (arrayOffset) {
                arrayOffset += (((uint8_t) shiftJisString[indexInput]) & 0xf) << 8;
                indexInput++;
                if (indexInput >= shiftJisStringLength) break;
            }
            arrayOffset += (uint8_t) shiftJisString[indexInput++];
            arrayOffset <<= 1;

            //unicode number is...
            unicodeValue = (sjisTable[arrayOffset] << 8) | sjisTable[arrayOffset + 1];

            //converting to UTF8
            if (unicodeValue < 0x80) {
                tmp[indexOutput++] = unicodeValue;
            } else if (unicodeValue < 0x800) {
                tmp[indexOutput++] = 0xC0 | (unicodeValue >> 6);
                tmp[indexOutput++] = 0x80 | (unicodeValue & 0x3f);
            } else {
                tmp[indexOutput++] = 0xE0 | (unicodeValue >> 12);
                tmp[indexOutput++] = 0x80 | ((unicodeValue & 0xfff) >> 6);
                tmp[indexOutput++] = 0x80 | (unicodeValue & 0x3f);
            }
        }

        //Try to shrink the size of the string to free up unnecessary bytes.
        output = calloc(strlen(tmp), sizeof(char));
        if (output) {
            strcpy(output, tmp);
            free(tmp);
        } else {
            writeToLogger("Couldn't allocate memory for final string, returning temporary string!");
            output = tmp;
        }
    } else { writeToLogger("Couldn't allocate memory for temporary string!"); }
    return output;
}