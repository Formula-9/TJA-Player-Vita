#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>

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

    char *output = NULL;
    char *tmp = calloc(1, 3 * shiftJisStringLength + 1);
    if (tmp != NULL) {
        while (indexInput < shiftJisStringLength) {
            char arraySection = ((uint8_t) shiftJisString[indexInput]) >> 4;

            size_t arrayOffset;
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
            uint16_t unicodeValue = (sjisTable[arrayOffset] << 8) | sjisTable[arrayOffset + 1];

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
		tmp[indexOutput] = '\0';
		
		//Try to shrink the size of the string to free up unnecessary bytes.
		output = strdup(tmp);
		free(tmp);
    }

    return output;
}