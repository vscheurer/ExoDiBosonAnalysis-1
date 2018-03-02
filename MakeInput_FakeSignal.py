from ROOT import *
import numpy as np
from array import array
import sys

mass = sys.argv[1]
Fake = sys.argv[2]
tag =0.6
i=j=k=l=m=n=o=p=q=r=s=t=0


HPcut = 0.35

if mass != 'QCD':
    file = TFile.Open('ExoDiBosonAnalysis.test-'+mass+'.VV.VV.root','READ')
    print file

    tree = file.Get("tree")

    Testhist = TH1F('t','t',100,-1,1)
    nEvents =0
    BtaggedMass = TH1F('BtaggedMass_'+mass+'GeV', 'BtaggedMass_'+mass+'GeV', 4000,1000,5000)
    ZZHP = TH1F('ZZHP_'+mass+'GeV', 'ZZHP', 4000,1000,5000)
    ZZLP = TH1F('ZZLP_'+mass+'GeV', 'ZZLP', 4000,1000,5000)
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
        if event.MVV > 1050:
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

    
    OutputFile.Append(ZZHP)
    OutputFile.Append(ZZLP)
    OutputFile.Append(ZZHPBtagged)
    OutputFile.Append(ZZLPBtagged)
    OutputFile.Append(WZHP)
    OutputFile.Append(WZLP)
    OutputFile.Append(WZHPBtagged)
    OutputFile.Append(WZLPBtagged)
    OutputFile.Append(WWHP)
    OutputFile.Append(WWLP)
    OutputFile.Append(WWHPBtagged)
    OutputFile.Append(WWLPBtagged)
    OutputFile.Append(AllMass)
    #OutputFile.Append(Testhist)
    OutputFile.Write()
    print nEvents
    print "bb:     " , BtaggedMass.GetEntries()
    print "ZZHP:   " , ZZHP.GetEntries()
    print "ZZHPBtagged:   " , ZZHPBtagged.GetEntries()
    print "WWHP:   " , WWHP.GetEntries()
    print "WWHP:   " , WWHP.GetEntries()
    print "WZHP:   " , WZHP.GetEntries()
    print "ZZLP:   " , ZZLP.GetEntries()
    print "WWLP:   " , WWLP.GetEntries()
    print "WZLP:   " , WZLP.GetEntries()
