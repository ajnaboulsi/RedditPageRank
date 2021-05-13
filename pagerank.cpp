#include <time.h>
#include <string>
#include <iostream>
#include <sys/stat.h>
#include "graph.h"
#include "springembedder/springembedder.h"
#include "cs225/PNG.h"
#include "cs225/Animation.h"
#include "util/util.h"

using namespace cs225;
using namespace util;
using namespace std;

namespace opts
{
    bool help = false;
}

inline bool fileExists (const std::string& name) {
  struct stat buffer;   
  return (stat (name.c_str(), &buffer) == 0); 
}

int main(int argc, const char** argv) {

    string dataset = "redditHyperlinksWithoutLengths.tsv";
    string steps = "9876543";
    string dampening = "0.85";
    string display = "10";

    OptionsParser optsparse;
    optsparse.addArg(display);
    optsparse.addArg(steps);
    optsparse.addArg(dampening);
    optsparse.addArg(dataset);
    optsparse.addOption("help", opts::help);
    optsparse.addOption("h", opts::help);
    optsparse.parse(argc, argv);

    if (opts::help) {
        cout << "Usage: " << argv[0]
             << " [number to be displayed] [steps to be taken] [dampening factor] [dataset]"
             << endl;
        return 1;
    }

    if (!fileExists(dataset)) {
        cout << "Dataset " << dataset << " does not exist." << endl;
        return 1;
    }

    srand(time(NULL));
    Graph g;
    g.readFromTSV(dataset);
    cout << "\n" << "Number of nodes: " << g.getSize() << endl;
    g.runPageRank(lexical_cast<int>(steps), lexical_cast<float>(dampening), 100);
    g.printResults(0, lexical_cast<int>(display));

    return 0;
}