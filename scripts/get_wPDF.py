import os
import glob
import math
import array
import ROOT
import ntpath
import sys
import subprocess
import time
import numpy
from subprocess import Popen
from optparse import OptionParser
from array import array

from ROOT import gROOT, TPaveLabel, gStyle, gSystem, TGaxis, TStyle, TLatex, TString, TF1,TFile,TLine, TLegend, TH1D,TH1F,TH2D,THStack,TChain, TCanvas, TMatrixDSym, TMath, TText, TPad

from array import array

parser = OptionParser()

parser.add_option('--filename', action="store",type="string",dest = "filename",default="../wpdf_M1000_qV.txt")
parser.add_option('--p',action="store",type="string",dest="printoption",default="N")
parser.add_option('--s',action="store",type="string",dest="suffix",default="")

(options, args) = parser.parse_args()


#run with :  python scripts/get_wPDF.py --filename wpdf_M1000_QstarQW --p all --s _BulkWW


def getList(filename,variable):
    f = open(filename+".txt",'r').readlines();
  #f.readlines()
    N=[]
  
    for line in f:
        #line = f.readline();
        #print line
        if line.find(variable) != -1:
            l = line.split(":")
            N.append(float(l[1]))
    
    return N


def writeInfo(mass,suffix,printoption):
  if printoption.find("all")!=-1:
    print "mass    mean     std      std (%)"
    print " ====================================================" 
    for m in mass:
        N_tmp = numpy.array(getList("wpdf_M"+str(int(m))+suffix,"N :"))
        m_N_tmp = numpy.mean(N_tmp)
        std_N_tmp = numpy.std(N_tmp)
        print str(int(m))+" "+str(numpy.round(m_N_tmp,1))+"     "+str(numpy.round(std_N_tmp,1))+"      "+str(numpy.round(std_N_tmp/m_N_tmp*100,2))
        #print "--------------------------------------------------------------------"
    print "mass    mean     std      std (%)"
    print " ===================================================="
    for m in mass:
        Npassed_tmp = numpy.array(getList("wpdf_M"+str(int(m))+suffix,"N passed"))
        m_Npassed_tmp = numpy.mean(Npassed_tmp)
        std_Npassed_tmp = numpy.std(Npassed_tmp)
        print str(int(m))+" "+str(numpy.round(m_Npassed_tmp,1))+"     "+str(numpy.round(std_Npassed_tmp,1))+"    "+str(numpy.round(std_Npassed_tmp/m_Npassed_tmp*100,2))
        #print "--------------------------------------------------------------------"
    print "mass    mean     std      std (%)"
    print " ===================================================="
    for m in mass:
        N_tmp = numpy.array(getList("wpdf_M"+str(int(m))+suffix,"N :"))
        Npassed_tmp = numpy.array(getList("wpdf_M"+str(int(m))+suffix,"N passed"))
        Eff_tmp = []
        for n in range(0,len(N_tmp)):
            Eff_tmp.append(Npassed_tmp[n]/N_tmp[n])
        eff_tmp = numpy.array(Eff_tmp)
        m_eff_tmp = numpy.mean(eff_tmp)
        std_eff_tmp = numpy.std(eff_tmp)
        print str(int(m))+" "+str(numpy.round(m_eff_tmp,4))+"     "+str(numpy.round(std_eff_tmp,4))+"    "+str(numpy.round(std_eff_tmp/m_eff_tmp*100,2))
        #print "--------------------------------------------------------------------"
  
      
    
  else:    
    print "mass    mean     std      std (%)"
    print " ===================================================="
    for m in mass:
        N_tmp = numpy.array(getList("wpdf_M"+str(int(m))+suffix,"N :"))
        Npassed_tmp = numpy.array(getList("wpdf_M"+str(int(m))+suffix,"N passed"))
        #print " mass : "+str(int(m))
        m_N_tmp = numpy.mean(N_tmp)
        std_N_tmp = numpy.std(N_tmp)
        m_Npassed_tmp = numpy.mean(Npassed_tmp)
        std_Npassed_tmp = numpy.std(Npassed_tmp)
        if printoption == "N":
            print str(int(m))+" "+str(numpy.round(m_N_tmp,1))+"     "+str(numpy.round(std_N_tmp,1))+"      "+str(numpy.round(std_N_tmp/m_N_tmp*100,2))
        if printoption.find("passed")!=-1:
            print str(int(m))+" "+str(numpy.round(m_Npassed_tmp,1))+"     "+str(numpy.round(std_Npassed_tmp,1))+"    "+str(numpy.round(std_Npassed_tmp/m_Npassed_tmp*100,2))
        Eff_tmp = []
        for n in range(0,len(N_tmp)):
            Eff_tmp.append(Npassed_tmp[n]/N_tmp[n])
        eff_tmp = numpy.array(Eff_tmp)
        m_eff_tmp = numpy.mean(eff_tmp)
        std_eff_tmp = numpy.std(eff_tmp)
        if printoption.find("acc")!=-1:
            print str(int(m))+" "+str(numpy.round(m_eff_tmp,4))+"     "+str(numpy.round(std_eff_tmp,4))+"    "+str(numpy.round(std_eff_tmp/m_eff_tmp*100,2))
        print "--------------------------------------------------------------------"
  
    

