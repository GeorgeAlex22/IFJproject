#include "Event.h"
#include "EllipseCut.h"
#include "defaultBetheBloch.h"
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TH2.h>
#include <TH3.h>
#include <TGraph.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TMath.h>
#include <TRandom3.h>
#include <iostream>
using namespace std;

void Loop(TChain &fChain, char *outputFileName, bool Debug)
{
    // Define output file
    TFile f(outputFileName, "RECREATE");

    /* Initialize chain */
    fChain.SetBranchStatus("*", 1); // select all branches
    EventClass::Event *pevent = nullptr;
    fChain.SetBranchAddress("Event", &pevent);

    // clone tree structure
    TTree *tree_mTTD = (TTree *)fChain.CloneTree(0);

    Long64_t nentries = fChain.GetEntries();

    if (Debug)
    {
        nentries = 10000;
        // nentries = 2265;
    }

    TH2D h_dsxdsy_before("h_dsxdsy_before", "Dsx vs Dsy", 100, 0, 0, 100, 0, 0);
    TH2D h_dsxdrho_before("h_dsxdrho_before", "Drho vs Dsx", 100, 0, 0, 100, 0, 0);
    TH2D h_dsydrho_before("h_dsydrho_before", "Dsy vs rho", 100, 0, 0, 100, 0, 0);

    TH2D h_dsxdsy_discarded("h_dsxdsy_discarded", "Dsx vs Dsy", 100, 0, 0, 100, 0, 0);
    TH2D h_dsxdrho_discarded("h_dsxdrho_discarded", "Drho vs Dsx", 100, 0, 0, 100, 0, 0);
    TH2D h_dsydrho_discarded("h_dsydrho_discarded", "Dsy vs rho", 100, 0, 0, 100, 0, 0);

    TH2D h_dsxdsy_after("h_dsxdsy_after", "Dsx vs Dsy", 100, 0, 0, 100, 0, 0);
    TH2D h_dsxdrho_after("h_dsxdrho_after", "Drho vs Dsx", 100, 0, 0, 100, 0, 0);
    TH2D h_dsydrho_after("h_dsydrho_after", "Dsy vs rho", 100, 0, 0, 100, 0, 0);

    double sx1, sy1, rho1;
    double sx2, sy2, rho2;
    double Dsx, Dsy, Drho;

    double cut_x = 0.0105;
    double cut_y = 0.0018;
    double cut_r = 0.0080;
    double cut_r2 = 0.02;
    double cut_x2 = 0.0023;
    double alpha = 51;

    bool isInside;

    TRandom3 *rnd = new TRandom3(0);

    for (Long64_t jentry = 0; jentry < nentries; jentry++)
    {
        fChain.GetEntry(jentry);

        std::vector<bool> tracks_mask(pevent->tracks.size(), false);
        // Begin pairs loop
        for (int i = 0; i < (int)pevent->tracks.size() - 1; i++)
        {
            for (int j = i + 1; j < (int)pevent->tracks.size(); j++)
            {
                rho1 = 1 / sqrt(pevent->tracks[i].px * pevent->tracks[i].px + pevent->tracks[i].pz * pevent->tracks[i].pz);
                sx1 = pevent->tracks[i].px * rho1;
                sy1 = pevent->tracks[i].py * rho1;

                rho2 = 1 / sqrt(pevent->tracks[j].px * pevent->tracks[j].px + pevent->tracks[j].pz * pevent->tracks[j].pz);
                sx2 = pevent->tracks[j].px * rho2;
                sy2 = pevent->tracks[j].py * rho2;

                Dsx = sx2 - sx1;
                Dsy = sy2 - sy1;
                Drho = rho2 - rho1;

                h_dsxdsy_before.Fill(Dsx, Dsy);
                h_dsxdrho_before.Fill(Drho, Dsx);
                h_dsydrho_before.Fill(Drho, Dsy);

                isInside = is_inside_ellipse(Dsx, Dsy, 0, 0, cut_x, cut_y, 0) &&
                           is_inside_ellipse(Drho, Dsy, 0, 0, cut_r, cut_y, 0) &&
                           is_inside_ellipse(Drho, Dsx, 0, 0, cut_r2, cut_x2, alpha);

                if (isInside)
                {
                    h_dsxdsy_discarded.Fill(Dsx, Dsy);
                    h_dsxdrho_discarded.Fill(Drho, Dsx);
                    h_dsydrho_discarded.Fill(Drho, Dsx);

                    // Randomly discard track
                    if (rnd->Rndm() > 0.5)
                    {
                        tracks_mask[i] = true;
                    }
                    else
                    {
                        tracks_mask[j] = true;
                    }
                }
                else
                {
                    h_dsxdsy_after.Fill(Dsx, Dsy);
                    h_dsxdrho_after.Fill(Drho, Dsx);
                    h_dsydrho_after.Fill(Drho, Dsy);
                }
            }
        } // end of pairs loop

        // loop over tracks, filling newTracks
        std::vector<EventClass::Track> newTracks;
        // Begin tracks loop for filtering pair members
        for (int i = 0; i < (int)pevent->tracks.size(); i++)
        {
            if (tracks_mask[i])
                continue;

            // we passed all cuts, fill newTracks
            newTracks.push_back(pevent->tracks[i]);
        } // end of tracks loop for filtering pair members

        // point event->tracks to new tracks
        pevent->tracks = newTracks;

        // fill new event to tree_filtered
        tree_mTTD->Fill();

    } // end of events loop

    f.cd();
    h_dsxdsy_before.Write();
    h_dsxdrho_before.Write();
    h_dsydrho_before.Write();
    h_dsxdsy_discarded.Write();
    h_dsxdrho_discarded.Write();
    h_dsydrho_discarded.Write();
    h_dsxdsy_after.Write();
    h_dsxdrho_after.Write();
    h_dsydrho_after.Write();
    tree_mTTD->Write();
    f.Close();
}

int main(int argc, char **argv)
{

    if (argc < 3)
    {
        std::cout << "Usage:\n\t" << argv[0] << " output.root input1.root [input2.root input3.root ...] [-d] \n\n";
        return 1;
    }

    bool Debug = false;

    std::cout << "Output: " << argv[1] << "\n";
    // TChain is like a TTree, but can work across several root files
    TChain chain("event_tree");
    std::cout << "Inputs:\n";
    for (int i = 2; i < argc; i++)
    {
        if (!strncmp(argv[i], "-d", 2))
        {                 // check if we have
            Debug = true; // debug flag
            std::cout << "Debug mode on" << endl;
            continue;
        }

        std::cout << "\t" << argv[i] << "\n";
        chain.Add(argv[i]);
    }

    Loop(chain, argv[1], Debug);

    std::cout << "[ DONE ]\n\n";
}
