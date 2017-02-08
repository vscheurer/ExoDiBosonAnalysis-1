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
  


def doFit(fname):

    tfile = TFile.Open(fname,'READ')

    hPRE  =tfile.Get("JetPt_preSmearing")
    hPOST =tfile.Get("JetPt_postSmearing")
    hPRE .Scale(1./hPRE.Integral())
    hPOST.Scale(1./hPOST.Integral())
    hPRE .Rebin(2)
    hPOST.Rebin(2)
    binmax_pre = hPRE.GetMaximumBin();
    x_pre = hPRE.GetXaxis().GetBinCenter(binmax_pre);
    binmax_post = hPOST.GetMaximumBin();
    x_post = hPOST.GetXaxis().GetBinCenter(binmax_post);

    gPRE  = TF1("gPRE" ,"gaus", x_pre-100,x_pre+120)
    gPOST = TF1("gPOST","gaus", x_post-100,x_post+120)
    gPRE  = TF1("gPRE" ,"gaus", x_pre-100,x_pre+120)
    gPOST = TF1("gPOST","gaus", x_post-100,x_post+120)
        
    hPRE.Fit(gPRE,"SR")
    hPRE.Fit(gPRE,"SR")
    hPRE.Fit(gPRE,"SR")
    hPOST.Fit(gPOST,"SR")
    hPOST.Fit(gPOST,"SR")
    hPOST.Fit(gPOST,"SR")

    canv = getCanvas()
    canv.cd()
    vFrame = canv.DrawFrame(200,0,2000,hPRE.GetMaximum()*1.5)
    vFrame.SetYTitle("A.U")
    vFrame.SetXTitle("AK8 jet p_{T} (GeV)")
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

    l = TLegend(0.560461809,0.7620725,0.70559296,0.9009845)
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
    ratio =[ ((gPOST.GetParameter(2)/gPRE.GetParameter(2)-1)*100), ((gPOST.GetParameter(1)/gPRE.GetParameter(1)-1)*100)]
    l.AddEntry(0,"Ratio_{#sigma} = %.2f %%" % ((gPOST.GetParameter(2)/gPRE.GetParameter(2)-1)*100),"")
    l.Draw("same")
    suffix = "JES"
    if fname.find("JER")!=-1:
        suffix = "JER"
    if fname.find("up")!=-1:
        suffix= suffix+"up"
    if fname.find("down")!=-1:
        suffix= suffix+"down"    
    canv.SaveAs("/mnt/t3nfs01/data01/shome/dschafer/AnalysisOutput/figures/systematics/preVsPostSmearing_pt"+suffix+"_M"+str(int(mass[0]))+".pdf")
    time.sleep(2)
    del canv, hPRE, hPOST
    
    return ratio 

if __name__=="__main__":
    gStyle.SetOptTitle(0)
    gStyle.SetOptStat(0)

    mass =[1200,1400,1800]#,3000,3500,4000,4500]
    systematics = ["JESup","JESdown","JERup","JERdown"]
    JESup =[]
    JESdown =[]
    JERup = []
    JERdown =[]
    JESup_peak =[]
    JESdown_peak =[]
    JERup_peak = []
    JERdown_peak =[]

     #"ExoDiBosonAnalysis.TEST.VV.root"
    for sys in systematics:
        for m in mass:
            fname = "/mnt/t3nfs01/data01/shome/dschafer/AnalysisOutput/80X/SignalMC/Summer16/Sys/ExoDiBosonAnalysis.ZprimeWW_13TeV_"+str(int(m))+"GeV."+sys+".root"
            r = doFit(fname)
            if fname.find("JESup")!=-1:
                JESup.append(r[0])
                JESup_peak.append(r[1])
            if fname.find("JESdown")!=-1:
                JESdown.append(r[0])
                JESdown_peak.append(r[1])
            if fname.find("JERup")!=-1:
                JERup.append(r[0])
                JERup_peak.append(r[1])
            if fname.find("JERdown")!=-1:
                JERdown.append(r[0])
                JERdown_peak.append(r[1])
    i=0 
    print "width: "
    print "mass:      JESup/JESdown       JERup/JERdown"
    for m in mass:
        print str(m)+"   "+str(round(JESup[i],2))+"/"+str(round(JESdown[i],2))+"   "+str(round(JERup[i],2))+"/"+str(round(JERdown[i],2))
        i+=1
        
    print "peak position: "
    i=0
    print "mass:      JESup/JESdown       JERup/JERdown"
    for m in mass:
        print str(m)+"   "+str(round(JESup_peak[i],2))+"/"+str(round(JESdown_peak[i],2))+"   "+str(round(JERup_peak[i],2))+"/"+str(round(JERdown_peak[i],2))
        i+=1
                
    
    
    
