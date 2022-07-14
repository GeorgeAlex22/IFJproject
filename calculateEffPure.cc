#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <iostream>
using namespace std;
// #include "defaultBetheBloch.h"
#include <TGraph.h>
#include <TFile.h>

int main()
{
    TFile f("OutData_ArScCharged150T2_cb34_noDeuterons.root");
    TFile g("efficiency_purity.root", "RECREATE");
    TH2D *chisq_0 = (TH2D *)f.Get("chisq_0");
    TH2D *h_efficiency = (TH2D *)chisq_0->Clone("h_efficiency");
    h_efficiency->Reset();
    TH2D *h_purity = (TH2D *)chisq_0->Clone("h_purity");
    h_purity->Reset();
    int nbinsptot = chisq_0->GetNbinsX();
    int nbinspt = chisq_0->GetNbinsY();
    int iBinX, iBinY, iv_0;
    double v0;
    double TP;
    double FN;
    double FP;
    double eff, pur;
    for (iBinX = 1; iBinX < nbinsptot; iBinX++)
    {
        v0 = chisq_0->GetXaxis()->GetBinCenter(iBinX);
        for (iBinY = 1; iBinY < nbinspt; iBinY++)
        {
            char hname[255];
            TH1D *hmodel[5];
            TP = 0;
            FN = 0;
            FP = 0;
            cout << "----------------------------------------------------" << endl;
            for (unsigned int ip = 0; ip < 5; ip++)
            {
                sprintf(hname, "dist_model_0_1_%d_%d_%d", ip, iBinX, iBinY);
                hmodel[ip] = (TH1D *)f.Get(hname);
                iv_0 = hmodel[ip]->FindFixBin(v0);
                if (ip == 3)
                {
                    TP = hmodel[3]->Integral(1, iv_0);
                    FN = hmodel[3]->Integral(iv_0, hmodel[3]->GetNbinsX());
                    cout << "nbins = " << hmodel[3]->GetNbinsX() << endl;
                    cout << "iv_0 = " << iv_0 << endl;
                }
                else
                {
                    FP += hmodel[ip]->Integral(1, iv_0);
                }
            }
            eff = TP / (TP + FN);
            pur = TP / (TP + FP);
            cout << "TP = " << TP << " FN = " << FN << " FP = " << FP << endl;
            cout << "eff = " << eff << " pur = " << pur << endl;
            h_efficiency->SetBinContent(iBinX, iBinY, eff);
            h_purity->SetBinContent(iBinX, iBinY, pur);
        }
    }
    g.Write();
    g.Close();
}