else:
    file = TFile.Open('QCD_pt.root','READ')
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
    
    for event in tree:
        if event.MVV > 1050:
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
    

    print "ZZHP:   " , ZZHP.GetEntries()
    print "ZZHPBtagged:   " , ZZHPBtagged.GetEntries()
    print "WWHP:   " , WWHP.GetEntries()
    print "WWHP:   " , WWHP.GetEntries()
    print "WZHP:   " , WZHP.GetEntries()
    print "ZZLP:   " , ZZLP.GetEntries()
    print "WWLP:   " , WWLP.GetEntries()
    print "WZLP:   " , WZLP.GetEntries()
    file2 = TFile.Open('ExoDiBosonAnalysis.test-'+str(Fake)+'.VV.VV.root','READ')
    print file2
    FakeSignal = np.genfromtxt("../DijetCombineLimitCode/FakeSignal"+str(Fake)+".txt")
    tree2 = file2.Get("tree")
    for event in tree2:
        if event.MVV > 1050:
            if event.jet_puppi_softdrop_jet1 > 85. and event.jet_puppi_softdrop_jet1 <=105. and event.jet_puppi_softdrop_jet2 > 85. and event.jet_puppi_softdrop_jet2 <=105.:
                if event.jet_puppi_tau2tau1_jet1 <=0.35 and event.jet_puppi_tau2tau1_jet2 <= 0.35:
                    
                        if (event.jet1_Hbbtag > tag and event.jet1_Hbbtag <1.1) or (event.jet2_Hbbtag > tag and event.jet2_Hbbtag < 1.1):
                            if ((i < FakeSignal[6]) and np.random.random()<1.0):
                                ZZHPBtagged.Fill(event.MVV, event.weight)
                                AllMass.Fill(event.MVV, event.weight)
                                i=i+1
                        else: 
                            if ((j < FakeSignal[0]) and np.random.random()<1.0):
                                ZZHP.Fill(event.MVV,event.weight)
                                AllMass.Fill(event.MVV, event.weight)
                                j=j+1
                else: 
                        if (event.jet_puppi_tau2tau1_jet1 <=0.35 and event.jet_puppi_tau2tau1_jet2 <= 0.75) or (event.jet_puppi_tau2tau1_jet1 <=0.75 and event.jet_puppi_tau2tau1_jet2 <= 0.35):
                            if (event.jet1_Hbbtag > tag and event.jet1_Hbbtag <1.1) or (event.jet2_Hbbtag > tag and event.jet2_Hbbtag < 1.1):
                                if ((k < FakeSignal[7]) and np.random.random()<1.0):
                                    ZZLPBtagged.Fill(event.MVV, event.weight)
                                    AllMass.Fill(event.MVV, event.weight)
                                    k=k+1
                            else:
                                if ((l < FakeSignal[1]) and np.random.random()<1.0):
                                    ZZLP.Fill(event.MVV,event.weight)
                                    AllMass.Fill(event.MVV, event.weight)
                                    l=l+1

            if event.jet_puppi_softdrop_jet1 >= 65. and event.jet_puppi_softdrop_jet1 <=85. and event.jet_puppi_softdrop_jet2 >= 65. and event.jet_puppi_softdrop_jet2 <=85.:
                if event.jet_puppi_tau2tau1_jet1 <=0.35 and event.jet_puppi_tau2tau1_jet2 <= 0.35:
                    
                        if (event.jet1_Hbbtag > tag and event.jet1_Hbbtag <1.1) or (event.jet2_Hbbtag > tag and event.jet2_Hbbtag < 1.1):
                            if ((m < FakeSignal[10]) and np.random.random()<1.0):
                                print m
                                WWHPBtagged.Fill(event.MVV, event.weight)
                                AllMass.Fill(event.MVV, event.weight)
                                m=m+1
                        else: 
                            if ((n < FakeSignal[4]) and np.random.random()<1.0):
                                WWHP.Fill(event.MVV,event.weight)
                                AllMass.Fill(event.MVV, event.weight)
                                n=n+1
                else: 
                        if (event.jet_puppi_tau2tau1_jet1 <=0.35 and event.jet_puppi_tau2tau1_jet2 <= 0.75) or (event.jet_puppi_tau2tau1_jet1 <=0.75 and event.jet_puppi_tau2tau1_jet2 <= 0.35):
                            if (event.jet1_Hbbtag > tag and event.jet1_Hbbtag <1.1) or (event.jet2_Hbbtag > tag and event.jet2_Hbbtag < 1.1):
                                if ((o < FakeSignal[11]) and np.random.random()<1.0):
                                    WWLPBtagged.Fill(event.MVV, event.weight)
                                    AllMass.Fill(event.MVV, event.weight)
                                    o=o+1
                            else:
                                if ((p < FakeSignal[5]) and np.random.random()<1.0):
                                    WWLP.Fill(event.MVV,event.weight)
                                    AllMass.Fill(event.MVV, event.weight)
                                    p=p+1
                        
            if (event.jet_puppi_softdrop_jet1 >= 65. and event.jet_puppi_softdrop_jet1 <=85. and event.jet_puppi_softdrop_jet2 > 85. and event.jet_puppi_softdrop_jet2 <=105.) or (event.jet_puppi_softdrop_jet1 > 85. and event.jet_puppi_softdrop_jet1 <=105. and event.jet_puppi_softdrop_jet2 >= 65. and event.jet_puppi_softdrop_jet2 <=85.):
                if event.jet_puppi_tau2tau1_jet1 <=0.35 and event.jet_puppi_tau2tau1_jet2 <= 0.35:
                    
                        if (event.jet1_Hbbtag > tag and event.jet1_Hbbtag <1.1) or (event.jet2_Hbbtag > tag and event.jet2_Hbbtag < 1.1):
                            if ((q < FakeSignal[8]) and np.random.random()<1.0):
                                WZHPBtagged.Fill(event.MVV, event.weight)
                                AllMass.Fill(event.MVV, event.weight)
                                q=q+1
                        else: 
                            if ((r < FakeSignal[2]) and np.random.random()<1.0):
                                WZHP.Fill(event.MVV,event.weight)
                                AllMass.Fill(event.MVV, event.weight)
                                r=r+1
                else: 
                        if (event.jet_puppi_tau2tau1_jet1 <=0.35 and event.jet_puppi_tau2tau1_jet2 <= 0.75) or (event.jet_puppi_tau2tau1_jet1 <=0.75 and event.jet_puppi_tau2tau1_jet2 <= 0.35):
                            if (event.jet1_Hbbtag > tag and event.jet1_Hbbtag <1.1) or (event.jet2_Hbbtag > tag and event.jet2_Hbbtag < 1.1):
                                if ((s < FakeSignal[9]) and np.random.random()<1.0):
                                    WZLPBtagged.Fill(event.MVV, event.weight)
                                    AllMass.Fill(event.MVV, event.weight)
                                    s=s+1
                            else:
                                if ((t < FakeSignal[3]) and np.random.random()<1.0):
                                    WZLP.Fill(event.MVV,event.weight)
                                    AllMass.Fill(event.MVV, event.weight) 
                                    t=t+1
 
        BtaggedMass.Scale(35867.0)
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
    print "WWHPBtagged:   " , ZZHPBtagged.GetEntries()

        
    print "ZZHP:   " , ZZHP.GetEntries()
    print "ZZHPBtagged:   " , ZZHPBtagged.GetEntries()
    print "WWHP:   " , WWHP.GetEntries()
    print "WWHP:   " , WWHP.GetEntries()
    print "WZHP:   " , WZHP.GetEntries()
    print "ZZLP:   " , ZZLP.GetEntries()
    print "WWLP:   " , WWLP.GetEntries()
    print "WZLP:   " , WZLP.GetEntries()
    OutputFilename = "../DijetCombineLimitCode/BulkGtoZZ_bb_QCD.root"
    OutputFile = TFile(OutputFilename, "RECREATE")
    OutputFile.Append(BtaggedMass)
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
    OutputFile.Append(AllMass)
    #OutputFile.Append(Testhist)
    OutputFile.Write()

#---------------------------------------Backup-------------------------------------
# with Interpolation:
    #for event in tree:
        #if event.jet1_Hbbtag < 1.1 and event.jet2_Hbbtag <1.1:
            #if event.MVV > 1050 and event.MVV <= 1400:
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