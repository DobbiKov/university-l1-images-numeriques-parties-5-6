#include <stdexcept>
/** @file
 * Filtre Super Pixel
 **/
#include <cmath>
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
        throw runtime_error("L'ensemble des points et vide!");
    if(Q[0].size() == 0)
        throw runtime_error("Le point est vide!");
    
    int iteration = 1;
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
    // Point temp_barycentre = barycentre(P);
    // EnsemblePoints new_ensemble = sousEnsemble(P, C, temp_barycentre);
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
    // Remplacez cette ligne et la suivante par le code adéquat
    throw runtime_error("Fonction pivotSuperPixel non implantée ligne 74");
}

EnsemblePoints superPixels(Image img,double lambda, int mu, int nbAmeliorations) {
    // Remplacez cette ligne et la suivante par le code adéquat
    throw runtime_error("Fonction superPixels non implantée ligne 79");
}

Image superPixel(Image img, double lambda, int mu, int nbAmeliorations) {
    // Remplacez cette ligne et la suivante par le code adéquat
    throw runtime_error("Fonction superPixel non implantée ligne 84");
}



// Ecrire votre code ici


