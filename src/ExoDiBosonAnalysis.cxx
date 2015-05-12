#include "../ExoDiBosonAnalysis/include/ExoDiBosonAnalysis.h"
#include "../ExoDiBosonAnalysis/include/Utilities.h"
#include "../ExoDiBosonAnalysis/include/HistosManager.h"
#include "../ExoDiBosonAnalysis/include/NtupleManager.h"
#include "../ExoDiBosonAnalysis/include/MatchingTools.h"

#include <iostream>


//==============================================================================================
ClassImp( ExoDiBosonAnalysis );

//==============================================================================================
ExoDiBosonAnalysis::ExoDiBosonAnalysis()
	: SCycleBase()
, weight_		(1.)
, lheweight_	(1.)
, puweight_		(1.)
, hltweight_	(1.)
, btagweight_	(1.)
, lumiweight_	(1.){

	SetLogName( GetName() );
   
	/* general settings */   
	DeclareProperty( "InputTreeName"		, InputTreeName_		);
	DeclareProperty( "OutputTreeName"		, OutputTreeName_		);
	DeclareProperty( "isSignal"         , isSignal_				);
	DeclareProperty( "runOnMC"          , runOnMC_				);
	DeclareProperty( "GenFilter"        , genFilter_			);
	DeclareProperty( "Flavour"          , Flavour_				);
	DeclareProperty( "Channel"          , Channel_				);
	DeclareProperty( "Trigger"          , Trigger_				);
	DeclareProperty( "Synch"            , Synch_					);
	 
	/* leptonic selections */
	DeclareProperty( "LeptPtCut"			, leptPtCut_			);
	DeclareProperty( "LeptEtaCut"			, leptEtaCut_			);
	DeclareProperty( "AleptPtCut"			, AleptPtCut_			);
	DeclareProperty( "AleptEtaCut"		, AleptEtaCut_		);
	DeclareProperty( "METCut"					, METCut_					);
	DeclareProperty( "WptCut"					, WptCut_					);

	/* jet selections */
	DeclareProperty( "MjjCut"						, MjjCut_					);
	DeclareProperty( "JetPtCutLoose"		, JetPtCutLoose_	);
	DeclareProperty( "JetPtCutTight"		, JetPtCutTight_	);
	DeclareProperty( "JetEtaCut"        , JetEtaCut_			);  
	DeclareProperty( "Tau21Cut"         , Tau21Cut_				);  
	DeclareProperty( "Tau21HPLow"       , Tau21HPLow_			);
	DeclareProperty( "Tau21HPHigh"			, Tau21HPHigh_		);
	DeclareProperty( "Tau21Low"       	, Tau21Low_			);
	DeclareProperty( "Tau21High"     	 , Tau21High_		);
	       
	/* btag veto */
	DeclareProperty( "nAJetCut"         , nAJetCut_				);
	DeclareProperty( "BtagVetoWP"       , BtagVetoWP_			);
   
	/* top mass veto */
	DeclareProperty( "TopMassCut"       , TopMassCut_			);
	DeclareProperty( "leptTopMassLow"   , leptTopMassLow_    );
	DeclareProperty( "leptTopMassHigh"  , leptTopMassHigh_   );
	DeclareProperty( "hadrTopMassLow"   , hadrTopMassLow_    );
	DeclareProperty( "hadrTopMassHigh"  , hadrTopMassHigh_   );
   
	/* pruned mass */ 
	DeclareProperty( "UsePruned"        , UsePruned_			);
	DeclareProperty( "UseSD"            , UseSD_					); 
	DeclareProperty( "VetoSR"						, VetoSR_			);
	DeclareProperty( "mPMLow"						, mPMLow_			);
	DeclareProperty( "mPMHigh"					, mPMHigh_		);
	DeclareProperty( "mSDLow"						, mSDLow_			);
	DeclareProperty( "mSDHigh"					, mSDHigh_		);
	
	/* WH mass window */
	DeclareProperty( "WHMass"						, WHMass_			);
	
	/* weights settings */
	DeclareProperty( "LHEsample"				, LHEsample_		);
	DeclareProperty( "xSec"							, xSec_					);
	DeclareProperty( "genEvents"				, genEvents_		);
	DeclareProperty( "Lumi"							, Lumi_					);
	DeclareProperty( "PUdata"						, PUProfileData_    	  );
	DeclareProperty( "BTagEff4vetoData"		, BTagEff4vetoData_   );
	DeclareProperty( "BTagEff4fatjetData"	, BTagEff4fatjetData_ );
	DeclareProperty( "BTagEff4subjetData"	, BTagEff4subjetData_ );
      
	/* systematics */
	DeclareProperty( "BtagSFSysUpVeto"  , BtagSFSysUpVeto_   );
	DeclareProperty( "BtagSFSysDownVeto", BtagSFSysDownVeto_ );
	DeclareProperty( "ScaleMuonUpDown"  , ScaleMuonUpDown_   );
	DeclareProperty( "ScalePrunedMass"  , ScalePrunedMass_   );
            
	theHistosManager_ = new HistosManager( this );
	theNtupleManager_ = new NtupleManager( this );
   
	bTagWPmap_["CSVL"] = 0.244;
	bTagWPmap_["CSVM"] = 0.679;
	bTagWPmap_["CSVT"] = 0.898;  
	
	pdgMtop = 173.34;
	pdgMw		= 80.385;   
	pdgWidthtop = 1.29;
	pdgWidthw		= 2.085;
   
	jetIndex_						= 0;
   
	nEvents_							= 0;
	nPassedTrigger_				= 0;	      
	nPassedJetPrunedMass_		= 0;
	nPassedTau21Cut_				= 0;  
	nPassedExoCandidateMass_	= 0;
	nPassedWTag_	= 0;
   
	Mjj								= 0;
	jetsDeltaEta					= 0;
	nBTags							= 0;
   
	nPassedFoundJets_				= 0;
	nPassedJetsDEta_				= 0;
	nPassedMjj_						= 0;
	nPassedWtagging_				= 0;
	nPassedFoundLept_				= 0;
	
	nPassedIsoLep_					= 0;
	nPassedVetoLep_				= 0;
	nPassed1Jet_					= 0;
	nPassed2Jet_					= 0;
	nPassed3Jet_					= 0;
	nPassed4Jet_					= 0;
	nPassed1bTag_					= 0;
	nPassed2bTag_					= 0;
   
}

//==============================================================================================
ExoDiBosonAnalysis::~ExoDiBosonAnalysis() {
	
	if( theHistosManager_ ){
		delete theHistosManager_;
		theHistosManager_ = 0;
	}
   
	if( theNtupleManager_ ){
		delete theNtupleManager_;
		theNtupleManager_ = 0;
	}
}

//==============================================================================================
void ExoDiBosonAnalysis::BeginCycle() throw( SError ) {

	initWeight();    
                     
	return;

}
//==============================================================================================
void ExoDiBosonAnalysis::initWeight( void ){

	PUWeight::Scenario sc = PUWeight_.toScenario("PUS10");
	PUWeight_.initPUWeights(PUProfileData_,sc); 

	LHEWeight::Sample sm = LHEWeight_.toSample(LHEsample_);
	LHEWeight_.initLHEWeights(sm);

	HLTWeight::Channel ch = HLTWeight_.toChannel(Channel_);
	HLTWeight_.initHLTWeights(ch);
   
	BTagWeight_.initBTagWeights(BTagEff4vetoData_,BTagEff4fatjetData_,BTagEff4subjetData_);
   
}

//==============================================================================================
void ExoDiBosonAnalysis::BeginInputFile( const SInputData& ) throw( SError ) {

	theNtupleManager_->ConnectVariables( InputTreeName_ );
         
	return;
}

//==============================================================================================
void ExoDiBosonAnalysis::BeginInputData( const SInputData& ) throw( SError ) {
	
	if( Synch_ ){  

		Book( TH1F( "Event", "event", 30000, 0, 30000));
   
		/* for synch */
		DeclareVariable( run						, "run"					, OutputTreeName_.c_str() );
		DeclareVariable( event					, "event"				, OutputTreeName_.c_str() );
		DeclareVariable( lumi						, "lumi"					, OutputTreeName_.c_str() );
		DeclareVariable( nPV						, "nPV"					, OutputTreeName_.c_str() );
		DeclareVariable( pfMET					, "pfMET"				, OutputTreeName_.c_str() );
		DeclareVariable( pfMETPhi				, "pfMETPhi"			, OutputTreeName_.c_str() );
		DeclareVariable( nLooseEle			, "nLooseEle"			, OutputTreeName_.c_str() );
		DeclareVariable( nLooseMu				, "nLooseMu"			, OutputTreeName_.c_str() );
		DeclareVariable( l_pt						, "l_pt"					, OutputTreeName_.c_str() );
		DeclareVariable( l_eta					, "l_eta"				, OutputTreeName_.c_str() );
		DeclareVariable( l_phi					, "l_phi"				, OutputTreeName_.c_str() );
		DeclareVariable( jet_pt					, "jet_pt"				, OutputTreeName_.c_str() );
		DeclareVariable( jet_eta				, "jet_eta"				, OutputTreeName_.c_str() );
		DeclareVariable( jet_phi				, "jet_phi"				, OutputTreeName_.c_str() );
		DeclareVariable( jet_mass_pruned		, "jet_mass_pruned"	, OutputTreeName_.c_str() );
		DeclareVariable( jet_mass_softdrop	, "jet_mass_softdrop", OutputTreeName_.c_str() );
		DeclareVariable( jet_tau2tau1			, "jet_tau2tau1"		, OutputTreeName_.c_str() );
		DeclareVariable( W_pt						, "W_pt"					, OutputTreeName_.c_str() );
		DeclareVariable( W_eta					, "W_eta"				, OutputTreeName_.c_str() );
		DeclareVariable( W_phi					, "W_phi"				, OutputTreeName_.c_str() );
		DeclareVariable( m_lvj					, "m_lvj"				, OutputTreeName_.c_str() );
		DeclareVariable( njets					, "njets"				, OutputTreeName_.c_str() );
		DeclareVariable( nbtag					, "nbtag"				, OutputTreeName_.c_str() );
		DeclareVariable( jet2_pt				, "jet2_pt"				, OutputTreeName_.c_str() );
		DeclareVariable( jet2_btag			, "jet2_btag"			, OutputTreeName_.c_str() );
		DeclareVariable( jet3_pt				, "jet3_pt"				, OutputTreeName_.c_str() );
		DeclareVariable( jet3_btag			, "jet3_btag"			, OutputTreeName_.c_str() );
	}
	else{
      
		theHistosManager_->bookHistos(); 

		DeclareVariable( MVV						, "MVV"					, OutputTreeName_.c_str() );
		DeclareVariable( Mj							, "Mj"					, OutputTreeName_.c_str() );
		// DeclareVariable( weight_     , "weight"    , OutputTreeName_.c_str() );
		// DeclareVariable( puweight_   , "puweight"  , OutputTreeName_.c_str() );
		// DeclareVariable( hltweight_  , "hltweight" , OutputTreeName_.c_str() );
		// DeclareVariable( lumiweight_ , "lumiweight", OutputTreeName_.c_str() );
		// DeclareVariable( btagweight_ , "btagweight", OutputTreeName_.c_str() );
		// DeclareVariable( channel     , "channel"   , OutputTreeName_.c_str() );
	}
     
	return;

}

//==============================================================================================
void ExoDiBosonAnalysis::initData( void ){

	data_ = theNtupleManager_->getData();
      
}

//==============================================================================================
void ExoDiBosonAnalysis::reset( void ){

	genCandidates_	.clear();
	leptonCand_			.clear();
	AK4jetCand_			.clear();
	AK4bjetCand_		.clear();
	Vcand						.clear();
	METCand_				.clear();
	WCand_					.clear();
	
	Leptonicb_			.clear();
	Hadronicb_			.clear();
	HadronicJ_			.clear();
   
}

//==============================================================================================
void ExoDiBosonAnalysis::setGenCandidates( void ) {

	if( !runOnMC_ ) return;
	if( !isSignal_ && !genFilter_ ) return;

	TLorentzVector genP;   
	double genptV = -99;
	for( unsigned int p = 0; p < (data_.genParticle_pdgId)->size(); ++p ){
		if( (*data_.genParticle_status)[p] != 4 && (*data_.genParticle_status)[p] != 22 && (*data_.genParticle_status)[p] != 23 ) continue;
		genP.SetPtEtaPhiE( (*data_.genParticle_pt)[p], (*data_.genParticle_eta)[p], (*data_.genParticle_phi)[p], (*data_.genParticle_e)[p] );
		genCandidates_[(*data_.genParticle_pdgId)[p]] = genP;   
	}
                    
	return;
}
//==============================================================================================
bool ExoDiBosonAnalysis::selectChannel( void ){

	if( !runOnMC_ ) return true;
	if( !genFilter_ ) return true;  
	     
	bool foundMu  = false;
	bool foundEle = false;
	bool foundTau = false;
	int  nMus = 0;
	int  nEles = 0;
	int  nTaus = 0;
	for( unsigned int p = 0; p < (data_.genParticle_pdgId)->size(); ++p ){
    
		if( (*data_.genParticle_status)[p] != 4 && (*data_.genParticle_status)[p] != 22 && (*data_.genParticle_status)[p] != 23 ) continue;
       
		if( abs((*data_.genParticle_pdgId)[p]) == 13 ){
			for( unsigned int m = 0; m < (*data_.genParticle_mother)[p].size(); ++m ){
				if( abs((*data_.genParticle_mother)[p][m]) == 24 || abs((*data_.genParticle_mother)[p][m]) == 23 ){
					foundMu = true;
					nMus++;
					break;
				}  				     
			}
		}
		if( abs((*data_.genParticle_pdgId)[p]) == 11 ){
			for( unsigned int m = 0; m < (*data_.genParticle_mother)[p].size(); ++m ){
				if( abs((*data_.genParticle_mother)[p][m]) == 24 || abs((*data_.genParticle_mother)[p][m]) == 23 ){
					foundEle = true;
					nEles++;
					break;
				}  				     
			}
		}
		if( abs((*data_.genParticle_pdgId)[p]) == 15 ){
			for( unsigned int m = 0; m < (*data_.genParticle_mother)[p].size(); ++m ){
				if( abs((*data_.genParticle_mother)[p][m]) == 24 || abs((*data_.genParticle_mother)[p][m]) == 23 ){
					foundTau = true;
					nTaus++;
					break;
				}  				     
			}
		}       																														  
	} 
   
	if( Channel_ == "muon" && (!foundMu || nMus > 1) ) return false;     

	if( Channel_ == "electron" && (!foundEle || nEles > 1) ) return false;

	if( Channel_ == "tau" && (!foundTau || nTaus > 1) ) return false;
            
	return true;   
   
}

//==============================================================================================
void ExoDiBosonAnalysis::setWeight( TString infile ){

	if( !runOnMC_ ) return;

	//for( unsigned int v = 0; v < (data_.nPUTrue)->size(); ++v ){
	//   if( (*data_.bX)[v] == 0 ) puweight_ = PUWeight_.getPUWeight( (*data_.nPUTrue)[v] );
	//}
      
	//hltweight_ = HLTWeight_.getHLTWeight( leptonCand_[0].p4.Pt(), leptonCand_[0].p4.Eta() );
   
	// lheweight_ = LHEWeight_.getLHEWeight(data_.lheV_pt);
      
	double lumiw = xSec_/genEvents_;
      
	lumiweight_ = lumiw*LumiWeight_.getLumiWeight( infile );
 
	btagvetow = 1.; 
	htagw = 1.;
   
	//if( BtagSFSysUpVeto_ ) btagvetow = BTagWeight_.getBTagSFWeightUp( AK4jetCand_, "veto" ); 
	//else if( BtagSFSysDownVeto_ ) btagvetow = BTagWeight_.getBTagSFWeightDown( AK4jetCand_, "veto" ); 
	//else btagvetow = BTagWeight_.getBTagWeight( AK4jetCand_, "veto" ); 
      
	if( nAJetCut_ == -1 ) btagvetow = 1.;

	// btagweight_ =  btagvetow*htagw;
      
	weight_ = puweight_*lheweight_*lumiweight_*hltweight_*btagweight_;
}

