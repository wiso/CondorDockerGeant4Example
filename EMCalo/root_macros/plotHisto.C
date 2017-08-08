{
  gROOT->Reset();
  
  vector<string> filenames;
  filenames.push_back("run_1GeV.root");
  filenames.push_back("run_10GeV.root");
  filenames.push_back("run_50GeV.root");
  filenames.push_back("run_100GeV.root");

  vector<double> energies;
  energies.push_back(1);
  energies.push_back(10);
  energies.push_back(50);
  energies.push_back(100);

  TFile * f;
  TF1 * shower;
  TGraph * gr = new TGraph();

  // =============================================================
  // study the shower max dependence with the energy
  // =============================================================

  for ( int k = 0 ; k < filenames.size() ; k++){
    f = new TFile(filenames[k].c_str());    
    shower = new TF1("shower","[2]*[1]* ( pow([1]*x,[0]-1)*exp(-1*[1]*x))/(TMath::Gamma([0])) ",0,50);
    shower->SetParameter(0,1) ;
    shower->SetParameter(1,0.5) ;
    shower->SetParameter(2,1);
    
    TCanvas * c2 = new TCanvas("c2","c2");
    TH1D* hist3 = (TH1D*)f.Get("11");
    c2->cd();
    hist3->Draw();
    hist3->Fit(shower, "","",0,50);
    double a = shower->GetParameter(0);
    double b = shower->GetParameter(1);
    double max = (a-1.) / b ;
    cout << max << endl;
    gr->SetPoint(k,energies[k], max );

  }

  filenames.clear();
  filenames.push_back("run_1GeV_sampl.root");
  filenames.push_back("run_10GeV_sampl.root");
  filenames.push_back("run_50GeV_sampl.root");
  filenames.push_back("run_100GeV_sampl.root");

  // =============================================================
  // This is to look at the energy resolution
  // =============================================================

  TGraph * gr_res = new TGraph();

  for ( int k = 0 ; k < filenames.size() ; k++){
    f = new TFile(filenames[k].c_str());    
    
    TCanvas * c2 = new TCanvas("c2","c2");
    TH1D* hist3 = (TH1D*)f.Get("1");
    c2->cd();
    hist3->Draw();
    TF1 * fitfun = new TF1("gaus","gaus");
    hist3->Fit(fitfun);
    double mean  = fitfun->GetParameter(1);
    double sigma = fitfun->GetParameter(2); 
    cout << mean << " " << sigma << endl;
    gr_res->SetPoint(k,energies[k], sigma/ mean );
  }
  
  TCanvas* c1 = new TCanvas("c1", "c1");
  gr_res->Draw("ALP");
  
  // =============================================================
  // This is to look at the longitudinal leakage XO ?
  // =============================================================
  
  for ( int k = 0 ; k < filenames.size() ; k++){
    
    f = new TFile(filenames[k].c_str());        
    TH1D* hist3 = (TH1D*)f.Get("21");
    cout << hist3->GetBinContent(50) << endl;
    
    //    gr_res->SetPoint(k,energies[k], sigma/ mean );
  }

  
}  
