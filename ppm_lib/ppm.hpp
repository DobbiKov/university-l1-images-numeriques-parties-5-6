/** @file
 * Lecture et ecriture de fichiers au format PPM
 **/

#include <string>

#ifndef IMAGE_H
#define IMAGE_H
    #include "../image.hpp"
#endif

using namespace std;

/// BEGIN ppm

/** Lit une image au format PPM, retourne un tableau de Couleur
 * @param source vers une image .ppm
 * @return une image
 **/
Image lirePPM(string source);

/**  Écrit une image dans un fichier PPM
 * @param img une image
 * @param cible le nom d'un fichier PPM
 **/
void  ecrirePPM(Image img, string cible);
