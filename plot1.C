void plot1()
{

  // opening files
  TFile f("filtered.root");
  TFile g("bethebloch.root");
  TFile facc("accepted.root");
  TFile feff("efficiency_purity.root");
  TFile mttd("mTTD_cut.root");

  // get histograms from the files
  // filtered
  TH1F *h_vz_before = (TH1F *)f.Get("h_vz_before");
  TH1F *h_vz_after = (TH1F *)f.Get("h_vz_after");
  TH1F *h_NPratio_before = (TH1F *)f.Get("h_NPratio_before");
  TH1F *h_NPratio_after = (TH1F *)f.Get("h_NPratio_after");
  TH2F *h_bxby_before = (TH2F *)f.Get("h_bxby_before");
  TH2F *h_bxby_after = (TH2F *)f.Get("h_bxby_after");
  TH2F *h_dEdxVSp_pos_before = (TH2F *)f.Get("h_dEdxVSp_pos_before");
  TH2F *h_dEdxVSp_neg_before = (TH2F *)f.Get("h_dEdxVSp_neg_before");
  TH2F *h_dEdxVSp_pos_after = (TH2F *)f.Get("h_dEdxVSp_pos_after");
  TH2F *h_dEdxVSp_neg_after = (TH2F *)f.Get("h_dEdxVSp_neg_after");
  TH2F *h_dEdxVSp_pos_final = (TH2F *)f.Get("h_dEdxVSp_pos_final");
  TH2F *h_dEdxVSp_neg_final = (TH2F *)f.Get("h_dEdxVSp_neg_final");
  TH2F *h_pxpy_before = (TH2F *)f.Get("h_pxpy_before");
  TH2F *h_pxpy_after = (TH2F *)f.Get("h_pxpy_after");
  TH1F *h_rapidityCM_before = (TH1F *)f.Get("h_rapidityCM_before");
  TH1F *h_rapidityCM_after = (TH1F *)f.Get("h_rapidityCM_after");

  // Bethe Bloch
  TGraph *bethebloch_e = (TGraph *)g.Get("bethebloch_e");
  TGraph *bethebloch_pion = (TGraph *)g.Get("bethebloch_pion");
  TGraph *bethebloch_k = (TGraph *)g.Get("bethebloch_k");
  TGraph *bethebloch_p = (TGraph *)g.Get("bethebloch_p");
  // TGraph *bethebloch_d = (TGraph *)g.Get("bethebloch_d");

  // accepted
  TH2F *h_dEdxVSp_pos_acc = (TH2F *)facc.Get("h_dEdxVSp_pos_acc");
  TH2F *h_pxpy = (TH2F *)facc.Get("h_pxpy");
  TH2F *h_ptyCM = (TH2F *)facc.Get("h_ptyCM");
  TH1F *h_px = (TH1F *)facc.Get("h_px");
  TH1F *h_py = (TH1F *)facc.Get("h_py");
  TH1F *h_pt = (TH1F *)facc.Get("h_pt");
  TH1F *h_yCM = (TH1F *)facc.Get("h_yCM");
  TH1F *h_np = (TH1F *)facc.Get("h_np");

  // efficiency purity
  TH2F *h_efficiency = (TH2F *)feff.Get("h_efficiency");
  TH2F *h_purity = (TH2F *)feff.Get("h_purity");

  // mTTD cuts
  TH2F *h_dsxdsy_before = (TH2F *)mttd.Get("h_dsxdsy_before");
  TH2F *h_dsxdrho_before = (TH2F *)mttd.Get("h_dsxdrho_before");
  TH2F *h_dsydrho_before = (TH2F *)mttd.Get("h_dsydrho_before");

  TH2F *h_dsxdsy_discarded = (TH2F *)mttd.Get("h_dsxdsy_discarded");
  TH2F *h_dsxdrho_discarded = (TH2F *)mttd.Get("h_dsxdrho_discarded");
  TH2F *h_dsydrho_discarded = (TH2F *)mttd.Get("h_dsydrho_discarded");

  TH2F *h_dsxdsy_after = (TH2F *)mttd.Get("h_dsxdsy_after");
  TH2F *h_dsxdrho_after = (TH2F *)mttd.Get("h_dsxdrho_after");
  TH2F *h_dsydrho_after = (TH2F *)mttd.Get("h_dsydrho_after");

  // h_vz_before
  h_vz_before->GetXaxis()->SetTitle("VertexZ [cm]");
  h_vz_before->GetXaxis()->SetTitleSize(0.05);
  h_vz_before->GetYaxis()->SetTitle("nTracks");
  h_vz_before->GetYaxis()->SetTitleSize(0.05);

  // h_vz_after
  h_vz_after->GetXaxis()->SetTitle("VertexZ [cm]");
  h_vz_after->GetYaxis()->SetTitle("nTracks");

  // h_NPratio_before
  h_NPratio_before->GetXaxis()->SetTitle("NPratio");
  h_NPratio_before->GetXaxis()->SetTitleSize(0.05);
  h_NPratio_before->GetYaxis()->SetTitle("nTracks");
  h_NPratio_before->GetYaxis()->SetTitleSize(0.05);

  // h_NPratio_after
  h_NPratio_after->GetXaxis()->SetTitle("NPratio");
  h_NPratio_after->GetYaxis()->SetTitle("nTracks");

  // h_bxby_before
  h_bxby_before->GetXaxis()->SetTitle("bx [cm]");
  h_bxby_before->GetXaxis()->SetTitleSize(0.05);
  h_bxby_before->GetYaxis()->SetTitle("by [cm]");
  h_bxby_before->GetYaxis()->SetTitleSize(0.05);

  // h_bxby_after
  h_bxby_after->GetXaxis()->SetTitle("bx [cm]");
  h_bxby_after->GetYaxis()->SetTitle("by [cm]");

  // h_dEdxVSp_pos_before
  h_dEdxVSp_pos_before->GetXaxis()->SetTitle("log_{10}(p)");
  h_dEdxVSp_pos_before->GetXaxis()->SetTitleSize(0.045);
  h_dEdxVSp_pos_before->GetYaxis()->SetTitle("dE/dx)");
  h_dEdxVSp_pos_before->GetYaxis()->SetTitleSize(0.045);

  // h_dEdxVSp_neg_before
  h_dEdxVSp_neg_before->GetYaxis()->SetTitle("log_{10}(p)");
  h_dEdxVSp_neg_before->GetXaxis()->SetTitle("dE/dx");

  // h_dEdxVSp_pos_after
  h_dEdxVSp_pos_after->GetXaxis()->SetTitle("log_{10}(p)");
  h_dEdxVSp_pos_after->GetXaxis()->SetTitleSize(0.045);
  h_dEdxVSp_pos_after->GetYaxis()->SetTitle("dE/dx");
  h_dEdxVSp_pos_after->GetYaxis()->SetTitleSize(0.045);

  // h_dEdxVSp_neg_after
  h_dEdxVSp_neg_after->GetYaxis()->SetTitle("log_{10}(p)");
  h_dEdxVSp_neg_after->GetXaxis()->SetTitle("dE/dx");

  // h_dEdxVSp_pos_final
  h_dEdxVSp_pos_final->GetXaxis()->SetTitle("log_{10}(p)");
  h_dEdxVSp_pos_final->GetXaxis()->SetTitleSize(0.045);
  h_dEdxVSp_pos_final->GetYaxis()->SetTitle("dE/dx");
  h_dEdxVSp_pos_final->GetYaxis()->SetTitleSize(0.045);

  // h_dEdxVSp_neg_final
  h_dEdxVSp_neg_final->GetYaxis()->SetTitle("log_{10}(p)");
  h_dEdxVSp_neg_final->GetXaxis()->SetTitle("dE/dx");

  // h_pxpy_before
  h_pxpy_before->GetXaxis()->SetTitle("px");
  h_pxpy_before->GetYaxis()->SetTitle("py");

  // h_pxpy_after
  h_pxpy_after->GetXaxis()->SetTitle("px");
  h_pxpy_after->GetYaxis()->SetTitle("py");

  // h_rapidityCM_before
  h_rapidityCM_before->GetXaxis()->SetTitle("rapidityCM");
  h_rapidityCM_before->GetYaxis()->SetTitle("nTracks");

  // h_rapidityCM_after
  h_rapidityCM_after->GetXaxis()->SetTitle("rapidityCM");
  h_rapidityCM_after->GetYaxis()->SetTitle("nTracks");

  // h_dEdxVSp_pos_acc
  h_dEdxVSp_pos_acc->GetXaxis()->SetTitle("log_{10}(p)");
  h_dEdxVSp_pos_acc->GetXaxis()->SetTitleSize(0.045);
  h_dEdxVSp_pos_acc->GetYaxis()->SetTitle("dE/dx");
  h_dEdxVSp_pos_acc->GetYaxis()->SetTitleSize(0.045);

  // h_pxpy
  h_pxpy->GetXaxis()->SetTitle("px");
  h_pxpy->GetYaxis()->SetTitle("py");

  // h_ptyCM
  h_ptyCM->GetXaxis()->SetTitle("pt");
  h_ptyCM->GetYaxis()->SetTitle("rapidityCM");

  // h_px
  h_px->GetXaxis()->SetTitle("px");
  h_px->GetYaxis()->SetTitle("nTracks");

  // h_py
  h_py->GetXaxis()->SetTitle("py");
  h_py->GetYaxis()->SetTitle("nTracks");

  // h_pt
  h_pt->GetXaxis()->SetTitle("pt");
  h_pt->GetYaxis()->SetTitle("nTracks");

  // h_yCM
  h_yCM->GetXaxis()->SetTitle("rapidityCM");
  h_yCM->GetYaxis()->SetTitle("nTracks");

  // h_np
  h_np->GetXaxis()->SetTitle("Np");
  h_np->GetYaxis()->SetTitle("nTracks");

  // h_efficiency
  h_efficiency->GetXaxis()->SetTitle("ptot");
  h_efficiency->GetYaxis()->SetTitle("pt");

  // h_purity
  h_purity->GetXaxis()->SetTitle("ptot");
  h_purity->GetYaxis()->SetTitle("pt");

  // h_dsxdsy_before
  h_dsxdsy_before->GetXaxis()->SetTitle("dsx");
  h_dsxdsy_before->GetYaxis()->SetTitle("dsy");

  // h_dsxdrho_before
  h_dsxdrho_before->GetXaxis()->SetTitle("dsx");
  h_dsxdrho_before->GetYaxis()->SetTitle("dsrho");

  // h_dsydrho_before
  h_dsydrho_before->GetXaxis()->SetTitle("dsy");
  h_dsydrho_before->GetYaxis()->SetTitle("dsrho");

  // h_dsxdsy_discarded
  h_dsxdsy_discarded->GetXaxis()->SetTitle("dsx");
  h_dsxdsy_discarded->GetXaxis()->SetTitleSize(0.045);
  h_dsxdsy_discarded->GetYaxis()->SetTitle("dsy");
  h_dsxdsy_discarded->GetYaxis()->SetTitleSize(0.045);
  h_dsxdsy_discarded->GetYaxis()->SetMaxDigits(3);

  // h_dsxdrho_discarded
  h_dsxdrho_discarded->GetXaxis()->SetTitle("dsx");
  h_dsxdrho_discarded->GetXaxis()->SetTitleSize(0.045);
  h_dsxdrho_discarded->GetYaxis()->SetTitle("dsrho");
  h_dsxdrho_discarded->GetYaxis()->SetTitleSize(0.045);
  h_dsxdrho_discarded->GetYaxis()->SetMaxDigits(3);
  h_dsxdrho_discarded->SetTitle("dsx vs drho");

  // h_dsydrho_discarded
  h_dsydrho_discarded->GetXaxis()->SetTitle("dsy");
  h_dsydrho_discarded->GetXaxis()->SetTitleSize(0.045);
  h_dsydrho_discarded->GetYaxis()->SetTitle("dsrho");
  h_dsydrho_discarded->GetYaxis()->SetTitleSize(0.045);
  h_dsydrho_discarded->GetYaxis()->SetMaxDigits(3);

  // h_dsxdsy_after
  h_dsxdsy_after->GetXaxis()->SetTitle("dsx");
  h_dsxdsy_after->GetYaxis()->SetTitle("dsy");

  // h_dsxdrho_after
  h_dsxdrho_after->GetXaxis()->SetTitle("dsx");
  h_dsxdrho_after->GetYaxis()->SetTitle("dsrho");

  // h_dsydrho_after
  h_dsydrho_after->GetXaxis()->SetTitle("dsy");
  h_dsydrho_after->GetYaxis()->SetTitle("dsrho");

  // Remove stats box
  h_vz_before->SetStats(0);
  h_vz_after->SetStats(0);
  h_NPratio_before->SetStats(0);
  h_NPratio_after->SetStats(0);
  h_bxby_before->SetStats(0);
  h_bxby_after->SetStats(0);
  h_dEdxVSp_pos_before->SetStats(0);
  h_dEdxVSp_neg_before->SetStats(0);
  h_dEdxVSp_pos_after->SetStats(0);
  h_dEdxVSp_neg_after->SetStats(0);
  h_dEdxVSp_pos_final->SetStats(0);
  h_dEdxVSp_neg_final->SetStats(0);
  h_pxpy_before->SetStats(0);
  h_pxpy_after->SetStats(0);
  h_rapidityCM_before->SetStats(0);
  h_rapidityCM_after->SetStats(0);
  h_dEdxVSp_pos_acc->SetStats(0);
  h_px->SetStats(0);
  h_py->SetStats(0);
  h_pt->SetStats(0);
  h_yCM->SetStats(0);
  h_np->SetStats(0);
  h_efficiency->SetStats(0);
  h_purity->SetStats(0);
  h_pxpy->SetStats(0);
  h_ptyCM->SetStats(0);
  h_dsxdsy_before->SetStats(0);
  h_dsxdrho_before->SetStats(0);
  h_dsydrho_before->SetStats(0);
  h_dsxdsy_discarded->SetStats(0);
  h_dsxdrho_discarded->SetStats(0);
  h_dsydrho_discarded->SetStats(0);
  h_dsxdsy_after->SetStats(0);
  h_dsxdrho_after->SetStats(0);
  h_dsydrho_after->SetStats(0);

  // Color Bethe Bloch
  bethebloch_e->SetLineColor(kRed);
  bethebloch_pion->SetLineColor(kGreen);
  bethebloch_k->SetLineColor(kViolet);
  bethebloch_p->SetLineColor(kBlack);

  // Legends
  auto legend_bethe_bloch = new TLegend(0.7, 0.12, 0.88, 0.35);
  legend_bethe_bloch->AddEntry(bethebloch_e, "Electron", "l");
  legend_bethe_bloch->AddEntry(bethebloch_pion, "Pion", "l");
  legend_bethe_bloch->AddEntry(bethebloch_k, "Kaon", "l");
  legend_bethe_bloch->AddEntry(bethebloch_p, "Proton", "l");

  TCanvas c;
  // c.SaveAs("plots.png["); // opening pdf

  // draw all histograms
  c.SetLogy();
  h_vz_before->Draw("hist");

  TLine *l_left = new TLine(h_vz_after->GetXaxis()->GetXmin(), 0, h_vz_after->GetXaxis()->GetXmin(), h_vz_before->GetMaximum());
  l_left->SetLineColor(kRed);
  l_left->SetLineStyle(9);
  l_left->Draw();

  TLine *l_right = new TLine(h_vz_after->GetXaxis()->GetXmax(), 0, h_vz_after->GetXaxis()->GetXmax(), h_vz_before->GetMaximum());
  l_right->SetLineColor(kRed);
  l_right->SetLineStyle(9);
  l_right->Draw();

  TLatex *pvz = new TLatex();
  pvz->SetTextSize(0.045);
  pvz->DrawLatexNDC(0.11, 0.7, "Cut:-570 #leq VertexZ #leq -590");

  h_vz_before->SetTitle("");

  // TLatex *nvz= new TLatex();
  // nvz->SetTextSize(0.025);
  // nvz->SetTextFont(82);
  // char entriesvz[25];
  // int entries= h_vz_before->GetEntries();
  // sprintf(entriesvz, "Entries: %d",entries);
  // cout << entriesvz << endl;
  // char hello[15] = "hello";
  // nvz->DrawLatex(0.8, 0.8, hello);

  // c.SaveAs("plots.png");
  c.SaveAs("./plots/h_vz_before.png"); // plot

  // next plot
  c.Clear();
  h_vz_after->Draw("hist");
  // c.SaveAs("plots.png");
  c.SaveAs("./plots/h_vz_after.png");

  // next plot
  c.Clear();
  h_NPratio_before->Draw("hist");

  l_left = new TLine(h_NPratio_after->GetXaxis()->GetXmin(), 0, h_NPratio_after->GetXaxis()->GetXmin(), h_NPratio_before->GetMaximum());
  l_left->SetLineColor(kRed);
  l_left->SetLineStyle(9);
  l_left->Draw();

  l_right = new TLine(h_NPratio_after->GetXaxis()->GetXmax(), 0, h_NPratio_after->GetXaxis()->GetXmax(), h_NPratio_before->GetMaximum());
  l_right->SetLineColor(kRed);
  l_right->SetLineStyle(9);
  l_right->Draw();

  TLatex *pNPratio = new TLatex();
  pNPratio->SetTextSize(0.045);
  pNPratio->DrawLatexNDC(0.115, 0.865, "Cut: 0.5 #leq NPratio #leq 1.1");

  h_NPratio_before->SetTitle("");

  // c.SaveAs("plots.png");
  c.SaveAs("./plots/h_NPratio_before.png");

  // next plot
  c.Clear();
  h_NPratio_after->Draw("hist");
  // c.SaveAs("plots.png");
  c.SaveAs("./plots/h_NPratio_after.png");

  // next plot
  c.Clear();
  c.SetLogy(0);
  c.SetLogz();
  h_bxby_before->Draw("colz");

  TBox *box = new TBox(h_bxby_after->GetXaxis()->GetXmin(), h_bxby_after->GetYaxis()->GetXmin(), h_bxby_after->GetXaxis()->GetXmax(), h_bxby_after->GetYaxis()->GetXmax());
  box->SetLineColor(kRed);
  box->SetFillStyle(0);
  box->Draw();

  TLatex *pbxby = new TLatex();
  pbxby->SetTextSize(0.03);
  pbxby->DrawLatexNDC(0.4, 0.37, "#splitline{Cut:-4 #leq b_{x} #leq 4}{-2 #leq b_{y} #leq 2}");

  h_bxby_before->SetTitle("");
  // c.SaveAs("plots.png");
  c.SaveAs("./plots/h_bxby_before.png");

  // next plot
  c.Clear();
  h_bxby_after->Draw("colz");
  // c.SaveAs("plots.png");
  c.SaveAs("./plots/h_bxby_after.png");

  // next plot
  c.Clear();
  h_dEdxVSp_pos_before->Draw("colz");
  bethebloch_e->Draw("same");
  bethebloch_pion->Draw("same");
  bethebloch_k->Draw("same");
  bethebloch_p->Draw("same");
  legend_bethe_bloch->Draw("same");
  // bethebloch_d->Draw("same");
  h_dEdxVSp_pos_before->SetTitle("dE/dx vs p before cut");

  // c.SaveAs("plots.png");
  c.SaveAs("./plots/h_dEdxVSp_pos_before.png");

  // next plot
  c.Clear();
  h_dEdxVSp_neg_before->Draw("colz");
  // c.SaveAs("plots.png");
  c.SaveAs("./plots/h_dEdxVSp_neg_before.png");

  // next plot
  c.Clear();
  h_dEdxVSp_pos_after->Draw("colz");
  bethebloch_e->Draw("same");
  bethebloch_pion->Draw("same");
  bethebloch_k->Draw("same");
  bethebloch_p->Draw("same");
  legend_bethe_bloch->Draw("same");
  // bethebloch_d->Draw("same");
  h_dEdxVSp_pos_after->SetTitle("dE/dx vs p after cut");
  // c.SaveAs("plots.png");
  c.SaveAs("./plots/h_dEdxVSp_pos_after.png");

  // next plot
  c.Clear();
  h_dEdxVSp_neg_after->Draw("colz");
  bethebloch_e->Draw("same");
  bethebloch_pion->Draw("same");
  bethebloch_k->Draw("same");
  bethebloch_p->Draw("same");
  // bethebloch_d->Draw("same");
  // c.SaveAs("plots.png");
  c.SaveAs("./plots/h_dEdxVSp_neg_after.png");

  // next plot
  c.Clear();
  h_dEdxVSp_pos_final->Draw("colz");
  bethebloch_e->Draw("same");
  bethebloch_pion->Draw("same");
  bethebloch_k->Draw("same");
  bethebloch_p->Draw("same");
  legend_bethe_bloch->Draw("same");
  // bethebloch_d->Draw("same");
  h_dEdxVSp_pos_final->SetTitle("dE/dx vs p after cut");
  // c.SaveAs("plots.png");
  c.SaveAs("./plots/h_dEdxVSp_pos_final.png");

  // next plot
  c.Clear();
  h_dEdxVSp_neg_final->Draw("colz");
  bethebloch_e->Draw("same");
  bethebloch_pion->Draw("same");
  bethebloch_k->Draw("same");
  bethebloch_p->Draw("same");
  // bethebloch_d->Draw("same");
  //  c.SaveAs("plots.png");
  c.SaveAs("./plots/h_dEdxVSp_neg_final.png");

  // next plot
  c.Clear();
  h_dEdxVSp_neg_final->Draw("colz");
  bethebloch_e->Draw("same");
  bethebloch_pion->Draw("same");
  bethebloch_k->Draw("same");
  bethebloch_p->Draw("same");
  // bethebloch_d->Draw("same");
  //  c.SaveAs("plots.png");
  c.SaveAs("./plots/h_dEdxVSp_neg_final.png");

  // next plot
  c.Clear();
  h_pxpy_before->Draw("colz");
  // c.SaveAs("plots.png");
  c.SaveAs("./plots/h_pxpy_before.png");

  // next plot
  c.Clear();
  h_pxpy_after->Draw("colz");
  // c.SaveAs("plots.png");
  c.SaveAs("./plots/h_pxpy_after.png");

  // next plot
  c.Clear();
  h_rapidityCM_before->Draw("hist");
  l_left = new TLine(h_rapidityCM_after->GetXaxis()->GetXmin(), 0, h_rapidityCM_after->GetXaxis()->GetXmin(), h_rapidityCM_before->GetMaximum());
  l_left->SetLineColor(kRed);
  l_left->SetLineStyle(9);
  l_left->Draw();

  l_right = new TLine(h_rapidityCM_after->GetXaxis()->GetXmax(), 0, h_rapidityCM_after->GetXaxis()->GetXmax(), h_rapidityCM_before->GetMaximum());
  l_right->SetLineColor(kRed);
  l_right->SetLineStyle(9);
  l_right->Draw();

  TLatex *prapidityCM = new TLatex();
  prapidityCM->SetTextSize(0.03);
  prapidityCM->SetTextFont(82);
  prapidityCM->DrawLatexNDC(0.12, 0.87, "Cut:-0.75 #leq yCM #leq 0.75");

  // c.SaveAs("plots.png");
  c.SaveAs("./plots/h_rapidityCM_before.png");

  // next plot
  c.Clear();
  h_rapidityCM_after->Draw("hist");
  // c.SaveAs("plots.png");
  c.SaveAs("./plots/h_rapidityCM_after.png");

  // next plot
  c.Clear();
  h_dEdxVSp_pos_acc->Draw("colz");
  bethebloch_e->Draw("same");
  bethebloch_pion->Draw("same");
  bethebloch_k->Draw("same");
  bethebloch_p->Draw("same");
  legend_bethe_bloch->Draw("same");
  // bethebloch_d->Draw("same");
  //  c.SaveAs("plots.png");
  c.SaveAs("./plots/h_dEdxVSp_pos_acc.png");

  // next plot
  c.Clear();
  h_pxpy->Draw("colz");
  // c.SaveAs("plots.png");
  c.SaveAs("./plots/h_pxpy.png");

  // next plot
  c.Clear();
  h_ptyCM->Draw("colz");
  // c.SaveAs("plots.png");
  c.SaveAs("./plots/h_ptyCM.png");

  // next plot
  c.Clear();
  h_px->Draw("hist");
  // c.SaveAs("plots.png");
  c.SaveAs("./plots/h_px.png");

  // next plot
  c.Clear();
  h_py->Draw("hist");
  // c.SaveAs("plots.png");
  c.SaveAs("./plots/h_py.png");

  // next plot
  c.Clear();
  h_pt->Draw("hist");
  // c.SaveAs("plots.png");
  c.SaveAs("./plots/h_pt.png");

  // next plot
  c.Clear();
  h_yCM->Draw("hist");
  // c.SaveAs("plots.png");
  c.SaveAs("./plots/h_yCM.png");

  // next plot
  c.Clear();
  h_np->Draw("hist");
  // c.SaveAs("plots.png");
  c.SaveAs("./plots/h_np.png");

  // next plot
  c.Clear();
  h_efficiency->Draw("colz");
  // c.SaveAs("plots.png");
  c.SaveAs("./plots/h_efficiency.png");

  // next plot
  c.Clear();
  h_purity->Draw("colz");
  // c.SaveAs("plots.png");
  c.SaveAs("./plots/h_purity.png");

  // next plot
  c.Clear();
  h_dsxdsy_before->Draw("colz");
  // c.SaveAs("plots.png");
  c.SaveAs("./plots/h_dsxdsy_before.png");

  // next plot
  c.Clear();
  h_dsxdrho_before->Draw("colz");
  // c.SaveAs("plots.png");
  c.SaveAs("./plots/h_dsxdrho_before.png");

  // next plot
  c.Clear();
  h_dsydrho_before->Draw("colz");
  // c.SaveAs("plots.png");
  c.SaveAs("./plots/h_dsydrho_before.png");

  // next plot
  c.Clear();
  h_dsxdsy_discarded->Draw("colz");
  // c.SaveAs("plots.png");
  c.SaveAs("./plots/h_dsxdsy_discarded.png");

  // next plot
  c.Clear();
  h_dsxdrho_discarded->Draw("colz");
  // c.SaveAs("plots.png");
  c.SaveAs("./plots/h_dsxdrho_discarded.png");

  // next plot
  c.Clear();
  h_dsydrho_discarded->Draw("colz");
  // c.SaveAs("plots.png");
  c.SaveAs("./plots/h_dsydrho_discarded.png");

  // next plot
  c.Clear();
  h_dsxdsy_after->Draw("colz");
  // c.SaveAs("plots.png");
  c.SaveAs("./plots/h_dsxdsy_after.png");

  // next plot
  c.Clear();
  h_dsxdrho_after->Draw("colz");
  // c.SaveAs("plots.png");
  c.SaveAs("./plots/h_dsxdsy_after.png");

  // next plot
  c.Clear();
  h_dsydrho_after->Draw("colz");
  // c.SaveAs("plots.png");
  c.SaveAs("./plots/h_dsydrho_after.png");

  // c.SaveAs("plots.png]"); // closing pdf
}
