void plot()
{

  // opening files
  TFile f("tracks_filtered.root");
  TFile g("bethebloch.root");

  // get histograms from the files
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
  TH2F *h_dEdxVSp_pos_probCut = (TH2F *)f.Get("h_dEdxVSp_pos_probCut");
  TH2F *h_dEdxVSp_neg_probCut = (TH2F *)f.Get("h_dEdxVSp_neg_probCut");

  TGraph *bethebloch_e = (TGraph *)g.Get("bethebloch_e");
  TGraph *bethebloch_pion = (TGraph *)g.Get("bethebloch_pion");
  TGraph *bethebloch_k = (TGraph *)g.Get("bethebloch_k");
  TGraph *bethebloch_p = (TGraph *)g.Get("bethebloch_p");
  TGraph *bethebloch_d = (TGraph *)g.Get("bethebloch_d");

  // set line colors
  // h_vz_before->SetLineColor(1);
  // h_vz_after->SetLineColor(2);
  // h_NPratio_before->SetLineColor(1);
  // h_NPratio_after->SetLineColor(2);
  // h_bxby_before->SetLineColor(1);
  // h_bxby_after->SetLineColor(2);

  // h_vz_before
  h_vz_before->GetXaxis()->SetTitle("VertexZ [cm]");
  h_vz_before->GetYaxis()->SetTitle("nTracks");

  // h_vz_after
  h_vz_after->GetXaxis()->SetTitle("VertexZ [cm]");
  h_vz_after->GetYaxis()->SetTitle("nTracks");

  // h_NPratio_before
  h_NPratio_before->GetXaxis()->SetTitle("NPratio");
  h_NPratio_before->GetYaxis()->SetTitle("nTracks");

  // h_NPratio_after
  h_NPratio_after->GetXaxis()->SetTitle("NPratio");
  h_NPratio_after->GetYaxis()->SetTitle("nTracks");

  // h_bxby_before
  h_bxby_before->GetXaxis()->SetTitle("bx [cm]");
  h_bxby_before->GetYaxis()->SetTitle("by [cm]");

  // h_bxby_after
  h_bxby_after->GetXaxis()->SetTitle("bx [cm]");
  h_bxby_after->GetYaxis()->SetTitle("by [cm]");

  // h_dEdxVSp_pos_before
  h_dEdxVSp_pos_before->GetYaxis()->SetTitle("dE/dx");
  h_dEdxVSp_pos_before->GetXaxis()->SetTitle("log_{10}(p)");

  // h_dEdxVSp_neg_before
  h_dEdxVSp_neg_before->GetYaxis()->SetTitle("dE/dx");
  h_dEdxVSp_neg_before->GetXaxis()->SetTitle("log_{10}(p)");

  // h_dEdxVSp_pos_after
  h_dEdxVSp_pos_after->GetYaxis()->SetTitle("dE/dx");
  h_dEdxVSp_pos_after->GetXaxis()->SetTitle("log_{10}(p)");

  // h_dEdxVSp_neg_after
  h_dEdxVSp_neg_after->GetYaxis()->SetTitle("dE/dx");
  h_dEdxVSp_neg_after->GetXaxis()->SetTitle("log_{10}(p)");

  // h_dEdxVSp_pos_final
  h_dEdxVSp_pos_final->GetYaxis()->SetTitle("dE/dx");
  h_dEdxVSp_pos_final->GetXaxis()->SetTitle("log_{10}(p)");

  // h_dEdxVSp_neg_final
  h_dEdxVSp_neg_final->GetYaxis()->SetTitle("dE/dx");
  h_dEdxVSp_neg_final->GetXaxis()->SetTitle("log_{10}(p)");

  TCanvas c;
  // c.SaveAs("plots.pdf["); // opening pdf

  // draw all histograms
  c.SetLogy();
  h_vz_before->Draw("hist");

  TLine *l_left = new TLine(h_vz_after->GetXaxis()->GetXmin(), 0, h_vz_after->GetXaxis()->GetXmin(), h_vz_before->GetMaximum());
  l_left->SetLineColor(kBlack);
  l_left->SetLineStyle(9);
  l_left->Draw();

  TLine *l_right = new TLine(h_vz_after->GetXaxis()->GetXmax(), 0, h_vz_after->GetXaxis()->GetXmax(), h_vz_before->GetMaximum());
  l_right->SetLineColor(kBlack);
  l_right->SetLineStyle(9);
  l_right->Draw();

  // c.SaveAs("plots.pdf");
  c.SaveAs("./plots/h_vz_before.pdf"); // plot

  // next plot
  c.Clear();
  h_vz_after->Draw("hist");
  // c.SaveAs("plots.pdf");
  c.SaveAs("./plots/h_vz_after.pdf");

  // next plot
  c.Clear();
  h_NPratio_before->Draw("hist");

  l_left = new TLine(h_NPratio_after->GetXaxis()->GetXmin(), 0, h_NPratio_after->GetXaxis()->GetXmin(), h_NPratio_before->GetMaximum());
  l_left->SetLineColor(kBlack);
  l_left->SetLineStyle(9);
  l_left->Draw();

  l_right = new TLine(h_NPratio_after->GetXaxis()->GetXmax(), 0, h_NPratio_after->GetXaxis()->GetXmax(), h_NPratio_before->GetMaximum());
  l_right->SetLineColor(kBlack);
  l_right->SetLineStyle(9);
  l_right->Draw();

  // c.SaveAs("plots.pdf");
  c.SaveAs("./plots/h_NPratio_before.pdf");

  // next plot
  c.Clear();
  h_NPratio_after->Draw("hist");
  // c.SaveAs("plots.pdf");
  c.SaveAs("./plots/h_NPratio_after.pdf");

  // next plot
  c.Clear();
  c.SetLogy(0);
  c.SetLogz();
  h_bxby_before->Draw("colz");

  TBox *box = new TBox(h_bxby_after->GetXaxis()->GetXmin(), h_bxby_after->GetYaxis()->GetXmin(), h_bxby_after->GetXaxis()->GetXmax(), h_bxby_after->GetYaxis()->GetXmax());
  box->SetLineColor(kRed);
  box->SetFillStyle(0);
  box->Draw();

  // c.SaveAs("plots.pdf");
  c.SaveAs("./plots/h_bxby_before.pdf");

  // next plot
  c.Clear();
  h_bxby_after->Draw("colz");
  // c.SaveAs("plots.pdf");
  c.SaveAs("./plots/h_bxby_after.pdf");

  // next plot
  c.Clear();
  h_dEdxVSp_pos_before->Draw("colz");
  bethebloch_e->Draw("same");
  bethebloch_pion->Draw("same");
  bethebloch_k->Draw("same");
  bethebloch_p->Draw("same");
  bethebloch_d->Draw("same");

  // c.SaveAs("plots.pdf");
  c.SaveAs("./plots/h_dEdxVSp_pos_before.pdf");

  // next plot
  c.Clear();
  h_dEdxVSp_neg_before->Draw("colz");
  // c.SaveAs("plots.pdf");
  c.SaveAs("./plots/h_dEdxVSp_neg_before.pdf");

  // next plot
  c.Clear();
  h_dEdxVSp_pos_after->Draw("colz");
  bethebloch_e->Draw("same");
  bethebloch_pion->Draw("same");
  bethebloch_k->Draw("same");
  bethebloch_p->Draw("same");
  bethebloch_d->Draw("same");
  // c.SaveAs("plots.pdf");
  c.SaveAs("./plots/h_dEdxVSp_pos_after.pdf");

  // next plot
  c.Clear();
  h_dEdxVSp_pos_final->Draw("colz");
  bethebloch_e->Draw("same");
  bethebloch_pion->Draw("same");
  bethebloch_k->Draw("same");
  bethebloch_p->Draw("same");
  bethebloch_d->Draw("same");
  // c.SaveAs("plots.pdf");
  c.SaveAs("./plots/h_dEdxVSp_pos_final.pdf");

  // next plot
  c.Clear();
  h_dEdxVSp_neg_after->Draw("colz");
  // c.SaveAs("plots.pdf");
  c.SaveAs("./plots/h_dEdxVSp_neg_after.pdf");

  c.Clear();
  h_dEdxVSp_pos_probCut->Draw("colz");
  bethebloch_e->Draw("same");
  bethebloch_pion->Draw("same");
  bethebloch_k->Draw("same");
  bethebloch_p->Draw("same");
  bethebloch_d->Draw("same");
  // c.SaveAs("plots.pdf");
  c.SaveAs("./plots/h_dEdxVSp_pos_probCut.pdf");

  // c.SaveAs("plots.pdf]"); // closing pdf
}
