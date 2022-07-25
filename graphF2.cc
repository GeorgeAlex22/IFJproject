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
#include <fstream>
using namespace std;

void Loop(char *outputFileName, char *inputFileName, bool Debug)
{
    int num = 0;
    double M2values[150];
    double F2[150];
    double nanan[150];
    double F2_boot[150];
    double sigma_F2[150];

    int M_min = 1;
    int M_max = 150;
    int M;

    double Mvalues[150];
    for (M = M_min - 1; M < M_max; M++)
    {
        Mvalues[M] = M;
        // M2values[M] = M * M;
    }

    ifstream inputFile;
    inputFile.open(inputFileName);
    if (inputFile.fail())
    {
        cout << "Error opening input file" << endl;
        return;
    }
    else
    {
        while (!inputFile.eof())
        {
            if (num >= 5)
            {
                if (num > 154)
                    break;
                inputFile >> M2values[num - 5] >> F2[num - 5] >> sigma_F2[num - 5];
                if (!Debug)
                    continue;

                cout << "Line = " << num + 1 << endl;
                cout << "M2= " << M2values[num - 5] << " F2= " << F2[num - 5] << " sigma_F2= " << sigma_F2[num - 5] << endl;
            }
            num++;
        }
    }
    inputFile.close();

    // Define output file
    TFile f(outputFileName, "RECREATE");

    TGraph g_F2(M_max, Mvalues, F2);
    g_F2.SetTitle("F2");
    g_F2.SetName("g_F2");

    TGraph g_sigma_F2(M_max, Mvalues, sigma_F2);
    g_sigma_F2.SetTitle("sigma_F2");
    g_sigma_F2.SetName("g_sigma_F2");

    TGraphErrors g_F2_errors(M_max, Mvalues, F2, 0, sigma_F2);
    g_F2_errors.SetTitle("F2_errors");
    g_F2_errors.SetName("g_F2_errors");

    TGraph g_F2_M2(M_max, M2values, F2);
    g_F2_M2.SetTitle("F2 vs M2");
    g_F2_M2.SetName("g_F2_M2");

    TGraph g_sigma_F2_M2(M_max, M2values, sigma_F2);
    g_sigma_F2_M2.SetTitle("sigma_F2 vs M2");
    g_sigma_F2_M2.SetName("g_sigma_F2_M2");

    TGraphErrors g_F2_errors_M2(M_max, M2values, F2, 0, sigma_F2);
    g_F2_errors_M2.SetTitle("F2_errors vs M2");
    g_F2_errors_M2.SetName("g_F2_errors_M2");

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
        std::cout << "Usage:\n\t" << argv[0] << " output.root input.dat [-d] \n\n";
        return 1;
    }

    bool Debug = false;

    std::cout << "Output: " << argv[1] << "\n";
    // TChain is like a TTree, but can work across several root files
    // TChain chain("event_tree");
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
        // chain.Add(argv[M]);
    }

    Loop(argv[1], argv[2], Debug);

    std::cout << "[ DONE ]\n\n";
}
