#include <stdexcept>

#include <iostream>

#ifndef IMAGE_H
#define IMAGE_H
    #include "image.hpp"
#endif
#include "ppm_lib/ppm.hpp"
#include "gris_couleurs/gris-couleurs.hpp"
#include "gris-couleurs-test.hpp"

using namespace std;



void testColorInGrey(){
    Image baboon = lirePPM("images/Baboon.512.ppm");
    ImageGris baboon_gris = CouleurAuGris(baboon);
    Image ppm_gris_baboon = GrisACouleur(baboon_gris);

    ecrirePPM(ppm_gris_baboon,  "ppm/Baboon.512-gris.ppm");
    
    ecrirePPM(
        GrisACouleur(
            CouleurAuGris(
                lirePPM("images/Billes.256.ppm")
            )
        ),  "ppm/Billes.256-gris.ppm");
    ecrirePPM(
        GrisACouleur(
            CouleurAuGris(
                lirePPM("images/Embryos.512.ppm")
            )
        ),  "ppm/Embryos.512-gris.ppm");
    ecrirePPM(
        GrisACouleur(
            CouleurAuGris(
                lirePPM("images/House.256.ppm")
            )
        ),  "ppm/House.256-gris.ppm");
}


int main(){
    cerr << "Tests des fonctions gris..." << endl;
    testColorInGrey();
}

