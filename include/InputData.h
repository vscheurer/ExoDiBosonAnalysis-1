#ifndef INPUTDATA_H
#define INPUTDATA_H

#include <vector>
#include <TLorentzVector.h>

class InputData {

public:
   InputData( void );
   ~InputData( void );

   std::vector<int  >*		   genParticle_pdgId 	 ;
   std::vector<int  >*		   genParticle_status 	 ;
   std::vector<float>*		   genParticle_pt    	 ;
   std::vector<float>*  	   genParticle_mass  	 ;
   std::vector<float>*		   genParticle_e     	 ;
   std::vector<float>*		   genParticle_eta   	 ;
   std::vector<float>*		   genParticle_phi   	 ;
   std::vector<std::vector<int> >* genParticle_mother 	 ;
   std::vector<std::vector<int> >* genParticle_dau   	 ;
   float                           lheV_pt               ;
   
   int                             nlep              	 ;
   std::vector<float>*    	   lep_e             	 ;
   std::vector<float>*  	   lep_eta           	 ;
   std::vector<float>*  	   lep_pt            	 ;
   std::vector<float>*  	   lep_phi           	 ;
   std::vector<int  >*  	   lep_type	     	 ;
   std::vector<float>*  	   lep_pfDeltaCorrRelIso ;
   std::vector<float>*  	   lep_trackIso          ;   
   std::vector<int  >*  	   lep_tightId           ;
   std::vector<int  >*  	   lep_isHEEP            ;   
   std::vector<float>*             lep_chargedHadIsoBoost;
   std::vector<float>*             lep_neutralHadIsoBoost;
   std::vector<float>*             lep_photonIsoBoost    ;
   std::vector<int  >*             lep_isHighPtMuon      ;
   std::vector<int  >*  	   lep_isGlobalMuon	 ;
   
   std::vector<float>* 	           MET_et                ;
   std::vector<float>* 	           MET_phi               ;
   
   int                             njetsAK4          	 ;
   std::vector<float>*		   jetAK4_pt	     	 ;
   std::vector<float>*		   jetAK4_eta	     	 ;
   std::vector<float>*		   jetAK4_phi	     	 ;
   std::vector<float>*		   jetAK4_e	     	 ;
   std::vector<float>*		   jetAK4_csv	     	 ;
   std::vector<int  >*		   jetAK4_flavor	 ;
   std::vector<bool  >*  	   jetAK4_IDLoose        ;  
   
   int                             njetsAK8          	 ;
   std::vector<float>*		   jetAK8_pt	     	 ;
   std::vector<float>*		   jetAK8_eta	     	 ;
   std::vector<float>*		   jetAK8_phi	     	 ;
   std::vector<float>*		   jetAK8_e	     	 ;
   std::vector<float>*		   jetAK8_mass	     	 ;
   std::vector<float>*  	   jetAK8_prunedmass     ;
   std::vector<float>*  	   jetAK8_softdropmass   ;
   std::vector<float>*  	   jetAK8_trimmedmass    ;
   std::vector<float>*  	   jetAK8_filteredmass   ;
   std::vector<float>*		   jetAK8_csv	     	 ;
   std::vector<int  >*             jetAK8_nm             ;
   std::vector<int  >*             jetAK8_cm             ;
   std::vector<float>*             jetAK8_che            ;
   std::vector<float>*             jetAK8_ne             ;
   std::vector<float>*		   jetAK8_tau1	     	 ;
   std::vector<float>*		   jetAK8_tau2	     	 ;
   std::vector<float>*		   jetAK8_tau3	     	 ;
   std::vector<bool  >*  	   jetAK8_IDLoose        ;  
   std::vector<int   >*  	   jetAK8_flavor         ;
   std::vector<int   >*  	   jetAK8_nconstituents  ;
      
   int                             njetsAK8pruned    	 ;
   std::vector<float>*		   jetAK8pruned_pt   	 ;
   std::vector<float>*		   jetAK8pruned_eta  	 ;
   std::vector<float>*		   jetAK8pruned_phi  	 ;
   std::vector<float>*		   jetAK8pruned_e    	 ;
   std::vector<float>*		   jetAK8pruned_mass 	 ;

   std::vector<int>*    	      nsubjets           ;
   std::vector< std::vector<float> >* subjetAK8pruned_csv;    
   std::vector< std::vector<float> >* subjetAK8pruned_pt ;    
   std::vector< std::vector<float> >* subjetAK8pruned_eta;    
   std::vector< std::vector<float> >* subjetAK8pruned_phi;    
   std::vector< std::vector<float> >* subjetAK8pruned_e  ;    
   std::vector< std::vector<int> >*   subjetAK8pruned_flavor;    
       
   std::vector<int  >*             nPUTrue               ;
   std::vector<int  >*             bX                    ;
   int                             nPVs                  ; 
   int                             EVENT_event           ;
   int                             EVENT_run             ;
   int                             EVENT_lumi            ;

   bool isFired_HLT_Mu40_v1 ;
   bool isFired_HLT_Ele95_CaloIdVT_GsfTrkIdT_v1;
              
private:
   
};

#endif // INPUTDATA_H
