#include <vector>
#include <iostream>
#ifndef IMAGE_H
#define IMAGE_H
    #include "../image.hpp"
#endif

using namespace std;

/** lissage 
 * @param img une image
 * @return une image lissé
**/
ImageGris lissage(ImageGris img);

/** filtre de Sobel horizontal
 * @param img une image en teintes de gris
 * @return une image en teintes de gris de l'intensite horizontale de img
 **/
ImageGris intensiteH(ImageGris img);


/// BEGIN intensiteV

/** filtre de Sobel vertical
 * @param img une image en teintes de gris
 * @return une image en teintes de gris de l'intensite verticale de img
 **/
ImageGris intensiteV(ImageGris img);


/// BEGIN intensiteHV

/** filtre de Sobel
 * @param img une image en teintes de gris
 * @return une image en teintes de gris de l'intensite de img
 **/
ImageGris intensite(ImageGris img);