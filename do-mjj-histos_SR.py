# for data SB: python do-mjj-histos_SR.py --dataSB >> results/Data_VVdijet_SB.log
# for anything MC just leave our --dataSB and uncomment one of the filenames specifiyng which sample to use

from optparse import OptionParser
import os,commands, os.path
import sys
from ROOT import *
import math
import time
from array import *
# import CMS_lumi, tdrstyle
import copy
# ---------------------------------------------------------------------------------------------------------------------------
def write(fname, histolist):
    """Write the new histogram to disk"""
    base = fname
    outfname = "results/" + base + ".root"
    # outfname = base + ".root"
    print "Saving file %s " %outfname
    fout = TFile(outfname,"RECREATE")
    for h in histolist:
      h.Write()
    fout.Close()
# ---------------------------------------------------------------------------------------------------------------------------
argv = sys.argv
parser = OptionParser()   
parser.add_option("-L", "--lumi", dest="lumi", default=36400,
                              help="Set lumi")
parser.add_option("--dataSB", dest="dataSB", action="store_true",default=False)

(opts, args) = parser.parse_args(argv)  

path = "/shome/dschafer/AnalysisOutput/80X/Bkg/Summer16/"
rebin = 1
data_filename = "Data_VVdijet_SB_36400ifb.root"
#data_filename = "Data_qVdijet_SB_36400ifb.root"
data_path = "/shome/dschafer/AnalysisOutput/80X/Data/"



#filename = "QCD_Spring16_Ptbinned_pythia8_qVdijet.root"
#filename = "QCD_Spring16_Ptbinned_pythia8_qVdijet_SB_test.root"
#filename = "QCD_Spring16_madgraph_pythia8_VVdijet.root"
#filename = "QCD_Spring16_madgraph_pythia8_VVdijet_SB.root"
#filename = "QCD_Spring16_madgraph_pythia8_qVdijet.root"
#filename = "QCD_Spring16_madgraph_pythia8_qVdijet_SB.root"
#filename = "ExoDiBosonAnalysis.QCD_herwig_cgalloni_VVdijet.root"
#filename = "ExoDiBosonAnalysis.QCD_herwig_cgalloni_VVdijet_SB.root"
#filename = "ExoDiBosonAnalysis.QCD_herwig_cgalloni_qVdijet.root"
#filename = "ExoDiBosonAnalysis.QCD_herwig_cgalloni_qVdijet_SB.root"
filename = "QCD_pythia8_qVdijet_SB.root"
filename = "QCD_pythia8_qVdijet_SR.root"
filename = "QCD_pythia8_qVdijet_SB_test.root"

# ---------------------------------------------------------------------------------------------------------------------------  

# cmd = "rm /shome/thaarres/EXOVVAnalysisRunII/CMSSW_7_1_5/src/DijetCombineLimitCode/input/*.root"
# print cmd
# os.system(cmd)

print path
gROOT.SetBatch(kTRUE)
      
i =0
histolist = []
nEvents = []
gen = "pythia8"
if filename.find("madgraph")!=-1:
    gen = "madgraph_pythia8"
if filename.find("herwig")!=-1:
    gen= "herwig"
name = "QCD_"+gen+"_VV"
if filename.find("qV")!=-1:
    name = "QCD_"+gen+"_qV"
if path.find("Summer16")!=-1:
    name +="_summer16"
if opts.dataSB:
    name = "Data_VVdijet" #_test40GeV"
    if data_filename.find("qV")!=-1:
        name = "Data_qVdijet"
    filename = data_filename
    path = data_path