//==============================================================================================
void ExoDiBosonAnalysis::ExecuteEvent( const SInputData&, Double_t ) throw( SError ) {
	
	//Connect branches in tree
	initData();
	
	//Reset vectors
	reset();
	
	// Semileptonic analysis begins HERE
	if( Channel_ == "electron" || Channel_ == "muon"  ){
		setGenCandidates(); 
            	
		if( !selectChannel() ) throw SError( SError::SkipEvent );
		nEvents_++;
   
		if( !passedTrigger() ) throw SError( SError::SkipEvent );  
		nPassedTrigger_++;

		bool DEBUGgen = false;
		
		if( DEBUGgen ){
			std::cout << "====================================" << std::endl;
			for( unsigned int p = 0; p < (data_.genParticle_pdgId)->size(); ++p ){
				if( (*data_.genParticle_status)[p] != 4 && (*data_.genParticle_status)[p] != 22 && (*data_.genParticle_status)[p] != 23 ) continue;
				std::cout << " gen particle: " << (*data_.genParticle_pdgId)[p] << " status " << (*data_.genParticle_status)[p] << std::endl;
				std::cout << "    - mothers: ";
				for( unsigned int m = 0; m < (*data_.genParticle_mother)[p].size(); ++m ) std::cout << (*data_.genParticle_mother)[p][m] << ",";
				std::cout << std::endl;
				std::cout << "    - daughters: ";
				for( unsigned int d = 0; d < (*data_.genParticle_dau)[p].size(); ++d ) std::cout << (*data_.genParticle_dau)[p][d] << ",";     
				std::cout << std::endl;
			}
		}
		//doLeptonRecoEfficiency(); 
		if( /*data_.EVENT_event == 3 &&*/ Synch_ && run4Synch() ){ Hist( "Event" )->Fill(data_.EVENT_event); }
		else
		if( !Synch_ && passedSelections() ){
			
			TString infile = TString(this->GetHistInputFile()->GetName());
			// setWeight(infile);
			// fillHistos();
			Mj = Vcand[0].prunedMass;
			if( Channel_ == "muon" ) channel = 1;
			else if( Channel_ == "electron" ) channel = 0;
			else channel = 2;
		}
	}
	
	// Dijet analysis begins HERE
	else
	if( Channel_ == "VVdijet" || Channel_ == "qVdijet" ){
		
		nEvents_++;
		// if( !passedTrigger() ) throw SError( SError::SkipEvent );
		nPassedTrigger_++;  
		
		//Set weights xSec/genEvents
		TString infile = TString(this->GetHistInputFile()->GetName());
		setWeight(infile);
		
		
		// //Check QCD HT sample overlap regions
		// float ptJet	= -9999	;
		// float HT		= 0.		;
		//
		// for( int j = 0; j < data_.njetsAK4; ++j ){
		// 	HT += (*data_.jetAK4_pt)[j];
		// 	if( (*data_.jetAK4_pt)[j] > ptJet )	ptJet = (*data_.jetAK4_pt)[j];
		// }
		// Hist( "AK4jetHT")->Fill( HT, weight_ );
		// Hist( "AK4jetPt")->Fill( ptJet, weight_ );
		// Hist( "AK4jetHT_HTweight")->Fill( HT, HT );
		// Hist( "AK4jetPt_PTweight")->Fill( ptJet, ptJet);
		
		//Get diboson invariant mass
		if( passedDijetSelections() ){
			
			//Fill all histograms after full selection
			fillHistos();	
			// MVV = (Vcand[0].p4 + Vcand[1].p4).M()	;
			// Mj1 = Vcand[0].prunedMass					;
			// Mj2 = Vcand[1].prunedMass					;
		}
	}
	
	else if( Channel_ == "SFeleJets" ){
		nEvents_++;		
		if( passedTTbarSelections() ){
			fillSFHistos();
		}
		
	}
	else if( Channel_ == "SFmuJets"){
		nEvents_++;		
		if( passedTTbarSelections() ){
			setGenCandidates(); 
			findMETCandidate					();
			findWCandidate						();
			
			TLorentzVector p4nu					= getp4Nu();		
			TLorentzVector p4nuMethod2	= getp4NuMethod2();	
			Double_t deltaRmin = 99.;
			Double_t deltaTmassMin = 999.;
			float chi2Min = 999999.;
			
			for(int i=0; i < 4; i++ ){
				Hadronicb_.push_back(AK4jetCand_[i]);
				for(int j=0; j < 4; j++ ){
					for(int k=0; k < 4; k++ ){
						Hadronicb_.push_back(AK4jetCand_[k]);
						if( i==j || i==k || j==k) continue;
						float deltaTmass = ((AK4bjetCand_[i].p4 + AK4bjetCand_[j].p4 + AK4bjetCand_[k].p4).M())-pdgMtop;
						float deltaWmass = ((AK4bjetCand_[i].p4 + AK4bjetCand_[j].p4).M())-pdgMw;
						float chi2 = pow((deltaTmass/pdgWidthtop),2)+pow((deltaWmass/pdgWidthw),2);
						if(chi2 < chi2Min ){
							chi2Min = chi2;
							Hadronicb_[0]=AK4bjetCand_[i];
							Hadronicb_[1]=AK4bjetCand_[j];
							Hadronicb_[2]=AK4bjetCand_[k];
						}
					}
				}
			}
			if( chi2Min > 200. ) throw SError( SError::SkipEvent );
			
			
			for(int i=0; i < 4; i++ ){
				if (AK4jetCand_[i].p4.Pt() == Hadronicb_[0].p4.Pt() || AK4jetCand_[i].p4.Pt() == Hadronicb_[1].p4.Pt()  || AK4jetCand_[i].p4.Pt() == Hadronicb_[2].p4.Pt()) continue;
				Leptonicb_.push_back(AK4jetCand_[i]);
				Double_t deltaR = AK4jetCand_[i].p4.DeltaR(leptonCand_[0].p4);
				Double_t deltaTmass = fabs(pdgMtop - ((p4nu + leptonCand_[0].p4 + AK4jetCand_[i].p4).M()));
				if(deltaTmass < deltaTmassMin ){
					deltaRmin = deltaR;
					deltaTmassMin = deltaTmass;
					Leptonicb_[0]=AK4bjetCand_[i];
				}
			}
			
			Double_t TmassHad		= (Hadronicb_[0].p4 + Hadronicb_[1].p4 + Hadronicb_[2].p4).M();
			Double_t WmassHad		= (Hadronicb_[0].p4 + Hadronicb_[1].p4).M();
			
			// std::cout<<"Hadronic W mass = "<<(Hadronicb_[0].p4 + Hadronicb_[1].p4).M()<<std::endl;
			// std::cout<<"Hadronic b flavor = "<<Hadronicb_[2].flavor<<std::endl;
			// std::cout<<"Hadronic Top mass = "<<(Hadronicb_[0].p4 + Hadronicb_[1].p4 + Hadronicb_[2].p4).M()<<std::endl;
			// std::cout<<"Chi2 = "<<chi2Min<<std::endl;
			
			// findHadronicWCandidate		();
	//
	// 		deltaTmassMin = 999.;
	// 		TLorentzVector TLV;
	//
	// 		for(int i=0; i < AK4jetCand_.size(); i++ ){
	// 			Hadronicb_.push_back( AK4jetCand_[i] );
	// 			if (AK4jetCand_[i].p4.Pt() == Leptonicb_[0].p4.Pt() || AK4jetCand_[i].p4.Pt() == HadronicJ_[0].p4.Pt() || AK4jetCand_[i].p4.Pt() == HadronicJ_[1].p4.Pt() ) continue;
	// 			Double_t deltaTmass = fabs(pdgMtop - ((AK4jetCand_[i].p4 + HadronicJ_[0].p4 + HadronicJ_[1].p4).M()));
	// 			if( deltaTmass < deltaTmassMin ){
	// 				deltaTmassMin = deltaTmass;
	// 				Hadronicb_[0] = AK4jetCand_[i];
	// 			}
	// 		}
	//
			Double_t TmassLep		= (p4nu + leptonCand_[0].p4 + Leptonicb_[0].p4).M();
			Double_t WmassLep		= TMath::Sqrt( 2*METCand_[0].p4.Pt()*leptonCand_[0].p4.Pt()*(1-cos(leptonCand_[0].p4.DeltaPhi(METCand_[0].p4))));
			Double_t TmassLep2	= (p4nuMethod2 + leptonCand_[0].p4 + Leptonicb_[0].p4).M()	;
// 		Double_t TmassHad		= (Hadronicb_[0].p4 + HadronicJ_[0].p4 + HadronicJ_[1].p4).M();
	// 		Double_t WmassHad		= WCand_[1].p4.M();
	//
	// 		if( !(fabs(pdgMtop - TmassLep) < 0.20*pdgMtop && abs(pdgMtop - TmassHad) < 0.20*pdgMtop) ) throw SError( SError::SkipEvent );
	//
			Hist( "LeptonicbCSV"				)->Fill ( Leptonicb_[0].csv, weight_    );
			Hist( "LeptonicbFlavor"			)->Fill ( Leptonicb_[0].flavor, weight_	);
			// Hist( "bCandCSV"						)->Fill ( Hadronicb_[0].csv, weight_    );
// 			Hist( "bCandFlavor"					)->Fill ( Hadronicb_[0].flavor, weight_	);
			Hist( "bCandCSV"						)->Fill ( Hadronicb_[2].csv, weight_    );
			Hist( "bCandFlavor"					)->Fill ( Hadronicb_[2].flavor, weight_	);
			Hist( "HadronicTop"					)->Fill ( TmassHad, weight_	);
			Hist( "WmassHadronic"				)->Fill ( WmassHad , weight_	);
	// 		Hist( "WtransvMassHadronic"	)->Fill ( WCand_[1].p4.Mt() , weight_	);
			Hist( "WptLeptonic"					)->Fill ( WCand_[0].p4.Pt(), weight_	);
	// 		Hist( "WptHadronic"					)->Fill ( WCand_[1].p4.Pt(), weight_	);
			Hist( "WmassLeptonic"				)->Fill ( WmassLep , weight_	);
			Hist( "LeptonicTop"					)->Fill ( TmassLep, weight_	);
	// 		Hist( "WmassLeptonic2"			)->Fill ( (p4nuMethod2 + leptonCand_[0].p4).M() , weight_	);
	// 		Hist( "LeptonicTop2"				)->Fill ( TmassLep2, weight_	);
			fillSFHistos();
		}		
	}
	else
		throw SError( SError::SkipEvent );
	return;
}
//DONE!
//==============================================================================================
bool ExoDiBosonAnalysis::passedTrigger( void ){
	
	//Make sure event is triggered
	if( !Trigger_ ) return true;
	
	//Dijet triggers
	if( Channel_ == "VVdijet" || (Channel_.find("qcd") != std::string::npos) ){
		if( data_.isFired_HLT_AK8PFJet360_TrimMass30_v1											){ nPassedTrigger_++; return true;}
		else
			if( data_.isFired_HLT_AK8PFHT700_TrimR0p1PT0p03Mass50_v1					){ nPassedTrigger_++; return true;}
		else
			if( data_.isFired_HLT_AK8DiPFJet280_200_TrimMass30_BTagCSV0p41_v1	){ nPassedTrigger_++; return true;}
		else
			if( data_.isFired_HLT_PFHT650_WideJetMJJ950DEtaJJ1p5_v1						){ nPassedTrigger_++; return true;}
		else
			if( data_.isFired_HLT_PFHT650_WideJetMJJ900DEtaJJ1p5_v1						){ nPassedTrigger_++; return true;}
		else
			if( data_.isFired_HLT_PFHT900_v1																	){ nPassedTrigger_++; return true;}
	}
	
	//Muon trigger
	if( Channel_ == "muon" || (Channel_.find("ttbarmu") != std::string::npos) ){
		if( data_.isFired_HLT_Mu40_v1 													){nPassedTrigger_++; return true;}
	}
	//Electron trigger
	else
	if( Channel_ == "electron" || (Channel_.find("ttbarel") != std::string::npos) ){
		if( data_.isFired_HLT_Ele95_CaloIdVT_GsfTrkIdT_v1 						){ nPassedTrigger_++; return true;}
	}
	else
		return false;
    
}

