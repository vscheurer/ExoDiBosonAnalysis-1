from ROOT import*

file = TFile.Open("/usr/users/vscheurer/AnalysisOutput/QCD_pt_complete.root")
#file = TFile.Open("/usr/users/vscheurer/ExoDiBosonAnalysis/ExoDiBosonAnalysis.test-2000.VV.VV.root")

tree = file.Get("tree")
gStyle.SetOptStat(0)
Hbbtag = TH1F('Hbbtag', 'Double-b tag discriminant in Background', 100,-1.1,1.1)
for event in tree:
    Hbbtag.Fill(event.jet1_Hbbtag)
Hbbtag.GetXaxis().SetTitle("Double-b tag discriminant")
Hbbtag.Draw()
x = raw_input()