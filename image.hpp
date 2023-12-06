#include <vector>

using namespace std;

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