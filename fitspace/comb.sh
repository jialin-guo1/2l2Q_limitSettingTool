combineCards.py HP=../hig0218_bdt1j0.70-1.00_hignorm1.2/roofit_unbinned2d.txt MP=../hig0218_bdt1j0.40-0.70_hignorm1.2/roofit_unbinned2d.txt LP=../hig0218_bdt1j0.00-0.40_hignorm1.2/roofit_unbinned2d.txt > roofit_unbinned2d.txt
combine -M AsymptoticLimits -t -1 --expectSignal 1 --saveWorkspace --freezeParameters a1_hig,a1_hc,a2_hig,a2_hc,b1_ggzz,b1_qqzz,b2_ggzz,b2_qqzz,b3_ggzz,b3_qqzz,l1_zx,l2_zx,mean_hig,mean_hc,n1_hig,n1_hc,n2_hig,n2_hc,nevt_hig,nevt_ggzz,nevt_hc,nevt_qqzz,nevt_zx,weight,width_hig,width_hc -n _cH_unbinned2d roofit_unbinned2d.txt | tee fit.log

# 0-jet: BDT>0.3
combineCards.py HP=../hig0218_bdt1j0.70-1.00_hignorm1.2/roofit_unbinned2d.txt MP=../hig0218_bdt1j0.40-0.70_hignorm1.2/roofit_unbinned2d.txt LP=../hig0218_bdt1j0.00-0.40_hignorm1.2/roofit_unbinned2d.txt SR0j=../hig0218_bdt0j0.30_hignorm1.2/roofit_unbinned2d.txt > roofit_unbinned2d.txt
combine -M AsymptoticLimits -t -1 --expectSignal 1 --saveWorkspace --freezeParameters a1_hig,a1_hc,a2_hig,a2_hc,b1_ggzz,b1_qqzz,b2_ggzz,b2_qqzz,b3_ggzz,b3_qqzz,l1_zx,l2_zx,mean_hig,mean_hc,n1_hig,n1_hc,n2_hig,n2_hc,nevt_hig,nevt_ggzz,nevt_hc,nevt_qqzz,nevt_zx,weight,width_hig,width_hc -n _cH_unbinned2d roofit_unbinned2d.txt | tee fit.log
