#pragma once

#include "../graph.h"
#include "../cs225/PNG.h"
#include "../cs225/HSLAPixel.h"
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <vector>
#include <string>
#include <unordered_map>
#include <utility>
#include <algorithm>
#include <stdlib.h>
#include <iomanip>
#include <random>
#include <initializer_list>

using namespace std;

class ForceDirectedGraph {

public:

    class Vertex {

    public:
        Vertex(string source) : source_(source) { }

        void insertEdge(Vertex* target, unsigned int length) {
            edges_[target] = length;
        }

        string getSource() {
            return source_;
        }

        float & getSize() {
            return size_;
        }

        pair<float, float> & getPosition() {
            return position_;
        }

        unsigned int getLength(Vertex* target) {
            return edges_[target];
        }

        bool isTarget(Vertex* vertex) {
            if (vertex == this)
                return false;
            return edges_.find(vertex) != edges_.end();
        }

    //private:
        string source_;
        float size_;
        pair<float, float> position_;
        unordered_map<Vertex*, unsigned int> edges_;
    };

    /**
     * This function reads node data from tsv file, including duplicates
     * @param filename --> name of tsv data file
     */
    void readFromTSV(string fileName);

    void importSizes(const vector<pair<string, float> > & sizes);

    virtual void findEquilibrium(unsigned int iterations) = 0;

    cs225::PNG* printGraph(unsigned int width, unsigned int height); // add PNG class to project and return PNG*

    void lubysAlg(); //MIS alg

    /**
    * inserts vertex into vertices_ unordered map
    * @param source
    */
    void insertVertex(string source);

    /**
    * insertEdge creates source and target vertices if they do not exists
    * @param source
    * @param target
    */
    void insertEdge(string source, string target, unsigned int length);

protected:

    unordered_map<string, Vertex*> vertices_; // map: node name >> pointer to node

    vector<string> keys_;

    int bound_;

};