//==============================================================================================
//Methods for VVdijet analysis====================================================================
//==============================================================================================
bool ExoDiBosonAnalysis::passedDijetSelections( void ){
	bool foundTwoJets					= false;
	bool passedDeltaEtaCut		= false;
	bool passedMjjCut					= false;
	bool passedPrunedMassCut	= false;
	bool passedTau21Cut				= false;
	bool passedWTag						= false;
	
	//Make sure events contains two AK8 jets passing loose requirements
	if( !findJetCandidates() ) return false;
	foundTwoJets = true;
	Hist( "Pt" ) -> Fill( ( Vcand[0].p4 ).Pt() , weight_ );	
	Hist( "Pt" ) -> Fill( ( Vcand[1].p4 ).Pt() , weight_ );	
	Hist( "Eta" ) -> Fill( ( Vcand[0].p4).Eta() , weight_ );	
	Hist( "Eta" ) -> Fill( ( Vcand[1].p4).Eta() , weight_ );	

	//Only select jets separated by |DeltaEta| < cut
	jetsDeltaEta = fabs( Vcand[0].p4.Eta()  - Vcand[1].p4.Eta() ) ; 
	if ( jetsDeltaEta <= 1.3 ){
		Hist( "Mjj" ) -> Fill( ( Vcand[0].p4 + Vcand[1].p4 ).M() , weight_ );	
		passedDeltaEtaCut = true;	
	}	
	
	//Only select jets with Mjj > cut
	// Mjj = ( Vcand[0].p4 + Vcand[1].p4 ).M();	
	if ( ( Vcand[0].p4 + Vcand[1].p4 ).M() >= MjjCut_ ){
		Hist( "DeltaEta"			)	->Fill( jetsDeltaEta , weight_ ); 	
		passedMjjCut = true;
	}
	
	
	//Only select jets with cut < Tau21 < cut
	if( Channel_ == "VVdijet"){
		if( (Vcand[0].tau2/Vcand[0].tau1 >= Tau21HPLow_ && Vcand[0].tau2/Vcand[0].tau1 <= Tau21HPHigh_ && Vcand[1].tau2/Vcand[1].tau1 > Tau21Low_ && Vcand[1].tau2/Vcand[1].tau1 <= Tau21High_ ) ||
			(	 Vcand[1].tau2/Vcand[1].tau1 >= Tau21HPLow_ && Vcand[1].tau2/Vcand[1].tau1 <= Tau21HPHigh_ && Vcand[0].tau2/Vcand[0].tau1 > Tau21Low_ && Vcand[0].tau2/Vcand[0].tau1 <= Tau21High_ ) ) passedTau21Cut = true ;

		//Only select jets in groomed mass window
		if( UsePruned_ && ( Vcand[0].prunedMass > mPMLow_ && Vcand[0].prunedMass < mPMHigh_ ) && ( Vcand[1].prunedMass > mPMLow_ && Vcand[1].prunedMass < mPMHigh_ ) )				passedPrunedMassCut = true ;	
		else 
			if(  UseSD_ && ( Vcand[0].softdropMass > mSDLow_ && Vcand[0].softdropMass < mSDHigh_ ) && ( Vcand[1].softdropMass > mSDLow_ && Vcand[1].softdropMass < mSDHigh_ ) )	passedPrunedMassCut = true ;
		
	}
	else
	if( Channel_ == "qVdijet"){
		if( (Vcand[0].tau2/Vcand[0].tau1 > Tau21Low_ && Vcand[0].tau2/Vcand[0].tau1 <= Tau21High_ ) || ( Vcand[1].tau2/Vcand[1].tau1 > Tau21Low_ && Vcand[1].tau2/Vcand[1].tau1 <= Tau21High_ ) ) passedTau21Cut = true ;
		if( (Vcand[0].tau2/Vcand[0].tau1 > Tau21Low_ && Vcand[0].tau2/Vcand[0].tau1 <= Tau21High_ ) && ( Vcand[0].prunedMass > mPMLow_ && Vcand[0].prunedMass < mPMHigh_ ) ) passedPrunedMassCut = true;
		else
			if( (Vcand[1].tau2/Vcand[1].tau1 > Tau21Low_ && Vcand[1].tau2/Vcand[1].tau1 <= Tau21High_ ) && ( Vcand[1].prunedMass > mPMLow_ && Vcand[1].prunedMass < mPMHigh_ ) ) passedPrunedMassCut = true ;			
	} 
	
	if(passedPrunedMassCut && passedTau21Cut) passedWTag = true ;	
	
	if( passedDeltaEtaCut && passedMjjCut ){
		Hist( "Tau21"	)->Fill( Vcand[0].tau2/Vcand[0].tau1,weight_ );
		Hist( "Tau21"	)->Fill( Vcand[1].tau2/Vcand[1].tau1,weight_ );
		Hist( "PrunedMass"		)	->Fill( Vcand[0].prunedMass, weight_ );
		Hist( "PrunedMass"		)	->Fill( Vcand[1].prunedMass, weight_ );
		Hist( "SoftdropMass"	)	->Fill( Vcand[0].softdropMass, weight_ );
		Hist( "SoftdropMass"	)	->Fill( Vcand[1].softdropMass, weight_ );	
	}
	
	if ( passedDeltaEtaCut && passedMjjCut && passedPrunedMassCut ){
		Hist( "Tau21_punzi"	)->Fill( Vcand[0].tau2/Vcand[0].tau1,weight_ );
		Hist( "Tau21_punzi"	)->Fill( Vcand[1].tau2/Vcand[1].tau1,weight_ );
	}
	//Some trigger efficiencies without dEta requirement
	if( Vcand[0].p4.Pt() > 500 ){
		Hist( "TriggerEffPrunedMassDen_PtCut"  ) ->Fill( Vcand[0].prunedMass		);
		Hist( "TriggerEffSoftdropMassDen_PtCut") ->Fill( Vcand[0].softdropMass	);
		
		if( data_.isFired_HLT_AK8PFJet360_TrimMass30_v1 ){
			Hist( "TriggerEffPrunedMass_HLT_AK8PFJet360_TrimMass30_PtCut"											)->Fill ( Vcand[0].prunedMass		);
			Hist( "TriggerEffSoftdropMass_HLT_AK8PFJet360_TrimMass30_PtCut"										)->Fill ( Vcand[0].softdropMass	);
		}
		if( data_.isFired_HLT_AK8PFHT700_TrimR0p1PT0p03Mass50_v1 ){
			Hist( "TriggerEffPrunedMass_HLT_AK8PFHT700_TrimR0p1PT0p03Mass50_PtCut"						)->Fill ( Vcand[0].prunedMass		);
			Hist( "TriggerEffSoftdropMass_HLT_AK8PFHT700_TrimR0p1PT0p03Mass50_PtCut"					)->Fill ( Vcand[0].softdropMass	);
		}
		if( data_.isFired_HLT_AK8DiPFJet280_200_TrimMass30_BTagCSV0p41_v1 ){
			Hist( "TriggerEffPrunedMass_HLT_AK8DiPFJet280_200_TrimMass30_BTagCSV0p41_PtCut"		)->Fill ( Vcand[0].prunedMass		);
			Hist( "TriggerEffSoftdropMass_HLT_AK8DiPFJet280_200_TrimMass30_BTagCSV0p41_PtCut"	)->Fill ( Vcand[0].softdropMass	);
		}
		if( data_.isFired_HLT_AK8DiPFJet280_200_TrimMass30_BTagCSV0p41_v1 || data_.isFired_HLT_AK8PFHT700_TrimR0p1PT0p03Mass50_v1 || data_.isFired_HLT_AK8PFJet360_TrimMass30_v1 || data_.isFired_HLT_PFHT650_WideJetMJJ950DEtaJJ1p5_v1
		|| data_.isFired_HLT_PFHT650_WideJetMJJ900DEtaJJ1p5_v1 || data_.isFired_HLT_PFHT900_v1){
			Hist( "TriggerEffPrunedMass_ALL_PtCut"		)->Fill ( Vcand[0].prunedMass		);
			Hist( "TriggerEffSoftdropMass_ALL_PtCut"	)->Fill ( Vcand[0].softdropMass	);
		}
		if( data_.isFired_HLT_AK8DiPFJet280_200_TrimMass30_BTagCSV0p41_v1 || data_.isFired_HLT_AK8PFHT700_TrimR0p1PT0p03Mass50_v1 || data_.isFired_HLT_AK8PFJet360_TrimMass30_v1){
			Hist( "TriggerEffPrunedMass_trimmed_PtCut"		)->Fill ( Vcand[0].prunedMass		);
			Hist( "TriggerEffSoftdropMass_trimmed_PtCut"	)->Fill ( Vcand[0].softdropMass	);
		}  
		
	}
	
	// Trigger efficiencies
	if( passedDeltaEtaCut ) doJetRecoEfficiency();
   
   
	//Cut flow
	if( !foundTwoJets 			)	return false;
	nPassedFoundJets_++;

	if( !passedDeltaEtaCut	)	return false;   
	nPassedJetsDEta_++;

	if( !passedMjjCut 			)	return false;      
	nPassedMjj_++;
   
	if( !passedPrunedMassCut)	return false;
	nPassedJetPrunedMass_++;
   
	if( !passedTau21Cut			)	return false;      
	nPassedTau21Cut_++;
	
	// if( !passedWTag				)	return false;
	nPassedWTag_++;
	
	
	//Apply selection
	if ( foundTwoJets && passedDeltaEtaCut && passedMjjCut && passedPrunedMassCut && passedTau21Cut   ) return true;
   
	else return false;
	
}
//==============================================================================================
bool ExoDiBosonAnalysis::findJetCandidates( void ){
	
	TLorentzVector			TLV;
	std::vector<float>	jetPt;
	bool foundJets = false;
		
	jetPt.clear();
	
	//Make sure jets passes loose ID, pT and eta cuts
	for( int j = 0; j < data_.njetsAK8; ++j ){
		if( (*data_.jetAK8_IDLoose)[j]		!= 1							)continue;
		if( (*data_.jetAK8_pt)[j]					<= JetPtCutLoose_	)continue;
		if( fabs((*data_.jetAK8_eta)[j]) 	>= JetEtaCut_ 		)continue;
				
		jetPt.push_back((*data_.jetAK8_pt)[j]);
		
	}
	
	if( jetPt.size() < 2 ) return false;
	else
		foundJets = true;
		
	//Find two highest pT jets in event
	if( foundJets ){
		std::sort	(jetPt.begin(),jetPt.end());
		std::reverse(jetPt.begin(),jetPt.end());
		for( int jj = 0; jj < data_.njetsAK8; ++jj ){
			if( (*data_.jetAK8_pt)[jj] == jetPt[0] ){
				TLV.SetPtEtaPhiE( (*data_.jetAK8_pt)[jj], (*data_.jetAK8_eta)[jj], (*data_.jetAK8_phi)[jj], (*data_.jetAK8_e)[jj] );
				JetCandidate leadingJet(TLV);
				leadingJet.csv					= -99																			;
				leadingJet.tau1					= (*data_.jetAK8_tau1)[jj]								;
				leadingJet.tau2					= (*data_.jetAK8_tau2)[jj]								;
				leadingJet.tau3					= (*data_.jetAK8_tau3)[jj]								;
				leadingJet.prunedMass		= (*data_.jetAK8_prunedmassUnCorr)[jj]		;
				leadingJet.softdropMass	= (*data_.jetAK8_softdropmassUnCorr)[jj]	;
				leadingJet.mass					= (*data_.jetAK8_mass)[jj]								;
				leadingJet.flavor				= -99																			;
				leadingJet.rcn					= (*data_.jetAK8_che)[jj]/(*data_.jetAK8_ne)[jj];
				Vcand.push_back( leadingJet );
			}
			else
			if( (*data_.jetAK8_pt)[jj] == jetPt[1] ){
				TLV.SetPtEtaPhiE( (*data_.jetAK8_pt)[jj], (*data_.jetAK8_eta)[jj], (*data_.jetAK8_phi)[jj], (*data_.jetAK8_e)[jj] );
				JetCandidate secondJet(TLV);
				secondJet.csv					= -99																							;
				secondJet.tau1					= (*data_.jetAK8_tau1)[jj]											;
				secondJet.tau2					= (*data_.jetAK8_tau2)[jj]											;
				secondJet.tau3					= (*data_.jetAK8_tau3)[jj]											;
				secondJet.prunedMass		= (*data_.jetAK8_prunedmassUnCorr)[jj]					;
				secondJet.softdropMass	= (*data_.jetAK8_softdropmassUnCorr)[jj]				;
				secondJet.mass					= (*data_.jetAK8_mass)[jj]											;
				secondJet.flavor				= -99																						;
				secondJet.rcn						= (*data_.jetAK8_che)[jj]/(*data_.jetAK8_ne)[jj];
				Vcand.push_back( secondJet );
			}
			else
				continue;
		}
	}
	if (Vcand.size() < 2) return false;
	return foundJets;
}
//==============================================================================================
//==============================================================================================

//==============================================================================================
//Methods for TTbar SF measurement==============================================================
//==============================================================================================
bool ExoDiBosonAnalysis::passedTTbarSelections( void ){
	bool foundLept = false;
	bool found1Jet = false;
	bool found2Jet = false;
	bool found3Jet = false;
	bool found4Jet = false;
	bool found1b   = false;
	bool found2b   = false;
  
	if( findLeptonCandidate() ) foundLept = true; 
   
	if( !foundLept ) return false;
	nPassedFoundLept_++;
	
	findExtraJets();
	Hist( "nAK4"	)->Fill ( AK4jetCand_.size() );
	if( AK4jetCand_.size() >= 1 ) found1Jet = true;
	if( !found1Jet ) return false;	
	nPassed1Jet_++;
	if( AK4jetCand_.size() >= 2 ) found2Jet = true;
	if( !found2Jet ) return false;
	nPassed2Jet_++;
	if( AK4jetCand_.size() >= 3 ) found3Jet = true;
	if( !found3Jet ) return false;
	nPassed3Jet_++;
	if( AK4jetCand_.size() >= 4 ) found4Jet = true;
	if( !found4Jet ) return false;
	nPassed4Jet_++;
	
	Hist( "nbTagAK4"	)->Fill ( nBTags );
	
	if ( nBTags > 0) found1b = true;
	if( !found1b ) return false;
	nPassed1bTag_++;
	if ( nBTags > 1) found2b = true;
	if( !found2b ) return false;
	nPassed2bTag_++;
	
	if( foundLept && found4Jet) return true;
	
	else
		return false;
}

//==============================================================================================
//Methods for semileptonic analysis=============================================================
//==============================================================================================
bool ExoDiBosonAnalysis::passedSelections( void ){

	/*************************************************************/
	bool foundLept = false;
  
	if( findLeptonCandidate() ) foundLept = true; 
   
	if( !foundLept ) return false;
	nPassedFoundLept_++;
   
	/*************************************************************/
	bool foundMET = false;
   
	if( findMETCandidate() ){ 
		if( METCand_[0].p4.Pt() > METCut_ )foundMET = true;
	} 

	if( !foundMET ) return false;   
	nPassedFoundMET_++;

	/*************************************************************/  
	bool foundW = false;
   
	if( foundLept && foundMET && findWCandidate() ){ 
		if( WCand_[0].p4.Pt() > WptCut_ ) foundW = true;
	} 

	if( !foundW ) return false;   
	nPassedFoundW_++;
 
	/*************************************************************/
	bool foundJet1 = false;
	bool foundJet2 = false;
	bool foundJet3 = false;
      
	if( foundLept && findJetCandidate() ){
		foundJet1 = true;
		if( leptonCand_[0].p4.DeltaR(Vcand[0].p4) > 1.0 ) foundJet2 = true;
		if( Vcand[0].p4.Pt() > JetPtCutTight_ ) foundJet3 = true;
	}

	if( !foundJet1 ) return false;
	nPassedFoundJet_++;

	if( !foundJet2 ) return false;   
	nPassedLepJetDR_++;

	if( !foundJet3 ) return false;      
	nPassedJetPtTight_++;
     
	/*************************************************************/
	findExtraJets();
            
	bool najetCut = false; 
	int najet = 0;
	for( unsigned int j = 0; j < AK4jetCand_.size(); j++ ){
		if( AK4jetCand_[j].csv > bTagWPmap_[BtagVetoWP_] ) najet++;
	}
   
	if( (Channel_.find("ttbar") == std::string::npos && najet <= nAJetCut_) || (Channel_.find("ttbar") != std::string::npos && najet  > nAJetCut_) ) najetCut = true;
   
	if( nAJetCut_ != -1 && !najetCut ) return false;
	nPassedAJetCut_++;    
    
	/*************************************************************/            
	bool lepJetDR = false;
	if( foundLept && foundJet1 && leptonCand_[0].p4.DeltaR(Vcand[0].p4) > TMath::Pi()/2. ) lepJetDR = true;    

	if( Channel_.find("ttbar") == std::string::npos && !lepJetDR ) return false;
	nPassedLepJetDR2_++;
    
	/*************************************************************/      
	bool METJetDPhi = false;
	if( foundMET && foundJet1 && fabs(METCand_[0].p4.DeltaPhi(Vcand[0].p4)) > 2. ) METJetDPhi = true;

	if( Channel_.find("ttbar") == std::string::npos && !METJetDPhi ) return false;
	nPassedMETJetDPhi_++;
     
	/*************************************************************/         
	bool JetWDPhi = false;
	if( foundW && foundJet1 && fabs(WCand_[0].p4.DeltaPhi(Vcand[0].p4)) > 2. ) JetWDPhi = true;

	if( Channel_.find("ttbar") == std::string::npos && !JetWDPhi ) return false;
	nPassedJetWDPhi_++;   

	/*************************************************************/         
	findTopCandidate();
	if( TopMassCut_ && ((ltopmass > leptTopMassLow_ && ltopmass < leptTopMassHigh_) || (htopmass > hadrTopMassLow_ && htopmass < hadrTopMassHigh_)) ) return false;   
	nPassedTopMass_++;
             
	/*************************************************************/                  
	if( VetoSR_ && Vcand[0].prunedMass > 110. && Vcand[0].prunedMass < 135 ) return false;
   
	bool foundJet = false;   
	if( foundJet1 && Vcand[0].tau2/Vcand[0].tau1 > Tau21Low_ && Vcand[0].tau2/Vcand[0].tau1 < Tau21High_ ) foundJet = true;

	if( Tau21Cut_ && !foundJet ) return false; 
	nPassedTau21Cut_++;
   
	foundJet = false;
	if( foundJet1 && Vcand[0].prunedMass > mPMLow_ && Vcand[0].prunedMass < mPMHigh_ ) foundJet = true;

	if( !foundJet ) return false; 
	nPassedJetMass_++;
             
	/*************************************************************/    
	findExoCandidate();
      
	if( WHMass_ == -1 ){
		nPassedExoCandidateMass_++;       
		return true;
	}
   	        
	double low = WHMass_ - WHMass_*15./100.;
	double up = WHMass_ + WHMass_*15./100.; 
	if( MVV > low && MVV < up ){
		nPassedExoCandidateMass_++;
		return true;
	}
	else return false;

}

//==============================================================================================
double ExoDiBosonAnalysis::getMuonScale( double oldpt ){

	double scale = 0.;
   
	if( oldpt < 200. ) scale = (ScaleMuonUpDown_)*0.2*oldpt/100.;
	else if( oldpt >= 200. ) scale = (ScaleMuonUpDown_)*5.*oldpt/100.;	
   
	return scale;
      
}

//==============================================================================================
double ExoDiBosonAnalysis::getPrunedMassScale( double prunedmass ){
   
	return (ScalePrunedMass_)*1.9*prunedmass/100.;
      
}

//==============================================================================================
bool ExoDiBosonAnalysis::findLeptonCandidate( void ){

	if( Channel_.find("el") != std::string::npos ) return findElectronCandidate();
	else if( Channel_.find("mu") != std::string::npos ) return findMuonCandidate();
	else return false;
   
}

