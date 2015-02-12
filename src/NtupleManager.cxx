#include "include/NtupleManager.h"
#include "core/include/SCycleBase.h"

////////////////////////////////////////////////////////////////////
NtupleManager::NtupleManager( SCycleBase* theAnalysis ):theAnalysis_( theAnalysis )
{

}

////////////////////////////////////////////////////////////////////
NtupleManager::~NtupleManager( void ){

}

////////////////////////////////////////////////////////////////////
void NtupleManager::ConnectVariables( std::string treeName  ){
   
   theAnalysis_->ConnectVariable( treeName.c_str(), "genParticle_pdgId"     , theData_.genParticle_pdgId      );
   theAnalysis_->ConnectVariable( treeName.c_str(), "genParticle_status"    , theData_.genParticle_status     );
   theAnalysis_->ConnectVariable( treeName.c_str(), "genParticle_pt"        , theData_.genParticle_pt	      );
   theAnalysis_->ConnectVariable( treeName.c_str(), "genParticle_mass"      , theData_.genParticle_mass       );
   theAnalysis_->ConnectVariable( treeName.c_str(), "genParticle_e"         , theData_.genParticle_e	      );
   theAnalysis_->ConnectVariable( treeName.c_str(), "genParticle_eta"       , theData_.genParticle_eta	      );
   theAnalysis_->ConnectVariable( treeName.c_str(), "genParticle_phi"       , theData_.genParticle_phi	      );
   theAnalysis_->ConnectVariable( treeName.c_str(), "genParticle_dau"       , theData_.genParticle_dau	      );
   theAnalysis_->ConnectVariable( treeName.c_str(), "genParticle_mother"    , theData_.genParticle_mother     );
   theAnalysis_->ConnectVariable( treeName.c_str(), "lheV_pt"               , theData_.lheV_pt                );
   
   theAnalysis_->ConnectVariable( treeName.c_str(), "nlep"		    , theData_.nlep		      );
   theAnalysis_->ConnectVariable( treeName.c_str(), "lep_e"		    , theData_.lep_e		      );
   theAnalysis_->ConnectVariable( treeName.c_str(), "lep_eta"		    , theData_.lep_eta		      );
   theAnalysis_->ConnectVariable( treeName.c_str(), "lep_pt"		    , theData_.lep_pt		      );
   theAnalysis_->ConnectVariable( treeName.c_str(), "lep_phi"		    , theData_.lep_phi		      );
   theAnalysis_->ConnectVariable( treeName.c_str(), "lep_type"		    , theData_.lep_type  	      );
   theAnalysis_->ConnectVariable( treeName.c_str(), "lep_isHEEP"            , theData_.lep_isHEEP             ); 
   theAnalysis_->ConnectVariable( treeName.c_str(), "lep_trackIso"          , theData_.lep_trackIso           );        
   theAnalysis_->ConnectVariable( treeName.c_str(), "lep_isHighPtMuon"      , theData_.lep_isHighPtMuon       );

   theAnalysis_->ConnectVariable( treeName.c_str(), "njetsAK4"           , theData_.njetsAK4	            );
   theAnalysis_->ConnectVariable( treeName.c_str(), "jetAK4_e"		   , theData_.jetAK4_e		    );
   theAnalysis_->ConnectVariable( treeName.c_str(), "jetAK4_eta"	   , theData_.jetAK4_eta 	    );
   theAnalysis_->ConnectVariable( treeName.c_str(), "jetAK4_pt"		   , theData_.jetAK4_pt  	    );
   theAnalysis_->ConnectVariable( treeName.c_str(), "jetAK4_phi"	   , theData_.jetAK4_phi 	    );
   theAnalysis_->ConnectVariable( treeName.c_str(), "jetAK4_cisv"	   , theData_.jetAK4_csv 	    );
   theAnalysis_->ConnectVariable( treeName.c_str(), "jetAK4_flavour"	   , theData_.jetAK4_flavor	    );
   theAnalysis_->ConnectVariable( treeName.c_str(), "jetAK4_IDLoose"	   , theData_.jetAK4_IDLoose	    );
   
   theAnalysis_->ConnectVariable( treeName.c_str(), "njetsAK8"             , theData_.njetsAK8		    );
   theAnalysis_->ConnectVariable( treeName.c_str(), "jetAK8_e"		   , theData_.jetAK8_e		    );
   theAnalysis_->ConnectVariable( treeName.c_str(), "jetAK8_mass"	   , theData_.jetAK8_mass           );
   theAnalysis_->ConnectVariable( treeName.c_str(), "jetAK8_prunedmass"	   , theData_.jetAK8_prunedmass     );
   theAnalysis_->ConnectVariable( treeName.c_str(), "jetAK8_softdropmass"  , theData_.jetAK8_softdropmass   );
   theAnalysis_->ConnectVariable( treeName.c_str(), "jetAK8_trimmedmass"   , theData_.jetAK8_trimmedmass    );
   theAnalysis_->ConnectVariable( treeName.c_str(), "jetAK8_filteredmass"  , theData_.jetAK8_filteredmass   );

   theAnalysis_->ConnectVariable( treeName.c_str(), "jetAK8_eta"	   , theData_.jetAK8_eta 	    );
   theAnalysis_->ConnectVariable( treeName.c_str(), "jetAK8_pt"		   , theData_.jetAK8_pt  	    );
   theAnalysis_->ConnectVariable( treeName.c_str(), "jetAK8_phi"	   , theData_.jetAK8_phi 	    );
   theAnalysis_->ConnectVariable( treeName.c_str(), "jetAK8_csv"	   , theData_.jetAK8_csv 	    );
   theAnalysis_->ConnectVariable( treeName.c_str(), "jetAK8_cm"	           , theData_.jetAK8_cm	            );
   theAnalysis_->ConnectVariable( treeName.c_str(), "jetAK8_nm"	           , theData_.jetAK8_nm	            );
   theAnalysis_->ConnectVariable( treeName.c_str(), "jetAK8_tau1"	   , theData_.jetAK8_tau1	    );
   theAnalysis_->ConnectVariable( treeName.c_str(), "jetAK8_tau2"	   , theData_.jetAK8_tau2	    );
   theAnalysis_->ConnectVariable( treeName.c_str(), "jetAK8_tau3"	   , theData_.jetAK8_tau3	    );
   theAnalysis_->ConnectVariable( treeName.c_str(), "jetAK8_IDLoose"	   , theData_.jetAK8_IDLoose	    );
   theAnalysis_->ConnectVariable( treeName.c_str(), "jetAK8_flavour"	   , theData_.jetAK8_flavor	    );
   theAnalysis_->ConnectVariable( treeName.c_str(), "jetAK8_che"	   , theData_.jetAK8_che 	    );
   theAnalysis_->ConnectVariable( treeName.c_str(), "jetAK8_ne"	           , theData_.jetAK8_ne 	    );
      
   theAnalysis_->ConnectVariable( treeName.c_str(), "nsubjets"             , theData_.nsubjets	            );
   theAnalysis_->ConnectVariable( treeName.c_str(), "subjetAK8pruned_csv"  , theData_.subjetAK8pruned_csv   );  
   theAnalysis_->ConnectVariable( treeName.c_str(), "subjetAK8pruned_pt"   , theData_.subjetAK8pruned_pt    );  
   theAnalysis_->ConnectVariable( treeName.c_str(), "subjetAK8pruned_eta"  , theData_.subjetAK8pruned_eta   );  
   theAnalysis_->ConnectVariable( treeName.c_str(), "subjetAK8pruned_phi"  , theData_.subjetAK8pruned_phi   );  
   theAnalysis_->ConnectVariable( treeName.c_str(), "subjetAK8pruned_e"    , theData_.subjetAK8pruned_e	    );  
   theAnalysis_->ConnectVariable( treeName.c_str(), "subjetAK8pruned_flavour", theData_.subjetAK8pruned_flavor);  

   theAnalysis_->ConnectVariable( treeName.c_str(), "njetsAK8pruned"       , theData_.njetsAK8pruned	    );
   theAnalysis_->ConnectVariable( treeName.c_str(), "jetAK8pruned_e"	   , theData_.jetAK8pruned_e	    );
   theAnalysis_->ConnectVariable( treeName.c_str(), "jetAK8pruned_eta"	   , theData_.jetAK8pruned_eta	    );
   theAnalysis_->ConnectVariable( treeName.c_str(), "jetAK8pruned_pt"      , theData_.jetAK8pruned_pt	    );
   theAnalysis_->ConnectVariable( treeName.c_str(), "jetAK8pruned_phi"	   , theData_.jetAK8pruned_phi	    );
   theAnalysis_->ConnectVariable( treeName.c_str(), "jetAK8pruned_mass"	   , theData_.jetAK8pruned_mass	    );    
   
   theAnalysis_->ConnectVariable( treeName.c_str(), "MET_et"	   	   , theData_.MET_et	            );
   theAnalysis_->ConnectVariable( treeName.c_str(), "MET_phi"	   	   , theData_.MET_phi	            );
   
   theAnalysis_->ConnectVariable( treeName.c_str(), "nPuVtxTrue"           , theData_.nPUTrue               );
   theAnalysis_->ConnectVariable( treeName.c_str(), "bX"                   , theData_.bX                    );
   theAnalysis_->ConnectVariable( treeName.c_str(), "nPVs"                 , theData_.nPVs                  );
   
   theAnalysis_->ConnectVariable( treeName.c_str(), "EVENT_event"          , theData_.EVENT_event           );
   theAnalysis_->ConnectVariable( treeName.c_str(), "EVENT_run"            , theData_.EVENT_run             );
   theAnalysis_->ConnectVariable( treeName.c_str(), "EVENT_lumiBlock"      , theData_.EVENT_lumi            );

   theAnalysis_->ConnectVariable( treeName.c_str(), "isFired_HLT_Mu40_v1" 	             , theData_.isFired_HLT_Mu40_v1                     );
   theAnalysis_->ConnectVariable( treeName.c_str(), "isFired_HLT_Ele95_CaloIdVT_GsfTrkIdT_v1", theData_.isFired_HLT_Ele95_CaloIdVT_GsfTrkIdT_v1 );

}
