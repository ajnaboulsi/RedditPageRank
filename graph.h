#pragma once

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
#include <utility>
#include <queue>

using namespace std;

class Graph {

public:

    class Vertex {

    public:
        Vertex(string source) : source_(source), visits_(0), label(0), depth(0) {}
        // Vertex(string source, vector<pair<Vertex*, int> > edges) : source_(source), edges_(edges), visits_(0) {}

        void insertEdge(Vertex* edge) {
            edges_.push_back(make_pair(edge, 0));
        }

        string getsource() {
            return source_;
        }

        unsigned int & getVisits() {
            return visits_;
        }

        Vertex * randEdge() {
            if (edges_.empty()) {
                return this;
            }
            return edges_[rand() % edges_.size()].first;
        }

        bool getLabel() {
            return label;
        }

        void setLabel(bool newLabel) {
            label = newLabel;
        }

        void setDepth(int newDepth) {
            depth = newDepth;
        }

        int getDepth() {
            return depth;
        }

        int getDegree() {
            return edges_.size();
        }

        int getEdgeLabel(int index) {
            return edges_[index].second;
        }

        void setEdgeLabel(int index, int newLabel) {
            edges_[index].second = newLabel;
        }

        string getEdgeTarget(int index) {
            return edges_[index].first->source_;
        }

        void setPred(Vertex* PRED) {
            pred = PRED;
        }

        Vertex* getPred() {
            return pred;
        }
    private:
        string source_;
        vector<pair<Vertex*, int> > edges_; //0 unexplored, 1 discovery, 2 cross
        unsigned int visits_;
        bool label; //0 unexplored, 1 visited
        int depth;
        Vertex* pred;
    };

    /**
    * Reads data from .tsv file and creates a graph.
    * Lines should have the following structure: source target target target target ...
    * @param tsv file that includes subreddit data
    */
    void readFromTSV(string fileName);

    /**
    * runPageRank
    * @param steps --> Number of steps to take (the more the higher the accuracy)
    * @param factor --> Factor to mulitply the popularities by
    */
    void runPageRank(unsigned int steps, float dampening = 0.85f, float factor = 1.0f);

    /**
    * printResults
    * @param upperRange
    * @param lowerRange
    */
    void printResults(unsigned int upperRange = 0, unsigned int lowerRange = 1);

    bool printRank(std::string subreddit);

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
    void insertEdge(string source, string target);

    vector<Vertex*> BFS();
    void BFS_V(Vertex*, vector<Vertex*>&);

    unsigned int getSize() {
        return vertices_.size();
    }

    vector<pair<string, float> > getPopularities();
    int getSubComponents() {return subComponents;}
private:

    /**
     * private functions
    */

    /**
     * private variables
    */
    int subComponents;
    unordered_map<string, pair<Vertex*, float> > vertices_;
};

/**
 * Helper function for sorting vector of pairs by second element
 * @param a
 * @param b
 * @return the expression a > b
 */
bool sortbysec(const pair<string,float> &a, const pair<string,float> &b);