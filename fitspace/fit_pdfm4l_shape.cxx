using namespace RooFit ;
void fit_pdfm4l_shape(TString basedir) {
    RooRandom::randomGenerator()->SetSeed(301);

    RooWorkspace *w = new RooWorkspace("w","w");
    w->factory("ZZMass[118,130]") ;
    w->factory("weight[-100,100]") ;

    TTree* tree_hig = (TTree*)TFile::Open(TString::Format("/home/pku/licq/cH/zz/fit/roofit_tpl/%s/hig.root", basedir.Data()))->Get("Events");
    RooDataSet ds_hig("ds_hig","ds_hig", RooArgSet(*w->var("ZZMass"), *w->var("weight")), Import(*tree_hig), WeightVar("weight")) ;
    float nevt_hig = ds_hig.sumEntries();
    w->factory("RooDoubleCBFast::hig(ZZMass, mean_hig[120,100,160], width_hig[1,0.01,20], a1_hig[1,0.01,20], a2_hig[1,0.01,20], n1_hig[1,0.01,20], n2_hig[1,0.01,20])");
    w->pdf("hig")->fitTo(ds_hig, Save()) ;

    TTree* tree_hc = (TTree*)TFile::Open(TString::Format("/home/pku/licq/cH/zz/fit/roofit_tpl/%s/hc.root", basedir.Data()))->Get("Events");
    RooDataSet ds_hc("ds_hc","ds_hc", RooArgSet(*w->var("ZZMass"), *w->var("weight")), Import(*tree_hc), WeightVar("weight")) ;
    float nevt_hc = ds_hc.sumEntries();
    w->factory("RooDoubleCBFast::hc(ZZMass, mean_hc[120,100,160], width_hc[1,0.01,20], a1_hc[1,0.01,20], a2_hc[1,0.01,20], n1_hc[1,0.01,20], n2_hc[1,0.01,20])");
    w->pdf("hc")->fitTo(ds_hc, Save()) ;
    
    TTree* tree_qqzz = (TTree*)TFile::Open(TString::Format("/home/pku/licq/cH/zz/fit/roofit_tpl/%s/qqzz.root", basedir.Data()))->Get("Events");
    RooDataSet ds_qqzz("ds_qqzz","ds_qqzz", RooArgSet(*w->var("ZZMass"), *w->var("weight")), Import(*tree_qqzz), WeightVar("weight")) ;
    float nevt_qqzz = ds_qqzz.sumEntries();
    w->factory("RooBernstein::qqzz(ZZMass, {b1_qqzz[0.5,0.,1.], b2_qqzz[0.5,0.,1.], b3_qqzz[0.5,0.,1.]})");
    w->pdf("qqzz")->fitTo(ds_qqzz, Save()) ;
    
    TTree* tree_ggzz = (TTree*)TFile::Open(TString::Format("/home/pku/licq/cH/zz/fit/roofit_tpl/%s/ggzz.root", basedir.Data()))->Get("Events");
    RooDataSet ds_ggzz("ds_ggzz","ds_ggzz", RooArgSet(*w->var("ZZMass"), *w->var("weight")), Import(*tree_ggzz), WeightVar("weight")) ;
    float nevt_ggzz = ds_ggzz.sumEntries();
    w->factory("RooBernstein::ggzz(ZZMass, {b1_ggzz[0.5,0.,1.], b2_ggzz[0.5,0.,1.], b3_ggzz[0.5,0.,1.]})");
    w->pdf("ggzz")->fitTo(ds_ggzz, Save()) ;
    
    TTree* tree_zx = (TTree*)TFile::Open(TString::Format("/home/pku/licq/cH/zz/fit/roofit_tpl/%s/zx.root", basedir.Data()))->Get("Events");
    RooDataSet ds_zx("ds_zx","ds_zx", RooArgSet(*w->var("ZZMass"), *w->var("weight")), Import(*tree_zx), WeightVar("weight")) ;
    float nevt_zx = ds_zx.sumEntries();
    w->factory("RooLandau::zx(ZZMass, l1_zx[100,100,160], l2_zx[20,-100,100])");
    w->pdf("zx")->fitTo(ds_zx, Save()) ;

    // combine all
    float nevt = nevt_hig + nevt_hc + nevt_qqzz + nevt_ggzz + nevt_zx;
    cout << ">>TAG>>" << nevt_hc << "  " << nevt_hig << "  " << nevt_qqzz << "  " << nevt_ggzz << "  " << nevt_zx << endl;
    // cout << ">>" << nevt << endl;
    w->factory(TString::Format("SUM::pdfall(nevt_hig[%f]*hig, nevt_hc[%f]*hc, nevt_qqzz[%f]*qqzz, nevt_ggzz[%f]*ggzz, nevt_zx[%f]*zx)", nevt_hig, nevt_hc, nevt_qqzz, nevt_ggzz, nevt_zx));
    RooDataSet* ds_toy = w->pdf("pdfall")->generate(*w->var("ZZMass"), (int)nevt);
    w->import(*ds_toy, Rename("data_obs"));
    w->writeToFile("roofit_pdfm4l_shape.root"); // uncomment when writing 1d pdfm4l shapes to root

    // w->pdf("pdfall")->fitTo(*ds_toy, Save()) ;


    // plot dataset on frame

    TCanvas* c = new TCanvas("c","c",2400,1600) ;
    c->Divide(3, 2) ;
    c->cd(1); RooPlot* frame2 = w->var("ZZMass")->frame(); frame2->SetTitle("H+c signal (DoubleCB)"); ds_hc.plotOn(frame2); w->pdf("hc")->plotOn(frame2); frame2->Draw() ;
    c->cd(2); RooPlot* frame1 = w->var("ZZMass")->frame(); frame1->SetTitle("Higgs BKG (DoubleCB)"); ds_hig.plotOn(frame1); w->pdf("hig")->plotOn(frame1); frame1->Draw() ;
    c->cd(3); RooPlot* frame3 = w->var("ZZMass")->frame(); frame3->SetTitle("qqzz BKG (Bernstein)"); ds_qqzz.plotOn(frame3); w->pdf("qqzz")->plotOn(frame3); frame3->Draw() ;
    c->cd(4); RooPlot* frame4 = w->var("ZZMass")->frame(); frame4->SetTitle("ggzz BKG (Bernstein)"); ds_ggzz.plotOn(frame4); w->pdf("ggzz")->plotOn(frame4); frame4->Draw() ;
    c->cd(5); RooPlot* frame5 = w->var("ZZMass")->frame(); frame5->SetTitle("Z+X BKG (Landau)"); ds_zx.plotOn(frame5); w->pdf("zx")->plotOn(frame5); frame5->Draw() ;
    c->cd(6); RooPlot* frame6 = w->var("ZZMass")->frame(); frame6->SetTitle("All MC with toy data"); ds_toy->plotOn(frame6); w->pdf("pdfall")->plotOn(frame6); frame6->Draw() ;
    c->SaveAs("pdfm4l_shape.png");

}