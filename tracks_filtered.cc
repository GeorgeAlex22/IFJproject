#define tracks_filtered_cxx
#include "tracks_filtered.h"
#include "defaultBetheBloch.h"
#include <TH2.h>
#include <TGraph.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <iostream>
using namespace std;

void tracks_filtered::Loop()
{
   //   In a ROOT session, you can do:
   //      root> .L tracks_filtered.C
   //      root> tracks_filtered t
   //      root> t.GetEntry(12); // Fill t data members with entry number 12
   //      root> t.Show();       // Show values of entry 12
   //      root> t.Show(16);     // Read and show values of entry 16
   //      root> t.Loop();       // Loop on all entries
   //

   //     This is the loop skeleton where:
   //    jentry is the global entry number in the chain
   //    ientry is the entry number in the current Tree
   //  Note that the argument to GetEntry must be:
   //    jentry for TChain::GetEntry
   //    ientry for TTree::GetEntry and TBranch::GetEntry
   //
   //       To read only selected branches, Insert statements like:
   // METHOD1:
   //    fChain->SetBranchStatus("*",0);  // disable all branches
   //    fChain->SetBranchStatus("branchname",1);  // activate branchname
   // METHOD2: replace line
   //    fChain->GetEntry(jentry);       //read all branches
   // by  b_branchname->GetEntry(ientry); //read only this branch
   if (fChain == 0)
      return;

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry = 0; jentry < nentries; jentry++)
   {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0)
         break;
      nb = fChain->GetEntry(jentry);
      nbytes += nb;
      // if (Cut(ientry) < 0) continue;
   }
}

int main(int argc, char **argv)
{

   if (argc < 3)
   {
      std::cout << "Usage:\n\t" << argv[0] << " output.root input1.root [input2.root input3.root ...]\n\n";
      return 1;
   }

   std::cout << "Output: " << argv[1] << "\n";
   // TChain is like a TTree, but can work across several root files
   TChain *chain = new TChain("tracks_tree");
   std::cout << "Inputs:\n";
   for (int i = 2; i < argc; i++)
   {
      std::cout << "\t" << argv[i] << "\n";
      chain->Add(argv[i]);
   }

   tracks_filtered t(chain);

   // if (argc > 3)
   // {
   //    t.Debug = true;
   // }

   t.outputFileName = argv[1];
   t.Loop();

   std::cout << "[ DONE ]\n\n";
}