#ifndef IMAGE_H
#define IMAGE_H
    #include "image.hpp"
#endif

/** Infrastructure minimale de test **/
#define CHECK(test) if (!(test)) cerr << "Test failed in file " << __FILE__ << " line " << __LINE__ << ": " #test << endl

/** Une image 4x4 pour faire des tests **/
Image imgTest = {
    { Couleur({0,0,0}), Couleur({255,255,255}), Couleur({255,0,0}), Couleur({255,255,0}) },
    { Couleur({0,0,255}), Couleur({0,255,0}), Couleur({0,255,255}), Couleur({120,120,120}) },
    { Couleur({42,174,86}), Couleur({141,194,57}), Couleur({68,107,43}), Couleur({73, 98, 40}) },
    { Couleur({60, 196, 74}), Couleur({141,194,57}), Couleur({61,102,43}), Couleur({214,38,102}) }
};