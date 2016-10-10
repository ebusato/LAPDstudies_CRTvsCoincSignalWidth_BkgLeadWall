
struct Result {
  TH1F* h;
  double halffwhm;
};

Result* getHisto(TString fileName, TString histoName, int color, int Nbins, float Xmin, float Xmax) {
  cout <<  "Processing fileName=" << fileName << ", histoName=" << histoName << endl; 
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
  int bin1 = h->FindFirstBinAbove(h->GetMaximum()/2);
  int bin2 = h->FindLastBinAbove(h->GetMaximum()/2);
  double fwhm = h->GetBinCenter(bin2) - h->GetBinCenter(bin1);
  Result *res = new Result();
  res->h = h;
  res->halffwhm = fwhm/2.;
  return res;
}

void plot(int Nbins = 80, float Xmin = -40, float Xmax = 55) {

  gStyle->SetOptTitle(0);
  gStyle->SetOptStat(0);

  Result* r5 = getHisto("data/run52_test.root", "h5", kBlue, Nbins, Xmin, Xmax);
  Result* r6 = getHisto("data/run53_test.root", "h6", kRed, Nbins, Xmin, Xmax);
  Result* r7 = getHisto("data/run54_test.root", "h7", kGreen+2, Nbins, Xmin, Xmax);
  Result* r8 = getHisto("data/run55_test.root", "h8", kMagenta, Nbins, Xmin, Xmax);
  Result* r9 = getHisto("data/run56_test.root", "h9", kOrange, Nbins, Xmin, Xmax);
  Result* ra = getHisto("data/run57_test.root", "ha", kBlack, Nbins, Xmin, Xmax);
  Result* rb = getHisto("data/run58_test.root", "hb", kBlue-9, Nbins, Xmin, Xmax);
  
  TH1F* h5 = r5->h;
  TH1F* h6 = r6->h;
  TH1F* h7 = r7->h;
  TH1F* h8 = r8->h;
  TH1F* h9 = r9->h;
  TH1F* ha = ra->h;
  TH1F* hb = rb->h;

  double halffwhm5 = r5->halffwhm;
  double halffwhm6 = r6->halffwhm;
  double halffwhm7 = r7->halffwhm;
  double halffwhm8 = r8->halffwhm;
  double halffwhm9 = r9->halffwhm;
  double halffwhma = ra->halffwhm;
  double halffwhmb = rb->halffwhm;

  /*
  TH1F* h5 = getHisto("data/run52_test.root", "h5", kBlue, Nbins, Xmin, Xmax);
  TH1F* h6 = getHisto("data/run53_test.root", "h6", kRed, Nbins, Xmin, Xmax);
  TH1F* h7 = getHisto("data/run54_test.root", "h7", kGreen+2, Nbins, Xmin, Xmax);
  TH1F* h8 = getHisto("data/run55_test.root", "h8", kMagenta, Nbins, Xmin, Xmax);
  TH1F* h9 = getHisto("data/run56_test.root", "h9", kOrange, Nbins, Xmin, Xmax);
  TH1F* ha = getHisto("data/run57_test.root", "ha", kBlack, Nbins, Xmin, Xmax);
  TH1F* hb = getHisto("data/run58_test.root", "hb", kBlue-9, Nbins, Xmin, Xmax);
  */

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
  leg->AddEntry(h5, "coinc. window = 4.16 ns (+ 0 #rightarrow 4.16 ns)", "f");
  leg->AddEntry(h6, "coinc. window = 8.32 ns (+ 0 #rightarrow 4.16 ns)", "f");
  leg->AddEntry(h7, "coinc. window = 12.48 ns (+ 0 #rightarrow 4.16 ns)", "f");
  leg->AddEntry(h8, "coinc. window = 16.64 ns (+ 0 #rightarrow 4.16 ns)", "f");
  leg->AddEntry(h9, "coinc. window = 20.80 ns (+ 0 #rightarrow 4.16 ns)", "f");
  leg->AddEntry(ha, "coinc. window = 24.96 ns (+ 0 #rightarrow 4.16 ns)", "f");
  leg->AddEntry(hb, "coinc. window = 29.12 ns (+ 0 #rightarrow 4.16 ns)", "f");
  leg->SetLineWidth(0);
  leg->Draw();
  
  TLatex* la1 = new TLatex(-36, 0.145, "LAPD");
  la1->SetTextSize(0.04);
  la1->Draw();

  TLatex* la2 = new TLatex(-36, 0.137, "Background w/ lead wall");
  la2->SetTextSize(0.04);
  la2->Draw();

  c1->SaveAs("CRTvsCoincSignalWidth_BkgLeadWall.png");

  TCanvas* c2 = new TCanvas("c2", "c2", 800, 800);
  gPad->SetGridx();
  gPad->SetGridy();
  TGraph* gr = new TGraph(7);
  gr->SetPoint(0, 4.16, halffwhm5);
  gr->SetPoint(1, 8.32, halffwhm6);
  gr->SetPoint(2, 12.48, halffwhm7);
  gr->SetPoint(3, 16.64, halffwhm8);
  gr->SetPoint(4, 20.80, halffwhm9);
  gr->SetPoint(5, 24.96, halffwhma);
  gr->SetPoint(6, 29.12, halffwhmb);
  gr->SetMarkerStyle(8);
  gr->Draw("ap");
  gr->GetYaxis()->SetTitle("FWHM/2 [ns]");
  gr->GetXaxis()->SetTitle("Coinc. window [ns]");
  gr->GetXaxis()->SetRangeUser(0, 30);
  gr->GetYaxis()->SetRangeUser(0, 30);
  gr->Draw("ap");
  TLine* l1 = new TLine(0, 0 - (4.16 + 4.16/2.)/2., 30, 30 - (4.16 + 4.16/2.)/2.);
  l1->SetLineColor(kBlue);
  l1->Draw("same");
  TLine* l2 = new TLine(0, 0, 30, 30);
  l2->SetLineColor(kRed);
  l2->Draw("same");
  c2->SaveAs("HalfFWHMvsTheo.png");
}
