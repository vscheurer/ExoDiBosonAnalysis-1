from ROOT import *
import time
import CMS_lumi, tdrstyle

tdrstyle.setTDRStyle()

def getCanvas():
  c = TCanvas("c","c",800,800)
  c.GetWindowHeight()
  c.GetWindowWidth()
  c.SetTitle("")
  return c
  
gStyle.SetOptTitle(0)
gStyle.SetOptStat(0)

fname = "ExoDiBosonAnalysis.TEST.VV.root"
tfile = TFile.Open(fname,'READ')

hPRE  =tfile.Get("SoftdropMass_preSmearing")
hPOST =tfile.Get("SoftdropMass_postSmearing")
hPRE .Scale(1./hPRE.Integral())
hPOST.Scale(1./hPOST.Integral())

gPRE  = TF1("gPRE" ,"gaus", 68,91)
gPOST = TF1("gPOST","gaus", 68,91)
gPRE  = TF1("gPRE" ,"gaus", 65,95)
gPOST = TF1("gPOST","gaus", 65,95)
    
hPRE.Fit(gPRE,"SR")
hPRE.Fit(gPRE,"SR")
hPRE.Fit(gPRE,"SR")
hPOST.Fit(gPOST,"SR")
hPOST.Fit(gPOST,"SR")
hPOST.Fit(gPOST,"SR")

canv = getCanvas()
canv.cd()
vFrame = canv.DrawFrame(0,0,180,0.05)
vFrame.SetYTitle("A.U")
vFrame.SetXTitle("PUPPI softdrop mass (GeV)")
vFrame.GetXaxis().SetTitleSize(0.06)
vFrame.GetXaxis().SetTitleOffset(0.95)
vFrame.GetXaxis().SetLabelSize(0.05)
vFrame.GetYaxis().SetTitleSize(0.06)
vFrame.GetYaxis().SetTitleOffset(1.3)
vFrame.GetYaxis().SetLabelSize(0.05)
vFrame.GetXaxis().SetNdivisions(807)
vFrame.GetYaxis().SetNdivisions(703)
hPRE.Draw('same')
# hPRE.SetTitle("Smearing formula: mass = tr_->Gaus( mass, TMath::Sqrt(jmr*jmr-1)*(massResolution-1)*mass")
hPRE.SetLineColor(kRed)
hPOST.Draw('same')

l = TLegend(0.60461809,0.7620725,0.7559296,0.9009845)
l.SetTextSize(0.035)
l.SetLineColor(0)
l.SetShadowColor(0)
l.SetLineStyle(1)
l.SetLineWidth(1)
l.SetFillColor(0)
l.SetFillStyle(0)
l.SetMargin(0.35)
l.AddEntry(hPRE,"Pre-smear: #sigma = %.2f"%gPRE.GetParameter(2),"lp")
l.AddEntry(hPOST,"Post-smear: #sigma = %.2f"%gPOST.GetParameter(2),"lp")
l.AddEntry(0,"Ratio_{#sigma} = %.2f %%" % ((gPOST.GetParameter(2)/gPRE.GetParameter(2)-1)*100),"")
l.Draw("same")
canv.SaveAs("preVsPostSmearing.pdf")
time.sleep(200)