//==============================================================================================
bool ExoDiBosonAnalysis::findMuonCandidate( void ){

	TLorentzVector TLV;
	bool foundLept			= false	;
	double ptMu				= -999	;
	unsigned int muIndex = 999		;
	double scale			= 0.		;
	double newpt			= 0.		;
	double scale_			= 0.		;
	
	for( unsigned int l = 0; l < (data_.lep_pt)->size(); ++l ){
		if( abs((*data_.lep_type)[l])															!= 13	) continue;	
		if( Channel_ == "muon" && (*data_.lep_isHighPtMuon)[l]		!= 1	) continue;
		if( Channel_ == "SFmuJets" && (*data_.lep_isTightMuon)[l]	!= 1	) continue;
		scale = getMuonScale((*data_.lep_pt)[l]);
		newpt = (*data_.lep_pt)[l]+scale;
		if( Channel_ == "SFmuJets" && (*data_.lep_pt)[l]*(*data_.lep_pfRelIso)[l]/newpt	>= 0.12	)	continue;
		if( Channel_ == "muon" 		&& (*data_.lep_trackIso)[l]/newpt							>= 0.10	)	continue;
		if( newpt													<= leptPtCut_							)	continue;
		if( fabs((*data_.lep_eta)[l]) 		>= leptEtaCut_						)	continue;
		foundLept = true;
		if( newpt > ptMu ){   
			ptMu		= newpt	;
			muIndex	= l		;
			scale_	= scale	;
			TLV.SetPtEtaPhiE( newpt, (*data_.lep_eta)[l], (*data_.lep_phi)[l], (*data_.lep_e)[l]+scale );  
		}      
	}
   
	if( foundLept ){
		LeptonCandidate muCand(TLV);
		muCand.iso		= (*data_.lep_trackIso)[muIndex]/newpt;
		muCand.scale	= scale_;
		leptonCand_.push_back( muCand );
		nPassedIsoLep_++;
	}
	int foundAMu	= 0	;
	scale				= 0.	;
	for( unsigned int l = 0; l < (data_.lep_pt)->size(); ++l ){
		if( abs((*data_.lep_type)[l]) 		!= 13									) continue;   
		if( muIndex 	== 999 							|| l == muIndex				) continue;
		if( Channel_ 	== "muon" && (*data_.lep_isHighPtMuon)[l]	!= 1		) continue;
		if( Channel_ 	== "SFmuJets" && (*data_.lep_isLooseMuon)[l]!= 1	) continue;		
		scale 			= getMuonScale((*data_.lep_pt)[l])	;
		newpt				= (*data_.lep_pt)[l]+scale				;
		if( Channel_ 	== "SFmuJets" && (*data_.lep_pt)[l]*(*data_.lep_pfRelIso)[l]/newpt	>= 0.20	)	continue;
		if( Channel_ 	== "muon" && (*data_.lep_trackIso)[l]/newpt									>= 0.10	)	continue;
		if( newpt 									<= AleptPtCut_					)	continue;
		if( fabs((*data_.lep_eta)[l]) 		>= AleptEtaCut_				)	continue;
		foundAMu++;
	}
   
	int foundAEle = 0;
	for( unsigned int l = 0; l < (data_.lep_pt)->size(); ++l ){
		if( abs((*data_.lep_type)[l])											!= 11																) continue;
		if( Channel_ == "muon" && (*data_.lep_isHEEP)[l]	!= 1																) continue;
		if( (*data_.lep_pt)[l]														<= 35.															) continue;
		if( Channel_ == "muon" && fabs((*data_.lep_eta)[l])>= 1.4442	&& fabs((*data_.lep_eta)[l]) <= 1.566	) continue;
		if( fabs((*data_.lep_eta)[l]) 										>= 2.5															) continue;
		foundAEle++;
	}
    
	if( (foundAMu+foundAEle)<1 && foundLept ){
		nPassedVetoLep_++;
		return true;
	}
	else return false;
   
}

//==============================================================================================
bool ExoDiBosonAnalysis::findElectronCandidate( void ){
	
	TLorentzVector TLV;
	bool foundEle = false;
	double ptEle = -999;
	unsigned int eleIndex = 999;
	
	for( unsigned int l = 0; l < (data_.lep_pt)->size(); ++l ){
		
		if( abs((*data_.lep_type)[l])	!= 11															)	continue;
		if( (*data_.lep_pt)[l]			<= 35.														)	continue;     
		if( fabs((*data_.lep_eta)[l])	>= 1.4442 && fabs((*data_.lep_eta)[l]) <= 1.566 )	continue;            
		if( fabs((*data_.lep_eta)[l])	>= leptEtaCut_ 											)	continue; 
		if( (*data_.lep_isHEEP)[l]		!= 1															)	continue;
		if( (*data_.lep_pt)[l]			<= leptPtCut_												)	continue;
		foundEle = true;
		
		if( (*data_.lep_pt)[l] > ptEle ){
			ptEle 	= (*data_.lep_pt)[l];
			TLV.SetPtEtaPhiE( (*data_.lep_pt)[l], (*data_.lep_eta)[l], (*data_.lep_phi)[l], (*data_.lep_e)[l] );         
			eleIndex = l;
		}
	}
      
	if( foundEle )	leptonCand_.push_back( LeptonCandidate( TLV ) );
   
	int foundAEle = 0;
	for( unsigned int l = 0; l < (data_.lep_pt)->size(); ++l ){
		if( abs((*data_.lep_type)[l])	!= 11															) continue;
		if( eleIndex == 999 				|| l == eleIndex											) continue;
		if( (*data_.lep_isHEEP)[l]		!= 1															) continue;
		if( (*data_.lep_pt)[l]			<= AleptPtCut_												) continue;
		if( fabs((*data_.lep_eta)[l]) >= 1.4442 && fabs((*data_.lep_eta)[l]) <= 1.566 ) continue;
		if( fabs((*data_.lep_eta)[l]) >= AleptEtaCut_											) continue;
		foundAEle++;
	}
   
	int foundAMu = 0;
	for( unsigned int l = 0; l < (data_.lep_pt)->size(); ++l ){
		if( abs((*data_.lep_type)[l])		!= 13														) continue;   
		if( (*data_.lep_isHighPtMuon)[l] != 1														) continue;
		if( (*data_.lep_trackIso)[l]/(*data_.lep_pt)[l] >= 0.1								) continue;
		if( (*data_.lep_pt)[l]				<= 20.													) continue;
		if( fabs((*data_.lep_eta)[l]) 	>= 2.4													) continue;
		foundAMu++;
	}
      
	if( (foundAMu+foundAEle)<1 && foundEle ){
		nPassedVetoLep_++;
		return true;
	}
	
	else return false;   
   
	return true;
   
}

//==============================================================================================
bool ExoDiBosonAnalysis::findJetCandidate( void ){

	TLorentzVector jet;
	TLorentzVector bestJet;
   
	bool  foundJet    = false;
	float csv         = -9999;
	float ptJet       = -9999; 
	unsigned int jetIndex = 999;
	float tau1        = -9999;
	float tau2        = -9999;
	float tau3        = -9999;
   
	for( unsigned int j = 0; j < (data_.jetAK8_pt)->size(); ++j ){
		jet.SetPtEtaPhiE( (*data_.jetAK8_pt)[j], (*data_.jetAK8_eta)[j], (*data_.jetAK8_phi)[j], (*data_.jetAK8_e)[j] );
		if( (*data_.jetAK8_IDLoose)[j] != 1 ) continue;
		if( (*data_.jetAK8_pt)[j] <= JetPtCutLoose_ ) continue;
		if( fabs((*data_.jetAK8_eta)[j]) >= JetEtaCut_ ) continue;
		if( leptonCand_[0].p4.DeltaR(jet) <= 1.0 ) continue;
		if( (*data_.jetAK8_pt)[j] > ptJet ){
			ptJet = (*data_.jetAK8_pt)[j];
			bestJet.SetPtEtaPhiE( (*data_.jetAK8_pt)[j], (*data_.jetAK8_eta)[j], (*data_.jetAK8_phi)[j], (*data_.jetAK8_e)[j] ); 
			csv = (*data_.jetAK8_csv)[j];
			tau1 = (*data_.jetAK8_tau1)[j];
			tau2 = (*data_.jetAK8_tau2)[j];
			tau3 = (*data_.jetAK8_tau3)[j]; 
			foundJet = true;
			jetIndex = j;
		}
	}

	if( foundJet ){
		JetCandidate jetC(bestJet); 
		jetC.csv  = csv;
		jetC.tau1 = tau1;
		jetC.tau2 = tau2;
		jetC.tau3 = tau3;
		jetC.prunedMass = (*data_.jetAK8_prunedmassUnCorr)[jetIndex]+getPrunedMassScale((*data_.jetAK8_prunedmassUnCorr)[jetIndex]);
		jetC.softdropMass = (*data_.jetAK8_softdropmassUnCorr)[jetIndex];
		jetC.mass = (*data_.jetAK8_mass)[jetIndex];
		Vcand.push_back( jetC );
	}
                        
	return foundJet;

}

//==============================================================================================	
void ExoDiBosonAnalysis::findExtraJets( void ){
	
	nBTags = 0;
	TLorentzVector jet;
	for( unsigned int j = 0; j < (data_.jetAK4_pt)->size(); ++j ){ 
		jet.SetPtEtaPhiE( (*data_.jetAK4_pt)[j], (*data_.jetAK4_eta)[j], (*data_.jetAK4_phi)[j], (*data_.jetAK4_e)[j] );
		if( (Channel_ == "electron" || Channel_ == "muon"  ) && jet.DeltaR(WCand_[0].p4) < 0.8 ) continue;
		if( (*data_.jetAK4_IDLoose)[j] != 1 ) continue;
		if( (*data_.jetAK4_pt)[j] <= 30. ) continue;
		if( fabs((*data_.jetAK4_eta)[j]) >= JetEtaCut_ ) continue;
		if( jet.DeltaR(leptonCand_[0].p4) < 0.3 ) continue;
		JetCandidate Ajet(jet);
		Ajet.csv = (*data_.jetAK4_csv)[j];
		Ajet.flavor = abs((*data_.jetAK4_flavor)[j]);
		AK4jetCand_.push_back(Ajet);
		if ((*data_.jetAK4_csv)[j] > 0.814){
			nBTags++;
			AK4bjetCand_.push_back(Ajet);
		} 
	}
}

//==============================================================================================
bool ExoDiBosonAnalysis::findMETCandidate( void ){
 
	TLorentzVector TLV;
	bool foundMET = false;
	if( (*data_.MET_et)[0] > 0. ){
   
		if( ScaleMuonUpDown_ == 0 ) TLV.SetPtEtaPhiE( (*data_.MET_et)[0], 0., (*data_.MET_phi)[0], 0. );
		else{

			TVector2 lepnew; lepnew.SetMagPhi( leptonCand_[0].p4.Pt(), leptonCand_[0].p4.Phi() );
			TVector2 lep; lep.SetMagPhi( leptonCand_[0].p4.Pt() - leptonCand_[0].scale, leptonCand_[0].p4.Phi() );
			TVector2 diff = lepnew - lep;
			TVector2 met; met.SetMagPhi( (*data_.MET_et)[0], (*data_.MET_phi)[0] );
			TVector2 METcorr = met - diff;
			TLV.SetPtEtaPhiE( METcorr.Mod(), 0., METcorr.Phi(), 0. );
	 
		}
      
		METCand_.push_back( METCandidate( TLV ) );
		foundMET = true;
      
	}
    
	return foundMET; 
   
}

//==============================================================================================
bool ExoDiBosonAnalysis::findWCandidate( void ){

	TLorentzVector TLV;
	bool foundW = false;
	if( (METCand_[0].p4+leptonCand_[0].p4).Pt() > 0. ){
		foundW = true;
		TLV = METCand_[0].p4+leptonCand_[0].p4;
		WCand_.push_back( TLV );
	}
   
	return foundW;
}
//==============================================================================================
bool ExoDiBosonAnalysis::findHadronicWCandidate( void ){

	TLorentzVector TLV,TLV1, TLV2;
	bool foundW = false;
	Double_t deltaWmassMin = 999.;

	for(int i=0; i < AK4jetCand_.size(); i++ ){
		if (AK4jetCand_[i].p4.Pt() == Leptonicb_[0].p4.Pt() || AK4jetCand_[i].p4.Pt() <= 0. ) continue;
		for(int j=0; j != i && j < AK4jetCand_.size(); j++ ){
			Double_t deltaWmass = fabs(pdgMw - ((AK4jetCand_[i].p4+ AK4jetCand_[j].p4).M()));
			if( deltaWmass < deltaWmassMin ){
				deltaWmassMin = deltaWmass;
				foundW = true;
				TLV = AK4jetCand_[i].p4+AK4jetCand_[j].p4;
				TLV1 = AK4jetCand_[i].p4;
				TLV2 = AK4jetCand_[j].p4;
			}
		}
	}
	HadronicJ_.push_back( TLV1 );
	HadronicJ_.push_back( TLV2 );
	Hist( "DeltaRJJ")->Fill ( HadronicJ_[1].p4.DeltaR(HadronicJ_[0].p4) , weight_	);
	
	WCand_.push_back( TLV );
	return foundW;

}

//==============================================================================================
TLorentzVector ExoDiBosonAnalysis::getp4Nu( void ){

	return Utilities::NuMomentum( leptonCand_[0].p4.Px(), leptonCand_[0].p4.Py(), leptonCand_[0].p4.Pz(), leptonCand_[0].p4.Pt(), leptonCand_[0].p4.E(), METCand_[0].p4.Px(), METCand_[0].p4.Py() );   
   
}

//==============================================================================================
TLorentzVector ExoDiBosonAnalysis::getp4NuMethod2( void ){

	double E_l  = leptonCand_[0].p4.E();
	double m_l  = leptonCand_[0].p4.M();
	double px_l = leptonCand_[0].p4.Px();
	double py_l = leptonCand_[0].p4.Py();
	double pz_l = leptonCand_[0].p4.Pz();

	//std::cout << "lep: px = " << px_l << " - py = " << py_l << " - pz = " << pz_l << " - pt = " << TMath::Sqrt(px_l*px_l + py_l*py_l);
	//std::cout << " - pt LTV = " << leptonCand_[0].p4.Pt() << " - mass = " << m_l << std::endl;
      
	double px_v = METCand_[0].p4.Px();
	double py_v = METCand_[0].p4.Py();
   
	//std::cout << "MET: metx = " << px_v << " - mety = " << py_v << " - et = " << TMath::Sqrt(px_v*px_v + py_v*py_v);
	//std::cout << " - et TLV = " << METCand_[0].p4.Pt() << std::endl;
   
	double m_W = 80.4;
   
	double a = m_W*m_W - m_l*m_l + 2*px_l*px_v + 2*py_l*py_v;
	double A = 4*(E_l*E_l - pz_l*pz_l);
	double B = (-4)*a*pz_l;
	double C = 4*E_l*E_l*(px_v*px_v + py_v*py_v) - a*a;
	double Delta = B*B - 4*A*C;
   
	/*Hist( "Discriminant")->Fill(Delta/1e15);
	Hist( "A"           )->Fill(A/1e+05);
	Hist( "B"           )->Fill(B/1e+07);
	Hist( "C"           )->Fill(C/1e+09);
	Hist( "a"           )->Fill(a/1e+04);*/
   
	double pz_v_1 = -9999;
	double pz_v_2 = -9999;
	double pz_v   = -9999;
      
	if( Delta > 0 ){
		pz_v_1 = ( -B + TMath::Sqrt(Delta) )/( 2*A );
		pz_v_2 = ( -B - TMath::Sqrt(Delta) )/( 2*A ); 
		if( fabs(pz_v_1) <= fabs(pz_v_2) ) pz_v = pz_v_1;
		else pz_v = pz_v_2;     
	}
	else if ( Delta <= 0 )
		pz_v = -B/(2*A);

	TLorentzVector v; v.SetPxPyPzE(px_v,py_v,pz_v,fabs(TMath::Sqrt(pz_v*pz_v + py_v*py_v + px_v*px_v)));
	v.SetPz(pz_v);
	v.SetPx(px_v);
	v.SetPy(py_v);
	v.SetE(fabs(TMath::Sqrt(pz_v*pz_v + py_v*py_v + px_v*px_v)));  

	/*if( Delta > 0){
	Hist( "NuLeptInvMassDeltap"  )->Fill( (v + leptonCand_[0].p4).M() );
	Hist( "DiBosonInvMassDeltap" )->Fill( (v + leptonCand_[0].p4 + WCand_[0].p4).M() );
	}
	else if( Delta <= 0 ){
	Hist( "NuLeptInvMassDeltam"  )->Fill( (v + leptonCand_[0].p4).M() );
	Hist( "DiBosonInvMassDeltam" )->Fill( (v + leptonCand_[0].p4 + WCand_[0].p4).M() );   
	}*/
   
	//std::cout << "Method 2: " << Delta << std::endl;
   
	return v;
      
}

