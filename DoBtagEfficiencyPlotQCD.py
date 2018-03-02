from ROOT import *
import numpy as np

file = TFile.Open('../AnalysisOutput/ZbbSignal.root','READ')
#file = TFile.Open('ExoDiBosonAnalysis.test-All.VV.root','READ')
#file = TFile.Open('ExoDiBosonAnalysis.test-2000.VV.root','READ')
print file
tree = file.Get("tree")


c1 = TCanvas(" ","",600,400)
#gStyle.SetPalette(kOcean)
Jet1Pt = TH1F("Jet1Pt_total","Jet1Pt_total",30,0,3500)
Jet2Pt = TH1F("Jet2Pt_total","Jet2Pt_total",30,0,3500)
BtaggedJet1Pt = TH1F("Jet1Pt_passed","Jet1Pt_passed",30,0,3500)
BtaggedJet2Pt = TH1F("Jet2Pt_passed","Jet2Pt_passed",30,0,3500)
BtaggedJet1Pt_loose = TH1F("Jet1Pt_passed_loose","Jet1Pt_passed_loose",30,0,3500)
BtaggedJet2Pt_loose = TH1F("Jet2Pt_passed_loose","Jet2Pt_passed_loose",30,0,3500)
BtaggedJet1Pt_medium = TH1F("Jet1Pt_passed_medium","Jet1Pt_passed_medium",30,0,3500)
BtaggedJet2Pt_medium = TH1F("Jet2Pt_passed_medium","Jet2Pt_passed_medium",30,0,3500)
BtaggedJet1Pt_tight = TH1F("Jet1Pt_passed_tight","Jet1Pt_passed_tight",30,0,3500)
BtaggedJet2Pt_tight = TH1F("Jet2Pt_passed_tight","Jet2Pt_passed_tight",30,0,3500)
for event in tree:
    pt = event.jet_pt_jet1
    Jet1Pt.Fill(pt)
    pt2 = event.jet_pt_jet2
    Jet2Pt.Fill(pt2)
    if event.jet1_Hbbtag > 0.3:
        BtaggedJet1Pt_loose.Fill(pt);
    if event.jet1_Hbbtag > 0.6:
        BtaggedJet1Pt_medium.Fill(pt);
    if event.jet1_Hbbtag > 0.9:
        BtaggedJet1Pt_tight.Fill(pt);
    if event.jet2_Hbbtag > 0.3:
        BtaggedJet2Pt_loose.Fill(pt);
    if event.jet2_Hbbtag > 0.6:
        BtaggedJet2Pt_medium.Fill(pt);
    if event.jet2_Hbbtag > 0.9:
        BtaggedJet2Pt_tight.Fill(pt);

#Jet1Pt.Draw()
BtaggedJet1Pt.Add(BtaggedJet2Pt)
Jet1Pt.Add(Jet2Pt)
BtaggedJet1Pt_loose.Add(BtaggedJet2Pt_loose)
BtaggedJet1Pt_medium.Add(BtaggedJet2Pt_medium)
BtaggedJet1Pt_tight.Add(BtaggedJet2Pt_tight)



EffJet = TEfficiency(BtaggedJet1Pt,Jet1Pt)
EffJet_loose = TEfficiency(BtaggedJet1Pt_loose,Jet1Pt)
EffJet_medium = TEfficiency(BtaggedJet1Pt_medium,Jet1Pt)
EffJet_tight = TEfficiency(BtaggedJet1Pt_tight,Jet1Pt)





EffJet.SetMarkerStyle(20)
EffJet_loose.SetMarkerStyle(20)
EffJet_medium.SetMarkerStyle(20)
EffJet_tight.SetMarkerStyle(20)

EffJet.SetMarkerSize(0.8)
EffJet_loose.SetMarkerSize(0.8)
EffJet_medium.SetMarkerSize(0.8)
EffJet_tight.SetMarkerSize(0.8)

EffJet.SetMarkerColor(2)
EffJet_loose.SetMarkerColor(7)
EffJet_medium.SetMarkerColor(4)
EffJet_tight.SetMarkerColor(2)

gStyle.SetLegendBorderSize(0)
gStyle.SetOptStat(0)
l = TLegend(0.58361,0.723552,0.90124,0.9024967)
l.SetFillStyle(0)
#l.AddEntry(EffJet,"Double b 0.8","lp")
l.AddEntry(EffJet_loose,"Double b loose","lp")
l.AddEntry(EffJet_medium,"Double b medium","lp")
l.AddEntry(EffJet_tight,"Double b tight",",lp")

dummyhist = TH1F("dummyhist","Signal Efficiency",1,300,2050)
dummyhist.SetMinimum(0)
dummyhist.SetMaximum(1.1)
dummyhist.Draw()
dummyhist.GetYaxis().SetTitle("Signal Efficiency")
dummyhist.GetXaxis().SetTitle("jet_pt (GeV)")
dummyhist.GetYaxis().SetTitleOffset(1.3)
#EffJet.Draw("same")
#gr.GetYaxis().SetRangeUser(0.,1.)
#gr.Draw()
EffJet_loose.Draw('SAME ')
EffJet_medium.Draw('SAME ')
EffJet_tight.Draw('SAME ')
l.Draw('SAME')



input = raw_input("FINISHED")
