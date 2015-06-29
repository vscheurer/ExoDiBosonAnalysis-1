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
  
  theAnalysis_->Book( TH1F( "nConstituents"        , "nConstituents, M_{SD} < 5 GeV"    ,   51,     0. ,  50.   ) );
  theAnalysis_->Book( TH1F( "genWMass"             , "Gen W#rightarrow qq"              ,  200,     0. ,  200.  ) );
  theAnalysis_->Book( TH1F( "genZMass"             , "Gen Z#rightarrow qq"              ,  200,     0. ,  200.  ) );
  theAnalysis_->Book( TH1F( "genHMass"             , "Gen H#rightarrow bb"              ,  200,     0. ,  200.  ) );
  theAnalysis_->Book( TH1F( "recoWPrunedMass"      , "Reco W#rightarrow qq"             ,  200,     0. ,  200.  ) );
  theAnalysis_->Book( TH1F( "recoZPrunedMass"      , "Reco Z#rightarrow qq"             ,  200,     0. ,  200.  ) );
  theAnalysis_->Book( TH1F( "recoHPrunedMass"      , "Reco H#rightarrow bb"             ,  200,     0. ,  200.  ) );
  theAnalysis_->Book( TH1F( "recoWSoftdropMass"    , "Reco W#rightarrow qq"             ,  200,     0. ,  2000. ) );
  theAnalysis_->Book( TH1F( "recoZSoftdropMass"    , "Reco Z#rightarrow qq"             ,  200,     0. ,  200.  ) );
  theAnalysis_->Book( TH1F( "recoHSoftdropMass"    , "Reco H#rightarrow bb"             ,  200,     0. ,  200.  ) );
	
		theAnalysis_->Book( TH1F( "Mjj_all"                                    , "M_{jj}, loose selecion"           , 200	, 0.	, 5000.	) );
		theAnalysis_->Book( TH1F( "Pt"                                         , "jet pt, loose selecion"           , 200	, 0.	, 5000.	) );
		theAnalysis_->Book( TH1F( "Eta"                                        , "#eta, loose selecion"             , 200	, -5.0, 5.0		) );
  	theAnalysis_->Book( TH1F( "PrunedMass_all"                             , "pruned M_{j}, loose selecion"     , 80	, 0.	, 200.	) );
  	theAnalysis_->Book( TH1F( "SoftdropMass_all"                           , "softdrop M_{j}, loose selecion	"	, 80	, 0.	, 200.	) );
    
    theAnalysis_->Book( TH1F( "Softdrop_eta1v2"                           , "softdrop M_{j}, |#eta| < 1.2	"	, 80	, 0.	, 200.	) );
    theAnalysis_->Book( TH1F( "Softdrop_eta1v8"                           , "softdrop M_{j}, 1.2 < |#eta| < 1.8	"	, 80	, 0.	, 200.	) );
    theAnalysis_->Book( TH1F( "Softdrop_eta2v4"                           , "softdrop M_{j}, 1.8 < |#eta| < 2.4	"	, 80	, 0.	, 200.	) );
    
    theAnalysis_->Book( TH2F( "GenVsSoftdrop"     	   								  	, "Gen vs. softdrop mass"		, 200	,  0. , 200., 200	,  0.	, 200.) );
    theAnalysis_->Book( TH2F( "SoftdropvsEta"     	   								  	, "Softdrop mass vs. #eta"		, 200	,  0. , 200., 200	,  -2.5	, 2.5) );
    theAnalysis_->Book( TH2F( "SoftdropvsPt"     	   								  	  , "Softdrop mass vs. p_{T}"		, 200	,  0. , 200., 200	,  0.	, 2000.) );
    

	
	/************************ Dijet analysis histos ************************/
	
	/* AK4 */
	theAnalysis_->Book( TH1F( "nAK4" 	    		  														, "# AK4"	     											, 13	, 0.	, 12.		) );
	theAnalysis_->Book( TH1F( "nbTagAK4" 	    		  												, "# b-tag AK4"	  									, 13	, 0.	, 12.		) );
	theAnalysis_->Book( TH1F( "AK4jetPt" 	    		  												, "Leading AK4 jet pt"	     				, 200	, 0.	, 2000.	) );
	theAnalysis_->Book( TH1F( "AK4jetHT" 	    		  												, "Leading AK4 jet HT"	     				, 200	, 0.	, 2000.	) );
	theAnalysis_->Book( TH1F( "AK4jetPt_PTweight" 	  											, "Leading AK4 jet pt weighted"	    , 200	, 0.	, 2000.	) );
	theAnalysis_->Book( TH1F( "AK4jetHT_HTweight" 	 												, "Leading AK4 jet ht weighted"	    , 200	, 0.	, 2000.	) );
	
  theAnalysis_->Book( TH1F( "tmass" 	    												       	, "Tmass"       , 200	,  0. , 1000.	) );
  theAnalysis_->Book( TH1F( "wmass" 	    												       	, "Wmass"       , 200	,  0. , 1000.	) );
  theAnalysis_->Book( TH1F( "Chi2" 	    												        	, "Chi2"        , 200	,  0. , 50000.	) );
  theAnalysis_->Book( TH2F( "Chi2vsMass" 	    													  , "Chi2vsMass"  , 200	,  0. , 30000.  , 200	,  0. , 1000.	) );
      
      
	theAnalysis_->Book( TH1F( "LeptonicWMass" 	    													, "W transverse mass leptonic"        , 200	,  0. , 200.	) );
	theAnalysis_->Book( TH1F( "LeptonicTopMass" 	    												, "Leptonic top mass"									, 800	,  0. , 800.	) );	
	theAnalysis_->Book( TH1F( "LeptonicbCSV" 	    														, "CSV"										          	, 100	,  0. , 1.		) );
	theAnalysis_->Book( TH1F( "LeptonicbFlavor" 	    												, "Flavor"								          	, 26	,  0. , 25.	) );
  
  theAnalysis_->Book( TH1F( "HadronicWMass" 	    													, "W mass hadronic"                   , 200	,  0. , 200.	) );
  theAnalysis_->Book( TH1F( "HadronicTopMass" 	    												, "Hadronic top mass"									, 800	,  0. , 800.	) );
	theAnalysis_->Book( TH1F( "HadronicbCSV" 	    														, "CSV"										          	, 100	,  0. , 1.		) );
	theAnalysis_->Book( TH1F( "HadronicbFlavor" 	    												, "Flavor"									          , 26	,  0. , 25.	) );
	
  
  theAnalysis_->Book( TH1F( "genJetAK8_mass"   										         , "genJet AK8 mass"	     								    , 80	, 0.	, 200.	) );
  theAnalysis_->Book( TH1F( "genJetAK8_mass_pT200eta2v4"   							   , "genJet AK8 mass, pT>200 and eta<2.4"      , 80	, 0.	, 200.	) );
  
	/* V candidate */
	theAnalysis_->Book( TH1F( "Mjj"   										                		, "M_{jj}, dEta cut "	     								    , 200	, 0.	, 5000.	) );
	theAnalysis_->Book( TH1F( "DeltaEta"	 	    															, "#Delta#eta_{jj}, Mjj cut"	     				  	, 200	, 0.	, 5.0		) );
	theAnalysis_->Book( TH1F( "Tau21"     	   																, "#tau_{21}, dEta+Mjj cut"  	  				      , 100	,  0. , 1.  	) );
	theAnalysis_->Book( TH1F( "Tau21_punzi"     	   													, "#tau_{21}, dEta+Mjj+Mass cut"  	  				, 100	,  0. , 1.  	) );
  theAnalysis_->Book( TH2F( "Tau21vsPt"     	   								  					, "#tau_{21} vs. p_{T}, dEta+Mjj+Mass cut"		, 100	,  0. , 1., 200	,  0.	, 2000.) );
	theAnalysis_->Book( TH1F( "PrunedMass"																		, "pruned M_{j}, dEta+Mjj cut"		            , 80	, 0.	, 200.	) );
	theAnalysis_->Book( TH1F( "SoftdropMass"																	, "softdrop M_{j}, dEta+Mjj cut	"	            , 80	, 0.	, 200.	) );
			
	
	theAnalysis_->Book( TH1F( "VVdeltaEta"		 																, "#Delta#eta_{jj}, all cuts"	   		, 200	, -0.1, 1.4 	) );
	theAnalysis_->Book( TH1F( "VcandPrunedMass" 															, "pruned M_{j}, all cuts applied"		, 80	, 0.	, 200.	) );
	theAnalysis_->Book( TH1F( "VcandSoftdropMass" 														, "Softdrop M_{j}, all cuts applied"	, 80	, 0.	, 200.	) ); 	
	theAnalysis_->Book( TH1F( "VcandTau21"     	    													, "Jet #tau_{21}, all cuts applied"		, 100	,  0. , 1.		) );
	theAnalysis_->Book( TH1F( "DiBosonInvMass"	      												, "di-bosons inv. mass"						, 5000, 0.	, 5000.	) );
	theAnalysis_->Book( TH1F( "VcandPt1" 	    																, "Leading AK8 jet pt"						, 200	,  0.	, 2000.	) );
	theAnalysis_->Book( TH1F( "VcandPt2"  	    															, "Second AK8 jet pt"						, 200	,  0.	, 2000.	) );
	theAnalysis_->Book( TH1F( "VcandEta1"	    																, "Leading AK8 jet eta"						, 50	, -2.5, 2.5		) );
	theAnalysis_->Book( TH1F( "VcandEta2" 	   																, "Second AK8 jet eta"						, 50	, -2.5, 2.5		) );
	theAnalysis_->Book( TH1F( "VcandPhi1"	    																, "Leading AK8 jet phi"						, 64	, -3.2, 3.2		) );
	theAnalysis_->Book( TH1F( "VcandPhi2" 	    															, "Second AK8 jet phi"						, 64	, -3.2, 3.2		) );
	theAnalysis_->Book( TH1F( "VcandMass1" 	    															, "Leading AK8 jet mass"					, 80	,  0. , 200.	) );
	theAnalysis_->Book( TH1F( "VcandMass2" 	    															, "Second AK8 jet mass"	     				, 80	,  0. , 200.	) );
	
	/* Cut flow */
	theAnalysis_->Book( TH1F( "nEvents"                													, "nEvents"									  	, 1	, 0.5, 1.5		) );
	theAnalysis_->Book( TH1F( "nPassedTrigger"         													, "nPassedTrigger"							, 1	, 0.5, 1.5		) );
	theAnalysis_->Book( TH1F( "nPassedFoundJets"       													, "nPassedFoundJets"						, 1	, 0.5, 1.5		) );
	theAnalysis_->Book( TH1F( "nPassedJetsDEta"        													, "nPassedJetsDEta"							, 1	, 0.5, 1.5		) );
	theAnalysis_->Book( TH1F( "nPassedMjj"             													, "nPassedMjj"									, 1	, 0.5, 1.5		) );
	theAnalysis_->Book( TH1F( "nPassedTrigger"         													, "nPassedTrigger"							, 1	, 0.5, 1.5		) );
	theAnalysis_->Book( TH1F( "nPassedPrunedJetMass"   													, "nPassedPrunedJetMass"				, 1	, 0.5, 1.5		) );
	theAnalysis_->Book( TH1F( "nPassedTau21Cut"        													, "nPassedTau21Cut"							, 1	, 0.5, 1.5		) );
   
	/* Triggers */
	theAnalysis_->Book( TH1F( "TriggerEffDen"                     , "M(jj)"                     , 5000, 0.	, 5000.	) );  
	theAnalysis_->Book( TH1F( "TriggerEffPrunedMassDen"           , "Pruned M_{j}"              , 200	, 0. ,  200.  ) );
	theAnalysis_->Book( TH1F( "TriggerEffSoftdropMassDen"         , "Softdrop M_{j}"            , 200	, 0. ,  200.  ) );
	theAnalysis_->Book( TH1F( "TriggerEffPrunedMassDen_PtCut"     , "Pruned M_{j}"              , 200	, 0. ,  200.  ) );
	theAnalysis_->Book( TH1F( "TriggerEffSoftdropMassDen_PtCut"   , "Softdrop M_{j}"	        	, 200	, 0. ,  200.  ) );
	theAnalysis_->Book( TH1F( "TriggerEffPruningCut"              , "M(jj)"	      		 					, 5000, 0. , 5000.  ) );
	theAnalysis_->Book( TH1F( "TriggerEffPruningCut_qstar"        , "M(jj)"	      							, 5000, 0. , 5000.  ) );	 
	theAnalysis_->Book( TH1F( "TriggerEffSoftdropCut"             , "M(jj)"	      		 					, 5000, 0. , 5000.  ) );
	theAnalysis_->Book( TH1F( "TriggerEffSoftdropCut_qstar"       , "M(jj)"	      							, 5000, 0. , 5000.  ) );
	theAnalysis_->Book( TH1F( "TriggerEffTau21Cut"                , "M(jj)"	      		 					, 5000, 0. , 5000.  ) );
	theAnalysis_->Book( TH1F( "TriggerEffTau21Cut_qstar"          , "M(jj)"	      		 					, 5000, 0. , 5000.  ) );
	
	
	theAnalysis_->Book( TH1F( "TriggerEff_HLT_AK8PFJet360_TrimMass30"																								, "HLT_AK8PFJet360_TrimMass30_v1"	, 5000, 0. , 5000.  ) );
	theAnalysis_->Book( TH1F( "TriggerEff_HLT_AK8PFJet360_TrimMass30_wPruningCut"																		, "HLT_AK8PFJet360_TrimMass30_v1"	, 5000, 0. , 5000.  ) );
	theAnalysis_->Book( TH1F( "TriggerEff_HLT_AK8PFJet360_TrimMass30_wSoftdropCut"																	, "HLT_AK8PFJet360_TrimMass30_v1"   , 5000, 0. , 5000.  ) );
	theAnalysis_->Book( TH1F( "TriggerEff_HLT_AK8PFJet360_TrimMass30_wPruningCut_qstar"															, "HLT_AK8PFJet360_TrimMass30_v1"   , 5000, 0. , 5000.  ) );
	theAnalysis_->Book( TH1F( "TriggerEff_HLT_AK8PFJet360_TrimMass30_wSoftdropCut_qstar"														, "HLT_AK8PFJet360_TrimMass30_v1"   , 5000, 0. , 5000.  ) );
	theAnalysis_->Book( TH1F( "TriggerEff_HLT_AK8PFJet360_TrimMass30_wTau21Cut"																			, "HLT_AK8PFJet360_TrimMass30_v1"	, 5000, 0. , 5000.  ) );
	
	theAnalysis_->Book( TH1F( "TriggerEff_HLT_AK8PFHT700_TrimR0p1PT0p03Mass50"																    	, "HLT_AK8PFHT700_TrimR0p1PT0p03Mass50_Mass30_v1"	, 5000, 0. , 5000.  ) );
	theAnalysis_->Book( TH1F( "TriggerEff_HLT_AK8PFHT700_TrimR0p1PT0p03Mass50_wPruningCut"										    	, "HLT_AK8PFHT700_TrimR0p1PT0p03Mass50_Mass30_v1"	, 5000, 0. , 5000.  ) );
	theAnalysis_->Book( TH1F( "TriggerEff_HLT_AK8PFHT700_TrimR0p1PT0p03Mass50_wSoftdropCut"										    	, "HLT_AK8PFHT700_TrimR0p1PT0p03Mass50_Mass30_v1"   , 5000, 0. , 5000.  ) );
	theAnalysis_->Book( TH1F( "TriggerEff_HLT_AK8PFHT700_TrimR0p1PT0p03Mass50_wPruningCut_qstar"						    		, "HLT_AK8PFHT700_TrimR0p1PT0p03Mass50_Mass30_v1"   , 5000, 0. , 5000.  ) );
	theAnalysis_->Book( TH1F( "TriggerEff_HLT_AK8PFHT700_TrimR0p1PT0p03Mass50_wSoftdropCut_qstar"						    		, "HLT_AK8PFHT700_TrimR0p1PT0p03Mass50_Mass30_v1"   , 5000, 0. , 5000.  ) );
	theAnalysis_->Book( TH1F( "TriggerEff_HLT_AK8PFHT700_TrimR0p1PT0p03Mass50_wTau21Cut"										    		, "HLT_AK8PFHT700_TrimR0p1PT0p03Mass50_Mass30_v1"		, 5000, 0. , 5000.  ) );
	
	theAnalysis_->Book( TH1F( "TriggerEff_HLT_AK8DiPFJet280_200_TrimMass30_BTagCSV0p41"															, "HLT_AK8DiPFJet280_200_TrimMass30_BTagCSV0p41_Mass30_v1"	, 5000, 0. , 5000.  ) );
	theAnalysis_->Book( TH1F( "TriggerEff_HLT_AK8DiPFJet280_200_TrimMass30_BTagCSV0p41_wPruningCut"									, "HLT_AK8DiPFJet280_200_TrimMass30_BTagCSV0p41_Mass30_v1"	, 5000, 0. , 5000.  ) );
	theAnalysis_->Book( TH1F( "TriggerEff_HLT_AK8DiPFJet280_200_TrimMass30_BTagCSV0p41_wSoftdropCut"								, "HLT_AK8DiPFJet280_200_TrimMass30_BTagCSV0p41_Mass30_v1"   , 5000, 0. , 5000.  ) );
	theAnalysis_->Book( TH1F( "TriggerEff_HLT_AK8DiPFJet280_200_TrimMass30_BTagCSV0p41_wPruningCut_qstar"						, "HLT_AK8DiPFJet280_200_TrimMass30_BTagCSV0p41_Mass30_v1"   , 5000, 0. , 5000.  ) );
	theAnalysis_->Book( TH1F( "TriggerEff_HLT_AK8DiPFJet280_200_TrimMass30_BTagCSV0p41_wSoftdropCut_qstar"					, "HLT_AK8DiPFJet280_200_TrimMass30_BTagCSV0p41_Mass30_v1"   , 5000, 0. , 5000.  ) );
	theAnalysis_->Book( TH1F( "TriggerEff_HLT_AK8DiPFJet280_200_TrimMass30_BTagCSV0p41_wTau21Cut"							  		, "HLT_AK8DiPFJet280_200_TrimMass30_BTagCSV0p41_Mass30_v1"		, 5000, 0. , 5000.  ) );
	
	theAnalysis_->Book( TH1F( "TriggerEff_HLT_PFHT900"														, "HLT_PFHT900_v1"	    					, 5000, 0. , 5000.  ) );
	theAnalysis_->Book( TH1F( "TriggerEff_HLT_PFHT900_wPruningCut"								, "HLT_PFHT900_v1"	    					, 5000, 0. , 5000.  ) );
	theAnalysis_->Book( TH1F( "TriggerEff_HLT_PFHT900_wPruningCut_qstar"					, "HLT_PFHT900_v1"	        			, 5000, 0. , 5000.  ) );
	theAnalysis_->Book( TH1F( "TriggerEff_HLT_PFHT900_wSoftdropCut"								, "HLT_PFHT900_v1"	    					, 5000, 0. , 5000.  ) );
	theAnalysis_->Book( TH1F( "TriggerEff_HLT_PFHT900_wTau21Cut"									, "HLT_PFHT900_v1"	    					, 5000, 0. , 5000.  ) );	
	
	theAnalysis_->Book( TH1F( "TriggerEff_HLT_PFHT600"														, "HLT_PFHT600_v1"	    					, 5000, 0. , 5000.  ) );
	theAnalysis_->Book( TH1F( "TriggerEff_HLT_PFHT600_wPruningCut"								, "HLT_PFHT600_v1"	    					, 5000, 0. , 5000.  ) );
	theAnalysis_->Book( TH1F( "TriggerEff_HLT_PFHT600_wPruningCut_qstar"					, "HLT_PFHT600_v1"	        			, 5000, 0. , 5000.  ) );
	theAnalysis_->Book( TH1F( "TriggerEff_HLT_PFHT600_wSoftdropCut"								, "HLT_PFHT600_v1"	    					, 5000, 0. , 5000.  ) );
	theAnalysis_->Book( TH1F( "TriggerEff_HLT_PFHT600_wTau21Cut"									, "HLT_PFHT600_v1"	    					, 5000, 0. , 5000.  ) );	
  
	theAnalysis_->Book( TH1F( "TriggerEff_HLT_PFHT650"														, "HLT_PFHT650_v1"	    					, 5000, 0. , 5000.  ) );
	theAnalysis_->Book( TH1F( "TriggerEff_HLT_PFHT650_wPruningCut"								, "HLT_PFHT650_v1"	    					, 5000, 0. , 5000.  ) );
	theAnalysis_->Book( TH1F( "TriggerEff_HLT_PFHT650_wPruningCut_qstar"					, "HLT_PFHT650_v1"	        			, 5000, 0. , 5000.  ) );
	theAnalysis_->Book( TH1F( "TriggerEff_HLT_PFHT650_wSoftdropCut"								, "HLT_PFHT650_v1"	    					, 5000, 0. , 5000.  ) );
	theAnalysis_->Book( TH1F( "TriggerEff_HLT_PFHT650_wTau21Cut"									, "HLT_PFHT650_v1"	    					, 5000, 0. , 5000.  ) );	
  
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
	
	
}

