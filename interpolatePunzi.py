from ROOT import *
import numpy as np
from array import array

masses = [1200,1400,1600,1800,2000,2500,3000,3500,4000]
xbins = array('f', [1100,1300,1500,1700,1900,2100,2900,3100,3900,4100])
c1 = TCanvas(" ","",600,400)
Best_btag_discriminant = TH1F('Best_btag_discriminant','Best_btag_discriminant',9,xbins)


for masspoint in masses :
    inputname = 'PunziSignificance_for_M=%s_GeV_WZ.root' %str(masspoint)
    
    file = TFile.Open(inputname, 'READ') 
    print file
    Hist = file.Get('PunziSignificance')
    #Hist = TH1F(Hist)
    #print type(Hist)
    nmax = Hist.GetMaximumBin()
    tag_discriminant = Hist.GetXaxis().GetBinCenter(nmax)
    Best_btag_discriminant.Fill(masspoint,tag_discriminant)


Best_btag_discriminant.GetYaxis().SetRangeUser(-1,1)
Best_btag_discriminant.SetMarkerStyle(20)
Best_btag_discriminant.Draw('hist p')
Best_btag_discriminant.GetXaxis().SetTitle("dijet invariant mass")
Best_btag_discriminant.GetYaxis().SetTitle("Best_btag_discriminant")

Outfilename = "Best_btag_discriminant_WZ.root"
Outfile = TFile(Outfilename, 'RECREATE')
Outfile.Append(Best_btag_discriminant)
Outfile.Write()


x = raw_input('Finished')