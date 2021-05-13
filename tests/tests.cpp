#include "../graph.h"
#include "../springembedder/springembedder.h"
#include "../cs225/PNG.h"
#include "../cs225/Animation.h"
#include "../cs225/catch/catch.hpp"

#include <time.h>
#include <string>
#include <iostream>
#include <map>

using namespace std;

TEST_CASE("test_bfs_size", "[weight=5]") {
    Graph g;
    g.readFromTSV("redditHyperlinksWithoutLengths.tsv");
    unsigned int correct_bfs_size = g.getSize();
    vector<Graph::Vertex*> bfs = g.BFS();

    REQUIRE(bfs.size() == correct_bfs_size);
}

TEST_CASE("test_bfs_duplicates", "[weight=5]") {
    bool duplicates_exist = 0;
    Graph g;
    g.readFromTSV("redditHyperlinksWithoutLengths.tsv");
    vector<Graph::Vertex*> bfs = g.BFS();
    std::map <string, bool> m;
    int index = 0;

    for (auto it : bfs) {
        if (m.count(it->getsource()) == 1) {
            duplicates_exist = 1;
            break;
        }
        else {
            m[it->getsource()] = 0;
        }
    }

    REQUIRE(duplicates_exist == 0);
}

TEST_CASE("test_pagerank_normprob", "[weight=5]") {
    Graph g;
    g.readFromTSV("redditHyperlinksWithoutLengths.tsv");
    g.runPageRank(9876543, 0.85, 100);
    vector<pair<string, float> > popularities = g.getPopularities();
    float sum = 0.0;

    for (auto it : popularities) {
        sum += it.second;
    }

    REQUIRE((int)sum == 100);
}

TEST_CASE("test_printrank_nonexistant", "[weight=5]") {
    Graph g;
    g.readFromTSV("redditHyperlinksWithoutLengths.tsv");
    g.runPageRank(9876543, 0.85, 100);

    cout << "Print rank of \"cs225\": ";
    bool exists = g.printRank("cs225");

    REQUIRE(exists == 0);
}

TEST_CASE("test_printrank_existant", "[weight=5]") {
    Graph g;
    g.readFromTSV("redditHyperlinksWithoutLengths.tsv");
    g.runPageRank(9876543, 0.85, 100);

    cout << "Print rank of \"uiuc\": ";
    bool exists = g.printRank("uiuc");

    REQUIRE(exists == 1);
}
