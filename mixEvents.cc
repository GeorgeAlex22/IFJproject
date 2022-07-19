#include <iostream>
//
#include <TChain.h>
#include <TFile.h>
#include <TRandom3.h>
//
#include "Event.h"
#include "CutsMap.h"
#include "EventMixer.h"

using namespace std;

void Loop(EventMixer &eventMixer, char *outputFileName)
{
    cout << "Entered Loop()" << endl;
    // Define output file
    TFile f(outputFileName, "RECREATE");
    cout << "Opening output file " << outputFileName << endl;

    // Define mixed event tree
    TTree tree_mixed("event_tree", "event_tree_2022_07_19");
    EventClass::Event *pevent = nullptr;
    tree_mixed.Branch("Event", "EventClass::Event", &pevent);

    /* Set up random event generator */
    auto eventStream = eventMixer.randomStream();
    cout << "Entering event stream loop" << endl;
    // loop and mix events
    for (auto &event : eventStream)
    {
        pevent = &event;
        tree_mixed.Fill();
        cout << "Filled tree with event " << endl;
    }

    // write mixed tree to file
    f.cd();
    tree_mixed.Write();
    f.Close();
}

int main(int argc, char **argv)
{

    if (argc < 4)
    {
        std::cout << "Usage:\n\t" << argv[0] << " config.inp output.root input1.root [input2.root input3.root ...] \n\n";
        return 1;
    }

    std::cout << "Config: " << argv[1] << "\n";
    std::cout << "Output: " << argv[2] << "\n";
    // TChain is like a TTree, but can work across several root files
    TChain chain("event_tree");
    std::cout << "Inputs:\n";
    for (int i = 3; i < argc; i++)
    {
        std::cout << "\t" << argv[i] << "\n";
        chain.Add(argv[i]);
    }

    // Read config file
    cout << "Reading config file..." << endl;
    std::string config_file(argv[1]);
    cout << "Applying cuts map..." << endl;
https: // root.cern/manual/
    CutsMap cutsMap(config_file);
    cout << "Read config file." << endl;

    /* Random number generator & seed */
    TRandom3 rndGen;
    rndGen.SetSeed(2650323802); // fixed seed for RNG
    cout << "Entering loop..." << endl;

    /* Define Event Mixer */
    EventMixer myEventMixer(chain, rndGen, config_file);
    Loop(myEventMixer, argv[2]);

    std::cout << "[ DONE ]\n\n";
}
