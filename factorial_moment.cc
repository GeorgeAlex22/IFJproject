#include "Event.h"
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TGraphErrors.h>
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TMath.h>
#include <iostream>
using namespace std;

void pointpairs(double &mean, double &pairs, std::vector<EventClass::Track> &tracks, int M)
{
    TH2D h2("h2", "h2", M, -1.5, 1.5, M, -1.5, 1.5);
    mean = 0.;
    pairs = 0.;
    for (unsigned int i = 0; i < tracks.size(); i++)
    {
        int bin = h2.FindFixBin(tracks[i].px, tracks[i].py);
        int nbin;
        if (abs(tracks[i].px) < 1.5 && abs(tracks[i].py) < 1.5)
            nbin = h2.GetBinContent(bin);

        mean += 1;
        pairs += 2 * nbin;

        h2.Fill(tracks[i].px, tracks[i].py);
    }

    // for (unsigned int nbx = 1; nbx <= M; nbx++)
    // {
    //     for (unsigned int nby = 1; nby <= M; nby++)
    //     {
    //         double n_i = h2.GetBinContent(nbx, nby);
    //         mean += n_i;
    //         pairs += n_i * (n_i - 1.);
    //     }
    // }

    mean /= (double)(M * M);
    pairs /= (double)(M * M);
}

void Loop(TChain &fChain, char *outputFileName, bool Debug)
{
    // Define output file
    TFile f(outputFileName, "RECREATE");

    /* Initialize chain */
    fChain.SetBranchStatus("*", 1); // select all branches
    EventClass::Event *pevent = nullptr;
    fChain.SetBranchAddress("Event", &pevent);

    // clone tree structure
    // TTree *tree = (TTree *)fChain.CloneTree(0);

    Long64_t nentries = fChain.GetEntries();

    if (Debug)

    {
        nentries = 100;
        // nentries = 2265;
    }

    const int M_min = 1;
    const int M_max = 150;

    // TH1D h_F2("h_F2", "F2", M_max - M_min + 1, M_min - 0.5, M_max + 0.5);
    // TH1D h_sigma_F2("h_sigma_F2", "sigma_F2", M_max - M_min + 1, M_min - 0.5, M_max + 0.5);

    double event_mean[M_max];
    double event_pairs[M_max];
    double event_sigma_mean[M_max];
    double event_sigma_pairs[M_max];
    double F2[M_max];
    double sigma_F2[M_max];
    double Mvalues[M_max];
    double M2values[M_max];

    for (int M = M_min; M <= M_max; M++)
    {
        event_mean[M - 1] = 0.;
        event_pairs[M - 1] = 0.;
        event_sigma_mean[M - 1] = 0.;
        event_sigma_pairs[M - 1] = 0.;
        F2[M - 1] = 0.;
        sigma_F2[M - 1] = 0.;
        Mvalues[M - 1] = M;
        M2values[M - 1] = M * M;
    }

    for (Long64_t jentry = 0; jentry < nentries; jentry++)
    {
        fChain.GetEntry(jentry);
        if (jentry % 100 == 0)
        {
            std::cout << "Processing event " << jentry << std::endl;
        }

        for (int M = M_min; M <= M_max; M++)
        {
            double mean, pairs;
            std::vector<EventClass::Track> tracks = pevent->tracks;
            pointpairs(mean, pairs, tracks, M);

            event_mean[M - 1] += mean;
            event_pairs[M - 1] += pairs;
            event_sigma_mean[M - 1] += mean * mean;
            event_sigma_pairs[M - 1] += pairs * pairs;
        }
    }

    for (int M = M_min; M <= M_max; M++)
    {

        event_mean[M - 1] /= (double)nentries;
        event_pairs[M - 1] /= (double)nentries;

        event_sigma_mean[M - 1] /= (double)nentries;
        event_sigma_pairs[M - 1] /= (double)nentries;
        event_sigma_mean[M - 1] -= event_mean[M - 1] * event_mean[M - 1];
        event_sigma_pairs[M - 1] -= event_pairs[M - 1] * event_pairs[M - 1];

        double tmpF2 = event_pairs[M - 1] / (event_mean[M - 1] * event_mean[M - 1]);
        F2[M - 1] = tmpF2;

        double sigma_F2tmp = tmpF2 * sqrt(pow(event_sigma_mean[M - 1] / event_mean[M - 1], 2) + pow(2 * event_sigma_pairs[M - 1] / event_pairs[M - 1], 2));
        sigma_F2[M - 1] = sigma_F2tmp;
    }

    TGraph g_F2(M_max, Mvalues, F2);
    g_F2.SetTitle("F2");

    TGraph g_sigma_F2(M_max, Mvalues, sigma_F2);
    g_sigma_F2.SetTitle("sigma_F2");

    TGraphErrors g_F2_errors(M_max, Mvalues, F2, 0, sigma_F2);
    g_F2_errors.SetTitle("F2_errors");

    TGraph g_F2_M2(M_max, M2values, F2);
    g_F2_M2.SetTitle("F2 vs M2");

    TGraph g_sigma_F2_M2(M_max, M2values, sigma_F2);
    g_sigma_F2_M2.SetTitle("sigma_F2 vs M2");

    TGraphErrors g_F2_errors_M2(M_max, M2values, F2, 0, sigma_F2);
    g_F2_errors_M2.SetTitle("F2_errors vs M2");

    f.cd();
    g_F2.Write();
    g_sigma_F2.Write();
    g_F2_errors.Write();
    g_F2_M2.Write();
    g_sigma_F2_M2.Write();
    g_F2_errors_M2.Write();
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
    for (int M = 2; M < argc; M++)
    {
        if (!strncmp(argv[M], "-d", 2))
        {                 // check if we have
            Debug = true; // debug flag
            std::cout << "Debug mode on" << endl;
            continue;
        }

        std::cout << "\t" << argv[M] << "\n";
        chain.Add(argv[M]);
    }

    Loop(chain, argv[1], Debug);

    std::cout << "[ DONE ]\n\n";
}
