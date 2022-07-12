//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Mon Jul 11 11:33:35 2022 by ROOT version 6.26/04
// from TTree tracks_tree/./ArSc150_charged_tree.root
// found on file: ArSc150_charged_tree.root
//////////////////////////////////////////////////////////

#ifndef tracks_tree_h
#define tracks_tree_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.

class tracks_tree
{
public:
   TTree *fChain;  //! pointer to the analyzed TTree or TChain
   Int_t fCurrent; //! current Tree number in a TChain

   // Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   UInt_t Run_number;
   UInt_t Event_id;
   UInt_t cBin;
   UInt_t nTracksFit;
   UInt_t nTracksAll;
   Float_t VertexZ;
   Float_t energySpectatorModules;
   Float_t energyAllPSDModules;
   Float_t bx;
   Float_t by;
   Float_t NPratio;
   UInt_t clustersVTPC1;
   UInt_t clustersVTPC2;
   UInt_t clustersGTPC;
   UInt_t clustersdEdx;
   UInt_t clustersPotentialAll;
   UInt_t clustersAll;
   Float_t px;
   Float_t py;
   Float_t pz;
   Float_t dEdx;
   Float_t probElectron;
   Float_t probPion;
   Float_t probKaon;
   Float_t probProton;
   Float_t probDeuteron;

   // List of branches
   TBranch *b_Run_number;             //!
   TBranch *b_Event_id;               //!
   TBranch *b_cBin;                   //!
   TBranch *b_nTracksFit;             //!
   TBranch *b_nTracksAll;             //!
   TBranch *b_VertexZ;                //!
   TBranch *b_energySpectatorModules; //!
   TBranch *b_energyAllPSDModules;    //!
   TBranch *b_bx;                     //!
   TBranch *b_by;                     //!
   TBranch *b_NPratio;                //!
   TBranch *b_clustersVTPC1;          //!
   TBranch *b_clustersVTPC2;          //!
   TBranch *b_clustersGTPC;           //!
   TBranch *b_clustersdEdx;           //!
   TBranch *b_clustersPotentialAll;   //!
   TBranch *b_clustersAll;            //!
   TBranch *b_px;                     //!
   TBranch *b_py;                     //!
   TBranch *b_pz;                     //!
   TBranch *b_dEdx;                   //!
   TBranch *b_probElectron;           //!
   TBranch *b_probPion;               //!
   TBranch *b_probKaon;               //!
   TBranch *b_probProton;             //!
   TBranch *b_probDeuteron;           //!

   tracks_tree(TTree *tree = 0);
   virtual ~tracks_tree();
   virtual Int_t Cut(Long64_t entry);
   virtual Int_t GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void Init(TTree *tree);
   virtual void Loop();
   virtual Bool_t Notify();
   virtual void Show(Long64_t entry = -1);

   std::string outputFileName;
   bool Debug = false;
};

#endif

#ifdef tracks_tree_cxx
tracks_tree::tracks_tree(TTree *tree) : fChain(0)
{
   // if parameter tree is not specified (or zero), connect the file
   // used to generate this class and read the Tree.
   if (tree == 0)
   {
      TFile *f = (TFile *)gROOT->GetListOfFiles()->FindObject("ArSc150_charged_tree.root");
      if (!f || !f->IsOpen())
      {
         f = new TFile("ArSc150_charged_tree.root");
      }
      f->GetObject("tracks_tree", tree);
   }
   Init(tree);
}

tracks_tree::~tracks_tree()
{
   if (!fChain)
      return;
   delete fChain->GetCurrentFile();
}

Int_t tracks_tree::GetEntry(Long64_t entry)
{
   // Read contents of entry.
   if (!fChain)
      return 0;
   return fChain->GetEntry(entry);
}
Long64_t tracks_tree::LoadTree(Long64_t entry)
{
   // Set the environment to read one entry
   if (!fChain)
      return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0)
      return centry;
   if (fChain->GetTreeNumber() != fCurrent)
   {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void tracks_tree::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree)
      return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("Run_number", &Run_number, &b_Run_number);
   fChain->SetBranchAddress("Event_id", &Event_id, &b_Event_id);
   fChain->SetBranchAddress("cBin", &cBin, &b_cBin);
   fChain->SetBranchAddress("nTracksFit", &nTracksFit, &b_nTracksFit);
   fChain->SetBranchAddress("nTracksAll", &nTracksAll, &b_nTracksAll);
   fChain->SetBranchAddress("VertexZ", &VertexZ, &b_VertexZ);
   fChain->SetBranchAddress("energySpectatorModules", &energySpectatorModules, &b_energySpectatorModules);
   fChain->SetBranchAddress("energyAllPSDModules", &energyAllPSDModules, &b_energyAllPSDModules);
   fChain->SetBranchAddress("bx", &bx, &b_bx);
   fChain->SetBranchAddress("by", &by, &b_by);
   fChain->SetBranchAddress("NPratio", &NPratio, &b_NPratio);
   fChain->SetBranchAddress("clustersVTPC1", &clustersVTPC1, &b_clustersVTPC1);
   fChain->SetBranchAddress("clustersVTPC2", &clustersVTPC2, &b_clustersVTPC2);
   fChain->SetBranchAddress("clustersGTPC", &clustersGTPC, &b_clustersGTPC);
   fChain->SetBranchAddress("clustersdEdx", &clustersdEdx, &b_clustersdEdx);
   fChain->SetBranchAddress("clustersPotentialAll", &clustersPotentialAll, &b_clustersPotentialAll);
   fChain->SetBranchAddress("clustersAll", &clustersAll, &b_clustersAll);
   fChain->SetBranchAddress("px", &px, &b_px);
   fChain->SetBranchAddress("py", &py, &b_py);
   fChain->SetBranchAddress("pz", &pz, &b_pz);
   fChain->SetBranchAddress("dEdx", &dEdx, &b_dEdx);
   fChain->SetBranchAddress("probElectron", &probElectron, &b_probElectron);
   fChain->SetBranchAddress("probPion", &probPion, &b_probPion);
   fChain->SetBranchAddress("probKaon", &probKaon, &b_probKaon);
   fChain->SetBranchAddress("probProton", &probProton, &b_probProton);
   fChain->SetBranchAddress("probDeuteron", &probDeuteron, &b_probDeuteron);
   Notify();
}

Bool_t tracks_tree::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void tracks_tree::Show(Long64_t entry)
{
   // Print contents of entry.
   // If entry is not specified, print current entry
   if (!fChain)
      return;
   fChain->Show(entry);
}
Int_t tracks_tree::Cut(Long64_t entry)
{
   // This function may be called from Loop.
   // returns  1 if entry is accepted.
   // returns -1 otherwise.
   return 1;
}
#endif // #ifdef tracks_tree_cxx
