#include "include/JetCandidate.h"

///////////////////////////////////////////////////////////////////////////////////////////////
JetCandidate::JetCandidate( TLorentzVector tlv )
   : RecoCandidate( tlv )
   , csv(-99)
   , mass(-99)
   , prunedMass(-99)
   , prunedMassUnCorr(-99)
   , softdropMass(-99)   
   , tau1(-99)
   , tau2(-99)
   , tau3(-99)
   , flavor(-99)   
   , rcn(-99)
   ,cm(-99)
   ,nm(-99)
   ,muf(-99)
   ,phf(-99)
   ,emf(-99)
   ,nhf(-99)
   ,chf(-99)
   ,che(-99)
   ,ne(-99)  
   ,hf_hf(-99)
   ,hf_emf(-99)
   ,hof(-99)
   ,chm (-99)
   ,neHadMult(-99)
   ,phoMult(-99)
   ,nemf(-99)
   ,cemf(-99)
   ,charge(-99)
   ,area(-99)
   ,rho(-99)
   ,jec(-99)
   ,pruned_jec(-99) 
   ,puppi_prunedMass(-99) 
   ,puppi_softdropMass(-99)   
   ,puppi_tau1(-99)   
   ,puppi_tau2(-99)   
   ,puppi_tau3(-99)   
   ,puppi_pt(-99) 
   ,Hbbtag(-99)
   ,P4()
   ,nbHadrons(-99)
{

}

///////////////////////////////////////////////////////////////////////////////////////////////
JetCandidate::~JetCandidate( void )
{

} 



