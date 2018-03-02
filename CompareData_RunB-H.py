from ROOT import *
import ctypes
import numpy as np

class EventID:
    def __init__(self, runnr, evnr,check):
        self.runnr = runnr
        self.evnr = evnr
        self.check = check
    def printID(self):
        strprint = str(self.runnr) + "  " + str(self.evnr)
        return strprint
    
percentold = -1
Danielasfile = TFile.Open("/storage/jbod/dschaefer/AnalysisOutput/80X/Bkg/Summer16/QCD_pythia8_VVdijet_SR.root")
file = TFile.Open("/usr/users/vscheurer/ExoDiBosonAnalysis/QCD_pt.root")
#file = TFile.Open("/storage/jbod/dschaefer/AnalysisOutput/80X/Data/ReReco2016/Data_VVdijet_SR_36814ifb.root")

print file
print Danielasfile

mytree = file.Get("tree")
Danielastree = Danielasfile.Get("tree")
DanielasEvents  = []
myEvents = []
LostEvents = []
LostRuns = [0]
FinalArray = []
#LostRunsList = np.genfromtxt("LostRuns.dat")


print "start looping over tree1"
for event in Danielastree:
    if event.MVV>1050 and event.event >10000000 and event.event < 13000000:
        #if event.jet_puppi_softdrop_jet1 > 65. and event.jet_puppi_softdrop_jet1 <=105. and event.jet_puppi_softdrop_jet2 > 65. and event.jet_puppi_softdrop_jet2 <=105.:
        DanielasEvents.append(EventID(event.run,(event.event),0))
Danielasfile.Close()
print "start looping over tree2"        
for event in mytree:
    if event.MVV>1050 and event.event >10000000 and event.event < 13000000:
        #if event.jet_puppi_softdrop_jet1 > 65. and event.jet_puppi_softdrop_jet1 <=105. and event.jet_puppi_softdrop_jet2 > 65. and event.jet_puppi_softdrop_jet2 <=105.:
        myEvents.append(EventID(event.run,(event.event),0))
file.Close()
print "checking EventID"
n=0
for ID in DanielasEvents:
    n=n+1
    for ID2 in myEvents:
        
        if ID.runnr == ID2.runnr and ID.evnr == ID2.evnr:
            ID.check = 1
            
            percent =  int(float(n)/float(len(DanielasEvents))*100)
            if percent > percentold:
                print "%s Percent done" %percent
                percentold = percent
print "putting lost events in array"
for ID in DanielasEvents:  
    if ID.check ==0:
        LostEvents.append(ID)
        
for ID in LostEvents:
    check2 =0
    for i in range(len(LostRuns)):

        if ID.runnr == LostRuns[i]:
            check2 = 1
    if check2 ==0:
        LostRuns.append(ID.runnr)
        print ID.runnr
print "printing"        
for i in LostEvents:
    FinalArray.append([i.runnr, i.evnr])
print LostRuns
print len(DanielasEvents)
print len(LostEvents)
print len(LostRuns)
np.savetxt( "LostEventC.dat",FinalArray, fmt = "%i")