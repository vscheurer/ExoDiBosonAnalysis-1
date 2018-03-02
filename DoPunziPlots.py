from ROOT import *
import numpy as np
from array import array
import sys

mass = sys.argv[1] 

filename =  'ExoDiBosonAnalysis.test-WZ_4000.VV.root' 
file = TFile.Open(filename,'READ')

#QCD file
file_QCD = TFile.Open('~/AnalysisOutput/80X/ExoDiBosonAnalysis.QCD_Pt_All.root','READ')

print file
print file_QCD
tree = file.Get("tree")
tree_QCD = file_QCD.Get("tree")

c1 = TCanvas(" ","",600,400)
gStyle.SetPalette(kOcean)
gStyle.SetOptStat(0)
nbins = 100 
MaxRange = 5000
MinRange = 1000
xbins =array('f' ,[-0.95, -0.85, -.75,-.65,-.55,-.45,-.35,-.25,-.15,-.05,0.05,0.15,.25,.35,.45,.55,.65,.75,.85,0.95,1.00])
xbins2 =array('f' ,[0.79,0.81,0.83,0.85,0.87,0.89,0.91,0.93,0.95,0.97,0.99,1.01])

print xbins
Minbin = 1

Punzihist = TH1F('PunziSignificance', 'WZ_PunziSignificance_for_M=4000_GeV', 19,xbins)
#Punzihist2 = TH1F('PunziSignificance', 'PunziSignificance', 8,xbins2)


AllMass = TH1F('MVV' , 'MVV', nbins,MinRange,MaxRange)
BtaggedMass_QCD = TH1F('BtaggedMassQCD', 'BtaggedMassQCD', nbins,MinRange,MaxRange)
BtaggedMass = TH1F('BtaggedMass', 'BtaggedMass', nbins,MinRange,MaxRange)

for event in tree:
    if event.MVV > 1050:
        AllMass.Fill(event.MVV,event.weight)
    else:
        AllMass.Fill(0.)

for i in range(1,nbins+1):
        
        if (AllMass.Integral(1,i)<=AllMass.Integral(1,nbins)*0.95):
            Maxbin = i
        if (AllMass.Integral(1,i)<=AllMass.Integral('')*0.05):
            Minbin = i
       
    
print AllMass.Integral(Minbin,Maxbin)/AllMass.Integral(1,nbins)

for tag in range(-9,11):
   

    if tag < 11:
        btag = 0.1*(tag)
    else:
        btag = 0.95


    for event in tree_QCD:
        #print event.weight
        #print event.lumiweight
        if event.MVV > 1050:
            if event.jet2_Hbbtag < 1.1 and event.jet1_Hbbtag <1.1:
                if event.jet2_Hbbtag >btag or event.jet1_Hbbtag >btag:
                    BtaggedMass_QCD.Fill(event.MVV, event.weight)
                else: 
                    BtaggedMass_QCD.Fill(0.)
            else: 
               BtaggedMass_QCD.Fill(0.)
        else: 
            BtaggedMass_QCD.Fill(0.)
    
    for event in tree:
        if event.MVV > 1050:
           
            if event.jet2_Hbbtag < 1.1 and event.jet1_Hbbtag <1.1:
                if event.jet2_Hbbtag >btag or event.jet1_Hbbtag > btag:
                    BtaggedMass.Fill(event.MVV,event.weight)
                else:  
                     BtaggedMass.Fill(0.) 
            else:  
                BtaggedMass.Fill(0.) 
        else: 
             BtaggedMass.Fill(0.)
    
    Effi = BtaggedMass.Integral(Minbin,Maxbin)/AllMass.Integral(Minbin,Maxbin)
    print Effi
    BtaggedMass_QCD.Scale(35867.)
    Punzi = Effi/(1+np.sqrt(BtaggedMass_QCD.Integral(Minbin,Maxbin)))
    Punzihist.Fill(btag,Punzi)
    print Punzi
    BtaggedMass.Reset()
    BtaggedMass_QCD.Reset()
    
    


print "Finished"
gStyle.SetLegendBorderSize(0)
#

l = TLegend(0.654361,0.723552,0.868124,0.9024967)
l.AddEntry(Punzihist, "Punzi significance")
l.SetFillStyle(0)
#Sl.SetTextSize(200.)
#Punzihist2.GetYaxis().SetRangeUser(0.003,0.0045)
Punzihist.SetMarkerStyle(20)
Punzihist.SetMarkerColor(6)
Punzihist.GetXaxis().SetTitle("double-b tagger discriminant")
Punzihist.GetYaxis().SetTitle("Punzi significance")
Punzihist.GetYaxis().SetTitleOffset(1.4)

Punzihist.Draw('hist p')
l.Draw("SAME")
Outfilename = "PunziSignificance_for_M=%s_GeV_WZ.root" %mass
Outfile = TFile(Outfilename, 'RECREATE')
Outfile.Append(Punzihist)
Outfile.Write()
input = raw_input()