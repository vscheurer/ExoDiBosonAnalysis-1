#ifndef INPUTDATA_H
#define INPUTDATA_H

#include <vector>
#include <TLorentzVector.h>

class InputData {

public:
	InputData( void );
	~InputData( void );

	std::vector<int  >*					genParticle_pdgId		;
	std::vector<int  >*					genParticle_status	;
	std::vector<float>*					genParticle_pt			;
	std::vector<float>*					genParticle_px			;
	std::vector<float>*					genParticle_py			;
	std::vector<float>*					genParticle_pz			;
	std::vector<float>*					genParticle_mass		;
	std::vector<float>*					genParticle_e			;
	std::vector<float>*					genParticle_eta		;
	std::vector<float>*					genParticle_phi		;
	std::vector<std::vector<int> >*	genParticle_mother	;
	std::vector<std::vector<int> >*	genParticle_dau		;
	std::vector<int  >*					genParticle_nDau		;
	std::vector<int  >*					genParticle_nMoth    ;
	float										lheV_pt					;
	float                            lheHT                ;
	float                            lheNj                ;
	float                            genWeight            ;
	float                            qScale               ;
   
	int                        nlep							;
	std::vector<float>*    	   lep_e							;
	std::vector<float>*  	   lep_eta						;
	std::vector<float>*  	   lep_pt						;
	std::vector<float>*  	   lep_phi						;
	std::vector<int  >*  	   lep_type						;
	std::vector<float>*  	   lep_pfDeltaCorrRelIso	;
	std::vector<float>*  	   lep_trackIso				;  
	std::vector<float>*  	   lep_pfRelIso				; 
	std::vector<int  >*  	   lep_tightId					;
	std::vector<int  >*  	   lep_isHEEP					;   
	std::vector<int  >*  	   lep_isHEEPv50				;   
	std::vector<float>*  	   lep_chargedHadIsoBoost	;
	std::vector<float>*  	   lep_neutralHadIsoBoost	;
	std::vector<float>*  	   lep_photonIsoBoost		;
	std::vector<int  >*  	   lep_isHighPtMuon			;
	std::vector<int  >*  	   lep_isTightMuon			;
	std::vector<int  >*  	   lep_isLooseMuon			;
	std::vector<int  >*  	   lep_isGlobalMuon			;
   
	std::vector<float>*         METraw_et              ;	 
	std::vector<float>*         METraw_phi             ;
	std::vector<float>*  	    METraw_sumEt 	     		; 
	std::vector<float>*  	    MET_corrPx 	     		;
	std::vector<float>*  	    MET_corrPy 	     		;    
	std::vector<float>*  	    MET_et 	     				;
	std::vector<float>*  	    MET_phi 	     			;
	std::vector<float>*  	    MET_sumEt 	     			;
	std::vector<float>*  	    MET_T1Uncertainty      ;
   
   
	int                        njetsAK4 	     			;
	std::vector<float>*		   jetAK4_pt 	     			;
	std::vector<float>*		   jetAK4_eta 	     			;
	std::vector<float>*		   jetAK4_phi 	     			;
	std::vector<float>*		   jetAK4_e 	     			;
	std::vector<float>*		   jetAK4_csv 	     			;
	std::vector<int  >*		   jetAK4_flavor 	     		;
	std::vector<bool >*  	   jetAK4_IDLoose 	     	;  
   
	int                        njetsAK8 	     			;
	std::vector<float>*		   jetAK8_pt 	     			;
	std::vector<float>*		   jetAK8_eta 	     			;
	std::vector<float>*		   jetAK8_phi 	     			;
	std::vector<float>*		   jetAK8_e 	     			;
	std::vector<float>*		   jetAK8_mass 	     		;
	std::vector<float>*		   jetAK8_prunedmassUnCorr	;
	std::vector<float>*		   jetAK8_softdropmassUnCorr;
	std::vector<float>*		   jetAK8_prunedmassCorr	;
	std::vector<float>*		   jetAK8_softdropmassCorr	;
	std::vector<float>*  	   jetAK8pruned_jec			;
	std::vector<float>*  	   jetAK8softdrop_jec		;
	std::vector<float>*		   jetAK8_csv					;
	std::vector<int  >*		   jetAK8_nm					;
	std::vector<int  >*		   jetAK8_cm					;
	std::vector<float>*		   jetAK8_che					;
	std::vector<float>*		   jetAK8_ne					;
	std::vector<float>*		   jetAK8_muf					;
	std::vector<float>*		   jetAK8_phf					;
	std::vector<float>* 	      jetAK8_emf					;
	std::vector<float>*	      jetAK8_nhf					;
	std::vector<float>*		   jetAK8_chf					;
	std::vector<float>*		   jetAK8_area					;
   
	std::vector<float>*		   jetAK8_tau1					;
	std::vector<float>*		   jetAK8_tau2					;
	std::vector<float>*		   jetAK8_tau3					;
	std::vector<bool >*  	   jetAK8_IDLoose				;  
	std::vector<int  >*  	   jetAK8_flavor				;
	std::vector<int  >*  	   jetAK8_nconstituents		;
      
	// int                             njetsAK8pruned    	 ;
	//   std::vector<float>*		   jetAK8pruned_pt   	 ;
	//   std::vector<float>*		   jetAK8pruned_eta  	 ;
	//   std::vector<float>*		   jetAK8pruned_phi  	 ;
	//   std::vector<float>*		   jetAK8pruned_e    	 ;
	//   std::vector<float>*		   jetAK8pruned_mass 	 ;

	std::vector<int						>* nsubjets						;
	std::vector< std::vector<float>	>* subjetAK8pruned_csv		;    
	std::vector< std::vector<float>	>* subjetAK8pruned_pt 		;    
	std::vector< std::vector<float>	>* subjetAK8pruned_eta		;    
	std::vector< std::vector<float>	>* subjetAK8pruned_phi		;    
	std::vector< std::vector<float>	>* subjetAK8pruned_e  		;    
	std::vector< std::vector<int>		>* subjetAK8pruned_flavor	;    
       
	std::vector<int  >*             nPUTrue                     ;
	std::vector<int  >*             bX                     		;
	int                             nPVs                     	; 
	int                             EVENT_event						;
	int                             EVENT_run							;
	int                             EVENT_lumi						;

	bool    isFired_HLT_AK8PFJet360_TrimMass30_v1										;
	bool    isFired_HLT_AK8PFHT700_TrimR0p1PT0p03Mass50_v1					;
	bool    isFired_HLT_AK8DiPFJet280_200_TrimMass30_BTagCSV0p41_v1	;
	bool    isFired_HLT_PFHT650_WideJetMJJ950DEtaJJ1p5_v1						;
	bool    isFired_HLT_PFHT650_WideJetMJJ900DEtaJJ1p5_v1						;
	bool    isFired_HLT_PFHT900_v1																	;
	
	bool   	isFired_HLT_Mu40_v1																			;
	bool		isFired_HLT_Ele95_CaloIdVT_GsfTrkIdT_v1									;
	
              
private:
   
};

#endif // INPUTDATA_H
