from ROOT import *
import numpy as np
from array import array




file = TFile.Open('higgsCombinetest.MultiDimFit.mH1200.root','READ')
print file

tree = file.Get("limit")

Testhist = TH1F('t','t',100,-1,1)

BtaggedMass = TH1F('likelihood', 'likelihood', 500,0,5000)

for event in tree:
    BtaggedMass.Fill(event.r, event.deltaNLL)

OutputFilename = "Likelihoodscan.pdf"
OutputFile = TFile(OutputFilename, "RECREATE")

OutputFile.Append(BtaggedMass)
#OutputFile.Append(Testhist)
OutputFile.Write()

#file = TFile.Open('../AnalysisOutput/80X/ExoDiBosonAnalysis.QCD_Pt_All.root','READ')
#print file

#tree = file.Get("tree")

#Testhist = TH1F('t','t',100,-1,1)

#Mass = TH1F('MVV', 'MVV', 4000,1000,5000)

#for event in tree:
    #print "lumi : "+str(event.lumiweight)
    #print "pu   : "+str(event.puweight)
    #print "b-tag: "+str(event.btagweight)
    
    #print event.weight
    #Mass.Fill(event.MVV,event.weight)
            
            
#Mass.Scale(35867.)
#OutputFilename = "../DijetCombineLimitCode/BulkGtoZZ_bb_QCD.root"
#OutputFile = TFile(OutputFilename, "RECREATE")

#OutputFile.Append(Mass)
##OutputFile.Append(Testhist)
#OutputFile.Write()