////////////////////////////////////////////////////////////////////
void HistosManager::formatHistos( void ){
  
	theAnalysis_->Hist( "LeptonicWMass"       )->GetXaxis()->SetTitle( "M [GeV]");
	theAnalysis_->Hist( "HadronicWMass" 	    )->GetXaxis()->SetTitle( "M [GeV]");
	theAnalysis_->Hist( "HadronicTopMass"     )->GetXaxis()->SetTitle( "M [GeV]");
	theAnalysis_->Hist( "LeptonicTopMass"     )->GetXaxis()->SetTitle( "M [GeV]");
	
	theAnalysis_->Hist( "AK4jetHT"					  )->GetXaxis()->SetTitle( "H_{T} [GeV]"           	  );
	theAnalysis_->Hist( "AK4jetPt"					  )->GetXaxis()->SetTitle( "p_{T} [GeV]"           	  );
	theAnalysis_->Hist( "AK4jetHT_HTweight"   )->GetXaxis()->SetTitle( "H_{T} [GeV]"           	  );
	theAnalysis_->Hist( "AK4jetPt_PTweight"   )->GetXaxis()->SetTitle( "p_{T} [GeV]"           	  );
	
	theAnalysis_->Hist( "DiBosonInvMass"			)->GetXaxis()->SetTitle( "M_{G} [GeV]"              );
	theAnalysis_->Hist( "VVdeltaEta"					)->GetXaxis()->SetTitle( "#Delta#eta_{jj}"          );
	theAnalysis_->Hist( "DeltaEta"            )->GetXaxis()->SetTitle( "#Delta#eta_{jj}"          );
	theAnalysis_->Hist( "Mjj"                 )->GetXaxis()->SetTitle( "M_{jj} [GeV]"             );
	theAnalysis_->Hist( "Tau21"					    	)->GetXaxis()->SetTitle( "#tau_{21}"			    		  );
	theAnalysis_->Hist( "Tau21_punzi"		  		)->GetXaxis()->SetTitle( "#tau_{21}"			    	  	);
	theAnalysis_->Hist( "PrunedMass"					)->GetXaxis()->SetTitle( "M_{j} [GeV]"           	  );
	theAnalysis_->Hist( "SoftdropMass"				)->GetXaxis()->SetTitle( "M_{j} [GeV]"           	  );
	theAnalysis_->Hist( "VcandPrunedMass"			)->GetXaxis()->SetTitle( "M_{j} [GeV]"           	  );
	theAnalysis_->Hist( "VcandSoftdropMass"		)->GetXaxis()->SetTitle( "M_{j} [GeV]"           	  );
	
	theAnalysis_->Hist( "VcandPt1"					)->GetXaxis()->SetTitle( "W_{hadr} p_{T} [GeV]"       );
	theAnalysis_->Hist( "VcandPt2"					)->GetXaxis()->SetTitle( "W_{hadr} p_{T} [GeV]"       );
	theAnalysis_->Hist( "VcandEta1"					)->GetXaxis()->SetTitle( "W_{hadr} #eta"              );
	theAnalysis_->Hist( "VcandEta2"					)->GetXaxis()->SetTitle( "W_{hadr} #eta"              );
	theAnalysis_->Hist( "VcandPhi1"					)->GetXaxis()->SetTitle( "W_{hadr} #phi [rad]"        );
	theAnalysis_->Hist( "VcandPhi2"					)->GetXaxis()->SetTitle( "W_{hadr} #phi [rad]"        );
	theAnalysis_->Hist( "VcandMass1"				)->GetXaxis()->SetTitle( "W_{hadr} mass [GeV]"        );
	theAnalysis_->Hist( "VcandMass2"				)->GetXaxis()->SetTitle( "W_{hadr} mass [GeV]"        );
	theAnalysis_->Hist( "VcandTau21"				)->GetXaxis()->SetTitle( "#tau_{21}"                  );
	
	
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
