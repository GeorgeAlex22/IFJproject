#define tracks_filtered_cxx
#include "tracks_filtered.h"
#include "defaultBetheBloch.h"
#include <TH2.h>
#include <TH3.h>
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

   if (Debug)
   {
      nentries = 10000;
      // nentries = 2265;
   }

   TFile facc("ArSc150-acc-map.root");
   TFile *f = new TFile("histogramsFiltered.root", "RECREATE");

   TH3C *h_acc = (TH3C *)facc.Get("acc");

   TH2D *h_dEdxVSp_pos_acc = new TH2D("h_dEdxVSp_pos_acc", "p vs dE/dx", 100, -0.5, 2.3, 100, 0.5, 2);

   TH1D *h_px = new TH1D("h_px", "p_x", 100, -1.5, 1.5);
   TH1D *h_py = new TH1D("h_py", "p_y", 100, -1.5, 1.5);
   TH1D *h_pt = new TH1D("h_pt", "p_{T}", 100, 0, 3);
   TH1D *h_yCM = new TH1D("h_yCM", "y_{CM}", 100, -0.75, 0.75);
   TH1D *h_np = new TH1D("h_np", "N_p", 25, -0.5, 24.5);

   TH2D *h_pxpy = new TH2D("h_pxpy", "p_x vs p_y", 100, -1.5, 1.5, 100, -1.5, 1.5);
   TH2D *h_ptyCM = new TH2D("h_ptyCM", "p_{T} vs y_{CM}", 100, 0, 3, 100, -0.75, 0.75);

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
   bool sameEvent;

   int tmp_Run_number;
   int tmp_Event_id;

   int Nprotons = 0;

   Long64_t nbytes = 0, nb = 0;

   for (Long64_t jentry = 0; jentry < nentries; jentry++)
   {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0)
         break;
      nb = fChain->GetEntry(jentry);
      nbytes += nb;
      // if (Cut(ientry) < 0) continue;

      p = sqrt(px * px + py * py + pz * pz);
      E = sqrt(p * p + m_nucleon * m_nucleon);
      rapidity = 0.5 * log((E + pz) / (E - pz));
      rapidityCM = rapidity - beam_rapidity;

      pt = sqrt(px * px + py * py);

      isAccepted = (bool)h_acc->GetBinContent(h_acc->FindFixBin(rapidityCM, px, py));

      if (!isAccepted)
         continue;

      h_dEdxVSp_pos_acc->Fill(log10(p), dEdx);
      h_px->Fill(px);
      h_py->Fill(py);
      h_pt->Fill(pt);
      h_yCM->Fill(rapidityCM);
      h_pxpy->Fill(px, py);
      h_ptyCM->Fill(pt, rapidityCM);

      Nprotons++;

      // Update tmp_Run_number and tmp_Event_id
      tmp_Run_number = Run_number;
      tmp_Event_id = Event_id;

      // Check if the next event is the same as this
      nb = fChain->GetEntry(jentry + 1);
      sameEvent = (tmp_Run_number == Run_number) && (tmp_Event_id == Event_id);
      // nb = fChain->GetEntry(jentry);
      if (!sameEvent)
      {
         h_np->Fill(Nprotons);

         Nprotons = 0;
      }
   }

   // Handle the last event for Nprotons
   h_np->Fill(Nprotons);

   f->cd();
   h_dEdxVSp_pos_acc->Write();
   h_px->Write();
   h_py->Write();
   h_pt->Write();
   h_yCM->Write();
   h_np->Write();
   h_pxpy->Write();
   h_ptyCM->Write();
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

   tracks_filtered t(chain);

   if (argc > 3)
   {
      t.Debug = true;
   }

   t.outputFileName = argv[1];
   t.Loop();

   std::cout << "[ DONE ]\n\n";
}