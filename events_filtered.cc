#include "Event.h"
#include "defaultBetheBloch.h"
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TH2.h>
#include <TH3.h>
#include <TGraph.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <iostream>
using namespace std;

void Loop(TChain &fChain, char *outputFileName, bool Debug, int first_cBin, int last_cBin, bool mc)
{
    // Define output file
    TFile f(outputFileName, "RECREATE");

    /* Initialize chain */
    fChain.SetBranchStatus("*", 1); // select all branches
    EventClass::Event *pevent = nullptr;
    fChain.SetBranchAddress("Event", &pevent);

    // clone tree structure
    TTree *tree_accepted = (TTree *)fChain.CloneTree(0);

    Long64_t nentries = fChain.GetEntries();

    if (Debug)
    {
        nentries = 10000;
        // nentries = 2265;
    }

    TFile facc("ArSc150-acc-map.root");

    TH3C *h_acc = (TH3C *)facc.Get("acc");

    TH2D h_dEdxVSp_pos_acc("h_dEdxVSp_pos_acc", "p vs dE/dx", 100, -0.5, 2.3, 100, 0.5, 2);

    TH1D h_px("h_px", "p_x", 100, -1.5, 1.5);
    TH1D h_py("h_py", "p_y", 100, -1.5, 1.5);
    TH1D h_pt("h_pt", "p_{T}", 100, 0, 3);
    TH1D h_yCM("h_yCM", "y_{CM}", 100, -0.75, 0.75);
    TH1D h_np("h_np", "N_p", 25, -0.5, 24.5);

    TH2D h_pxpy("h_pxpy", "p_x vs p_y", 100, -1.5, 1.5, 100, -1.5, 1.5);
    TH2D h_ptyCM("h_ptyCM", "p_{T} vs y_{CM}", 100, 0, 3, 100, -0.75, 0.75);

    double p;

    const double Ecm = 16.84 / 2;   // GeV
    const double m_nucleon = 0.939; // GeV
    // const double beam_rapidity = TMath::ACosH(Ecm / (m_nucleon));
    const double beam_rapidity = acosh(Ecm / (m_nucleon));

    double rapidity;
    double rapidityCM;

    double E;
    double pt;

    double dEdx_BBp;
    double dEdx_BBk;

    bool isAccepted;
    bool isPositive;
    bool sameEvent;

    int tmp_Run_number;
    int tmp_Event_id;

    Long64_t nbytes = 0, nb = 0;

    for (Long64_t jentry = 0; jentry < nentries; jentry++)
    {
        fChain.GetEntry(jentry);
        if (!(pevent->cBin >= first_cBin && pevent->cBin <= last_cBin))
            continue;
        // loop over tracks, filling newTracks
        std::vector<EventClass::Track> newTracks;
        for (const auto &t : pevent->tracks)
        {

            p = sqrt(t.px * t.px + t.py * t.py + t.pz * t.pz);
            E = sqrt(p * p + m_nucleon * m_nucleon);
            rapidity = 0.5 * log((E + t.pz) / (E - t.pz));
            rapidityCM = rapidity - beam_rapidity;

            pt = sqrt(t.px * t.px + t.py * t.py);

            isAccepted = (bool)h_acc->GetBinContent(h_acc->FindFixBin(rapidityCM, t.px, t.py));

            isPositive = t.dEdx > 0;
            if (mc)
            {
                isPositive = true;
            }

            // double check in case of mc
            if (!(abs(t.px) <= 1.5 && abs(t.py) <= 1.5)) // && abs(rapidityCM) <= 0.75))
            {
                // cout << "out of range" << endl;
                continue;
            }

            if (!(isAccepted && isPositive))
                continue;

            h_dEdxVSp_pos_acc.Fill(log10(p), t.dEdx);
            h_px.Fill(t.px);
            h_py.Fill(t.py);
            h_pt.Fill(pt);
            h_yCM.Fill(rapidityCM);
            h_pxpy.Fill(t.px, t.py);
            h_ptyCM.Fill(pt, rapidityCM);

            // we passed all cuts, fill newTracks
            newTracks.push_back(t);
        } // end of tracks loop

        h_np.Fill(newTracks.size());
        // point event->tracks to new tracks
        pevent->tracks = newTracks;

        // fill new event to tree_filtered
        tree_accepted->Fill();

    } // end of events loop

    facc.Close();
    f.cd();
    tree_accepted->Write();
    h_dEdxVSp_pos_acc.Write();
    h_px.Write();
    h_py.Write();
    h_pt.Write();
    h_yCM.Write();
    h_np.Write();
    h_pxpy.Write();
    h_ptyCM.Write();
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
    bool mc = false;
    int first_cBin = 0;
    int last_cBin = 5;

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
        if (!strncmp(argv[i], "-1", 2))
        { // check if we have
            first_cBin = 1;
            last_cBin = 2;
            std::cout << "Selected cBins = 1,2" << endl;
            continue;
        }
        if (!strncmp(argv[i], "-2", 2))
        { // check if we have
            first_cBin = 3;
            last_cBin = 4;
            std::cout << "Selected cBins = 3,4" << endl;
            continue;
        }
        if (!strncmp(argv[i], "-mc", 3))
        {
            mc = true;
            std::cout << "running on CMC events" << endl;
            continue;
        }

        std::cout << "\t" << argv[i] << "\n";
        chain.Add(argv[i]);
    }

    Loop(chain, argv[1], Debug, first_cBin, last_cBin, mc);

    std::cout << "[ DONE ]\n\n";
}
