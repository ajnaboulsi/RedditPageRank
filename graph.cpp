#include "graph.h"

/**
 * Reads in the TSV file and sets up the data as a graph. This graph is used for our pagerank algorithm.
 *
 * @param fileName Name of the file that is being read from
 * @return 
 */
void Graph::readFromTSV(string fileName) {
    size_t pos = 0;
    bool isSource;
    string token, line, source;
    string delimiter = "\t";
    ifstream file;
    file.open(fileName);
    if (file.is_open()) {
        while(getline(file, line)) {
            pos = 0;
            isSource = true;
            while(pos != std::string::npos) {
                pos = line.find(delimiter);
                token = line.substr(0, pos);
                if (isSource) {
                    source = token;
                    insertVertex(source);
                    isSource = false;
                }
                else
                    insertEdge(source, token);
                line.erase(0, pos + delimiter.length());
            }
        }
    }
}


/**
 * Calculates a metric for the difference between two pixels, used to
 * calculate if a pixel is within a tolerance.
 *
 * @param steps number of iterations to run the pagerank algorithm
 * @param dampening decimal indicating how much the probability is of picking a neighboring node
 * @param factor the factor to multiply the probabilities by
 * @return the difference between two HSLAPixels
 */
void Graph::runPageRank(unsigned int steps, float dampening, float factor) {
    // TODO: finish PageRank algorithm

    // put keys in vector
    vector<string> keys;
    keys.reserve(vertices_.size());
    for (auto kv : vertices_) {
        keys.push_back(kv.first);
    }

    // web surfing
    float r;
    string current;
    for (unsigned int step = 0; step < steps; ++step) {
        r = (float)rand() / (float)RAND_MAX;
        if (r < dampening && step != 0) {
            current = vertices_[current].first->randEdge()->getsource();
            vertices_[current].first->getVisits() += 1;
        }
        else {
            current = keys[rand() % keys.size()];
            vertices_[current].first->getVisits() += 1;
        }
    }

    // calculate popularities
    for (auto k : keys) {
        vertices_[k].second = factor * (float)vertices_[k].first->getVisits() / (float)steps;
    }

}



/**
 * Prints out the subreddits names and popularities for a certain range of popularity ranks.
 *
 * @param upperRange the start of the range of popularities that you want to print
 * @param lowerRange the end of the range of popularities that you want to print
 * @return 
 */
void Graph::printResults(unsigned int upperRange, unsigned int lowerRange) {

    // store sources/popularities in vector and sort by popularity
    vector<pair<string, float> > results;
    results.reserve(vertices_.size());
    for (auto kv : vertices_) {
        results.push_back({kv.first, kv.second.second});
    }

    sort(results.begin(), results.end(), sortbysec);

    // print values to std::cout
    cout << "\033[1;37m\n";
    cout << "Popularities\n" << endl;
    cout << "\033[0m";
    for (unsigned int i = upperRange; i < lowerRange; ++i) {
        cout << setw(5) << left << i + 1 << "\033[0;36m" << setw(20) << results[i].first << "\033[0m" << setw(12) << right << showbase << setprecision(5) << fixed << results[i].second << " %" << endl;
    }
    cout << "\033[0m\n";
}


/**
 * Prints out the rank of a subreddit, also has a wildcard feature.
 *
 * @param subreddit the subreddit keyword that you are looking for the rank of
 * @return 
 */
