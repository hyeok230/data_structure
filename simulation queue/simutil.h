#ifndef _SIM_UTIL_
#define _SIM_UTIL_

#include "simdef.h"
#include "linkeddeque.h"

void insertCustomer(int arrivalTime, int processTime, char id, LinkedDeque *pArrivalDeque);
void processArrival(int currentTime, LinkedDeque *pArrivalDeque, LinkedDeque *pWaitDeque);
DequeNode* processServiceNodeStart(int currentTime, LinkedDeque *pWaitDeque);
DequeNode* processServiceNodeEnd(int currentTime, DequeNode *pServiceNode, int *pServiceUserCount, int *pTotalWaitTime);
void printSimCustomer(int currentTime, SimCustomer customer);
void printWaitQueueStatus(int currentTime, LinkedDeque *pWaitDeque);
void printReport(LinkedDeque *pWaitDeque, int serviceUserCount, int totalWaitTime);

#endif