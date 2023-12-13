#include <stdexcept>
/** @file
 * Filtre Super Pixel
 **/
#include <cmath>
#ifndef IMAGE_H
#define IMAGE_H
    #include "../image.hpp"
#endif
#include "superpixel.hpp"

double distancePoints(Point p, Point c) {
    if(p.size() != c.size())
        throw runtime_error("Impossible to calculate a distance: the sizes of vectors aren't same!");

    double squares_sum = 0;
    for(int i = 0; i < p.size(); i++){
        squares_sum += (p[i] - c[i]) * (p[i] - c[i]);
    }

    double distance = sqrt(squares_sum);
    return distance;
}

double distanceAEnsemble(Point p, EnsemblePoints C) {
    double smallest_distance = distancePoints(p, C[0]);
    for(Point point : C){
        double distance = distancePoints(p, point);
        if(distance < smallest_distance)
            smallest_distance = distance;
    }
    return smallest_distance;
}

int plusProcheVoisin(Point p, EnsemblePoints C) {
    int index_of_closest_neighbour = 0;
    double smallest_distance = distancePoints(p, C[ index_of_closest_neighbour ]);

    for(int i = 0; i < C.size(); i++){
        Point point = C[i]; 
        double distance = distancePoints(p, point);
        if(distance < smallest_distance){
            smallest_distance = distance;
            index_of_closest_neighbour = i;
        }
    }
    return index_of_closest_neighbour;
}

EnsemblePoints sousEnsemble(EnsemblePoints P,EnsemblePoints C,int k) {
    EnsemblePoints ensemble = EnsemblePoints(0);
    for(int i = 0; i < P.size(); i++){
        Point p = P[i];
        if(k == plusProcheVoisin(p, C))
            ensemble.push_back(p);
    }
    return ensemble;
}

Point barycentre(EnsemblePoints Q) {
    if(Q.size() == 0)
        throw runtime_error("L'ensemble des points est vide!");
    if(Q[0].size() == 0)
        throw runtime_error("Le point est vide!");
    
    Point barycentre = Point(Q[0].size());
    for(int i = 0; i < Q.size(); i++){
        for(int j = 0; j < Q[i].size(); j++){
            barycentre[j] += Q[i][j];
        }
    }
    for(int j = 0; j < Q[0].size(); j++){
        barycentre[j] /= Q.size();
    }
    return barycentre;
}

EnsemblePoints KMoyenne(EnsemblePoints P,EnsemblePoints C, int nbAmeliorations) {
    EnsemblePoints C_better_version = C;
    EnsemblePoints C_new_better_version = C;
    for(int i = 0; i < nbAmeliorations; i++){
        for(int j = 0; j < C.size(); j++){
            C_new_better_version[j] = barycentre(sousEnsemble(P, C_better_version, j));
        }
        C_better_version = C_new_better_version;
    }
    return C_better_version;
}

EnsemblePoints FAST_KMoyenne(EnsemblePoints P,EnsemblePoints C, int nbAmeliorations) {
    vector<int> label;
    label.resize(P.size());
    for(int n=0; n<nbAmeliorations; n++) {
        vector<int> clusterSize;
        clusterSize.resize(C.size(),0);
        for (int p=((int)P.size())-1; p>=0; p--) {
            double di = 0;
            int nn=0;
            for(int d=((int)P[0].size())-1; d>=0; d--)
                di+=(P[p][d]-C[0][d])*(P[p][d]-C[0][d]);
            for(int c=((int)C.size())-1; c>=1; c--) {
                double dt=0;
                for(int d=((int)P[0].size())-1; d>=0; d--)
                    dt+=(P[p][d]-C[c][d])*(P[p][d]-C[c][d]);
                if(dt<di) {
                    di=dt;
                    nn=c;
                }
            }
            label[p]=nn;
            clusterSize[nn]++;
        }
        for (int p=((int)P.size())-1; p>=0; p--)
            for(int d=((int)P[0].size())-1; d>=0; d--)
                C[label[p]][d]+=P[p][d];
        for(int c=((int)C.size())-1; c>=0; c--)
            if(clusterSize[c]!=0)
                for(int d=((int)P[0].size())-1; d>=0; d--)
                    C[c][d] = C[c][d]/(clusterSize[c]+1);
    }
    return C;
}

EnsemblePoints pivotSuperPixel(Image img, double lambda, int mu) {
    EnsemblePoints new_ensemble = EnsemblePoints(0);
    for(int i = 0; i < img.size(); i += mu){
        for(int j = 0; j < img[i].size(); j += mu){
            Couleur color = img[ i ][ j ];
            Point point = consrtuireUnPointDePixel(i, j, lambda * color.r, lambda * color.g, lambda * color.b);

            new_ensemble.push_back(point);
        }
    }
    return new_ensemble;
}

EnsemblePoints superPixels(Image img,double lambda, int mu, int nbAmeliorations) {
    EnsemblePoints img_points = EnsemblePoints(0);
    for(int i = 0; i < img.size(); i++){
        for(int j = 0; j < img[i].size(); j++){
            Point img_point = consrtuireUnPointDePixel(i, j, lambda * img[i][j].r, lambda * img[i][j].g, lambda * img[i][j].b);

            img_points.push_back(img_point);
        }
    }
    return FAST_KMoyenne(img_points, pivotSuperPixel(img, lambda, mu), nbAmeliorations);
}

Image superPixel(Image img, double lambda, int mu, int nbAmeliorations) {
    Image new_image = Image(img.size());
    for(int i = 0; i < img.size(); i++){
        new_image[i] = vector<Couleur>(img[i].size());
    }
    EnsemblePoints super_pixels = superPixels(img, lambda, mu, nbAmeliorations);

    for(int i = 0; i < img.size(); i++){
        for(int j = 0; j < img[i].size(); j++){
            Couleur pixel = img[i][j];
            Point point = consrtuireUnPointDePixel(i, j, lambda * pixel.r, lambda * pixel.g, lambda * pixel.b);
            Point point_associe = super_pixels[plusProcheVoisin(point, super_pixels)];

            Couleur new_pixel;
            new_pixel.r = point_associe[2] / lambda;
            new_pixel.g = point_associe[3] / lambda;
            new_pixel.b = point_associe[4] / lambda;

            new_image[i][j] = new_pixel;
        }
    }
    return new_image;
}

Image bordurePixels(Image img){
    if(img.size() == 0)
        throw runtime_error("L'image est vide!");
    if(img[0].size() == 0)
        throw runtime_error("L'image est vide!");

    Image new_image = Image(img.size());
    for(int i = 0; i < img.size(); i++){
        new_image[i] = vector<Couleur>(img[i].size());
    }

    for(int i = 0; i < img.size(); i++){
        for(int j = 0; j < img[i].size(); j++){
            new_image[i][j] = img[i][j];
        }
    }

    for(int i = 1; i < new_image.size(); i++){
        for(int j = 1; j < new_image[i].size(); j++){
            if(!areColorsEquals(img[i-1][j], img[i][j]) || !areColorsEquals(img[i][j-1], img[i][j])){
                Couleur bleu;
                bleu.r = 0;
                bleu.g = 0;
                bleu.b = 255;
                new_image[i][j] = bleu;
            }

        }
    }
    return new_image;
}

bool areColorsEquals(Couleur color1, Couleur color2){
    return color1.r == color2.r && color1.g == color2.g && color1.b == color2.b;
}

Point consrtuireUnPointDePixel(int i, int j, double r, double g, double b){
    Point point = Point(5);
    point[0] = i;
    point[1] = j;
    point[2] = r;
    point[3] = g;
    point[4] = b;
    return point;
}


