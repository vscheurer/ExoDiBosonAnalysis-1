#run with : python extractMjj.py --filename ExoDiBosonAnalysis.JetHT_Run2016H_part2_data_sideband_doubleTag.root --isMC False --s Run2016H_part2 --region SB
# fills histos with V,W,Z and NP,HP,LP categories for data sideband when isMC==False!

from subprocess import Popen
from optparse import OptionParser
from array import array
import ROOT

from ROOT import gROOT, TPaveLabel, gStyle, gSystem, TGaxis, TStyle, TLatex, TString, TF1,TFile,TLine, TLegend, TH1D,TH1F,TH2D,THStack,TChain, TCanvas, TMatrixDSym, TMath, TText, TPad

from array import array

parser = OptionParser()

parser.add_option('--filename', action="store",type="string",dest = "filename",default="../config/BulkWW_M1000.xml")
parser.add_option('--outdir',action="store",type="string",dest="outdir",default="../results/")
parser.add_option('--s',action="store",type="string",dest="suffix",default="")
parser.add_option('--isMC',action="store",type="string",dest="isMC",default="True")
parser.add_option('--region',action="store",type="string",dest="region",default="SB")
parser.add_option('--mode',action='store',type='string',dest='mode',default='Mjj')

(options, args) = parser.parse_args()



def openRootFile(filename,inputdir):
    f = ROOT.TFile(inputdir+filename)
    print inputdir+filename
    #print f
    return f

def passedMjjCut(tree):
    mass = tree.MVV
    if mass>=1055:
        return True
    else:
        return False

def getMjj(tree):
    mass = tree.MVV
    return mass

def passedTau21(category,tree):
    HPHigh = 0.4
    HPLow  = 0.00
    LPLow  = 0.4
    LPHigh = 0.75
    tau21_jet1 = tree.jet_tau2tau1_jet1
    tau21_jet2 = tree.jet_tau2tau1_jet2
   # print str(tau21_jet1)+"   "+str(tau21_jet2)
    if category.find("HP")!=-1 and category.find("q")==-1:
        if tau21_jet1 <= HPHigh and tau21_jet1 > HPLow and tau21_jet2 <= HPHigh and tau21_jet2 > HPLow:
    #        print "passed HP "
            return True;
    if category.find("LP")!=-1 and category.find("q")==-1:
        one = False
        two = False
        if  (tau21_jet1 > HPLow and tau21_jet1 <= HPHigh and tau21_jet2 > LPLow and tau21_jet2 <= LPHigh):
            one = True
        if  (tau21_jet2 > HPLow and tau21_jet2 <= HPHigh and tau21_jet1 > LPLow and tau21_jet1 <= LPHigh):
            two = True
        if one or two: 
     #       print "passed LP "
            return True;
    if category.find("HP")!=-1 and category.find("q")!=-1:
        if tau21_jet1 <= 0.4:# or tau21_jet2 <= 0.4:
            return True;
    if category.find("LP")!=-1 and category.find("q")!=-1:
        if (LPLow < tau21_jet1 and tau21_jet1 <= LPHigh) : #or (LPLow < tau21_jet2 and tau21_jet2 <= LPHigh): 
            return True;
    if category.find("NP")!=-1:
        return True;
    return False;

