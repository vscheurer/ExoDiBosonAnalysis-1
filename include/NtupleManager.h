#ifndef NTUPLEMANAGER_H
#define NTUPLEMANAGER_H

#include "../ExoDiBosonAnalysis/include/InputData.h"

class SCycleBase;

class NtupleManager {

public:
   NtupleManager( SCycleBase * theAnalysis );
   ~NtupleManager( void );
   
   void ConnectVariables( std::string treeName, TString sample, bool runOnMC_ , bool usePuppiSD_ );
   InputData getData( void ){return theData_;}
   
private:
   SCycleBase* theAnalysis_;
   InputData   theData_    ;
   
};

#endif // NTUPLEMANAGER_H
