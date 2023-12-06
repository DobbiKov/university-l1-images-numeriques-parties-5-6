
/** @file
 * Filtres de conversion couleur <-> teintes de gris
 **/

#include <iostream>
#include <stdexcept>

#include "./ppm_lib/ppm.hpp"
#include "ppm-test.hpp"
using namespace std;

void lireEcrirePPMTest(){
    cout << "Vérifier que les images obtenues dans 'ppm/' sont identiques aux images d'origine dans 'images/'" << endl;
    ecrirePPM(lirePPM("images/Baboon.512.ppm"),  "ppm/Baboon.512.ppm");
    ecrirePPM(lirePPM("images/Billes.256.ppm"),  "ppm/Billes.256.ppm");
    ecrirePPM(lirePPM("images/Embryos.512.ppm"), "ppm/Embryos.512.ppm");
    ecrirePPM(lirePPM("images/House.256.ppm"),   "ppm/House.256.ppm");
}

int main(){
    cerr << "Tests des fonctions lirePPM et ecrirePPM" << endl;
    lireEcrirePPMTest();
}

