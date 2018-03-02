from ROOT import *
import numpy as np

#file = TFile.Open('/portal/ekpbms2/home/vscheurer/AnalysisOutput/QCD_pt_complete.root','READ')
#file = TFile.Open('/portal/ekpbms2/home/vscheurer/AnalysisOutput/ExoDiBosonAnalysis.test-All.VV.root','READ')
file = TFile.Open('ExoDiBosonAnalysis.test-2000.VV.VV.root','READ')
print file
tree = file.Get("tree")


c1 = TCanvas(" ","",1200,800)
#c1.SetLogy()
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
#TrueHbb = TH1F("Signal dijet mass","",100,-1.1,1.1)
TrueHbb = TH1F("Signal dijet mass","",100,1000,4000)
for event in tree:
    MVV = event.MVV
    TrueHbb.Fill(MVV,event.weight)
    #TrueHbb.Fill(event.jet1_Hbbtag)
#Jet1Pt.Draw()
#BtaggedJet1Pt.Add(BtaggedJet2Pt)
#Jet1Pt.Add(Jet2Pt)
#BtaggedJet1Pt_loose.Add(BtaggedJet2Pt_loose)
#BtaggedJet1Pt_medium.Add(BtaggedJet2Pt_medium)
#BtaggedJet1Pt_tight.Add(BtaggedJet2Pt_tight)



#EffJet = TEfficiency(BtaggedJet1Pt,Jet1Pt)
#EffJet_loose = TEfficiency(BtaggedJet1Pt_loose,Jet1Pt)
#EffJet_medium = TEfficiency(BtaggedJet1Pt_medium,Jet1Pt)
#EffJet_tight = TEfficiency(BtaggedJet1Pt_tight,Jet1Pt)





TrueHbb.SetMarkerStyle(20)
#EffJet_loose.SetMarkerStyle(20)
#EffJet_medium.SetMarkerStyle(20)
#EffJet_tight.SetMarkerStyle(20)

TrueHbb.SetMarkerSize(0.8)
#EffJet_loose.SetMarkerSize(0.8)
#EffJet_medium.SetMarkerSize(0.8)
#EffJet_tight.SetMarkerSize(0.8)

TrueHbb.SetMarkerColor(4)
#EffJet_loose.SetMarkerColor(7)
#EffJet_medium.SetMarkerColor(4)
#EffJet_tight.SetMarkerColor(2)

gStyle.SetLegendBorderSize(0)
gStyle.SetOptStat(0)
#l = TLegend(0.58361,0.723552,0.90124,0.9024967)
#l.SetFillStyle(0)
#l.AddEntry(EffJet,"Double b 0.8","lp")
#l.AddEntry(EffJet_loose,"Double b loose","lp")
#l.AddEntry(EffJet_medium,"Double b medium","lp")
#l.AddEntry(EffJet_tight,"Double b tight",",lp")

#dummyhist = TH1F("dummyhist","double-b discriminant (Z->bb)",100,-1.1,1.1)
#dummyhist.SetMinimum(0)
#dummyhist.SetMaximum(2000)
#TrueHbb.Scale(35867.0)
TrueHbb.Draw()
TrueHbb.GetYaxis().SetTitle("a.u.")
TrueHbb.GetXaxis().SetTitle("dijet mass (GeV)")
TrueHbb.GetYaxis().SetTitleOffset(1.2)

#EffJet.Draw("same")
#gr.GetYaxis().SetRangeUser(0.,1.)
#gr.Draw()
#EffJet_loose.Draw('SAME ')
#EffJet_medium.Draw('SAME ')
#EffJet_tight.Draw('SAME ')
#l.Draw('SAME')
#TrueHbb.Draw('SAME')


input = raw_input("FINISHED")