//==============================================================================================
void ExoDiBosonAnalysis::findExoCandidate( void ){

	TLorentzVector p4nu = getp4Nu();      
	MVV = (p4nu + leptonCand_[0].p4 + Vcand[jetIndex_].p4).M();
	WMass = (p4nu + leptonCand_[0].p4).M();
   
	TLorentzVector p4nu2 = getp4NuMethod2();
	//Hist( "pzNu" )->Fill(p4nu2.Pz());

	//Hist( "NuLeptInvMass"  )->Fill( (p4nu2 + leptonCand_[0].p4).M() );
	MVVmethod2 = (p4nu2 + leptonCand_[0].p4 + Vcand[0].p4).M();  
	WMassMethod2 = (p4nu2 + leptonCand_[0].p4).M();  

	return;
            
}

//==============================================================================================
void ExoDiBosonAnalysis::fillSFHistos( void ){
	Hist( "leptonPT"            )->Fill( leptonCand_[0].p4.Pt()	, weight_ );
	Hist( "leptonPhi"         	)->Fill( leptonCand_[0].p4.Phi(), weight_ );
	Hist( "leptonEta"        	 	)->Fill( leptonCand_[0].p4.Eta(), weight_ );
	
	Hist( "WtransvMassLeptonic")->Fill( TMath::Sqrt( 2*METCand_[0].p4.Pt()*leptonCand_[0].p4.Pt()*(1-cos(leptonCand_[0].p4.DeltaPhi(METCand_[0].p4))) ), weight_ );
	if( AK4jetCand_.size() != 0 ){ 
		Hist( "AK4jetPt"       )->Fill( AK4jetCand_[0].p4.Pt(), weight_ );
		Hist( "AK4jetPt"       )->Fill( AK4jetCand_[1].p4.Pt(), weight_ );
		Hist( "AK4jetPt"       )->Fill( AK4jetCand_[2].p4.Pt(), weight_ );
		Hist( "AK4jetPt"       )->Fill( AK4jetCand_[3].p4.Pt(), weight_ );
		Hist( "AK4jetCSV"      )->Fill( AK4jetCand_[0].csv		, weight_ );
		Hist( "AK4jetCSV"      )->Fill( AK4jetCand_[1].csv		, weight_ );
		Hist( "AK4jetCSV"      )->Fill( AK4jetCand_[2].csv		, weight_ );
		Hist( "AK4jetCSV"      )->Fill( AK4jetCand_[3].csv		, weight_ );
		Hist( "AK4jetMass"     )->Fill( AK4jetCand_[0].p4.M()	, weight_ );
		Hist( "AK4jetMass"     )->Fill( AK4jetCand_[1].p4.M()	, weight_ );
		Hist( "AK4jetMass"     )->Fill( AK4jetCand_[2].p4.M()	, weight_ );
		Hist( "AK4jetMass"     )->Fill( AK4jetCand_[3].p4.M()	, weight_ );
	}
	
}

//==============================================================================================
void ExoDiBosonAnalysis::fillHistos( void ){


	if(Channel_ == "VVdijet" && (Vcand[0].p4 + Vcand[1].p4).M() > MjjCut_  ){
		// /* MVV */
		Hist( "VVdeltaEta"					)-> Fill( jetsDeltaEta , weight_ ); 
		Hist( "VcandTau21"	     		 	)->Fill( Vcand[0].tau2/Vcand[0].tau1,weight_ );
		Hist( "VcandTau21"	      		)->Fill( Vcand[1].tau2/Vcand[1].tau1,weight_ );
		Hist( "DiBosonInvMass"       		)->Fill( (Vcand[0].p4 + Vcand[1].p4).M(), weight_ );
		Hist( "VcandPrunedMass" 	    	)->Fill( Vcand[0].prunedMass, weight_ );
		Hist( "VcandPrunedMass" 	    	)->Fill( Vcand[1].prunedMass, weight_ );
		Hist( "VcandSoftdropMass"			)->Fill( Vcand[0].softdropMass, weight_ );
		Hist( "VcandSoftdropMass"			)->Fill( Vcand[1].softdropMass, weight_ );
		Hist( "VcandPt1"						)->Fill( Vcand[0].p4.Pt() , weight_ );
		Hist( "VcandPt2"						)->Fill( Vcand[1].p4.Pt() , weight_ );
		Hist( "VcandEta1" 	  		  		)->Fill( Vcand[0].p4.Eta(), weight_ );
		Hist( "VcandEta2" 	    			)->Fill( Vcand[1].p4.Eta(), weight_ );
		Hist( "VcandPhi1" 	    			)->Fill( Vcand[0].p4.Phi(), weight_ );
		Hist( "VcandPhi2" 	   	 		)->Fill( Vcand[1].p4.Phi(), weight_ );
		Hist( "VcandMass1" 	    			)->Fill( Vcand[0].mass , weight_ );
		Hist( "VcandMass2" 	    			)->Fill( Vcand[1].mass , weight_ );
	}
	
	else if(Channel_ == "muon" || Channel_ == "electron"){
		/* lepton histos */
		Hist( "leptonPT"        	 )->Fill( leptonCand_[0].p4.Pt(), weight_ );
		Hist( "leptonPhi"         	 )->Fill( leptonCand_[0].p4.Phi(), weight_ );
		Hist( "leptonEta"        	 )->Fill( leptonCand_[0].p4.Eta(), weight_ );

		/* MET histos */
		Hist( "MET"              	 )->Fill( METCand_[0].p4.Pt(), weight_ );
		Hist( "METphi"              )->Fill( METCand_[0].p4.Phi(), weight_ );

		/* leptonic W histos */
		Hist( "recoWPT"          	 )->Fill( WCand_[0].p4.Pt(), weight_ );
		Hist( "recoWMT"          	 )->Fill( TMath::Sqrt( 2*METCand_[0].p4.Pt()*leptonCand_[0].p4.Pt()*(1-cos(leptonCand_[0].p4.DeltaPhi(METCand_[0].p4))) ), weight_ );
   
		std::map<int,TLorentzVector>::iterator it = genCandidates_.find(24)!=genCandidates_.end() ? genCandidates_.find(24) : genCandidates_.find(-24);
		Hist( "genWMass" )->Fill( (it->second).M() );
		Hist( "WMassResolution" )->Fill( ((it->second).M()-WMass)/(it->second).M() );
		Hist( "WMassResolutionV2" )->Fill( ((it->second).M()-WMassMethod2)/(it->second).M() );
		for( unsigned int p = 0; p < (data_.genParticle_pdgId)->size(); ++p ){
			if( (*data_.genParticle_status)[p] != 4 && (*data_.genParticle_status)[p] != 22 && (*data_.genParticle_status)[p] != 23 ) continue;
			if( (*data_.genParticle_pdgId)[p] == 5100039 ){
				Hist( "WHMassResolution" )->Fill( ( (*data_.genParticle_mass)[p]-MVV )/(it->second).M() );
				Hist( "WHMassResolutionV2" )->Fill( ( (*data_.genParticle_mass)[p]-MVVmethod2)/(it->second).M() );
				break;
			}
		}
            
		/* topology histos */
		Hist( "lepJetDR"         	 )->Fill( leptonCand_[0].p4.DeltaR(Vcand[jetIndex_].p4), weight_ );
		Hist( "METJetDphi"       	 )->Fill( fabs(METCand_[0].p4.DeltaPhi(Vcand[jetIndex_].p4)), weight_ );
		Hist( "WJetDphi"         	 )->Fill( fabs(Vcand[jetIndex_].p4.DeltaPhi(WCand_[0].p4)), weight_ );

		/* top histos */
		Hist( "leptonictopmass"       )->Fill( ltopmass,weight_ );
		Hist( "hadronictopmass"       )->Fill( htopmass,weight_ );
		Hist( "leptonictopmassV2"       )->Fill( ltopmassMethod2,weight_ );

		/* MVV */
		// Hist( "DiBosonInvMass"        )->Fill( MVV, weight_ );
		Hist( "DiBosonInvMassMethod2" )->Fill( MVVmethod2, weight_ );

		/* other histos */
		Hist( "PUWeights"        	 )->Fill( puweight_ );
		Hist( "nVertices"        	 )->Fill( data_.nPVs, weight_ );
		Hist( "htagweight"            )->Fill(htagw);
		Hist( "btagvweight"           )->Fill(btagvetow);

		/* AK8 b-jet histos */
		Hist( "AK8bjetPT"       	 )->Fill( Vcand[jetIndex_].p4.Pt(), weight_ );
		Hist( "AK8bjetEta"      	 )->Fill( Vcand[jetIndex_].p4.Eta(), weight_ );
		Hist( "AK8bjetPhi"      	 )->Fill( Vcand[jetIndex_].p4.Phi(), weight_ );
		Hist( "AK8bjetCSV"      	 )->Fill( Vcand[jetIndex_].csv, weight_ );
		Hist( "AK8bjetPrunedMass" 	 )->Fill( Vcand[jetIndex_].prunedMass, weight_ );
		Hist( "AK8bjetMass"       	 )->Fill( Vcand[jetIndex_].mass, weight_ );
		Hist( "tau21"	         )->Fill( Vcand[jetIndex_].tau2/Vcand[jetIndex_].tau1,weight_ );
		Hist( "tau31"	         )->Fill( Vcand[jetIndex_].tau3/Vcand[jetIndex_].tau1,weight_ );
		Hist( "tau32"	         )->Fill( Vcand[jetIndex_].tau3/Vcand[jetIndex_].tau2,weight_ );
          
		/* AK4 jets histos */    
		int najets=0; 
		for( unsigned int j = 0; j < AK4jetCand_.size(); ++j ){
			if( AK4jetCand_[j].csv > bTagWPmap_[BtagVetoWP_] ) najets++;
		}    
		Hist( "nAJetsBTag" )->Fill(najets, weight_ );
		Hist( "nAJets" )->Fill(AK4jetCand_.size(), weight_ );
   
		if( AK4jetCand_.size() != 0 ){ 
			Hist( "AK4jetPt"       )->Fill( AK4jetCand_[0].p4.Pt(), weight_ );
			Hist( "AK4jetCSV"      )->Fill( AK4jetCand_[0].csv , weight_ );
			Hist( "AK4jetMass"     )->Fill( AK4jetCand_[0].p4.M(), weight_ );
		}
	}  

}


//==============================================================================================
void ExoDiBosonAnalysis::findTopCandidate( void ){

	unsigned int size = AK4jetCand_.size();
	htopmass = 1.;
	ltopmass = 1.;
   
	if( size == 0 )
		return;
     
	double dRtmp = 9999.;
	double dR = 0.;
	unsigned int jetIndex = 0;
	for( unsigned int j = 0; j < size; ++j ){
		dR = AK4jetCand_[j].p4.DeltaR(Vcand[jetIndex_].p4);
		if( dR < dRtmp ){
			jetIndex = j;
			dRtmp = dR;  
		} 
	}
   
	htopmass = (AK4jetCand_[jetIndex].p4+Vcand[jetIndex_].p4).M();
   
	dRtmp = 9999.;
	dR = 0.;
	jetIndex = 0;
	for( unsigned int j = 0; j < size; ++j ){
		dR = AK4jetCand_[j].p4.DeltaR(leptonCand_[0].p4);
		if( dR < dRtmp ){
			jetIndex = j;
			dRtmp = dR;  
		} 
	}
   
	TLorentzVector p4nu = getp4Nu();
	ltopmass = (p4nu + leptonCand_[0].p4 + AK4jetCand_[jetIndex].p4).M();

	TLorentzVector p4nu2 = getp4NuMethod2();
	ltopmassMethod2 = (p4nu2 + leptonCand_[0].p4 + AK4jetCand_[jetIndex].p4).M();
      
}
       			        
//==============================================================================================
void ExoDiBosonAnalysis::EndInputData( const SInputData& ) throw( SError ) {
		
	if (Channel_ == "VVdijet"){

		printCutFlow();                  
		theHistosManager_->formatHistos();

		//   Hist( "genEvents"               )->SetBinContent(1,genEvents_              );
		Hist( "nEvents"	    	       )->SetBinContent(1,nEvents_  	      );
		Hist( "nPassedTrigger"   	   )->SetBinContent(1,nPassedTrigger_	      );
		Hist( "nPassedFoundJets"   	   )->SetBinContent(1,nPassedFoundJets_	      );
		Hist( "nPassedJetsDEta"   	   )->SetBinContent(1,nPassedJetsDEta_	      );
		Hist( "nPassedMjj"   	   	   )->SetBinContent(1,nPassedMjj_	      		);
		Hist( "nPassedTau21Cut"   	   )->SetBinContent(1,nPassedTau21Cut_	      );
		Hist( "nPassedPrunedJetMass"    )->SetBinContent(1,nPassedJetPrunedMass_	      );
	}
	else if (Channel_ == "SFmuJets"){

		printCutFlow();                  
		theHistosManager_->formatHistos();

		Hist( "nEvents"					)->SetBinContent(1,nEvents_				);
		Hist( "nPassedIsoLep"			)->SetBinContent(1,nPassedIsoLep_		);
		Hist( "nPassedVetoLep"			)->SetBinContent(1,nPassedVetoLep_		);
		Hist( "nPassed1Jet"				)->SetBinContent(1,nPassed1Jet_	      );
		Hist( "nPassed2Jet"				)->SetBinContent(1,nPassed2Jet_			);
		Hist( "nPassed3Jet"				)->SetBinContent(1,nPassed3Jet_			);
		Hist( "nPassed4Jet"				)->SetBinContent(1,nPassed4Jet_			);
		Hist( "nPassed1bTag"				)->SetBinContent(1,nPassed1bTag_			);
		Hist( "nPassed2bTag"				)->SetBinContent(1,nPassed2bTag_			);
	
	}
	
	else if (Channel_ == "muon" || Channel_ == "electron"){
		
		if( Synch_ ) return;
   
		printCutFlow();                  
		theHistosManager_->formatHistos();

		Hist( "genEvents"               )->SetBinContent(1,genEvents_              );
		Hist( "nEvents"	    	   )->SetBinContent(1,nEvents_  	      );
		Hist( "nPassedTrigger"   	   )->SetBinContent(1,nPassedTrigger_	      );
		Hist( "nPassedFoundLepton" 	   )->SetBinContent(1,nPassedFoundLept_       );
		Hist( "nPassedFoundMET"  	   )->SetBinContent(1,nPassedFoundMET_        );
		Hist( "nPassedFoundW"    	   )->SetBinContent(1,nPassedFoundW_	      );   
		Hist( "nPassedFoundJet"  	   )->SetBinContent(1,nPassedFoundJet_        );
		Hist( "nPassedLepJetDR"  	   )->SetBinContent(1,nPassedLepJetDR_        );
		Hist( "nPassedJetPtTight"	   )->SetBinContent(1,nPassedJetPtTight_      );
		Hist( "nPassedAJetCut"   	   )->SetBinContent(1,nPassedAJetCut_	      );   
		Hist( "nPassedLepJetDR2" 	   )->SetBinContent(1,nPassedLepJetDR2_       );
		Hist( "nPassedMETJetDPhi"	   )->SetBinContent(1,nPassedMETJetDPhi_      );
		Hist( "nPassedJetWDPhi"  	   )->SetBinContent(1,nPassedJetWDPhi_        );
		Hist( "nPassedTopMass"  	   )->SetBinContent(1,nPassedTopMass_         );   
		Hist( "nPassedJetMass"   	   )->SetBinContent(1,nPassedJetMass_	      );
		Hist( "nPassedExoCandidateMass" )->SetBinContent(1,nPassedExoCandidateMass_);
   
		m_logger << INFO << std::endl; 
		m_logger << INFO << "############ Cut flow: ############" << std::endl;     
		m_logger << INFO << "number of events		                         " << nEvents_ << std::endl;
		m_logger << INFO << "passed trigger		                                 " << nPassedTrigger_ << " --- eff = " << (double)nPassedTrigger_/nEvents_ << std::endl; 
		m_logger << INFO << "found lepton		                                 " << nPassedFoundLept_ << " --- eff = " << (double)nPassedFoundLept_/nEvents_ << std::endl;
		m_logger << INFO << "found MET 		                                 " << nPassedFoundMET_ << " --- eff = " << (double)nPassedFoundMET_/nEvents_ << std::endl;
		m_logger << INFO << "found W 		                                 " << nPassedFoundW_ << " --- eff = " << (double)nPassedFoundW_/nEvents_ << std::endl;
		m_logger << INFO << "found jet candidate with pt cut loose (80 GeV)		 " << nPassedFoundJet_ << " --- eff = " << (double)nPassedFoundJet_/nEvents_ << std::endl;
		m_logger << INFO << "DR(j,l) > 1		                                 " << nPassedLepJetDR_ << " --- eff = " << (double)nPassedLepJetDR_/nEvents_ << std::endl;
		m_logger << INFO << "jet pt cut tight (200 GeV)		                 " << nPassedJetPtTight_ << " --- eff = " << (double)nPassedJetPtTight_/nEvents_ << std::endl;
		m_logger << INFO << "additional jets cut		                         " << nPassedAJetCut_ << " --- eff = " << (double)nPassedAJetCut_/nEvents_ << std::endl;
		m_logger << INFO << "DR(j,l) > pi/2		                                 " << nPassedLepJetDR2_ << " --- eff = " << (double)nPassedLepJetDR2_/nEvents_ << std::endl;
		m_logger << INFO << "Dphi(MET,j) > 2		                                        " << nPassedMETJetDPhi_ << " --- eff = " << (double)nPassedMETJetDPhi_/nEvents_ << std::endl;
		m_logger << INFO << "Dphi(j,W) > 2		                                 " << nPassedJetWDPhi_ << " --- eff = " << (double)nPassedJetWDPhi_/nEvents_ << std::endl;
		m_logger << INFO << "top mass cut		                                 " << nPassedTopMass_ << " --- eff = " << (double)nPassedTopMass_/nEvents_ << std::endl;
		m_logger << INFO << "tau 21 cut		                                 " << nPassedTau21Cut_ << " --- eff = " << (double)nPassedTau21Cut_/nEvents_ << std::endl;
		m_logger << INFO << "jet mass cut		                                 " << nPassedJetMass_ << " --- eff = " << (double)nPassedJetMass_/nEvents_ << std::endl;
		m_logger << INFO << "WH mass window		                                 " << nPassedExoCandidateMass_ << " --- eff = " << (double)nPassedExoCandidateMass_/nEvents_ << std::endl;

		m_logger << INFO << std::endl; 
	}
   
	return;

}

