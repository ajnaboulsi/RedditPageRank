#include "springembedder.h"



/**
 * Finds the equilibrium position of a set of vertices and edges using the displacement function.
 *
 * @param iterations the number of iterations 
 * @return 
 */
void SpringEmbedder::findEquilibrium(unsigned int iterations) {
    unordered_map<string, pair<float, float> > displacements;
    unsigned int t = 0;
    unsigned int i = 0;
    while (t++ < iterations) {
        for (auto kv : vertices_) {
            ++i;
            displacements[kv.first] = displacement(kv.second);
        }
        for (auto kv : vertices_) {
            setPosition(kv.first, kv.second->getPosition().first + displacements[kv.first].first, kv.second->getPosition().second + displacements[kv.first].second);
            //cout << displacements[kv.first].first << ", " << displacements[kv.first].second << endl;
            // kv.second->getPosition().first += displacements[kv.first].first;
            // kv.second->getPosition().second += displacements[kv.first].second;
        }
    }
}


/**
 * Sets the vertices at random locations.
 *
 * @param bound a bound set so that the locations of the vertices are within a certain range.
 * @return 
 */
void SpringEmbedder::setRandomPositions(float bound) {
    bound_ = (int)bound;
    for (auto kv : vertices_) {
        kv.second->getPosition() = {bound * (float)rand() / (float)RAND_MAX, bound * (float)rand() / (float)RAND_MAX};
    }
}

/**
 * Sets the vertex at a specified position.
 *
 * @param vertex the subreddit that is being placed on the plane
 * @param x the x coordinate of the new location of the subreddit
 * @param y the y coordinate of the new location of the subreddit
 * @return 
 */
void SpringEmbedder::setPosition(string vertex, float x, float y) {
    vertices_[vertex]->getPosition() = {x, y};
    if (x >= bound_)
        vertices_[vertex]->getPosition().first = bound_ - 1;
    else if (x < 0)
        vertices_[vertex]->getPosition().first = 0;
    if (y >= bound_)
        vertices_[vertex]->getPosition().second = bound_ - 1;
    else if (y < 0)
        vertices_[vertex]->getPosition().second = 0;
}

/**
 * Prints the positions of each vertex.
 *
 * @param num the number of vertices' locations to be printed
 * @return 
 */
void SpringEmbedder::printPositions(unsigned int num) {
    pair<float, float> pos;
    cout << "Positions: " << endl;
    unsigned int i = 0;
    for (auto kv : vertices_) {
        if (i++ > num) break;
        pos = kv.second->getPosition();
        cout << kv.first << setprecision(5) << fixed << ": < " << pos.first << ", " << pos.second << " >" << endl;
    }
}

/**
 * Finds the repuslive force between two vertices.
 *
 * @param source a pointer to the source vertex
 * @param target a pointer to the target vertex
 * @return a pair containing an x and y coordinate of the force vector. 
 */
pair<float, float> SpringEmbedder::repulsiveForce(Vertex* source, Vertex* target) {
    float diffX = target->getPosition().first - source->getPosition().first; // ∆x
    float diffY = target->getPosition().second - source->getPosition().second; // ∆y
    float magSqrd = diffX * diffX + diffY * diffY; // magnitude squared of vector <∆x, ∆y>
    magSqrd = (magSqrd == 0.0f) ? 0.1f : magSqrd;
    return {C_REP * -diffX / magSqrd, C_REP * -diffY / magSqrd};
}

/**
 * Finds the attractive force between two vertices.
 *
 * @param source a pointer to the source vertex
 * @param target a pointer to the target vertex
 * @return a pair containing an x and y coordinate of the force vector. 
 */
pair<float, float> SpringEmbedder::attractiveForce(Vertex* source, Vertex* target) {
    float diffX = target->getPosition().first - source->getPosition().first; // -∆x
    float diffY = target->getPosition().second - source->getPosition().second; // -∆y
    // diffX = (diffX > 50) ? 50 : (diffX < -50) ? -50 : diffX;
    // diffY = (diffY > 50) ? 50 : (diffY < -50) ? -50 : diffY;
    float logTerm = log10(sqrt(diffX * diffX + diffY * diffY) * ((float)source->getLength(target))); // log term: log(mag/l)
    return {C_STRING * logTerm * diffX, C_STRING * logTerm * diffY};
}

/**
 * Finds the displacement of a vertex due to the attractive and repulsive forces.
 *
 * @param source a pointer to the source vertex
 * @return a pair containing an x and y coordinate of the displacement vector 
 */
pair<float, float> SpringEmbedder::displacement(Vertex* source) {
    pair<float, float> force;
    float sumX = 0, sumY = 0;
    for (auto kv : source->edges_) {
        force = attractiveForce(source, kv.first);
        sumX = (sumX + force.first > 2000) ? 2000 : (sumX + force.first < -2000) ? -2000 : sumX + force.first;
        sumY = (sumY + force.second > 2000) ? 2000 : (sumY + force.second < -2000) ? -2000 : sumY + force.second;
    }

    // string current;
    // for (int i = 0; i < 100; ++i) {
    //     current = keys_[rand() % keys_.size()];
    //     while (source->isTarget(vertices_[current]))
    //         current = keys_[rand() % keys_.size()];
    //     force = repulsiveForce(source, vertices_[current]);
    //     sumX = (sumX + force.first > 2000) ? 2000 : (sumX + force.first < -2000) ? -2000 : sumX + force.first;
    //     sumY = (sumY + force.second > 2000) ? 2000 : (sumY + force.second < -2000) ? -2000 : sumY + force.second;
    //     //cout << force.first << ", " << force.second << endl;
    // }
    //cout << sumX << ", " << sumY << endl;

    // for (auto kv : vertices_) {
    //     if (kv.second == source) continue;
    //     if (source->isTarget(kv.second)) {
    //         force = attractiveForce(source, kv.second);
    //         sumX += force.first;
    //         sumY += force.second;
    //     }
    //     else if (!kv.second->isTarget(source)) {
    //         force = repulsiveForce(source, kv.second);
    //         sumX += force.first;
    //         sumY += force.second;
    //     }
    // }
    return {DELTA * sumX, DELTA * sumY};
}