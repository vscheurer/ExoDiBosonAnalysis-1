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
    , weight_		  (1.)
      , genweight_  (1.)
        , puweight_		(1.)
, lumiweight_	(1.){

  SetLogName( GetName() );
   
  /* general settings */   
  DeclareProperty( "InputTreeName"		, InputTreeName_	);
  DeclareProperty( "OutputTreeName"		, OutputTreeName_	);
  DeclareProperty( "isSignal"         , isSignal_				);
  DeclareProperty( "runOnMC"          , runOnMC_				);
  DeclareProperty( "GenStudies"       , GenStudies_			);
  DeclareProperty( "Channel"          , Channel_				);
  DeclareProperty( "Trigger"          , Trigger_				);
  DeclareProperty( "applyFilters"     , applyFilters_   );
	 
  /* leptonic selections */
  DeclareProperty( "LeptPtCut"			, leptPtCut_			);
  DeclareProperty( "LeptEtaCut"			, leptEtaCut_			);
  DeclareProperty( "AleptPtCut"			, AleptPtCut_			);
  DeclareProperty( "AleptEtaCut"		, AleptEtaCut_		);
  DeclareProperty( "METCut"					, METCut_					);

  /* jet selections */
  DeclareProperty( "MjjCut"						, MjjCut_					);
  DeclareProperty( "dEtaCut"					, dEtaCut_				);
  DeclareProperty( "JetPtCutLoose"		, JetPtCutLoose_	);
  DeclareProperty( "JetPtCutTight"		, JetPtCutTight_	);
  DeclareProperty( "JetEtaCut"        , JetEtaCut_			);  
  DeclareProperty( "Tau21Cut"         , Tau21Cut_				);  
  DeclareProperty( "Tau21HPLow"       , Tau21HPLow_			);
  DeclareProperty( "Tau21HPHigh"			, Tau21HPHigh_		);
  DeclareProperty( "Tau21Low"       	, Tau21Low_			);
  DeclareProperty( "Tau21High"     	 , Tau21High_		);
	        
  /* pruned mass */ 
  DeclareProperty( "UsePruned"        , UsePruned_			);
  DeclareProperty( "mPMLow"						, mPMLow_			);
  DeclareProperty( "mPMHigh"					, mPMHigh_		);
  DeclareProperty( "mSDLow"						, mSDLow_			);
  DeclareProperty( "mSDHigh"					, mSDHigh_		);
	
  /* weights settings */
  DeclareProperty( "xSec"							, xSec_					);
  DeclareProperty( "genEvents"				, genEvents_		);
  DeclareProperty( "Lumi"							, Lumi_					);
  DeclareProperty( "PUdata"						, PUProfileData_    	  );
      
            
  theHistosManager_ = new HistosManager( this );
  theNtupleManager_ = new NtupleManager( this );

  pdgMtop = 171.3;
  pdgMw		= 79.5;   
  pdgWidthtop = 19.1;
  pdgWidthw    = 8.9;
  
  
  nSumGenWeights_           = 0; 
  nEvents_                  = 0;
  nPassedTrigger_           = 0;
  nPassedFilters_           = 0;	      
  nPassedJetPrunedMass_     = 0;
  nPassedTau21Cut_          = 0;  
  nPassedWTag_              = 0;
   
  Mjj                       = 0;
  jetsDeltaEta              = 0;
  nBTags                    = 0;
   
  nPassedFoundJets_				= 0;
  nPassedJetsDEta_				= 0;
  nPassedMjj_             = 0;
  nPassedWtagging_				= 0;
  nPassedFoundLept_				= 0;
  nPassedFoundMET_				= 0;
	
  
  nPassedChi2_          = 0;
  nPassedFoundLept_     = 0;
  nPassedVetoLep_				= 0;
  nPassedFoundMET_      = 0;
  
  nPassed1Jet_					= 0;
  nPassed2Jet_					= 0;
  nPassed3Jet_					= 0;
  nPassed4Jet_					= 0;
  nPassed1bTag_					= 0;
  nPassed2bTag_					= 0;
  
  jetINDX     					= 99;
  
  nPassedFilter_HBHE_                = 0;
  nPassedFilter_CSCHalo_             = 0;
  nPassedFilter_HCALlaser_           = 0;
  nPassedFilter_ECALDeadCell_        = 0;
  nPassedFilter_GoodVtx_             = 0;
  nPassedFilter_TrkFailure_          = 0;
  nPassedFilter_EEBadSc_             = 0;
  nPassedFilter_ECALlaser_           = 0;
  nPassedFilter_TrkPOG_              = 0;
  nPassedFilter_TrkPOG_manystrip_    = 0;
  nPassedFilter_TrkPOG_toomanystrip_ = 0;
  nPassedFilter_TrkPOG_logError_     = 0;
  nPassedFilter_METFilters_          = 0;
  nPassedMETFiltersAll_              = 0;
  nPassedTrkFiltersAll_              = 0;
  nPassedGoodPVFilter_               = 0;
  
   
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

  PUWeight::Scenario sc = PUWeight_.toScenario("PUS25ns");
  PUWeight_.initPUWeights(PUProfileData_,sc);
  
  // TFile* fPUweights = TFile::Open(PUProfileData_.c_str(),"READ");
  // hPUweights_ = (TH1F*)fPUweights->Get("puweights");
   
}

//==============================================================================================
void ExoDiBosonAnalysis::BeginInputFile( const SInputData& ) throw( SError ) {

  theNtupleManager_->ConnectVariables( InputTreeName_, runOnMC_ );
         
  return;
}

//==============================================================================================
void ExoDiBosonAnalysis::BeginInputData( const SInputData& ) throw( SError ) {
	
 
      
  theHistosManager_->bookHistos(Channel_); 
  DeclareVariable( nPV		, "nPV" 	     , OutputTreeName_.c_str() );
  DeclareVariable( MVV                  , "MVV"               , OutputTreeName_.c_str() );
  DeclareVariable( Mj						      	, "Mj"                , OutputTreeName_.c_str() );
  DeclareVariable( jet_mass_pruned      , "jet_mass_pruned"   , OutputTreeName_.c_str() );
  DeclareVariable( jet_mass_softdrop    , "jet_mass_softdrop" , OutputTreeName_.c_str() );
  DeclareVariable( jet_pt               , "jet_pt"            , OutputTreeName_.c_str() );
  DeclareVariable( jet_eta              , "jet_eta"           , OutputTreeName_.c_str() );
  DeclareVariable( jet_deta              , "jet_deta"           , OutputTreeName_.c_str() );
  DeclareVariable( jet_phi              , "jet_phi"			    	, OutputTreeName_.c_str() );
  DeclareVariable( jet_tau2tau1         , "jet_tau2tau1"		  , OutputTreeName_.c_str() );
  DeclareVariable( lumiweight_          , "lumiweight"        , OutputTreeName_.c_str() );
  DeclareVariable( sum_genweights       , "sum_genweights"        , OutputTreeName_.c_str() );
     
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
  genJetCand      .clear();
  Leptonicb_			.clear();
  Hadronicb_			.clear();
  HadronicJ_			.clear();
   
}

//==============================================================================================
void ExoDiBosonAnalysis::setGenCandidates( void ) {
  
  if( !runOnMC_ ) return;
  if( !isSignal_ && !GenStudies_ ) return;

  TLorentzVector genP;   
  double genptV = -99;
  for( unsigned int p = 0; p < (data_.genParticle_pdgId)->size(); ++p ){
    if( (*data_.genParticle_pt).at(p) < 0.1) continue;
    if( (*data_.genParticle_status).at(p) != 4 && (*data_.genParticle_status).at(p) != 22 && (*data_.genParticle_status).at(p) != 23) continue;
    genP.SetPtEtaPhiE( (*data_.genParticle_pt).at(p), (*data_.genParticle_eta).at(p), (*data_.genParticle_phi).at(p), (*data_.genParticle_e).at(p) );
    genCandidates_[ (*data_.genParticle_pdgId).at(p) ] = genP;
  }
                    
  return;
}

//==============================================================================================
void ExoDiBosonAnalysis::setWeight( TString infile ){

  if( !runOnMC_ ) return;

  for( unsigned int v = 0; v < (data_.nPUTrue)->size(); ++v ){
    if( (*data_.bX)[v] == 0 ) puweight_ = PUWeight_.getPUWeight( (*data_.nPUTrue)[v] );
  }

  // if( data_.nPVs <= 52 ){
  //   int bin = hPUweights_->GetXaxis()->FindBin(data_.nPVs);
  //   puweight_ = hPUweights_->GetBinContent(bin);
  // }
         
  double lumiw = xSec_/genEvents_;     
  lumiweight_ = lumiw*LumiWeight_.getLumiWeight( infile )*Lumi_; 
  genweight_ = data_.genWeight < 0 ? -1 : 1; 
      
  weight_ = puweight_*lumiweight_*genweight_;  
  
  // std::cout<<"puweight_ = "<<puweight_<<std::endl;
  //    std::cout<<"lumiweight_ = "<<lumiweight_<<std::endl;
  // std::cout<<"genweight_ = "<<genweight_<<std::endl;
  //  std::cout<<"Weight = "<<weight_<<std::endl;
  
}

