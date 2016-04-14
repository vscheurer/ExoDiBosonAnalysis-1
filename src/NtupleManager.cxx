#include "include/NtupleManager.h"
#include "core/include/SCycleBase.h"
#include <iostream>

////////////////////////////////////////////////////////////////////
NtupleManager::NtupleManager( SCycleBase* theAnalysis ):theAnalysis_( theAnalysis )
{

}

////////////////////////////////////////////////////////////////////
NtupleManager::~NtupleManager( void ){

}

////////////////////////////////////////////////////////////////////
void NtupleManager::ConnectVariables( std::string treeName, TString sample, bool runOnMC_ , bool usePuppiSD_){
  
  if(runOnMC_){
    theAnalysis_->ConnectVariable( treeName.c_str(), "genParticle_pdgId"     , theData_.genParticle_pdgId   );
    theAnalysis_->ConnectVariable( treeName.c_str(), "genParticle_status"    , theData_.genParticle_status  );
    theAnalysis_->ConnectVariable( treeName.c_str(), "genParticle_pt"        , theData_.genParticle_pt      );
    theAnalysis_->ConnectVariable( treeName.c_str(), "genParticle_px"        , theData_.genParticle_px      );
    theAnalysis_->ConnectVariable( treeName.c_str(), "genParticle_py"        , theData_.genParticle_py      );
    theAnalysis_->ConnectVariable( treeName.c_str(), "genParticle_pz"        , theData_.genParticle_pz      );
    theAnalysis_->ConnectVariable( treeName.c_str(), "genParticle_mass"      , theData_.genParticle_mass    );
    theAnalysis_->ConnectVariable( treeName.c_str(), "genParticle_e"         , theData_.genParticle_e	      );
    theAnalysis_->ConnectVariable( treeName.c_str(), "genParticle_eta"       , theData_.genParticle_eta     );
    theAnalysis_->ConnectVariable( treeName.c_str(), "genParticle_phi"       , theData_.genParticle_phi     );
    theAnalysis_->ConnectVariable( treeName.c_str(), "genParticle_dau"       , theData_.genParticle_dau     );
    theAnalysis_->ConnectVariable( treeName.c_str(), "genParticle_nDau"    	 , theData_.genParticle_nDau    );
    theAnalysis_->ConnectVariable( treeName.c_str(), "genParticle_mother"    , theData_.genParticle_mother  );
    theAnalysis_->ConnectVariable( treeName.c_str(), "genParticle_nMoth"     , theData_.genParticle_nMoth   );
    theAnalysis_->ConnectVariable( treeName.c_str(), "lheV_pt"               , theData_.lheV_pt             );
    theAnalysis_->ConnectVariable( treeName.c_str(), "lheHT"                 , theData_.lheHT               );
    theAnalysis_->ConnectVariable( treeName.c_str(), "lheNj"                 , theData_.lheNj               );
    theAnalysis_->ConnectVariable( treeName.c_str(), "genWeight"             , theData_.genWeight           );
    theAnalysis_->ConnectVariable( treeName.c_str(), "qScale"                , theData_.qScale              );
    
    theAnalysis_->ConnectVariable( treeName.c_str(), "nPuVtxTrue"	      , theData_.nPUTrue     );
    theAnalysis_->ConnectVariable( treeName.c_str(), "bX"		            , theData_.bX          );
    
    theAnalysis_->ConnectVariable( treeName.c_str(), "jetAK4_hadronFlavour" , theData_.jetAK4_flavor  );
    
    // theAnalysis_->ConnectVariable( treeName.c_str(), "genJetAK8_N"    , theData_.ngenJetsAK8    );
    // theAnalysis_->ConnectVariable( treeName.c_str(), "genJetAK8_pt"   , theData_.genJetAK8_pt   );
    // theAnalysis_->ConnectVariable( treeName.c_str(), "genJetAK8_eta"  , theData_.genJetAK8_eta  );
    // theAnalysis_->ConnectVariable( treeName.c_str(), "genJetAK8_mass" , theData_.genJetAK8_mass );
    // theAnalysis_->ConnectVariable( treeName.c_str(), "genJetAK8_phi"  , theData_.genJetAK8_phi  );
    // theAnalysis_->ConnectVariable( treeName.c_str(), "genJetAK8_e"    , theData_.genJetAK8_e    );
    // theAnalysis_->ConnectVariable( treeName.c_str(), "genJetAK8_prunedmass"   , theData_.genJetAK8_prunedmass   );
    // theAnalysis_->ConnectVariable( treeName.c_str(), "genJetAK8_softdropmass" , theData_.genJetAK8_softdropmass );
  }
  
   
  theAnalysis_->ConnectVariable( treeName.c_str(), "el_N"		       , theData_.el_N      	    );
  theAnalysis_->ConnectVariable( treeName.c_str(), "el_e"		       , theData_.el_e      	    );
  theAnalysis_->ConnectVariable( treeName.c_str(), "el_eta"		       , theData_.el_eta    	    );
  theAnalysis_->ConnectVariable( treeName.c_str(), "el_pt"		       , theData_.el_pt     	    );
  theAnalysis_->ConnectVariable( treeName.c_str(), "el_phi"		       , theData_.el_phi    	    );
  theAnalysis_->ConnectVariable( treeName.c_str(), "el_isHeepElectron"        , theData_.el_isHEEP         );
  theAnalysis_->ConnectVariable( treeName.c_str(), "el_isLooseElectron"       , theData_.el_isLooseElectron   );
  theAnalysis_->ConnectVariable( treeName.c_str(), "el_isMediumElectron"      , theData_.el_isMediumElectron  );
  theAnalysis_->ConnectVariable( treeName.c_str(), "el_isTightElectron"       , theData_.el_isTightElectron   );
  theAnalysis_->ConnectVariable( treeName.c_str(), "el_isVetoElectron"        , theData_.el_isVetoElectron    );

  theAnalysis_->ConnectVariable( treeName.c_str(), "mu_N"		       , theData_.mu_N      	    );
  theAnalysis_->ConnectVariable( treeName.c_str(), "mu_e"		       , theData_.mu_e      	    );
  theAnalysis_->ConnectVariable( treeName.c_str(), "mu_eta"		       , theData_.mu_eta    	    );
  theAnalysis_->ConnectVariable( treeName.c_str(), "mu_pt"		       , theData_.mu_pt     	    );
  theAnalysis_->ConnectVariable( treeName.c_str(), "mu_phi"		       , theData_.mu_phi    	    );
  theAnalysis_->ConnectVariable( treeName.c_str(), "mu_trackIso"              , theData_.mu_trackIso       );	
  theAnalysis_->ConnectVariable( treeName.c_str(), "mu_isHighPtMuon"          , theData_.mu_isHighPtMuon   );
  theAnalysis_->ConnectVariable( treeName.c_str(), "mu_isPFMuon"              , theData_.mu_isPFMuon       );
  theAnalysis_->ConnectVariable( treeName.c_str(), "mu_isLooseMuon"           , theData_.mu_isLooseMuon       );
  theAnalysis_->ConnectVariable( treeName.c_str(), "mu_isTightMuon"           , theData_.mu_isTightMuon       );
   
  theAnalysis_->ConnectVariable( treeName.c_str(), "jetAK4_N"                 , theData_.njetsAK4	      	);
  theAnalysis_->ConnectVariable( treeName.c_str(), "jetAK4_e"       , theData_.jetAK4_e       );
  theAnalysis_->ConnectVariable( treeName.c_str(), "jetAK4_eta"     , theData_.jetAK4_eta     );
  theAnalysis_->ConnectVariable( treeName.c_str(), "jetAK4_pt"      , theData_.jetAK4_pt      );
  theAnalysis_->ConnectVariable( treeName.c_str(), "jetAK4_phi"     , theData_.jetAK4_phi     );
  theAnalysis_->ConnectVariable( treeName.c_str(), "jetAK4_IDLoose" , theData_.jetAK4_IDLoose	);
  theAnalysis_->ConnectVariable( treeName.c_str(), "jetAK4_IDTight" , theData_.jetAK4_IDTight	);
  
  
  if( sample.Contains( "Fall" ) or sample.Contains( "16Dec2015" ) or sample.Contains( "JEC_Summer15_25nsV7" ) ) theAnalysis_->ConnectVariable( treeName.c_str(), "jetAK4_csv"    , theData_.jetAK4_csv     );
  else{
    theAnalysis_->ConnectVariable( treeName.c_str(), "jetAK4_cisv"    , theData_.jetAK4_csv     );
  }
  
 
  if( sample.Contains( "Fall" ) or sample.Contains( "16Dec2015" ) ){
  theAnalysis_->ConnectVariable( treeName.c_str(), "jetAK8_puppi_eta"     , theData_.jetAK8_puppi_eta 	  );
  theAnalysis_->ConnectVariable( treeName.c_str(), "jetAK8_puppi_pt"      , theData_.jetAK8_puppi_pt  	  );
  theAnalysis_->ConnectVariable( treeName.c_str(), "jetAK8_puppi_phi"     , theData_.jetAK8_puppi_phi 	  );
  theAnalysis_->ConnectVariable( treeName.c_str(), "jetAK8_puppi_tau1"    , theData_.jetAK8_puppi_tau1    );
  theAnalysis_->ConnectVariable( treeName.c_str(), "jetAK8_puppi_tau2"    , theData_.jetAK8_puppi_tau2    );
  theAnalysis_->ConnectVariable( treeName.c_str(), "jetAK8_puppi_tau3"    , theData_.jetAK8_puppi_tau3    );
  
  theAnalysis_->ConnectVariable( treeName.c_str(), "jetAK8_puppi_pruned_mass"       , theData_.jetAK8_puppi_pruned_mass   );
  theAnalysis_->ConnectVariable( treeName.c_str(), "jetAK8_puppi_pruned_massCorr"   , theData_.jetAK8_puppi_pruned_massCorr   );
  theAnalysis_->ConnectVariable( treeName.c_str(), "jetAK8_puppi_softdrop_mass"     , theData_.jetAK8_puppi_softdrop_mass );
  theAnalysis_->ConnectVariable( treeName.c_str(), "jetAK8_puppi_softdrop_massCorr" , theData_.jetAK8_puppi_softdrop_massCorr );
  
  theAnalysis_->ConnectVariable( treeName.c_str(), "jetAK10_trimmed_mass"     , theData_.jetAK10_trimmed_mass     );
  theAnalysis_->ConnectVariable( treeName.c_str(), "jetAK10_trimmed_massCorr" , theData_.jetAK10_trimmed_massCorr );
}

  if( sample.Contains( "Fall" ) or sample.Contains( "16Dec2015" ) ){
  theAnalysis_->ConnectVariable( treeName.c_str(), "jetAK8_puppi_e"       , theData_.jetAK8_puppi_e 	    );
  theAnalysis_->ConnectVariable( treeName.c_str(), "jetAK8_puppi_eta"     , theData_.jetAK8_puppi_eta 	  );
  theAnalysis_->ConnectVariable( treeName.c_str(), "jetAK8_puppi_pt"      , theData_.jetAK8_puppi_pt  	  );
  theAnalysis_->ConnectVariable( treeName.c_str(), "jetAK8_puppi_phi"     , theData_.jetAK8_puppi_phi 	  );
  theAnalysis_->ConnectVariable( treeName.c_str(), "jetAK8_puppi_tau1"    , theData_.jetAK8_puppi_tau1    );
  theAnalysis_->ConnectVariable( treeName.c_str(), "jetAK8_puppi_tau2"    , theData_.jetAK8_puppi_tau2    );
  theAnalysis_->ConnectVariable( treeName.c_str(), "jetAK8_puppi_tau3"    , theData_.jetAK8_puppi_tau3    );
  
  theAnalysis_->ConnectVariable( treeName.c_str(), "jetAK8_puppi_pruned_mass"   , theData_.jetAK8_puppi_pruned_mass   );
  theAnalysis_->ConnectVariable( treeName.c_str(), "jetAK8_puppi_pruned_massCorr"   , theData_.jetAK8_puppi_pruned_massCorr   );
  theAnalysis_->ConnectVariable( treeName.c_str(), "jetAK8_puppi_softdrop_mass" , theData_.jetAK8_puppi_softdrop_mass );
  theAnalysis_->ConnectVariable( treeName.c_str(), "jetAK8_puppi_softdrop_massCorr" , theData_.jetAK8_puppi_softdrop_massCorr );
  
  theAnalysis_->ConnectVariable( treeName.c_str(), "jetAK10_trimmed_mass"     , theData_.jetAK10_trimmed_mass     );
  theAnalysis_->ConnectVariable( treeName.c_str(), "jetAK10_trimmed_massCorr" , theData_.jetAK10_trimmed_massCorr );
}
  
  
  
  theAnalysis_->ConnectVariable( treeName.c_str(), "jetAK8_N"                 , theData_.njetsAK8          );
  theAnalysis_->ConnectVariable( treeName.c_str(), "jetAK8_e"                 , theData_.jetAK8_e                 );
  theAnalysis_->ConnectVariable( treeName.c_str(), "jetAK8_mass"              , theData_.jetAK8_mass              );
  
  theAnalysis_->ConnectVariable( treeName.c_str(), "jetAK8_pruned_massCorr", theData_.jetAK8_prunedmass);
  theAnalysis_->ConnectVariable( treeName.c_str(), "jetAK8_pruned_mass"    , theData_.jetAK8_prunedmass_unCorr);
  theAnalysis_->ConnectVariable( treeName.c_str(), "jetAK8_pruned_jec"     , theData_.jetAK8_pruned_jec);
  theAnalysis_->ConnectVariable( treeName.c_str(), "jetAK8_softdrop_mass"  , theData_.jetAK8_softdropmass);
  theAnalysis_->ConnectVariable( treeName.c_str(), "jetAK8_softdrop_jec"   , theData_.jetAK8_softdrop_jec);
      


  theAnalysis_->ConnectVariable( treeName.c_str(), "jetAK8_eta"     , theData_.jetAK8_eta 	  );
  theAnalysis_->ConnectVariable( treeName.c_str(), "jetAK8_pt"      , theData_.jetAK8_pt  	  );
  theAnalysis_->ConnectVariable( treeName.c_str(), "jetAK8_phi"     , theData_.jetAK8_phi 	  );
  theAnalysis_->ConnectVariable( treeName.c_str(), "jetAK8_csv"     , theData_.jetAK8_csv 	  );
  theAnalysis_->ConnectVariable( treeName.c_str(), "jetAK8_tau1"    , theData_.jetAK8_tau1    );
  theAnalysis_->ConnectVariable( treeName.c_str(), "jetAK8_tau2"    , theData_.jetAK8_tau2    );
  theAnalysis_->ConnectVariable( treeName.c_str(), "jetAK8_tau3"    , theData_.jetAK8_tau3    );
  theAnalysis_->ConnectVariable( treeName.c_str(), "jetAK8_IDLoose" , theData_.jetAK8_IDLoose );
  theAnalysis_->ConnectVariable( treeName.c_str(), "jetAK8_IDTight" , theData_.jetAK8_IDTight );
  
  theAnalysis_->ConnectVariable( treeName.c_str(), "jetAK8_jec" , theData_.jetAK8_jec );
  theAnalysis_->ConnectVariable( treeName.c_str(), "jetAK8_cm"      , theData_.jetAK8_cm	    ); //chargedMultiplicity
  theAnalysis_->ConnectVariable( treeName.c_str(), "jetAK8_nm"      , theData_.jetAK8_nm	    ); //neutralMultiplicity
  theAnalysis_->ConnectVariable( treeName.c_str(), "jetAK8_muf"     , theData_.jetAK8_muf			); //muonEnergyFraction
  theAnalysis_->ConnectVariable( treeName.c_str(), "jetAK8_phf"     , theData_.jetAK8_phf			); //photonEnergyFraction
  theAnalysis_->ConnectVariable( treeName.c_str(), "jetAK8_emf"     , theData_.jetAK8_emf			); //chargedEmEnergyFraction
  theAnalysis_->ConnectVariable( treeName.c_str(), "jetAK8_nhf"     , theData_.jetAK8_nhf			); //neutralHadronEnergyFraction
  theAnalysis_->ConnectVariable( treeName.c_str(), "jetAK8_chf"     , theData_.jetAK8_chf		 	); //chargedHadronEnergyFraction
  theAnalysis_->ConnectVariable( treeName.c_str(), "jetAK8_area"    , theData_.jetAK8_area		); //jetArea
  theAnalysis_->ConnectVariable( treeName.c_str(), "jetAK8_che"     , theData_.jetAK8_che     ); //fj.chargedHadronEnergy()+fj.electronEnergy()+fj.muonEnergy()
  theAnalysis_->ConnectVariable( treeName.c_str(), "jetAK8_ne"      , theData_.jetAK8_ne      ); //fj.neutralHadronEnergy()+fj.photonEnergy()
  theAnalysis_->ConnectVariable( treeName.c_str(), "jetAK8_hf_hf"     , theData_.jetAK8_hf_hf     ); //HFHadronEnergyFraction());
  theAnalysis_->ConnectVariable( treeName.c_str(), "jetAK8_hf_emf"     , theData_.jetAK8_hf_emf     ); //HFEMEnergyFraction());
  theAnalysis_->ConnectVariable( treeName.c_str(), "jetAK8_hof"     , theData_.jetAK8_hof     ); //hoEnergyFraction());
  theAnalysis_->ConnectVariable( treeName.c_str(), "jetAK8_chm"     , theData_.jetAK8_chm     ); //chargedHadronMultiplicity());
  theAnalysis_->ConnectVariable( treeName.c_str(), "jetAK8_neHadMult"     , theData_.jetAK8_neHadMult     ); //neutralHadronMultiplicity());
  theAnalysis_->ConnectVariable( treeName.c_str(), "jetAK8_phoMult"     , theData_.jetAK8_phoMult     ); //photonMultiplicity());
  theAnalysis_->ConnectVariable( treeName.c_str(), "jetAK8_nemf"     , theData_.jetAK8_nemf     ); //neutralEmEnergyFraction());
  theAnalysis_->ConnectVariable( treeName.c_str(), "jetAK8_cemf"     , theData_.jetAK8_cemf     ); //chargedEmEnergyFraction());
  theAnalysis_->ConnectVariable( treeName.c_str(), "jetAK8_charge"     , theData_.jetAK8_charge     ); //charge());		
  
  // theAnalysis_->ConnectVariable( treeName.c_str(), "subjetAK8_softdrop_N"  , theData_.subjetAK8_softdrop_N       );
  // theAnalysis_->ConnectVariable( treeName.c_str(), "subjetAK8_softdrop_pt"  , theData_.subjetAK8_softdrop_pt      );
  // theAnalysis_->ConnectVariable( treeName.c_str(), "subjetAK8_softdrop_eta"  , theData_.subjetAK8_softdrop_eta     );
  // theAnalysis_->ConnectVariable( treeName.c_str(), "subjetAK8_softdrop_phi"  , theData_.subjetAK8_softdrop_phi     );
  // theAnalysis_->ConnectVariable( treeName.c_str(), "subjetAK8_softdrop_e"  , theData_.subjetAK8_softdrop_e       );
  // theAnalysis_->ConnectVariable( treeName.c_str(), "subjetAK8_softdrop_csv"  , theData_.subjetAK8_softdrop_csv     );
  // theAnalysis_->ConnectVariable( treeName.c_str(), "subjetAK8_softdrop_partonFlavour", theData_.subjetAK8_softdrop_flavour );
  //
  // theAnalysis_->ConnectVariable( treeName.c_str(), "subjetAK8_pruned_N"  , theData_.subjetAK8_pruned_N       );
  // theAnalysis_->ConnectVariable( treeName.c_str(), "subjetAK8_pruned_pt"  , theData_.subjetAK8_pruned_pt      );
  // theAnalysis_->ConnectVariable( treeName.c_str(), "subjetAK8_pruned_eta"  , theData_.subjetAK8_pruned_eta     );
  // theAnalysis_->ConnectVariable( treeName.c_str(), "subjetAK8_pruned_phi"  , theData_.subjetAK8_pruned_phi     );
  // theAnalysis_->ConnectVariable( treeName.c_str(), "subjetAK8_pruned_e"  , theData_.subjetAK8_pruned_e       );
  // theAnalysis_->ConnectVariable( treeName.c_str(), "subjetAK8_pruned_csv"  , theData_.subjetAK8_pruned_csv     );
  // theAnalysis_->ConnectVariable( treeName.c_str(), "subjetAK8_pruned_partonFlavour", theData_.subjetAK8_pruned_flavour );

  theAnalysis_->ConnectVariable( treeName.c_str(), "MET_et"           , theData_.MET_et             );
  theAnalysis_->ConnectVariable( treeName.c_str(), "MET_sumEt"        , theData_.MET_sumEt          );
  theAnalysis_->ConnectVariable( treeName.c_str(), "MET_phi"					, theData_.MET_phi            );
  theAnalysis_->ConnectVariable( treeName.c_str(), "METraw_et"        , theData_.METraw_et          );
  theAnalysis_->ConnectVariable( treeName.c_str(), "METraw_sumEt"     , theData_.METraw_sumEt       );
  theAnalysis_->ConnectVariable( treeName.c_str(), "METraw_phi"       , theData_.METraw_phi         );
  theAnalysis_->ConnectVariable( treeName.c_str(), "MET_corrPx"       , theData_.MET_corrPx         );
  theAnalysis_->ConnectVariable( treeName.c_str(), "MET_corrPy"       , theData_.MET_corrPy         );
   

  theAnalysis_->ConnectVariable( treeName.c_str(), "PV_N"             , theData_.nPVs        );
  theAnalysis_->ConnectVariable( treeName.c_str(), "PV_filter"        , theData_.PV_filter   );
   
  theAnalysis_->ConnectVariable( treeName.c_str(), "EVENT_event"      , theData_.EVENT_event        );
  theAnalysis_->ConnectVariable( treeName.c_str(), "EVENT_run"        , theData_.EVENT_run          );
  theAnalysis_->ConnectVariable( treeName.c_str(), "EVENT_lumiBlock"  , theData_.EVENT_lumi         );
  theAnalysis_->ConnectVariable( treeName.c_str(), "HLT_isFired" 	   , theData_.HLT_isFired );

  theAnalysis_->ConnectVariable( treeName.c_str(), "passFilter_HBHE"                , theData_.passFilter_HBHE_		 );
  theAnalysis_->ConnectVariable( treeName.c_str(), "passFilter_HBHELoose"           , theData_.passFilter_HBHELoose_		 );
  theAnalysis_->ConnectVariable( treeName.c_str(), "passFilter_HBHEIso"             , theData_.passFilter_HBHEIso_		 );
  theAnalysis_->ConnectVariable( treeName.c_str(), "passFilter_CSCHalo"             , theData_.passFilter_CSCHalo_		 ); 
  theAnalysis_->ConnectVariable( treeName.c_str(), "passFilter_CSCTightHalo2015"    , theData_.passFilter_CSCTightHalo2015_);
  theAnalysis_->ConnectVariable( treeName.c_str(), "passFilter_HCALlaser"           , theData_.passFilter_HCALlaser_  	 );
  theAnalysis_->ConnectVariable( treeName.c_str(), "passFilter_ECALDeadCell"	      , theData_.passFilter_ECALDeadCell_	 );
  theAnalysis_->ConnectVariable( treeName.c_str(), "passFilter_GoodVtx"             , theData_.passFilter_GoodVtx_		 );
  theAnalysis_->ConnectVariable( treeName.c_str(), "passFilter_TrkFailure"          , theData_.passFilter_TrkFailure_ 	 );
  theAnalysis_->ConnectVariable( treeName.c_str(), "passFilter_EEBadSc"             , theData_.passFilter_EEBadSc_		 );
  theAnalysis_->ConnectVariable( treeName.c_str(), "passFilter_ECALlaser"           , theData_.passFilter_ECALlaser_  	 );
  theAnalysis_->ConnectVariable( treeName.c_str(), "passFilter_TrkPOG"              , theData_.passFilter_TrkPOG_		 );
  theAnalysis_->ConnectVariable( treeName.c_str(), "passFilter_TrkPOG_manystrip"    , theData_.passFilter_TrkPOG_manystrip_	 );
  theAnalysis_->ConnectVariable( treeName.c_str(), "passFilter_TrkPOG_toomanystrip" , theData_.passFilter_TrkPOG_toomanystrip_ );
  theAnalysis_->ConnectVariable( treeName.c_str(), "passFilter_TrkPOG_logError"     , theData_.passFilter_TrkPOG_logError_	 );
  theAnalysis_->ConnectVariable( treeName.c_str(), "passFilter_METFilters"          , theData_.passFilter_METFilters_ 	 );
}