#######################################
############ Main Code ################
#######################################

if __name__== '__main__':
  
  
  filename = options.filename;
  printoption  = options.printoption;
  suffix = options.suffix;
  current_directory = os.getcwd();
  N=[];
  Npassed=[];
  
  f = open(filename+".txt",'r').readlines();
  #f.readlines()
  
  for line in f:
        #line = f.readline();
        #print line
        if line.find("N : ") != -1:
            l = line.split(":")
            N.append(float(l[1]))
            #print l
        if line.find("N passed")!=-1:
            l = line.split(":")
            Npassed.append(float(l[1]))
        
        
  print N
  print len(N)
  print Npassed
  print len(Npassed)
  
  npN = numpy.array(N)
  npNpassed = numpy.array(Npassed)
  mean_N = numpy.mean(npN)
  std_N  = numpy.std(npN)
  mean_Npassed = numpy.mean(npNpassed)
  std_Npassed = numpy.std(npNpassed)
  print mean_N
  
  text = ROOT.TLatex()
  text.SetTextFont(43)
  text.SetTextSize(15)
  
  scaler = 2.0;
  
  hN = TH1F("N","N",20,mean_N-std_N*(scaler),mean_N+std_N*(scaler))
  for n in N:
      hN.Fill(n);
  hNpassed = TH1F("Npassed","Npassed",20,mean_Npassed+std_Npassed*(scaler),mean_Npassed+std_Npassed*(scaler))
  for n in Npassed:
      hNpassed.Fill(n);
      
  c = TCanvas("c","c",400,400)
  hN.SetMaximum(20)
  hN.SetStats(0)
  hN.SetTitle("")
  hN.GetXaxis().SetTitle("# events")
  hN.Draw()
  text.DrawLatex(mean_N+std_N*(0.5),18,("m="+str(numpy.round(mean_N,1))))
  text.DrawLatex(mean_N+std_N*0.5,16.5,"#delta m="+str(numpy.round(std_N, 1)))
  c1 = TCanvas("c1","c1",400,400)
  hNpassed.SetStats(0)
  hNpassed.GetXaxis().SetTitle("# events")
  hNpassed.SetTitle("")
  hNpassed.Draw()
  hNpassed.SetMaximum(20)
  text.DrawLatex(mean_Npassed+std_Npassed*1,18,"m="+str(numpy.round(mean_Npassed,1)))
  text.DrawLatex(mean_Npassed+std_Npassed*1,16.5,"#delta m="+str(numpy.round(std_Npassed, 1)))
  
  Eff = []
  for n in range(0,len(N)):
      Eff.append(Npassed[n]/N[n])
  
  npEff = numpy.array(Eff)
  mean_eff = numpy.mean(npEff)
  std_eff  = numpy.std(npEff);
  
  for i in Eff:
      print i
  print " standard deviation acceptance : "+str(std_eff)+" unc : "+str(std_eff/mean_eff*100)
  print " standard deviation cross section : "+str(std_N)+" unc : "+str(std_N/mean_N*100)
  print str(len(Eff))
 
  hEff = TH1F("acceptance","acceptance",20,mean_eff-std_eff*(scaler),mean_eff+std_eff*(scaler))
  for n in range(0,len(N)):
      hEff.Fill(Npassed[n]/N[n])
      
  
  c2 = TCanvas("c2","c2",400,400)
  hEff.SetStats(0)
  hEff.SetMaximum(25)
  hEff.SetTitle("")
  hEff.GetXaxis().SetTitle(" acceptance")
  hEff.Draw()
  text.DrawLatex(mean_eff+std_eff*(1),18,"m ="+str(numpy.round(mean_eff,4)))
  text.DrawLatex(mean_eff+std_eff*1,16.5,"#delta m="+str(numpy.round(std_eff, 4)))
  
  c.SaveAs("results/misc/N_"+filename+".pdf")
  c1.SaveAs("results/misc/Npassed_"+filename+".pdf")
  c2.SaveAs("results/misc/Eff_"+filename+".pdf")
  
  mass = [800,1000,1200,1400,1600,1800,2000,2500,3000,3500,4000,4500]#,5000,5500,6000,6500,7000]
  #mass=[1000,1400,2000,2500,3000,4000,4500,5000,5500,6000,6500,7000,7500]
  #mass = [1000,1400,2500,3500,4000]
  
  writeInfo(mass,suffix,printoption)
  
  time.sleep(10)
  
