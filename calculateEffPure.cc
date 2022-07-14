#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <iostream>
using namespace std;
#include "defaultBetheBloch.h"
using namespace Dedx;
#include <TGraph.h>
#include <TFile.h>

int main()
{
    TFile f("OutData_ArScCharged150T2_cb34_noDeuterons.root");
    TFile g("efficiency_purity.root", "RECREATE");

    TH2D *chisq_0 = (TH2D *)f.Get("chisq_0");
    TH2D *h_efficiency = (TH2D *)chisq_0->Clone("h_efficiency");
    TH2D *h_purity = (TH2D *)chisq_0->Clone("h_purity");

    h_efficiency->Reset();
    h_purity->Reset();

    int nbinsptot = chisq_0->GetNbinsX();
    int nbinspt = chisq_0->GetNbinsY();

    int iBinX, iBinY, iv_0;

    double v0;
    double ptot_0;

    double dEdx_BBk, dEdx_BBp;
    double x = 0.15;

    double TP;
    double FN;
    double FP;

    double eff, pur;

    for (iBinX = 1; iBinX <= nbinsptot; iBinX++)
    {
        ptot_0 = chisq_0->GetXaxis()->GetBinCenter(iBinX);

        dEdx_BBk = defaultBetheBloch(4, ptot_0);
        dEdx_BBp = defaultBetheBloch(3, ptot_0);

        v0 = log10(dEdx_BBp + x * (dEdx_BBk - dEdx_BBp));

        for (iBinY = 1; iBinY <= nbinspt; iBinY++)
        {
            if (chisq_0->GetBinContent(iBinX, iBinY) != 0)
            {

                // cout << "----------------------------------------------------" << endl;
                // cout << "v0 = " << v0 << endl;
                // cout << "iBinX = " << iBinX << " iBinY = " << iBinY << endl;

                char hname[255];
                TH1D *hmodel[5];

                TP = 0;
                FN = 0;
                FP = 0;

                for (unsigned int ip = 0; ip < 5; ip++)
                {
                    sprintf(hname, "dist_model_0_1_%d_%d_%d", ip, iBinX - 1, iBinY - 1);
                    // cout << hname << endl;

                    hmodel[ip] = (TH1D *)f.Get(hname);
                    // cout << "reading successfull" << endl;

                    iv_0 = hmodel[ip]->FindFixBin(v0);
                    // cout << "find fix bin successfull" << endl;

                    if (ip == 3)
                    {
                        TP = hmodel[ip]->Integral(1, iv_0);
                        // cout << "TP successfull" << endl;
                        FN = hmodel[ip]->Integral(iv_0, hmodel[ip]->GetNbinsX());
                        // cout << "FN successfull" << endl;

                        // cout << "nbins = " << hmodel[3]->GetNbinsX() << endl;
                    }
                    else
                    {
                        FP += hmodel[ip]->Integral(1, iv_0);
                        // cout << "FP increment" << ip << "successfull" << endl;
                    }
                }
                if ((TP + FN) != 0)
                {
                    eff = TP / (TP + FN);
                    // cout << "efficiency calclation successfull" << endl;
                    h_efficiency->SetBinContent(iBinX, iBinY, eff);
                    // cout << "efficiency set bin content successfull" << endl;
                }
                if ((TP + FP) != 0)
                {
                    pur = TP / (TP + FP);
                    // cout << "purity calclation successfull" << endl;
                    h_purity->SetBinContent(iBinX, iBinY, pur);
                    // cout << "purity set bin content successfull" << endl;
                }
                // cout << "TP = " << TP << " FN = " << FN << " FP = " << FP << endl;
                // cout << "eff = " << eff << endl;
                cout << pur << endl;
                // h_efficiency->SetBinContent(iBinX, iBinY, eff);
                // h_purity->SetBinContent(iBinX, iBinY, pur);
            }
        }
    }
    g.Write();
    g.Close();
}