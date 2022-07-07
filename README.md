# Setup

1. Setup combine

  ```bash
  export SCRAM_ARCH=slc7_amd64_gcc700
  cmsrel CMSSW_10_2_13
  cd CMSSW_10_2_13/src
  cmsenv
  git clone https://github.com/cms-analysis/HiggsAnalysis-CombinedLimit.git HiggsAnalysis/CombinedLimit
  cd HiggsAnalysis/CombinedLimit
  cd $CMSSW_BASE/src/HiggsAnalysis/CombinedLimit
  git fetch origin
  git checkout v8.2.0
  scramv1 b clean; scramv1 b # always make a clean build
  ```

2. Get the custom tool for datacard creation and limit computation

  ```bash
  cd $CMSSW_BASE/src
  git clone git@github.com:jialin-guo1/2l2q_limitsettingtool.git -b develop
  ```

