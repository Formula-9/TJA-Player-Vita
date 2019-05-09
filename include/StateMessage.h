#ifndef TJA_PLAYER_VITA_STATEMESSAGE_H
#define TJA_PLAYER_VITA_STATEMESSAGE_H

/**
 * This structure might be a bit confusing, but it exists to
 * pass various structures or data from one state to another.
 * @var messageData:     Array of pointers to the data to pass around.
 * @var messageSize:     Array of int to the sizes of the data.
 * @var structType:      Array of strings to the types of data that are passed.
 * @var numberOfObjects: Int indicating the number of items stored in this StateMessage.
 */
typedef struct StateMessage {
    void **messageData;
    int   *messageSize;
    char **structType;
    int    numberOfObjects;
} StateMessage;

void cleanupStateMessage(StateMessage *stateMessage);

#endif //TJA_PLAYER_VITA_STATEMESSAGE_H