//==============================================================================================
void ExoDiBosonAnalysis::ExecuteEvent( const SInputData&, Double_t ) throw( SError ) {
  
	
  // Connect branches in tree
  initData();
  // Reset vectors
  reset();

  ////////////////////////////////////////////////////////////////////////////////////////////////////////
  //// Dijet analysis begins HERE/////////////////////////////////////////////////////////////////////////
  if( Channel_ == "VVdijet" || Channel_ == "qVdijet" ){
    
    TString infile = TString(this->GetHistInputFile()->GetName());
    setWeight(infile);

    if( GenStudies_ ){
      setGenCandidates();
      TLorentzVector genTLV;
      for( int jj = 0; jj < abs((data_.genJetAK8_pt)->size()); ++jj ){
        genTLV.SetPtEtaPhiE( (*data_.genJetAK8_pt)[jj], (*data_.genJetAK8_eta)[jj], (*data_.genJetAK8_phi)[jj], (*data_.genJetAK8_e)[jj] );
        JetCandidate genJet(genTLV);
        genJet.mass= (*data_.genJetAK8_mass)[jj];
        genJet.prunedMass    = (*data_.genJetAK8_prunedmass)[jj]    ;
        genJet.softdropMass  = (*data_.genJetAK8_softdropmass)[jj]  ;
        genJetCand.push_back( genJet );
      }
    }
    if (data_.EVENT_run == 256729 ||data_.EVENT_run == 256734||data_.EVENT_run == 257394 || data_.EVENT_run == 257395) throw SError( SError::SkipEvent );
    Hist( "runNumber" )->Fill(data_.EVENT_run);

    nEvents_++;
    // if( passedFilters() ) nPassedFilters_++;
    //  if( passedTrigger() ) nPassedTrigger_++;

    if( !passedTrigger() ) throw SError( SError::SkipEvent );
    nPassedTrigger_++;  
    if( !passedFilters() ) throw SError( SError::SkipEvent );
    nPassedFilters_++;
    if( passedDijetSelections(infile) ) {
      fillHistos(Channel_);
    }
  }
  
  ////////////////////////////////////////////////////////////////////////////////////////////////////////
  //// SF measurements begins HERE/////////////////////////////////////////////////////////////////////////	

  else if( Channel_ == "SFmuJets"){
    float gW = data_.genWeight < 0 ? -1 : 1; 
    sum_genweights += gW;
    nSumGenWeights_+= gW;
    
    TString infile = TString(this->GetHistInputFile()->GetName());
    setWeight(infile);
    
    Hist( "runNumber" )->Fill(data_.EVENT_run);
    nEvents_++;
    // if( passedFilters() ) nPassedFilters_++;
    // if( passedTrigger() ) nPassedTrigger_++;
    if( !passedTrigger() ) throw SError( SError::SkipEvent );
    nPassedTrigger_++;
        
    if( !passedFilters() ) throw SError( SError::SkipEvent );
    nPassedFilters_++;
    
     
    if( !passedTTbarSelections() ) return;
    if(GenStudies_){
      doGenTTReco();
    }
      
    // findWCandidate();
    TLorentzVector p4nu          = getp4Nu();
    // TLorentzVector p4nuMethod2   = getp4NuMethod2();

    Double_t deltaTmassMin = 999.;
    float chi2Min = 999999.;
    float Tmass = 0;
    float Wmass = 0;

    //Reconstruct hadronic top
    for(int i=0; i < 4; i++ ){
      // Hadronicb_.push_back(AK4jetCand_.at(i));
      for(int j=0; j < 4; j++ ){
        if( i==j) continue;
        float deltaWmass = ((AK4jetCand_.at(i).p4 + AK4jetCand_.at(j).p4).M())-pdgMw;
        for(int k=0; k < 4; k++ ){
          // Hadronicb_.push_back(AK4jetCand_.at(k));
          if( i==j || i==k || j==k) continue;
          float deltaTmass = ((AK4jetCand_.at(i).p4 + AK4jetCand_.at(j).p4 + AK4jetCand_.at(k).p4).M())-pdgMtop;

          float chi2 = pow((deltaTmass/pdgWidthtop),2)+pow((deltaWmass/pdgWidthw),2);
          if(chi2 > chi2Min ) continue;
          Hadronicb_.clear();
          chi2Min = chi2;
          Tmass = (AK4jetCand_.at(i).p4 + AK4jetCand_.at(j).p4 + AK4jetCand_.at(k).p4).M();
          Wmass = (AK4jetCand_.at(i).p4 + AK4jetCand_.at(j).p4).M();
          Hadronicb_.push_back(AK4jetCand_.at(i));
          Hadronicb_.push_back(AK4jetCand_.at(j));
          Hadronicb_.push_back(AK4jetCand_.at(k));       
        }
      }
    }
    
    Hist( "tmass"             )->Fill ( Tmass, weight_ );
    Hist( "wmass"             )->Fill ( Wmass, weight_ );
    Hist( "Chi2"              )->Fill ( chi2Min, weight_ );
    Hist( "Chi2vsTMass"        )->Fill ( chi2Min,Tmass);
    Hist( "Chi2vsWMass"        )->Fill ( chi2Min,Wmass);

    if( chi2Min > 100. ) throw SError( SError::SkipEvent );
    nPassedChi2_++;
    fillHistos(Channel_);
      
    //Reconstruct leptonic top
    for(int i=0; i < 4; i++ ){
      if (AK4jetCand_.at(i).p4.Pt() == Hadronicb_.at(0).p4.Pt() || AK4jetCand_.at(i).p4.Pt() == Hadronicb_.at(1).p4.Pt()  || AK4jetCand_.at(i).p4.Pt() == Hadronicb_.at(2).p4.Pt()) continue;
      Leptonicb_.push_back(AK4jetCand_.at(i));
    }
      
    Double_t mlj = (leptonCand_.at(0).p4 + Leptonicb_.at(0).p4).M();
    Double_t TmassHad    = (Hadronicb_.at(0).p4 + Hadronicb_.at(1).p4 + Hadronicb_.at(2).p4).M();
    Double_t WmassHad    = (Hadronicb_.at(0).p4 + Hadronicb_.at(1).p4).M();
    Double_t TmassLep    = (p4nu + leptonCand_.at(0).p4 + Leptonicb_.at(0).p4).M();
    Double_t WmassLep    = TMath::Sqrt( 2*METCand_.at(0).p4.Pt()*leptonCand_.at(0).p4.Pt()*(1-cos(leptonCand_.at(0).p4.DeltaPhi(METCand_.at(0).p4))));
      
    Hist( "Mlj" )->Fill ( mlj, weight_  );
  
    if(runOnMC_){
      Hist( "LeptonicbFlavor" )->Fill ( Leptonicb_.at(0).flavor, weight_);
      Hist( "HadronicbFlavor" )->Fill ( Hadronicb_.at(2).flavor, weight_);      
      Hist( "Chi2vsbCandFlav" )->Fill ( chi2Min,abs(Leptonicb_.at(0).flavor));
        
      if( fabs(Leptonicb_.at(0).flavor)==5 ) {
        Hist( "MljbEnriched")->Fill ( mlj, weight_);
        if( mlj > 40 && mlj < 170) Hist( "CSV_enriched_trueB")->Fill( Leptonicb_.at(0).csv, weight_    );   
        if(TmassLep > 140 && TmassLep < 210) Hist( "Method2_CSV_enriched_trueB")->Fill( Leptonicb_.at(0).csv, weight_);   
        Hist( "LeptonicbCSV_B")   ->Fill ( Leptonicb_.at(0).csv, weight_    );
        Hist( "LeptonicbFlavor_B")->Fill ( Leptonicb_.at(0).flavor, weight_    );
        Hist( "LeptonicTopMass_B")->Fill ( TmassLep, weight_    );
      }
      else
      if( fabs(Leptonicb_.at(0).flavor)!=5 ) {
        if( mlj > 40 && mlj < 170) Hist( "CSV_enriched_nonB")->Fill( Leptonicb_.at(0).csv, weight_    );   
        if(TmassLep > 140 && TmassLep < 210) Hist( "Method2_CSV_enriched_nonB")->Fill( Leptonicb_.at(0).csv, weight_);   
        Hist( "MljbDepleted")->Fill ( mlj, weight_  );
        Hist( "LeptonicbCSV_nonB" )->Fill ( Leptonicb_.at(0).csv, weight_    );
        Hist( "LeptonicbFlavor_nonB" )->Fill ( Leptonicb_.at(0).flavor, weight_    );
        Hist( "LeptonicTopMass_nonB" )->Fill ( TmassLep, weight_    );
      }
    }
      
    if(mlj > 40 && mlj < 170)  Hist( "CSV_enriched")->Fill( Leptonicb_.at(0).csv, weight_    );
    if(mlj > 170 && mlj < 300) Hist( "CSV_depleted")->Fill( Leptonicb_.at(0).csv, weight_    );
    if(TmassLep > 140 && TmassLep < 210) Hist( "Method2_CSV_enriched")->Fill( Leptonicb_.at(0).csv, weight_);     
    if(TmassLep > 260 && TmassLep < 400) Hist( "Method2_CSV_depleted")->Fill( Leptonicb_.at(0).csv, weight_);

    Hist( "LeptonicbCSV" )->Fill ( Leptonicb_.at(0).csv, weight_);
    Hist( "HadronicbCSV" )->Fill ( Hadronicb_.at(2).csv, weight_);
    Hist( "HadronicTopMass" )->Fill ( TmassHad, weight_);
    Hist( "HadronicWMass" )->Fill ( WmassHad , weight_);
    Hist( "LeptonicWMass" )->Fill ( WmassLep , weight_);
    Hist( "LeptonicTopMass" )->Fill ( TmassLep, weight_);
  }
  else
    return;
}
//DONE!
//==============================================================================================

//Passed filters
//==============================================================================================
bool ExoDiBosonAnalysis::passedFilters( void ){
  
  if( data_.PV_filter ) nPassedGoodPVFilter_++;
  else return false;
   
  if( !applyFilters_ ) return true;
        
  //if( data_.PV_filter                       ) nPassedGoodPVFilter_++;
       
  if( data_.passFilter_HBHE_                ) nPassedFilter_HBHE_++;
  if( data_.passFilter_CSCHalo_             ) nPassedFilter_CSCHalo_++;
  if( data_.passFilter_EEBadSc_	     ) nPassedFilter_EEBadSc_++;
  if( data_.passFilter_HCALlaser_	     ) nPassedFilter_HCALlaser_++;
  if( data_.passFilter_ECALDeadCell_        ) nPassedFilter_ECALDeadCell_++;
  if( data_.passFilter_GoodVtx_	     ) nPassedFilter_GoodVtx_++;
  if( data_.passFilter_TrkFailure_	     ) nPassedFilter_TrkFailure_++;
  if( data_.passFilter_ECALlaser_           ) nPassedFilter_ECALlaser_++;
  if( data_.passFilter_TrkPOG_              ) nPassedFilter_TrkPOG_++;
  if( data_.passFilter_TrkPOG_manystrip_    ) nPassedFilter_TrkPOG_manystrip_++;
  if( data_.passFilter_TrkPOG_toomanystrip_ ) nPassedFilter_TrkPOG_toomanystrip_++;
  if( data_.passFilter_TrkPOG_logError_     ) nPassedFilter_TrkPOG_logError_++;
  if( data_.passFilter_METFilters_	     ) nPassedFilter_METFilters_++;
   
  //bool passMETFiltersAll = data_.passFilter_HBHE_ && data_.passFilter_CSCHalo_ && data_.passFilter_HCALlaser_;
  bool passMETFiltersAll = data_.passFilter_CSCHalo_ && data_.passFilter_HCALlaser_;
  passMETFiltersAll = passMETFiltersAll && data_.passFilter_ECALDeadCell_ && data_.passFilter_GoodVtx_ && data_.passFilter_TrkFailure_;
  passMETFiltersAll = passMETFiltersAll && data_.passFilter_EEBadSc_ && data_.passFilter_ECALlaser_ && data_.passFilter_TrkPOG_;
   
  bool passTrkFiltersAll = data_.passFilter_TrkPOG_manystrip_ && data_.passFilter_TrkPOG_toomanystrip_ && data_.passFilter_TrkPOG_logError_;
      
  if( passMETFiltersAll ) nPassedMETFiltersAll_++;
  if( passTrkFiltersAll ) nPassedTrkFiltersAll_++;
   
  bool passAllfilters = data_.passFilter_HBHE_ && data_.passFilter_CSCHalo_ && data_.PV_filter && data_.passFilter_EEBadSc_;
  if( passAllfilters ) return true;
   
  return false;    

}

//==============================================================================================
bool ExoDiBosonAnalysis::passedTrigger( void ){
 
  //Make sure event is triggered
  if( !Trigger_ ) return true;
  
  std::vector<std::string> trignames;
	
  if( Channel_ == "VVdijet" || Channel_ == "qVdijet" ){
    //Dijet triggers
    trignames.push_back("AK8PFJet360_TrimMass30") ;
    trignames.push_back("AK8PFHT700_TrimR0p1PT0p03Mass50") ;
    // trignames.push_back("AK8DiPFJet280_200_TrimMass30_BTagCSV0p45") ;
    trignames.push_back("PFHT650_WideJetMJJ950DEtaJJ1p5") ;
    trignames.push_back("PFHT650_WideJetMJJ900DEtaJJ1p5") ;
    trignames.push_back("PFHT800_v") ;
  }
  
  else if( Channel_ == "SFmuJets"){
    // trignames.push_back("HLT_IsoMu20_eta2p1_v") ;
//     trignames.push_back("HLT_IsoMu20_eta2p1_TriCentralPFJet30_v") ;
//     trignames.push_back("HLT_IsoMu20_eta2p1_TriCentralPFJet50_40_30_v") ;
    // if( runOnMC_ ) trignames.push_back("HLT_IsoMu24_eta2p1_") ;
    trignames.push_back("HLT_IsoMu24_eta2p1_CentralPFJet30_BTagCSV07_v") ;
    trignames.push_back("HLT_IsoMu24_eta2p1_TriCentralPFJet30_v") ;
    trignames.push_back("HLT_IsoMu24_eta2p1_TriCentralPFJet50_40_30_v") ;
  }
	
  bool isfired = false;
  for( std::map<std::string,bool>::iterator it = (data_.HLT_isFired)->begin(); it != (data_.HLT_isFired)->end(); ++it){
    // std::cout<<(it->first)<<std::endl;
    for( unsigned int t = 0; t < trignames.size(); ++t ){
      if( (it->first).find(trignames[t]) != std::string::npos && it->second ) isfired = true;
    }
  }

  return isfired;
    
}

