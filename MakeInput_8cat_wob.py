from ROOT import *
import numpy as np
from array import array
import sys

mass = sys.argv[1]
tag =1.01
Mjjcut = 1050


HPcut = 0.35

if mass != 'QCD':
    #file = TFile.Open('/storage/jbod/dschaefer/AnalysisOutput/80X/SignalMC/Summer16/ExoDiBosonAnalysis.BulkZZ_13TeV_'+mass+'GeV.CV.root','READ')
    file = TFile.Open('ExoDiBosonAnalysis.test-'+mass+'.VV.VV.root','READ')
    print file

    tree = file.Get("tree")

    Testhist = TH1F('t','t',100,-1,1)
    nEvents =0
    BtaggedMass = TH1F('BtaggedMass_'+mass+'GeV', 'BtaggedMass_'+mass+'GeV', 4000,1000,5000)
    ZZHP = TH1F('ZZHP_'+mass+'GeV', 'ZZHP', 4000,1000,5000)
    ZZLP = TH1F('ZZLP_'+mass+'GeV', 'ZZLP', 4000,1000,5000)
    VVHP = TH1F('VVHP_'+mass+'GeV', 'VVHP', 4000,1000,5000)
    VVLP = TH1F('VVLP_'+mass+'GeV', 'VVLP', 4000,1000,5000)
    WZHP = TH1F('WZHP_'+mass+'GeV', 'WZHP', 4000,1000,5000)
    WZLP = TH1F('WZLP_'+mass+'GeV', 'WZLP', 4000,1000,5000)
    WWHP = TH1F('WWHP_'+mass+'GeV', 'WWHP', 4000,1000,5000)
    WWLP = TH1F('WWLP_'+mass+'GeV', 'WWLP', 4000,1000,5000)
    
    ZZHPBtagged = TH1F('ZZHPBtagged_'+mass+'GeV', 'ZZHP', 4000,1000,5000)
    
    WZHPBtagged = TH1F('WZHPBtagged_'+mass+'GeV', 'WZHP', 4000,1000,5000)
    
    WWHPBtagged = TH1F('WWHPBtagged_'+mass+'GeV', 'WWHP', 4000,1000,5000)
    
    ZZLPBtagged = TH1F('ZZLPBtagged_'+mass+'GeV', 'ZZHP', 4000,1000,5000)
    
    WZLPBtagged = TH1F('WZLPBtagged_'+mass+'GeV', 'WZHP', 4000,1000,5000)
    
    WWLPBtagged = TH1F('WWLPBtagged_'+mass+'GeV', 'WWHP', 4000,1000,5000)
      
    AllMass = TH1F('Allmass_'+mass+'GeV', 'WWLP', 4000,1000,5000)
   
    for event in tree:
        if event.MVV > Mjjcut:
            if event.jet_puppi_softdrop_jet1 > 85. and event.jet_puppi_softdrop_jet1 <=105. and event.jet_puppi_softdrop_jet2 > 85. and event.jet_puppi_softdrop_jet2 <=105.:
                if event.jet_puppi_tau2tau1_jet1 <=0.35 and event.jet_puppi_tau2tau1_jet2 <= 0.35:
                    
                        if (event.jet1_Hbbtag > tag and event.jet1_Hbbtag <1.1) or (event.jet2_Hbbtag > tag and event.jet2_Hbbtag < 1.1):
                            ZZHPBtagged.Fill(event.MVV, event.weight)
                            AllMass.Fill(event.MVV, event.weight)
                        else: 
                            ZZHP.Fill(event.MVV,event.weight)
                            AllMass.Fill(event.MVV, event.weight)
                else: 
                        if (event.jet_puppi_tau2tau1_jet1 <=0.35 and event.jet_puppi_tau2tau1_jet2 <= 0.75) or (event.jet_puppi_tau2tau1_jet1 <=0.75 and event.jet_puppi_tau2tau1_jet2 <= 0.35):
                            if (event.jet1_Hbbtag > tag and event.jet1_Hbbtag <1.1) or (event.jet2_Hbbtag > tag and event.jet2_Hbbtag < 1.1):
                                ZZLPBtagged.Fill(event.MVV, event.weight)
                                AllMass.Fill(event.MVV, event.weight)                              
                            else:
                                ZZLP.Fill(event.MVV,event.weight)
                                AllMass.Fill(event.MVV, event.weight)

            if event.jet_puppi_softdrop_jet1 >= 106. and event.jet_puppi_softdrop_jet1 <=105. and event.jet_puppi_softdrop_jet2 >= 106. and event.jet_puppi_softdrop_jet2 <=105.:
                if event.jet_puppi_tau2tau1_jet1 <=0.35 and event.jet_puppi_tau2tau1_jet2 <= 0.35:
                    
                        if (event.jet1_Hbbtag > tag and event.jet1_Hbbtag <1.1) or (event.jet2_Hbbtag > tag and event.jet2_Hbbtag < 1.1):
                            ZZHPBtagged.Fill(event.MVV, event.weight)
                            AllMass.Fill(event.MVV, event.weight)
                        else: 
                            VVHP.Fill(event.MVV,event.weight)
                            AllMass.Fill(event.MVV, event.weight)
                else: 
                        if (event.jet_puppi_tau2tau1_jet1 <=0.35 and event.jet_puppi_tau2tau1_jet2 <= 0.75) or (event.jet_puppi_tau2tau1_jet1 <=0.75 and event.jet_puppi_tau2tau1_jet2 <= 0.35):
                            if (event.jet1_Hbbtag > tag and event.jet1_Hbbtag <1.1) or (event.jet2_Hbbtag > tag and event.jet2_Hbbtag < 1.1):
                                ZZLPBtagged.Fill(event.MVV, event.weight)
                                AllMass.Fill(event.MVV, event.weight)                              
                            else:
                                VVLP.Fill(event.MVV,event.weight)
                                AllMass.Fill(event.MVV, event.weight)


            if event.jet_puppi_softdrop_jet1 >= 65. and event.jet_puppi_softdrop_jet1 <=85. and event.jet_puppi_softdrop_jet2 >= 65. and event.jet_puppi_softdrop_jet2 <=85.:
                if event.jet_puppi_tau2tau1_jet1 <=0.35 and event.jet_puppi_tau2tau1_jet2 <= 0.35:
                    
                        if (event.jet1_Hbbtag > tag and event.jet1_Hbbtag <1.1) or (event.jet2_Hbbtag > tag and event.jet2_Hbbtag < 1.1):
                            WWHPBtagged.Fill(event.MVV, event.weight)
                            AllMass.Fill(event.MVV, event.weight)
                        else: 
                            WWHP.Fill(event.MVV,event.weight)
                            AllMass.Fill(event.MVV, event.weight)
                else: 
                        if (event.jet_puppi_tau2tau1_jet1 <=0.35 and event.jet_puppi_tau2tau1_jet2 <= 0.75) or (event.jet_puppi_tau2tau1_jet1 <=0.75 and event.jet_puppi_tau2tau1_jet2 <= 0.35):
                            if (event.jet1_Hbbtag > tag and event.jet1_Hbbtag <1.1) or (event.jet2_Hbbtag > tag and event.jet2_Hbbtag < 1.1):
                                WWLPBtagged.Fill(event.MVV, event.weight)
                                AllMass.Fill(event.MVV, event.weight)                              
                            else:
                                WWLP.Fill(event.MVV,event.weight)
                                AllMass.Fill(event.MVV, event.weight)
                        
            if (event.jet_puppi_softdrop_jet1 >= 65. and event.jet_puppi_softdrop_jet1 <=85. and event.jet_puppi_softdrop_jet2 > 85. and event.jet_puppi_softdrop_jet2 <=105.) or (event.jet_puppi_softdrop_jet1 > 85. and event.jet_puppi_softdrop_jet1 <=105. and event.jet_puppi_softdrop_jet2 >= 65. and event.jet_puppi_softdrop_jet2 <=85.):
                if event.jet_puppi_tau2tau1_jet1 <=0.35 and event.jet_puppi_tau2tau1_jet2 <= 0.35:
                    
                        if (event.jet1_Hbbtag > tag and event.jet1_Hbbtag <1.1) or (event.jet2_Hbbtag > tag and event.jet2_Hbbtag < 1.1):
                            WZHPBtagged.Fill(event.MVV, event.weight)
                            AllMass.Fill(event.MVV, event.weight)
                        else: 
                            WZHP.Fill(event.MVV,event.weight)
                            AllMass.Fill(event.MVV, event.weight)
                else: 
                        if (event.jet_puppi_tau2tau1_jet1 <=0.35 and event.jet_puppi_tau2tau1_jet2 <= 0.75) or (event.jet_puppi_tau2tau1_jet1 <=0.75 and event.jet_puppi_tau2tau1_jet2 <= 0.35):
                            if (event.jet1_Hbbtag > tag and event.jet1_Hbbtag <1.1) or (event.jet2_Hbbtag > tag and event.jet2_Hbbtag < 1.1):
                                WZLPBtagged.Fill(event.MVV, event.weight)
                                AllMass.Fill(event.MVV, event.weight)                              
                            else:
                                WZLP.Fill(event.MVV,event.weight)
                                AllMass.Fill(event.MVV, event.weight)
           
           
    OutputFilename = "BulkGtoZZ_bb_%sGeV.root" %mass
    OutputFile = TFile(OutputFilename, "RECREATE")

    

    OutputFile.Append(VVHP)
    OutputFile.Append(VVLP)
    OutputFile.Append(WWHP)
    OutputFile.Append(WWLP)
    OutputFile.Append(WZHP)
    OutputFile.Append(WZLP)
    OutputFile.Append(ZZHP)
    OutputFile.Append(ZZLP)
    OutputFile.Append(WZHPBtagged)
    OutputFile.Append(WZLPBtagged)
    
    OutputFile.Append(ZZHPBtagged)
    OutputFile.Append(ZZLPBtagged)
    OutputFile.Append(WWHPBtagged)
    OutputFile.Append(WWLPBtagged)
    #OutputFile.Append(AllMass)
    #OutputFile.Append(Testhist)
    OutputFile.Write()
    print nEvents
    #print "bb:     " , BtaggedMass.GetEntries()
    print "ZZHP:   " , ZZHP.GetEntries()
    #print "ZZHPBtagged:   " , ZZHPBtagged.GetEntries()
    print "WWHP:   " , WWHP.GetEntries()
    print "WWHP:   " , WWHP.GetEntries()
    print "WZHP:   " , WZHP.GetEntries()
    print "ZZLP:   " , ZZLP.GetEntries()
    print "WWLP:   " , WWLP.GetEntries()
    print "WZLP:   " , WZLP.GetEntries()
    print "VVLP:   " , VVLP.GetEntries()
    print "VVHP:   " , VVHP.GetEntries()
