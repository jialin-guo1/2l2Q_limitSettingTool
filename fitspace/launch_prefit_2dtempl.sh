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
root -b -q /home/pku/licq/cH/zz/fit/fitspace/ws2d_maker.cxx\("$2"\)