//==============================================================================================
void ExoDiBosonAnalysis::EndCycle() throw( SError ) {

	return;

}

//==============================================================================================
void ExoDiBosonAnalysis::printCutFlow( void ) {
		
	if (Channel_ == "VVdijet"){

		std::cout << std::endl; 
		std::cout << "############ Cut flow: ############" << std::endl;	
		std::cout << "number of events		                         " << nEvents_ << std::endl;
		std::cout << "passed trigger		                             " << nPassedTrigger_ << " --- eff = " << (double)nPassedTrigger_/nEvents_ << std::endl; 
		std::cout << "found at least 2 jets with pT > 30/ eta < 2.4   " << nPassedFoundJets_ << " --- eff = " << (double)nPassedFoundJets_/nEvents_ << std::endl;
		std::cout << "dEta(j,j) < 1.3		                         " << nPassedJetsDEta_ << " --- eff = " << (double)nPassedJetsDEta_/nEvents_ << std::endl;
		std::cout << "M(j,j) > 890 GeV		                         " << nPassedMjj_ << " --- eff = " << (double)nPassedMjj_/nEvents_ << std::endl;
		std::cout << "jet pruned mass cut		                     " << nPassedJetPrunedMass_ << " --- eff = " << (double)nPassedJetPrunedMass_/nEvents_ << std::endl;
		std::cout << "tau 21 cut		                                 " << nPassedTau21Cut_ << " --- eff = " << (double)nPassedTau21Cut_/nEvents_ << std::endl;
   
		std::cout << std::endl; 
	}
		
	else if (Channel_ == "muon" || Channel_ == "electron"){
			
		std::cout << std::endl; 
		std::cout << "############ Cut flow: ############" << std::endl;	
		std::cout << "number of events		                         " << nEvents_ << std::endl;
		std::cout << "passed trigger		                                 " << nPassedTrigger_ << " --- eff = " << (double)nPassedTrigger_/nEvents_ << std::endl; 
		std::cout << "found lepton		                                 " << nPassedFoundLept_ << " --- eff = " << (double)nPassedFoundLept_/nEvents_ << std::endl;
		std::cout << "found MET 		                                 " << nPassedFoundMET_ << " --- eff = " << (double)nPassedFoundMET_/nEvents_ << std::endl;
		std::cout << "found W 		                                 " << nPassedFoundW_ << " --- eff = " << (double)nPassedFoundW_/nEvents_ << std::endl;
		std::cout << "found jet candidate with pt cut loose (80 GeV)		 " << nPassedFoundJet_ << " --- eff = " << (double)nPassedFoundJet_/nEvents_ << std::endl;
		std::cout << "DR(j,l) > 1		                                 " << nPassedLepJetDR_ << " --- eff = " << (double)nPassedLepJetDR_/nEvents_ << std::endl;
		std::cout << "jet pt cut tight (200 GeV)		                 " << nPassedJetPtTight_ << " --- eff = " << (double)nPassedJetPtTight_/nEvents_ << std::endl;
		std::cout << "additional jets cut		                         " << nPassedAJetCut_ << " --- eff = " << (double)nPassedAJetCut_/nEvents_ << std::endl;
		std::cout << "DR(j,l) > pi/2		                                 " << nPassedLepJetDR2_ << " --- eff = " << (double)nPassedLepJetDR2_/nEvents_ << std::endl;
		std::cout << "Dphi(MET,j) > 2		                         " << nPassedMETJetDPhi_ << " --- eff = " << (double)nPassedMETJetDPhi_/nEvents_ << std::endl;
		std::cout << "Dphi(j,W) > 2		                                 " << nPassedJetWDPhi_ << " --- eff = " << (double)nPassedJetWDPhi_/nEvents_ << std::endl;
		std::cout << "top mass cut		                                 " << nPassedTopMass_ << " --- eff = " << (double)nPassedTopMass_/nEvents_ << std::endl;
		std::cout << "tau 21 cut		                                 " << nPassedTau21Cut_ << " --- eff = " << (double)nPassedTau21Cut_/nEvents_ << std::endl;
		std::cout << "jet mass cut		                                 " << nPassedJetMass_ << " --- eff = " << (double)nPassedJetMass_/nEvents_ << std::endl;
		std::cout << "WH mass window		                                 " << nPassedExoCandidateMass_ << " --- eff = " << (double)nPassedExoCandidateMass_/nEvents_ << std::endl;

		std::cout << std::endl; 
	}

   
}	

//==============================================================================================
bool ExoDiBosonAnalysis::run4Synch( void ){

	bool DEBUG = false;
      
	/************ reset variables *************/   
	run = data_.EVENT_run;
	event = data_.EVENT_event;
	lumi = data_.EVENT_lumi;
	nPV = data_.nPVs;
	l_eta = -99;
	l_phi = -99;
	l_pt = -99;
	jet_pt = -99;
	jet_eta = -99;
	jet_phi = -99;
	jet_mass_pruned = -99;
	jet_mass_softdrop = -99;
	jet_tau2tau1 = -99;
	W_pt = -99;
	W_eta = -99;
	W_phi = -99;
	m_lvj = -99;
	njets = 0;
	jet2_pt = -99;
	jet2_btag = -99;
	jet3_pt = -99;
	jet3_btag = -99;
	nbtag = 0;     
	nLooseEle = 0;
	nLooseMu = 0;

	/************ MET *************/   
	TLorentzVector met;
	met.SetPtEtaPhiE( (*data_.MET_et)[0], 0., (*data_.MET_phi)[0], 0. );
	METCand_.push_back( METCandidate( met ) );
     
	pfMET = (*data_.MET_et)[0];
	pfMETPhi = (*data_.MET_phi)[0];

	/************ leptons *************/      
	std::vector<LeptonCandidate> looseEle_;
	std::vector<LeptonCandidate> looseMu_ ;

	std::vector<LeptonCandidate> muCand_;
	std::vector<LeptonCandidate> eleCand_ ;

	/************ electrons *************/            
	bool foundEle = false;
	bool isgoodele = true;

	for( unsigned int l = 0; l < (data_.lep_pt)->size(); ++l ){
            
		if( DEBUG ) std::cout << "lepton " << l << "/" << (data_.lep_pt)->size() << " is a " << abs((*data_.lep_type)[l]) << std::endl; 
                 
		if( abs((*data_.lep_type)[l]) != 11 ) continue;      
		foundEle = true;
      
		if( (*data_.lep_isHEEP)[l] != 1 ) continue;      
		if( DEBUG ) std::cout << "isHEEP" << std::endl;
      
		if( (*data_.lep_pt)[l] <= 35. ) continue; /* JEN DEFINITION*/
		if( DEBUG ) std::cout << "is good ele!" << std::endl;    

		TLorentzVector ele; ele.SetPtEtaPhiE( (*data_.lep_pt)[l], (*data_.lep_eta)[l], (*data_.lep_phi)[l], (*data_.lep_e)[l] );      
        
		looseEle_.push_back( LeptonCandidate( ele ) );
      
		if( (*data_.lep_pt)[l] <= 90. ) continue;
		if( DEBUG ) std::cout << "is tight ele!" << std::endl;
      
		eleCand_.push_back( LeptonCandidate( ele ) );
      
	}
      
	if( Channel_ == "electron" && !foundEle ) return false;      
   
	/************ muons *************/         
	bool foundMu = false;
	for( unsigned int l = 0; l < (data_.lep_pt)->size(); ++l ){
   
		if( DEBUG ){ std::cout << "lepton " << l << "/" << (data_.lep_pt)->size() << " is a " << abs((*data_.lep_type)[l]);std::cout << " pt " << (*data_.lep_pt)[l] << std::endl;}
      
		if( abs((*data_.lep_type)[l]) != 13 ) continue;
		foundMu = true;
      
		if( (*data_.lep_isHighPtMuon)[l] != 1 ) continue;      
		if( DEBUG ) std::cout << "isHighPTMuon" << std::endl;

		/* JEN LOOSE MUONS */
		if( (*data_.lep_trackIso)[l]/(*data_.lep_pt)[l] >= 0.1 ) continue; 
		if( DEBUG ) std::cout << "iso cut passed" << std::endl;   
		if( (*data_.lep_pt)[l] <= 20. ) continue;
		if( fabs((*data_.lep_eta)[l]) >= 2.4 ) continue;
		/* JEN LOOSE MUONS */      
		if( DEBUG ) std::cout << "is loose mu" << std::endl;
                  
		TLorentzVector mu; mu.SetPtEtaPhiE( (*data_.lep_pt)[l], (*data_.lep_eta)[l], (*data_.lep_phi)[l], (*data_.lep_e)[l]);  
		looseMu_.push_back( LeptonCandidate(mu) );

		if( (*data_.lep_pt)[l] <= 40. ) continue;
		if( DEBUG ) std::cout << "is tight mu" << std::endl;

		muCand_.push_back( LeptonCandidate(mu) );
      
	}
   
	if( Channel_ == "muon" && !foundMu ) return false;

	nLooseEle = looseEle_.size();
	nLooseMu = looseMu_.size();

	/************ AK8 jets *************/         
	TLorentzVector lep;
	TLorentzVector jet;
  
	bool foundJet = false;   
	bool isgoodjet = true;
      
	for( unsigned int j = 0; j < (data_.jetAK8_pt)->size(); ++j ){
         
		foundJet = true;
		isgoodjet = true;

		jet.SetPtEtaPhiE( (*data_.jetAK8_pt)[j], (*data_.jetAK8_eta)[j], (*data_.jetAK8_phi)[j], (*data_.jetAK8_e)[j] );
      
		if( (*data_.jetAK8_IDLoose)[j] != 1 ) continue;
      
		if( DEBUG ) std::cout << "is loose ID with " << (*data_.jetAK8_pt)[j] << " eta " << (*data_.jetAK8_eta)[j] << std::endl;
      
		for( unsigned int l = 0; l < muCand_.size(); ++l ){
			if( DEBUG ) std::cout << " * muon " << l << "/" <<  muCand_.size() << " dr " << jet.DeltaR(muCand_[l].p4) << std::endl; 
			if( jet.DeltaR(muCand_[l].p4) < 1. ){ isgoodjet = false; break;}
		}
      
		if( !isgoodjet ) continue;
		if( DEBUG ) std::cout << "is cleaned by muons" << std::endl;

		isgoodjet = true;
      
		for( unsigned int l = 0; l < eleCand_.size(); ++l ){
			if( DEBUG ) std::cout << " * ele " << l << "/" <<  eleCand_.size() << " dr " << jet.DeltaR(eleCand_[l].p4) << std::endl;
			if( jet.DeltaR(eleCand_[l].p4) < 1. ){ isgoodjet = false; break;}
		}
      
		if( !isgoodjet ) continue;
		if( DEBUG ) std::cout << "is cleaned by electrons" << std::endl;
      
		//if( fabs((*data_.jetAK8_eta)[j]) >= 2.4 ) continue; /* JEN DEFINITION*/
      
		JetCandidate jetC(jet);
		jetC.csv = (*data_.jetAK8_csv)[j];
		jetC.tau1 = (*data_.jetAK8_tau1)[j];
		jetC.tau2 = (*data_.jetAK8_tau2)[j];
		jetC.prunedMass = (*data_.jetAK8_prunedmassUnCorr)[j];
		jetC.softdropMass = (*data_.jetAK8_softdropmassUnCorr)[j];      
		Vcand.push_back(jetC);
      
	}

	if( !foundJet ) return false;

	/************ AK4 jets *************/         
	bool isnotfatjet = true; 
                	                
	for( unsigned int j = 0; j < (data_.jetAK4_pt)->size(); ++j ){ 
         
		isgoodjet = true;
		isnotfatjet = true;
      
		jet.SetPtEtaPhiE( (*data_.jetAK4_pt)[j], (*data_.jetAK4_eta)[j], (*data_.jetAK4_phi)[j], (*data_.jetAK4_e)[j] );

		if( DEBUG ) std::cout << "AK4 " << j << "/" << (data_.jetAK4_pt)->size() << " pt " << (*data_.jetAK4_pt)[j];
		if( DEBUG )std::cout << " eta " << (*data_.jetAK4_eta)[j] << std::endl;      

		if( Vcand.size() != 0 && jet.DeltaR(Vcand[0].p4) < 0.8 ){isnotfatjet = false;}/* JEN DEFINITION */
      
		if( !isnotfatjet ) continue;   
		if( DEBUG ) std::cout << "   * AK4 is cleaned by fat jet" << std::endl;   
		if( (*data_.jetAK4_IDLoose)[j] != 1 ) continue;
		if( DEBUG ) std::cout << "   * AK4 is id loose" << std::endl;
      
		for( unsigned int l = 0; l < muCand_.size(); ++l ){
			if( DEBUG ) std::cout << " * muon " << l << "/" <<  muCand_.size() << std::endl; 
			if( jet.DeltaR(muCand_[l].p4) < 0.3 ){ isgoodjet = false; break;} /* JEN DEFINITION */
		}
      
		if( !isgoodjet ) continue;
		if( DEBUG ) std::cout << "   * AK4 is cleaned by muons" << std::endl;

		isgoodjet = true;
      
		for( unsigned int l = 0; l < eleCand_.size(); ++l ){
			if( DEBUG ) std::cout << " * ele " << l << "/" <<  eleCand_.size() << std::endl; 
			if( jet.DeltaR(eleCand_[l].p4) < 0.3 ){ isgoodjet = false; break;} /* JEN DEFINITION */
		}
      
		if( !isgoodjet ) continue;
		if( DEBUG ) std::cout << "   * AK4 is cleaned by electrons" << std::endl;
      
		if( (*data_.jetAK4_pt)[j] <= 30. ) continue; /* JEN DEFINITION */
		if( fabs((*data_.jetAK4_eta)[j]) >= 2.4 ) continue; /* JEN DEFINITION */
		if( DEBUG ) std::cout << "   * AK4 is high pt and central" << std::endl;
      
		JetCandidate Ajet(jet);
		Ajet.csv = (*data_.jetAK4_csv)[j];
		AK4jetCand_.push_back(Ajet);
      
	}

	/************ fill variables *************/         
	if( Channel_ == "muon" && muCand_.size() != 0 ) leptonCand_.push_back(muCand_[0]); 
	if( Channel_ == "electron" && eleCand_.size() != 0 ) leptonCand_.push_back(eleCand_[0]);
   
	if( leptonCand_.size() != 0 ){
		l_pt = leptonCand_[0].p4.Pt();
		l_eta = leptonCand_[0].p4.Eta();
		l_phi = leptonCand_[0].p4.Phi();
	}

	if( Vcand.size() != 0 ){
		jet_pt = Vcand[0].p4.Pt();
		jet_eta = Vcand[0].p4.Eta();
		jet_phi = Vcand[0].p4.Phi();
		jet_mass_pruned = Vcand[0].prunedMass;
		jet_mass_softdrop = Vcand[0].softdropMass;
		jet_tau2tau1 = Vcand[0].tau2/Vcand[0].tau1;
	}

	njets = AK4jetCand_.size();
	if( njets != 0 ){
		jet2_pt = AK4jetCand_[0].p4.Pt();
		jet2_btag = AK4jetCand_[0].csv;
		if( njets > 1 ){
			jet3_pt = AK4jetCand_[1].p4.Pt();
			jet3_btag = AK4jetCand_[1].csv;
		}
	}

	for( unsigned int j = 0; j < AK4jetCand_.size(); ++j ){
		if( AK4jetCand_[j].csv > bTagWPmap_[BtagVetoWP_] ) nbtag++;
	}    

	if( leptonCand_.size() != 0 ){
		TLorentzVector W;
		W = METCand_[0].p4+leptonCand_[0].p4;
		WCand_.push_back( W );

		W_pt = (leptonCand_[0].p4+METCand_[0].p4).Pt();
		W_eta = WCand_[0].p4.Eta();
		W_phi = WCand_[0].p4.Phi();
	}

	if( WCand_.size() != 0 && Vcand.size() != 0 ){
		findExoCandidate();      
		m_lvj = MVV;
	}
   
	return true;        
}
//==============================================================================================