def checkMassWindow(category,region,tree):
    mass1 = tree.jet_puppi_softdrop_jet1
    mass2 = tree.jet_puppi_softdrop_jet2
    if region.find("SB")!=-1:
        if category.find("V") !=-1 and category.find("q")==-1:
            if ((65 < mass1 and mass1 <= 105) or (65 < mass2 and mass2 <= 105)) and ((20 < mass1 and mass1 < 65) or (20 < mass2 and mass2 < 65)):
                return True
            else:
                return False
        if category.find("W") !=-1 and category.find("q")==-1:
            if (65 < mass1 and mass1 <= 85) or (65 < mass2 and mass2 <= 85)  and ((20 < mass1 and mass1 < 65) or (20 < mass2 and mass2 < 65)):
                return True
            else:
                return False
        if category.find("Z") !=-1 and category.find("q")==-1:
            if (85 < mass1 and mass1 <= 105) or (85 < mass2 and mass2 <= 105) and ((20 < mass1 and mass1 < 65) or (20 < mass2 and mass2 < 65)): 
                return True
            else:
                return False
        if category.find("q")!=-1:
            return True
    if region.find("SR")!=-1:
        if category.find("WW") !=-1 and category.find("q")==-1:
            if (65 < mass1 and mass1 <= 85) and (65 < mass2 and mass2 <= 85):
                #print "passed WW " 
                return True
            else:
                return False
        if category.find("ZZ") !=-1 and category.find("q")==-1:
            if (85 < mass1 and mass1 <= 105) and (85 < mass2 and mass2 <= 105):
                #print " passed ZZ"
                return True
            else:
                return False
        if category.find("WZ") !=-1 and category.find("q")==-1:
            if ((65 < mass1 and mass1 <= 85) and (85 < mass2 and mass2 <= 105)) or ((85 < mass1 and mass1 <= 105) and (65 < mass2 and mass2 <= 85)):
                #print " passed WZ" 
                return True
            else:
                return False
        if category.find("qV")!=-1:
            if (mass1 > 65 and mass1 <= 105 and not(mass2 > 65 and mass2 <= 105)) or (mass2 > 65 and mass2 <= 105 and not(mass1 > 65 and mass1 <= 105)):  
                return True
            else:
                return False
        if category.find("qW")!=-1:
            if (mass1 > 65 and mass1 <= 85 and not(mass2 > 65 and mass2 <= 105)) or (mass2 > 65 and mass2 <= 85 and not(mass1 > 65 and mass1 <= 85)): 
                return True
            else:
                return False
        if category.find("qZ")!=-1:
            if (mass1 > 85 and mass1 <= 105 and not(mass2 > 65 and mass2 <= 105)) or (mass2 > 85 and mass2 <= 105 and not(mass1 > 65 and mass1 <= 85)):
                return True
            else:
                return False
    return True

