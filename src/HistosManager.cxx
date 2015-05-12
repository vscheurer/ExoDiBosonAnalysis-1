#include "include/HistosManager.h"
#include "include/ExoDiBosonAnalysis.h"
#include "include/Utilities.h"

#include <TH1F.h>
#include <TH2F.h>

////////////////////////////////////////////////////////////////////
HistosManager::HistosManager( ExoDiBosonAnalysis* theAnalysis ):theAnalysis_( theAnalysis )
{

}

////////////////////////////////////////////////////////////////////
HistosManager::~HistosManager( void ){

}

////////////////////////////////////////////////////////////////////
void HistosManager::bookHistos( void ){
	
		theAnalysis_->Book( TH1F(  "Mjj_all"     																	, "M_{jj}"	     				, 200	, 0.	, 5000.	) );
		theAnalysis_->Book( TH1F(  "Pt"	    		  																, "jet pt"	     				, 200	, 0.	, 5000.	) );
		theAnalysis_->Book( TH1F(  "Eta"	 	    																	, "#eta"	     					, 200	, -5.0, 5.0		) );

	
	/************************ Dijet analysis histos ************************/
	
	/* AK4 */
	theAnalysis_->Book( TH1F( "nAK4" 	    		  																, "# AK4"	     											, 13	, 0.	, 12.		) );
	theAnalysis_->Book( TH1F( "nbTagAK4" 	    		  														, "# b-tag AK4"	  									, 13	, 0.	, 12.		) );
	theAnalysis_->Book( TH1F( "AK4jetPt" 	    		  														, "Leading AK4 jet pt"	     				, 200	, 0.	, 2000.	) );
	theAnalysis_->Book( TH1F( "AK4jetHT" 	    		  														, "Leading AK4 jet HT"	     				, 200	, 0.	, 2000.	) );
	theAnalysis_->Book( TH1F( "AK4jetPt_PTweight" 	  													, "Leading AK4 jet pt weighted"	    , 200	, 0.	, 2000.	) );
	theAnalysis_->Book( TH1F( "AK4jetHT_HTweight" 	 														, "Leading AK4 jet ht weighted"	    , 200	, 0.	, 2000.	) );
	
	theAnalysis_->Book( TH1F( "WmassLeptonic" 	    													, "W mass leptonic"										, 200	,  0. , 200.	) );
	theAnalysis_->Book( TH1F( "WmassLeptonic2" 	    													, "W mass leptonic"										, 200	,  0. , 200.	) );
	theAnalysis_->Book( TH1F( "WmassHadronic" 	    													, "W mass hadronic deltaR"						, 200	,  0. , 200.	) );
	theAnalysis_->Book( TH1F( "WtransvMassLeptonic" 	    										, "W mt"															, 200	,  0. , 250.	) );
	theAnalysis_->Book( TH1F( "WtransvMassHadronic" 	    										, "W mt"															, 200	,  0. , 250.	) );
	theAnalysis_->Book( TH1F( "HadronicTop" 	    														, "Hadronic top mass"									, 800	,  0. , 800.	) );
	theAnalysis_->Book( TH1F( "LeptonicTop" 	    														, "Leptonic top mass"									, 800	,  0. , 800.	) );
	theAnalysis_->Book( TH1F( "LeptonicTop2" 	    														, "Leptonic top mass"									, 800	,  0. , 800.	) );
	theAnalysis_->Book( TH1F( "DeltaRJJ" 	    																, "DeltaRJJ"													, 350	,  0. , 3.5	) );

	theAnalysis_->Book( TH1F( "WptLeptonic" 	    														, "W pt"											, 200	,  0. , 200.	) );
	theAnalysis_->Book( TH1F( "WptHadronic" 	    														, "W pt"											, 200	,  0. , 200.	) );
	
	theAnalysis_->Book( TH1F( "LeptonicbCSV" 	    														, "CSV"											, 100	,  0. , 1.		) );
	theAnalysis_->Book( TH1F( "LeptonicbFlavor" 	    												, "Flavor"									, 26	,  0. , 25.	) );
	theAnalysis_->Book( TH1F( "bCandCSV" 	    																, "CSV"											, 100	,  0. , 1.		) );
	theAnalysis_->Book( TH1F( "bCandFlavor" 	    														, "Flavor"									, 26	,  0. , 25.	) );
	
	/* V candidate */
	theAnalysis_->Book( TH1F( "Mjj"    																			, "M_{jj}"	     								, 200	, 0.	, 5000.	) );
	theAnalysis_->Book( TH1F( "DeltaEta"	 	    															, "#Delta#eta_{jj}"	     					, 200	, 0.	, 5.0		) );
	theAnalysis_->Book( TH1F( "Tau21"     	   																, "Second jet #tau_{21}"  	  				, 100	,  0. , 1.  	) );
	theAnalysis_->Book( TH1F( "Tau21_punzi"     	   														, "Second jet #tau_{21}"  	  				, 100	,  0. , 1.  	) );
	theAnalysis_->Book( TH1F( "PrunedMass"																		, "pruned M_{j}, M_{jj} > 890 GeV"		, 80	, 0.	, 200.	) );
	theAnalysis_->Book( TH1F( "SoftdropMass"																	, "softdrop M_{j}	, M_{jj} > 890 GeV"	, 80	, 0.	, 200.	) );
			
	
	theAnalysis_->Book( TH1F( "VVdeltaEta"		 																, "#Delta#eta_{jj}, all cuts"	   		, 200	, -0.1, 1.4 	) );
	theAnalysis_->Book( TH1F( "VcandPrunedMass" 																, "pruned M_{j}, all cuts applied"		, 80	, 0.	, 200.	) );
	theAnalysis_->Book( TH1F( "VcandSoftdropMass" 															, "Softdrop M_{j}, all cuts applied"	, 80	, 0.	, 200.	) ); 	
	theAnalysis_->Book( TH1F( "VcandTau21"     	    														, "Jet #tau_{21}, all cuts applied"		, 100	,  0. , 1.		) );
	theAnalysis_->Book( TH1F( "DiBosonInvMass"	      													, "di-bosons inv mass"						, 5000, 0.	, 5000.	) );
	theAnalysis_->Book( TH1F( "VcandPt1" 	    																, "Leading AK8 jet pt"						, 200	,  0.	, 2000.	) );
	theAnalysis_->Book( TH1F( "VcandPt2"  	    																, "Second AK8 jet pt"						, 200	,  0.	, 2000.	) );
	theAnalysis_->Book( TH1F( "VcandEta1"	    																, "Leading AK8 jet eta"						, 50	, -2.5, 2.5		) );
	theAnalysis_->Book( TH1F( "VcandEta2" 	   																, "Second AK8 jet eta"						, 50	, -2.5, 2.5		) );
	theAnalysis_->Book( TH1F( "VcandPhi1"	    																, "Leading AK8 jet phi"						, 64	, -3.2, 3.2		) );
	theAnalysis_->Book( TH1F( "VcandPhi2" 	    																, "Second AK8 jet phi"						, 64	, -3.2, 3.2		) );
	theAnalysis_->Book( TH1F( "VcandMass1" 	    															, "Leading AK8 jet mass"					, 80	,  0. , 200.	) );
	theAnalysis_->Book( TH1F( "VcandMass2" 	    															, "Second AK8 jet mass"	     				, 80	,  0. , 200.	) );
	
	/* Cut flow */
	theAnalysis_->Book( TH1F( "nEvents"                													, "nEvents"										, 1	, 0.5, 1.5		) );
	theAnalysis_->Book( TH1F( "nPassedTrigger"         													, "nPassedTrigger"							, 1	, 0.5, 1.5		) );
	theAnalysis_->Book( TH1F( "nPassedFoundJets"       													, "nPassedFoundJets"							, 1	, 0.5, 1.5		) );
	theAnalysis_->Book( TH1F( "nPassedJetsDEta"        													, "nPassedJetsDEta"							, 1	, 0.5, 1.5		) );
	theAnalysis_->Book( TH1F( "nPassedMjj"             													, "nPassedMjj"									, 1	, 0.5, 1.5		) );
	theAnalysis_->Book( TH1F( "nPassedTrigger"         													, "nPassedTrigger"							, 1	, 0.5, 1.5		) );
	theAnalysis_->Book( TH1F( "nPassedPrunedJetMass"   													, "nPassedPrunedJetMass"					, 1	, 0.5, 1.5		) );
	theAnalysis_->Book( TH1F( "nPassedTau21Cut"        													, "nPassedTau21Cut"							, 1	, 0.5, 1.5		) );
   
	/* Triggers */
	theAnalysis_->Book( TH1F( "TriggerEffDen" 															, "M(jj)"										, 5000, 0.	, 5000.	) );  
	theAnalysis_->Book( TH1F( "TriggerEffPrunedMassDen"  													, "Pruned M_{j}"	      	 				, 200	, 0. ,  200.  ) );
	theAnalysis_->Book( TH1F( "TriggerEffSoftdropMassDen"													, "Softdrop M_{j}"	      	 			, 200	, 0. ,  200.  ) );
	theAnalysis_->Book( TH1F( "TriggerEffPrunedMassDen_PtCut"  											, "Pruned M_{j}"	      	 				, 200	, 0. ,  200.  ) );
	theAnalysis_->Book( TH1F( "TriggerEffSoftdropMassDen_PtCut"											, "Softdrop M_{j}"	      			 	, 200	, 0. ,  200.  ) );
	theAnalysis_->Book( TH1F( "TriggerEffPruningCut" 												, "M(jj)"	      		 					, 5000, 0. , 5000.  ) );
	theAnalysis_->Book( TH1F( "TriggerEffPruningCut_qstar" 										, "M(jj)"	      							, 5000, 0. , 5000.  ) );	 
	theAnalysis_->Book( TH1F( "TriggerEffSoftdropCut" 												, "M(jj)"	      		 					, 5000, 0. , 5000.  ) );
	theAnalysis_->Book( TH1F( "TriggerEffSoftdropCut_qstar" 										, "M(jj)"	      							, 5000, 0. , 5000.  ) );
	theAnalysis_->Book( TH1F( "TriggerEffTau21Cut" 													, "M(jj)"	      		 					, 5000, 0. , 5000.  ) );
	theAnalysis_->Book( TH1F( "TriggerEffTau21Cut_qstar"											, "M(jj)"	      		 					, 5000, 0. , 5000.  ) );
	
	
	theAnalysis_->Book( TH1F( "TriggerEff_HLT_AK8PFJet360_TrimMass30"																								, "HLT_AK8PFJet360_TrimMass30_v1"	, 5000, 0. , 5000.  ) );
	theAnalysis_->Book( TH1F( "TriggerEff_HLT_AK8PFJet360_TrimMass30_wPruningCut"																		, "HLT_AK8PFJet360_TrimMass30_v1"	, 5000, 0. , 5000.  ) );
	theAnalysis_->Book( TH1F( "TriggerEff_HLT_AK8PFJet360_TrimMass30_wSoftdropCut"																	, "HLT_AK8PFJet360_TrimMass30_v1"   , 5000, 0. , 5000.  ) );
	theAnalysis_->Book( TH1F( "TriggerEff_HLT_AK8PFJet360_TrimMass30_wPruningCut_qstar"															, "HLT_AK8PFJet360_TrimMass30_v1"   , 5000, 0. , 5000.  ) );
	theAnalysis_->Book( TH1F( "TriggerEff_HLT_AK8PFJet360_TrimMass30_wSoftdropCut_qstar"														, "HLT_AK8PFJet360_TrimMass30_v1"   , 5000, 0. , 5000.  ) );
	theAnalysis_->Book( TH1F( "TriggerEff_HLT_AK8PFJet360_TrimMass30_wTau21Cut"																			, "HLT_AK8PFJet360_TrimMass30_v1"	, 5000, 0. , 5000.  ) );
	
	theAnalysis_->Book( TH1F( "TriggerEff_HLT_AK8PFHT700_TrimR0p1PT0p03Mass50"																	, "HLT_AK8PFHT700_TrimR0p1PT0p03Mass50_Mass30_v1"	, 5000, 0. , 5000.  ) );
	theAnalysis_->Book( TH1F( "TriggerEff_HLT_AK8PFHT700_TrimR0p1PT0p03Mass50_wPruningCut"											, "HLT_AK8PFHT700_TrimR0p1PT0p03Mass50_Mass30_v1"	, 5000, 0. , 5000.  ) );
	theAnalysis_->Book( TH1F( "TriggerEff_HLT_AK8PFHT700_TrimR0p1PT0p03Mass50_wSoftdropCut"											, "HLT_AK8PFHT700_TrimR0p1PT0p03Mass50_Mass30_v1"   , 5000, 0. , 5000.  ) );
	theAnalysis_->Book( TH1F( "TriggerEff_HLT_AK8PFHT700_TrimR0p1PT0p03Mass50_wPruningCut_qstar"								, "HLT_AK8PFHT700_TrimR0p1PT0p03Mass50_Mass30_v1"   , 5000, 0. , 5000.  ) );
	theAnalysis_->Book( TH1F( "TriggerEff_HLT_AK8PFHT700_TrimR0p1PT0p03Mass50_wSoftdropCut_qstar"								, "HLT_AK8PFHT700_TrimR0p1PT0p03Mass50_Mass30_v1"   , 5000, 0. , 5000.  ) );
	theAnalysis_->Book( TH1F( "TriggerEff_HLT_AK8PFHT700_TrimR0p1PT0p03Mass50_wTau21Cut"												, "HLT_AK8PFHT700_TrimR0p1PT0p03Mass50_Mass30_v1"		, 5000, 0. , 5000.  ) );
	
	theAnalysis_->Book( TH1F( "TriggerEff_HLT_AK8DiPFJet280_200_TrimMass30_BTagCSV0p41"																	, "HLT_AK8DiPFJet280_200_TrimMass30_BTagCSV0p41_Mass30_v1"	, 5000, 0. , 5000.  ) );
	theAnalysis_->Book( TH1F( "TriggerEff_HLT_AK8DiPFJet280_200_TrimMass30_BTagCSV0p41_wPruningCut"											, "HLT_AK8DiPFJet280_200_TrimMass30_BTagCSV0p41_Mass30_v1"	, 5000, 0. , 5000.  ) );
	theAnalysis_->Book( TH1F( "TriggerEff_HLT_AK8DiPFJet280_200_TrimMass30_BTagCSV0p41_wSoftdropCut"											, "HLT_AK8DiPFJet280_200_TrimMass30_BTagCSV0p41_Mass30_v1"   , 5000, 0. , 5000.  ) );
	theAnalysis_->Book( TH1F( "TriggerEff_HLT_AK8DiPFJet280_200_TrimMass30_BTagCSV0p41_wPruningCut_qstar"								, "HLT_AK8DiPFJet280_200_TrimMass30_BTagCSV0p41_Mass30_v1"   , 5000, 0. , 5000.  ) );
	theAnalysis_->Book( TH1F( "TriggerEff_HLT_AK8DiPFJet280_200_TrimMass30_BTagCSV0p41_wSoftdropCut_qstar"								, "HLT_AK8DiPFJet280_200_TrimMass30_BTagCSV0p41_Mass30_v1"   , 5000, 0. , 5000.  ) );
	theAnalysis_->Book( TH1F( "TriggerEff_HLT_AK8DiPFJet280_200_TrimMass30_BTagCSV0p41_wTau21Cut"												, "HLT_AK8DiPFJet280_200_TrimMass30_BTagCSV0p41_Mass30_v1"		, 5000, 0. , 5000.  ) );
	
	theAnalysis_->Book( TH1F( "TriggerEff_HLT_PFHT900"														, "HLT_PFHT900_v1"	    					, 5000, 0. , 5000.  ) );
	theAnalysis_->Book( TH1F( "TriggerEff_HLT_PFHT900_wPruningCut"								, "HLT_PFHT900_v1"	    					, 5000, 0. , 5000.  ) );
	theAnalysis_->Book( TH1F( "TriggerEff_HLT_PFHT900_wPruningCut_qstar"								, "HLT_PFHT900_v1"	    					, 5000, 0. , 5000.  ) );
	theAnalysis_->Book( TH1F( "TriggerEff_HLT_PFHT900_wSoftdropCut"								, "HLT_PFHT900_v1"	    					, 5000, 0. , 5000.  ) );
	theAnalysis_->Book( TH1F( "TriggerEff_HLT_PFHT900_wTau21Cut"									, "HLT_PFHT900_v1"	    					, 5000, 0. , 5000.  ) );	
	
	theAnalysis_->Book( TH1F( "TriggerEff_HLT_PFHT650_WideJetMJJ950DEtaJJ1p5"														, "HLT_PFHT650_WideJetMJJ950DEtaJJ1p5_v1"	    					, 5000, 0. , 5000.  ) );
	theAnalysis_->Book( TH1F( "TriggerEff_HLT_PFHT650_WideJetMJJ950DEtaJJ1p5_wPruningCut"								, "HLT_PFHT650_WideJetMJJ950DEtaJJ1p5_v1"	    					, 5000, 0. , 5000.  ) );
	theAnalysis_->Book( TH1F( "TriggerEff_HLT_PFHT650_WideJetMJJ950DEtaJJ1p5_wPruningCut_qstar"					, "HLT_PFHT650_WideJetMJJ950DEtaJJ1p5_v1"	    					, 5000, 0. , 5000.  ) );
	theAnalysis_->Book( TH1F( "TriggerEff_HLT_PFHT650_WideJetMJJ950DEtaJJ1p5_wSoftdropCut"							, "HLT_PFHT650_WideJetMJJ950DEtaJJ1p5_v1"	    					, 5000, 0. , 5000.  ) );
	theAnalysis_->Book( TH1F( "TriggerEff_HLT_PFHT650_WideJetMJJ950DEtaJJ1p5_wTau21Cut"									, "HLT_PFHT650_WideJetMJJ950DEtaJJ1p5_v1"	    					, 5000, 0. , 5000.  ) );	
	theAnalysis_->Book( TH1F( "TriggerEff_HLT_PFHT650_WideJetMJJ900DEtaJJ1p5"														, "HLT_PFHT650_WideJetMJJ900DEtaJJ1p5_v1"	    					, 5000, 0. , 5000.  ) );
	theAnalysis_->Book( TH1F( "TriggerEff_HLT_PFHT650_WideJetMJJ900DEtaJJ1p5_wPruningCut"								, "HLT_PFHT650_WideJetMJJ900DEtaJJ1p5_v1"	    					, 5000, 0. , 5000.  ) );
	theAnalysis_->Book( TH1F( "TriggerEff_HLT_PFHT650_WideJetMJJ900DEtaJJ1p5_wPruningCut_qstar"					, "HLT_PFHT650_WideJetMJJ900DEtaJJ1p5_v1"	    					, 5000, 0. , 5000.  ) );
	theAnalysis_->Book( TH1F( "TriggerEff_HLT_PFHT650_WideJetMJJ900DEtaJJ1p5_wSoftdropCut"							, "HLT_PFHT650_WideJetMJJ900DEtaJJ1p5_v1"	    					, 5000, 0. , 5000.  ) );
	theAnalysis_->Book( TH1F( "TriggerEff_HLT_PFHT650_WideJetMJJ900DEtaJJ1p5_wTau21Cut"									, "HLT_PFHT650_WideJetMJJ900DEtaJJ1p5_v1"	    					, 5000, 0. , 5000.  ) );
	
	theAnalysis_->Book( TH1F( "TriggerEff_ALL"																				, "OR"	    									, 5000, 0. , 5000.  ) );
	theAnalysis_->Book( TH1F( "TriggerEff_ALL_wPruningCut"														, "OR"	    									, 5000, 0. , 5000.  ) );
	theAnalysis_->Book( TH1F( "TriggerEff_ALL_wSoftdropCut"													, "OR"	    									, 5000, 0. , 5000.  ) );
	theAnalysis_->Book( TH1F( "TriggerEff_ALL_wTau21Cut"															, "OR"	   									, 5000, 0. , 5000.  ) );
	theAnalysis_->Book( TH1F( "TriggerEff_ALL_wPruningCut_qstar"											, "OR"	   									, 5000, 0. , 5000.  ) );
	theAnalysis_->Book( TH1F( "TriggerEff_ALL_wSoftdropCut_qstar"										, "OR"	   									, 5000, 0. , 5000.  ) );		
	theAnalysis_->Book( TH1F( "TriggerEffPrunedMass_ALL_PtCut"												, "OR"	, 200	, 0. ,  200.  ) );
	theAnalysis_->Book( TH1F( "TriggerEffSoftdropMass_ALL_PtCut"											, "OR"	, 200	, 0. ,  200.  ) );
	
	theAnalysis_->Book( TH1F( "TriggerEff_HT"																				, "OR"	    									, 5000, 0. , 5000.  ) );
	theAnalysis_->Book( TH1F( "TriggerEff_HT_wPruningCut"														, "OR"	    									, 5000, 0. , 5000.  ) );
	theAnalysis_->Book( TH1F( "TriggerEff_HT_wSoftdropCut"													, "OR"	    									, 5000, 0. , 5000.  ) );
	theAnalysis_->Book( TH1F( "TriggerEff_HT_wTau21Cut"															, "OR"	   									, 5000, 0. , 5000.  ) );
	theAnalysis_->Book( TH1F( "TriggerEff_HT_wPruningCut_qstar"											, "OR"	   									, 5000, 0. , 5000.  ) );
	theAnalysis_->Book( TH1F( "TriggerEff_HT_wSoftdropCut_qstar"										, "OR"	   									, 5000, 0. , 5000.  ) );		
	theAnalysis_->Book( TH1F( "TriggerEffPrunedMass_HT_PtCut"												, "OR"	, 200	, 0. ,  200.  ) );
	theAnalysis_->Book( TH1F( "TriggerEffSoftdropMass_HT_PtCut"											, "OR"	, 200	, 0. ,  200.  ) );
	theAnalysis_->Book( TH1F( "TriggerEffPrunedMass_trimmed_PtCut"											, "OR"	, 200	, 0. ,  200.  ) );
	theAnalysis_->Book( TH1F( "TriggerEffSoftdropMass_trimmed_PtCut"										, "OR"	, 200	, 0. ,  200.  ) );
	theAnalysis_->Book( TH1F( "TriggerEff_trimmed_wPruningCut"														, "OR"	    									, 5000, 0. , 5000.  ) );
	theAnalysis_->Book( TH1F( "TriggerEff_trimmed_wPruningCut_qstar"														, "OR"	    									, 5000, 0. , 5000.  ) );
	theAnalysis_->Book( TH1F( "TriggerEff_trimmed_wSoftdropCut"											, "OR"	    									, 5000, 0. , 5000.  ) );
	theAnalysis_->Book( TH1F( "TriggerEff_trimmed_wSoftdropCut_qstar"								, "OR"	    									, 5000, 0. , 5000.  ) );
	
	theAnalysis_->Book( TH1F( "TriggerEffPrunedMass_HLT_AK8PFJet360_TrimMass30_wMjjCut"											, "HLT_AK8PFJet360_TrimMass30"	, 200	, 0. ,  200.  ) );
	theAnalysis_->Book( TH1F( "TriggerEffSoftdropMass_HLT_AK8PFJet360_TrimMass30_wMjjCut"										, "HLT_AK8PFJet360_TrimMass30"	, 200	, 0. ,  200.  ) );
	theAnalysis_->Book( TH1F( "TriggerEffPrunedMass_HLT_AK8PFJet360_TrimMass30_PtCut"												, "HLT_AK8PFJet360_TrimMass30"	, 200	, 0. ,  200.  ) );
	theAnalysis_->Book( TH1F( "TriggerEffSoftdropMass_HLT_AK8PFJet360_TrimMass30_PtCut"											, "HLT_AK8PFJet360_TrimMass30"	, 200	, 0. ,  200.  ) );
	
	theAnalysis_->Book( TH1F( "TriggerEffPrunedMass_HLT_AK8PFHT700_TrimR0p1PT0p03Mass50_wMjjCut"				, "HLT_AK8PFHT700_TrimR0p1PT0p03Mass50_v1"	, 200	, 0. ,  200.  ) );
	theAnalysis_->Book( TH1F( "TriggerEffSoftdropMass_HLT_AK8PFHT700_TrimR0p1PT0p03Mass50_wMjjCut"			, "HLT_AK8PFHT700_TrimR0p1PT0p03Mass50_v1"	, 200	, 0. ,  200.  ) );
	theAnalysis_->Book( TH1F( "TriggerEffPrunedMass_HLT_AK8PFHT700_TrimR0p1PT0p03Mass50_PtCut"					, "HLT_AK8PFHT700_TrimR0p1PT0p03Mass50_v1"	, 200	, 0. ,  200.  ) );
	theAnalysis_->Book( TH1F( "TriggerEffSoftdropMass_HLT_AK8PFHT700_TrimR0p1PT0p03Mass50_PtCut"				, "HLT_AK8PFHT700_TrimR0p1PT0p03Mass50_v1"	, 200	, 0. ,  200.  ) );
	
	theAnalysis_->Book( TH1F( "TriggerEffPrunedMass_HLT_AK8DiPFJet280_200_TrimMass30_BTagCSV0p41_wMjjCut"				, "HLT_AK8DiPFJet280_200_TrimMass30_BTagCSV0p41_v1"	, 200	, 0. ,  200.  ) );
	theAnalysis_->Book( TH1F( "TriggerEffSoftdropMass_HLT_AK8DiPFJet280_200_TrimMass30_BTagCSV0p41_wMjjCut"			, "HLT_AK8DiPFJet280_200_TrimMass30_BTagCSV0p41_v1"	, 200	, 0. ,  200.  ) );
	theAnalysis_->Book( TH1F( "TriggerEffPrunedMass_HLT_AK8DiPFJet280_200_TrimMass30_BTagCSV0p41_PtCut"					, "HLT_AK8DiPFJet280_200_TrimMass30_BTagCSV0p41_v1"	, 200	, 0. ,  200.  ) );
	theAnalysis_->Book( TH1F( "TriggerEffSoftdropMass_HLT_AK8DiPFJet280_200_TrimMass30_BTagCSV0p41_PtCut"				, "HLT_AK8DiPFJet280_200_TrimMass30_BTagCSV0p41_v1"	, 200	, 0. ,  200.  ) );
	
	
	/************************ Semileoptonic analysis histos ************************/
	
   /* lepton efficiency histos */
   theAnalysis_->Book( TH1F( "leptonRecoEffPT"       , "lepton pt"	      ,    50,  0. , 5000.  ) );
   theAnalysis_->Book( TH1F( "leptonRecoEffPTden"    , "lepton pt"	      ,    50,  0. , 5000.  ) );
   theAnalysis_->Book( TH1F( "leptonRecoEffEta"      , "lepton eta"	      ,    50, -2.5,	2.5 ) );
   theAnalysis_->Book( TH1F( "leptonRecoEffEtaden"   , "lepton eta"	      ,    50, -2.5,	2.5 ) );
   theAnalysis_->Book( TH1F( "leptonRecoGenDR"       , "#DeltaR(gen,reco)"    ,  1000,  0. ,   10.  ) );
   theAnalysis_->Book( TH1F( "leptonRecoGenDPT"      , "#Deltap_{T}(gen,reco)",  1000,-10. ,   10.  ) );
   theAnalysis_->Book( TH1F( "leptonIDEffPT"         , "lepton pt"	      ,   500,  0. , 5000.  ) );
   theAnalysis_->Book( TH1F( "leptonIDEffPTden"      , "lepton pt"	      ,   500,  0. , 5000.  ) );
   theAnalysis_->Book( TH1F( "leptonIDEffEta"        , "lepton eta"	      ,    50, -2.5,	2.5 ) );
   theAnalysis_->Book( TH1F( "leptonIDEffEtaden"     , "lepton eta"	      ,    50, -2.5,	2.5 ) );
   theAnalysis_->Book( TH1F( "leptonTriggerEffPT"    , "lepton pt"	      ,  5000,  0. , 5000.  ) );
   theAnalysis_->Book( TH1F( "leptonTriggerEffPTden" , "lepton pt"	      ,  5000,  0. , 5000.  ) );
   theAnalysis_->Book( TH1F( "leptonTriggerEffEta"   , "lepton eta"	      ,    50, -2.5,	2.5 ) );
   theAnalysis_->Book( TH1F( "leptonTriggerEffEtaden", "lepton eta"	      ,    50, -2.5,	2.5 ) );
         
   /* AK8 b-jet histos */
   theAnalysis_->Book( TH1F( "AK8bjetPT"				, "AK8 b-jet pt"				,   200,  0. , 2000.  ) );
   theAnalysis_->Book( TH1F( "AK8bjetEta"				, "AK8 b-jet eta"				,    50, -2.5,    2.5 ) );
   theAnalysis_->Book( TH1F( "AK8bjetPhi"				, "AK8 b-jet phi"				,    64, -3.2,    3.2 ) );
   theAnalysis_->Book( TH1F( "AK8bjetCSV"				, "AK8 b-jet csv"				,    50,  0. ,    1.  ) );
   theAnalysis_->Book( TH1F( "AK8bjetMass"			, "AK8 b-jet mass"			,    80,  0. ,  200.  ) );
   theAnalysis_->Book( TH1F( "AK8bjetPrunedMass"	, "AK8 b-jet pruned mass"	,    80,  0. ,  200.  ) );
   theAnalysis_->Book( TH1F( "tau21"					, "#tau_{21}"					,   100,  0. ,    1.  ) );
   theAnalysis_->Book( TH1F( "tau31"					, "#tau_{31}"					,   100,  0. ,    1.  ) );
   theAnalysis_->Book( TH1F( "tau32"					, "#tau_{32}"					,   100,  0. ,    1.  ) );

   /* lepton histos */
   theAnalysis_->Book( TH1F( "leptonPT"   	    , "lepton pt"	     ,   200,  0. , 2000.  ) );		   
   theAnalysis_->Book( TH1F( "leptonPhi"   	    , "lepton #phi"	     ,    32, -3.2,    3.2 ) );		   
   theAnalysis_->Book( TH1F( "leptonEta"  	    , "lepton eta"	     ,    50, -2.5,    2.5 ) );		   

   /* MET histos */
   theAnalysis_->Book( TH1F( "MET"	  	    , "#slash{E}_T"	     ,   200,  0. , 2000.  ) );
   theAnalysis_->Book( TH1F( "METphi"	  	    , "MET $phi"	     ,    64, -3.2,    3.2 ) );
 
   /* leptonic W histos */
   theAnalysis_->Book( TH1F( "recoWPT"    	    , "W p_{T}" 	     ,   200,  0. , 2000.  ) );
   theAnalysis_->Book( TH1F( "recoWMT"    	    , "W M_{T}" 	     ,   400,  0. , 2000.  ) );
 
   /* AK4 jets histos */
   theAnalysis_->Book( TH1F( "nAJets"    	    , "# additional jets"    ,    21, -0.5,   20.5 ) );
   theAnalysis_->Book( TH1F( "nAJetsBTag"    	    , "# additional jets"    ,    21, -0.5,   20.5 ) );
   theAnalysis_->Book( TH1F( "AK4jetPt"    	    , "AK4 leading jet p_{T}",   100,  0. , 1000.  ) );
   theAnalysis_->Book( TH1F( "AK4jetCSV"    	    , "AK4 jet CSV"          ,    50,  0. ,    1.  ) );
   theAnalysis_->Book( TH1F( "AK4jetMass"    	    , "AK4 jet mass"         ,   150,  0. ,  300.  ) );

    /* topology histos */
   theAnalysis_->Book( TH1F( "lepJetDR"   	      , "#DeltaR(l,j)"	         , 100, 0. ,   10.  ) );
   theAnalysis_->Book( TH1F( "METJetDphi" 	      , "#Delta#phi(MET,j)"      , 128, 0. ,    3.2 ) );
   theAnalysis_->Book( TH1F( "WJetDphi"     	      , "#Delta#phi(j,W)"        , 128, 0. ,    3.2 ) );      

   /* top histos */
   theAnalysis_->Book( TH1F( "leptonictopmass"        , "leptonic top mass"      , 100, 0. , 1000.  ) );
   theAnalysis_->Book( TH1F( "hadronictopmass"        , "hadronic top mass"      , 100, 0. , 1000.  ) );
   theAnalysis_->Book( TH1F( "leptonictopmassV2"        , "leptonic top mass"      , 100, 0. , 1000.  ) );

   /* cut flow */
   theAnalysis_->Book( TH1F( "genEvents"              , "genEvents"              ,   1, 0.5,    1.5 ) );    
   theAnalysis_->Book( TH1F( "nEvents"                , "nEvents"	    	 ,   1, 0.5,    1.5 ) );
   theAnalysis_->Book( TH1F( "nPassedTrigger"         , "nPassedTrigger"    	 ,   1, 0.5,    1.5 ) );
   theAnalysis_->Book( TH1F( "nPassedFoundLepton"     , "nPassedFoundLepton" 	 ,   1, 0.5,    1.5 ) );
   theAnalysis_->Book( TH1F( "nPassedFoundMET"        , "nPassedFoundMET"  	 ,   1, 0.5,    1.5 ) );
   theAnalysis_->Book( TH1F( "nPassedFoundW"          , "nnPassedFoundW"    	 ,   1, 0.5,    1.5 ) );
   theAnalysis_->Book( TH1F( "nPassedFoundJet"        , "nPassedFoundJet"  	 ,   1, 0.5,    1.5 ) );
   theAnalysis_->Book( TH1F( "nPassedJetPtTight"      , "nPassedJetPtTight"	 ,   1, 0.5,    1.5 ) );
   theAnalysis_->Book( TH1F( "nPassedLepJetDR"        , "nPassedLepJetDR"  	 ,   1, 0.5,    1.5 ) );
   theAnalysis_->Book( TH1F( "nPassedTOBTECFilter"    , "nPassedTOBTECFilter"  	 ,   1, 0.5,    1.5 ) );
   theAnalysis_->Book( TH1F( "nPassedNsubj"           , "nPassedNsubj"  	 ,   1, 0.5,    1.5 ) );
   theAnalysis_->Book( TH1F( "nPassedDRsubj"          , "nPassedDRsubj"  	 ,   1, 0.5,    1.5 ) );
   theAnalysis_->Book( TH1F( "nPassedJetCSV"          , "nPassedJetCSV"    	 ,   1, 0.5,    1.5 ) );   
   theAnalysis_->Book( TH1F( "nPassedAJetCut"         , "nPassedAJetCut"    	 ,   1, 0.5,    1.5 ) );
   theAnalysis_->Book( TH1F( "nPassedLepJetDR2"       , "nPassedLepJetDR2" 	 ,   1, 0.5,    1.5 ) );
   theAnalysis_->Book( TH1F( "nPassedMETJetDPhi"      , "nPassedMETJetDPhi"	 ,   1, 0.5,    1.5 ) );
   theAnalysis_->Book( TH1F( "nPassedJetWDPhi"        , "nPassedJetWDPhi"  	 ,   1, 0.5,    1.5 ) );
   theAnalysis_->Book( TH1F( "nPassedTopMass"         , "nPassedTopMass"  	 ,   1, 0.5,    1.5 ) );   
   theAnalysis_->Book( TH1F( "nPassedJetMass"         , "nPassedJetMass"    	 ,   1, 0.5,    1.5 ) );
   theAnalysis_->Book( TH1F( "nPassedExoCandidateMass", "nPassedExoCandidateMass",   1, 0.5,    1.5 ) );
	
	
	theAnalysis_->Book( TH1F( "nPassedIsoLep"			,"nPassedIsoLep"		,   1, 0.5,    1.5 ) );
	theAnalysis_->Book( TH1F( "nPassedVetoLep"		,"nPassedVetoLep"		,   1, 0.5,    1.5 ) );
	theAnalysis_->Book( TH1F( "nPassed1Jet"			,"nPassed1Jet"			,   1, 0.5,    1.5 ) );
	theAnalysis_->Book( TH1F( "nPassed2Jet"			,"nPassed2Jet"			,   1, 0.5,    1.5 ) );
	theAnalysis_->Book( TH1F( "nPassed3Jet"			,"nPassed3Jet"			,   1, 0.5,    1.5 ) );
	theAnalysis_->Book( TH1F( "nPassed4Jet"			,"nPassed4Jet"			,   1, 0.5,    1.5 ) );
	theAnalysis_->Book( TH1F( "nPassed1bTag"			,"nPassed1bTag"		,   1, 0.5,    1.5 ) );
	theAnalysis_->Book( TH1F( "nPassed2bTag"			,"nPassed2bTag"		,   1, 0.5,    1.5 ) );

   /* other histos */
   theAnalysis_->Book( TH1F( "PUWeights"            , "pu weights"           ,   100,  0. ,    5.  ) );
   theAnalysis_->Book( TH1F( "htagweight"           , "h tag weights"        ,   100,  0. ,    5.  ) );
   theAnalysis_->Book( TH1F( "btagvweight"          , "b tag veto weights"   ,   100,  0. ,    5.  ) );
   theAnalysis_->Book( TH1F( "nVertices"            , "number of PVs"        ,    40,  0. ,   40.  ) );

   /* debugging di-boson inv mass reconstruction*/
   theAnalysis_->Book( TH1F( "Discriminant"         , "#Delta"            ,   80,   -20. ,   20. ) );
   theAnalysis_->Book( TH1F( "A"                    , "A"                 ,   80,     0. ,   20. ) );
   theAnalysis_->Book( TH1F( "B"                    , "B"                 ,  100,   -50. ,   50. ) );
   theAnalysis_->Book( TH1F( "C"                    , "C"                 ,  120,   -10. ,   50. ) );
   theAnalysis_->Book( TH1F( "a"                    , "a"                 ,  100,     0. ,   50. ) );
   theAnalysis_->Book( TH1F( "pzNu"                 , "pzNu"              ,  100, -1000. , 1000. ) );
   theAnalysis_->Book( TH1F( "DiBosonInvMassMethod2", "mass"              ,  500,     0. , 5000. ) );
   theAnalysis_->Book( TH1F( "DiBosonInvMassDeltam" , "mass"              ,  500,     0. , 5000. ) );
   theAnalysis_->Book( TH1F( "DiBosonInvMassDeltap" , "mass"              ,  500,     0. , 5000. ) );
   theAnalysis_->Book( TH1F( "NuLeptInvMass"        , "mass"              ,  200,     0. ,  200. ) );
   theAnalysis_->Book( TH1F( "NuLeptInvMassDeltam"  , "mass"              ,  200,     0. ,  200. ) );
   theAnalysis_->Book( TH1F( "NuLeptInvMassDeltap"  , "mass"              ,  200,     0. ,  200. ) );
   theAnalysis_->Book( TH1F( "genWMass"             , "mass"              ,  200,     0. ,  200. ) );
   theAnalysis_->Book( TH1F( "WMassResolution"      , "resolution"        , 1000,   -10. ,   10. ) );
   theAnalysis_->Book( TH1F( "WMassResolutionV2"    , "resolution"        , 1000,   -10. ,   10. ) );
   theAnalysis_->Book( TH1F( "WHMassResolution"     , "resolution"        , 1000,   -10. ,   10. ) );
   theAnalysis_->Book( TH1F( "WHMassResolutionV2"   , "resolution"        , 1000,   -10. ,   10. ) );
           
	
}

