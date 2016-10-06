
TH1F* getHisto(TString fileName, TString histoName, int color, int Nbins, float Xmin, float Xmax) {
  TFile* f = new TFile(fileName);                                         
  TTree* t = (TTree*) f->Get("tree");                                                  
  t->Draw(Form("T30[0] - T30[1]>>%s(%i, %f, %f)", histoName.Data(), Nbins, Xmin, Xmax), "", "goff");      
  TH1F* h = (TH1F*) gDirectory->Get(histoName);            
  h->SetLineColor(color);
  h->Scale(1/h->Integral());
  h->SetFillColor(color);
  h->SetFillStyle(3001);
  h->SetLineWidth(2);
  h->SetLineColor(color);
  return h;
}

void plot(int Nbins = 50, float Xmin = -40, float Xmax = 40) {

  gStyle->SetOptTitle(0);
  gStyle->SetOptStat(0);

  TH1F* h5 = getHisto("data/run52_test.root", "h5", kBlue-3, Nbins, Xmin, Xmax);
  TH1F* h6 = getHisto("data/run53_test.root", "h6", kBlue-2, Nbins, Xmin, Xmax);
  TH1F* h7 = getHisto("data/run54_test.root", "h7", kBlue-1, Nbins, Xmin, Xmax);
  TH1F* h8 = getHisto("data/run55_test.root", "h8", kBlue, Nbins, Xmin, Xmax);
  TH1F* h9 = getHisto("data/run56_test.root", "h9", kBlue+1, Nbins, Xmin, Xmax);
  TH1F* ha = getHisto("data/run57_test.root", "ha", kBlue+2, Nbins, Xmin, Xmax);
  TH1F* hb = getHisto("data/run58_test.root", "hb", kBlue+3, Nbins, Xmin, Xmax);

  h5->GetXaxis()->SetTitle("#Deltat [ns]");

  TCanvas* c1 = new TCanvas("c1","c1",400,400);
  h5->Draw();
  h6->Draw("same");
  h7->Draw("same");
  h8->Draw("same");
  h9->Draw("same");
  ha->Draw("same");
  hb->Draw("same");
  
}
