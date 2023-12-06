#include <stdexcept>
#include <fstream>
#include <vector>

#ifndef IMAGE_H
#define IMAGE_H
    #include "../image.hpp"
#endif
#include "ppm.hpp"

using namespace std;

Image lirePPM(string source){
    ifstream file;
    file.open(source);

    string temp;
    file >> temp; //read P3

    int colonnes, lignes;
    file >> colonnes;
    file >> lignes;

    double colors;
    file >> colors;

    Image img = Image(lignes);
    for(int i = 0; i < lignes; i++){
        img[i] = vector<Couleur>(colonnes);
    }

    double value;
    int pixel_count = 0;
    for(int i = 0; i < lignes; i++){
        for(int j = 0; j < colonnes; j++){
            Couleur color;

            file >> value;
            color.r = (value / colors) * 255.0;

            file >> value;
            color.g = (value / colors) * 255.0;

            file >> value;
            color.b = (value / colors) * 255.0;

            img[i][j] = color;
        }
    }
    file.close();
    return img;
}

void  ecrirePPM(Image img, string cible){
    if(img.size() == 0)
        throw runtime_error("The image is empty!");
    if(img[0].size() == 0)
        throw runtime_error("The image is empty!");

    ofstream file;
    file.open(cible);
    file << "P3\n";
    int lignes = img.size();
    int colonnes = img[0].size();

    file << colonnes << " " << lignes << endl;
    file << "255\n";

    for(vector<Couleur> ligne : img){
        for(Couleur color : ligne){
            file << (int)color.r << " " << (int)color.g << " " << (int)color.b << " ";
        }
        file << endl;
    }
    file.close();
}