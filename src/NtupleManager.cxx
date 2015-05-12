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
	theAnalysis_->ConnectVariable( treeName.c_str(), "genParticle_px"        , theData_.genParticle_px	      );
	theAnalysis_->ConnectVariable( treeName.c_str(), "genParticle_py"        , theData_.genParticle_py	      );
	theAnalysis_->ConnectVariable( treeName.c_str(), "genParticle_pz"        , theData_.genParticle_pz	      );
	theAnalysis_->ConnectVariable( treeName.c_str(), "genParticle_mass"      , theData_.genParticle_mass       );
	theAnalysis_->ConnectVariable( treeName.c_str(), "genParticle_e"         , theData_.genParticle_e	      );
	theAnalysis_->ConnectVariable( treeName.c_str(), "genParticle_eta"       , theData_.genParticle_eta	      );
	theAnalysis_->ConnectVariable( treeName.c_str(), "genParticle_phi"       , theData_.genParticle_phi	      );
	theAnalysis_->ConnectVariable( treeName.c_str(), "genParticle_dau"       , theData_.genParticle_dau	      );
	theAnalysis_->ConnectVariable( treeName.c_str(), "genParticle_nDau"    	 , theData_.genParticle_nDau     );
	theAnalysis_->ConnectVariable( treeName.c_str(), "genParticle_mother"    , theData_.genParticle_mother     );
	theAnalysis_->ConnectVariable( treeName.c_str(), "genParticle_nMoth"     , theData_.genParticle_nMoth     );
	theAnalysis_->ConnectVariable( treeName.c_str(), "lheV_pt"               , theData_.lheV_pt                );
	theAnalysis_->ConnectVariable( treeName.c_str(), "lheHT"                 , theData_.lheHT                );
	theAnalysis_->ConnectVariable( treeName.c_str(), "lheNj"                 , theData_.lheNj                );
	theAnalysis_->ConnectVariable( treeName.c_str(), "genWeight"             , theData_.genWeight                );
	theAnalysis_->ConnectVariable( treeName.c_str(), "qScale"                , theData_.qScale                );
   
   
   
	theAnalysis_->ConnectVariable( treeName.c_str(), "nlep"		    			, theData_.nlep		      );
	theAnalysis_->ConnectVariable( treeName.c_str(), "lep_e"		    			, theData_.lep_e		      );
	theAnalysis_->ConnectVariable( treeName.c_str(), "lep_eta"		    		, theData_.lep_eta		   );
	theAnalysis_->ConnectVariable( treeName.c_str(), "lep_pt"		    		, theData_.lep_pt		      );
	theAnalysis_->ConnectVariable( treeName.c_str(), "lep_phi"		    		, theData_.lep_phi		   );
	theAnalysis_->ConnectVariable( treeName.c_str(), "lep_type"		   		, theData_.lep_type  	   );
	theAnalysis_->ConnectVariable( treeName.c_str(), "lep_isHEEP"           , theData_.lep_isHEEP      ); 
	theAnalysis_->ConnectVariable( treeName.c_str(), "lep_isHEEPv50"        , theData_.lep_isHEEPv50   ); 
	theAnalysis_->ConnectVariable( treeName.c_str(), "lep_trackIso"         , theData_.lep_trackIso   	);        
	theAnalysis_->ConnectVariable( treeName.c_str(), "lep_isHighPtMuon"     , theData_.lep_isHighPtMuon);
	theAnalysis_->ConnectVariable( treeName.c_str(), "lep_isTightMuon"      , theData_.lep_isTightMuon	);
	theAnalysis_->ConnectVariable( treeName.c_str(), "lep_isLooseMuon"      , theData_.lep_isLooseMuon	);
	theAnalysis_->ConnectVariable( treeName.c_str(), "lep_pfRelIso"      	, theData_.lep_pfRelIso		);

	theAnalysis_->ConnectVariable( treeName.c_str(), "njetsAK4"           	, theData_.njetsAK4			);
	theAnalysis_->ConnectVariable( treeName.c_str(), "jetAK4_e"		 		  	, theData_.jetAK4_e			);
	theAnalysis_->ConnectVariable( treeName.c_str(), "jetAK4_eta"	   		, theData_.jetAK4_eta		);
	theAnalysis_->ConnectVariable( treeName.c_str(), "jetAK4_pt"		   	, theData_.jetAK4_pt			);
	theAnalysis_->ConnectVariable( treeName.c_str(), "jetAK4_phi"	   		, theData_.jetAK4_phi		);
	theAnalysis_->ConnectVariable( treeName.c_str(), "jetAK4_cisv"	   		, theData_.jetAK4_csv		);
	theAnalysis_->ConnectVariable( treeName.c_str(), "jetAK4_flavour"	   	, theData_.jetAK4_flavor	);
	theAnalysis_->ConnectVariable( treeName.c_str(), "jetAK4_IDLoose"	   	, theData_.jetAK4_IDLoose	);
   
	theAnalysis_->ConnectVariable( treeName.c_str(), "njetsAK8"             		, theData_.njetsAK8						);
	theAnalysis_->ConnectVariable( treeName.c_str(), "jetAK8_e"				  			, theData_.jetAK8_e						);
	theAnalysis_->ConnectVariable( treeName.c_str(), "jetAK8_mass"	  					, theData_.jetAK8_mass           	);
	theAnalysis_->ConnectVariable( treeName.c_str(), "jetAK8_prunedmassUnCorr"	   , theData_.jetAK8_prunedmassUnCorr  );
	theAnalysis_->ConnectVariable( treeName.c_str(), "jetAK8_prunedmassCorr"	   , theData_.jetAK8_prunedmassCorr		);
	theAnalysis_->ConnectVariable( treeName.c_str(), "jetAK8pruned_jec"	   		, theData_.jetAK8pruned_jec			);
	theAnalysis_->ConnectVariable( treeName.c_str(), "jetAK8_softdropmassUnCorr"  , theData_.jetAK8_softdropmassUnCorr);
	theAnalysis_->ConnectVariable( treeName.c_str(), "jetAK8_softdropmassCorr"  	, theData_.jetAK8_softdropmassCorr	);
	theAnalysis_->ConnectVariable( treeName.c_str(), "jetAK8softdrop_jec"	   	, theData_.jetAK8softdrop_jec			);
   
	theAnalysis_->ConnectVariable( treeName.c_str(), "jetAK8_eta"	   				, theData_.jetAK8_eta 	    );
	theAnalysis_->ConnectVariable( treeName.c_str(), "jetAK8_pt"		   			, theData_.jetAK8_pt  	    );
	theAnalysis_->ConnectVariable( treeName.c_str(), "jetAK8_phi"	   				, theData_.jetAK8_phi 	    );
	theAnalysis_->ConnectVariable( treeName.c_str(), "jetAK8_csv"	   				, theData_.jetAK8_csv 	    );
	theAnalysis_->ConnectVariable( treeName.c_str(), "jetAK8_cm"	           		, theData_.jetAK8_cm	       );
	theAnalysis_->ConnectVariable( treeName.c_str(), "jetAK8_nm"	           		, theData_.jetAK8_nm	       );
   	
	theAnalysis_->ConnectVariable( treeName.c_str(), "jetAK8_muf"	           , theData_.jetAK8_muf			);
	theAnalysis_->ConnectVariable( treeName.c_str(), "jetAK8_phf"	           , theData_.jetAK8_phf			);
	theAnalysis_->ConnectVariable( treeName.c_str(), "jetAK8_emf"	           , theData_.jetAK8_emf			);
	theAnalysis_->ConnectVariable( treeName.c_str(), "jetAK8_nhf"	           , theData_.jetAK8_nhf			);
	theAnalysis_->ConnectVariable( treeName.c_str(), "jetAK8_chf"	           , theData_.jetAK8_chf		 	);
	theAnalysis_->ConnectVariable( treeName.c_str(), "jetAK8_area"	           , theData_.jetAK8_area		);
   
	theAnalysis_->ConnectVariable( treeName.c_str(), "jetAK8_tau1"	   , theData_.jetAK8_tau1	    );
	theAnalysis_->ConnectVariable( treeName.c_str(), "jetAK8_tau2"	   , theData_.jetAK8_tau2	    );
	theAnalysis_->ConnectVariable( treeName.c_str(), "jetAK8_tau3"	   , theData_.jetAK8_tau3	    );
	theAnalysis_->ConnectVariable( treeName.c_str(), "jetAK8_IDLoose"	, theData_.jetAK8_IDLoose	 );
	theAnalysis_->ConnectVariable( treeName.c_str(), "jetAK8_flavour" , theData_.jetAK8_flavor	 );
	theAnalysis_->ConnectVariable( treeName.c_str(), "jetAK8_che"	   , theData_.jetAK8_che 	    );
	theAnalysis_->ConnectVariable( treeName.c_str(), "jetAK8_ne"	   , theData_.jetAK8_ne 	    );
      
	theAnalysis_->ConnectVariable( treeName.c_str(), "nsubjets"             	, theData_.nsubjets						);
	theAnalysis_->ConnectVariable( treeName.c_str(), "subjetAK8pruned_csv"  	, theData_.subjetAK8pruned_csv		);  
	theAnalysis_->ConnectVariable( treeName.c_str(), "subjetAK8pruned_pt"   	, theData_.subjetAK8pruned_pt			);  
	theAnalysis_->ConnectVariable( treeName.c_str(), "subjetAK8pruned_eta"  	, theData_.subjetAK8pruned_eta		);  
	theAnalysis_->ConnectVariable( treeName.c_str(), "subjetAK8pruned_phi"  	, theData_.subjetAK8pruned_phi		);  
	theAnalysis_->ConnectVariable( treeName.c_str(), "subjetAK8pruned_e"    	, theData_.subjetAK8pruned_e	    	);  
	theAnalysis_->ConnectVariable( treeName.c_str(), "subjetAK8pruned_flavour"	, theData_.subjetAK8pruned_flavor	);  

	// theAnalysis_->ConnectVariable( treeName.c_str(), "njetsAK8pruned"       , theData_.njetsAK8pruned	    );
	//    theAnalysis_->ConnectVariable( treeName.c_str(), "jetAK8pruned_e"	   , theData_.jetAK8pruned_e	    );
	//    theAnalysis_->ConnectVariable( treeName.c_str(), "jetAK8pruned_eta"	   , theData_.jetAK8pruned_eta	    );
	//    theAnalysis_->ConnectVariable( treeName.c_str(), "jetAK8pruned_pt"      , theData_.jetAK8pruned_pt	    );
	//    theAnalysis_->ConnectVariable( treeName.c_str(), "jetAK8pruned_phi"	   , theData_.jetAK8pruned_phi	    );
	//    theAnalysis_->ConnectVariable( treeName.c_str(), "jetAK8pruned_mass"	   , theData_.jetAK8pruned_mass	    );
   
	theAnalysis_->ConnectVariable( treeName.c_str(), "MET_et"	   		   , theData_.MET_et						);
	theAnalysis_->ConnectVariable( treeName.c_str(), "MET_sumEt"	   	   , theData_.MET_sumEt	            );
	theAnalysis_->ConnectVariable( treeName.c_str(), "MET_phi"					, theData_.MET_phi	            );
	theAnalysis_->ConnectVariable( treeName.c_str(), "METraw_et"	   	   , theData_.METraw_et	            );
	theAnalysis_->ConnectVariable( treeName.c_str(), "METraw_sumEt"			, theData_.METraw_sumEt				);
	theAnalysis_->ConnectVariable( treeName.c_str(), "METraw_phi"	   	   , theData_.METraw_phi	         );
	theAnalysis_->ConnectVariable( treeName.c_str(), "MET_corrPx"	   	   , theData_.MET_corrPx	         );
	theAnalysis_->ConnectVariable( treeName.c_str(), "MET_corrPy"	   	   , theData_.MET_corrPy	         );
   
	theAnalysis_->ConnectVariable( treeName.c_str(), "nPuVtxTrue"           , theData_.nPUTrue               );
	theAnalysis_->ConnectVariable( treeName.c_str(), "bX"                   , theData_.bX                    );
	theAnalysis_->ConnectVariable( treeName.c_str(), "nPVs"                 , theData_.nPVs                  );
   
	theAnalysis_->ConnectVariable( treeName.c_str(), "EVENT_event"          , theData_.EVENT_event           );
	theAnalysis_->ConnectVariable( treeName.c_str(), "EVENT_run"            , theData_.EVENT_run             );
	theAnalysis_->ConnectVariable( treeName.c_str(), "EVENT_lumiBlock"      , theData_.EVENT_lumi            );
   
	theAnalysis_->ConnectVariable( treeName.c_str(), "isFired_HLT_AK8PFJet360_TrimMass30_v1"		 							, theData_.isFired_HLT_AK8PFJet360_TrimMass30_v1								);
	theAnalysis_->ConnectVariable( treeName.c_str(), "isFired_HLT_AK8PFHT700_TrimR0p1PT0p03Mass50_v1"					, theData_.isFired_HLT_AK8PFHT700_TrimR0p1PT0p03Mass50_v1					);
	theAnalysis_->ConnectVariable( treeName.c_str(), "isFired_HLT_AK8DiPFJet280_200_TrimMass30_BTagCSV0p41_v1", theData_.isFired_HLT_AK8DiPFJet280_200_TrimMass30_BTagCSV0p41_v1	);
	theAnalysis_->ConnectVariable( treeName.c_str(), "isFired_HLT_PFHT650_WideJetMJJ950DEtaJJ1p5_v1"					, theData_.isFired_HLT_PFHT650_WideJetMJJ950DEtaJJ1p5_v1					);
	theAnalysis_->ConnectVariable( treeName.c_str(), "isFired_HLT_PFHT650_WideJetMJJ900DEtaJJ1p5_v1"		 			, theData_.isFired_HLT_PFHT650_WideJetMJJ900DEtaJJ1p5_v1					);
	theAnalysis_->ConnectVariable( treeName.c_str(), "isFired_HLT_PFHT900_v1"							 										, theData_.isFired_HLT_PFHT900_v1																	);

}
