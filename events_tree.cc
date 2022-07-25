#include "Event.h"
#include "defaultBetheBloch.h"
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TH2.h>
#include <TGraph.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <iostream>
using namespace std;

void Loop(TChain &fChain, char *outputFileName, bool Debug, double probProton_cut)
{
    // Define output file
    TFile f(outputFileName, "RECREATE");

    /* Initialize chain */
    fChain.SetBranchStatus("*", 1); // select all branches
    EventClass::Event *pevent = nullptr;
    fChain.SetBranchAddress("Event", &pevent);

    // clone tree structure
    TTree *tree_filtered = (TTree *)fChain.CloneTree(0);

    Long64_t nentries = fChain.GetEntries();
    if (Debug)
    {
        nentries = 10000;
        // nentries = 2265;
    }

    // Define histograms
    TH1D h_vz_before("h_vz_before", "VertexZ", 100, -700, -450);
    TH1D h_vz_after("h_vz_after", "VertexZ", 100, -590, -570);

    TH1D h_NPratio_before("h_NPratio_before", "NPratio", 100, 0, 2.1);
    TH1D h_NPratio_after("h_NPratio_after", "NPratio", 30, 0.5, 1.1);

    TH2D h_bxby_before("h_bxby_before", "bx vs by", 100, -11, 11, 100, -11, 11);
    TH2D h_bxby_after("h_bxby_after", "bx vs by", 100, -4, 4, 100, -2, 2);

    TH2D h_dEdxVSp_pos_before("h_dEdxVSp_pos_before", "p vs dE/dx", 100, -0.5, 2.3, 100, 0.5, 2);
    TH2D h_dEdxVSp_neg_before("h_dEdxVSp_neg_before", "p vs dE/dx", 100, -0.5, 2.3, 100, 0.5, 2);

    TH2D h_dEdxVSp_pos_after("h_dEdxVSp_pos_after", "p vs dE/dx", 100, -0.5, 2.3, 100, 0.5, 2);
    TH2D h_dEdxVSp_neg_after("h_dEdxVSp_neg_after", "p vs dE/dx", 100, -0.5, 2.3, 100, 0.5, 2);

    TH2D h_dEdxVSp_pos_final("h_dEdxVSp_pos_final", "p vs dE/dx", 100, -0.5, 2.3, 100, 0.5, 2);
    TH2D h_dEdxVSp_neg_final("h_dEdxVSp_neg_final", "p vs dE/dx", 100, -0.5, 2.3, 100, 0.5, 2);

    TH2D h_pxpy_before("h_pxpy_before", "px vs py", 100, 0, 0, 100, 0, 0);
    TH2D h_pxpy_after("h_pxpy_after", "px vs py", 100, -1.5, 1.5, 100, -1.5, 1.5);

    TH1D h_rapidityCM_before("h_rapidityCM_before", "yCM", 100, 0, 0);
    TH1D h_rapidityCM_after("h_rapidityCM_after", "yCM", 100, -0.5, 0.5);

    const double Ecm = 16.84 / 2;   // GeV
    const double m_nucleon = 0.939; // GeV
    const double beam_rapidity = acosh(Ecm / (m_nucleon));

    // Loop over events in tree
    for (Long64_t jentry = 0; jentry < nentries; jentry++)
    {
        fChain.GetEntry(jentry);

        // apply event cuts
        h_vz_before.Fill(pevent->VertexZ);

        bool vertex_cut = pevent->VertexZ < -570 && pevent->VertexZ > -590;

        if (!vertex_cut)
            continue;

        h_vz_after.Fill(pevent->VertexZ);

        // loop over tracks, filling newTracks
        std::vector<EventClass::Track> newTracks;
        for (const auto &t : pevent->tracks)
        {
            // fill before histograms
            h_NPratio_before.Fill(t.NPratio);
            h_bxby_before.Fill(t.bx, t.by);

            bool npratio_cut = t.NPratio > 0.5 && t.NPratio < 1.1;
            bool bxby_cut = t.bx > -4 && t.bx < 4 && t.by > -2 && t.by < 2;

            if (!(npratio_cut && bxby_cut))
                continue;

            h_NPratio_after.Fill(t.NPratio);
            h_bxby_after.Fill(t.bx, t.by);

            // dE/dx
            double p = sqrt(t.px * t.px + t.py * t.py + t.pz * t.pz);
            double dEdx_BBp = Dedx::defaultBetheBloch(3, p);
            double dEdx_BBk = Dedx::defaultBetheBloch(2, p);

            if (t.dEdx > 0)
            {
                h_dEdxVSp_pos_before.Fill(log10(p), t.dEdx);
            }
            else
            {
                h_dEdxVSp_neg_before.Fill(log10(p), -t.dEdx);
            }

            if (!(log10(p) >= 0.6 && log10(p) <= 2.1))
                continue;
            if (!(abs(t.dEdx) >= 0.5 && abs(t.dEdx) <= dEdx_BBp + 0.15 * (dEdx_BBk - dEdx_BBp)))
                continue;

            if (t.dEdx > 0)
            {
                h_dEdxVSp_pos_after.Fill(log10(p), t.dEdx);
            }
            else
            {
                h_dEdxVSp_neg_after.Fill(log10(p), -t.dEdx);
            }

            h_pxpy_before.Fill(t.px, t.py);

            // Calculate nucleon energy
            double E = sqrt(p * p + m_nucleon * m_nucleon);
            // Calculate rapidity at the center of mass
            double rapidity = 0.5 * log((E + t.pz) / (E - t.pz));
            double rapidityCM = rapidity - beam_rapidity;
            h_rapidityCM_before.Fill(rapidityCM);
            // Apply momentum cuts
            if (!(abs(t.px) <= 1.5 && abs(t.py) <= 1.5 && abs(rapidityCM) <= 0.75))
                continue;

            h_pxpy_after.Fill(t.px, t.py);
            h_rapidityCM_after.Fill(rapidityCM);

            if (t.dEdx > 0)
            {
                h_dEdxVSp_pos_final.Fill(log10(p), t.dEdx);
            }
            else
            {
                h_dEdxVSp_neg_final.Fill(log10(p), -t.dEdx);
            }

            if (t.probProton < probProton_cut)
                continue;

            // we passed all cuts, fill newTracks
            newTracks.push_back(t);
        } // end of tracks loop

        // point event->tracks to new tracks
        pevent->tracks = newTracks;

        // fill new event to tree_filtered
        tree_filtered->Fill();

    } // end of events loop

    // write to file
    f.cd();
    tree_filtered->Write();
    h_vz_before.Write();
    h_vz_after.Write();
    h_NPratio_before.Write();
    h_NPratio_after.Write();
    h_bxby_before.Write();
    h_bxby_after.Write();
    h_dEdxVSp_pos_before.Write();
    h_dEdxVSp_neg_before.Write();
    h_dEdxVSp_pos_after.Write();
    h_dEdxVSp_neg_after.Write();
    h_pxpy_before.Write();
    h_pxpy_after.Write();
    h_rapidityCM_before.Write();
    h_rapidityCM_after.Write();
    h_dEdxVSp_pos_final.Write();
    h_dEdxVSp_neg_final.Write();
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
    double probProton_cut = 0;

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

        if (!strncmp(argv[i], "-80", 3))
        { // check if we have

            probProton_cut = 0.8;

            std::cout << "Selected probProton >= " << probProton_cut << endl;
            continue;
        }
        if (!strncmp(argv[i], "-90", 3))
        { // check if we have

            probProton_cut = 0.9;

            std::cout << "Selected probProton >= " << probProton_cut << endl;
            continue;
        }
        if (!strncmp(argv[i], "-95", 3))
        { // check if we have

            probProton_cut = 0.95;

            std::cout << "Selected probProton >= " << probProton_cut << endl;
            continue;
        }

        std::cout << "\t" << argv[i] << "\n";
        chain.Add(argv[i]);
    }
    Loop(chain, argv[1], Debug, probProton_cut);

    std::cout << "[ DONE ]\n\n";
}
