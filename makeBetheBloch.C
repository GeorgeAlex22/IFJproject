#include "defaultBetheBloch.h"
#include <TChain.h>
#include <TFile.h>
#include <TGraph.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <iostream>
using namespace std;

void makeBetheBloch()
{
    TFile *f = new TFile("bethebloch.root", "RECREATE");

    TGraph *bethebloch_e = new TGraph();
    bethebloch_e->SetName("bethebloch_e");
    TGraph *bethebloch_pion = new TGraph();
    bethebloch_pion->SetName("bethebloch_pion");
    TGraph *bethebloch_k = new TGraph();
    bethebloch_k->SetName("bethebloch_k");
    TGraph *bethebloch_p = new TGraph();
    bethebloch_p->SetName("bethebloch_p");
    TGraph *bethebloch_d = new TGraph();
    bethebloch_d->SetName("bethebloch_d");

    double log10_p_min = -0.5;
    double log10_p_max = 2.0;

    for (double log10_p = log10_p_min; log10_p <= log10_p_max; log10_p += 0.01)
    {
        bethebloch_e->SetPoint(bethebloch_e->GetN(), log10_p, Dedx::defaultBetheBloch(0, pow(10, log10_p)));
        bethebloch_pion->SetPoint(bethebloch_pion->GetN(), log10_p, Dedx::defaultBetheBloch(1, pow(10, log10_p)));
        bethebloch_k->SetPoint(bethebloch_k->GetN(), log10_p, Dedx::defaultBetheBloch(2, pow(10, log10_p)));
        bethebloch_p->SetPoint(bethebloch_p->GetN(), log10_p, Dedx::defaultBetheBloch(3, pow(10, log10_p)));
        bethebloch_d->SetPoint(bethebloch_d->GetN(), log10_p, Dedx::defaultBetheBloch(4, pow(10, log10_p)));
        // cout << "Added momentum p = " << pow(10, log10_p) << endl;
    }

    bethebloch_e->Write();
    bethebloch_pion->Write();
    bethebloch_k->Write();
    bethebloch_p->Write();
    bethebloch_d->Write();
    f->Close();
}

int main(int argc, char **argv)
{

    makeBetheBloch();

    std::cout << "[ DONE ]\n\n";
}