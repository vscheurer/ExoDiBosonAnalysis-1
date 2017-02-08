#!bin/bash

runs=("D" "E" "F" "G" "H")
#lumi=(0.58 0.17 0.30 0.26 0.10 0.12 0.14)
# lumi for JEtHT dataset using baseline trigger PFHT650 and PFJet320
lumi=(0.30 0.26 0.10 0.12 0.14)
l=0
# #runs=("G" "H")
# for r in "${runs[@]}"
# do
#     python doTriggerEffPlots.py --filename ExoDiBosonAnalysis.JetHT_Run2016${r}_noTrigger_data_sideband_doubleTag.root --isMC False -s True --run $r --lumi ${lumi[$l]}
#     l=$l+1
# done
lumiAll=0.58+0.17+0.30+0.26+0.10+0.12+0.14
#lumiAll=1.67
#python doTriggerEffPlots.py --filename Data_VVsideband_All_noTrigger.root --isMC False -s True --run All --lumi $lumiAll

# for single muon samples:

runs=("B" "C" "D" "E" "F" "G" "H")
#lumi for Single muon dataset using no baseline trigger
lumi=(5.8 2.5 4.4 4.1 3.2 7.7 8.9)
# lumi for single muon using HLT_Mu50 baseline trigger
lumi=(3.2 2.3 4.4 4.1 3.2 7.7 8.9)
l=0
lumiAll2=33.8
for r in "${runs[@]}"
do
    python doTriggerEffPlots.py --filename ExoDiBosonAnalysis.SingleMuon_Run2016${r}_triggerStudies_BaseHLT_Mu50.root --isMC False -s True --run $r --lumi ${lumi[$l]} --plot turnOn
    l=$l+1
done
python doTriggerEffPlots.py --filename ExoDiBosonAnalysis.SingleMuon_Run2016All_triggerStudies_BaseHLT_Mu50.root --isMC False -s True --run All --lumi $lumiAll2 --plot turnOn
