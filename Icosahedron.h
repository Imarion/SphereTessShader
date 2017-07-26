#ifndef Icosahedron_H
#define Icosahedron_H

class Icosahedron
{

private:
    int nFaces;

    // Vertices
    float *v;
    int nVerts;

    // Normals
    float *n;

    // Tex coords
    float *tc;

    // Elements
    unsigned int *el;

public:
    Icosahedron();

    float        *getv();
    unsigned int *getel();

    int    getnVerts();
    int    getnFaces();    
};

#endif // Icosahedron
