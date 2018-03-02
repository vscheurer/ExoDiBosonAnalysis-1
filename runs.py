import numpy as np
from ROOT import *


MissingEvents = np.genfromtxt("LostEvents.dat")
print len(MissingEvents)


def whichruns(LostEvents):
    Runs = []
   
    Runs2 =[0]
    for Event in LostEvents:
        run = Event[0]
        #print Event[0]
       
        Runs.append(int(run))
        Runs.sort()
        
    for run in Runs:
        if run !=Runs2[-1]:
            Runs2.append(run)
    return(Runs2)        
            

def lookforRun(lostruns):
    Data = TFile.Open("/usr/users/vscheurer/AnalysisOutput/Data/DATA.root")

    checkedRuns =[0]
    tree = Data.Get("tree")
    #tree.Print()
    for event in tree:
        if event.MVV >1050:
            #print event.run
            for onerun in lostruns:
                #print onerun
                if int(onerun) == int(event.run):
                    print onerun
                    #print event.event
                    print "run not completely lost"
                    if onerun not in checkedRuns:
                        checkedRuns.append(onerun)
    return checkedRuns
            
def lookatrun(LostEvents, Data):
    tree = Data.Get("tree")
    
    for event in LostEvents:
        if event[0] == 279841:
            print event
    #for event in tree:
        #if event.run == 279841:
            #print event.run 
            #print event.event

def removeruns(LostRuns,checkedRuns):
    completelyLostruns = []
    for i in range(len(LostRuns)):
        if LostRuns[i] not in checkedRuns:
           completelyLostruns.append(LostRuns[i])
    return completelyLostruns

#LostRuns = whichruns(MissingEvents)
#notcompletelymissingruns = lookforRun(LostRuns)

#print (notcompletelymissingruns)
##print len(LostRuns)
##print len(notcompletelymissingruns)
#print ""
#print ""
##lookatrun(MissingEvents,Data)
#LostRuns.pop(0)
#LostRuns = removeruns(LostRuns,notcompletelymissingruns)
#print (LostRuns)
#np.savetxt("LostRuns.dat", LostRuns)
NewLostEvents = []
for i in MissingEvents:
    if i[1] <0:
        i[1] = i[1] + 2**32
np.savetxt("NewLostEvents.dat",MissingEvents, fmt = '%d %d')    
    
    
    
    
    
    