//==============================================================================================
//Methods for VVdijet analysis====================================================================
//==============================================================================================
bool ExoDiBosonAnalysis::passedDijetSelections(  TString infile  ){
  bool foundTwoJets					= false;
  bool passedDeltaEtaCut		= false;
  bool passedMjjCut					= false;
  bool passedGroomedMassCut	= false;
  bool passedTau21Cut				= false;
  bool passedWTag						= false;
	
  //Make sure events contains two AK8 jets passing loose requirements
  if( findJetCandidates() ) foundTwoJets = true;
  if( !foundTwoJets) return false;
   nPassedFoundJets_++;
  //Only select jets separated by |DeltaEta| < cut
  jetsDeltaEta = fabs( Vcand.at(0).p4.Eta()  - Vcand.at(1).p4.Eta() ) ; 
  if (jetsDeltaEta <= dEtaCut_) passedDeltaEtaCut = true;	
  
  if ( ( Vcand.at(0).p4 + Vcand.at(1).p4 ).M() >= MjjCut_ ){
    jet_deta = fabs( Vcand.at(0).p4.Eta()  - Vcand.at(1).p4.Eta());	
    passedMjjCut = true;
  }
  
  if( !passedDeltaEtaCut) return false;  
  nPassedJetsDEta_++;
  
  doJetTriggerEfficiency();    
  if(Vcand.at(0).p4.Pt() > 500 || Vcand.at(1).p4.Pt() > 500) doJetTriggerEfficiency2();
  
  
  if( !passedMjjCut) return false;   
  nPassedMjj_++;
  
  Hist( "DeltaEta")	->Fill( jetsDeltaEta , weight_ ); 	
  Hist( "DeltaR")	  ->Fill( (Vcand.at(0).p4).DeltaR(Vcand.at(1).p4) , weight_ ); 
  
  if(GenStudies_ && isSignal_) doGroomingStudies(infile);
  
  nPVs = data_.nPVs;
  Hist( "nVertices"        	 )->Fill( data_.nPVs, weight_ );
  
  for( int i = 0; i < abs(Vcand.size()) ; i++){
    Hist( "Mass"          )  ->Fill( Vcand.at(i).p4.M(), weight_ );
    Hist( "PrunedMass"    )  ->Fill( Vcand.at(i).prunedMass, weight_ );
    Hist( "SoftdropMass"  )  ->Fill( Vcand.at(i).softdropMass, weight_ );
    Hist( "Tau21"         )  ->Fill( Vcand.at(i).tau2/Vcand.at(i).tau1, weight_ );
    Hist( "Pt"         )  ->Fill( Vcand.at(i).p4.Pt(), weight_ );
    Hist( "Eta"         )  ->Fill( Vcand.at(i).p4.Eta(), weight_ );
    Hist( "Phi"         )  ->Fill( Vcand.at(i).p4.Phi(), weight_ );
    Hist( "Mass"         )  ->Fill( Vcand.at(i).p4.M(), weight_ );      
    Hist( "cm"      )  ->Fill( Vcand.at(i).cm	   , weight_ );
    Hist( "nm"      )  ->Fill( Vcand.at(i).nm	   , weight_ );
    Hist( "muf"     )  ->Fill( Vcand.at(i).muf  , weight_ );
    Hist( "phf"     )  ->Fill( Vcand.at(i).phf  , weight_ );
    Hist( "emf"     )  ->Fill( Vcand.at(i).emf  , weight_ );
    Hist( "nhf"     )  ->Fill( Vcand.at(i).nhf  , weight_ );
    Hist( "chf"     )  ->Fill( Vcand.at(i).chf  , weight_ );
    Hist( "area"    )  ->Fill( Vcand.at(i).area  , weight_ );
    Hist( "tau1"    )  ->Fill( Vcand.at(i).tau1  , weight_ );
    Hist( "tau2"    )  ->Fill( Vcand.at(i).tau2  , weight_ );
    Hist( "tau3tau2"    )  ->Fill( Vcand.at(i).tau3/Vcand.at(i).tau2  , weight_ );
    Hist( "tau3tau1"    )  ->Fill( Vcand.at(i).tau3/Vcand.at(i).tau1  , weight_ );
    Hist( "tau2tau1"    )  ->Fill( Vcand.at(i).tau2/Vcand.at(i).tau1  , weight_ );
    Hist( "tau3"    )  ->Fill( Vcand.at(i).tau3  , weight_ );
    Hist( "che"     )  ->Fill( Vcand.at(i).che  , weight_ );
    Hist( "ne"      )  ->Fill( Vcand.at(i).ne  , weight_ );
    Hist( "HFHadronEnergyFraction"     )  ->Fill( Vcand.at(i).hf_hf , weight_ ); //HFHadronEnergyFraction());
    Hist( "HFEMEnergyFraction"     )  ->Fill( Vcand.at(i).hf_emf , weight_ ); //HFEMEnergyFraction());
    Hist( "hoEnergyFraction"     )  ->Fill( Vcand.at(i).hof , weight_ ); //hoEnergyFraction());
    Hist( "chargedHadronMultiplicity"     )  ->Fill( Vcand.at(i).chm , weight_ ); //chargedHadronMultiplicity());
    Hist( "neutralHadronMultiplicity"     )  ->Fill( Vcand.at(i).neHadMult  , weight_ ); //neutralHadronMultiplicity());
    Hist( "photonMultiplicity"     )  ->Fill( Vcand.at(i).phoMult , weight_ ); //photonMultiplicity());
    Hist( "neutralEmEnergyFraction"     )  ->Fill( Vcand.at(i).nemf , weight_ ); //neutralEmEnergyFraction());
    Hist( "chargedEmEnergyFraction"     )  ->Fill( Vcand.at(i).cemf  , weight_ ); //chargedEmEnergyFraction());
    Hist( "charge"     )  ->Fill( Vcand.at(i).charge , weight_ ); //charge());
    if( Vcand.at(i).tau2/Vcand.at(i).tau1 >= Tau21HPLow_ && Vcand.at(i).tau2/Vcand.at(i).tau1 <= Tau21HPHigh_ ) Hist( "PrunedMass_afterTau21"    )  ->Fill( Vcand.at(i).prunedMass, weight_ );
    
    if(!isSignal_){
      jet_pt = Vcand.at(i).p4.Pt();
      jet_eta = Vcand.at(i).p4.Eta();
      jet_phi = Vcand.at(i).p4.Phi();
      jet_mass_pruned = Vcand.at(i).prunedMass;
      jet_mass_softdrop = Vcand.at(i).softdropMass;
      jet_tau2tau1 = Vcand.at(i).tau2/Vcand.at(i).tau1;
    }
    
    
    
    
  }
  Hist( "Mjj" ) -> Fill( ( Vcand.at(0).p4 + Vcand.at(1).p4 ).M() , weight_ );	
    // if((Vcand.at(0).p4 + Vcand.at(1).p4 ).M()>5000. && !runOnMC_){
    //   std::cout<<"IAMHERE!!!"<<std::endl;
    //   std::cout<<"Event = "<<data_.EVENT_event<<std::endl;
    //   std::cout<<"Run number = "<<data_.EVENT_run<<std::endl;
    //   std::cout<<"Lumi block = "<<data_.EVENT_lumi<<std::endl;
    //   std::cout<<"Mjj = "<<(Vcand.at(0).p4 + Vcand.at(1).p4 ).M()<<std::endl;
    //   for( int i = 0; i < abs(Vcand.size()) ; i++){
    //     std::cout<<"M pruned = "<< Vcand.at(i).prunedMass <<std::endl;
    //     std::cout<<"pT = "<< Vcand.at(i).p4.Pt() <<std::endl;
    //     std::cout<<"Eta = "<< Vcand.at(i).p4.Eta() <<std::endl;
    //     std::cout<<"Phi = "<< Vcand.at(i).p4.Phi() <<std::endl;
    //     std::cout<<"Tau21 = "<< Vcand.at(i).tau2/Vcand.at(i).tau1 <<std::endl;
    //     std::cout<<"Tau31 = "<< Vcand.at(i).tau3/Vcand.at(i).tau1 <<std::endl;
    //   }
    // }
  
  if(!isSignal_){
    MVV = (Vcand.at(0).p4 + Vcand.at(1).p4).M();
  //  Hist( "Mjj") -> Fill( MVV , weight_ );
  } 
  float MET   = (*data_.MET_et).at(0);
  float SumEt = (*data_.MET_sumEt).at(0);
  if( MET > 0. ) Hist( "METsumET" )->Fill(MET/SumEt, weight_ );
  if( MET > 0. ) Hist( "MET" )->Fill(MET, weight_ );

  	
  //Only select jets with cut < Tau21 < cut
  if( Channel_ == "VVdijet"){
    if(( (Vcand.at(0).tau2/Vcand.at(0).tau1 >= Tau21HPLow_ && Vcand.at(0).tau2/Vcand.at(0).tau1 <= Tau21HPHigh_) && (Vcand.at(1).tau2/Vcand.at(1).tau1 > Tau21Low_ && Vcand.at(1).tau2/Vcand.at(1).tau1 <= Tau21High_) ) ||
      ( (Vcand.at(1).tau2/Vcand.at(1).tau1 >= Tau21HPLow_ && Vcand.at(1).tau2/Vcand.at(1).tau1 <= Tau21HPHigh_) && (Vcand.at(0).tau2/Vcand.at(0).tau1 > Tau21Low_ && Vcand.at(0).tau2/Vcand.at(0).tau1 <= Tau21High_) ) ) passedTau21Cut = true ;

    //Only select jets in groomed mass window
    passedGroomedMassCut = UsePruned_ ? ((Vcand.at(0).prunedMass > mPMLow_ && Vcand.at(0).prunedMass < mPMHigh_)     && (Vcand.at(1).prunedMass > mPMLow_   && Vcand.at(1).prunedMass < mPMHigh_)) 
      : ((Vcand.at(0).softdropMass > mSDLow_ && Vcand.at(0).softdropMass < mSDHigh_) && (Vcand.at(1).softdropMass > mSDLow_ && Vcand.at(1).softdropMass < mSDHigh_));
  }
  else if( Channel_ == "qVdijet"){
    for( int i = 0; i < abs(Vcand.size()) ; i++){
      if( UsePruned_ ? (Vcand.at(i).prunedMass > mPMLow_ && Vcand.at(i).prunedMass < mPMHigh_) : (Vcand.at(i).softdropMass > mSDLow_ && Vcand.at(i).softdropMass < mSDHigh_) ){
        passedGroomedMassCut = true;
        if( Vcand.at(i).tau2/Vcand.at(i).tau1 > Tau21Low_ && Vcand.at(i).tau2/Vcand.at(i).tau1 <= Tau21High_ ){  
          jetINDX=i;
          passedTau21Cut = true;
        }
      }
    }
  }
  
  if(passedGroomedMassCut && passedTau21Cut) passedWTag = true ;

  if ( passedGroomedMassCut ){
    if( Channel_ == "VVdijet"){
      Hist( "Tau21_punzi"	)->Fill( Vcand.at(0).tau2/Vcand.at(0).tau1,weight_ );
      Hist( "Tau21_punzi"	)->Fill( Vcand.at(1).tau2/Vcand.at(1).tau1,weight_ );
    }
    if( Channel_ == "qVdijet") Hist( "Tau21_punzi"	)->Fill( Vcand.at(jetINDX).tau2/Vcand.at(jetINDX).tau1,weight_ );
      
    for( int i = 0; i < abs(Vcand.size()) ; i++){
      if ( ( Vcand.at(0).p4 + Vcand.at(1).p4 ).M() >= 850. && ( Vcand.at(0).p4 + Vcand.at(1).p4 ).M() <= 1150.  )   Hist( "Tau21_punzi1TeV")	->Fill( Vcand.at(i).tau2/Vcand.at(i).tau1 , weight_ ); 	
      if ( ( Vcand.at(0).p4 + Vcand.at(1).p4 ).M() >= 1020. && ( Vcand.at(0).p4 + Vcand.at(1).p4 ).M() <= 1380.  )   Hist( "Tau21_punzi1v2TeV")	->Fill( Vcand.at(i).tau2/Vcand.at(i).tau1 , weight_ ); 	
      if ( ( Vcand.at(0).p4 + Vcand.at(1).p4 ).M() >= 1360. && ( Vcand.at(0).p4 + Vcand.at(1).p4 ).M() <= 1840.  )   Hist( "Tau21_punzi1v6TeV")	->Fill( Vcand.at(i).tau2/Vcand.at(i).tau1 , weight_ ); 	
      if ( ( Vcand.at(0).p4 + Vcand.at(1).p4 ).M() >= 1530. && ( Vcand.at(0).p4 + Vcand.at(1).p4 ).M() <= 2070.  )   Hist( "Tau21_punzi1v8TeV")	->Fill( Vcand.at(i).tau2/Vcand.at(i).tau1 , weight_ ); 
      if ( ( Vcand.at(0).p4 + Vcand.at(1).p4 ).M() >= 1700. && ( Vcand.at(0).p4 + Vcand.at(1).p4 ).M() <= 2300.  )  Hist( "Tau21_punzi2TeV")	->Fill( Vcand.at(i).tau2/Vcand.at(i).tau1 , weight_ ); 	
      if ( ( Vcand.at(0).p4 + Vcand.at(1).p4 ).M() >= 2125. && ( Vcand.at(0).p4 + Vcand.at(1).p4 ).M() <= 2875.  )  Hist( "Tau21_punzi2v5TeV")	->Fill( Vcand.at(i).tau2/Vcand.at(i).tau1 , weight_ ); 
      if ( ( Vcand.at(0).p4 + Vcand.at(1).p4 ).M() >= 2550. && ( Vcand.at(0).p4 + Vcand.at(1).p4 ).M() <= 3450.  )  Hist( "Tau21_punzi3TeV")	->Fill( Vcand.at(i).tau2/Vcand.at(i).tau1 , weight_ ); 	
      if ( ( Vcand.at(0).p4 + Vcand.at(1).p4 ).M() >= 3400. && ( Vcand.at(0).p4 + Vcand.at(1).p4 ).M() <= 4600.  )  Hist( "Tau21_punzi4TeV")	->Fill( Vcand.at(i).tau2/Vcand.at(i).tau1 , weight_ ); 	
    }
  }

  
   
  //Cut flow
  if( !passedGroomedMassCut)	return false;
  nPassedJetPrunedMass_++;
  
  if( !passedTau21Cut			)	return false;      
  nPassedTau21Cut_++;
  
  if( !passedWTag			)	return false;      
  nPassedWTag_++;
  
  // //Apply selection
  // if ( foundTwoJets && passedDeltaEtaCut && passedMjjCut && passedGroomedMassCut && passedTau21Cut   ) return true;
  // else
    
  return true;
	
}
//==============================================================================================
bool ExoDiBosonAnalysis::findJetCandidates( void ){
  
  TLorentzVector			TLV;
  std::vector<float>	jetPt;
  bool foundJets = false;
		
  jetPt.clear();
  //Make sure jets passes loose ID, pT and eta cuts
  for( int j = 0; j < data_.njetsAK8 ; ++j ){
    if( j < 2 && (*data_.jetAK8_IDLoose).at(j) != 1         )break;
    if( (*data_.jetAK8_IDLoose).at(j)		!= 1				  			)continue;
    if( (*data_.jetAK8_pt).at(j)					<= JetPtCutTight_	)continue;
    if( fabs((*data_.jetAK8_eta).at(j)) 	>= JetEtaCut_ 		)continue;		
    jetPt.push_back((*data_.jetAK8_pt).at(j));
  }
	
  if( jetPt.size() > 1 ) foundJets = true;
  if( !foundJets) return false;
		
  //Find two highest pT jets in event
  if( foundJets ){
    std::sort  (jetPt.begin(),jetPt.end());
    std::reverse(jetPt.begin(),jetPt.end());
    for( int jj = 0; jj < 2; ++jj ){
      bool foundOverlap = false;
      if( (*data_.jetAK8_pt)[jj] == jetPt.at(0) ){
        TLV.SetPtEtaPhiE( (*data_.jetAK8_pt).at(jj), (*data_.jetAK8_eta).at(jj), (*data_.jetAK8_phi).at(jj), (*data_.jetAK8_e).at(jj) );
        Hist( "LeptonJet_JetID" )->Fill( 0.);
        if( (*data_.jetAK8_IDTight).at(jj) ) Hist( "LeptonJet_JetID" )->Fill( 1.);
        if ( GenStudies_){
          std::map<int,TLorentzVector>::iterator itE = genCandidates_.find(11)!=genCandidates_.end() ? genCandidates_.find(11) : genCandidates_.find(-11);
          std::map<int,TLorentzVector>::iterator itM = genCandidates_.find(13)!=genCandidates_.end() ? genCandidates_.find(13) : genCandidates_.find(-13);
          std::map<int,TLorentzVector>::iterator itT = genCandidates_.find(15)!=genCandidates_.end() ? genCandidates_.find(15) : genCandidates_.find(-15);
          if( TLV.DeltaR(itE->second) < 0.8 || TLV.DeltaR(itM->second) < 0.8 ){ 
            Hist( "LeptonJet_JetID" )->Fill( 3.);
            if( (*data_.jetAK8_IDTight).at(jj) ) Hist( "LeptonJet_JetID" )->Fill( 4.);
          }
          if( TLV.DeltaR(itE->second) < 0.8 || TLV.DeltaR(itM->second) < 0.8 || TLV.DeltaR(itT->second) < 0.8 ){ 
            Hist( "LeptonJet_JetID" )->Fill( 2.);
          }
        }
       
        if ( findMuonCandidate() || findElectronCandidate() ){
          for(int i = 0; i < abs(leptonCand_.size()); i++){
            if( TLV.DeltaR(leptonCand_.at(i).p4) < 0.8 ){
              Hist( "LeptonJet_JetID" )->Fill( 5.);
              if( (*data_.jetAK8_IDTight).at(jj) ) Hist( "LeptonJet_JetID" )->Fill( 6.);
              foundOverlap = true;
            }
          }
        }
       
        if( foundOverlap ) break;
        JetCandidate jet(TLV);
        jet.csv					= -99                                   ;
        jet.tau1					= (*data_.jetAK8_tau1).at(jj)         ;
        jet.tau2					= (*data_.jetAK8_tau2).at(jj)         ;
        jet.tau3					= (*data_.jetAK8_tau3).at(jj)         ;
        jet.prunedMass		= (*data_.jetAK8_prunedmass).at(jj)		;
        jet.softdropMass	= (*data_.jetAK8_softdropmass).at(jj)	;
        jet.mass					= (*data_.jetAK8_mass).at(jj)         ;
        jet.flavor				= -99                               ;
        jet.rcn					= (*data_.jetAK8_che).at(jj)/(*data_.jetAK8_ne).at(jj);
        jet.cm = (*data_.jetAK8_cm).at(jj);
        jet.nm = (*data_.jetAK8_nm).at(jj);
        jet.muf = (*data_.jetAK8_muf).at(jj);
        jet.phf = (*data_.jetAK8_phf).at(jj);
        jet.emf = (*data_.jetAK8_emf).at(jj);
        jet.nhf = (*data_.jetAK8_nhf).at(jj);
        jet.chf = (*data_.jetAK8_chf).at(jj);
        jet.che = (*data_.jetAK8_che).at(jj);
        jet.ne = (*data_.jetAK8_ne).at(jj);  
        jet.hf_hf = (*data_.jetAK8_hf_hf).at(jj);
        jet.hf_emf = (*data_.jetAK8_hf_emf).at(jj);
        jet.hof = (*data_.jetAK8_hof).at(jj);
        jet.chm  = (*data_.jetAK8_chm).at(jj);
        jet.neHadMult = (*data_.jetAK8_neHadMult).at(jj);
        jet.phoMult = (*data_.jetAK8_phoMult).at(jj);
        jet.nemf = (*data_.jetAK8_nemf).at(jj);
        jet.cemf = (*data_.jetAK8_cemf).at(jj);
        jet.charge = (*data_.jetAK8_charge).at(jj);
        jet.area = (*data_.jetAK8_area).at(jj);
        Vcand.push_back( jet );
      }
      else
      if( (*data_.jetAK8_pt).at(jj) == jetPt.at(1) ){
        TLV.SetPtEtaPhiE( (*data_.jetAK8_pt).at(jj), (*data_.jetAK8_eta).at(jj), (*data_.jetAK8_phi).at(jj), (*data_.jetAK8_e).at(jj) );
        Hist( "LeptonJet_JetID" )->Fill( 0.);
        if( (*data_.jetAK8_IDTight).at(jj) ) Hist( "LeptonJet_JetID" )->Fill( 1.);
        if ( GenStudies_){
          std::map<int,TLorentzVector>::iterator itE = genCandidates_.find(11)!=genCandidates_.end() ? genCandidates_.find(11) : genCandidates_.find(-11);
          std::map<int,TLorentzVector>::iterator itM = genCandidates_.find(13)!=genCandidates_.end() ? genCandidates_.find(13) : genCandidates_.find(-13);
          std::map<int,TLorentzVector>::iterator itT = genCandidates_.find(15)!=genCandidates_.end() ? genCandidates_.find(15) : genCandidates_.find(-15);
          if( TLV.DeltaR(itE->second) < 0.8 || TLV.DeltaR(itM->second) < 0.8 ){ 
            Hist( "LeptonJet_JetID" )->Fill( 3.);
            if( (*data_.jetAK8_IDTight).at(jj) ) Hist( "LeptonJet_JetID" )->Fill( 4.);
          }
          if( TLV.DeltaR(itE->second) < 0.8 || TLV.DeltaR(itM->second) < 0.8 || TLV.DeltaR(itT->second) < 0.8 ){ 
            Hist( "LeptonJet_JetID" )->Fill( 2.);
          }
        }
       
        if ( findMuonCandidate() || findElectronCandidate() ){
          for(int i = 0; i < abs(leptonCand_.size()); i++){
            if( TLV.DeltaR(leptonCand_.at(i).p4) < 0.8 ){
              Hist( "LeptonJet_JetID" )->Fill( 5.);
              if( (*data_.jetAK8_IDTight).at(jj) ) Hist( "LeptonJet_JetID" )->Fill( 6.);
              foundOverlap = true;
            }
          }
        }
        if( foundOverlap ) break;
        JetCandidate secondJet(TLV);
        secondJet.csv          = -99                                              ;
        secondJet.tau1          = (*data_.jetAK8_tau1).at(jj)                      ;
        secondJet.tau2          = (*data_.jetAK8_tau2).at(jj)                      ;
        secondJet.tau3          = (*data_.jetAK8_tau3).at(jj)                      ;
        secondJet.prunedMass    = (*data_.jetAK8_prunedmass).at(jj)          ;
        secondJet.softdropMass  = (*data_.jetAK8_softdropmass).at(jj)        ;
        secondJet.mass          = (*data_.jetAK8_mass).at(jj)                      ;
        secondJet.flavor        = -99                                            ;
        secondJet.rcn            = (*data_.jetAK8_che).at(jj)/(*data_.jetAK8_ne).at(jj);
        secondJet.cm = (*data_.jetAK8_cm).at(jj);
        secondJet.nm = (*data_.jetAK8_nm).at(jj);
        secondJet.muf = (*data_.jetAK8_muf).at(jj);
        secondJet.phf = (*data_.jetAK8_phf).at(jj);
        secondJet.emf = (*data_.jetAK8_emf).at(jj);
        secondJet.nhf = (*data_.jetAK8_nhf).at(jj);
        secondJet.chf = (*data_.jetAK8_chf).at(jj);
        secondJet.che = (*data_.jetAK8_che).at(jj);
        secondJet.ne = (*data_.jetAK8_ne).at(jj);  
        secondJet.hf_hf = (*data_.jetAK8_hf_hf).at(jj);
        secondJet.hf_emf = (*data_.jetAK8_hf_emf).at(jj);
        secondJet.hof = (*data_.jetAK8_hof).at(jj);
        secondJet.chm  = (*data_.jetAK8_chm).at(jj);
        secondJet.neHadMult = (*data_.jetAK8_neHadMult).at(jj);
        secondJet.phoMult = (*data_.jetAK8_phoMult).at(jj);
        secondJet.nemf = (*data_.jetAK8_nemf).at(jj);
        secondJet.cemf = (*data_.jetAK8_cemf).at(jj);
        secondJet.charge = (*data_.jetAK8_charge).at(jj);
        secondJet.area = (*data_.jetAK8_area).at(jj);
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
  foundAMu = 0;
  foundAEle = 0;
  bool passVeto  = false;
  bool found1Jet = false;
  bool found2Jet = false;
  bool found3Jet = false;
  bool found4Jet = false;
  bool found1b   = false;
  bool found2b   = false;
  bool foundMET  = false;
  
  if( findLeptonCandidate() ) foundLept = true; 
  if( !foundLept ) return false;
  nPassedFoundLept_++;
  
  if ( (foundAMu+foundAEle)<1) passVeto = true; 
  if( !passVeto ) return false;
  nPassedVetoLep_++;
  
  if( findMETCandidate() ) foundMET = true;
  if( !foundMET ) return false;
  nPassedFoundMET_++;
  
  findAK4Jets();
  Hist( "nAK4"	)->Fill ( abs(AK4jetCand_.size()) );
  if( abs(AK4jetCand_.size()) >= 1 ) found1Jet = true;
  if( !found1Jet ) return false;	
  nPassed1Jet_++;
  if( abs(AK4jetCand_.size()) >= 2 ) found2Jet = true;
  if( !found2Jet ) return false;
  nPassed2Jet_++;
  if( abs(AK4jetCand_.size()) >= 3 ) found3Jet = true;
  if( !found3Jet ) return false;
  nPassed3Jet_++;
  if( abs(AK4jetCand_.size()) >= 4 ) found4Jet = true;
  if( !found4Jet ) return false;
  nPassed4Jet_++;
	
  // if ( nBTags > 0) found1b = true;
  // if( !found1b ) return false;
  // nPassed1bTag_++;
  // if ( nBTags > 1) found2b = true;
  // if( !found2b ) return false;
  // nPassed2bTag_++;
  
  if ( nBTags > 0) nPassed1bTag_++;
  if ( nBTags > 1) nPassed2bTag_++;
  if( foundLept && passVeto && foundMET && found4Jet) return true;
	
  else
    return false;
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
  bool foundLept = false;
  double ptMu = -999;
  int muIndex = 999;
  double newpt = 0.;
  for( int l = 0; l < data_.mu_N; ++l ){
    if( (Channel_ == "VVdijet"  || Channel_ == "qVdijet")  && (*data_.mu_isHighPtMuon)[l] != 1 ) continue;
    if( (Channel_ == "SFmuJets" || Channel_ == "SFelJets") && (*data_.mu_isTightMuon)[l] != 1 ) continue;
    if( (*data_.mu_isPFMuon)[l] != 1 ) continue;
    if( (*data_.mu_trackIso)[l]/(*data_.mu_pt)[l] >= 0.1 ) continue;
    if( (*data_.mu_pt)[l] <= leptPtCut_ ) continue;
    if( fabs((*data_.mu_eta)[l]) >= leptEtaCut_ ) continue;
    foundLept = true;
    if( (*data_.mu_pt)[l] > ptMu ){   
      ptMu = (*data_.mu_pt)[l];
      TLV.SetPtEtaPhiE( (*data_.mu_pt)[l], (*data_.mu_eta)[l], (*data_.mu_phi)[l], (*data_.mu_e)[l] );  
      muIndex = l;
    }      
  }
   
  if( foundLept ){
    LeptonCandidate muCand(TLV);
    muCand.iso = (*data_.mu_trackIso)[muIndex]/(*data_.mu_pt)[muIndex];
    leptonCand_.push_back( muCand );
  }
   
  for( int l = 0; l < data_.mu_N; ++l ){
    if( muIndex == 999 || l == muIndex ) continue;
    if( (Channel_ == "VVdijet"  || Channel_ == "qVdijet")  && (*data_.mu_isHighPtMuon)[l] != 1 ) continue;
    if( (Channel_ == "SFmuJets" || Channel_ == "SFelJets") && (*data_.mu_isLooseMuon)[l] != 1 ) continue;
    if( (*data_.mu_trackIso)[l]/(*data_.mu_pt)[l] >= 0.1 ) continue;
    if( (*data_.mu_pt)[l] <= AleptPtCut_ ) continue;
    if( fabs((*data_.mu_eta)[l]) >= AleptEtaCut_ ) continue;
    foundAMu++;
  }
   
  for( int l = 0; l < data_.el_N; ++l ){
    if( (Channel_ == "VVdijet"  || Channel_ == "qVdijet")  && (*data_.el_isHEEP)[l] != 1 ) continue;
    if( (Channel_ == "SFmuJets" || Channel_ == "SFelJets") && (*data_.el_isLooseElectron)[l] != 1 ) continue;
    if( (*data_.el_pt)[l] <= 35. ) continue;
    //if( fabs((*data_.el_eta)[l]) >= 1.4442 && fabs((*data_.el_eta)[l]) <= 1.566 ) continue;
    //if( fabs((*data_.el_eta)[l]) >= 2.5 ) continue;
    foundAEle++;
  }
    
  if( foundLept ) return true;
  else return false;
   
}

//==============================================================================================
bool ExoDiBosonAnalysis::findElectronCandidate( void ){

  TLorentzVector TLV;
  bool foundEle = false;
  double ptEle = -999;
  int eleIndex = 999;
  for( int l = 0; l < data_.el_N; ++l ){
    if( (*data_.el_pt)[l] <= 10. ) continue;     
    //if( fabs((*data_.el_eta)[l]) >= 1.4442 && fabs((*data_.el_eta)[l]) <= 1.566 ) continue; 
    if( fabs((*data_.el_eta)[l]) >= leptEtaCut_ ) continue;
    if( (Channel_ == "VVdijet"  || Channel_ == "qVdijet")  && (*data_.el_isHEEP)[l] != 1 ) continue;
    if( (Channel_ == "SFmuJets" || Channel_ == "SFelJets") && (*data_.el_isMediumElectron)[l] != 1 ) continue;
    if( (*data_.el_pt)[l] <= leptPtCut_ ) continue;
    foundEle = true;
    if( (*data_.el_pt)[l] > ptEle ){   
      ptEle = (*data_.el_pt)[l];
      TLV.SetPtEtaPhiE( (*data_.el_pt)[l], (*data_.el_eta)[l], (*data_.el_phi)[l], (*data_.el_e)[l] );         
      eleIndex = l;
    }
  }

  if( foundEle )
    leptonCand_.push_back( LeptonCandidate( TLV ) );
   
  int foundAEle = 0;
  for( int l = 0; l < data_.el_N; ++l ){
    if( eleIndex == 999 || l == eleIndex ) continue;
    if( (Channel_ == "VVdijet"  || Channel_ == "qVdijet")  && (*data_.el_isHEEP)[l] != 1 ) continue;
    if( (Channel_ == "SFmuJets" || Channel_ == "SFelJets") && (*data_.el_isLooseElectron)[l] != 1 ) continue;
    if( (*data_.el_pt)[l] <= AleptPtCut_ ) continue;
    //if( fabs((*data_.el_eta)[l]) >= 1.4442 && fabs((*data_.el_eta)[l]) <= 1.566 ) continue;
    if( fabs((*data_.el_eta)[l]) >= AleptEtaCut_ ) continue;
    foundAEle++;
  }   
  int foundAMu = 0;
  for( int l = 0; l < data_.mu_N; ++l ){
    if( (Channel_ == "VVdijet"  || Channel_ == "qVdijet")  && (*data_.mu_isHighPtMuon)[l] != 1 ) continue;
    if( (Channel_ == "SFmuJets" || Channel_ == "SFelJets") && (*data_.mu_isTightMuon)[l] != 1 ) continue;
    if( (*data_.mu_trackIso)[l]/(*data_.mu_pt)[l] >= 0.1 ) continue;
    if( (*data_.mu_pt)[l] <= 20. ) continue;
    if( fabs((*data_.mu_eta)[l]) >= 2.4 ) continue;
    foundAMu++;
  }
    
  if( /*(foundAMu+foundAEle)<1 &&*/ foundEle ) return true;
  else return false;   
   
  return true;
   
}

//==============================================================================================
void ExoDiBosonAnalysis::findAK4Jets( void ){
	
  nBTags = 0;
  TLorentzVector jet;
  for( unsigned int j = 0; j < (data_.jetAK4_pt)->size(); ++j ){ 
    jet.SetPtEtaPhiE( (*data_.jetAK4_pt).at(j), (*data_.jetAK4_eta).at(j), (*data_.jetAK4_phi).at(j), (*data_.jetAK4_e).at(j) );
    if( (*data_.jetAK4_IDLoose).at(j) != 1 ) continue;
    if( (*data_.jetAK4_pt).at(j) <= JetPtCutLoose_ ) continue;
    if( fabs((*data_.jetAK4_eta).at(j)) >= JetEtaCut_ ) continue;
    if( jet.DeltaR(leptonCand_.at(0).p4) < 0.3 ) continue;
    JetCandidate Ajet(jet);
    Ajet.csv = (*data_.jetAK4_csv).at(j);
    Ajet.flavor = abs((*data_.jetAK4_flavor).at(j));
    AK4jetCand_.push_back(Ajet);
    if ((*data_.jetAK4_csv).at(j) > 0.814){
      nBTags++;
      // AK4bjetCand_.push_back(Ajet);
    } 
  }
}

//==============================================================================================
bool ExoDiBosonAnalysis::findMETCandidate( void ){
 
  TLorentzVector TLV;
  bool foundMET = false;
  if( (*data_.MET_et).at(0) > METCut_ ){
    TLV.SetPtEtaPhiE( (*data_.MET_et).at(0), 0., (*data_.MET_phi).at(0), 0. ); 
    METCand_.push_back( METCandidate( TLV ) );
    foundMET = true;
  }
  return foundMET; 
   
}

//==============================================================================================
bool ExoDiBosonAnalysis::findWCandidate( void ){

  TLorentzVector TLV;
  bool foundW = false;
  if( (METCand_.at(0).p4+leptonCand_.at(0).p4).Pt() > 0. ){
    foundW = true;
    TLV = METCand_.at(0).p4+leptonCand_.at(0).p4;
    WCand_.push_back( TLV );
  }
   
  return foundW;
}
//==============================================================================================
bool ExoDiBosonAnalysis::findHadronicWCandidate( void ){

  TLorentzVector TLV,TLV1, TLV2;
  bool foundW = false;
  Double_t deltaWmassMin = 999.;

  for(int i=0; i < abs(AK4jetCand_.size()); i++ ){
    if (AK4jetCand_.at(i).p4.Pt() == Leptonicb_.at(0).p4.Pt() || AK4jetCand_.at(i).p4.Pt() <= 0. ) continue;
    for(int j=0; j != i && j < abs(AK4jetCand_.size()); j++ ){
      Double_t deltaWmass = fabs(pdgMw - ((AK4jetCand_.at(i).p4+ AK4jetCand_.at(j).p4).M()));
      if( deltaWmass < deltaWmassMin ){
        deltaWmassMin = deltaWmass;
        foundW = true;
        TLV = AK4jetCand_.at(i).p4+AK4jetCand_.at(j).p4;
        TLV1 = AK4jetCand_.at(i).p4;
        TLV2 = AK4jetCand_.at(j).p4;
      }
    }
  }
  HadronicJ_.push_back( TLV1 );
  HadronicJ_.push_back( TLV2 );
  Hist( "DeltaRJJ")->Fill ( HadronicJ_.at(1).p4.DeltaR(HadronicJ_.at(0).p4) , weight_	);
	
  WCand_.push_back( TLV );
  return foundW;

}

//==============================================================================================
TLorentzVector ExoDiBosonAnalysis::getp4Nu( void ){

  return Utilities::NuMomentum( leptonCand_.at(0).p4.Px(), leptonCand_.at(0).p4.Py(), leptonCand_.at(0).p4.Pz(), leptonCand_.at(0).p4.Pt(), leptonCand_.at(0).p4.E(), METCand_.at(0).p4.Px(), METCand_.at(0).p4.Py() );   
   
}

//==============================================================================================
TLorentzVector ExoDiBosonAnalysis::getp4NuMethod2( void ){

  double E_l  = leptonCand_.at(0).p4.E();
  double m_l  = leptonCand_.at(0).p4.M();
  double px_l = leptonCand_.at(0).p4.Px();
  double py_l = leptonCand_.at(0).p4.Py();
  double pz_l = leptonCand_.at(0).p4.Pz();

  //std::cout << "lep: px = " << px_l << " - py = " << py_l << " - pz = " << pz_l << " - pt = " << TMath::Sqrt(px_l*px_l + py_l*py_l);
  //std::cout << " - pt LTV = " << leptonCand_.at(0).p4.Pt() << " - mass = " << m_l << std::endl;
      
  double px_v = METCand_.at(0).p4.Px();
  double py_v = METCand_.at(0).p4.Py();
   
  //std::cout << "MET: metx = " << px_v << " - mety = " << py_v << " - et = " << TMath::Sqrt(px_v*px_v + py_v*py_v);
  //std::cout << " - et TLV = " << METCand_.at(0).p4.Pt() << std::endl;
   
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
  Hist( "NuLeptInvMassDeltap"  )->Fill( (v + leptonCand_.at(0).p4).M() );
  Hist( "DiBosonInvMassDeltap" )->Fill( (v + leptonCand_.at(0).p4 + WCand_.at(0).p4).M() );
  }
  else if( Delta <= 0 ){
  Hist( "NuLeptInvMassDeltam"  )->Fill( (v + leptonCand_.at(0).p4).M() );
  Hist( "DiBosonInvMassDeltam" )->Fill( (v + leptonCand_.at(0).p4 + WCand_.at(0).p4).M() );   
  }*/
   
  //std::cout << "Method 2: " << Delta << std::endl;
   
  return v;
      
}


//==============================================================================================
void ExoDiBosonAnalysis::fillHistos( std::string Channel ){
  
  std::string Channel_ = Channel;
  
  if( Channel_ == "VVdijet" || Channel_ == "qVdijet" ){
    Hist( "VVdeltaEta"        )-> Fill( jetsDeltaEta , weight_ ); 
    Hist( "DiBosonInvMass"    )->Fill( (Vcand.at(0).p4 + Vcand.at(1).p4).M(), weight_ );
    
    for(int i = 0; i < Vcand.size();i++){
      if( Channel_ == "qVdijet" && i != jetINDX) continue;
      Hist( "VcandTau21"        )->Fill( Vcand.at(i).tau2/Vcand.at(i).tau1,weight_ );
      Hist( "VcandPrunedMass"   )->Fill( Vcand.at(i).prunedMass, weight_ );
      Hist( "VcandSoftdropMass" )->Fill( Vcand.at(i).softdropMass, weight_ );
      Hist( "VcandPt"           )->Fill( Vcand.at(i).p4.Pt() , weight_ );
      Hist( "VcandEta"          )->Fill( Vcand.at(i).p4.Eta(), weight_ );
      Hist( "VcandPhi"          )->Fill( Vcand.at(i).p4.Phi(), weight_ );
      Hist( "VcandMass"         )->Fill( Vcand.at(i).mass , weight_ );
    }
  }
  
  else if(Channel_ == "SFmuJets"){
    
    float MET = (*data_.MET_et).at(0);
    Hist( "leptonPT"    )->Fill( leptonCand_.at(0).p4.Pt()	, weight_ );
    Hist( "leptonPhi"   )->Fill( leptonCand_.at(0).p4.Phi(), weight_ );
    Hist( "leptonEta"   )->Fill( leptonCand_.at(0).p4.Eta(), weight_ );
    Hist( "MET"         )->Fill(MET, weight_ );
    Hist( "nbTagAK4"    )->Fill ( nBTags );
    Hist( "AK4jetPt"    )->Fill( AK4jetCand_.at(0).p4.Pt(), weight_ );
    Hist( "AK4jetCSV"   )->Fill( AK4jetCand_.at(0).csv		, weight_ );
    Hist( "AK4jetMass"  )->Fill( AK4jetCand_.at(0).p4.M()	, weight_ );
  }
   
}


       			        
//==============================================================================================
void ExoDiBosonAnalysis::EndInputData( const SInputData& ) throw( SError ) {
		
  if( Channel_ == "VVdijet" || Channel_ == "qVdijet" ){

    printCutFlow();
    theHistosManager_->formatHistos(Channel_);

    //   Hist( "genEvents"               )->SetBinContent(1,genEvents_              );
    Hist( "nEvents"               )->SetBinContent(1,nEvents_*weight_               );
    Hist( "nPassedFilter"        )->SetBinContent(1,nPassedFilters_*weight_        );
    Hist( "nPassedTrigger"        )->SetBinContent(1,nPassedTrigger_*weight_        );
    Hist( "nPassedFoundJets"      )->SetBinContent(1,nPassedFoundJets_*weight_      );
    Hist( "nPassedJetsDEta"       )->SetBinContent(1,nPassedJetsDEta_*weight_       );
    Hist( "nPassedMjj"            )->SetBinContent(1,nPassedMjj_*weight_            );
    Hist( "nPassedTau21Cut"       )->SetBinContent(1,nPassedTau21Cut_*weight_       );
    Hist( "nPassedPrunedJetMass"  )->SetBinContent(1,nPassedJetPrunedMass_*weight_  );
  }
  else if (Channel_ == "SFmuJets"){

    printCutFlow();
    theHistosManager_->formatHistos(Channel_);
    
    Hist( "sumGenWeight" )->SetBinContent(1,nSumGenWeights_);
    Hist( "nEvents" )->SetBinContent(1,nEvents_*weight_        );
    Hist( "nPassedFilter" )->SetBinContent(1,nPassedFilters_*weight_        );
    Hist( "nPassedTrigger"  )->SetBinContent(1,nPassedTrigger_*weight_        );
    Hist( "nPassedFoundLept")->SetBinContent(1,nPassedFoundLept_*weight_    );
    Hist( "nPassedVetoLep"  )->SetBinContent(1,nPassedVetoLep_*weight_    );
    Hist( "nPassedFoundMET" )->SetBinContent(1,nPassedFoundMET_*weight_    );
    Hist( "nPassed1Jet"      )->SetBinContent(1,nPassed1Jet_*weight_        );
    Hist( "nPassed2Jet"      )->SetBinContent(1,nPassed2Jet_*weight_      );
    Hist( "nPassed3Jet"      )->SetBinContent(1,nPassed3Jet_*weight_      );
    Hist( "nPassed4Jet"      )->SetBinContent(1,nPassed4Jet_*weight_      );
    Hist( "nPassed1bTag"     )->SetBinContent(1,nPassed1bTag_*weight_      );
    Hist( "nPassed2bTag"     )->SetBinContent(1,nPassed2bTag_*weight_      );
    Hist( "nPassedChi2"     )->SetBinContent(1,nPassedChi2_*weight_      );

  }
   
  return;

}

//==============================================================================================
void ExoDiBosonAnalysis::EndCycle() throw( SError ) {

  return;

}

//==============================================================================================
void ExoDiBosonAnalysis::printCutFlow( void ) {
	
  if( Channel_ == "VVdijet" || Channel_ == "qVdijet" ){
    std::cout << std::endl; 
      
  
    std::cout << "############ Cut flow: ############" << std::endl;	
    std::cout << "number of events		                           " << nEvents_ << std::endl;
    std::cout << "passed filter		                             " << nPassedFilters_ << " --- eff = " << (double)nPassedFilters_/nEvents_ << std::endl; 
    std::cout << "passed trigger		                             " << nPassedTrigger_ << " --- eff = " << (double)nPassedTrigger_/nEvents_ << std::endl; 
    std::cout << "found at least 2 jets with pT > 200/ eta < 2.4  " << nPassedFoundJets_ << " --- eff = " << (double)nPassedFoundJets_/nEvents_ << std::endl;
    
    std::cout << "Passed M(j,j) cut		                           " << nPassedMjj_ << " --- eff = " << (double)nPassedMjj_/nEvents_ << std::endl;
    std::cout << "Passed dEta(j,j) < 1.3		                     " << nPassedJetsDEta_ << " --- eff = " << (double)nPassedJetsDEta_/nEvents_ << std::endl;
    std::cout << "Passed jet pruned mass cut		                 " << nPassedJetPrunedMass_ << " --- eff = " << (double)nPassedJetPrunedMass_/nEvents_ << std::endl;
    std::cout << "Passed tau 21 cut		                           " << nPassedTau21Cut_ << " --- eff = " << (double)nPassedTau21Cut_/nEvents_ << std::endl;
  }
  
  else if (Channel_ == "SFmuJets"){
    std::cout << "passed filter HBHE		                             " << nPassedFilter_HBHE_ << " --- eff = " << (double)nPassedFilter_HBHE_/nEvents_ << std::endl; 
    std::cout << "passed filter CSCHalo		                             " << nPassedFilter_CSCHalo_ << " --- eff = " << (double)nPassedFilter_CSCHalo_/nEvents_ << std::endl;  
    std::cout << "passed filter EEBadSc		                             " << nPassedFilter_EEBadSc_ << " --- eff = " << (double)nPassedFilter_EEBadSc_/nEvents_ << std::endl; 
    std::cout << "passed filter GoodPV		                             " << nPassedGoodPVFilter_ << " --- eff = " << (double)nPassedGoodPVFilter_/nEvents_ << std::endl; 
    
    std::cout << "number of events		                            " << nEvents_ << std::endl;
    std::cout << "passed filter		                                " << nPassedFilters_ << " --- eff = " << (double)nPassedFilters_/nEvents_ << std::endl; 
    std::cout << "passed trigger		                             " << nPassedTrigger_ << " --- eff = " << (double)nPassedTrigger_/nEvents_ << std::endl; 
    std::cout << "Passed found lep                               " << nPassedFoundLept_ << " --- eff = " << (double)nPassedFoundLept_/nEvents_ << std::endl;
    std::cout << "Passed VETO lep                                " << nPassedVetoLep_ << " --- eff = " << (double)nPassedVetoLep_/nEvents_ << std::endl;
    std::cout << "Passed found MET                               " << nPassedFoundMET_ << " --- eff = " << (double)nPassedFoundMET_/nEvents_ << std::endl;
    std::cout << "Passed 1 Jet                                   " << nPassed1Jet_ << " --- eff = " << (double)nPassed1Jet_/nEvents_ << std::endl;
    std::cout << "Passed 2 Jet                                   " << nPassed2Jet_ << " --- eff = " << (double)nPassed2Jet_/nEvents_ << std::endl;
    std::cout << "Passed 3 Jet                                   " << nPassed3Jet_ << " --- eff = " << (double)nPassed3Jet_/nEvents_ << std::endl;
    std::cout << "Passed 4 Jet                                   " << nPassed4Jet_ << " --- eff = " << (double)nPassed4Jet_/nEvents_ << std::endl;
    std::cout << "Passed Chi2                                   " << nPassedChi2_ << " --- eff = " << (double)nPassedChi2_/nEvents_ << std::endl;

  }
  
   
  std::cout << std::endl; 
   
}	
//==============================================================================================
//Efficiency studies============================================================================
//==============================================================================================
void ExoDiBosonAnalysis::doJetTriggerEfficiency( void ){

  Mjj = ( Vcand.at(0).p4 + Vcand.at(1).p4 ).M();

  ///////////////////////////////////////////// numerators /////////////////////////////////////////////
  // if(Vcand.at(0).p4.Pt() > 500 || Vcand.at(1).p4.Pt() > 500 ){
  for( std::map<std::string,bool>::iterator it = (data_.HLT_isFired)->begin(); it != (data_.HLT_isFired)->end(); it++){
    std::string trigName = it->first;
    bool decision = it->second;
    //HLT_IsoMu24_eta2p1_v2 or PFJet320 or PFHT650
    if( (trigName).find("PFHT650_v") != std::string::npos && decision ){
      //EVERYTHING BELOW PASSES PFHT650!!!-------------------------------------------------------------------------------------------------------|
      if( Vcand.at(0).prunedMass > 65. || Vcand.at(1).prunedMass > 65.){
        Hist( "PFHT650" )->Fill( Mjj);

        //Second loop
        bool passedHT = false;
        bool passedSubstructure = false;
        bool passedALL = false;
        
        for( std::map<std::string,bool>::iterator it2 = (data_.HLT_isFired)->begin(); it2 != (data_.HLT_isFired)->end(); it2++){
          std::string iter = it2->first;
          bool value = it2->second;

          if( (iter).find("PFHT800")                        != std::string::npos && value ) Hist( "HT800" )->Fill( Mjj);
          if( (iter).find("PFHT650_WideJetMJJ950DEtaJJ1p5") != std::string::npos && value ) Hist( "HT650_MJJ950" )->Fill( Mjj);
          if( (iter).find("PFHT650_WideJetMJJ900DEtaJJ1p5") != std::string::npos && value ) Hist( "HT650_MJJ900" )->Fill( Mjj);
          if( ((iter).find("PFHT800")                       != std::string::npos && value)
            ||((iter).find("PFHT650_WideJetMJJ900DEtaJJ1p5")!= std::string::npos && value)
              ||((iter).find("PFHT650_WideJetMJJ950DEtaJJ1p5")!= std::string::npos && value)) passedHT = true;
          
          if( ((iter).find("PFHT800")                       != std::string::npos && value)
            ||((iter).find("PFHT650_WideJetMJJ900DEtaJJ1p5")!= std::string::npos && value)
              ||((iter).find("PFHT650_WideJetMJJ950DEtaJJ1p5")!= std::string::npos && value)
                ||((iter).find("AK8PFJet360_TrimMass30")        != std::string::npos && value)
                  ||((iter).find("AK8PFHT700_TrimR0p1PT0p03Mass50")!= std::string::npos && value)) passedALL = true;


          //SUBSTRUCTURE TRIGGERS
          if( (iter).find("AK8PFJet360_TrimMass30")                    != std::string::npos && value ) Hist( "PFJet360_Trim" ) ->Fill( Mjj);
          if( (iter).find("AK8PFHT700_TrimR0p1PT0p03Mass50")           != std::string::npos && value ) Hist( "HT700_Trim" )    ->Fill( Mjj);
          if( (iter).find("AK8DiPFJet280_200_TrimMass30_BTagCSV0p45")  != std::string::npos && value ) Hist( "DiPFJet280_200_TrimMass30" )->Fill( Mjj);
          if( ((iter).find("AK8PFJet360_TrimMass30")                   != std::string::npos && value)
            || ((iter).find("AK8PFHT700_TrimR0p1PT0p03Mass50")         != std::string::npos && value) ) passedSubstructure = true;
          // || ((iter).find("AK8DiPFJet280_200_TrimMass30_BTagCSV0p45")!= std::string::npos && value)) passedSubstructure = true;
        }
        
        if( passedHT )          Hist( "HT" )->Fill( Mjj);
        if( passedSubstructure )Hist( "Substructure" )->Fill( Mjj);
        if( passedALL )         Hist( "ALL" )->Fill( Mjj);
        
      } //Second loop
    }
    //EVERYTHING ABOVE USES PFHT650 DENOMINATOR!!!-------------------------------------------------------------------------------------------------------|
  }
  // }
  return;
}

//==============================================================================================
void ExoDiBosonAnalysis::doJetTriggerEfficiency2( void ){
  
  for( std::map<std::string,bool>::iterator it = (data_.HLT_isFired)->begin(); it != (data_.HLT_isFired)->end(); it++){ //map1 loop
    std::string trigName = it->first;
    bool decision = it->second;
    //HLT_IsoMu24_eta2p1_v2 or PFJet320

    if( (trigName.find("PFJet320") != std::string::npos && decision) ){ 
      Hist( "PFJet320_SD" )->Fill( Vcand.at(0).softdropMass);
      Hist( "PFJet320_P" )->Fill( Vcand.at(0).prunedMass);

      bool passedSub = false;
      for( std::map<std::string,bool>::iterator it2 = (data_.HLT_isFired)->begin(); it2 != (data_.HLT_isFired)->end(); it2++){ //map2 loop
        std::string iter = it2->first;
        bool value = it2->second;

        if( iter.find("AK8PFJet360_TrimMass30")                     != std::string::npos && value ){
          Hist( "PFJet360_Trim_SD" ) ->Fill( Vcand.at(0).softdropMass);
          Hist( "PFJet360_Trim_P"  ) ->Fill( Vcand.at(0).prunedMass);
        }
        if( iter.find("AK8PFHT700_TrimR0p1PT0p03Mass50")            != std::string::npos && value ){
          Hist( "HT700_Trim_SD"    ) ->Fill( Vcand.at(0).softdropMass);
          Hist( "HT700_Trim_P"    ) ->Fill( Vcand.at(0).prunedMass);
        }
        if( iter.find("AK8DiPFJet280_200_TrimMass30_BTagCSV0p45")   != std::string::npos && value ){
          Hist( "DiPFJet280_200_TrimMass30_SD" ) ->Fill( Vcand.at(0).softdropMass);
          Hist( "DiPFJet280_200_TrimMass30_P" ) ->Fill( Vcand.at(0).prunedMass);
        }
        if( (iter.find("AK8PFJet360_TrimMass30")                    != std::string::npos && value)
          || (iter.find("AK8PFHT700_TrimR0p1PT0p03Mass50")          != std::string::npos && value)
            || (iter.find("AK8DiPFJet280_200_TrimMass30_BTagCSV0p45") != std::string::npos && value ))passedSub = true;
      } //map2 loop
        
      if(passedSub){
        Hist( "Substructure_SD" ) ->Fill(Vcand.at(0).softdropMass);
        Hist( "Substructure_P" )  ->Fill(Vcand.at(0).prunedMass);
      }  
    }
  }

  return;
}

//==============================================================================================

void ExoDiBosonAnalysis::doGenTTReco( void ){
  int nrBquarks = 0;
  int nrquarks = 0;
  int indx = -1;
  float dMmin = 999;
  float Mmin = 999;
  float chi2 = 999;
  float Mt1 = 0;
  float Mt2 = 0;
  TLorentzVector genP;
  std::vector<JetCandidate	>	AdditionalJ	;
  
  nBTags = 0;
  TLorentzVector jet;
  for( unsigned int j = 0; j < (data_.jetAK4_pt)->size(); ++j ){ 
    if( (*data_.jetAK4_IDLoose).at(j) != 1 ) continue;
    if( (*data_.jetAK4_pt).at(j) <= 30. ) continue;
    if( fabs((*data_.jetAK4_eta).at(j)) >= JetEtaCut_ ) continue;
    jet.SetPtEtaPhiE( (*data_.jetAK4_pt).at(j), (*data_.jetAK4_eta).at(j), (*data_.jetAK4_phi).at(j), (*data_.jetAK4_e).at(j) );
    JetCandidate Ajet(jet);
    Ajet.csv = (*data_.jetAK4_csv).at(j);
    Ajet.flavor = abs((*data_.jetAK4_flavor).at(j));
    AdditionalJ.push_back(Ajet);
  }
  
  
  std::map<int,TLorentzVector>::iterator it = genCandidates_.find(24)!=genCandidates_.end() ? genCandidates_.find(24) : genCandidates_.find(-24);
  // setGenCandidates();
  
  for( unsigned int p = 0; p < (data_.genParticle_pdgId)->size(); ++p ){
    if( (*data_.genParticle_pt).at(p) < 0.1) continue;
    if( (*data_.genParticle_status).at(p) != 4 && (*data_.genParticle_status).at(p) != 22 && (*data_.genParticle_status).at(p) != 23) continue;
     

    for( unsigned int m = 0; m < (*data_.genParticle_mother)[p].size(); ++m ){
      genP.SetPtEtaPhiE( (*data_.genParticle_pt).at(p), (*data_.genParticle_eta).at(p), (*data_.genParticle_phi).at(p), (*data_.genParticle_e).at(p) );

      for(int i=0; i < AdditionalJ.size(); i++ ){
        float dR = genP.DeltaR(AdditionalJ.at(i).p4);
        if(dR<0.4){
          if( abs((*data_.genParticle_pdgId)[p]) == 5 && abs((*data_.genParticle_mother)[p][m]) == 6 ){
            AK4bjetCand_.push_back(AdditionalJ.at(i));
            nrBquarks++;
          }
          else if( abs((*data_.genParticle_pdgId)[p]) != 5 && abs((*data_.genParticle_mother)[p][m]) == 24){
            AK4jetCand_.push_back(AdditionalJ.at(i));
            nrquarks++;
          }
        }
      }     
      
    }  
  }

  if(AK4bjetCand_.size()<2 || AK4jetCand_.size()<2 ) {
    throw SError( SError::SkipEvent );
  }
          
  for(int i=0; i < AK4jetCand_.size(); i++ ){
    if( (AK4bjetCand_.at(0).p4.Pt() == AK4jetCand_.at(i).p4.Pt()) || (AK4bjetCand_.at(1).p4.Pt() == AK4jetCand_.at(i).p4.Pt()))continue;
    for(int j=0; j < AK4jetCand_.size(); j++ ){
      if( (AK4bjetCand_.at(0).p4.Pt() == AK4jetCand_.at(j).p4.Pt()) || (AK4bjetCand_.at(1).p4.Pt() == AK4jetCand_.at(j).p4.Pt()) || j==i)continue;
      float M = (AK4jetCand_.at(j).p4+AK4jetCand_.at(i).p4).M();
      float dM= fabs(80-M);
      if(dM<dMmin) {
        dMmin=dM;
        Mmin = M;
        Mt1 = (AK4jetCand_.at(j).p4+AK4jetCand_.at(i).p4 + AK4bjetCand_.at(0).p4 ).M();
        Mt2 = (AK4jetCand_.at(j).p4+AK4jetCand_.at(i).p4 + AK4bjetCand_.at(1).p4 ).M();
      }
    }
  }
          
  if(fabs(180-Mt1)< fabs(180-Mt2)){
    float deltaWmass = Mmin-pdgMw;
    float deltaTmass = Mt1-pdgMtop;
    chi2 = pow((deltaTmass/pdgWidthtop),2)+pow((deltaWmass/pdgWidthw),2);  
    Hist( "tmass"			      	)->Fill ( Mt1);
    Hist( "Chi2vsTMass"        )->Fill ( chi2,Mt1);
  }
  else if(fabs(180-Mt1)> fabs(180-Mt2)){
    float deltaWmass = Mmin-pdgMw;
    float deltaTmass = Mt2-pdgMtop;
    chi2 = pow((deltaTmass/pdgWidthtop),2)+pow((deltaWmass/pdgWidthw),2);  
    Hist( "Chi2vsTMass"        )->Fill ( chi2,Mt2);
    Hist( "tmass")->Fill ( Mt2);         
  }
          
  Hist( "Chi2"              )->Fill ( chi2, weight_ );
  Hist( "Chi2vsWMass"        )->Fill ( chi2,Mmin);
  Hist( "wmass"			      	)->Fill ( Mmin);				     
      																														  
} 

//////////////////////////////////////////////////////// GEN STUDIES ////////////////////////////////////////////////////////////////////////////
void ExoDiBosonAnalysis::doGroomingStudies(  TString sample  ){
  
  std::map<int,TLorentzVector>::iterator itZ = genCandidates_.find(23)!=genCandidates_.end() ? genCandidates_.find(23) : genCandidates_.find(-23);
  std::map<int,TLorentzVector>::iterator it = genCandidates_.find(24)!=genCandidates_.end() ? genCandidates_.find(24) : genCandidates_.find(-24);
  std::map<int,TLorentzVector>::iterator itH = genCandidates_.find(25)!=genCandidates_.end() ? genCandidates_.find(25) : genCandidates_.find(-25);
    
  std::map<int,TLorentzVector>::iterator itE = genCandidates_.find(11)!=genCandidates_.end() ? genCandidates_.find(11) : genCandidates_.find(-11);
  std::map<int,TLorentzVector>::iterator itM = genCandidates_.find(13)!=genCandidates_.end() ? genCandidates_.find(13) : genCandidates_.find(-13);
  std::map<int,TLorentzVector>::iterator itT = genCandidates_.find(15)!=genCandidates_.end() ? genCandidates_.find(15) : genCandidates_.find(-15);
  
  for( int i = 0; i < abs(Vcand.size()) ; i++){
    if( ((Vcand.at(i).p4).DeltaR(itE->second)) < 0.8 || ((Vcand.at(i).p4).DeltaR(itM->second)) < 0.8 || ((Vcand.at(i).p4).DeltaR(itT->second)) < 0.8) continue;
    
    if ( ((Vcand.at(i).p4).DeltaR(it->second)) < 0.8){
      Hist( "recoWTau21" )->Fill( Vcand.at(i).tau2/Vcand.at(i).tau1,weight_ ); 
      Hist( "recoWPrunedMass" )->Fill( (Vcand.at(i)).prunedMass );
      Hist( "recoWSoftdropMass" )->Fill( (Vcand.at(i)).softdropMass );
      Hist( "recoWMass" )->Fill( (Vcand.at(i)).p4.M() );     
      if( sample.Contains( "WW" ) || sample.Contains( "QW" ) || sample.Contains( "WZ" ) ){
        jet_pt = Vcand.at(i).p4.Pt();
        jet_eta = Vcand.at(i).p4.Eta();
        jet_phi = Vcand.at(i).p4.Phi();
        jet_mass_pruned = Vcand.at(i).prunedMass;
        jet_mass_softdrop = Vcand.at(i).softdropMass;
        jet_tau2tau1 = Vcand.at(i).tau2/Vcand.at(i).tau1;
      }
    }   
    if ( (Vcand.at(i).p4).DeltaR(itH->second) < 0.2){
      Hist( "recoHTau21" )->Fill( Vcand.at(i).tau2/Vcand.at(i).tau1,weight_ ); 
      Hist( "recoHPrunedMass" )->Fill( (Vcand.at(i)).prunedMass );
      Hist( "recoHSoftdropMass" )->Fill( (Vcand.at(i)).softdropMass );      
      if( sample.Contains( "hh" ) ){
        jet_pt = Vcand.at(i).p4.Pt();
        jet_eta = Vcand.at(i).p4.Eta();
        jet_phi = Vcand.at(i).p4.Phi();
        jet_mass_pruned = Vcand.at(i).prunedMass;
        jet_mass_softdrop = Vcand.at(i).softdropMass;
        jet_tau2tau1 = Vcand.at(i).tau2/Vcand.at(i).tau1;
      }
    }    
    if ( (Vcand.at(i).p4).DeltaR(itZ->second) < 0.8){
      Hist( "recoZTau21" )->Fill( Vcand.at(i).tau2/Vcand.at(i).tau1,weight_ ); 
      Hist( "recoZPrunedMass" )->Fill( (Vcand.at(i)).prunedMass );
      Hist( "recoZSoftdropMass" )->Fill( (Vcand.at(i)).softdropMass );      
      if( sample.Contains( "ZZ" ) || sample.Contains( "QZ" ) || sample.Contains( "WZ" ) ){
        jet_pt = Vcand.at(i).p4.Pt();
        jet_eta = Vcand.at(i).p4.Eta();
        jet_phi = Vcand.at(i).p4.Phi();
        jet_mass_pruned = Vcand.at(i).prunedMass;
        jet_mass_softdrop = Vcand.at(i).softdropMass;
        jet_tau2tau1 = Vcand.at(i).tau2/Vcand.at(i).tau1;
      }
    }
  }
  
  bool TwoBosons = true;
  
  for( int i = 0; i < abs(Vcand.size()) ; i++){
    if( ((Vcand.at(i).p4).DeltaR(itE->second)) < 0.8 || ((Vcand.at(i).p4).DeltaR(itM->second)) < 0.8 || ((Vcand.at(i).p4).DeltaR(itT->second)) < 0.8) TwoBosons = false ;
  }
  
  if( TwoBosons){
    // if( sample.Contains( "WW" ) || sample.Contains( "ZZ" ) || sample.Contains( "WZ" ) ){
    //   if ( ((Vcand.at(0).p4).DeltaR(itZ->second) < 0.8 && (Vcand.at(1).p4).DeltaR(itZ->second) < 0.8) ||
    //     ((Vcand.at(0).p4).DeltaR(itH->second) < 0.8 && (Vcand.at(1).p4).DeltaR(itH->second) < 0.8) ||
    //     ((Vcand.at(0).p4).DeltaR(it->second)  < 0.8 && (Vcand.at(1).p4).DeltaR(it->second)  < 0.8) ||
    //     ((Vcand.at(0).p4).DeltaR(it->second) < 0.8 && (Vcand.at(1).p4).DeltaR(itZ->second) < 0.8)  ||
    //     ((Vcand.at(1).p4).DeltaR(it->second) < 0.8 && (Vcand.at(0).p4).DeltaR(itZ->second) < 0.8)  ||
    //     ((Vcand.at(0).p4).DeltaR(it->second) < 0.8 && (Vcand.at(1).p4).DeltaR(itH->second) < 0.8)  ||
    //     ((Vcand.at(1).p4).DeltaR(it->second) < 0.8 && (Vcand.at(0).p4).DeltaR(itH->second) < 0.8)   ) {
    //       std::cout<<"sample = "<<sample<<std::endl;
    //     MVV = (Vcand.at(0).p4 + Vcand.at(1).p4).M();
    //     std::cout<<"MVV = "<<MVV<<std::endl;
    //     Hist( "Mjj") -> Fill( MVV , weight_ );
    //   }
    // }
    // else if( sample.Contains( "QW" ) || sample.Contains( "QZ" ) ){
    // std::cout<<"MVV = "<<MVV<<std::endl;
    MVV = (Vcand.at(0).p4 + Vcand.at(1).p4).M();
    jet_deta = fabs( Vcand.at(0).p4.Eta()  - Vcand.at(1).p4.Eta());
    Hist( "Mjj") -> Fill( MVV , weight_ );
    // }
  }
    
  for( int jj = 0; jj < abs(genJetCand.size()); jj++ ){
    if( ((genJetCand.at(jj).p4).DeltaR(itE->second)) <= 0.8 && ((genJetCand.at(jj).p4).DeltaR(itM->second)) <= 0.8 && ((genJetCand.at(jj).p4).DeltaR(itT->second)) <= 0.8) continue;
    if ( (genJetCand[jj].p4).DeltaR(it->second) < 0.8){
      Hist( "genWMass" )->Fill( (genJetCand[jj].p4).M() ); 
      Hist( "genWSoftdropMass"  )->Fill( (genJetCand.at(jj)).softdropMass);
      Hist( "genWPrunedMass"    )->Fill( (genJetCand.at(jj)).prunedMass);
    }
    if ( (genJetCand[jj].p4).DeltaR(itH->second) < 0.8) Hist( "genHMass" )->Fill( (genJetCand[jj].p4).M() );
    if ( (genJetCand[jj].p4).DeltaR(itZ->second) < 0.8) Hist( "genZMass" )->Fill( (genJetCand[jj].p4).M() );
  }
}