else:
    
    
    #file = TFile.Open("/usr/users/vscheurer/AnalysisOutput/Data4.root")
    #Danielasfile = TFile.Open("/storage/jbod/dschaefer/AnalysisOutput/80X/Data/ReReco2016/Data_VVdijet_SR_36814ifb.root")
    file = TFile.Open("/portal/ekpbms2/home/vscheurer/AnalysisOutput/QCD_pt_complete.root")
    print file

    tree = file.Get("tree")

    Testhist = TH1F('t','t',100,-1,1)

    BtaggedMass = TH1F('MVV', 'MVV', 4000,1000,5000)
    ZZHP = TH1F('ZZHP', 'ZZHP', 4000,1000,5000)
    ZZHPBtagged = TH1F('ZZHPBtagged','ZZHP', 4000,1000,5000)
    ZZLPBtagged = TH1F('ZZLPBtagged','ZZHP', 4000,1000,5000)
    ZZLP = TH1F('ZZLP', 'ZZLP', 4000,1000,5000)
    WZHP = TH1F('WZHP', 'WZHP', 4000,1000,5000)
    WZHPBtagged = TH1F('WZHPBtagged', 'WZHP', 4000,1000,5000)
    WZLPBtagged = TH1F('WZLPBtagged', 'WZHP', 4000,1000,5000)
    WZLP = TH1F('WZLP', 'WZLP', 4000,1000,5000)
    WWHP = TH1F('WWHP', 'WWHP', 4000,1000,5000)
    WWHPBtagged = TH1F('WWHPBtagged', 'WWHP', 4000,1000,5000)
    WWLPBtagged = TH1F('WWLPBtagged', 'WWHP', 4000,1000,5000)
    WWLP = TH1F('WWLP', 'WWLP', 4000,1000,5000)
    AllMass = TH1F('All', 'MVV', 4000,1000,5000)
    VVHP = TH1F('VVHP', 'VVHP', 4000,1000,5000)
    VVLP = TH1F('VVLP', 'VVLP', 4000,1000,5000)
    
    for event in tree:
        if event.MVV > Mjjcut:
            if event.jet_puppi_softdrop_jet1 > 85. and event.jet_puppi_softdrop_jet1 <=105. and event.jet_puppi_softdrop_jet2 > 85. and event.jet_puppi_softdrop_jet2 <=105.:
                if event.jet_puppi_tau2tau1_jet1 <=0.35 and event.jet_puppi_tau2tau1_jet2 <= 0.35:
                    
                        if (event.jet1_Hbbtag > tag and event.jet1_Hbbtag <1.1) or (event.jet2_Hbbtag > tag and event.jet2_Hbbtag < 1.1):
                            ZZHPBtagged.Fill(event.MVV, event.weight)
                            AllMass.Fill(event.MVV, event.weight)
                        else: 
                            ZZHP.Fill(event.MVV,event.weight)
                            AllMass.Fill(event.MVV, event.weight)
                else: 
                        if (event.jet_puppi_tau2tau1_jet1 <=0.35 and event.jet_puppi_tau2tau1_jet2 <= 0.75) or (event.jet_puppi_tau2tau1_jet1 <=0.75 and event.jet_puppi_tau2tau1_jet2 <= 0.35):
                            if (event.jet1_Hbbtag > tag and event.jet1_Hbbtag <1.1) or (event.jet2_Hbbtag > tag and event.jet2_Hbbtag < 1.1):
                                ZZLPBtagged.Fill(event.MVV, event.weight)
                                AllMass.Fill(event.MVV, event.weight)                              
                            else:
                                ZZLP.Fill(event.MVV,event.weight)
                                AllMass.Fill(event.MVV, event.weight)


            if event.jet_puppi_softdrop_jet1 >= 106. and event.jet_puppi_softdrop_jet1 <=105. and event.jet_puppi_softdrop_jet2 >= 106. and event.jet_puppi_softdrop_jet2 <=105.:
                if event.jet_puppi_tau2tau1_jet1 <=0.35 and event.jet_puppi_tau2tau1_jet2 <= 0.35:
                    
                        if (event.jet1_Hbbtag > tag and event.jet1_Hbbtag <1.1) or (event.jet2_Hbbtag > tag and event.jet2_Hbbtag < 1.1):
                            ZZHPBtagged.Fill(event.MVV, event.weight)
                            AllMass.Fill(event.MVV, event.weight)
                        else: 
                            VVHP.Fill(event.MVV,event.weight)
                            AllMass.Fill(event.MVV, event.weight)
                else: 
                        if (event.jet_puppi_tau2tau1_jet1 <=0.35 and event.jet_puppi_tau2tau1_jet2 <= 0.75) or (event.jet_puppi_tau2tau1_jet1 <=0.75 and event.jet_puppi_tau2tau1_jet2 <= 0.35):
                            if (event.jet1_Hbbtag > tag and event.jet1_Hbbtag <1.1) or (event.jet2_Hbbtag > tag and event.jet2_Hbbtag < 1.1):
                                ZZLPBtagged.Fill(event.MVV, event.weight)
                                AllMass.Fill(event.MVV, event.weight)                              
                            else:
                                VVLP.Fill(event.MVV,event.weight)
                                AllMass.Fill(event.MVV, event.weight)

            if event.jet_puppi_softdrop_jet1 >= 65. and event.jet_puppi_softdrop_jet1 <=85. and event.jet_puppi_softdrop_jet2 >= 65. and event.jet_puppi_softdrop_jet2 <=85.:
                if event.jet_puppi_tau2tau1_jet1 <=0.35 and event.jet_puppi_tau2tau1_jet2 <= 0.35:
                    
                        if (event.jet1_Hbbtag > tag and event.jet1_Hbbtag <1.1) or (event.jet2_Hbbtag > tag and event.jet2_Hbbtag < 1.1):
                            WWHPBtagged.Fill(event.MVV, event.weight)
                            AllMass.Fill(event.MVV, event.weight)
                        else: 
                            WWHP.Fill(event.MVV,event.weight)
                            AllMass.Fill(event.MVV, event.weight)
                else: 
                        if (event.jet_puppi_tau2tau1_jet1 <=0.35 and event.jet_puppi_tau2tau1_jet2 <= 0.75) or (event.jet_puppi_tau2tau1_jet1 <=0.75 and event.jet_puppi_tau2tau1_jet2 <= 0.35):
                            if (event.jet1_Hbbtag > tag and event.jet1_Hbbtag <1.1) or (event.jet2_Hbbtag > tag and event.jet2_Hbbtag < 1.1):
                                WWLPBtagged.Fill(event.MVV, event.weight)
                                AllMass.Fill(event.MVV, event.weight)                              
                            else:
                                WWLP.Fill(event.MVV,event.weight)
                                AllMass.Fill(event.MVV, event.weight)
                        
            if (event.jet_puppi_softdrop_jet1 >= 65. and event.jet_puppi_softdrop_jet1 <=85. and event.jet_puppi_softdrop_jet2 > 85. and event.jet_puppi_softdrop_jet2 <=105.) or (event.jet_puppi_softdrop_jet1 > 85. and event.jet_puppi_softdrop_jet1 <=105. and event.jet_puppi_softdrop_jet2 >= 65. and event.jet_puppi_softdrop_jet2 <=85.):
                if event.jet_puppi_tau2tau1_jet1 <=0.35 and event.jet_puppi_tau2tau1_jet2 <= 0.35:
                    
                        if (event.jet1_Hbbtag > tag and event.jet1_Hbbtag <1.1) or (event.jet2_Hbbtag > tag and event.jet2_Hbbtag < 1.1):
                            WZHPBtagged.Fill(event.MVV, event.weight)
                            AllMass.Fill(event.MVV, event.weight)
                        else: 
                            WZHP.Fill(event.MVV,event.weight)
                            AllMass.Fill(event.MVV, event.weight)
                else: 
                        if (event.jet_puppi_tau2tau1_jet1 <=0.35 and event.jet_puppi_tau2tau1_jet2 <= 0.75) or (event.jet_puppi_tau2tau1_jet1 <=0.75 and event.jet_puppi_tau2tau1_jet2 <= 0.35):
                            if (event.jet1_Hbbtag > tag and event.jet1_Hbbtag <1.1) or (event.jet2_Hbbtag > tag and event.jet2_Hbbtag < 1.1):
                                WZLPBtagged.Fill(event.MVV, event.weight)
                                AllMass.Fill(event.MVV, event.weight)                              
                            else:
                                WZLP.Fill(event.MVV,event.weight)
                                AllMass.Fill(event.MVV, event.weight)
           
        
        
    #BtaggedMass.Scale(35867.0)
    VVHP.Scale(35867.0)
    VVLP.Scale(35867.0)
    ZZHP.Scale(35867.0)
    ZZLP.Scale(35867.0)
    WZHP.Scale(35867.0)
    WZLP.Scale(35867.0)
    WWHP.Scale(35867.0)
    WWLP.Scale(35867.0)
    ZZHPBtagged.Scale(35867.0)
    ZZLPBtagged.Scale(35867.0)
    WZHPBtagged.Scale(35867.0)
    WZLPBtagged.Scale(35867.0)
    WWHPBtagged.Scale(35867.0)
    WWLPBtagged.Scale(35867.0)
    OutputFilename = "../DijetCombineLimitCode/Bkg.root"
    OutputFile = TFile(OutputFilename, "RECREATE")
    print "bb:     " , BtaggedMass.GetEntries()
    print "ZZHP:   " , ZZHP.GetEntries()
    print "WWHP:   " , WWHP.GetEntries()
    print "WZHP:   " , WZHP.GetEntries()
    print "ZZLP:   " , ZZLP.GetEntries()
    print "WWLP:   " , WWLP.GetEntries()
    print "WZLP:   " , WZLP.GetEntries()
    
    #OutputFile.Append(BtaggedMass)
    OutputFile.Append(VVHP)
    OutputFile.Append(VVLP)    
    OutputFile.Append(ZZHP)
    OutputFile.Append(ZZLP)
    OutputFile.Append(WZHP)
    OutputFile.Append(WZLP)
    OutputFile.Append(WWHP)
    OutputFile.Append(WWLP)
    OutputFile.Append(ZZHPBtagged)
    OutputFile.Append(ZZLPBtagged)
    OutputFile.Append(WZHPBtagged)
    OutputFile.Append(WZLPBtagged)
    OutputFile.Append(WWHPBtagged)
    OutputFile.Append(WWLPBtagged)
    #OutputFile.Append(AllMass)
    #OutputFile.Append(Testhist)
    OutputFile.Write()

