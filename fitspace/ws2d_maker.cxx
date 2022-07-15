using namespace RooFit ;
void ws2d_maker(float nevt_hc, float nevt_hig, float nevt_qqzz, float nevt_ggzz, float nevt_zx) {
    RooRandom::randomGenerator()->SetSeed(301);

    RooWorkspace *w = new RooWorkspace("w","w");
    w->factory("ZZMass[118,130]") ;
    w->factory("dbkg_kin[0,1]") ;
    w->factory("weight[-100,100]") ;

    int nbin_mass=30, nbin_dbkg=35;
    TH2D *h = new TH2D("h", "h", nbin_mass, 118, 130, nbin_dbkg, 0., 1.);

    // read txt and fill Histograms
    std::map<TString, TH2D*> hist;

    fstream infile;
	infile.open("hist_raw.txt", ios::in);
    int isam = 0;
    Float_t value, error;

    TCanvas* c = new TCanvas("c","c",2400,1600);
    c->Divide(3, 2);
    for (TString sam: {"hig", "hc", "qqzz", "ggzz", "zx"}){
        auto name = TString::Format("hist[%s]", sam.Data());
        hist[sam] = new TH2D(name, name, nbin_mass, 118, 130, nbin_dbkg, 0., 1.);
        for (int i = 1; i <= nbin_mass; i++){
            for (int j = 1; j <= nbin_dbkg; j++){
                infile >> value >> error;
                hist[sam]->SetBinContent(i, j, value);
                hist[sam]->SetBinError(i, j, error);
            }
        }
        c->cd(isam+1);
        hist[sam]->Draw("surf3");
        isam++;
    }
    c->SaveAs("datahist.png");

    // convert to RooDataHist and also read 1d templates from existing workspace
    auto w1d = (RooWorkspace*) TFile::Open("roofit_pdfm4l_shape.root")->Get("w");

    for (TString sam: {"hig", "hc", "qqzz", "ggzz", "zx"}){
        auto dh_name = TString::Format("datahist_%s", sam.Data());
        auto hp_name = TString::Format("histpdf_%s", sam.Data());
        auto pdfm4l_name = TString::Format("pdfm4l_%s", sam.Data());
        auto dh = new RooDataHist(dh_name, dh_name, RooArgList(*w->var("ZZMass"), *w->var("dbkg_kin")), hist[sam]);
        auto hp = new RooHistPdf(hp_name, hp_name, RooArgSet(*w->var("ZZMass"), *w->var("dbkg_kin")), *dh);
        w->import(*hp);
        w->import(*w1d->pdf(sam), RenameVariable(sam, pdfm4l_name));
        w->factory(TString::Format("PROD::%s(%s, %s)", sam.Data(), pdfm4l_name.Data(), hp_name.Data()));
    }
    // RooPlot* frame1 = w->var("ZZMass")->frame(); dh.plotOn(frame1); frame1->Draw() ;

    // read from existing workspace
    w->factory(TString::Format("SUM::pdfall(nevt_hig[%f]*hig, nevt_hc[%f]*hc, nevt_qqzz[%f]*qqzz, nevt_ggzz[%f]*ggzz, nevt_zx[%f]*zx)", nevt_hig, nevt_hc, nevt_qqzz, nevt_ggzz, nevt_zx));
    // w->factory("SUM::pdfall(hig, hc, qqzz, ggzz, zx)"); // this cannot work!!
    float nevt = nevt_hig + nevt_hc + nevt_qqzz + nevt_ggzz + nevt_zx;
    RooDataSet* ds_toy = w->pdf("pdfall")->generate(RooArgSet(*w->var("ZZMass"), *w->var("dbkg_kin")), (int)nevt);
    w->import(*ds_toy, Rename("data_obs"));
    w->Print();
    w->writeToFile("roofit_unbinned2d.root");

}