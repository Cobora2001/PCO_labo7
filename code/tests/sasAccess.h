#ifndef SASACCESS_H
#define SASACCESS_H

#include <pcosynchro/pcothread.h>
#include <pcosynchro/pcomutex.h>
#include <pcosynchro/pcosemaphore.h>

class ThreadParent;

class SasAccess{
public:

    /**
     * @brief Construct a new Sas Access object
     * @param size the size of the sas
     * @param accessSectionId the ID of the section in the Access function
     * @param leaveSectionId the ID of the section in the Leave function
     * default values are 1 and 3 based on test that we run.
     */
    SasAccess(unsigned int size, unsigned int accessSectionId = 1, unsigned int leaveSectionId = 3); 

    /**
     * @brief Function called by an agent to enter the sas
     * @param id the agent's id (0 or 1)
     * @param overseer the agent's thread
     */
    void access(int id, ThreadParent* overseer);

    /**
     * @brief Function called by an agent to leave the sas
     * @param id the agent's id (0 or 1)
     * @param overseer the agent's thread
     */
    void leave(int id, ThreadParent* overseer);

    /**
     * @brief Get the number of agents in the sas
     * @return the number of agents in the sas
     */
    int getNbIn() {
        mutex.acquire();
        int res = nbIn;
        mutex.release();
        return res;
    }

    /**
     * @brief Get the number of 1 waiting to enter the sas
     * @return the number of 1 waiting to enter the sas
     */
    int getNbOfOneWaiting() {
        mutex.acquire();
        int res = nbOfOneWaiting;
        mutex.release();
        return res;
    }

    /**
     * @brief Get the number of 0 waiting to enter the sas
     * @return the number of 0 waiting to enter the sas
     */
    int getNbOfZerosWaiting() {
        mutex.acquire();
        int res = nbOfZerosWaiting;
        mutex.release();
        return res;
    }

    /**
     * @brief Reset the sas for the next scenario
     */
    void reset() {
        mutex.acquire();
        // Free all the agents waiting for the next scenario
        for(unsigned int i = 0; i < nbOfOneWaiting; ++i){
            numberOfOnesWaiting.release();
        }
        for(unsigned int i = 0; i < nbOfZerosWaiting; ++i){
            numberOfZerosWaiting.release();
        }

        // Reset the values
        nbIn = 0;
        nbOfOneWaiting = 0;
        nbOfZerosWaiting = 0;
        idIn = false;
    
        mutex.release();
    }
private:
    // Mutex to protect the critical section
    PcoSemaphore mutex;

    // Semaphore to wait for the right to enter the critical section
    PcoSemaphore numberOfZerosWaiting;
    PcoSemaphore numberOfOnesWaiting;

    // the size of the sas
    const unsigned int SIZE;
    // Number of agents in the sas
    unsigned int nbIn;
    // Number of 1 waiting to enter the sas
    unsigned int nbOfOneWaiting;
    // Number of 0 waiting to enter the sas
    unsigned int nbOfZerosWaiting;

    // Agent's type in the sas
    bool idIn;

    // The ID of the section in the Access function
    unsigned int accessSectionId;

    // The ID of the section in the Leave function
    unsigned int leaveSectionId;
    
    /**
     * @brief Check if an agent can enter the sas (agent type 1)
     * @return true if the agent can enter the sas, false otherwise
     */
    bool canEnterOne() {
        return (nbIn < SIZE) && (nbIn == 0 || idIn == 1);
    }

    /**
     * @brief Check if an agent can enter the sas (agent type 0)
     * @return true if the agent can enter the sas, false otherwise
     */
    bool canEnterZero() {
        return (nbIn < SIZE) && (nbIn == 0 || idIn == 0);
    }

    /**
     * @brief Check if there are people waiting to enter the sas
     * @return true if there are people waiting, false otherwise
     */
    bool peopleWaiting() {
        return nbOfOneWaiting > 0 || nbOfZerosWaiting > 0;
    }
};

#endif // SASACCESS_H
