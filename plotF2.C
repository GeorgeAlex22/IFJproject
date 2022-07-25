#include <iostream>
using namespace std;

void plotF2(char *fileName1, char *fileName2, char *outputName)
{

    // bool hasProb = true; // outputName.size() > 4;
    // // parse outputName to find cBins and probProton
    // // format is "F2_cBins_probProton"
    // char *cBinsStr = strtok(outputName, "_");
    // cBinsStr = strtok(NULL, "_");
    // int cBins = atoi(cBinsStr);
    // char *probProtonStr;
    // int probProton;
    // if (hasProb)
    // {
    //     probProtonStr = strtok(NULL, "_pr");
    //     probProtonStr = strtok(NULL, "_");
    //     probProton = atoi(probProtonStr);
    // }

    // cout << "cBinsStr = " << cBinsStr << "probProtonStr = " << probProtonStr << endl;
    // cout << "cBins = " << cBins << " probProton = " << probProton << endl;

    // opening files
    TFile f(fileName1);
    TFile g(fileName2);

    // get Graphs from the files
    TGraphErrors *g_F2_errors1 = (TGraphErrors *)f.Get("g_F2_errors_M2");
    g_F2_errors1->SetTitle("");
    TGraphErrors *g_F2_errors2 = (TGraphErrors *)g.Get("g_F2_errors_M2");
    g_F2_errors2->SetTitle("");
    TGraphErrors *g_F2_diff = new TGraphErrors();

    TCanvas c;
    TLegend legend(0.4, 0.45, 0.6, 0.55);
    legend.SetBorderSize(0);
    // TLegend legend_diff(0.15, 0.15, 0.40, 0.30);
    // legend_diff.SetBorderSize(0);

    legend.AddEntry(g_F2_errors1, "Data", "p");
    legend.AddEntry(g_F2_errors2, "Mixed Events", "p");

    // legend_diff.AddEntry(g_F2_diff, "Data - Mixed Events", "p");

    // g_F2_errors1->SetMarkerSize(10);
    // g_F2_errors2->SetMarkerSize(10);
    // Titles

    g_F2_errors1->GetXaxis()->SetTitle("M^{2}");
    g_F2_errors1->GetYaxis()->SetTitle("F_{2}");
    g_F2_errors2->GetXaxis()->SetTitle("M^{2}");
    g_F2_errors2->GetYaxis()->SetTitle("F_{2}");

    // Markers and marker colors for data
    g_F2_errors1->SetMarkerStyle(8);
    g_F2_errors1->SetMarkerColor(kBlack);

    // Markers and marker colors for mixed events
    g_F2_errors2->SetMarkerStyle(4);
    g_F2_errors2->SetMarkerColor(kRed);

    // Line color for data
    g_F2_errors1->SetLineColor(kBlack);

    // Line color for mixed events
    g_F2_errors2->SetLineColor(kRed);

    char save_loc[100];

    // draw plots
    c.SetLogx();
    g_F2_errors1->Draw("AP");
    g_F2_errors2->Draw("P,SAME");
    legend.Draw();
    sprintf(save_loc, "./plots/F2/%s/F2_M2_log.png", outputName);
    c.SaveAs(save_loc);

    c.Clear();
    c.SetLogy();
    g_F2_errors1->Draw("AP");
    g_F2_errors2->Draw("P,SAME");
    legend.Draw();
    sprintf(save_loc, "./plots/F2/%s/F2_M2_loglog.png", outputName);
    c.SaveAs(save_loc);

    c.Clear();
    c.SetLogx(0);
    c.SetLogy(0);
    g_F2_errors1->Draw("AP");
    g_F2_errors2->Draw("P,SAME");
    legend.Draw();
    sprintf(save_loc, "./plots/F2/%s/F2_M2.png", outputName);
    c.SaveAs(save_loc);

    // calculate difference of graphs
    for (int i = 0; i < g_F2_errors1->GetN(); i++)
    {
        double x1, y1, x2, y2;
        g_F2_errors1->GetPoint(i, x1, y1);
        g_F2_errors2->GetPoint(i, x2, y2);
        double diff = y1 - y2;
        double err1 = g_F2_errors1->GetErrorY(i);
        double err2 = g_F2_errors2->GetErrorY(i);
        double err = sqrt(err1 * err1 + err2 * err2);
        g_F2_diff->SetPoint(i, x1, diff);
        g_F2_diff->SetPointError(i, 0, err);
    }

    // g_F2_errors1->SetMarkerSize(1);
    g_F2_diff->GetXaxis()->SetTitle("M^{2}");
    g_F2_diff->GetYaxis()->SetTitle("#Delta F_{2}");
    g_F2_diff->SetMarkerStyle(7);
    g_F2_diff->SetMarkerColor(kBlack);

    // draw difference of graphs
    c.Clear();
    g_F2_diff->Draw("AP");
    // legend_diff.Draw();

    sprintf(save_loc, "./plots/F2/%s/F2_M2_diff.png", outputName);
    c.SaveAs(save_loc);

    // log x
    c.Clear();
    c.SetLogx();
    g_F2_diff->Draw("AP");
    // legend_diff.Draw();
    sprintf(save_loc, "./plots/F2/%s/F2_M2_diff_log.png", outputName);
    c.SaveAs(save_loc);
}
