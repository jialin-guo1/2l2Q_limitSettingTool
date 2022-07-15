#!/bin/bash

BASEDIR=$1

source /cvmfs/cms.cern.ch/cmsset_default.sh

cd /home/pku/licq/cH/zz/fit
cd CMSSW_10_2_27/src
eval `scram runtime -sh`
cd -

cd fitspace
if [ ! -d $BASEDIR ]; then
    mkdir $BASEDIR
fi
cd $BASEDIR

# run fit
combine -M AsymptoticLimits -t -1 --expectSignal 1 --saveWorkspace --freezeParameters a1_hig,a1_hc,a2_hig,a2_hc,b1_ggzz,b1_qqzz,b2_ggzz,b2_qqzz,b3_ggzz,b3_qqzz,l1_zx,l2_zx,mean_hig,mean_hc,n1_hig,n1_hc,n2_hig,n2_hc,nevt_hig,nevt_ggzz,nevt_hc,nevt_qqzz,nevt_zx,weight,width_hig,width_hc -n _cH_unbinned2d roofit_unbinned2d.txt | tee fit.log