#python do-jes.py -s JES -c VV --signal BulkWW
import xml.etree.ElementTree as ET
import os,commands
import sys
from optparse import OptionParser
import ROOT
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
  

argv = sys.argv
parser = OptionParser()
parser.add_option("--doCV", dest="doCV", default=False, action="store_true",help="Produce samples with central value! No scaleUP/DOWN")
parser.add_option('-s', '--sys',action="store",type="string",dest="sys",default="JES")           #JES JER JMS JMR ALL
parser.add_option('-c', '--channel',action="store",type="string",dest="channel",default="VV")    #VV qV
parser.add_option('-S', '--signal',action="store",type="string",dest="signal",default="BulkWW")  #VBulkWW BulkZZ WprimeWZ ZprimeWW QstarQW QstarQZ
(opts, args) = parser.parse_args(argv)

def drawMass(sys):
  
  outpath = '/mnt/t3nfs01/data01/shome/thaarres/EXOVVAnalysisRunII/ExoDiBosonAnalysis/forSystematics/'
    
  masses = [1000,1200,1400,1600,1800,2000,2500,3000,3500,4000,4500]
  masses = [1000]
  
  signals = ['%s'%opts.signal]
  if opts.signal == 'all':
    signals = ['BulkWW','BulkZZ','WprimeWZ',"ZprimeWW"]
  
  for signal in signals:
  
    fout = ['%s/%s/%ssys_HPVV_%s.txt'%(outpath,sys,sys,signal),'%s/%s/%ssys_LPVV_%s.txt'%(outpath,sys,sys,signal),
            '%s/%s/%ssys_HPWW_%s.txt'%(outpath,sys,sys,signal),'%s/%s/%ssys_LPWW_%s.txt'%(outpath,sys,sys,signal),
            '%s/%s/%ssys_HPWZ_%s.txt'%(outpath,sys,sys,signal),'%s/%s/%ssys_LPWZ_%s.txt'%(outpath,sys,sys,signal),
            '%s/%s/%ssys_HPZZ_%s.txt'%(outpath,sys,sys,signal),'%s/%s/%ssys_LPZZ_%s.txt'%(outpath,sys,sys,signal)]

    cuts = []
    debugs = []

    debugs.append("VV HP category")
    cut =  "jet_puppi_softdrop_jet1 > 65 && jet_puppi_softdrop_jet1 < 105 && jet_puppi_softdrop_jet2 > 65 && jet_puppi_softdrop_jet2 < 105 && jet_puppi_tau2tau1_jet1 < 0.4 && jet_puppi_tau2tau1_jet2 < 0.4"
    cuts.append(cut)

    debugs.append("VV LP category")
    cut =  "jet_puppi_softdrop_jet1 > 65 && jet_puppi_softdrop_jet1 < 105 && jet_puppi_softdrop_jet2 > 65 && jet_puppi_softdrop_jet2 < 105 && ((jet_puppi_tau2tau1_jet1 < 0.4 && jet_puppi_tau2tau1_jet2 > 0.4 && jet_puppi_tau2tau1_jet2 < 0.75) || (jet_puppi_tau2tau1_jet2 < 0.4 && jet_puppi_tau2tau1_jet1 > 0.4 && jet_puppi_tau2tau1_jet1 < 0.75))"
    cuts.append(cut)

    debugs.append("WW HP category")
    cut =  "jet_puppi_softdrop_jet1 > 65 && jet_puppi_softdrop_jet1 < 85 && jet_puppi_softdrop_jet2 > 65 && jet_puppi_softdrop_jet2 < 85 && jet_puppi_tau2tau1_jet1 < 0.4 && jet_puppi_tau2tau1_jet2 < 0.4"
    cuts.append(cut)

    debugs.append("WW LP category")
    cut =  "jet_puppi_softdrop_jet1 > 65 && jet_puppi_softdrop_jet1 < 85 && jet_puppi_softdrop_jet2 > 65 && jet_puppi_softdrop_jet2 < 85 &&  ((jet_puppi_tau2tau1_jet1 < 0.4 && jet_puppi_tau2tau1_jet2 > 0.4 && jet_puppi_tau2tau1_jet2 < 0.75) || (jet_puppi_tau2tau1_jet2 < 0.4 && jet_puppi_tau2tau1_jet1 > 0.4 && jet_puppi_tau2tau1_jet1 < 0.75))"
    cuts.append(cut)

    debugs.append("WZ HP category")
    cut =  "((jet_puppi_softdrop_jet1 > 65 && jet_puppi_softdrop_jet1 < 85 && jet_puppi_softdrop_jet2 > 85 && jet_puppi_softdrop_jet2 < 105) || (jet_puppi_softdrop_jet1 > 85 && jet_puppi_softdrop_jet1 < 105 && jet_puppi_softdrop_jet2 > 65 && jet_puppi_softdrop_jet2 < 85)) && jet_puppi_tau2tau1_jet1 < 0.4 && jet_puppi_tau2tau1_jet2 < 0.4"
    cuts.append(cut)

    debugs.append("WZ LP category")
    cut =  "((jet_puppi_softdrop_jet1 > 65 && jet_puppi_softdrop_jet1 < 85 && jet_puppi_softdrop_jet2 > 85 && jet_puppi_softdrop_jet2 < 105) || (jet_puppi_softdrop_jet1 > 85 && jet_puppi_softdrop_jet1 < 105 && jet_puppi_softdrop_jet2 > 65 && jet_puppi_softdrop_jet2 < 85)) &&  ((jet_puppi_tau2tau1_jet1 < 0.4 && jet_puppi_tau2tau1_jet2 > 0.4 && jet_puppi_tau2tau1_jet2 < 0.75) || (jet_puppi_tau2tau1_jet2 < 0.4 && jet_puppi_tau2tau1_jet1 > 0.4 && jet_puppi_tau2tau1_jet1 < 0.75))"
    cuts.append(cut)

    debugs.append("ZZ HP category")
    cut =  "jet_puppi_softdrop_jet1 > 85 && jet_puppi_softdrop_jet1 < 105 && jet_puppi_softdrop_jet2 > 85 && jet_puppi_softdrop_jet2 < 105 && jet_puppi_tau2tau1_jet1 < 0.4 && jet_puppi_tau2tau1_jet2 < 0.4"
    cuts.append(cut)

    debugs.append("ZZ LP category")
    cut =  "jet_puppi_softdrop_jet1 > 85 && jet_puppi_softdrop_jet1 < 105 && jet_puppi_softdrop_jet2 > 85 && jet_puppi_softdrop_jet2 < 105 && ((jet_puppi_tau2tau1_jet1 < 0.4 && jet_puppi_tau2tau1_jet2 > 0.4 && jet_puppi_tau2tau1_jet2 < 0.75) || (jet_puppi_tau2tau1_jet2 < 0.4 && jet_puppi_tau2tau1_jet1 > 0.4 && jet_puppi_tau2tau1_jet1 < 0.75))"
    cuts.append(cut)
    
    for f in range(len(fout)):
      
      print ""
      print debugs[f]
      print cuts[f]
      print ""

      for mass in masses:
        
        # canv = getCanvas()