//==============================================================================================
//Efficiency studies============================================================================
//==============================================================================================

void ExoDiBosonAnalysis::doLeptonRecoEfficiency( void ) {

	int pdgid = 0;
	if( Channel_ == "muon" ) pdgid = 13;
	else if( Channel_ == "electron" ) pdgid = 11;
   
	TLorentzVector recoLept;
	TLorentzVector genLept;
   
	float dRhadr;
	float dRtmp;
	float dRmin = 999;
	bool foundMatch = false;
	unsigned int index = 99;
	std::map<int,TLorentzVector>::iterator it = genCandidates_.find(pdgid)!=genCandidates_.end() ? genCandidates_.find(pdgid) : genCandidates_.find(-pdgid);
	for( unsigned int l = 0; l < (data_.lep_pt)->size(); ++l ){
		if( abs((*data_.lep_type)[l]) != pdgid ) continue;
		index = l;
		if( it != genCandidates_.end() ){
      
			recoLept.SetPtEtaPhiE( (*data_.lep_pt)[l], (*data_.lep_eta)[l], (*data_.lep_phi)[l], (*data_.lep_e)[l] );	 
			dRtmp = (it->second).DeltaR(recoLept);
			if( dRtmp < dRmin && dRtmp < 0.25 ){
				dRmin = dRtmp;
				foundMatch = true;
				index = l;
				break;
			}
	 	 
		}      
	}

	std::map<int,TLorentzVector>::iterator it2 = it->first<0 ? genCandidates_.find(-24) : genCandidates_.find(24) ;

	for( unsigned int l = 0; l < (data_.lep_pt)->size(); ++l ){
		if( abs((*data_.lep_type)[l]) == pdgid && it != genCandidates_.end() && (*data_.lep_pt)[l] > 35. ){
      
			recoLept.SetPtEtaPhiE( (*data_.lep_pt)[l], (*data_.lep_eta)[l], (*data_.lep_phi)[l], (*data_.lep_e)[l] );

			dRhadr = (it2->second).DeltaR(recoLept);
	 
			if( dRhadr < 1. ) continue;
	 
			Hist( "leptonRecoGenDR" )->Fill((it->second).DeltaR(recoLept));
			Hist( "leptonRecoGenDPT" )->Fill( (recoLept.Pt()-(it->second).Pt())/(it->second).Pt() );
	 
			break;
	 
		}
	}
   	 
	if( it != genCandidates_.end() ){
		Hist( "leptonRecoEffPTden"  )->Fill( (it->second).Pt() );
		Hist( "leptonRecoEffEtaden" )->Fill( (it->second).Eta() );
	}
	if( foundMatch ){
		Hist( "leptonRecoEffPT" )->Fill( (it->second).Pt() );
		Hist( "leptonRecoEffEta" )->Fill( (it->second).Eta() );
	}
   
	dRmin = 999;
	foundMatch = false;
	for( unsigned int l = 0; l < (data_.lep_pt)->size(); ++l ){
   
		if( Channel_ == "electron" && ( (it->second).Pt() <= leptPtCut_ || (fabs((it->second).Eta()) >= 1.4442 && fabs((it->second).Eta()) <= 1.566) ||
			fabs((it->second).Eta()) >= 2.5) ) break;  
          
		if( abs((*data_.lep_type)[l]) != pdgid ) continue;
      
		if( (*data_.lep_pt)[l] <= leptPtCut_ ) continue;
      
		recoLept.SetPtEtaPhiE( (*data_.lep_pt)[l], (*data_.lep_eta)[l], (*data_.lep_phi)[l], (*data_.lep_e)[l] );	 
		dRtmp = (it->second).DeltaR(recoLept);      
		if( dRtmp < dRmin && dRtmp < 0.25 ){
			dRmin = dRtmp;
			foundMatch = true;
			index = l;
		}
		if( !foundMatch ) continue;
      
		Hist( "leptonIDEffPTden" )->Fill( (*data_.lep_pt)[l] );
		Hist( "leptonIDEffEtaden" )->Fill( (*data_.lep_eta)[l] );
		if( (Channel_ == "electron" && (*data_.lep_isHEEPv50)[l] == 1) || (Channel_=="muon" && (*data_.lep_isHighPtMuon)[l] == 1) ){
			Hist( "leptonIDEffPT" )->Fill( (*data_.lep_pt)[l] );   
			Hist( "leptonIDEffEta" )->Fill( (*data_.lep_eta)[l] ); 
			break; 
		}
		/*recoLept.SetPtEtaPhiE( (*data_.lep_pt)[l], (*data_.lep_eta)[l], (*data_.lep_phi)[l], (*data_.lep_e)[l] );
		dRhadr = (it2->second).DeltaR(recoLept);
		if( dRhadr < 1. ) continue;
		Hist( "leptonIDEffPTden" )->Fill( (*data_.lep_pt)[l] ); 
		Hist( "leptonIDEffEtaden" )->Fill( (*data_.lep_eta)[l] );
		if( (Channel_ == "electron" && (*data_.lep_isHEEP)[l] == 1) || (Channel_=="muon" && (*data_.lep_isHighPtMuon)[l] == 1) ){
		Hist( "leptonIDEffPT" )->Fill( (*data_.lep_pt)[l] );   
		Hist( "leptonIDEffEta" )->Fill( (*data_.lep_eta)[l] ); 
		break; 
		}*/
	}

	dRmin = 999;
	foundMatch = false;
	for( unsigned int l = 0; l < (data_.lep_pt)->size(); ++l ){ 
         
		if( abs((*data_.lep_type)[l]) != pdgid ) continue;
		if( (Channel_ == "electron" && (*data_.lep_isHEEPv50)[l] != 1) || (Channel_ == "muon" && (*data_.lep_isHighPtMuon)[l] != 1) ) continue;
		//if( (Channel_ == "electron" && (*data_.lep_pt)[l] < 95.) || (Channel_ == "muon" && (*data_.lep_pt)[l] < 40.) ) continue;
            
		Hist( "leptonTriggerEffPTden" )->Fill( (*data_.lep_pt)[l] );
		Hist( "leptonTriggerEffEtaden" )->Fill( (*data_.lep_eta)[l] );
		if( (Channel_ == "electron" && data_.isFired_HLT_Ele95_CaloIdVT_GsfTrkIdT_v1) || (Channel_=="muon" && data_.isFired_HLT_Mu40_v1) ){
			Hist( "leptonTriggerEffPT" )->Fill( (*data_.lep_pt)[l] );   
			Hist( "leptonTriggerEffEta" )->Fill( (*data_.lep_eta)[l] ); 
			break; 
		}
	}
	return;     
}

