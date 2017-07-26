#include "Icosahedron.h"

#include <cstdio>

Icosahedron::Icosahedron()
    :nFaces(20), nVerts(12)
{

    v = new float[12*3]
    {
         0.000f,  0.000f,  1.000f,
         0.894f,  0.000f,  0.447f,
         0.276f,  0.851f,  0.447f,
        -0.724f,  0.526f,  0.447f,
        -0.724f, -0.526f,  0.447f,
         0.276f, -0.851f,  0.447f,
         0.724f,  0.526f, -0.447f,
        -0.276f,  0.851f, -0.447f,
        -0.894f,  0.000f, -0.447f,
        -0.276f, -0.851f, -0.447f,
         0.724f, -0.526f, -0.447f,
         0.000f,  0.000f, -1.000f
    };

    el = new unsigned int[20*3]
    {
         2,  1,  0,
         3,  2,  0,
         4,  3,  0,
         5,  4,  0,
         1,  5,  0,
        11,  6,  7,
        11,  7,  8,
        11,  8,  9,
        11,  9, 10,
        11, 10,  6,
         1,  2,  6,
         2,  3,  7,
         3,  4,  8,
         4,  5,  9,
         5,  1, 10,
         2,  7,  6,
         3,  8,  7,
         4,  9,  8,
         5, 10,  9,
         1,  6, 10
    };
/*
    glGenVertexArrays( 1, &vaoHandle );
    glBindVertexArray(vaoHandle);

    unsigned int handle[4];
    glGenBuffers(4, handle);

    glBindBuffer(GL_ARRAY_BUFFER, handle[0]);
    glBufferData(GL_ARRAY_BUFFER, 24 * 3 * sizeof(float), v, GL_STATIC_DRAW);
    glVertexAttribPointer( (GLuint)0, 3, GL_FLOAT, GL_FALSE, 0, ((GLubyte *)NULL + (0)) );
    glEnableVertexAttribArray(0);  // Vertex position

    glBindBuffer(GL_ARRAY_BUFFER, handle[1]);
    glBufferData(GL_ARRAY_BUFFER, 24 * 3 * sizeof(float), n, GL_STATIC_DRAW);
    glVertexAttribPointer( (GLuint)1, 3, GL_FLOAT, GL_FALSE, 0, ((GLubyte *)NULL + (0)) );
    glEnableVertexAttribArray(1);  // Vertex normal

    glBindBuffer(GL_ARRAY_BUFFER, handle[2]);
    glBufferData(GL_ARRAY_BUFFER, 24 * 2 * sizeof(float), tex, GL_STATIC_DRAW);
    glVertexAttribPointer( (GLuint)2, 2, GL_FLOAT, GL_FALSE, 0, ((GLubyte *)NULL + (0)) );
    glEnableVertexAttribArray(2);  // texture coords

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, handle[3]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 36 * sizeof(GLuint), el, GL_STATIC_DRAW);

    glBindVertexArray(0);
    */
}
/*
void VBOCube::render() {
    glBindVertexArray(vaoHandle);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, ((GLubyte *)NULL + (0)));
}
*/

float *Icosahedron::getv()
{
    return v;
}

int Icosahedron::getnVerts()
{
    return nVerts;
}

unsigned int *Icosahedron::getel()
{
    return el;
}

int Icosahedron::getnFaces()
{
    return nFaces;
}