#         canv.cd()
#         vFrame = canv.DrawFrame(65,0,105,20)
#         vFrame.SetYTitle("A.U")
#         vFrame.SetXTitle("PUPPI softdrop mass (GeV)")
#         vFrame.GetXaxis().SetTitleSize(0.06)
#         vFrame.GetXaxis().SetTitleOffset(0.95)
#         vFrame.GetXaxis().SetLabelSize(0.05)
#         vFrame.GetYaxis().SetTitleSize(0.06)
#         vFrame.GetYaxis().SetTitleOffset(1.3)
#         vFrame.GetYaxis().SetLabelSize(0.05)
#         vFrame.GetXaxis().SetNdivisions(807)
#         vFrame.GetYaxis().SetNdivisions(703)
          
        #Central value
        print "######## Mass = %i #########" %mass
        
        
        l = TLegend(0.7550336,0.7692308,0.9060403,0.9090909)
        l.SetTextSize(0.035)
        l.SetLineColor(0)
        l.SetShadowColor(0)
        l.SetLineStyle(1)
        l.SetLineWidth(1)
        l.SetFillColor(0)
        l.SetFillStyle(0)
        l.SetMargin(0.35)
        
        #Scale up value
        fnameUP = outpath + 'ExoDiBosonAnalysis.%s_13TeV_%sGeV.%sup.root' %(signal,mass,sys)
        tfileUP = ROOT.TFile.Open(fnameUP,'READ')
        treeUP = tfileUP.Get("tree")
        treeUP.Draw("jet_puppi_softdrop_jet1",cuts[f],"")
        gPad.GetListOfPrimitives().At(0).SetLineColor(kRed)
        l.AddEntry(gPad.GetListOfPrimitives().At(0) ,"%s up"%sys,"l")
        
        #Scale down value
        fnameDOWN = outpath + 'ExoDiBosonAnalysis.%s_13TeV_%sGeV.%sdown.root' %(signal,mass,sys)
        tfileDOWN = ROOT.TFile.Open(fnameDOWN,'READ')
        treeDOWN = tfileDOWN.Get("tree")
        treeDOWN.Draw("jet_puppi_softdrop_jet1",cuts[f],"same")
        gPad.GetListOfPrimitives().At(1).SetLineColor(kGreen)
        l.AddEntry(gPad.GetListOfPrimitives().At(1) ,"%s down"%sys,"l")
        
        fnameCV = outpath + 'ExoDiBosonAnalysis.%s_13TeV_%sGeV.CV.root' %(signal,mass)
        tfileCV = ROOT.TFile.Open(fnameCV,'READ')
        treeCV  = tfileCV.Get("tree")
        treeCV.Draw("jet_puppi_softdrop_jet1",cuts[f],"same")
        gPad.GetListOfPrimitives().At(2).SetLineColor(kBlack)
        l.AddEntry(gPad.GetListOfPrimitives().At(2) ,"%s CV"%sys,"l")
        # htemp.SetLineColor(kRed)
        
        gPad.Update()
        l.Draw("same")
        gPad.Update()
        
        gPad.GetListOfPrimitives().Print()
        c1.Print(outpath+"/control-plots/%s%s_%s_%s.pdf"%(signal,mass,sys,debugs[f].replace(" category","").replace(" ","")))
        tfileDOWN.Close()
        tfileDOWN.Delete()
        tfileCV.Close()
        tfileCV.Delete()
        tfileUP.Close()
        tfileUP.Delete()
       

       
### Start  main
if __name__ == '__main__':
  
  #Calculate yields 
  if opts.sys == 'ALL':
    systematics = ['JES','JER','JMS','JMR']
    for s in systematics:
      drawMass(s)
  else:
    drawMass(opts.sys)
  
        