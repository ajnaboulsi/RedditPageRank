#include "graph.h"
#include "springembedder/springembedder.h"
#include "cs225/PNG.h"
#include "cs225/Animation.h"
#include <time.h>
#include <string>
#include <iostream>

using namespace cs225;

int main() {
    srand(time(NULL));

    Graph g;
    g.readFromTSV("redditHyperlinksWithoutLengths.tsv");
    cout << "Number of nodes: " << g.getSize() << endl;
    g.runPageRank(9876543, 0.85, 100);
    g.printResults(0, 10);

    vector<Graph::Vertex*> bfs = g.BFS();

    cout <<"Graph #SubComponents = "<<g.getSubComponents()<<"\n";
    int node = 1521;
    Graph::Vertex* tmp = bfs[node];
    cout <<"Starting Node: "<<bfs[0]->getsource()<<"\n\n";
    cout <<"Node "<< node <<": "<<tmp->getsource()<<"\n";
    cout <<"\t--> Depth: "<<tmp->getDepth()<<"\n";
    while (tmp->getPred() != NULL && tmp->getsource() != bfs[0]->getsource()) {
        tmp = tmp->getPred();
        cout <<"\t"<<"--> Predecessor: "<<tmp->getsource()<<"\n";
    }

    int size = 3000;

    // PNG * png;
    // SpringEmbedder SEA;
    // SEA.readFromTSV("redditHyperlinksWithLengths.tsv");
    // SEA.setRandomPositions(size - 3);
    // SEA.findEquilibrium(20);
    // png = SEA.printGraph(size, size);
    // png->writeToFile("test.png");
    // delete png;

    // Animation animation;
    // for (int i = 0; i < 15; ++i) {
    //     SEA.findEquilibrium(1);
    //     png = SEA.printGraph(size, size);
    //     animation.addFrame(*png);
    //     delete png;
    // }
    // animation.write("test.gif");

    return 0;
}