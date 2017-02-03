import ROOT
from ROOT import *
import time
import CMS_lumi, tdrstyle
#import PhysicsTools.Utilities as PT
from optparse import OptionParser
import os

parser = OptionParser()
parser.add_option('--variable', '--variable',action="store",type="string",dest="variable",default="Eta")
(options, args) = parser.parse_args()



def get_canvas(cname,lumi):

   CMS_lumi.lumi_13TeV = "%.1f pb^{-1},#sqrt{s} = " %(lumi)
   CMS_lumi.writeExtraText = 0
   CMS_lumi.extraText = "Preliminary"

   iPos = 0
   if( iPos==0 ): CMS_lumi.relPosX = 0.15

   H_ref = 600; 
   W_ref = 800; 
   W = W_ref
   H  = H_ref

   T = 0.08*H_ref
   B = 0.12*H_ref 
   L = 0.12*W_ref
   R = 0.06*W_ref

   canvas = ROOT.TCanvas(cname,cname,W,H)
   canvas.SetFillColor(0)
   canvas.SetBorderMode(0)
   canvas.SetFrameFillStyle(0)
   canvas.SetFrameBorderMode(0)
   canvas.SetLeftMargin( L/W+0.01 )
   canvas.SetRightMargin( R/W )
   canvas.SetTopMargin( T/H )
   canvas.SetBottomMargin( B/H+0.03 )
   canvas.SetTickx()
   canvas.SetTicky()
   
   return canvas



# ==============================================================================================================================
#=============== test PU weights in MC Distribution ============================================================================
#===============================================================================================================================
if __name__=="__main__":
    #fMC = "/mnt/t3nfs01/data01/shome/dschafer/AnalysisOutput/80X/Bkg/ExoDiBosonAnalysis.QCD_Pt_15to7000_PUFlat_0to70_pythia8_VVdijet.root"
    fMC = "/mnt/t3nfs01/data01/shome/dschafer//AnalysisOutput/80X/Bkg/tmp.root"
    fSignalMC = '/mnt/t3nfs01/data01/shome/dschafer/AnalysisOutput/80X/PU/ExoDiBosonAnalysis.BulkZZ_13TeV_1200GeV.VV.root'
    fData = "/mnt/t3nfs01/data01/shome/dschafer/AnalysisOutput/80X/Data/tmp.root"
    testfmc = TFile.Open(fMC,'READ')
    
    testpumc   = testfmc.Get(options.variable)


    testfsignalmc = TFile.Open(fSignalMC,'READ')
    signalmc   = testfsignalmc.Get(options.variable)
    testfdata = TFile.Open(fData,'READ')
    testpudata = testfdata.Get(options.variable)
    xs = 2022100000.
    Nmc =  8093024.
    
   
    #cw = TCanvas("cw","cw",800,800)
    #cw.Divide(3,3)
    #wmc     = testfmc.Get("Weight"     )
    #pumc    = testfmc.Get("PUWeight"   )
    #lumimc  = testfmc.Get("LumiWeight" )
    #genmc   = testfmc.Get("GenWeight"  )
    #ptmc    = testfmc.Get("PtWeight"   )
    #btagmc  = testfmc.Get("BtagWeight" )
    #hltmc   = testfmc.Get("HLTWeight"  )
    #cw.cd(1)
    #wmc.Draw("PC")
    #cw.cd(2)
    #pumc.Draw("PC")
    #cw.cd(3)
    #genmc.Draw("PC")
    #cw.cd(4)
    #ptmc.Draw("PC")
    #cw.cd(5)
    #btagmc.Draw("PC")
    #cw.cd(6)
    #hltmc.Draw("PC")
    #cw.Update()
    
    #testpudata.GetXaxis().SetRangeUser(0,50);
    
    
    testpudata.Scale(1/testpudata.Integral())
    testpumc.Scale(1/testpumc.Integral())
    signalmc.Scale(1/signalmc.Integral())
    
    for w in range(1,testpumc.GetNbinsX()+1):
        print str(w)+ " "+str(testpumc.GetBinContent(w))
        
    
    leg = ROOT.TLegend(0.5574713,0.729021,0.7571839,0.8653846,"","NDC")
    leg.SetLineWidth(2)
    leg.SetBorderSize(0)
    leg.SetFillColor(0)
    leg.SetTextFont(42)
    leg.SetTextSize(0.035)
    leg.SetTextAlign(12)
        
    testpumc.SetLineColor(kBlue)
    testpudata.SetLineColor(kBlack)
    signalmc.SetLineColor(kRed)
    
    testpudata.SetMarkerStyle(20)
    testpudata.SetLineStyle(2)
    testpudata.GetXaxis().SetTitle(options.variable)
    testpudata.GetYaxis().SetTitle('Normalized')
    testpudata.GetYaxis().SetTitleOffset(1.1)
    testpudata.GetYaxis().SetNdivisions(505)
    testpudata.SetMaximum(0.1)
    leg.AddEntry(testpudata,'Run 2016 full promtreco','PL')
    leg.AddEntry(testpumc,'QCD MC','L')
    #leg.AddEntry(signalmc,'G_{Bulk} #rightarrow ZZ (1.2 TeV)','L')
    

    canvtest = get_canvas('ctest',36.4)
    canvtest.SetLogy()
    canvtest.cd()
    testpudata.Draw('PC')
    testpumc.Draw('same')
    #signalmc.Draw('same')
    leg.Draw()

    #CMS_lumi.CMS_lumi(canvtest, 4, 0)	
    #canvtest.cd()
    #canvtest.Update()
    #canvtest.RedrawAxis()
    #testframe = canvtest.GetFrame()
    #testframe.Draw()
    #canvtest.cd()
    #canvtest.Update()
    
 

    time.sleep(10)
