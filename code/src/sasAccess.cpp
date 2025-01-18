#include <sasAccess.h>
#include <iostream>
#include <algorithm> // Pour std::min

SasAccess::SasAccess(unsigned int N) 
    : idIn(0), SIZE(N), nbIn(0), nbOfOneWaiting(0), nbOfZerosWaiting(0),
      mutex(1), numberOfZerosWaiting(0), numberOfOnesWaiting(0) {
    if(N <= 1) {
        std::cerr << "La taille du sas doit être supérieure à 1" << std::endl;
        exit(1);
    }
}

void SasAccess::access(int id){
    mutex.acquire();
    
    if(id == 1){
        if(canEnterOne()){
            // Autoriser l'entrée
            idIn = true;
            nbIn++;
            mutex.release();
        }
        else{
            // Ajouter à la file d'attente des 1
            nbOfOneWaiting++;
            mutex.release();
            // Attendre d'être libéré
            numberOfOnesWaiting.acquire();
        }
    }
    else { // id == 0
        if(canEnterZero()){
            // Autoriser l'entrée
            idIn = false;
            nbIn++;
            mutex.release();
        }
        else{
            // Ajouter à la file d'attente des 0
            nbOfZerosWaiting++;
            mutex.release();
            // Attendre d'être libéré
            numberOfZerosWaiting.acquire();
        }
    }
}

void SasAccess::leave(int id){
    mutex.acquire();
    nbIn--;

    if(peopleWaiting()){
        if(id == 1){
            if(nbOfOneWaiting > 0){
                // Déterminer combien de 1 peuvent entrer sans dépasser la capacité
                unsigned int toRelease = std::min(nbOfOneWaiting, SIZE - nbIn);
                for(unsigned int i = 0; i < toRelease; ++i){
                    nbOfOneWaiting--;
                    nbIn++;
                    numberOfOnesWaiting.release();
                }
                // Définir le type actuel
                idIn = true;
            }
            else if(nbOfZerosWaiting > 0){
                // Déterminer combien de 0 peuvent entrer sans dépasser la capacité
                unsigned int toRelease = std::min(nbOfZerosWaiting, SIZE - nbIn);
                for(unsigned int i = 0; i < toRelease; ++i){
                    nbOfZerosWaiting--;
                    nbIn++;
                    numberOfZerosWaiting.release();
                }
                // Définir le type actuel
                idIn = false;
            }
        }
        else { // id == 0
            if(nbOfZerosWaiting > 0){
                // Déterminer combien de 0 peuvent entrer sans dépasser la capacité
                unsigned int toRelease = std::min(nbOfZerosWaiting, SIZE - nbIn);
                for(unsigned int i = 0; i < toRelease; ++i){
                    nbOfZerosWaiting--;
                    nbIn++;
                    numberOfZerosWaiting.release();
                }
                // Définir le type actuel
                idIn = false;
            }
            else if(nbOfOneWaiting > 0){
                // Déterminer combien de 1 peuvent entrer sans dépasser la capacité
                unsigned int toRelease = std::min(nbOfOneWaiting, SIZE - nbIn);
                for(unsigned int i = 0; i < toRelease; ++i){
                    nbOfOneWaiting--;
                    nbIn++;
                    numberOfOnesWaiting.release();
                }
                // Définir le type actuel
                idIn = true;
            }
        }
    }
    mutex.release();
}
