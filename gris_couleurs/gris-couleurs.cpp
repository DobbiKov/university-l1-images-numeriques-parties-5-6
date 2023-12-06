#include <stdexcept>
/** @file
 * Filtres de conversion couleur <-> teintes de gris
 **/
#include "gris-couleurs.hpp"

ImageGris CouleurAuGris( Image img ) {
    if(img.size() == 0)
        throw runtime_error("The image is empty!");
    if(img[0].size() == 0)
        throw runtime_error("The image is empty!");

    ImageGris gris_image = ImageGris(img.size());
    for(int i = 0; i < gris_image.size(); i++){
        gris_image[i] = vector<double>(img[i].size());
    }

    for(int i = 0; i < gris_image.size(); i++){
        for(int j = 0; j < gris_image[i].size(); j++){
            Couleur color = img[i][j];
            gris_image[i][j] = (0.2126 * color.r) + (0.7152 * color.g) + (0.0722 * color.b); 
        }
    }
    return gris_image;
}

Image GrisACouleur( ImageGris img ) {
    if(img.size() == 0)
        throw runtime_error("The image is empty!");
    if(img[0].size() == 0)
        throw runtime_error("The image is empty!");

    Image color_img = Image(img.size());
    for(int i = 0; i < color_img.size(); i++){
        color_img[i] = vector<Couleur>(img[i].size());
    }

    for(int i = 0; i < color_img.size(); i++){
        for(int j = 0; j < color_img[i].size(); j++){
            double grey_color = img[i][j];

            Couleur color;
            color.r = grey_color;
            color.g = grey_color;
            color.b = grey_color;

            color_img[i][j] = color;
        }
    }
    return color_img;
}