for root, _, files in os.walk(path):
  for f in files:
    fullpath = os.path.join(root, f)
    if f.find(filename)!=-1:
        print fullpath
        #if not fullpath.find(".qV.root")!=-1:
            #continue
        # if not fullpath.find("Qstar")!=-1:
        #   continue
        # print "+++++++++++"
        print "Working on  file %s" %fullpath
        if fullpath.find("QCD")!=-1:
            lumi = opts.lumi
        if fullpath.find("Data")!=-1:
            lumi = 1.
            #name1 = fullpath.split(".")[1]
            #name = name1.split("_")[0]
            #name += "_" + name1.split("_")[1]
            #name += "_SR"
        #if fullpath.find("_VV")!=-1: 
            #name = "QCD_VV"
        #if fullpath.find("_qV")!=-1: 
         #   name = "QCD_qV"
        #elif fullpath.find("DATA")!=-1:
            #name1 = fullpath.split(".")[1]
            #name = name1.split("_")[0]
        #if fullpath.find("_VV")!=-1 or (fullpath.find("QCD")!=-1 and fullpath.find("qV")==-1): 
            #name+= "_VV"
        #if fullpath.find("_qV")!=-1: 
            #name+= "_qV"
        if fullpath.find("SB")!=-1:
            #name1 = fullpath.split(".")[1]
            #name = name1.split("_")[0]
            name+= "_SB_test2"  
            #lumi = 1.
        #else:
            #name = fullpath.split(".")[1]+'.'+fullpath.split(".")[2]
            #name = name.split(".")[0]
            #lumi = 1.
        print "Will save to filename %s" %name
        filetmp = TFile.Open(fullpath,"READ") 
        intree = filetmp.Get("tree")
        print "Using lumi = %s" %lumi
    
        histolist=[]
        nEvents =[]

        VVHP = TH1F('DijetMassHighPuriVV','DijetMassHighPuriVV',7000,0,7000)
        WWHP = TH1F('DijetMassHighPuriWW','DijetMassHighPuriWW',7000,0,7000)
        WZHP = TH1F('DijetMassHighPuriWZ','DijetMassHighPuriWZ',7000,0,7000)
        ZZHP = TH1F('DijetMassHighPuriZZ','DijetMassHighPuriZZ',7000,0,7000)
        VVLP = TH1F('DijetMassLowPuriVV','DijetMassLowPuriVV',7000,0,7000)
        WWLP = TH1F('DijetMassLowPuriWW','DijetMassLowPuriWW',7000,0,7000)
        WZLP = TH1F('DijetMassLowPuriWZ','DijetMassLowPuriWZ',7000,0,7000)
        ZZLP = TH1F('DijetMassLowPuriZZ','DijetMassLowPuriZZ',7000,0,7000)
        qVHP = TH1F('DijetMassHighPuriqV','DijetMassHighPuriqV',8000,0,8000)
        qWHP = TH1F('DijetMassHighPuriqW','DijetMassHighPuriqW',8000,0,8000)
        qZHP = TH1F('DijetMassHighPuriqZ','DijetMassHighPuriqZ',8000,0,8000)
        qVLP = TH1F('DijetMassLowPuriqV','DijetMassLowPuriqV'  ,8000,0,8000)
        qWLP = TH1F('DijetMassLowPuriqW','DijetMassLowPuriqW'  ,8000,0,8000)
        qZLP = TH1F('DijetMassLowPuriqZ','DijetMassLowPuriqZ'  ,8000,0,8000)
        VVNP = TH1F('DijetMassNoPuriVV','DijetMassNoPuriVV',7000,0,7000)
        WWNP = TH1F('DijetMassNoPuriWW','DijetMassNoPuriWW',7000,0,7000)
        WZNP = TH1F('DijetMassNoPuriWZ','DijetMassNoPuriWZ',7000,0,7000)
        ZZNP = TH1F('DijetMassNoPuriZZ','DijetMassNoPuriZZ',7000,0,7000)
        qVNP = TH1F('DijetMassNoPuriqV','DijetMassNoPuriqV',7000,0,7000)
        qWNP = TH1F('DijetMassNoPuriqW','DijetMassNoPuriqW',7000,0,7000)
        qZNP = TH1F('DijetMassNoPuriqZ','DijetMassNoPuriqZ',7000,0,7000)
        
        
        if fullpath.find("q")==-1:
            histolist.append(VVHP)
            histolist.append(WWHP)
            histolist.append(WZHP)
            histolist.append(ZZHP)
            histolist.append(VVLP)
            histolist.append(WWLP)
            histolist.append(WZLP)
            histolist.append(ZZLP)
            nEvents = [0,0,0,0,0,0,0,0]
            #histolist.append(VVNP)
            #histolist.append(WWNP)
            #histolist.append(WZNP)
            #histolist.append(ZZNP)
        else:
            histolist.append(qVHP)
            histolist.append(qWHP)
            histolist.append(qZHP)
            histolist.append(qVLP)
            histolist.append(qWLP)
            histolist.append(qZLP)
            nEvents = [0,0,0,0,0,0]
            #histolist.append(qVNP)
            #histolist.append(qWNP)
            #histolist.append(qZNP)
        
        mw_min_SB = 20. # old value = 20.
        mw_max_SB = 65. # old value = 65.
        
        mw_min_SB_qVdown = 20. # old value = 20.
        mw_max_SB_qVdown = 65. # old value = 65.
        mw_min_SB_qVup = 105.
        mw_max_SB_qVup = 200.

        for event in intree:
      
               
               # VVdijet signal region :
            if fullpath.find("SB")==-1 and fullpath.find("q")==-1:
                    if ( event.MVV < 995.0): continue
                    if event.jet_puppi_tau2tau1_jet2 <= 0.40 and event.jet_puppi_tau2tau1_jet1 <= 0.40 :
                        VVHP.Fill(event.MVV,event.weight)
                        if (65. <= event.jet_puppi_softdrop_jet1 <= 85. and 65. <= event.jet_puppi_softdrop_jet2 <= 85.) :
                            WWHP.Fill(event.MVV,event.weight) #WWHP
                        if (85. < event.jet_puppi_softdrop_jet1 <= 105. and 85. < event.jet_puppi_softdrop_jet2 < 105.) :
                            ZZHP.Fill(event.MVV,event.weight) #ZZHP
                        if ( (85 < event.jet_puppi_softdrop_jet1 <= 105. and 65. <= event.jet_puppi_softdrop_jet2 <= 85.) or (85 < event.jet_puppi_softdrop_jet2 <= 105. and 65. <= event.jet_puppi_softdrop_jet1 <= 85.) ) :
                            WZHP.Fill(event.MVV,event.weight) #WZHP
          
                    if (event.jet_puppi_tau2tau1_jet2 <= 0.40 and 0.40 < event.jet_puppi_tau2tau1_jet1 <= 0.75) or (event.jet_puppi_tau2tau1_jet1 <= 0.40 and 0.40 < event.jet_puppi_tau2tau1_jet2 <= 0.75) :
                        VVLP.Fill(event.MVV,event.weight)
                        if (65 <= event.jet_puppi_softdrop_jet1 <= 85. and 65 <= event.jet_puppi_softdrop_jet2 < 85.) :
                            WWLP.Fill(event.MVV,event.weight) #WWLP
                        if (85 < event.jet_puppi_softdrop_jet1 <= 105. and 85. < event.jet_puppi_softdrop_jet2 <= 105.) :
                            ZZLP.Fill(event.MVV,event.weight) #ZZLP
                        if ( (85 < event.jet_puppi_softdrop_jet1 <= 105. and 65. <= event.jet_puppi_softdrop_jet2 < 85.) or (85 < event.jet_puppi_softdrop_jet2 <= 105. and 65. <= event.jet_puppi_softdrop_jet1 < 85.) ) :
                            WZLP.Fill(event.MVV,event.weight) #WZLP
               
               # VVdijet sideband region: (technically here WW histos contain the events where 1W is found, while ZZ contains the histos where 1Z is found!)
            if fullpath.find("SB")!=-1 and fullpath.find("q")==-1:
                   if ( event.MVV < 1055.0): continue
                   if (5000 < event.MVV < 6300):
                       print event.MVV
                       print event.jet_puppi_softdrop_jet1
                       print event.jet_puppi_softdrop_jet2
                       print event.jet_puppi_tau2tau1_jet1
                       print event.jet_puppi_tau2tau1_jet2
                   #=== play with jet mass window for sideband region ==============================
                   if  (mw_min_SB > event.jet_puppi_softdrop_jet1 or mw_min_SB > event.jet_puppi_softdrop_jet2): continue
                   if  (mw_max_SB < event.jet_puppi_softdrop_jet1 and mw_max_SB < event.jet_puppi_softdrop_jet2): continue
                   #================================================================================
                   if event.jet_puppi_tau2tau1_jet1 <= 0.40 and event.jet_puppi_tau2tau1_jet2<=0.40:
                       VVHP.Fill(event.MVV,event.weight)
                       nEvents[0]+=1
                       if (5000 < event.MVV < 6300): print "passed HP"
                       if ((65. <= event.jet_puppi_softdrop_jet1 <= 85.) or (65. <= event.jet_puppi_softdrop_jet2 <= 85.)) :
                            WWHP.Fill(event.MVV,event.weight) #WWHP
                            nEvents[1]+=1
                       if ((85. < event.jet_puppi_softdrop_jet1 <= 105.) or  (85. < event.jet_puppi_softdrop_jet2 < 105.)) :
                            ZZHP.Fill(event.MVV,event.weight) #ZZHP
                            nEvents[3]+=1
                   if (event.jet_puppi_tau2tau1_jet2 <= 0.40 and 0.40 < event.jet_puppi_tau2tau1_jet1 <= 0.75) or (event.jet_puppi_tau2tau1_jet1 <= 0.40 and 0.40 < event.jet_puppi_tau2tau1_jet2 <= 0.75) :
                       VVLP.Fill(event.MVV,event.weight)
                       nEvents[4]+=1
                       if (5000 < event.MVV < 6300): print "passed LP"
                       if ((65. <= event.jet_puppi_softdrop_jet1 <= 85.) or (65. <= event.jet_puppi_softdrop_jet2 <= 85.)) :
                            WWLP.Fill(event.MVV,event.weight) #WWLP
                            nEvents[5]+=1
                       if ((85. < event.jet_puppi_softdrop_jet1 <= 105.) or  (85. < event.jet_puppi_softdrop_jet2 < 105.)) :
                            ZZLP.Fill(event.MVV,event.weight) #ZZLP
                            nEvents[7]+=1
                   if (5000 < event.MVV < 6300): print "======================================="
     
            # qV sideband (fill histos for HP/LP region):
            
            if name.find("SB")!=-1 and name.find("q")!=-1:
                    if ( event.MVV < 1055.): continue
                    #if ( mw_min_SB_qVdown > event.jet_puppi_softdrop_jet1 or mw_min_SB_qVdown > event.jet_puppi_softdrop_jet2):
                        #continue
                    #if (event.jet_puppi_softdrop_jet1 > mw_max_SB_qVdown and event.jet_puppi_softdrop_jet1 < mw_min_SB_qVup):
                        #continue
                    #if (event.jet_puppi_softdrop_jet2 > mw_max_SB_qVdown and event.jet_puppi_softdrop_jet2 < mw_min_SB_qVup):
                        #continue
                    #if ( mw_max_SB_qVup < event.jet_puppi_softdrop_jet1 or mw_max_SB_qVup < event.jet_puppi_softdrop_jet2):
                        #continue
                    #if ( event.jet_puppi_tau2tau1_jet1 <= 0.40):
                        #qVHP.Fill(event.MVV,event.weight)
                        #nEvents[0]+=1
                    #if ( 0.40 <event.jet_puppi_tau2tau1_jet1 <= 0.75):
                        #qVLP.Fill(event.MVV,event.weight)
                        #nEvents[3]+=1
                    #===================== qV try new sideband definition: leave q jet as it is, and require V jet to have a mass between 105-200 GeV================
                    if ( event.jet_puppi_tau2tau1_jet1 <= 0.40 or event.jet_puppi_tau2tau1_jet2 <= 0.40):
                        if event.jet_puppi_tau2tau1_jet1<= 0.40:
                            if (105 < event.jet_puppi_softdrop_jet1 < 200):
                                qVHP.Fill(event.MVV, event.weight)
                                continue
                        if event.jet_puppi_tau2tau1_jet2 <= 0.40:
                            if (105 < event.jet_puppi_softdrop_jet2 < 200):
                                qVHP.Fill(event.MVV, event.weight)
                                
                    
                    if ((0.40 < event.jet_puppi_tau2tau1_jet1 <= 0.75) or (0.40 < event.jet_puppi_tau2tau1_jet2 <= 0.75)):
                        if 0.40 < event.jet_puppi_tau2tau1_jet1<= 0.75:
                            if (105 < event.jet_puppi_softdrop_jet1 < 200):
                                qVLP.Fill(event.MVV, event.weight)
                                continue
                        if 0.40 < event.jet_puppi_tau2tau1_jet2 <= 0.75:
                            if (105 < event.jet_puppi_softdrop_jet2 < 200):
                                qVLP.Fill(event.MVV, event.weight)
  
                        
                        
            # qV signal region (fill histos for W/Z and HP/LP):
            elif name.find("q")!=-1 and name.find("SB")==-1:
                
                if ( event.MVV < 1035.): continue
                if ( (65. <= event.jet_puppi_softdrop_jet2 <= 105. and event.jet_puppi_tau2tau1_jet2 <= 0.40) or (65. <= event.jet_puppi_softdrop_jet1 <= 105. and event.jet_puppi_tau2tau1_jet1 <= 0.40)):
                    qVHP.Fill(event.MVV,event.weight) #qVHP
                    nEvents[0]+=1
                if ( (65. <= event.jet_puppi_softdrop_jet2 <= 105. and 0.40 <event.jet_puppi_tau2tau1_jet2 <= 0.75) or (65. <= event.jet_puppi_softdrop_jet1 <= 105. and 0.40 <event.jet_puppi_tau2tau1_jet1 <= 0.75)):
                    qVLP.Fill(event.MVV,event.weight) #qVLP
                    nEvents[3]+=1

                if ( (85. < event.jet_puppi_softdrop_jet2 <= 105. and event.jet_puppi_tau2tau1_jet2 <= 0.40) or (85. < event.jet_puppi_softdrop_jet1 <= 105. and event.jet_puppi_tau2tau1_jet1 <= 0.40)):
                    qZHP.Fill(event.MVV,event.weight) #qZHP
                    nEvents[1]+=1
                if ( (85. < event.jet_puppi_softdrop_jet2 <= 105. and 0.40 <event.jet_puppi_tau2tau1_jet2 <= 0.75) or (85. < event.jet_puppi_softdrop_jet1 <= 105. and 0.40 <event.jet_puppi_tau2tau1_jet1 <= 0.75)):
                    qZLP.Fill(event.MVV,event.weight) #qZLP
                    nEvents[5]+=1
                if ( (65. <= event.jet_puppi_softdrop_jet2 <= 85. and event.jet_puppi_tau2tau1_jet2 <= 0.40) or (65. <= event.jet_puppi_softdrop_jet1 <= 85. and event.jet_puppi_tau2tau1_jet1 <= 0.40)):
                    qWHP.Fill(event.MVV,event.weight) #qWHP
                    nEvents[2]+=1
                if ( (65. <= event.jet_puppi_softdrop_jet2 <= 85. and 0.40 <event.jet_puppi_tau2tau1_jet2 <= 0.75) or (65. <= event.jet_puppi_softdrop_jet1 <= 85. and 0.40 <event.jet_puppi_tau2tau1_jet1 <= 0.75)):
                    qWLP.Fill(event.MVV,event.weight) #qWLP
                    nEvents[4]+=1
                
        i=0        
        for n in nEvents:
            print histolist[i].GetName()+": "+str(n)
            i+=1
        for h in histolist:
            print "Scaling histogram to %f pb"%lumi
            print "Saving histogram %s" %h.GetName()
            h.Scale(lumi)
        write(name,histolist)
        filetmp.Close()
        del intree
        del histolist

