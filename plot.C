
TH1F* getHisto(TString fileName, TString histoName, int color, int Nbins, float Xmin, float Xmax) {
  TFile* f = new TFile(fileName);                                         
  TTree* t = (TTree*) f->Get("tree");                                                  
  t->Draw(Form("T30[0] - T30[1]>>%s(%i, %f, %f)", histoName.Data(), Nbins, Xmin, Xmax), "", "goff");      
  TH1F* h = (TH1F*) gDirectory->Get(histoName);            
  h->SetLineColor(color);
  h->Scale(1/h->Integral());
  h->SetFillColor(color);
  h->SetFillStyle(3002);
  h->SetLineWidth(2);
  h->SetLineColor(color);
  return h;
}

void plot(int Nbins = 80, float Xmin = -40, float Xmax = 55) {

  gStyle->SetOptTitle(0);
  gStyle->SetOptStat(0);

  TH1F* h5 = getHisto("data/run52_test.root", "h5", kBlue, Nbins, Xmin, Xmax);
  TH1F* h6 = getHisto("data/run53_test.root", "h6", kRed, Nbins, Xmin, Xmax);
  TH1F* h7 = getHisto("data/run54_test.root", "h7", kGreen+2, Nbins, Xmin, Xmax);
  TH1F* h8 = getHisto("data/run55_test.root", "h8", kMagenta, Nbins, Xmin, Xmax);
  TH1F* h9 = getHisto("data/run56_test.root", "h9", kOrange, Nbins, Xmin, Xmax);
  TH1F* ha = getHisto("data/run57_test.root", "ha", kBlack, Nbins, Xmin, Xmax);
  TH1F* hb = getHisto("data/run58_test.root", "hb", kBlue-9, Nbins, Xmin, Xmax);

  h5->GetXaxis()->SetTitle("#Deltat [ns]");
  h5->GetYaxis()->SetRangeUser(0, 0.153);

  TCanvas* c1 = new TCanvas("c1","c1",800,800);
  h5->Draw();
  h6->Draw("same");
  h7->Draw("same");
  h8->Draw("same");
  h9->Draw("same");
  ha->Draw("same");
  hb->Draw("same");

  TLegend* leg = new TLegend(0.48,0.48,0.90,0.74);
  leg->AddEntry(h5, "coinc. width = 4.16 ns (+ 0 #rightarrow 4.16 ns)", "f");
  leg->AddEntry(h6, "coinc. width = 8.32 ns (+ 0 #rightarrow 4.16 ns)", "f");
  leg->AddEntry(h7, "coinc. width = 12.48 ns (+ 0 #rightarrow 4.16 ns)", "f");
  leg->AddEntry(h8, "coinc. width = 16.64 ns (+ 0 #rightarrow 4.16 ns)", "f");
  leg->AddEntry(h9, "coinc. width = 20.80 ns (+ 0 #rightarrow 4.16 ns)", "f");
  leg->AddEntry(ha, "coinc. width = 24.96 ns (+ 0 #rightarrow 4.16 ns)", "f");
  leg->AddEntry(hb, "coinc. width = 29.12 ns (+ 0 #rightarrow 4.16 ns)", "f");
  leg->SetLineWidth(0);
  leg->Draw();
  
  TLatex* la1 = new TLatex(-36, 0.145, "LAPD");
  la1->SetTextSize(0.04);
  la1->Draw();

  TLatex* la2 = new TLatex(-36, 0.137, "Background w/ lead wall");
  la2->SetTextSize(0.04);
  la2->Draw();

  c1->SaveAs("CRTvsCoincSignalWidth_BkgLeadWall.png");
}