if __name__== '__main__':
    
    fname  = options.filename
    outdir = options.outdir
    suffix = options.suffix
    region = options.region
    mode   = options.mode
    isMC   = True;
    if options.isMC=="False":
        isMC = False;
    print isMC
    
    inputdir = "../../AnalysisOutput/80X/SignalMC/Summer16/"
    f = openRootFile(fname,inputdir)
    print f
    if mode.find('Mjj')!=-1:
        histonames=[]
    
        if region.find("SB")!=-1:
            if region.find("qV")==-1:
                histonames.append("VHP")
                histonames.append("VLP")
                histonames.append("WHP")
                histonames.append("WLP")
                histonames.append("ZHP")
                histonames.append("ZLP")
                histonames.append("VNP")
                histonames.append("WNP")
                histonames.append("ZNP")
            if region.find("qV")!=-1:
                histonames.append("qVHP")
                histonames.append("qVLP")
                histonames.append("qVNP")
                #histonames.append("qWHP")
                #histonames.append("qWLP")
                #histonames.append("qZHP")
                #histonames.append("qZLP")
                #histonames.append("qVNP")
                #histonames.append("qWNP")
                #histonames.append("qZNP")
            
            
        if region.find("SR")!=-1:
            if region.find("qV")==-1:
                histonames.append("VVHPHP")
                histonames.append("VVLPHP")
                histonames.append("VVLPLP")
                histonames.append("WWHPHP")
                histonames.append("WWLPHP")
                histonames.append("WWLPLP")
                histonames.append("ZZHPHP")
                histonames.append("ZZLPHP")
                histonames.append("ZZLPLP")
                histonames.append("WZHPHP")
                histonames.append("WZLPHP")
                histonames.append("WZLPLP")
                
                
            else:
                histonames.append("qVHP")
                histonames.append("qVLP")
                histonames.append("qWHP")
                histonames.append("qWLP")
                histonames.append("qZHP")
                histonames.append("qZLP")
                histonames.append("qVNP")
                histonames.append("qWNP")
                histonames.append("qZNP")
        
        
        
        
        
    
    
    
    
        nBins = 7000;
        minBins= 0;
        maxBins= 7000;

        
        h =[]
        
        lumi = 36400.
        numberEvents =8093024.
        xs = 2022100000.
        prodlumi = numberEvents/xs
            
        scale = lumi/prodlumi
        
        for n in histonames:
            h.append(ROOT.TH1D(n,n,nBins,minBins,maxBins))
            print n
        
        Mjj= f.Get('Mjj')
        nevents =0;
        for event in f.tree:
            if passedMjjCut(f.tree)==False:
                continue;
            nevents +=1;
            passedSomething = False
            
            if event.jet_puppi_tau2tau1_jet2 <= 0.40 and event.jet_puppi_tau2tau1_jet1 <= 0.40 :
                 h[0].Fill(event.MVV,event.weight) #VVHPHP
                 if (65. <= event.jet_puppi_softdrop_jet1 <= 85. and 65. <= event.jet_puppi_softdrop_jet2 <= 85.) :
                    h[3].Fill(event.MVV,event.weight) #WWHPHP
                 if (85. < event.jet_puppi_softdrop_jet1 <= 105. and 85. < event.jet_puppi_softdrop_jet2 < 105.) :
                    h[6].Fill(event.MVV,event.weight) #ZZHPHP
                 if ( (85 < event.jet_puppi_softdrop_jet1 <= 105. and 65. <= event.jet_puppi_softdrop_jet2 <= 85.) or (85 < event.jet_puppi_softdrop_jet2 <= 105. and 65. <= event.jet_puppi_softdrop_jet1 <= 85.) ) :
                    h[9].Fill(event.MVV,event.weight) #WZHPHP
          
            if (event.jet_puppi_tau2tau1_jet2 <= 0.40 and 0.40 < event.jet_puppi_tau2tau1_jet1 <= 0.75) or (event.jet_puppi_tau2tau1_jet1 <= 0.40 and 0.40 < event.jet_puppi_tau2tau1_jet2 <= 0.75) :
                 h[1].Fill(event.MVV,event.weight) #VVHPLP
                 if (65 <= event.jet_puppi_softdrop_jet1 <= 85. and 65 <= event.jet_puppi_softdrop_jet2 < 85.) :
                    h[4].Fill(event.MVV,event.weight) #WWHPLP
                 if (85 < event.jet_puppi_softdrop_jet1 <= 105. and 85. < event.jet_puppi_softdrop_jet2 <= 105.) :
                    h[7].Fill(event.MVV,event.weight) #ZZHPLP
                 if ( (85 < event.jet_puppi_softdrop_jet1 <= 105. and 65. <= event.jet_puppi_softdrop_jet2 < 85.) or (85 < event.jet_puppi_softdrop_jet2 <= 105. and 65. <= event.jet_puppi_softdrop_jet1 < 85.) ) :
                    h[10].Fill(event.MVV,event.weight) #WZHPLP
                    
            if (0.40 < event.jet_puppi_tau2tau1_jet1 <= 0.75) and (0.40 < event.jet_puppi_tau2tau1_jet2 <= 0.75):
                 h[2].Fill(event.MVV,event.weight) #VVLPLP
                 if (65. <= event.jet_puppi_softdrop_jet1 <= 85. and 65. <= event.jet_puppi_softdrop_jet2 <= 85.) :
                    h[5].Fill(event.MVV,event.weight) #WWLPLP
                 if (85. < event.jet_puppi_softdrop_jet1 <= 105. and 85. < event.jet_puppi_softdrop_jet2 < 105.) :
                    h[8].Fill(event.MVV,event.weight) #ZZLPLP
                 if ( (85 < event.jet_puppi_softdrop_jet1 <= 105. and 65. <= event.jet_puppi_softdrop_jet2 <= 85.) or (85 < event.jet_puppi_softdrop_jet2 <= 105. and 65. <= event.jet_puppi_softdrop_jet1 <= 85.) ) :
                    h[11].Fill(event.MVV,event.weight) #WZLPLP
            
            #for i in range(0,len(histonames)):
                ##print getMjj(event)
                #if checkMassWindow(histonames[i],region,f.tree) and passedTau21(histonames[i],f.tree):
                    ##print "passed "+histonames[i]
                    #passedSomething=True
                    #if f.tree.puweight>100000:
                        #print "puweight infinite "#-> skip event"
                        #print getMjj(f.tree)
                        #print "weight:"
                        #print f.tree.weight
                        #print "lumi weight:"
                        #print f.tree.lumiweight
                        #print "gen weight:"
                        #print f.tree.genweight
                        #print "pu weight:"
                        #print f.tree.puweight
                        #print "btag weight:"
                        #print f.tree.btagweight
                        #print "pt weight:"
                        #print f.tree.ptweight
                        #print "=========================================="
                        ##continue
                    #if isMC==False:
                        #h[i].Fill(getMjj(f.tree),f.tree.weight)
                    #if isMC==True:
                        #w = f.tree.lumiweight*f.tree.puweight*f.tree.ptweight
                        #h[i].Fill(getMjj(f.tree),f.tree.weight)
                        
    
            
        print nevents
        if isMC==False:
            fout = ROOT.TFile(outdir+"Data_VV_"+region+"_"+suffix+".root","RECREATE")
            print  outdir+"Data_VV_"+region+"_"+suffix+".root"
            for obj in h:
                fout.WriteTObject(obj);

        else:
            fout = ROOT.TFile(outdir+"Signal_"+suffix+".root","RECREATE")
            Mjj.Scale(lumi)
            fout.WriteTObject(Mjj)
            #print outdir+"MC_VV_"+region+"_"+suffix+".root"
            for obj in h:
                obj.Scale(lumi)
                fout.WriteTObject(obj)
    
            
    if mode.find('qVcontamination')!=-1:
        numberSignalEvents_HP=0
        numberSignalEvents_NP=0
        numberSignalEvents_LP=0
        
        numberSignalEventsInVSidebandHP_HP=0
        numberSignalEventsInWSidebandHP_HP=0
        numberSignalEventsInZSidebandHP_HP=0
        numberSignalEventsInVSidebandHP_LP=0
        numberSignalEventsInWSidebandHP_LP=0
        numberSignalEventsInZSidebandHP_LP=0
        numberSignalEventsInVSidebandHP_NP=0
        numberSignalEventsInWSidebandHP_NP=0
        numberSignalEventsInZSidebandHP_NP=0
        
        numberSignalEventsInVSidebandLP_HP=0
        numberSignalEventsInWSidebandLP_HP=0
        numberSignalEventsInZSidebandLP_HP=0
        numberSignalEventsInVSidebandLP_LP=0
        numberSignalEventsInWSidebandLP_LP=0
        numberSignalEventsInZSidebandLP_LP=0
        numberSignalEventsInVSidebandLP_NP=0
        numberSignalEventsInWSidebandLP_NP=0
        numberSignalEventsInZSidebandLP_NP=0
        
        numberSignalEventsInVSidebandNP_HP=0
        numberSignalEventsInWSidebandNP_HP=0
        numberSignalEventsInZSidebandNP_HP=0
        numberSignalEventsInVSidebandNP_LP=0
        numberSignalEventsInWSidebandNP_LP=0
        numberSignalEventsInZSidebandNP_LP=0
        numberSignalEventsInVSidebandNP_NP=0
        numberSignalEventsInWSidebandNP_NP=0
        numberSignalEventsInZSidebandNP_NP=0
        
        
        for event in f.tree:
            numberSignalEvents_NP+=1
            
           
            if passedTau21("qNP",event):
                if  checkMassWindow("VNP",region,event):
                    numberSignalEventsInVSidebandNP_NP+=1
                if  checkMassWindow("WNP",region,event):
                    numberSignalEventsInWSidebandNP_NP+=1
                if  checkMassWindow("ZNP",region,event):
                    numberSignalEventsInZSidebandNP_NP+=1
                
                
                if  checkMassWindow("VLP",region,event) and passedTau21("LP",event):
                    numberSignalEventsInVSidebandLP_NP+=1
                if  checkMassWindow("WLP",region,event) and passedTau21("LP",event):
                    numberSignalEventsInWSidebandLP_NP+=1
                if  checkMassWindow("ZLP",region,event) and passedTau21("LP",event):
                    numberSignalEventsInZSidebandLP_NP+=1
            
            
                if  checkMassWindow("VHP",region,event) and passedTau21("HP",event):
                    numberSignalEventsInVSidebandHP_NP+=1
                if  checkMassWindow("WHP",region,event) and passedTau21("HP",event):
                    numberSignalEventsInWSidebandHP_NP+=1
                if  checkMassWindow("ZHP",region,event) and passedTau21("HP",event):
                    numberSignalEventsInZSidebandHP_NP+=1
        
        
            if passedTau21("qLP",event):
                 numberSignalEvents_LP+=1
                 if  checkMassWindow("VNP",region,event):
                     numberSignalEventsInVSidebandNP_LP+=1
                 if  checkMassWindow("WNP",region,event):
                     numberSignalEventsInWSidebandNP_LP+=1
                 if  checkMassWindow("ZNP",region,event):
                     numberSignalEventsInZSidebandNP_LP+=1
                 
                 
                 if  checkMassWindow("VLP",region,event) and passedTau21("LP",event):
                     numberSignalEventsInVSidebandLP_LP+=1
                 if  checkMassWindow("WLP",region,event) and passedTau21("LP",event):
                     numberSignalEventsInWSidebandLP_LP+=1
                 if  checkMassWindow("ZLP",region,event) and passedTau21("LP",event):
                     numberSignalEventsInZSidebandLP_LP+=1


                 if  checkMassWindow("VHP",region,event) and passedTau21("HP",event):
                     numberSignalEventsInVSidebandHP_LP+=1
                 if  checkMassWindow("WHP",region,event) and passedTau21("HP",event):
                     numberSignalEventsInWSidebandHP_LP+=1
                 if  checkMassWindow("ZHP",region,event) and passedTau21("HP",event):
                     numberSignalEventsInZSidebandHP_LP+=1
                     
            if passedTau21("qHP",event):
                numberSignalEvents_HP+=1;
                if  checkMassWindow("VNP",region,event):
                    numberSignalEventsInVSidebandNP_HP+=1
                if  checkMassWindow("WNP",region,event):
                    numberSignalEventsInWSidebandNP_HP+=1
                if  checkMassWindow("ZNP",region,event):
                    numberSignalEventsInZSidebandNP_HP+=1
                
                
                if  checkMassWindow("VLP",region,event) and passedTau21("LP",event):
                    numberSignalEventsInVSidebandLP_HP+=1
                if  checkMassWindow("WLP",region,event) and passedTau21("LP",event):
                    numberSignalEventsInWSidebandLP_HP+=1
                if  checkMassWindow("ZLP",region,event) and passedTau21("LP",event):
                    numberSignalEventsInZSidebandLP_HP+=1


                if  checkMassWindow("VHP",region,event) and passedTau21("HP",event):
                    numberSignalEventsInVSidebandHP_HP+=1
                if  checkMassWindow("WHP",region,event) and passedTau21("HP",event):
                    numberSignalEventsInWSidebandHP_HP+=1
                if  checkMassWindow("ZHP",region,event) and passedTau21("HP",event):
                    numberSignalEventsInZSidebandHP_HP+=1
                    
                    
        print '==================='+fname+'======================================================='
        print "number of signal events: NP "+str(numberSignalEvents_NP)+" LP "+str(numberSignalEvents_LP)+" HP "+str(numberSignalEvents_HP)
        print "  sidebands          &   signal NP           &  signal LP         &    signal HP      \\\\"
        print "VNP                  &"+ str(numberSignalEventsInVSidebandNP_NP)+" &   "+str(numberSignalEventsInVSidebandNP_LP)+" &  "+ str(numberSignalEventsInVSidebandNP_HP)+"\\\\"
        print "VLP                  &"+ str(numberSignalEventsInVSidebandLP_NP)+" &   "+str(numberSignalEventsInVSidebandLP_LP)+" &  "+ str(numberSignalEventsInVSidebandLP_HP)+"\\\\"
        print "VHP                  &"+str(numberSignalEventsInVSidebandHP_NP)+"  &  "+str(numberSignalEventsInVSidebandHP_LP)+"  & "+ str(numberSignalEventsInVSidebandHP_HP) +"\\\\"
        print "WNP                  &"+str(numberSignalEventsInWSidebandNP_NP)+"  &  "+str(numberSignalEventsInWSidebandNP_LP)+"  & "+ str(numberSignalEventsInWSidebandNP_HP) +"\\\\"
        print "WLP                  &"+str(numberSignalEventsInWSidebandLP_NP)+"  &  "+str(numberSignalEventsInWSidebandLP_LP)+"  & "+ str(numberSignalEventsInWSidebandLP_HP) +"\\\\"
        print "WHP                  &"+str(numberSignalEventsInWSidebandHP_NP)+"  &  "+str(numberSignalEventsInWSidebandHP_LP)+"  & "+ str(numberSignalEventsInWSidebandHP_HP) +"\\\\"
        print "ZNP                  &"+str(numberSignalEventsInZSidebandNP_NP)+"  &  "+str(numberSignalEventsInZSidebandNP_LP)+"  & "+ str(numberSignalEventsInZSidebandNP_HP) +"\\\\"
        print "ZLP                  &"+str(numberSignalEventsInZSidebandLP_NP)+"  &  "+str(numberSignalEventsInZSidebandLP_LP)+"  & "+ str(numberSignalEventsInZSidebandLP_HP) +"\\\\"
        print "ZHP                  &"+str(numberSignalEventsInZSidebandHP_NP)+"  &  "+str(numberSignalEventsInZSidebandHP_LP)+"  & "+ str(numberSignalEventsInZSidebandHP_HP) +"\\\\"
      
      
        print '==================='+fname+'======================================================='
        print "number of signal events: NP "+str(numberSignalEvents_NP)+" LP "+str(numberSignalEvents_LP)+" HP "+str(numberSignalEvents_HP)
        print "  sidebands          &   signal NP           &  signal LP         &    signal HP      \\\\"
        print "VNP                  &"+ str(round(numberSignalEventsInVSidebandNP_NP/float(numberSignalEvents_NP)*100,2))+"   &        "+str(round(numberSignalEventsInVSidebandNP_LP/float(numberSignalEvents_LP)*100,2))+"      &     "+ str(round(numberSignalEventsInVSidebandNP_HP/float(numberSignalEvents_HP)*100,2)) +"\\\\"
        print "VLP                  &"+ str(round(numberSignalEventsInVSidebandLP_NP/float(numberSignalEvents_NP)*100,2))+"   &        "+str(round(numberSignalEventsInVSidebandLP_LP/float(numberSignalEvents_LP)*100,2))+"      &     "+ str(round(numberSignalEventsInVSidebandLP_HP/float(numberSignalEvents_HP)*100,2)) +"\\\\"
        print "VHP                  &"+str(round(numberSignalEventsInVSidebandHP_NP/float(numberSignalEvents_NP)*100,2))+"    &        "+str(round(numberSignalEventsInVSidebandHP_LP/float(numberSignalEvents_LP)*100,2))+"      &     "+ str(round(numberSignalEventsInVSidebandHP_HP/float(numberSignalEvents_HP)*100,2)) +"\\\\"
        print "WNP                  &"+str(round(numberSignalEventsInWSidebandNP_NP/float(numberSignalEvents_NP)*100,2))+"    &        "+str(round(numberSignalEventsInWSidebandNP_LP/float(numberSignalEvents_LP)*100,2))+"      &     "+ str(round(numberSignalEventsInWSidebandNP_HP/float(numberSignalEvents_HP)*100,2)) +"\\\\"
        print "WLP                  &"+str(round(numberSignalEventsInWSidebandLP_NP/float(numberSignalEvents_NP)*100,2))+"    &        "+str(round(numberSignalEventsInWSidebandLP_LP/float(numberSignalEvents_LP)*100,2))+"      &     "+ str(round(numberSignalEventsInWSidebandLP_HP/float(numberSignalEvents_HP)*100,2)) +"\\\\"
        print "WHP                  &"+str(round(numberSignalEventsInWSidebandHP_NP/float(numberSignalEvents_NP)*100,2))+"    &        "+str(round(numberSignalEventsInWSidebandHP_LP/float(numberSignalEvents_LP)*100,2))+"      &     "+ str(round(numberSignalEventsInWSidebandHP_HP/float(numberSignalEvents_HP)*100,2)) +"\\\\"
        print "ZNP                  &"+str(round(numberSignalEventsInZSidebandNP_NP/float(numberSignalEvents_NP)*100,2))+"    &        "+str(round(numberSignalEventsInZSidebandNP_LP/float(numberSignalEvents_LP)*100,2))+"      &     "+ str(round(numberSignalEventsInZSidebandNP_HP/float(numberSignalEvents_HP)*100,2)) +"\\\\"
        print "ZLP                  &"+str(round(numberSignalEventsInZSidebandLP_NP/float(numberSignalEvents_NP)*100,2))+"    &        "+str(round(numberSignalEventsInZSidebandLP_LP/float(numberSignalEvents_LP)*100,2))+"      &     "+ str(round(numberSignalEventsInZSidebandLP_HP/float(numberSignalEvents_HP)*100,2)) +"\\\\"
        print "ZHP                  &"+str(round(numberSignalEventsInZSidebandHP_NP/float(numberSignalEvents_NP)*100,2))+"    &        "+str(round(numberSignalEventsInZSidebandHP_LP/float(numberSignalEvents_LP)*100,2))+"      &     "+ str(round(numberSignalEventsInZSidebandHP_HP/float(numberSignalEvents_HP)*100,2)) +"\\\\"
      
