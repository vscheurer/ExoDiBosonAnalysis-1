import os
import glob
import math
import array
import ROOT
import ntpath
import sys
import subprocess
import time
import numpy
from subprocess import Popen
from optparse import OptionParser
from array import array

from ROOT import gROOT, TPaveLabel, gStyle, gSystem, TGaxis, TStyle, TLatex, TString, TF1,TFile,TLine, TLegend, TH1D,TH1F,TH2D,THStack,TChain, TCanvas, TMatrixDSym, TMath, TText, TPad

from array import array

#parser = OptionParser()

#parser.add_option('--filename', action="store",type="string",dest = "filename",default="../config/BulkWW_M1000.xml")
#parser.add_option('--outname',action="store",type="string",dest="outname",default="N")
#parser.add_option('--s',action="store",type="string",dest="suffix",default="")

#(options, args) = parser.parse_args()



def write(pdfset,mass,model,sb=0):
    VV = 'VV'
    suffix = ''
    if model.find('BulkWW')!=-1:
        suffix = 'BulkGravToWW'
    if model.find('BulkZZ')!=-1:
        suffix = 'BulkGravToZZToZhadZhad'
    if model.find('Zprime')!=-1:
        suffix = 'ZprimeToWW'
    if model.find('Wprime')!=-1:
        suffix = 'WprimeToWZToWhadZhad'
    if model.find('QstarQW')!=-1:
        suffix = 'QstarToQW'
        VV ='qV'
    if model.find('QstarQZ')!=-1:
        suffix = 'QstarToQZ' 
        VV= 'qV'
        
    name = '../config/'+model+"_M"+str(int(mass))+".xml"
    if sb:
        name = '../config/'+model+"_M"+str(int(mass))+"_SB.xml"
        VV +='_SBtest'
    f = open(name,"w")
    f.write('<?xml version="1.0" encoding="UTF-8"?>\n')
    f.write('<!DOCTYPE JobConfiguration PUBLIC "" "JobConfig.dtd">\n')
    f.write('<JobConfiguration JobName="exovvJob" OutputLevel="INFO">\n')
    f.write('<Library Name="libGoodRunsLists" />\n')
    f.write('<Library Name="libLHAPDF"/>\n')
    f.write('<Library Name="libExoDiBosonAnalysis" />\n')

    f.write('<Package Name="SFrameCore.par" />\n')
    f.write('<Package Name="ExoDiBosonAnalysis.par" />\n')
      
    f.write('<Cycle Name="ExoDiBosonAnalysis" OutputDirectory="../AnalysisOutput/80X/SignalMC/" PostFix="" ProofServer="lite" ProofWorkDir="" RunMode="LOCAL" TargetLumi="1.0">\n')
    
    if model.find('Qstar')==-1:
        f.write('<InputData Lumi="0.0" NEventsMax="-1" NEventsSkip="0" SkipValid="False" Version="'+VV+'" Type="'+model+'_13TeV_'+str(int(mass))+'GeV">\n')
        f.write('  <In FileName="root://t3dcachedb.psi.ch:1094//pnfs/psi.ch/cms/trivcat/store/t3groups/uniz-higgs/Spring16/'+suffix+'_narrow_M-'+str(int(mass))+'_13TeV-madgraph_RunIISpring16MiniAODv2_PUSpring16RAWAODSIM_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/EXOVVTree_'+suffix+'_narrow_M-'+str(int(mass))+'_13TeV-madgraph_RunIISpring16MiniAODv2_PUSpring16RAWAODSIM_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1_1.root" Lumi="1.0"/>  \n')
    else:
        f.write('<InputData Lumi="0.0" NEventsMax="-1" NEventsSkip="0" SkipValid="False" Version="'+VV+'" Type="'+model+'_13TeV_'+str(int(mass))+'GeV">\n')
        f.write('  <In FileName="dcap://t3se01.psi.ch:22125//pnfs/psi.ch/cms/trivcat/store/t3groups/uniz-higgs/Spring16/'+suffix+'_M_'+str(int(mass))+'_TuneCUETP8M1_13TeV_pythia8_GEN-SIM_DIGI80X_RECO80X_MiniAODv2_80X_MiniAODv2_PUSpring16RAWAODSIM/EXOVVTree_'+suffix+'_M_'+str(int(mass))+'_TuneCUETP8M1_13TeV_pythia8_GEN-SIM_DIGI80X_RECO80X_MiniAODv2_80X_MiniAODv2_PUSpring16RAWAODSIM_1.root" Lumi="1.0"/> \n') 
        
    f.write('<InputTree Name="ntuplizer/tree" /> \n')   
    f.write('      <OutputTree Name="tree" />    \n')
    f.write('    </InputData>                    \n')

    
    
    f.write('<UserConfig>\n')                    
                   
    f.write('<!--general settings-->                     \n')
    f.write('<Item Name="InputTreeName" Value="tree" />  \n')
    f.write('<Item Name="OutputTreeName" Value="tree" /> \n')
    f.write('<Item Name="isSignal" Value="true" />       \n')
    f.write('<Item Name="runOnMC" Value="true" />        \n')
    f.write('<Item Name="usePuppiSD" Value="true" />     \n')
    f.write('<Item Name="GenStudies" Value="false" />    \n')
    if model.find("Qstar")==-1:
        if sb:
            f.write('<Item Name="Channel" Value="jetmassSidebandVVdijet" />     \n')
        else:
            f.write('<Item Name="Channel" Value="VVdijet" />     \n')
    else:
        if sb:
            f.write('<Item Name="Channel" Value="jetmassSidebandqVdijet" />     \n')
        else:
            f.write('<Item Name="Channel" Value="qVdijet" />     \n')
    f.write('<Item Name="MassWindow" Value="VV" />       \n')
    f.write('<Item Name="Trigger" Value="false" />       \n')
    f.write('<Item Name="applyFilters" Value="false" />  \n')
    f.write('                                            \n')
    f.write('<!--leptonic selections-->                  \n')
    f.write('<Item Name="LeptPtCut" Value="30" />        \n')
    f.write('<Item Name="LeptEtaCut" Value="2.1" />      \n')
    f.write('<Item Name="AleptPtCut" Value="30" />       \n')
    f.write('<Item Name="AleptEtaCut" Value="2.4" />     \n')
    f.write('<Item Name="METCut" Value="30" />           \n')
    f.write('                                            \n')
    f.write('<!--jet selections-->                       \n')
    f.write('                                            \n')
    f.write('<Item Name="dEtaCut" Value="1.3" />         \n')
    f.write('<Item Name="MjjCut" Value="1055.0" />        \n')
    f.write('<Item Name="JetPtCutLoose" Value="30." />   \n')
    f.write('<Item Name="JetPtCutTight" Value="200." />  \n')
    f.write('<Item Name="JetEtaCut" Value="2.5" />       \n')
    f.write('<Item Name="Tau21Cut" Value="true" />       \n')
    f.write('<Item Name="Tau21HPLow" Value="0.00" />     \n')
    f.write('<Item Name="Tau21HPHigh" Value="0.40" />    \n') 
    f.write('<Item Name="Tau21Low" Value="0.40" />       \n')
    f.write('<Item Name="Tau21High" Value="0.75" />      \n')
    f.write('                                            \n')
    f.write('<Item Name="mWLow" Value="65." />           \n')
    f.write('<Item Name="mWHigh" Value="85." />          \n')
    f.write('<Item Name="mZLow" Value="85." />           \n')
    f.write('<Item Name="mZHigh" Value="105." />         \n')
    f.write('                                            \n')
    f.write('<Item Name="xSec" Value="1." />             \n')
    f.write('<Item Name="genEvents" Value="1." />        \n')
    f.write('<Item Name="Lumi" Value="1." />             \n')
    f.write('<Item Name="PUdata" Value="results/PU/DataPUDistribution.root" /> \n')
    f.write('<Item Name="JSONfile" Value="No" />\n')
    f.write('<Item Name="BTagEff4vetoData" Value="data/TT_CT10_TuneZ2star_8TeV-powheg-tauola_AK5PF_CSVM_bTaggingEfficiencyMap.root" />  \n')
    f.write('<Item Name="BTagEff4fatjetData" Value="data/BtagEfficienciesMap_fatjets_Wp.root" />  \n')
    f.write('<Item Name="BTagEff4subjetData" Value="data/btag-efficiency-maps.root" />           \n')
    f.write('<Item Name="PUPPIJEC" Value="/mnt/t3nfs01/data01/shome/thaarres/EXOVVAnalysisRunII/PuppiSoftdropMassCorr_80X/PuppiSoftdropMassCorr/weights/puppiCorr.root" /> \n')
    f.write('<Item Name="PUPPIJMR" Value="/mnt/t3nfs01/data01/shome/thaarres//EXOVVAnalysisRunII/ExoDiBosonAnalysis/data/jetmassResolution.root" /> \n')
    f.write('<Item Name="scaleUncPar" Value="" /> <!-- -1 = NoScaling   0/1 = JMS UP/DOWN   2/3 =JMR UP/DOWN 4/5 = JES UP/DOWN 6/7 = JER UP/DOWN  -->  \n')
    f.write('<Item Name="JMS" Value="0.999" />  \n')
    f.write('<Item Name="JMSunc" Value="0.004" />  \n')
    f.write('<Item Name="JMR" Value="1.079" />      \n')
    f.write('<Item Name="JMRunc" Value="0.105" />    \n')
    #f.write('<Item Name="PDFSET" Value="'+str(int(pdfset))+'" />    \n')
    #f.write('<Item Name="wPDFname" Value="wpdf_M'+str(int(mass))+'_'+model+'" />  \n')
    
    f.write('  </UserConfig>  \n')
    f.write('</Cycle>  \n')
    f.write('</JobConfiguration>\n')
    
    
    
    
    
    
    
    
#######################################
############ Main Code ################
#######################################

if __name__== '__main__':
  
  masses=[800,1000,1200,1400,1600,1800,2000,2500,3000,3500,4000,4500]
  models=["WprimeWZ","ZprimeWW","BulkWW","BulkZZ"]
  altmodels=["QstarQW","QstarQZ"]
  #for model in models:
    #for m in masses:
      #write(263400,m,model)
  
  massesalt=[800,1000,1200,1400,1600,1800,2000,2500,3000,3500,4000,4500,5000,5500,6000,6500,7000,7500]
  
  for amodel in altmodels:
      for am in massesalt:
          write(263400,am,amodel,1)
  
