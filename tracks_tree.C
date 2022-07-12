#define tracks_tree_cxx
#include "tracks_tree.h"
#include "defaultBetheBloch.h"
#include <TH2.h>
#include <TGraph.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <iostream>
using namespace std;

void tracks_tree::Loop()
{
   //   In a ROOT session, you can do:
   //      root> .L tracks_tree.C
   //      root> tracks_tree t
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
   if (Debug)
   {
      nentries = 100000;
   }

   TFile *f = new TFile("histograms.root", "RECREATE");

   TH1D *h_vz_before = new TH1D("h_vz_before", "VertexZ", 100, -700, -450);
   TH1D *h_vz_after = new TH1D("h_vz_after", "VertexZ", 100, -590, -570);

   TH1D *h_NPratio_before = new TH1D("h_NPratio_before", "NPratio", 100, 0, 2.1);
   TH1D *h_NPratio_after = new TH1D("h_NPratio_after", "NPratio", 30, 0.5, 1.1);

   TH2D *h_bxby_before = new TH2D("h_bxby_before", "bx vs by", 100, -11, 11, 100, -11, 11);
   TH2D *h_bxby_after = new TH2D("h_bxby_after", "bx vs by", 100, -4, 4, 100, -2, 2);

   TH2D *h_dEdxVSp_pos_before = new TH2D("h_dEdxVSp_pos_before", "p vs dE/dx", 100, -0.5, 2.3, 100, 0.5, 2);
   TH2D *h_dEdxVSp_neg_before = new TH2D("h_dEdxVSp_neg_before", "p vs dE/dx", 100, -0.5, 2.3, 100, 0.5, 2);

   TH2D *h_dEdxVSp_pos_after = new TH2D("h_dEdxVSp_pos_after", "p vs dE/dx", 100, -0.5, 2.3, 100, 0.5, 2);
   TH2D *h_dEdxVSp_neg_after = new TH2D("h_dEdxVSp_neg_after", "p vs dE/dx", 100, -0.5, 2.3, 100, 0.5, 2);

   TH2D *h_dEdxVSp_pos_probCut = new TH2D("h_dEdxVSp_pos_probCut", "p vs dE/dx", 100, -0.5, 2.3, 100, 0.5, 2);
   TH2D *h_dEdxVSp_neg_probCut = new TH2D("h_dEdxVSp_neg_probCut", "p vs dE/dx", 100, -0.5, 2.3, 100, 0.5, 2);

   double dEdx_BBp;
   double dEdx_BBk;

   Long64_t nbytes = 0, nb = 0;

   for (Long64_t jentry = 0; jentry < nentries; jentry++)
   {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0)
         break;
      nb = fChain->GetEntry(jentry);
      nbytes += nb;
      // if (Cut(ientry) < 0) continue;

      h_vz_before->Fill(VertexZ);

      bool vertex_cut = VertexZ < -570 && VertexZ > -590;
      bool npratio_cut = NPratio > 0.5 && NPratio < 1.1;
      bool bxby_cut = bx > -4 && bx < 4 && by > -2 && by < 2;
      if (vertex_cut)
      {
         h_vz_after->Fill(VertexZ);
         h_NPratio_before->Fill(NPratio);
         h_bxby_before->Fill(bx, by);

         if (npratio_cut && bxby_cut)
         {
            h_NPratio_after->Fill(NPratio);
            h_bxby_after->Fill(bx, by);
            double p = sqrt(px * px + py * py + pz * pz);
            if (dEdx > 0)
            {
               h_dEdxVSp_pos_before->Fill(log10(p), dEdx);

               dEdx_BBp = Dedx::defaultBetheBloch(3, p);
               dEdx_BBk = Dedx::defaultBetheBloch(2, p);

               if (log10(p) >= 0.6 && log10(p) <= 2.1)
               {
                  if (dEdx >= 0.5 && dEdx <= dEdx_BBp + 0.15 * (dEdx_BBk - dEdx_BBp))
                  {
                     h_dEdxVSp_pos_after->Fill(log10(p), dEdx);
                  }

                  if (probProton >= 0.9)
                  {
                     h_dEdxVSp_pos_probCut->Fill(log10(p), dEdx);
                  }
               }
            }
            if (dEdx < 0)
            {
               h_dEdxVSp_neg_before->Fill(log10(p), -dEdx);
            }
         }
      }
   }

   f->Write();
   f->Close();
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

   tracks_tree t(chain);

   if (argc > 3)
   {
      t.Debug = true;
   }

   t.outputFileName = argv[1];
   t.Loop();

   std::cout << "[ DONE ]\n\n";
}
