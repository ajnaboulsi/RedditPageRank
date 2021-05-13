#include "fdgraph.h"


/**
 * Reads in the TSV file and sets up the data as a graph. This graph is used for our spring embedder algorithm.
 *
 * @param fileName Name of the file that is being read from
 * @return 
 */
void ForceDirectedGraph::readFromTSV(string fileName) {
    size_t pos = 0;
    size_t posTemp = 0;
    string line, source, target, length;
    unsigned int len;
    string delimiter = "\t";
    ifstream file;
    file.open(fileName);
    if (file.is_open()) {
        while(getline(file, line)) {
            pos = line.find(delimiter);
            source = line.substr(0, pos);
            posTemp = pos;
            pos = line.find(delimiter, posTemp + 1);
            target = line.substr(posTemp + 1, pos - posTemp - 1);
            posTemp = pos;
            pos = line.find(delimiter, posTemp);
            length = line.substr(posTemp + 1, line.length() - posTemp - 1);
            len = stoul(length);
            insertEdge(source, target, len);
        }
    }
    file.close();

    // put keys in vector
    keys_.reserve(vertices_.size());
    for (auto kv : vertices_) {
        keys_.push_back(kv.first);
    }
}

/**
 * Adds sizes to the graph so that they can be displayed when creating the spring embedder graph.
 *
 * @param sizes a vector of pairs that contain a subreddit and its probability
 * @return 
 */
void ForceDirectedGraph::importSizes(const vector<pair<string, float> > & sizes) {
    for (auto it : sizes) {
        // check if key exists... may want to omit because of time complexity
        if (vertices_.find(it.first) != vertices_.end()) {
            vertices_[it.first]->getSize() = it.second;
        }
    }
}


/**
 * Prints out the graph onto a PNG.
 *
 * @param width the width of the PNG
 * @param height the height of the PNG
 * @return a pointer to the PNG that contains the representation of the graph
 */
cs225::PNG* ForceDirectedGraph::printGraph(unsigned int width, unsigned int height) {
    using namespace cs225;

    PNG* png = new PNG(width + 3, height + 3);
    HSLAPixel black = HSLAPixel(0, 0, 0);

    int xPos, yPos;
    for (auto kv : vertices_) {
        xPos = (int)kv.second->getPosition().first;
        yPos = (int)kv.second->getPosition().second;
        for (int x = -1; x < 2; ++x) {
            for (int y = -1; y < 2; ++y) {
                HSLAPixel& pixel = png->getPixel(xPos + x + 2, yPos + y + 2);
                pixel = black;
            }
        }
    }

    return png;
} 


/**
 * Inserts a subreddit vertex.
 *
 * @param source the subreddit that is being added as a vertex
 * @return 
 */
void ForceDirectedGraph::insertVertex(string source) {
    vertices_[source] = new Vertex(source);
}


/**
 * Inserts a weighted edge between two subreddit vertices.
 *
 * @param source the subreddit that is the starting point for the edge
 * @param target the subreddit that is the ending point for the edge
 * @param length the weight of the edge that is being inserted
 * @return 
 */
void ForceDirectedGraph::insertEdge(string source, string target, unsigned int length) {
    // source does not exist
    if (vertices_.find(source) == vertices_.end())
        insertVertex(source);
    // target does not exist
    if (vertices_.find(target) == vertices_.end())
        insertVertex(target);
    vertices_[source]->insertEdge(vertices_[target], length);
}
