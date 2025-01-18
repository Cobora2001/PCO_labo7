#ifndef SASACCESS_H
#define SASSACCESS_H

#include <pcosynchro/pcothread.h>
#include <pcosynchro/pcomutex.h>
#include <pcosynchro/pcosemaphore.h>

class sasAccess{
public:
    sasAccess(unsigned int size) {};
    void access(int id);
    void leave(int id);
private:
    PcoMutex mutex;
    PcoSemaphore numberOfZerosWaiting;
    PcoSemaphore numberOfOnesWaiting;

    unsigned int SIZE;
    unsigned int nbOfOnesIn;
    unsigned int nbOfZerosIn;
    unsigned int nbOfOneWaiting;
    unsigned int nbOfZerosWaiting;

    bool isFirstAttempt, isItOne;

    void setFirstAttempt(int id){
        isItOne = id == 1;
        isFirstAttempt = false;
    }
  
    bool canEnterOne() {
        return (nbOfZerosIn == 0 && nbOfOnesIn <  SIZE ) && isItOne;
    }

    bool canEnterZero() {
        return (nbOfOnesIn == 0 && nbOfZerosIn < SIZE)  && !isItOne;
    }

    bool canLeaveOne() {
        return nbOfOnesIn > 0 && isItOne;
    }

    bool canLeaveZero() {
        return nbOfZerosIn > 0 && !isItOne;
    }

};

#endif // SASACCESS_H