#ifndef INPUTDATA_H
#define INPUTDATA_H

#include <vector>
#include <TLorentzVector.h>
#include <map>

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
  
  int                             el_N              	 ;
  std::vector<float>*    	   el_e 	    	 ;
  std::vector<float>*  	   el_eta	    	 ;
  std::vector<float>*  	   el_pt	    	 ;
  std::vector<float>*  	   el_phi	    	 ;
  std::vector<int  >*  	   el_isHEEP	         ;
   std::vector<int  >*  	 el_isLooseElectron	         ;
   std::vector<int  >*  	 el_isMediumElectron	         ;
   std::vector<int  >*  	 el_isTightElectron	         ;

  int                      mu_N          ;
  std::vector<float>*      mu_e 	    	 ;
  std::vector<float>*  	   mu_eta	    	 ;
  std::vector<float>*  	   mu_pt	    	 ;
  std::vector<float>*  	   mu_phi	    	 ;
  std::vector<float>*  	   mu_trackIso           ;   
  std::vector<int  >*      mu_isHighPtMuon       ;
  std::vector<int  >*      mu_isLooseMuon       ;
  std::vector<int  >*      mu_isTightMuon       ;
  std::vector<int  >*  	   mu_isPFMuon	         ;
   
	int                        nlep						    	;
	std::vector<float>*    	   lep_e					  		;
	std::vector<float>*  	   lep_eta					    	;
	std::vector<float>*  	   lep_pt				      		;
	std::vector<float>*  	   lep_phi					    	;
	std::vector<int  >*  	   lep_type					    	;
	std::vector<float>*  	   lep_pfDeltaCorrRelIso	;
	std::vector<float>*  	   lep_trackIso			    	;  
	std::vector<float>*  	   lep_pfRelIso			    	; 
	std::vector<int  >*  	   lep_tightId					  ;
  std::vector<int  >*  	   lep_isLooseElectron     ;
  std::vector<int  >*  	   lep_isMediumElectron     ;
  std::vector<int  >*  	   lep_isTightElectron     ;
	std::vector<int  >*  	   lep_isHeepElectron     ;  
	std::vector<float>*  	   lep_chargedHadIsoBoost	;
	std::vector<float>*  	   lep_neutralHadIsoBoost	;
	std::vector<float>*  	   lep_photonIsoBoost		  ;
	std::vector<int  >*  	   lep_isHighPtMuon			  ;
	std::vector<int  >*  	   lep_isTightMuon			  ;
	std::vector<int  >*  	   lep_isLooseMuon			  ;
	std::vector<int  >*  	   lep_isGlobalMuon			  ;
   
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
	std::vector<float>*		   jetAK8_prunedmass	;
	std::vector<float>*		   jetAK8_softdropmass;
	std::vector<float>*		   jetAK8_prunedmassCorr	;
	std::vector<float>*		   jetAK8_softdropmassCorr	;
	std::vector<float>*  	   jetAK8pruned_jec			;
	std::vector<float>*  	   jetAK8softdrop_jec		;
	std::vector<float>*		   jetAK8_csv					;
   
	std::vector<float>*		   jetAK8_tau1					;
	std::vector<float>*		   jetAK8_tau2					;
	std::vector<float>*		   jetAK8_tau3					;
	std::vector<bool >*  	   jetAK8_IDLoose				; 
  std::vector<bool >*  	   jetAK8_IDTight				; 
	std::vector<int  >*  	   jetAK8_flavor				;
	std::vector<int  >*  	   jetAK8_nconstituents		;
  
  std::vector<int>*        jetAK8_cm; //chargedMultiplicity
  std::vector<int>*        jetAK8_nm; //neutralMultiplicity
  std::vector<float>*		   jetAK8_muf; //muonEnergyFraction
  std::vector<float>*		   jetAK8_phf; //photonEnergyFraction
  std::vector<float>*		   jetAK8_emf; //chargedEmEnergyFraction
  std::vector<float>*		   jetAK8_nhf; //neutralHadronEnergyFraction
  std::vector<float>*		   jetAK8_chf; //chargedHadronEnergyFraction
  std::vector<float>*		   jetAK8_area; //jetArea
  std::vector<float>*		   jetAK8_che; //fj.chargedHadronEnergy()+fj.electronEnergy()+fj.muonEnergy()
  std::vector<float>*		   jetAK8_ne; //fj.neutralHadronEnergy()+fj.photonEnergy()
  std::vector<float>*		   jetAK8_hf_hf; //HFHadronEnergyFraction());
  std::vector<float>*		   jetAK8_hf_emf; //HFEMEnergyFraction());
  std::vector<float>*		   jetAK8_hof; //hoEnergyFraction());
  std::vector<int>*		     jetAK8_chm; //chargedHadronMultiplicity());
  std::vector<int>*		     jetAK8_neHadMult ; //neutralHadronMultiplicity());
  std::vector<int>*		     jetAK8_phoMult; //photonMultiplicity());
  std::vector<float>*		   jetAK8_nemf; //neutralEmEnergyFraction());
  std::vector<float>*		   jetAK8_cemf ; //chargedEmEnergyFraction());
  std::vector<float>*		   jetAK8_charge; //charge());		
  
  
  
  int			      ngenJetsAK8               ;
  std::vector<float>*  	      genJetAK8_pt              ;
  std::vector<float>*  	      genJetAK8_eta             ;
  std::vector<float>* 	      genJetAK8_mass            ;
  std::vector<float>*  	      genJetAK8_phi             ;
  std::vector<float>*  	      genJetAK8_e               ;
  std::vector<float>*  	      genJetAK8_prunedmass      ;
  std::vector<float>*  	      genJetAK8_softdropmass    ;
  
      
	// int                             njetsAK8pruned    	 ;
	//   std::vector<float>*		   jetAK8pruned_pt   	 ;
	//   std::vector<float>*		   jetAK8pruned_eta  	 ;
	//   std::vector<float>*		   jetAK8pruned_phi  	 ;
	//   std::vector<float>*		   jetAK8pruned_e    	 ;
	//   std::vector<float>*		   jetAK8pruned_mass 	 ;

	std::vector<int						>* subjetAK8_softdrop_N						;
	std::vector< std::vector<float>	>* subjetAK8_softdrop_csv		;    
	std::vector< std::vector<float>	>* subjetAK8_softdrop_pt 		;    
	std::vector< std::vector<float>	>* subjetAK8_softdrop_eta		;    
	std::vector< std::vector<float>	>* subjetAK8_softdrop_phi		;    
	std::vector< std::vector<float>	>* subjetAK8_softdrop_e  		;    
	std::vector< std::vector<int>		>* subjetAK8_softdrop_flavor	;    
  
  std::vector<int  >*             nPUTrue               ;
  std::vector<int  >*             bX                    ;
  int                             nPVs                  ; 
  int                             EVENT_event           ;
  int                             EVENT_run             ;
  int                             EVENT_lumi            ;
  bool                            PV_filter             ;
   
  std::map<std::string,bool>*         HLT_isFired;

  /*std::vector<float>*		       triggerObject_pt 	 ;
  std::vector<float>*		       triggerObject_eta	 ;
  std::vector<float>*		       triggerObject_phi	 ;
  std::vector<float>*		       triggerObject_mass	 ;
  std::vector< std::vector<float> >*  triggerObject_filterIDs   ;
  std::vector< std::vector<int> >*    triggerObject_firedTrigger;*/

  bool passFilter_HBHE_;
  bool passFilter_CSCHalo_;
  bool passFilter_HCALlaser_;
  bool passFilter_ECALDeadCell_;
  bool passFilter_GoodVtx_;
  bool passFilter_TrkFailure_;
  bool passFilter_EEBadSc_;
  bool passFilter_ECALlaser_;
  bool passFilter_TrkPOG_;
  bool passFilter_TrkPOG_manystrip_;
  bool passFilter_TrkPOG_toomanystrip_;
  bool passFilter_TrkPOG_logError_;
  bool passFilter_METFilters_;
               
private:
   
};

#endif // INPUTDATA_H