//==============================================================================================
void ExoDiBosonAnalysis::doJetRecoEfficiency( void ){
	
	Mjj = ( Vcand[0].p4 + Vcand[1].p4 ).M();
	//********************** denominators *************************// 	
	Hist( "TriggerEffDen" ) ->Fill( Mjj);
	
	if( Mjj > MjjCut_ && (Vcand[0].prunedMass 	> 30 || Vcand[1].prunedMass		> 30) )	Hist( "TriggerEffPrunedMassDen"  ) ->Fill( Vcand[0].prunedMass   );
	if( Mjj > MjjCut_ && (Vcand[0].softdropMass	> 30 || Vcand[1].softdropMass > 30) )	Hist( "TriggerEffSoftdropMassDen") ->Fill( Vcand[0].softdropMass );
	// if( Mjj > )	Hist( "TriggerEffPrunedMassDen"  ) ->Fill( Vcand[0].prunedMass   );
	// if( Mjj > )	Hist( "TriggerEffSoftdropMassDen") ->Fill( Vcand[0].softdropMass );
	
	if( ( Vcand[0].prunedMass		> mPMLow_ && Vcand[0].prunedMass		< mPMHigh_ ) && ( Vcand[1].prunedMass		> mPMLow_ && Vcand[1].prunedMass		< mPMHigh_ ) )Hist( "TriggerEffPruningCut"				)->Fill ( Mjj );
	if( ( Vcand[0].softdropMass > mSDLow_ && Vcand[0].softdropMass	< mSDHigh_ ) && ( Vcand[1].softdropMass	> mSDLow_ && Vcand[1].softdropMass	< mSDHigh_ ) )Hist( "TriggerEffSoftdropCut"				)->Fill ( Mjj );
	if( ( Vcand[0].prunedMass		> mPMLow_ && Vcand[0].prunedMass		< mPMHigh_ ) || ( Vcand[1].prunedMass		> mPMLow_ && Vcand[1].prunedMass		< mPMHigh_ ) )Hist( "TriggerEffPruningCut_qstar"	)->Fill ( Mjj );
	if( ( Vcand[0].softdropMass > mSDLow_ && Vcand[0].softdropMass	< mSDHigh_ ) || ( Vcand[1].softdropMass	> mSDLow_ && Vcand[1].softdropMass	< mSDHigh_ ) )Hist( "TriggerEffSoftdropCut_qstar"	)->Fill ( Mjj );
	
	if( ( Vcand[0].tau2/Vcand[0].tau1 > Tau21Low_ && Vcand[0].tau2/Vcand[0].tau1 < Tau21High_ ) && ( Vcand[1].tau2/Vcand[1].tau1 > Tau21Low_ && Vcand[1].tau2/Vcand[1].tau1 < Tau21High_ ) )Hist( "TriggerEffTau21Cut"				)->Fill ( Mjj );
	if( ( Vcand[0].tau2/Vcand[0].tau1 > Tau21Low_ && Vcand[0].tau2/Vcand[0].tau1 < Tau21High_ ) || ( Vcand[1].tau2/Vcand[1].tau1 > Tau21Low_ && Vcand[1].tau2/Vcand[1].tau1 < Tau21High_ ) )Hist( "TriggerEffTau21Cut_qstar"	)->Fill ( Mjj );
  
	//*************** HLT_AK8PFJet360_TrimMass30 ***************//
		
	if( data_.isFired_HLT_AK8PFJet360_TrimMass30_v1 ){
		
		Hist( "TriggerEff_HLT_AK8PFJet360_TrimMass30" )->Fill ( Mjj );
		if( ( Vcand[0].prunedMass		> mPMLow_ && Vcand[0].prunedMass		< mPMHigh_ ) && ( Vcand[1].prunedMass		> mPMLow_ && Vcand[1].prunedMass		< mPMHigh_	) )	Hist( "TriggerEff_HLT_AK8PFJet360_TrimMass30_wPruningCut"				)->Fill ( Mjj );	  
		if( ( Vcand[0].softdropMass	> mSDLow_ && Vcand[0].softdropMass	< mSDHigh_ ) && ( Vcand[1].softdropMass	> mSDLow_ && Vcand[1].softdropMass	< mSDHigh_	) )	Hist( "TriggerEff_HLT_AK8PFJet360_TrimMass30_wSoftdropCut"			)->Fill ( Mjj );	  
		if( ( Vcand[0].prunedMass		> mPMLow_ && Vcand[0].prunedMass		< mPMHigh_ ) || ( Vcand[1].prunedMass		> mPMLow_ && Vcand[1].prunedMass		< mPMHigh_	) )	Hist( "TriggerEff_HLT_AK8PFJet360_TrimMass30_wPruningCut_qstar"	)->Fill ( Mjj );	  
		if( ( Vcand[0].softdropMass	> mSDLow_ && Vcand[0].softdropMass	< mSDHigh_ ) || ( Vcand[1].softdropMass	> mSDLow_ && Vcand[1].softdropMass	< mSDHigh_	) )	Hist( "TriggerEff_HLT_AK8PFJet360_TrimMass30_wSoftdropCut_qstar")->Fill ( Mjj );
		
		if( ( Vcand[0].tau2/Vcand[0].tau1 > Tau21Low_ && Vcand[0].tau2/Vcand[0].tau1 < Tau21High_ ) && ( Vcand[1].tau2/Vcand[1].tau1 > Tau21Low_ && Vcand[1].tau2/Vcand[1].tau1 < Tau21High_ ) )Hist( "TriggerEff_HLT_AK8PFJet360_TrimMass30_wTau21Cut"  )->Fill ( Mjj );
	  
		if( Mjj > MjjCut_ && (Vcand[0].prunedMass		> 30 || Vcand[1].prunedMass		> 30) ) Hist( "TriggerEffPrunedMass_HLT_AK8PFJet360_TrimMass30_wMjjCut"			)->Fill ( Vcand[0].prunedMass		);
		if( Mjj > MjjCut_ && (Vcand[0].softdropMass	> 30 || Vcand[1].softdropMass	> 30) ) Hist( "TriggerEffSoftdropMass_HLT_AK8PFJet360_TrimMass30_wMjjCut"		)->Fill ( Vcand[0].softdropMass	);
	}
	
	//***************HLT_AK8PFHT700_TrimR0p1PT0p03Mass50_v1 ***************// 
	if( data_.isFired_HLT_AK8PFHT700_TrimR0p1PT0p03Mass50_v1 ){
		
		Hist( "TriggerEff_HLT_AK8PFHT700_TrimR0p1PT0p03Mass50" )->Fill ( Mjj );
		if( ( Vcand[0].prunedMass		> mPMLow_ && Vcand[0].prunedMass		< mPMHigh_ ) && ( Vcand[1].prunedMass		> mPMLow_ && Vcand[1].prunedMass		< mPMHigh_	) )	Hist( "TriggerEff_HLT_AK8PFHT700_TrimR0p1PT0p03Mass50_wPruningCut"				)->Fill ( Mjj );	  
		if( ( Vcand[0].softdropMass	> mSDLow_ && Vcand[0].softdropMass	< mSDHigh_ ) && ( Vcand[1].softdropMass	> mSDLow_ && Vcand[1].softdropMass	< mSDHigh_	) )	Hist( "TriggerEff_HLT_AK8PFHT700_TrimR0p1PT0p03Mass50_wSoftdropCut"			)->Fill ( Mjj );	  
		if( ( Vcand[0].prunedMass		> mPMLow_ && Vcand[0].prunedMass		< mPMHigh_ ) || ( Vcand[1].prunedMass		> mPMLow_ && Vcand[1].prunedMass		< mPMHigh_	) )	Hist( "TriggerEff_HLT_AK8PFHT700_TrimR0p1PT0p03Mass50_wPruningCut_qstar"		)->Fill ( Mjj );	  
		if( ( Vcand[0].softdropMass	> mSDLow_ && Vcand[0].softdropMass	< mSDHigh_ ) || ( Vcand[1].softdropMass	> mSDLow_ && Vcand[1].softdropMass	< mSDHigh_	) )	Hist( "TriggerEff_HLT_AK8PFHT700_TrimR0p1PT0p03Mass50_wSoftdropCut_qstar"	)->Fill ( Mjj );
		
		if( ( Vcand[0].tau2/Vcand[0].tau1 > Tau21Low_ && Vcand[0].tau2/Vcand[0].tau1 < Tau21High_ ) && ( Vcand[1].tau2/Vcand[1].tau1 > Tau21Low_ && Vcand[1].tau2/Vcand[1].tau1 < Tau21High_ ) )Hist( "TriggerEff_HLT_AK8PFHT700_TrimR0p1PT0p03Mass50_wTau21Cut"  )->Fill ( Mjj );
	  
		if( Mjj > MjjCut_ && (Vcand[0].prunedMass		> 30 || Vcand[1].prunedMass		> 30) ) Hist( "TriggerEffPrunedMass_HLT_AK8PFHT700_TrimR0p1PT0p03Mass50_wMjjCut"		)->Fill ( Vcand[0].prunedMass		);
		if( Mjj > MjjCut_ && (Vcand[0].softdropMass	> 30 || Vcand[1].softdropMass	> 30) ) Hist( "TriggerEffSoftdropMass_HLT_AK8PFHT700_TrimR0p1PT0p03Mass50_wMjjCut"	)->Fill ( Vcand[0].softdropMass	);
	}
	//***************HLT_AK8DiPFJet280_200_TrimMass30_BTagCSV0p41_v1 ***************// 
	if( data_.isFired_HLT_AK8DiPFJet280_200_TrimMass30_BTagCSV0p41_v1 ){
		
		Hist( "TriggerEff_HLT_AK8DiPFJet280_200_TrimMass30_BTagCSV0p41" )->Fill ( Mjj );
		if( ( Vcand[0].prunedMass		> mPMLow_ && Vcand[0].prunedMass		< mPMHigh_ ) && ( Vcand[1].prunedMass		> mPMLow_ && Vcand[1].prunedMass		< mPMHigh_	) )	Hist( "TriggerEff_HLT_AK8DiPFJet280_200_TrimMass30_BTagCSV0p41_wPruningCut"				)->Fill ( Mjj );	  
		if( ( Vcand[0].softdropMass	> mSDLow_ && Vcand[0].softdropMass	< mSDHigh_ ) && ( Vcand[1].softdropMass	> mSDLow_ && Vcand[1].softdropMass	< mSDHigh_	) )	Hist( "TriggerEff_HLT_AK8DiPFJet280_200_TrimMass30_BTagCSV0p41_wSoftdropCut"			)->Fill ( Mjj );	  
		if( ( Vcand[0].prunedMass		> mPMLow_ && Vcand[0].prunedMass		< mPMHigh_ ) || ( Vcand[1].prunedMass		> mPMLow_ && Vcand[1].prunedMass		< mPMHigh_	) )	Hist( "TriggerEff_HLT_AK8DiPFJet280_200_TrimMass30_BTagCSV0p41_wPruningCut_qstar"		)->Fill ( Mjj );	  
		if( ( Vcand[0].softdropMass	> mSDLow_ && Vcand[0].softdropMass	< mSDHigh_ ) || ( Vcand[1].softdropMass	> mSDLow_ && Vcand[1].softdropMass	< mSDHigh_	) )	Hist( "TriggerEff_HLT_AK8DiPFJet280_200_TrimMass30_BTagCSV0p41_wSoftdropCut_qstar"	)->Fill ( Mjj );
		
		if( ( Vcand[0].tau2/Vcand[0].tau1 > Tau21Low_ && Vcand[0].tau2/Vcand[0].tau1 < Tau21High_ ) && ( Vcand[1].tau2/Vcand[1].tau1 > Tau21Low_ && Vcand[1].tau2/Vcand[1].tau1 < Tau21High_ ) )Hist( "TriggerEff_HLT_AK8DiPFJet280_200_TrimMass30_BTagCSV0p41_wTau21Cut"  )->Fill ( Mjj );
	  
		if( Mjj > MjjCut_ && (Vcand[0].prunedMass		> 30 || Vcand[1].prunedMass	> 30) ) Hist( "TriggerEffPrunedMass_HLT_AK8DiPFJet280_200_TrimMass30_BTagCSV0p41_wMjjCut"			)->Fill ( Vcand[0].prunedMass		);
		if( Mjj > MjjCut_ && (Vcand[0].softdropMass	> 30 || Vcand[1].softdropMass	> 30) ) Hist( "TriggerEffSoftdropMass_HLT_AK8DiPFJet280_200_TrimMass30_BTagCSV0p41_wMjjCut"	)->Fill ( Vcand[0].softdropMass	);
	}
	
	//************************* HLT_PFHT900 **********************// 
	if( data_.isFired_HLT_PFHT900_v1 ){
		
		Hist( "TriggerEff_HLT_PFHT900" )->Fill ( Mjj );
  
		if( ( Vcand[0].prunedMass		> mPMLow_ && Vcand[0].prunedMass		< mPMHigh_ ) && ( Vcand[1].prunedMass		> mPMLow_ && Vcand[1].prunedMass		< mPMHigh_ ) )	Hist( "TriggerEff_HLT_PFHT900_wPruningCut"	)->Fill ( Mjj );
		if( ( Vcand[0].prunedMass		> mPMLow_ && Vcand[0].prunedMass		< mPMHigh_ ) || ( Vcand[1].prunedMass		> mPMLow_ && Vcand[1].prunedMass		< mPMHigh_ ) )	Hist( "TriggerEff_HLT_PFHT900_wPruningCut_qstar"	)->Fill ( Mjj );
		if( ( Vcand[0].softdropMass	> mSDLow_ && Vcand[0].softdropMass	< mSDHigh_ ) && ( Vcand[1].softdropMass	> mSDLow_ && Vcand[1].softdropMass	< mSDHigh_ ) )	Hist( "TriggerEff_HLT_PFHT900_wSoftdropCut"	)->Fill ( Mjj );
	
		if( ( Vcand[0].tau2/Vcand[0].tau1 > Tau21Low_ && Vcand[0].tau2/Vcand[0].tau1 < Tau21High_ ) && ( Vcand[1].tau2/Vcand[1].tau1 > Tau21Low_ && Vcand[1].tau2/Vcand[1].tau1 < Tau21High_ ) )Hist( "TriggerEff_HLT_PFHT900_wTau21Cut" )->Fill ( Mjj );
	}
	
	//************************* HLT_PFHT650_WideJetMJJ950DEtaJJ1p5 **********************// 
	if( data_.isFired_HLT_PFHT650_WideJetMJJ950DEtaJJ1p5_v1 ){
		
		Hist( "TriggerEff_HLT_PFHT650_WideJetMJJ950DEtaJJ1p5" )->Fill ( Mjj );
  
		if( ( Vcand[0].prunedMass		> mPMLow_ && Vcand[0].prunedMass		< mPMHigh_ ) && ( Vcand[1].prunedMass		> mPMLow_ && Vcand[1].prunedMass		< mPMHigh_ ) )	Hist( "TriggerEff_HLT_PFHT650_WideJetMJJ950DEtaJJ1p5_wPruningCut"	)->Fill ( Mjj );
		if( ( Vcand[0].prunedMass		> mPMLow_ && Vcand[0].prunedMass		< mPMHigh_ ) || ( Vcand[1].prunedMass		> mPMLow_ && Vcand[1].prunedMass		< mPMHigh_ ) )	Hist( "TriggerEff_HLT_PFHT650_WideJetMJJ950DEtaJJ1p5_wPruningCut_qstar"	)->Fill ( Mjj );
		if( ( Vcand[0].softdropMass	> mSDLow_ && Vcand[0].softdropMass	< mSDHigh_ ) && ( Vcand[1].softdropMass	> mSDLow_ && Vcand[1].softdropMass	< mSDHigh_ ) )	Hist( "TriggerEff_HLT_PFHT650_WideJetMJJ950DEtaJJ1p5_wSoftdropCut")->Fill ( Mjj );
	
		if( ( Vcand[0].tau2/Vcand[0].tau1 > Tau21Low_ && Vcand[0].tau2/Vcand[0].tau1 < Tau21High_ ) && ( Vcand[1].tau2/Vcand[1].tau1 > Tau21Low_ && Vcand[1].tau2/Vcand[1].tau1 < Tau21High_ ) )Hist( "TriggerEff_HLT_PFHT650_WideJetMJJ950DEtaJJ1p5_wTau21Cut" )->Fill ( Mjj );
	}
	//************************* HLT_PFHT650_WideJetMJJ900DEtaJJ1p5 **********************// 
	if( data_.isFired_HLT_PFHT650_WideJetMJJ900DEtaJJ1p5_v1 ){
		
		Hist( "TriggerEff_HLT_PFHT650_WideJetMJJ900DEtaJJ1p5" )->Fill ( Mjj );
  
		if( ( Vcand[0].prunedMass		> mPMLow_ && Vcand[0].prunedMass		< mPMHigh_ ) && ( Vcand[1].prunedMass		> mPMLow_ && Vcand[1].prunedMass		< mPMHigh_ ) )	Hist( "TriggerEff_HLT_PFHT650_WideJetMJJ900DEtaJJ1p5_wPruningCut"	)->Fill ( Mjj );
		if( ( Vcand[0].prunedMass		> mPMLow_ && Vcand[0].prunedMass		< mPMHigh_ ) || ( Vcand[1].prunedMass		> mPMLow_ && Vcand[1].prunedMass		< mPMHigh_ ) )	Hist( "TriggerEff_HLT_PFHT650_WideJetMJJ900DEtaJJ1p5_wPruningCut_qstar"	)->Fill ( Mjj );
		if( ( Vcand[0].softdropMass	> mSDLow_ && Vcand[0].softdropMass	< mSDHigh_ ) && ( Vcand[1].softdropMass	> mSDLow_ && Vcand[1].softdropMass	< mSDHigh_ ) )	Hist( "TriggerEff_HLT_PFHT650_WideJetMJJ900DEtaJJ1p5_wSoftdropCut"	)->Fill ( Mjj );
	
		if( ( Vcand[0].tau2/Vcand[0].tau1 > Tau21Low_ && Vcand[0].tau2/Vcand[0].tau1 < Tau21High_ ) && ( Vcand[1].tau2/Vcand[1].tau1 > Tau21Low_ && Vcand[1].tau2/Vcand[1].tau1 < Tau21High_ ) )Hist( "TriggerEff_HLT_PFHT650_WideJetMJJ900DEtaJJ1p5_wTau21Cut" )->Fill ( Mjj );
	}
  
	//**************************** OR HT only ****************************//
  
	if( data_.isFired_HLT_PFHT650_WideJetMJJ950DEtaJJ1p5_v1 || data_.isFired_HLT_PFHT650_WideJetMJJ900DEtaJJ1p5_v1 || data_.isFired_HLT_PFHT900_v1  ){
	  
		Hist( "TriggerEff_HT" )->Fill ( Mjj );
  
		if( ( Vcand[0].prunedMass		> mPMLow_ && Vcand[0].prunedMass		< mPMHigh_ ) && ( Vcand[1].prunedMass		> mPMLow_ && Vcand[1].prunedMass		< mPMHigh_ ) )	Hist( "TriggerEff_HT_wPruningCut"				)->Fill ( Mjj );		
		if( ( Vcand[0].softdropMass	> mSDLow_ && Vcand[0].softdropMass	< mSDHigh_ ) && ( Vcand[1].softdropMass	> mSDLow_ && Vcand[1].softdropMass	< mSDHigh_ ) )	Hist( "TriggerEff_HT_wSoftdropCut"			)->Fill ( Mjj );	  
		if( ( Vcand[0].prunedMass		> mPMLow_ && Vcand[0].prunedMass		< mPMHigh_ ) || ( Vcand[1].prunedMass		> mPMLow_ && Vcand[1].prunedMass		< mPMHigh_ ) )	Hist( "TriggerEff_HT_wPruningCut_qstar"	)->Fill ( Mjj );
		if( ( Vcand[0].softdropMass	> mSDLow_ && Vcand[0].softdropMass	< mSDHigh_ ) || ( Vcand[1].softdropMass	> mSDLow_ && Vcand[1].softdropMass	< mSDHigh_ ) )	Hist( "TriggerEff_HT_wSoftdropCut_qstar")->Fill ( Mjj );

		if( ( Vcand[0].tau2/Vcand[0].tau1 > Tau21Low_ && Vcand[0].tau2/Vcand[0].tau1 < Tau21High_ ) && ( Vcand[1].tau2/Vcand[1].tau1 > Tau21Low_ && Vcand[1].tau2/Vcand[1].tau1 < Tau21High_ ) )Hist( "TriggerEff_HT_wTau21Cut" )->Fill ( Mjj );
	}
	
	//**************************** OR trimmed only ****************************//
	if( data_.isFired_HLT_AK8DiPFJet280_200_TrimMass30_BTagCSV0p41_v1 || data_.isFired_HLT_AK8PFHT700_TrimR0p1PT0p03Mass50_v1 || data_.isFired_HLT_AK8PFJet360_TrimMass30_v1){
		if( ( Vcand[0].prunedMass		> mPMLow_ && Vcand[0].prunedMass		< mPMHigh_ ) || ( Vcand[1].prunedMass		> mPMLow_ && Vcand[1].prunedMass		< mPMHigh_ ) )	Hist( "TriggerEff_trimmed_wPruningCut_qstar"		)->Fill( Mjj);
		if( ( Vcand[0].prunedMass		> mPMLow_ && Vcand[0].prunedMass		< mPMHigh_ ) && ( Vcand[1].prunedMass		> mPMLow_ && Vcand[1].prunedMass		< mPMHigh_ ) )	Hist( "TriggerEff_trimmed_wPruningCut"		)->Fill( Mjj);
		if( ( Vcand[0].softdropMass	> mSDLow_ && Vcand[0].softdropMass	< mSDHigh_ ) && ( Vcand[1].softdropMass	> mSDLow_ && Vcand[1].softdropMass	< mSDHigh_ ) )	Hist( "TriggerEff_trimmed_wSoftdropCut"	)->Fill( Mjj	);
		if( ( Vcand[0].softdropMass	> mSDLow_ && Vcand[0].softdropMass	< mSDHigh_ ) || ( Vcand[1].softdropMass	> mSDLow_ && Vcand[1].softdropMass	< mSDHigh_ ) )	Hist( "TriggerEff_trimmed_wSoftdropCut_qstar"	)->Fill( Mjj	);
	}  
	
	//**************************** OR ****************************//
  
	if( data_.isFired_HLT_AK8PFJet360_TrimMass30_v1 || data_.isFired_HLT_AK8PFHT700_TrimR0p1PT0p03Mass50_v1 || data_.isFired_HLT_AK8DiPFJet280_200_TrimMass30_BTagCSV0p41_v1 || data_.isFired_HLT_PFHT650_WideJetMJJ950DEtaJJ1p5_v1 || data_.isFired_HLT_PFHT650_WideJetMJJ900DEtaJJ1p5_v1 || data_.isFired_HLT_PFHT900_v1  ){
	  
		Hist( "TriggerEff_ALL" )->Fill ( Mjj );
  
		if( ( Vcand[0].prunedMass		> mPMLow_ && Vcand[0].prunedMass		< mPMHigh_ ) && ( Vcand[1].prunedMass		> mPMLow_ && Vcand[1].prunedMass		< mPMHigh_ ) )	Hist( "TriggerEff_ALL_wPruningCut"				)->Fill ( Mjj );		
		if( ( Vcand[0].softdropMass	> mSDLow_ && Vcand[0].softdropMass	< mSDHigh_ ) && ( Vcand[1].softdropMass	> mSDLow_ && Vcand[1].softdropMass	< mSDHigh_ ) )	Hist( "TriggerEff_ALL_wSoftdropCut"			)->Fill ( Mjj );	  
		if( ( Vcand[0].prunedMass		> mPMLow_ && Vcand[0].prunedMass		< mPMHigh_ ) || ( Vcand[1].prunedMass		> mPMLow_ && Vcand[1].prunedMass		< mPMHigh_ ) )	Hist( "TriggerEff_ALL_wPruningCut_qstar"	)->Fill ( Mjj );
		if( ( Vcand[0].softdropMass	> mSDLow_ && Vcand[0].softdropMass	< mSDHigh_ ) || ( Vcand[1].softdropMass	> mSDLow_ && Vcand[1].softdropMass	< mSDHigh_ ) )	Hist( "TriggerEff_ALL_wSoftdropCut_qstar")->Fill ( Mjj );

		if( ( Vcand[0].tau2/Vcand[0].tau1 > Tau21Low_ && Vcand[0].tau2/Vcand[0].tau1 < Tau21High_ ) && ( Vcand[1].tau2/Vcand[1].tau1 > Tau21Low_ && Vcand[1].tau2/Vcand[1].tau1 < Tau21High_ ) )Hist( "TriggerEff_ALL_wTau21Cut" )->Fill ( Mjj );
	}
	
	return;
}
