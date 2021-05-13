#pragma once

#include "fdgraph.h"
#include <math.h>
#include <time.h>

#define C_REP 0.3f
#define C_STRING 1.0f
#define EPSILON 0.1f
#define DELTA 0.1f

class SpringEmbedder: public ForceDirectedGraph {

public:

    void findEquilibrium(unsigned int iterations);

    void setRandomPositions(float bound);

    void setPosition(string vertex, float x, float y);

    void printPositions(unsigned int num);

private:

    pair<float, float> repulsiveForce(Vertex* source, Vertex* target);
    pair<float, float> attractiveForce(Vertex* source, Vertex* target);
    pair<float, float> displacement(Vertex* source);

};