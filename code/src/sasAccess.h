#ifndef SASACCESS_H
#define SASACCESS_H

#include <pcosynchro/pcothread.h>
#include <pcosynchro/pcomutex.h>
#include <pcosynchro/pcosemaphore.h>

class sasAccess{
public:
    sasAccess(unsigned int size);
    void access(int id);
    void leave(int id);
private:
    // Mutex pour protéger la section critique
    PcoSemaphore mutex;

    // Sémaphores pour attendre le droit d'entrer dans la section critique
    PcoSemaphore numberOfZerosWaiting;
    PcoSemaphore numberOfOnesWaiting;

    // Taille du sas
    const unsigned int SIZE;
    // Nombre de personnes présentes dans le sas
    unsigned int nbIn;
    // Nombre de 1 en attente pour entrer dans le sas
    unsigned int nbOfOneWaiting;
    // Nombre de 0 en attente pour entrer dans le sas
    unsigned int nbOfZerosWaiting;

    // Type d'agents actuellement dans le sas (0 ou 1)
    bool idIn;
    
    // Vérifie si un agent de type 1 peut entrer
    bool canEnterOne() {
        return (nbIn < SIZE) && (nbIn == 0 || idIn == 1);
    }

    // Vérifie si un agent de type 0 peut entrer
    bool canEnterZero() {
        return (nbIn < SIZE) && (nbIn == 0 || idIn == 0);
    }

    // Vérifie si des agents sont en attente
    bool peopleWaiting() {
        return nbOfOneWaiting > 0 || nbOfZerosWaiting > 0;
    }
};

#endif // SASACCESS_H