bool Graph::printRank(std::string subreddit){
    vector<pair<string, float> > results;
    results.reserve(vertices_.size());
    for (auto kv : vertices_) {
        results.push_back({kv.first, kv.second.second});
    }

    sort(results.begin(), results.end(), sortbysec);


    //list all ...subreddit...
    if (subreddit[0] == '*' && subreddit[subreddit.size()-1] == '*'){ 
        std::string substring = subreddit.substr(1, subreddit.size() - 2);
        for (unsigned int i = 0; i < vertices_.size(); i++){

            if ((results[i].first).find(substring) != std::string::npos){
                std::cout << i + 1 << ". " << results[i].first;
                std::cout << std::endl;
            }
        }
        return 1;
    }

    //list all ...subreddit
    else if (subreddit[0] == '*'){ 
        std::string substring = subreddit.substr(1, subreddit.size());
        for (unsigned int i = 0; i < vertices_.size(); i++){
            if ((results[i].first).size() >= substring.size()){
                if (((results[i].first).substr((results[i].first).size() - substring.size(), (results[i].first).size())).find(substring) != std::string::npos){
                    std::cout << i + 1 << ". " << results[i].first;
                    std::cout << std::endl;
                }
            } 
        }
    }

    //list all subreddit...
    else if (subreddit[subreddit.size()-1] == '*'){
        std::string substring = subreddit.substr(0, subreddit.size() - 1);
        for (unsigned int i = 0; i < vertices_.size(); i++){
            if ((results[i].first).size() >= substring.size()){
                if (((results[i].first).substr(0, substring.size())).find(substring) != std::string::npos){
                    std::cout << i + 1 << ". " << results[i].first;
                    std::cout << std::endl;
                }
            }
        }
    }

    //list subreddit
    else{
        for (unsigned int i = 0; i < vertices_.size(); i++){
            if (subreddit == results[i].first){
                std::cout << i + 1 << ". " << subreddit;
                std::cout << std::endl;
                return 1;
            }
        }
        std::cout << "subreddit not found!" << std::endl;
        return 0;
    }
    
    std::cout << std::endl;
    return 1;
}


/**
 * Helper for the sort function that allows us to sort using the second element in the pair.
 *
 * @param a the first pair of (string, float) to be compared
 * @param b the second pair of (string, float) to be compared
 * @return a boolean value that checks if a is larger than b
 */
bool sortbysec(const pair<string,float> &a, const pair<string,float> &b) {
    return (a.second > b.second);
}

/**
 * Inserts a subreddit vertex.
 *
 * @param source the subreddit that is being added as a vertex
 * @return 
 */
void Graph::insertVertex(string source) {
    vertices_[source] = {new Vertex(source), 0.0};
}

/**
 * Inserts an edge between two subreddit vertices.
 *
 * @param source the subreddit that is the starting point for the edge
 * @param target the subreddit that is the ending point for the edge
 * @return 
 */
void Graph::insertEdge(string source, string target) {
    // target does not exist
    if (vertices_.find(target) == vertices_.end())
        insertVertex(target);
    vertices_[source].first->insertEdge(vertices_[target].first);
}

/**
 * BFS function to traverse the graph structure.
 *
 * @param
 * @return a vector of pointers to subreddits that have been traversed
 */
std::vector<Graph::Vertex*> Graph::BFS() {
    subComponents=0;
    vector<Graph::Vertex*> bfs;
    for (auto kv : vertices_)  {
        if (!kv.second.first->getLabel()) {
            BFS_V(kv.second.first, bfs);
            subComponents++;
        }
    }
    return bfs;
}

vector<pair<string, float> > Graph::getPopularities() {
    vector<pair<string, float> > V;
    for (auto kv : vertices_)  {
        V.push_back({kv.first, kv.second.second});
    }
    return V;
}

/**
 * Helper function for BFS.
 *
 * @param v starting vertex to start the traversal on
 * @param V a vector of vertex pointers storing the order of the traversal
 * @return 
 */
void Graph::BFS_V(Graph::Vertex* v, vector<Graph::Vertex*>& V) {
    Vertex* vertex;
    std::queue<Vertex*> q;
    v->setLabel(1);
    q.push(v);

    while (!q.empty()) {
        vertex = q.front();
        V.push_back(vertex);
        q.pop();
        for (int i = 0; i<vertex->getDegree(); ++i) {
            if (vertices_.find(vertex->getEdgeTarget(i))->second.first->getLabel() == 0) {
                vertex->setEdgeLabel(i, 1);
                vertices_.find(vertex->getEdgeTarget(i))->second.first->setLabel(1);
                q.push(vertices_.find(vertex->getEdgeTarget(i))->second.first);
                vertices_.find(vertex->getEdgeTarget(i))->second.first->setPred(vertex);
                vertices_.find(vertex->getEdgeTarget(i))->second.first->setDepth(vertex->getDepth()+1);
            }
            else if (vertex->getEdgeLabel(i) == 0) {
                vertex->setEdgeLabel(i, 2);
            }
        }
    }
}