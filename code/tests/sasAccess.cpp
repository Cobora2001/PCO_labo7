#include "sasAccess.h"
#include <iostream>
#include <algorithm> // Pour std::min
#include "modelsas.h"

SasAccess::SasAccess(unsigned int N, unsigned int accessSectionId, unsigned int leaveSectionId) 
    : idIn(0), SIZE(N), nbIn(0), nbOfOneWaiting(0), nbOfZerosWaiting(0),
      mutex(1), numberOfZerosWaiting(0), numberOfOnesWaiting(0), accessSectionId(accessSectionId), leaveSectionId(leaveSectionId){
    if(N <= 1) {
        std::cerr << "The size must be greater than 1" << std::endl;
        exit(1);
    }
}

// Unlock comments in the following functions to see the output

void SasAccess::access(int id, ThreadParent* overseer){
    mutex.acquire(); // Blocking
    //std::cout << "Thread " << overseer->getId() << " in access" << std::endl;
    overseer->startSect(accessSectionId);
    if(id == 1){
        if(canEnterOne()){
            // Allow entry
            idIn = true;
            nbIn++;
            mutex.release();
            //std::cout << "Thread " << overseer->getId() << " entered without waiting" << std::endl;
            overseer->endSect();
        }
        else{
            // Add to the 1 waiting queue
            nbOfOneWaiting++;
            mutex.release();
            overseer->endSect();
            //std::cout << "Thread " << overseer->getId() << " waiting" << std::endl;
            // Wait to be released
            numberOfOnesWaiting.acquire(); // Blocking
        }
    }
    else { // id == 0
        if(canEnterZero()){
            // Allow entry
            idIn = false;
            nbIn++;
            mutex.release();
            //std::cout << "Thread " << overseer->getId() << " entered without waiting" << std::endl;
            overseer->endSect();
        }
        else{
            // Add to the 0 waiting queue
            nbOfZerosWaiting++;
            mutex.release();
            overseer->endSect();
            //std::cout << "Thread " << overseer->getId() << " waiting" << std::endl;
            // Wait to be released
            numberOfZerosWaiting.acquire(); // Blocking
        }
    }

    //std::cout << "Thread " << overseer->getId() << " out access" << std::endl;
}

void SasAccess::leave(int id, ThreadParent* overseer){
    mutex.acquire(); // Blocking
    //std::cout << "Thread " << overseer->getId() << " in leave" << std::endl;
    overseer->startSect(leaveSectionId);
    nbIn--;

    if(peopleWaiting()){
        if(id == 1){
            if(nbOfOneWaiting > 0){
                // Check how many 1 can enter without exceeding the capacity
                unsigned int toRelease = std::min(nbOfOneWaiting, SIZE - nbIn);
                for(unsigned int i = 0; i < toRelease; ++i){
                    nbOfOneWaiting--;
                    nbIn++;
                    numberOfOnesWaiting.release();
                }
                // Define the current type
                idIn = true;
            }
            else if(nbOfZerosWaiting > 0){
                // Check how many 0 can enter without exceeding the capacity
                unsigned int toRelease = std::min(nbOfZerosWaiting, SIZE - nbIn);
                for(unsigned int i = 0; i < toRelease; ++i){
                    nbOfZerosWaiting--;
                    nbIn++;
                    numberOfZerosWaiting.release();
                }
                // Define the current type
                idIn = false;
            }
        }
        else { // id == 0
            if(nbOfZerosWaiting > 0){
                // Ceck how many 0 can enter without exceeding the capacity
                unsigned int toRelease = std::min(nbOfZerosWaiting, SIZE - nbIn);
                for(unsigned int i = 0; i < toRelease; ++i){
                    nbOfZerosWaiting--;
                    nbIn++;
                    numberOfZerosWaiting.release();
                }
                // Define the current type
                idIn = false;
            }
            else if(nbOfOneWaiting > 0){
                // Check how many 1 can enter without exceeding the capacity
                unsigned int toRelease = std::min(nbOfOneWaiting, SIZE - nbIn);
                for(unsigned int i = 0; i < toRelease; ++i){
                    nbOfOneWaiting--;
                    nbIn++;
                    numberOfOnesWaiting.release();
                }
                // Define the current type
                idIn = true;
            }
        }
    }
    mutex.release();
    //std::cout << "Thread " << overseer->getId() << " out leave" << std::endl;
    overseer->endScen();
}
