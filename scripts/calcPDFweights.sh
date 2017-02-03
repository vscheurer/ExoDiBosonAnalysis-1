#!/bin/bash

#"WprimeWZ","ZprimeWW","BulkWW","BulkZZ"
# mass=(800 1000 1200 1400 1600 1800 2000 2500 3000 3500 4000 4500)
# models=("ZprimeWW")

mass=(800 1000 1200 1400 1600 1800 2000 2500 3000 3500 4000 4500 5000 5500 6000 6500 7000 7500)
models=("QstarQW" "QstarQZ")

cd /mnt/t3nfs01/data01/shome/dschafer/ExoDiBosonAnalysis/

for mo in "${models[@]}"
do
    for m in "${mass[@]}"
    do
        sframe_main config/${mo}_M${m}.xml
    done
done