#---------------------------------------Backup-------------------------------------
# with Interpolation:
    #for event in tree:
        #if event.jet1_Hbbtag < 1.1 and event.jet2_Hbbtag <1.1:
            #if event.MVV > Mjjcut and event.MVV <= 1400:
                #if event.jet1_Hbbtag > tag or event.jet2_Hbbtag > tag:
                    #Mass.Fill(event.MVV, event.weight)
            #if event.MVV > 1400 and event.MVV < 1600:
                #interpolatedTag = tag-((0.1/200)*(event.MVV-1400))
                #if event.jet1_Hbbtag > interpolatedTag or event.jet2_Hbbtag > interpolatedTag:
                    #Mass.Fill(event.MVV, event.weight)    
            #if event.MVV >= 1600 and event.MVV <=2000:        
                #if event.jet1_Hbbtag > tag or event.jet2_Hbbtag > tag:
                    #Mass.Fill(event.MVV, event.weight)
            #if event.MVV > 2000 and event.MVV <=2500:
                #interpolatedTag = tag-((tag/500)*(event.MVV-2000))
                #if event.jet1_Hbbtag > interpolatedTag or event.jet2_Hbbtag > interpolatedTag:
                    #Mass.Fill(event.MVV, event.weight)
            #if event.MVV > 2500:
                #if event.jet1_Hbbtag > tag or event.jet2_Hbbtag > tag:
                    #Mass.Fill(event.MVV, event.weight) 
