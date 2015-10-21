# ExoDiBosonAnalysis

You first need to set up the SFrame Framework as described here:
https://wiki-zeuthen.desy.de/ATLAS/Projects/TopPhysicsInternal/AnalysisFramework/Tutorial 
(current tag is SFrame-04-00-01/)
In order to run SFrame you need a working version ROOT (setting up the CMSSW enviroment will do, CMSSW_7_4_X with X>1)
After sourcing SFrame 

cd SFrame
source setup.sh

You need to create a new package

sframe_new_package.sh ExoDiBosonAnalysis

in order to let SFrame now about the directory. Your package needs to have the same name as the repository your checking out 
(ExoDiBosonAnalysis). You can then move on to checking out the code.
Then you should be able to compile

make clean && make 

and run

sframe_main config/VV_HP.xml. 
