#ifndef TJA_PLAYER_VITA_LOGGER_H
#define TJA_PLAYER_VITA_LOGGER_H

void initializeLogger();
void writeTimestamp();
void writeToLogger(const char *message);
void writeIntToLogger(int value);
void writePointerToLogger(void *ptr);
void exitLogger();

#endif //TJA_PLAYER_VITA_LOGGER_H
