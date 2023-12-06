/** @file
 * Filtres de conversion couleur <-> teintes de gris
 **/

#ifndef IMAGE_H
#define IMAGE_H
    #include "../image.hpp"
#endif

/// BEGIN griscouleurh

/** Transforme une image couleur en une image en teintes de gris
 * @param img une image
 * @return une image en teintes de gris
 **/
ImageGris CouleurAuGris(Image img);

/** Transforme une image en teintes de gris en une image en couleurs (mais grise)
 * @param img une image en teintes de gris
 * @return une image
 **/
Image GrisACouleur(ImageGris img);

/// END griscouleurh
