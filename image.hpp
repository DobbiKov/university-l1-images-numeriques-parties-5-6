#include <iostream>
#include <vector>

using namespace std;

/** Structure de données pour représenter une image binaire **/
typedef vector<vector<int> > ImageNB;

/** Structure de donnees pour representer une image en teintes de gris **/
typedef vector<vector<double> > ImageGris;

/** Structure de donnees pour representer un pixel en couleur **/
struct Couleur {
    /** Intensite de rouge **/
    double r;
    /** Intensite de vert **/
    double g;
    /** Intensite de bleu **/
    double b;
};

/** Structure de donnees pour representer une image **/
typedef vector<vector<Couleur> > Image;