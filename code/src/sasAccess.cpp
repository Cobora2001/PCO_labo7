#include <sasAccess.h>
#include <iostream>
#include <pcosynchro/pcothread.h>
#include <pcosynchro/pcomutex.h>
#include <pcosynchro/pcosemaphore.h>

sasAccess::sasAccess(unsigned int N) : isFirstAttempt(true), isItOne(false), SIZE(N), 
                                 nbOfOnesIn(0), nbOfZerosIn(0), nbOfOneWaiting(0), nbOfZerosWaiting(0),
                                 mutex (), numberOfZerosWaiting(1), numberOfOnesWaiting(1){ }


void sasAccess::access(int id){
    mutex.lock();
    if(isFirstAttempt){
        setFirstAttempt(id);
    }

    if(id == 1){
        ++nbOfOneWaiting;
        while(!canEnterOne()){
            mutex.unlock();
            numberOfOnesWaiting.acquire();
            mutex.lock();
        }
        --nbOfOneWaiting;
        ++nbOfOnesIn;
    } else {
        ++nbOfZerosWaiting;
        while(!canEnterZero()){
            mutex.unlock();
            numberOfZerosWaiting.acquire();
            mutex.lock();
        }
        --nbOfZerosWaiting;
        ++nbOfZerosIn;
    }
    mutex.unlock();
}

void sasAccess::leave(int id){
    mutex.lock();
    if(id == 1){
        if(canLeaveOne()){
            --nbOfOnesIn;
            if(nbOfOnesIn == 0 && nbOfOneWaiting == 0){
                isItOne = false;
                while(nbOfZerosWaiting > 0){
                    --nbOfZerosWaiting;
                    numberOfZerosWaiting.release();
                }
            } else {
                numberOfOnesWaiting.release();
            }
        }else{
            mutex.unlock();
            return;
        }
    } else {
        if(canLeaveZero()){
            --nbOfZerosIn;
            if(nbOfZerosIn == 0 && nbOfZerosWaiting == 0){
                isItOne = true;
                while(nbOfOneWaiting > 0){
                    --nbOfOneWaiting;
                    numberOfOnesWaiting.release();
                }
            } else {
                numberOfZerosWaiting.release();
            }
        }else{
            mutex.unlock();
            return;
        }
    }
}