////////////////////////////////////////////////////////////////////
void HistosManager::formatHistos( void ){
	
	theAnalysis_->Hist( "AK4jetHT"					)->GetXaxis()->SetTitle( "H_{T} [GeV]"           	   );
	theAnalysis_->Hist( "AK4jetPt"					)->GetXaxis()->SetTitle( "p_{T} [GeV]"           	   );
	theAnalysis_->Hist( "AK4jetHT_HTweight"		)->GetXaxis()->SetTitle( "H_{T} [GeV]"           	   );
	theAnalysis_->Hist( "AK4jetPt_PTweight"		)->GetXaxis()->SetTitle( "p_{T} [GeV]"           	   );
	
	theAnalysis_->Hist( "DiBosonInvMass"			)->GetXaxis()->SetTitle( "M_{G} [GeV]"           	   );
	theAnalysis_->Hist( "VVdeltaEta"					)->GetXaxis()->SetTitle( "#Delta#eta_{jj}"           	);
	theAnalysis_->Hist( "DeltaEta"					)->GetXaxis()->SetTitle( "#Delta#eta_{jj}"           	);
	theAnalysis_->Hist( "Mjj"							)->GetXaxis()->SetTitle( "M_{jj} [GeV]"           	   );
	theAnalysis_->Hist( "Tau21"						)->GetXaxis()->SetTitle( "#tau_{21}"			    		);
	theAnalysis_->Hist( "Tau21_punzi"				)->GetXaxis()->SetTitle( "#tau_{21}"			    		);
	theAnalysis_->Hist( "PrunedMass"					)->GetXaxis()->SetTitle( "M_{j} [GeV]"           	   );
	theAnalysis_->Hist( "SoftdropMass"				)->GetXaxis()->SetTitle( "M_{j} [GeV]"           	   );
	theAnalysis_->Hist( "VcandPrunedMass"			)->GetXaxis()->SetTitle( "M_{j} [GeV]"           	   );
	theAnalysis_->Hist( "VcandSoftdropMass"		)->GetXaxis()->SetTitle( "M_{j} [GeV]"           	   );
	
	theAnalysis_->Hist( "VcandPt1"					)->GetXaxis()->SetTitle( "W_{hadr} p_{T} [GeV]"		   );
	theAnalysis_->Hist( "VcandPt2"					)->GetXaxis()->SetTitle( "W_{hadr} p_{T} [GeV]"		   );
	theAnalysis_->Hist( "VcandEta1"					)->GetXaxis()->SetTitle( "W_{hadr} #eta"		         );
	theAnalysis_->Hist( "VcandEta2"					)->GetXaxis()->SetTitle( "W_{hadr} #eta"		         );
	theAnalysis_->Hist( "VcandPhi1"					)->GetXaxis()->SetTitle( "W_{hadr} #phi [rad]"		   );
	theAnalysis_->Hist( "VcandPhi2"					)->GetXaxis()->SetTitle( "W_{hadr} #phi [rad]"		   );
	theAnalysis_->Hist( "VcandMass1"					)->GetXaxis()->SetTitle( "W_{hadr} mass [GeV]"		   );
	theAnalysis_->Hist( "VcandMass2"					)->GetXaxis()->SetTitle( "W_{hadr} mass [GeV]"		   );
	theAnalysis_->Hist( "VcandTau21"					)->GetXaxis()->SetTitle( "#tau_{21}"			    		);
	
	
	Utilities::OverflowToLast( theAnalysis_->Hist( "AK4jetPt"					) );
	Utilities::OverflowToLast( theAnalysis_->Hist( "DiBosonInvMass"			) );
	Utilities::OverflowToLast( theAnalysis_->Hist( "VVdeltaEta"					) );
	// Utilities::OverflowToLast( theAnalysis_->Hist( "DeltaEta"					) );
	// Utilities::OverflowToLast( theAnalysis_->Hist( "Mjj"							) );
	// Utilities::OverflowToLast( theAnalysis_->Hist( "PrunedMass"					) );
	// Utilities::OverflowToLast( theAnalysis_->Hist( "SoftdropMass"				) );
	// Utilities::OverflowToLast( theAnalysis_->Hist( "Tau21"						) );
	Utilities::OverflowToLast( theAnalysis_->Hist( "Tau21_punzi"				) );
	 
	Utilities::OverflowToLast( theAnalysis_->Hist( "VcandPt1"					) );
	Utilities::OverflowToLast( theAnalysis_->Hist( "VcandPt2"					) );
	Utilities::OverflowToLast( theAnalysis_->Hist( "VcandEta1"					) );
	Utilities::OverflowToLast( theAnalysis_->Hist( "VcandEta2"					) );
	Utilities::OverflowToLast( theAnalysis_->Hist( "VcandPhi1"					) );
	Utilities::OverflowToLast( theAnalysis_->Hist( "VcandPhi2"					) );
	Utilities::OverflowToLast( theAnalysis_->Hist( "VcandMass1"					) );
	Utilities::OverflowToLast( theAnalysis_->Hist( "VcandMass2"					) );
	Utilities::OverflowToLast( theAnalysis_->Hist( "VcandTau21"					) );
	

      
}
