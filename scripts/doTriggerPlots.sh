#!bin/bash

runs=("D" "E" "F" "G" "H")
lumi=(4.4 4.1 3.2 7.7 8.9)
l=0
#runs=("G" "H")
for r in "${runs[@]}"
do
    python doTriggerEffPlots.py --filename ExoDiBosonAnalysis.JetHT_Run2016${r}_noTrigger_data_sideband_doubleTag.root --isMC False -s True --run $r --lumi ${lumi[$l]}
    l=$l+1
done
