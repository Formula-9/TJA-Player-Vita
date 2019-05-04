#include "../include/StateMessage.h"

/**
 * Cleans up all the memory used by the StateMessage. This function
 * will free all the objects contained inside, as well as the strings
 * indicating the types and the array of int that indicates the objects'
 * size. In the case this instance must be reused, the numberOfObjects
 * variable is also reset to zero.
 * @param stateMessage A pointer to the StateMessage to clean.
 */
void cleanupStateMessage(StateMessage *stateMessage) {
    for (int i = 0; i < stateMessage->numberOfObjects; i++) {
        free(stateMessage->messageData[i]);
        free(stateMessage->structType[i]);
    }
    free(stateMessage->messageData);
    free(stateMessage->structType);
    free(stateMessage->messageSize);
    stateMessage->numberOfObjects = 0;
}