#include "../ExoDiBosonAnalysis/include/ExoDiBosonAnalysis.h"
#include "../ExoDiBosonAnalysis/include/Utilities.h"
#include "../ExoDiBosonAnalysis/include/HistosManager.h"
#include "../ExoDiBosonAnalysis/include/NtupleManager.h"
#include "../ExoDiBosonAnalysis/include/MatchingTools.h"

#include <iostream>
#include <TRandom.h>

//==============================================================================================
ClassImp( ExoDiBosonAnalysis );

//==============================================================================================
ExoDiBosonAnalysis::ExoDiBosonAnalysis()
  : SCycleBase()
    , weight_(1.)
    , genweight_(1.)
    , puweight_(1.)
    , hltweight_(1.)
    , btagweight_(1.)
    , lumiweight_(1.){

  SetLogName( GetName() );
  /* general settings */   
  DeclareProperty( "InputTreeName"		, InputTreeName_	);
  DeclareProperty( "OutputTreeName"		, OutputTreeName_	);
  DeclareProperty( "isSignal"         , isSignal_				);
  DeclareProperty( "runOnMC"          , runOnMC_				);
  DeclareProperty( "GenStudies"       , GenStudies_			);
  DeclareProperty( "Channel"          , Channel_				);
  DeclareProperty( "MassWindow"       , MassWindow_     );
  DeclareProperty( "Trigger"          , Trigger_				);
  DeclareProperty( "applyFilters"     , applyFilters_   );
	 
  /* leptonic selections */
  DeclareProperty( "LeptPtCut"			, leptPtCut_			  );
  DeclareProperty( "LeptEtaCut"			, leptEtaCut_			  );
  DeclareProperty( "AleptPtCut"			, AleptPtCut_			  );
  DeclareProperty( "AleptEtaCut"		, AleptEtaCut_		  );
  DeclareProperty( "METCut"					, METCut_					  );

  /* jet selections */
  DeclareProperty( "MjjCut"						, MjjCut_					);
  DeclareProperty( "dEtaCut"					, dEtaCut_				);
  DeclareProperty( "JetPtCutLoose"		, JetPtCutLoose_	);
  DeclareProperty( "JetPtCutTight"		, JetPtCutTight_	);
  DeclareProperty( "JetEtaCut"        , JetEtaCut_			);  
  DeclareProperty( "Tau21Cut"         , Tau21Cut_				);  
  DeclareProperty( "Tau21HPLow"       , Tau21HPLow_			);
  DeclareProperty( "Tau21HPHigh"			, Tau21HPHigh_		);
  DeclareProperty( "Tau21Low"       	, Tau21Low_		  	);
  DeclareProperty( "Tau21High"     	  , Tau21High_	  	);
	        
  /* pruned mass */ 
  DeclareProperty( "UsePruned"        , UsePruned_			);
  DeclareProperty( "mZLow"						, mZLow_			    );
  DeclareProperty( "mZHigh"					  , mZHigh_	      	);
  DeclareProperty( "mWLow"						, mWLow_		    	);
  DeclareProperty( "mWHigh"					  , mWHigh_		      );
	
  /* weights settings */
  DeclareProperty( "xSec"							, xSec_					  );
  DeclareProperty( "genEvents"				, genEvents_		  );
  DeclareProperty( "Lumi"							, Lumi_					  );
  DeclareProperty( "PUdata"						, PUProfileData_  );
  DeclareProperty( "JSONfile"         , JSONfile_       );
  
  DeclareProperty( "BTagEff4vetoData"  , BTagEff4vetoData_   );
  DeclareProperty( "BTagEff4fatjetData", BTagEff4fatjetData_ );
  DeclareProperty( "BTagEff4subjetData", BTagEff4subjetData_ );
      
            
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
 
	
  
  nPassedChi2_          = 0;
  
  nPassedFoundLept_ = 0;
  nPassedVetoLep_   = 0;
  nPassedFoundMET_  = 0;
  nPassedFoundW_    = 0;
  nPassedFoundJet_  = 0;
  nPassedLepJetDR_  = 0;
  nPassed1bTag_     = 0;
  
  jetINDX     					= 99;
  
  nPassedFilter_HBHEIso_             = 0;
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
  
  // setPredictedDistribution();
   
}

//==============================================================================================
ExoDiBosonAnalysis::~ExoDiBosonAnalysis() {

  // TFile * fout = new TFile("hvv_pred.root", "RECREATE");
  //  hvv_pred->GetPredictedHist()->Write();
  //  hvv_pred->GetTaggableHist()->Write();
  //  hvv_pred->GetObservedHist()->Write();
  //  if ( hvv_pred )
  //    delete hvv_pred;
  //  if ( fout )
  //    delete fout;
  //  if ( hMistag_ )
  //    delete hMistag_;
  //  if ( fMistag_ )
     // delete fMistag_;
	
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
  
  if( !runOnMC_ && JSONfile_ != "" ){
   m_logger << INFO << "Loading GoodRunsList from file: " << JSONfile_ << SLogger::endmsg;
   Root::TGoodRunsListReader reader( TString( JSONfile_.c_str() ) );
   if( ! reader.Interpret() ) {
     m_logger << FATAL << "Couldn't read in the GRL!" << SLogger::endmsg;
     throw SError( ( "Couldn't read in file: " + JSONfile_ ).c_str(), SError::SkipCycle );
   }
   m_grl = reader.GetMergedGoodRunsList();
   m_grl.Summary();
   m_grl.SetName( "MyGoodRunsList" );

   //
   // Add it as a configuration object, so that the worker nodes will receive it:
   //
   AddConfigObject( &m_grl );
  }
                     
  return;

}
//==============================================================================================
void ExoDiBosonAnalysis::initWeight( void ){

  TString infile = TString(this->GetHistInputFile()->GetName());
  
  std::cout<<infile<<std::endl;
  
  std::string scenario = "PUS25ns";
  if( infile.Contains("16Dec2015") or infile.Contains("Fall15") ) scenario = "PUS25ns76X";
  
  PUWeight::Scenario sc = PUWeight_.toScenario(scenario);
  PUWeight_.initPUWeights(PUProfileData_,sc);
  
  HLTWeight::Channel ch = HLTWeight_.toChannel(Channel_);
  HLTWeight_.initHLTWeights(ch);
  
  BTagWeight_.initBTagWeights(BTagEff4vetoData_,BTagEff4fatjetData_,BTagEff4subjetData_);

  // TFile* fPUweights = TFile::Open(PUProfileData_.c_str(),"READ");
  // hPUweights_ = (TH1F*)fPUweights->Get("puweights");
   
}

//==============================================================================================
void ExoDiBosonAnalysis::BeginInputFile( const SInputData& ) throw( SError ) {
  
  TString infile = TString(this->GetHistInputFile()->GetName());

  theNtupleManager_->ConnectVariables( InputTreeName_, runOnMC_ , infile );
  
  // Initialize weights
  initWeight(); 
         
  return;
}

//==============================================================================================
void ExoDiBosonAnalysis::BeginInputData( const SInputData& ) throw( SError ) {
  
  if( !runOnMC_ ) {
   TObject* grl;
   if( ! ( grl = GetConfigObject( "MyGoodRunsList" ) ) ) {
     m_logger << FATAL << "Can't access the GRL!" << SLogger::endmsg;
     throw SError( "Can't access the GRL!", SError::SkipCycle );
   }
   m_grl = *( dynamic_cast< Root::TGoodRunsList* >( grl ) );
  }
	
      
  theHistosManager_->bookHistos(Channel_); 
  
  DeclareVariable( puweight_      , "puweight"         , OutputTreeName_.c_str() );
  DeclareVariable( lumiweight_    , "lumiweight"        , OutputTreeName_.c_str() );
  DeclareVariable( genweight_    , "genweight"         , OutputTreeName_.c_str() );
  DeclareVariable( btagweight_ 	 , "btagweight"        , OutputTreeName_.c_str() );
  DeclareVariable( weight	   	   , "weight"	       , OutputTreeName_.c_str() );
  DeclareVariable( run     	 , "run"	       , OutputTreeName_.c_str() );
  DeclareVariable( event     	 , "event"	       , OutputTreeName_.c_str() );
  DeclareVariable( lumi     	 , "lumi"	       , OutputTreeName_.c_str() );
  DeclareVariable( nPVs    , "nPV"        , OutputTreeName_.c_str() );
  
  
  if( Channel_.find("WtagSF") != std::string::npos ){
    DeclareVariable( hltweight_         , "hltweight"         , OutputTreeName_.c_str() );
    DeclareVariable( MWW                , "MWW"         , OutputTreeName_.c_str() );
    DeclareVariable( jet_mass_pruned    , "Whadr_pruned", OutputTreeName_.c_str() );
    DeclareVariable( jet_csv            , "Whadr_csv"   , OutputTreeName_.c_str() );
    DeclareVariable( jet_pt             , "Whadr_pt"    , OutputTreeName_.c_str() );
    DeclareVariable( jet_eta            , "Whadr_eta"   , OutputTreeName_.c_str() );
    DeclareVariable( jet_phi            , "Whadr_phi"   , OutputTreeName_.c_str() );
    DeclareVariable( realW              , "Whadr_isW"   , OutputTreeName_.c_str() );
    DeclareVariable( jet_tau2tau1       , "Whadr_tau21" , OutputTreeName_.c_str() );
    DeclareVariable( l_pt               , "lept_pt"     , OutputTreeName_.c_str() );
    DeclareVariable( l_eta              , "lept_eta"    , OutputTreeName_.c_str() );
    DeclareVariable( l_phi              , "lept_phi"    , OutputTreeName_.c_str() );
    DeclareVariable( l_iso              , "lept_iso"    , OutputTreeName_.c_str() );
    DeclareVariable( Wlept_pt           , "Wlept_pt"    , OutputTreeName_.c_str() ); 
    DeclareVariable( Wlept_mt           , "Wlept_mt"    , OutputTreeName_.c_str() );
    DeclareVariable( WMass              , "Wlept_mass"  , OutputTreeName_.c_str() );
    DeclareVariable( pfMET              , "pfMET"       , OutputTreeName_.c_str() ); 
    DeclareVariable( pfMETPhi           , "pfMETPhi"    , OutputTreeName_.c_str() );
    DeclareVariable( nak4jets           , "nak4jets"    , OutputTreeName_.c_str() );
  }
  if( Channel_.find("dijet") != std::string::npos ){
  DeclareVariable( channel                 	 , "channel"	       , OutputTreeName_.c_str() );
  DeclareVariable( category     	           , "category"	       , OutputTreeName_.c_str() );
  DeclareVariable( jet_deta                  , "jet_deta"           , OutputTreeName_.c_str() );
  DeclareVariable( MVV                       , "MVV"               , OutputTreeName_.c_str() );
  DeclareVariable( jet_mass_jet1             , "jet_mass_jet1"	       , OutputTreeName_.c_str() );
  DeclareVariable( jet_mass_jet2             , "jet_mass_jet2"	       , OutputTreeName_.c_str() );
  DeclareVariable( jet_mass_pruned_jet1      , "jet_mass_pruned_jet1"   , OutputTreeName_.c_str() );
  DeclareVariable( jet_mass_pruned_jet2      , "jet_mass_pruned_jet2"   , OutputTreeName_.c_str() );
  DeclareVariable( jet_mass_pruned_W1        , "jet_mass_pruned_W1"   , OutputTreeName_.c_str() );
  DeclareVariable( jet_mass_pruned_W2        , "jet_mass_pruned_W2"   , OutputTreeName_.c_str() );
  DeclareVariable( jet_mass_pruned_Z1        , "jet_mass_pruned_Z1"   , OutputTreeName_.c_str() );
  DeclareVariable( jet_mass_pruned_Z2        , "jet_mass_pruned_Z2"   , OutputTreeName_.c_str() );
  DeclareVariable( jet_mass_softdrop_jet1    , "jet_mass_softdrop_jet1" , OutputTreeName_.c_str() );
  DeclareVariable( jet_mass_softdrop_jet2    , "jet_mass_softdrop_jet2" , OutputTreeName_.c_str() );
  DeclareVariable( jet_pt_jet1               , "jet_pt_jet1"            , OutputTreeName_.c_str() );
  DeclareVariable( jet_pt_jet2               , "jet_pt_jet2"            , OutputTreeName_.c_str() );
  DeclareVariable( jet_eta_jet1              , "jet_eta_jet1"           , OutputTreeName_.c_str() );
  DeclareVariable( jet_eta_jet2              , "jet_eta_jet2"           , OutputTreeName_.c_str() );
  DeclareVariable( jet_phi_jet1              , "jet_phi_jet1"			    	, OutputTreeName_.c_str() );
  DeclareVariable( jet_phi_jet2              , "jet_phi_jet2"			    	, OutputTreeName_.c_str() );
  DeclareVariable( jet_tau2tau1_jet1         , "jet_tau2tau1_jet1"		  , OutputTreeName_.c_str() );
  DeclareVariable( jet_tau2tau1_jet2         , "jet_tau2tau1_jet2"		  , OutputTreeName_.c_str() );
  
  // DeclareVariable( sum_genweights       , "sum_genweights"        , OutputTreeName_.c_str() );
  // DeclareVariable( jet_rho              , "jet_rho"            , OutputTreeName_.c_str() );
  
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
  genJetCand      .clear();
  Leptonicb_			.clear();
  Hadronicb_			.clear();
  HadronicJ_			.clear();
  PrunedSubjetCand_  .clear();
  SoftdropSubjetCand_.clear(); 
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
  
  btagvetow = 1.; 
  htagw = 1.;
  
  if( Channel_.find("WtagSF_mu") != std::string::npos ) hltweight_ = HLTWeight_.getHLTWeight( leptonCand_[0].p4.Pt(), leptonCand_[0].p4.Eta() );
  if( Channel_.find("WtagSF")    != std::string::npos ) btagvetow = BTagWeight_.getBTagWeight( AK4jetCand_, "veto" );
 
  btagweight_ =  btagvetow*htagw;
    
  double lumiw = xSec_/genEvents_;     
  lumiweight_ = lumiw*LumiWeight_.getLumiWeight( infile )*Lumi_; 
  genweight_ = data_.genWeight < 0 ? -1 : 1; 
 
  weight_ = puweight_*lumiweight_*genweight_*hltweight_; 

  
}

//==============================================================================================
void ExoDiBosonAnalysis::ExecuteEvent( const SInputData&, Double_t ) throw( SError ) {
  
	
  // Connect branches in tree
  initData();
  
  // // Initialize weights
  // initWeight();
  
  // Reset vectors
  reset();
   
  ////////////////////////////////////////////////////////////////////////////////////////////////////////
  //// Dijet analysis begins HERE/////////////////////////////////////////////////////////////////////////
  if( Channel_ == "VVdijet" || Channel_ == "qVdijet" ){
    
    TString infile = TString(this->GetHistInputFile()->GetName());
    setWeight(infile);
    
    int gW = data_.genWeight < 0 ? -1 : 1;
    nSumGenWeights_+=gW;
    sum_genweights+=gW;

    if( GenStudies_ ) setGenCandidates(); 

    Hist( "runNumber" )->Fill(data_.EVENT_run);

    nEvents_++;

    if( !passedTrigger() ) throw SError( SError::SkipEvent );
    nPassedTrigger_++;  
    if( !passedFilters() ) throw SError( SError::SkipEvent );
    nPassedFilters_++;
    
    // if( passedDijetSelectionsAK4(infile) ){
    //   Hist( "MjjAK4" ) -> Fill( ( AK4jetCand_.at(0).p4 + AK4jetCand_.at(1).p4 ).M() , weight_ );
    // }
      
    if( passedDijetSelections(infile) ) {
      
      bool passedTau21Cut				= false;
      
      if( Channel_ == "VVdijet"){
        channel = -1;
        //HP category
        if ( Vcand.at(0).tau2/Vcand.at(0).tau1 > Tau21HPLow_ && Vcand.at(0).tau2/Vcand.at(0).tau1 <= Tau21HPHigh_ && Vcand.at(1).tau2/Vcand.at(1).tau1 > Tau21HPLow_ && Vcand.at(1).tau2/Vcand.at(1).tau1 <= Tau21HPHigh_  ){
          passedTau21Cut = true ;
          
          if( (Vcand.at(0).prunedMass > mWLow_ && Vcand.at(0).prunedMass <= mZHigh_ && Vcand.at(1).prunedMass > mWLow_ && Vcand.at(1).prunedMass <= mZHigh_) ){
            category = 0; //VVHP
            if( (Vcand.at(0).prunedMass > mWLow_ && Vcand.at(0).prunedMass <= mWHigh_) && (Vcand.at(1).prunedMass > mWLow_   && Vcand.at(1).prunedMass <= mWHigh_))  channel = 2; //WWHP
            else if( (Vcand.at(0).prunedMass > mWLow_ && Vcand.at(0).prunedMass <= mWHigh_) && (Vcand.at(1).prunedMass > mZLow_   && Vcand.at(1).prunedMass <= mZHigh_))  channel = 4; //WZHP
            else if( (Vcand.at(1).prunedMass > mWLow_ && Vcand.at(1).prunedMass <= mWHigh_) && (Vcand.at(0).prunedMass > mZLow_   && Vcand.at(0).prunedMass <= mZHigh_))  channel = 4; //ZWHP
            else if( (Vcand.at(0).prunedMass > mZLow_ && Vcand.at(0).prunedMass <= mZHigh_) && (Vcand.at(1).prunedMass > mZLow_   && Vcand.at(1).prunedMass <= mZHigh_))  channel = 6; //ZZHP
          }
        }
        
        //LP category
        else if( ( Vcand.at(0).tau2/Vcand.at(0).tau1 > Tau21HPLow_ && Vcand.at(0).tau2/Vcand.at(0).tau1 <= Tau21HPHigh_ && Vcand.at(1).tau2/Vcand.at(1).tau1 > Tau21Low_ && Vcand.at(1).tau2/Vcand.at(1).tau1 <= Tau21High_  ) ||
        ( Vcand.at(1).tau2/Vcand.at(1).tau1 > Tau21HPLow_ && Vcand.at(1).tau2/Vcand.at(1).tau1 <= Tau21HPHigh_ && Vcand.at(0).tau2/Vcand.at(0).tau1 > Tau21Low_ && Vcand.at(0).tau2/Vcand.at(0).tau1 <= Tau21High_) ){
          
          if( (Vcand.at(0).prunedMass > mWLow_ && Vcand.at(0).prunedMass <= mZHigh_) && (Vcand.at(1).prunedMass > mWLow_   && Vcand.at(1).prunedMass <= mZHigh_))  {
            category = 1;  //VVLP
             
            if( (Vcand.at(0).prunedMass > mWLow_ && Vcand.at(0).prunedMass <= mWHigh_) && (Vcand.at(1).prunedMass > mWLow_   && Vcand.at(1).prunedMass <= mWHigh_))  channel = 3; //WWLP
            else if( (Vcand.at(0).prunedMass > mWLow_ && Vcand.at(0).prunedMass <= mWHigh_) && (Vcand.at(1).prunedMass > mZLow_   && Vcand.at(1).prunedMass <= mZHigh_))  channel = 5; //WZLP
            else if( (Vcand.at(1).prunedMass > mWLow_ && Vcand.at(1).prunedMass <= mWHigh_) && (Vcand.at(0).prunedMass > mZLow_   && Vcand.at(0).prunedMass <= mZHigh_))  channel = 5; //ZWLP
            else if( (Vcand.at(0).prunedMass > mZLow_ && Vcand.at(0).prunedMass <= mZHigh_) && (Vcand.at(1).prunedMass > mZLow_   && Vcand.at(1).prunedMass <= mZHigh_))  channel = 7; //ZZLP
          } 
        }
        // NP category
        else{
          if( (Vcand.at(0).prunedMass > mWLow_ && Vcand.at(0).prunedMass <= mZHigh_) && (Vcand.at(1).prunedMass > mWLow_   && Vcand.at(1).prunedMass <= mZHigh_))  {
            category = 4;  //VVNP

                 if( Vcand.at(0).prunedMass > mWLow_ && Vcand.at(0).prunedMass <= mWHigh_ && Vcand.at(1).prunedMass > mWLow_   && Vcand.at(1).prunedMass <= mWHigh_)  channel = 14; //WWNP
            else if( Vcand.at(0).prunedMass > mWLow_ && Vcand.at(0).prunedMass <= mWHigh_ && Vcand.at(1).prunedMass > mZLow_   && Vcand.at(1).prunedMass <= mZHigh_)  channel = 15; //WZNP
            else if( Vcand.at(1).prunedMass > mWLow_ && Vcand.at(1).prunedMass <= mWHigh_ && Vcand.at(0).prunedMass > mZLow_   && Vcand.at(0).prunedMass <= mZHigh_)  channel = 15; //ZWNP
            else if( Vcand.at(0).prunedMass > mZLow_ && Vcand.at(0).prunedMass <= mZHigh_ && Vcand.at(1).prunedMass > mZLow_   && Vcand.at(1).prunedMass <= mZHigh_)  channel = 16; //ZZNP
          }
        }
      }  
      
      else if( Channel_ == "qVdijet"){
        channel = -1;
        for( int i = 0; i < abs(Vcand.size()) ; i++){   
          //HP
          if( Vcand.at(i).tau2/Vcand.at(i).tau1 > Tau21HPLow_ && Vcand.at(i).tau2/Vcand.at(i).tau1 <= Tau21HPHigh_ ){
            passedTau21Cut = true;
            if(! (Vcand.at(i).prunedMass > mWLow_ && Vcand.at(i).prunedMass <= mZHigh_)) continue;
            category = 2; //qVHP
            jetINDX=i;
            if (Vcand.at(i).prunedMass > mWLow_ && Vcand.at(i).prunedMass <= mWHigh_) channel = 10; //qWHP
            else if (Vcand.at(i).prunedMass > mZLow_ && Vcand.at(i).prunedMass <= mZHigh_) channel = 12; //qZHP
          }
          //LP
          else if( Vcand.at(i).tau2/Vcand.at(i).tau1 > Tau21Low_ && Vcand.at(i).tau2/Vcand.at(i).tau1 <= Tau21High_ ){
            if( !(Vcand.at(i).prunedMass > mWLow_ && Vcand.at(i).prunedMass <= mZHigh_) ) continue;
            category = 3; //qVLP
            jetINDX=i;

            if (Vcand.at(i).prunedMass > mWLow_ && Vcand.at(i).prunedMass <= mWHigh_) channel = 11; //qWLP
            else if (Vcand.at(i).prunedMass > mZLow_ && Vcand.at(i).prunedMass <= mZHigh_) channel = 13; //qZLP
          }
      
          else{
            if(! (Vcand.at(i).prunedMass > mWLow_ && Vcand.at(i).prunedMass <= mZHigh_))continue;
            category = 5; //qVNP
            jetINDX=i;
            if (Vcand.at(i).prunedMass > mWLow_ && Vcand.at(i).prunedMass <= mWHigh_) channel = 17; //qWNP
            else if (Vcand.at(i).prunedMass > mZLow_ && Vcand.at(i).prunedMass <= mZHigh_) channel = 18; //qZNP
          }
        }
      }
      
      weight = weight_;
      run = data_.EVENT_run;
      event = data_.EVENT_event;
      lumi = data_.EVENT_lumi;
      MVV = (Vcand.at(0).p4 + Vcand.at(1).p4).M();
      jet_deta = fabs( Vcand.at(0).p4.Eta()  - Vcand.at(1).p4.Eta());	     
      jet_mass_jet1 = Vcand.at(0).p4.M();
      jet_mass_softdrop_jet1 = Vcand.at(0).softdropMass;
      jet_mass_pruned_jet1 = Vcand.at(0).prunedMass;
      jet_pt_jet1 = Vcand.at(0).p4.Pt();
      jet_eta_jet1 = Vcand.at(0).p4.Eta();
      jet_phi_jet1 = Vcand.at(0).p4.Phi();
      jet_tau2tau1_jet1 = Vcand.at(0).tau2/Vcand.at(0).tau1;     
      jet_mass_jet2 = Vcand.at(1).p4.M();
      jet_mass_softdrop_jet2 = Vcand.at(1).softdropMass;
      jet_mass_pruned_jet2 = Vcand.at(1).prunedMass;
      jet_pt_jet2 = Vcand.at(1).p4.Pt();
      jet_eta_jet2 = Vcand.at(1).p4.Eta();
      jet_phi_jet2 = Vcand.at(1).p4.Phi();
      jet_tau2tau1_jet2 = Vcand.at(1).tau2/Vcand.at(1).tau1;
      nPVs = data_.nPVs;
      
      fillHistos(Channel_);
      
    }
    
    else
      throw SError( SError::SkipEvent );
  }
  
  else if( Channel_ == "SFmuJets"){
    
    TString infile = TString(this->GetHistInputFile()->GetName());
    setWeight(infile);
    Hist( "runNumber" )->Fill(data_.EVENT_run);
  
    nEvents_++;
    if( !passedTrigger() ) throw SError( SError::SkipEvent );
    nPassedTrigger_++;
        
    if( !passedFilters() ) throw SError( SError::SkipEvent );
    nPassedFilters_++;
    
    Hist( "nVertices" )->Fill(data_.nPVs, weight_);
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
  
 
  else if( Channel_.find("WtagSF") != std::string::npos){
    
    int gW = data_.genWeight < 0 ? -1 : 1;
    nSumGenWeights_+=gW;
    
    isLowMass = false;
    if (leptPtCut_ < 50) isLowMass = true ; 
    TString infile = TString(this->GetHistInputFile()->GetName());
    
    
    Hist( "runNumber" )->Fill(data_.EVENT_run);
    nEvents_++;
    
    if( !applyJSON() ) throw SError( SError::SkipEvent );
    
    if( !passedTrigger() ) throw SError( SError::SkipEvent );
    nPassedTrigger_++;
        
    if( !passedFilters() ) throw SError( SError::SkipEvent );
    nPassedFilters_++;
    
    if( passedTTbarSelections() ){
      setWeight(infile);
     
      
      findExoCandidate();
      
      
      int isW = 0;
      
      if( runOnMC_ ){
        TLorentzVector genP;   
        double genptV = -99;
        for( unsigned int p = 0; p < (data_.genParticle_pdgId)->size(); ++p ){
          if( (*data_.genParticle_pt).at(p) < 0.1) continue;
          if( fabs((*data_.genParticle_pdgId).at(p)) != 24) continue;
          if( not infile.Contains( "herwig" ) && (*data_.genParticle_status).at(p) != 4 && (*data_.genParticle_status).at(p) != 22 && (*data_.genParticle_status).at(p) != 23) continue;
          if( infile.Contains( "herwig" ) && (*data_.genParticle_status).at(p) != 11 ) continue;
          genP.SetPtEtaPhiE( (*data_.genParticle_pt).at(p), (*data_.genParticle_eta).at(p), (*data_.genParticle_phi).at(p), (*data_.genParticle_e).at(p) );
          if( (Vcand.at(0).p4).DeltaR(genP) < 0.3 ) {
            isW = 1;
            break;
          }
        }
      }
      
      
      realW = isW;  
      weight = weight_;
      run = data_.EVENT_run;
      event = data_.EVENT_event;
      lumi = data_.EVENT_lumi;
      nPVs = data_.nPVs;
      jet_mass_pruned = Vcand.at(0).prunedMass;
      jet_csv = Vcand.at(0).csv;
      jet_pt = Vcand.at(0).p4.Pt();
      jet_eta = Vcand.at(0).p4.Eta();
      jet_phi = Vcand.at(0).p4.Phi();
      jet_tau2tau1 = Vcand.at(0).tau2/Vcand.at(0).tau1;
      l_pt  = leptonCand_[0].p4.Pt();
      l_eta = leptonCand_[0].p4.Eta();
      l_phi = leptonCand_[0].p4.Phi();
      l_iso = leptonCand_[0].iso;
      Wlept_pt = WCand_[0].p4.Pt();
      Wlept_mt = TMath::Sqrt( 2*METCand_[0].p4.Pt()*leptonCand_[0].p4.Pt()*(1-cos(leptonCand_[0].p4.DeltaPhi(METCand_[0].p4))) );
      pfMET = METCand_[0].p4.Pt();
      pfMETPhi = METCand_[0].p4.Phi();	
      nak4jets = AK4jetCand_.size();
    }
    else
      throw SError( SError::SkipEvent );
  }
  else
    return;
}

//==============================================================================================
bool ExoDiBosonAnalysis::applyJSON( void ){

   if( runOnMC_ || JSONfile_ == "" ) return true;
   return m_grl.HasRunLumiBlock( data_.EVENT_run, data_.EVENT_lumi );

   //bool isGood = m_grl.HasRunLumiBlock( data_.EVENT_run, data_.EVENT_lumi );
   //if( !isGood ) m_logger << DEBUG << "Bad event! Run: " << data_.EVENT_run <<  " - Lumi Section: " << data_.EVENT_lumi << SLogger::endmsg;
   //else m_logger << DEBUG << "Good event! Run: " << data_.EVENT_run <<  " - Lumi Section: " << data_.EVENT_lumi << SLogger::endmsg;

}

//Passed filters
//==============================================================================================
bool ExoDiBosonAnalysis::passedFilters( void ){
  
  if( data_.PV_filter ) nPassedGoodPVFilter_++;
  else return false;
  
  if( !applyFilters_ ) return true;

  //if( data_.PV_filter                       ) nPassedGoodPVFilter_++;       
  if( data_.passFilter_HBHELoose_           ) nPassedFilter_HBHE_++;
  if( data_.passFilter_HBHEIso_             ) nPassedFilter_HBHEIso_++;
  if( data_.passFilter_CSCHalo_             ) nPassedFilter_CSCHalo_++;
  if( data_.passFilter_HCALlaser_	     ) nPassedFilter_HCALlaser_++;
  if( data_.passFilter_ECALDeadCell_        ) nPassedFilter_ECALDeadCell_++;
  if( data_.passFilter_GoodVtx_	     ) nPassedFilter_GoodVtx_++;
  if( data_.passFilter_TrkFailure_	     ) nPassedFilter_TrkFailure_++;
  if( data_.passFilter_EEBadSc_	     ) nPassedFilter_EEBadSc_++;
  if( data_.passFilter_ECALlaser_           ) nPassedFilter_ECALlaser_++;
  if( data_.passFilter_TrkPOG_              ) nPassedFilter_TrkPOG_++;
  if( data_.passFilter_TrkPOG_manystrip_    ) nPassedFilter_TrkPOG_manystrip_++;
  if( data_.passFilter_TrkPOG_toomanystrip_ ) nPassedFilter_TrkPOG_toomanystrip_++;
  if( data_.passFilter_TrkPOG_logError_     ) nPassedFilter_TrkPOG_logError_++;
  if( data_.passFilter_METFilters_	     ) nPassedFilter_METFilters_++;
  //if( isGood ) nPassedFilter_EventList_++;          
  
  //bool passMETFiltersAll = data_.passFilter_HBHE_ && data_.passFilter_CSCHalo_ && data_.passFilter_HCALlaser_;
  bool passMETFiltersAll = data_.passFilter_CSCHalo_ && data_.passFilter_HCALlaser_;
  passMETFiltersAll = passMETFiltersAll && data_.passFilter_ECALDeadCell_ && data_.passFilter_GoodVtx_ && data_.passFilter_TrkFailure_;
  passMETFiltersAll = passMETFiltersAll && data_.passFilter_EEBadSc_ && data_.passFilter_ECALlaser_ && data_.passFilter_TrkPOG_;
  
  bool passTrkFiltersAll = data_.passFilter_TrkPOG_manystrip_ && data_.passFilter_TrkPOG_toomanystrip_ && data_.passFilter_TrkPOG_logError_;
     
  if( passMETFiltersAll ) nPassedMETFiltersAll_++;
  if( passTrkFiltersAll ) nPassedTrkFiltersAll_++;
  
  bool passAllfilters = data_.passFilter_HBHELoose_ && data_.passFilter_HBHEIso_ && data_.passFilter_CSCHalo_ && data_.PV_filter && data_.passFilter_EEBadSc_;
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
    trignames.push_back("Mu45_eta2p1_") ;
  }
  else if( Channel_ == "SFeleJets"){
    trignames.push_back("Ele27_eta2p1_WPLoose_Gsf") ;
  }
  
  else if( Channel_.find("WtagSF_mu") != std::string::npos){
     if (isLowMass) trignames.push_back("HLT_IsoMu27_v");
     else{
       trignames.push_back("HLT_Mu45_eta2p1");
       trignames.push_back("HLT_Mu50");
     }
  }
  
  else if( Channel_.find("WtagSF_el") != std::string::npos ){
    if (isLowMass){
      trignames.push_back("HLT_Ele27_eta2p1_WPLoose_Gsf_v"); //DATA
      trignames.push_back("HLT_Ele27_eta2p1_WP75_Gsf_"); //MC
  }
  else{
    trignames.push_back("HLT_Ele105_CaloIdVT_GsfTrkIdT");
    trignames.push_back("HLT_Ele115_CaloIdVT_GsfTrkIdT");
   }
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

bool ExoDiBosonAnalysis::passedDijetSelectionsAK4(  TString infile  ){
  bool foundTwoJets					= false;
  bool passedDeltaEtaCut		= false;
  bool passedMjjCut					= false;
	
  //Make sure events contains two AK8 jets passing loose requirements
  if( findJetCandidatesAK4() ) foundTwoJets = true;
  if( !foundTwoJets) return false;
  nPassedFoundJets_++;
  
  //Only select jets separated by |DeltaEta| < cut
  jetsDeltaEta = fabs( AK4jetCand_.at(0).p4.Eta()  - AK4jetCand_.at(1).p4.Eta() ) ; 
  if (jetsDeltaEta <= dEtaCut_) passedDeltaEtaCut = true;	
  
  if ( ( AK4jetCand_.at(0).p4 + AK4jetCand_.at(1).p4 ).M() >= MjjCut_ ){
    // jet_deta = fabs( AK4jetCand_.at(0).p4.Eta()  - AK4jetCand_.at(1).p4.Eta());
    passedMjjCut = true;
  }
  
  if( !passedDeltaEtaCut) return false;  
  nPassedJetsDEta_++;
  
  if( !passedMjjCut) return false;   
  nPassedMjj_++; 
  
  // //Apply selection
  if ( foundTwoJets && passedDeltaEtaCut && passedMjjCut ) return true;
  else
    return false;
  
}

//==============================================================================================  

  
  
bool ExoDiBosonAnalysis::passedDijetSelections(  TString infile  ){
  bool foundTwoJets					= false;
  bool passedDeltaEtaCut		= false;
  bool passedMjjCut					= false;
  bool passedGroomedMassCut	= false;
  bool passedWTag						= false;
	
  //Make sure events contains two AK8 jets passing loose requirements
  if( findJetCandidates() ) foundTwoJets = true;
  if( !foundTwoJets) return false;
  nPassedFoundJets_++;
  
  //Only select jets separated by |DeltaEta| < cut
  jetsDeltaEta = fabs( Vcand.at(0).p4.Eta()  - Vcand.at(1).p4.Eta() ) ; 
  if (jetsDeltaEta <= dEtaCut_) passedDeltaEtaCut = true;	
  if( !passedDeltaEtaCut) return false;  
  nPassedJetsDEta_++;
  
  if( !Trigger_ && !runOnMC_ ){
    doJetTriggerEfficiency();
    if(Vcand.at(0).p4.Pt() > 600 || Vcand.at(1).p4.Pt() > 600) doJetTriggerEfficiency2();
  }
  
  //Only select jets with Mjj > cut
  if ( ( Vcand.at(0).p4 + Vcand.at(1).p4 ).M() >= MjjCut_ ) passedMjjCut = true;
  if( !passedMjjCut) return false;   
  nPassedMjj_++;
    
  Hist( "DeltaEta")	->Fill( fabs( Vcand.at(0).p4.Eta()  - Vcand.at(1).p4.Eta() ) , weight_ ); 	
  Hist( "DeltaR")	  ->Fill( (Vcand.at(0).p4).DeltaR(Vcand.at(1).p4) , weight_ ); 
  
  if(isSignal_) doGroomingStudies(infile);
  
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
    if( Vcand.at(i).prunedMass > mWLow_ && Vcand.at(i).prunedMass <= mZHigh_ ) Hist( "Tau21_afterPrunedMass" )  ->Fill( Vcand.at(i).tau2/Vcand.at(i).tau1, weight_ );
  }

    
  
  if( Vcand.at(0).prunedMass > mWLow_ || Vcand.at(1).prunedMass > mWLow_ )Hist( "Mjj_afterPrunedMass" ) -> Fill( ( Vcand.at(0).p4 + Vcand.at(1).p4 ).M() , weight_ );	
  Hist( "Mjj" ) -> Fill( ( Vcand.at(0).p4 + Vcand.at(1).p4 ).M() , weight_ );	
  Hist( "Mjj_fine" ) -> Fill( ( Vcand.at(0).p4 + Vcand.at(1).p4 ).M() , weight_ );	

  
  int jetINDXPunzi = 99;
  float MET   = (*data_.MET_et).at(0);
  float SumEt = (*data_.MET_sumEt).at(0);
  if( MET > 0. ) Hist( "METsumET" )->Fill(MET/SumEt, weight_ );
  if( MET > 0. ) Hist( "MET" )->Fill(MET, weight_ );

if( Channel_ == "VVdijet" && Vcand.at(0).prunedMass > mWLow_ && Vcand.at(0).prunedMass <= mZHigh_ && Vcand.at(1).prunedMass > mWLow_ && Vcand.at(1).prunedMass <= mZHigh_ ){
  passedGroomedMassCut = true;
  Hist( "Tau21_punzi"	)->Fill( Vcand.at(0).tau2/Vcand.at(0).tau1,weight_ );
  Hist( "Tau21_punzi"	)->Fill( Vcand.at(1).tau2/Vcand.at(1).tau1,weight_ );
  Hist( "Tau21_punzi1"	)->Fill( Vcand.at(0).tau2/Vcand.at(0).tau1,weight_ );
  Hist( "Tau21_punzi2"	)->Fill( Vcand.at(1).tau2/Vcand.at(1).tau1,weight_ );
} 

if (Channel_ == "qVdijet"){
for( int i = 0; i < abs(Vcand.size()) ; i++){
  if(!(Vcand.at(i).prunedMass > mWLow_ && Vcand.at(i).prunedMass <= mZHigh_) ) continue;
    passedGroomedMassCut = true;
    jetINDXPunzi=i;
    Hist( "Tau21_punzi"	)->Fill( Vcand.at(jetINDXPunzi).tau2/Vcand.at(jetINDXPunzi).tau1,weight_ );
  }
}

  //Cut flow
  if( !passedGroomedMassCut)	return false;
  nPassedJetPrunedMass_++;
  
  // //Apply selection
  if ( foundTwoJets && passedDeltaEtaCut && passedMjjCut && passedGroomedMassCut) return true;
  else
    return false;
	
}

//==============================================================================================
bool ExoDiBosonAnalysis::findJetCandidatesAK4( void ){
  
  TLorentzVector			TLV;
  std::vector<float>	jetPt;
  bool foundJets = false;
  float csv         = -9999;
		
  jetPt.clear();
  //Make sure jets passes loose ID, pT and eta cuts
  for( int j = 0; j < data_.njetsAK4 ; ++j ){
    if( j < 2 && (*data_.jetAK4_IDTight).at(j) != 1         )break;
    if( (*data_.jetAK4_IDTight).at(j)		!= 1				  			)continue;
    if( (*data_.jetAK4_pt).at(j)					<= JetPtCutTight_	)continue;
    if( fabs((*data_.jetAK4_eta).at(j)) 	>= JetEtaCut_ 		)continue;		
    jetPt.push_back((*data_.jetAK4_pt).at(j));
  }
	
  if( jetPt.size() > 1 ) foundJets = true;
  if( !foundJets) return false;
		
  //Find two highest pT jets in event
  if( foundJets ){
    std::sort  (jetPt.begin(),jetPt.end());
    std::reverse(jetPt.begin(),jetPt.end());
    for( int jj = 0; jj < 2; ++jj ){
      bool foundOverlap = false;
      if( (*data_.jetAK4_pt)[jj] == jetPt.at(0) ){
        TLV.SetPtEtaPhiE( (*data_.jetAK4_pt).at(jj), (*data_.jetAK4_eta).at(jj), (*data_.jetAK4_phi).at(jj), (*data_.jetAK4_e).at(jj) );
        if ( findMuonCandidate() || findElectronCandidate() ){
          for(int i = 0; i < abs(leptonCand_.size()); i++){
            if( TLV.DeltaR(leptonCand_.at(i).p4) < 0.4 ){
              foundOverlap = true;
            }
          }
        }    
        if( foundOverlap ) break;
        JetCandidate jet(TLV);                               ;
        jet.flavor				= -99                               ;
        AK4jetCand_.push_back( jet );
        
      }
      else
      if( (*data_.jetAK4_pt).at(jj) == jetPt.at(1) ){
        TLV.SetPtEtaPhiE( (*data_.jetAK4_pt).at(jj), (*data_.jetAK4_eta).at(jj), (*data_.jetAK4_phi).at(jj), (*data_.jetAK4_e).at(jj) );
        if ( findMuonCandidate() || findElectronCandidate() ){
          for(int i = 0; i < abs(leptonCand_.size()); i++){
            if( TLV.DeltaR(leptonCand_.at(i).p4) < 0.4 ){
              foundOverlap = true;
            }
          }
        }
        if( foundOverlap ) break;
        JetCandidate secondJet(TLV);
        AK4jetCand_.push_back( secondJet );
      }
      else
        continue;
    }
  }
  
  if (AK4jetCand_.size() < 2) return false;
  return foundJets;
}
//==============================================================================================
bool ExoDiBosonAnalysis::findJetCandidates( void ){
  
  TLorentzVector			TLV;
  std::vector<float>	vJetPrunedMass;
  bool foundJet = false;
  bool foundJet2 = false;
  bool foundJets = false;
  float csv         = -9999;
  
  TLorentzVector bestjet_tlv;
  TLorentzVector bestjet2_tlv;
  int    jetIndex = 999;
  int    jetIndex2 = 999;
  float  jetmass  = -9999;
  float  jetmass2 = -9999;
		
  vJetPrunedMass.clear();
  //Make sure jets passes loose ID, pT and eta cuts
  for( int j = 0; j < data_.njetsAK8 ; ++j ){
    TLV.SetPtEtaPhiE( (*data_.jetAK8_pt).at(j), (*data_.jetAK8_eta).at(j), (*data_.jetAK8_phi).at(j), (*data_.jetAK8_e).at(j) );
     
    if( Channel_.find("dijet")!= std::string::npos && j < 2 && (*data_.jetAK8_IDTight).at(j) != 1   )break;
    if( Channel_.find("dijet")!= std::string::npos && (*data_.jetAK8_IDTight).at(j)    != 1         )continue;
    if( Channel_.find("dijet")!= std::string::npos && (*data_.jetAK8_pt).at(j) <= JetPtCutTight_    )continue;
    
    if( Channel_.find("WtagSF_")!= std::string::npos && (*data_.jetAK8_IDLoose).at(j) != 1          )continue;
    if( Channel_.find("WtagSF") != std::string::npos && (*data_.jetAK8_pt).at(j) <= 80	            )continue;
    
    if( fabs((*data_.jetAK8_eta).at(j)) >= JetEtaCut_ 	                                          	)continue;	
    
    if(Channel_.find("WtagSF") != std::string::npos && leptonCand_[0].p4.DeltaR(TLV) <= 1.0         )continue;
    // vJetPrunedMass.push_back((*data_.jetAK8_prunedmass).at(j));
    
    if( (*data_.jetAK8_prunedmass)[j] > jetmass ){
      jetmass = (*data_.jetAK8_prunedmass)[j];
      bestjet_tlv.SetPtEtaPhiE( (*data_.jetAK8_pt).at(j), (*data_.jetAK8_eta).at(j), (*data_.jetAK8_phi).at(j), (*data_.jetAK8_e).at(j) );
      foundJet = true;
      jetIndex = j;
    }
  }
    
  for( int j = 0; j < data_.njetsAK8 ; ++j ){  
    if( (*data_.jetAK8_prunedmass)[j] > jetmass2 && jetIndex!=j ){
      jetmass2 = (*data_.jetAK8_prunedmass)[j];
      bestjet2_tlv.SetPtEtaPhiE( (*data_.jetAK8_pt).at(j), (*data_.jetAK8_eta).at(j), (*data_.jetAK8_phi).at(j), (*data_.jetAK8_e).at(j) );
      foundJet2 = true;
      jetIndex2 = j;
    }
  }
      
	
  if( Channel_.find("dijet")!= std::string::npos ){
    if (foundJet && foundJet2) foundJets = true;
  }  
  else
  if( Channel_.find("WtagSF")!= std::string::npos){
    if (foundJet ) foundJets = true;
  }
  
  if( !foundJets) return false;
    
  bool foundOverlap = false;
  if ( Channel_.find("dijet")!= std::string::npos && (findMuonCandidate() || findElectronCandidate()) ){
    for( int i = 0; i < abs(leptonCand_.size()); i++){
      if( bestjet_tlv.DeltaR(leptonCand_.at(i).p4) < 0.8 ) foundOverlap = true;
    }
  }
  if( Channel_.find("dijet")!= std::string::npos && foundOverlap ) return false;
        
  JetCandidate jet(bestjet_tlv);
  jet.csv					  = (*data_.jetAK8_csv).at(jetIndex)           ;
  jet.tau1					= (*data_.jetAK8_tau1).at(jetIndex)          ;
  jet.tau2					= (*data_.jetAK8_tau2).at(jetIndex)          ;
  jet.tau3					= (*data_.jetAK8_tau3).at(jetIndex)          ;
  jet.prunedMass		= (*data_.jetAK8_prunedmass).at(jetIndex)    ;
  jet.softdropMass	= (*data_.jetAK8_softdropmass).at(jetIndex)*(*data_.jetAK8_pruned_jec).at(jetIndex)	;
  jet.mass					= (*data_.jetAK8_mass).at(jetIndex)         ;
  jet.flavor				= -99                               ;
  jet.rcn					= (*data_.jetAK8_che).at(jetIndex)/(*data_.jetAK8_ne).at(jetIndex);
  jet.cm = (*data_.jetAK8_cm).at(jetIndex);
  jet.nm = (*data_.jetAK8_nm).at(jetIndex);
  jet.muf = (*data_.jetAK8_muf).at(jetIndex);
  jet.phf = (*data_.jetAK8_phf).at(jetIndex);
  jet.emf = (*data_.jetAK8_emf).at(jetIndex);
  jet.nhf = (*data_.jetAK8_nhf).at(jetIndex);
  jet.chf = (*data_.jetAK8_chf).at(jetIndex);
  jet.che = (*data_.jetAK8_che).at(jetIndex);
  jet.ne = (*data_.jetAK8_ne).at(jetIndex);  
  jet.hf_hf = (*data_.jetAK8_hf_hf).at(jetIndex);
  jet.hf_emf = (*data_.jetAK8_hf_emf).at(jetIndex);
  jet.hof = (*data_.jetAK8_hof).at(jetIndex);
  jet.chm  = (*data_.jetAK8_chm).at(jetIndex);
  jet.neHadMult = (*data_.jetAK8_neHadMult).at(jetIndex);
  jet.phoMult = (*data_.jetAK8_phoMult).at(jetIndex);
  jet.nemf = (*data_.jetAK8_nemf).at(jetIndex);
  jet.cemf = (*data_.jetAK8_cemf).at(jetIndex);
  jet.charge = (*data_.jetAK8_charge).at(jetIndex);
  jet.area = (*data_.jetAK8_area).at(jetIndex);
      
  std::vector<JetCandidate> tmp;
    
  // TLorentzVector softdropP4;
  // for( int sj = 0; sj < (*data_.subjetAK8_softdrop_N)[jetIndex]; ++sj ){
  //   TLV.SetPtEtaPhiE((*data_.subjetAK8_softdrop_pt)[jetIndex][sj],(*data_.subjetAK8_softdrop_eta)[jetIndex][sj],(*data_.subjetAK8_softdrop_phi)[jetIndex][sj],(*data_.subjetAK8_softdrop_e)[jetIndex][sj]);
  //   csv = (*data_.subjetAK8_softdrop_csv)[jetIndex][sj];
  //   JetCandidate jetC(TLV);
  //   jetC.csv = csv;
  //   jetC.flavor = 0;
  //   jetC.rho = pow( TLV.M() / ((*data_.subjetAK8_softdrop_pt)[jetIndex][sj] * 0.8),2);
  //   // if( runOnMC_ ) jetC.flavor = (*data_.subjetAK8_softdrop_flavour)[jetIndex][sj];
  //   tmp.push_back(jetC);
  //   softdropP4 += TLV;
  // }
  // SoftdropSubjetCand_.push_back(tmp);
  // tmp.clear();
  //
  // jet.rho = pow( softdropP4.M() / (softdropP4.Perp() * 0.8), 2);
  Vcand.push_back( jet );
        
  if( Channel_.find("dijet")!= std::string::npos){
    bool foundOverlap = false;
      
    if ( findMuonCandidate() || findElectronCandidate() ){
      for(int i = 0; i < abs(leptonCand_.size()); i++){
        if( bestjet2_tlv.DeltaR(leptonCand_.at(i).p4) < 0.8 ) foundOverlap = true;
      }
    }
      
    if( foundOverlap ) return false;
    JetCandidate secondJet(bestjet2_tlv);
    secondJet.csv					  = (*data_.jetAK8_csv).at(jetIndex)    ;
    secondJet.tau1          = (*data_.jetAK8_tau1).at(jetIndex2)  ;
    secondJet.tau2          = (*data_.jetAK8_tau2).at(jetIndex2)  ;
    secondJet.tau3          = (*data_.jetAK8_tau3).at(jetIndex2)  ;
    secondJet.prunedMass    = (*data_.jetAK8_prunedmass).at(jetIndex2)    ;
    secondJet.softdropMass  = (*data_.jetAK8_softdropmass).at(jetIndex2)  ;
    secondJet.mass          = (*data_.jetAK8_mass).at(jetIndex2)          ;
    secondJet.flavor        = -99                                         ;
    secondJet.rcn            = (*data_.jetAK8_che).at(jetIndex2)/(*data_.jetAK8_ne).at(jetIndex2);
    secondJet.cm = (*data_.jetAK8_cm).at(jetIndex2);
    secondJet.nm = (*data_.jetAK8_nm).at(jetIndex2);
    secondJet.muf = (*data_.jetAK8_muf).at(jetIndex2);
    secondJet.phf = (*data_.jetAK8_phf).at(jetIndex2);
    secondJet.emf = (*data_.jetAK8_emf).at(jetIndex2);
    secondJet.nhf = (*data_.jetAK8_nhf).at(jetIndex2);
    secondJet.chf = (*data_.jetAK8_chf).at(jetIndex2);
    secondJet.che = (*data_.jetAK8_che).at(jetIndex2);
    secondJet.ne = (*data_.jetAK8_ne).at(jetIndex2);  
    secondJet.hf_hf = (*data_.jetAK8_hf_hf).at(jetIndex2);
    secondJet.hf_emf = (*data_.jetAK8_hf_emf).at(jetIndex2);
    secondJet.hof = (*data_.jetAK8_hof).at(jetIndex2);
    secondJet.chm  = (*data_.jetAK8_chm).at(jetIndex2);
    secondJet.neHadMult = (*data_.jetAK8_neHadMult).at(jetIndex2);
    secondJet.phoMult = (*data_.jetAK8_phoMult).at(jetIndex2);
    secondJet.nemf = (*data_.jetAK8_nemf).at(jetIndex2);
    secondJet.cemf = (*data_.jetAK8_cemf).at(jetIndex2);
    secondJet.charge = (*data_.jetAK8_charge).at(jetIndex2);
    secondJet.area = (*data_.jetAK8_area).at(jetIndex2);

    std::vector<JetCandidate> tmp;

    // TLorentzVector softdropP4;
  //   for( int sj = 0; sj < (*data_.subjetAK8_softdrop_N)[jetIndex2]; ++sj ){
  //     TLV.SetPtEtaPhiE((*data_.subjetAK8_softdrop_pt)[jetIndex2][sj],(*data_.subjetAK8_softdrop_eta)[jetIndex2][sj],(*data_.subjetAK8_softdrop_phi)[jetIndex2][sj],(*data_.subjetAK8_softdrop_e)[jetIndex2][sj]);
  //     csv = (*data_.subjetAK8_softdrop_csv)[jetIndex2][sj];
  //     JetCandidate jetC(TLV);
  //     jetC.csv = csv;
  //     jetC.flavor = 0;
  //     jetC.rho = pow( TLV.M() / ((*data_.subjetAK8_softdrop_pt)[jetIndex2][sj] * 0.8),2);
  //     // if( runOnMC_ ) jetC.flavor = (*data_.subjetAK8_softdrop_flavour)[jetIndex2][sj];
  //     tmp.push_back(jetC);
  //     softdropP4 += TLV;
  //   }
  //   SoftdropSubjetCand_.push_back(tmp);
  //
  //   secondJet.rho = pow( softdropP4.M() / (softdropP4.Perp() * 0.8), 2);
    Vcand.push_back( secondJet );
  }
    
  if ( (Channel_.find("dijet")!= std::string::npos && Vcand.size() < 2) || ((Channel_.find("WtagSF")!= std::string::npos && Vcand.size() < 1)) ) return false;
  else
    return true;
}
//==============================================================================================
bool ExoDiBosonAnalysis::passedTTbarSelections( void ){

  bool foundLept    = false;
  bool passVeto     = false;
  bool foundMET     = false;
  bool foundW       = false;
  bool foundAK8     = false;
  bool passAK8LepDR = false;
  bool passAK8PrunedMass = false;
  bool found1b      = false;
  
  foundAMu  = 0;
  foundAEle = 0;
  
  // Find lepton (muon/electron depending on channel)
  if( findLeptonCandidate() ) foundLept = true; 
  if( !foundLept ) return false;
  nPassedFoundLept_++;
  
  Hist( "leptonPT"    )->Fill( leptonCand_.at(0).p4.Pt()	, weight_ );
  Hist( "leptonPhi"   )->Fill( leptonCand_.at(0).p4.Phi(), weight_ );
  Hist( "leptonEta"   )->Fill( leptonCand_.at(0).p4.Eta(), weight_ );
  
  
  // Veto additional loose leptons (both muons/electrons )
  if ( (foundAMu+foundAEle) > 0) return false;
  else 
    passVeto = true;
  
  nPassedVetoLep_++;
  
  // Find MET
  if( findMETCandidate() ) {
    Hist( "MET"         )->Fill(  METCand_.at(0).sumEt, weight_ );
     if( METCand_[0].p4.Pt() > METCut_ ) foundMET = true;
   }
  if( !foundMET ) return false;
  nPassedFoundMET_++;

  // reconstruct W
  if( foundLept && foundMET && findWCandidate() ){
    Hist( "Wcand_pt")->Fill(  WCand_[0].p4.Pt() );
     if( WCand_[0].p4.Pt() > 200.0 ) foundW = true;
  } 

  if( !foundW ) return false;   
  nPassedFoundW_++;
  // Find AK8 W-jet candidate
  if(findJetCandidates()){
    foundAK8 = true;
    // if( leptonCand_[0].p4.DeltaR(Vcand.at(0).p4) > 1.0 ) passAK8LepDR = true;
    if( Vcand.at(0).p4.Pt() >= JetPtCutTight_	) passAK8LepDR = true;
    if( Vcand.at(0).prunedMass >= mWLow_ && Vcand.at(0).prunedMass <= mZHigh_ ) passAK8PrunedMass = true;
  }
  
  if( !foundAK8 ) return false;
  nPassedFoundJet_++;
 
  if( !passAK8LepDR ) return false;   
  nPassedLepJetDR_++;
  
  if( !passAK8PrunedMass ) return false;   
  nPassedJetPrunedMass_++;
  
  // Find b-tagged AK4 jet
  findAK4Jets();
  
  bool najetCut = false; 
  int najet = 0;
  for( unsigned int j = 0; j < abs(AK4jetCand_.size()); j++ ){
     if( AK4jetCand_[j].csv > 0.890 ) najet++;
  }
  
  if( najet  > 0 ) found1b = true;
  
  if( !found1b ) return false;   
  nPassed1bTag_++;
  
  if(foundLept && passVeto && foundMET && foundW && foundAK8 && passAK8LepDR && passAK8PrunedMass && found1b) return true;
	
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


   foundAEle = 0;
   foundAMu = 0;
   
   TLorentzVector TLV;
   bool foundLept = false;
   double ptMu = -999;
   int muIndex = 999;
   double scale = 0.;
   double newpt = 0.;
   double scale_ = 0.;
   for( int l = 0; l < data_.mu_N; ++l ){
     if( !isLowMass && (*data_.mu_isHighPtMuon)[l] != 1 ) continue;
     if(  isLowMass && (*data_.mu_isTightMuon)[l] != 1 ) continue;
      //if( (*data_.mu_isPFMuon)[l] != 1 ) continue;
      scale = getMuonScale((*data_.mu_pt)[l]);
      newpt = (*data_.mu_pt)[l]+scale;
      if( (*data_.mu_trackIso)[l]/newpt >= 0.1 ) continue;
      if( newpt <= leptPtCut_ ) continue;
      if( fabs((*data_.mu_eta)[l]) >= leptEtaCut_ ) continue;
      foundLept = true;
      if( newpt > ptMu ){  
         ptMu = newpt;
         TLV.SetPtEtaPhiE( newpt, (*data_.mu_eta)[l], (*data_.mu_phi)[l], (*data_.mu_e)[l]+scale );  
	 muIndex = l;
	 scale_ = scale;
      }      
   }
   
   if( foundLept ){
     LeptonCandidate muCand(TLV);
     muCand.iso = (*data_.mu_trackIso)[muIndex]/ptMu;
     // muCand.scale = scale_;
 //     muCand.isGlobalMuon = (*data_.mu_isGlobalMuon)[muIndex];
 //     muCand.globalHits = (*data_.mu_globalHits)[muIndex];
 //     muCand.matchedStations = (*data_.mu_matchedStations)[muIndex];
 //     muCand.bestTrack_ptErrRel = (*data_.mu_bestTrack_ptErr)[muIndex]/(*data_.mu_bestTrack_pt)[muIndex];
 //     muCand.d0 = (*data_.mu_d0)[muIndex];
 //     //muCand.dz = (*data_.mu_dz)[muIndex];
 //     muCand.pixelHits = (*data_.mu_pixelHits)[muIndex];
 //     muCand.trackerHits = (*data_.mu_trackerHits)[muIndex];
     leptonCand_.push_back( muCand );
   }
   
   scale = 0.;
   for( int l = 0; l < data_.mu_N; ++l ){
      if( muIndex == 999 || l == muIndex ) continue;
      if( !isLowMass && (*data_.mu_isHighPtMuon)[l] != 1 ) continue;
      if(  isLowMass && (*data_.mu_isLooseMuon)[l] != 1 ) continue;
      scale = getMuonScale((*data_.mu_pt)[l]);
      newpt = (*data_.mu_pt)[l]+scale;
      if( (*data_.mu_trackIso)[l]/newpt >= 0.1 ) continue;
      if( newpt <= AleptPtCut_ ) continue;
      if( fabs((*data_.mu_eta)[l]) >= AleptEtaCut_ ) continue;
      foundAMu++;
   }
   
   for( int l = 0; l < data_.el_N; ++l ){
      if( !isLowMass && (*data_.el_isHEEP)[l] != 1 ) continue;
      if( isLowMass && (*data_.el_isVetoElectron)[l] != 1 ) continue;
      if( (*data_.el_pt)[l] <= 35. ) continue;
      //if( fabs((*data_.el_eta)[l]) >= 1.4442 && fabs((*data_.el_eta)[l]) <= 1.566 ) continue;
      //if( fabs((*data_.el_eta)[l]) >= 2.5 ) continue;
      foundAEle++;
   }
   
   return foundLept;

   //if( (foundAMu+foundAEle)<1 && foundLept ) return true;
   //else return false;
   
}
//==============================================================================================
double ExoDiBosonAnalysis::getMuonScale( double oldpt ){
  int ScaleMuonUpDown_ = 0;

   double scale = 0.;
   
   if( oldpt < 200. ) scale = (ScaleMuonUpDown_)*0.2*oldpt/100.;
   else if( oldpt >= 200. ) scale = (ScaleMuonUpDown_)*5.*oldpt/100.;	
   
   return scale;
      
}
//==============================================================================================
bool ExoDiBosonAnalysis::findElectronCandidate( void ){

   foundAMu = 0;
   foundAEle = 0;

   TLorentzVector TLV;
   bool foundEle = false;
   double ptEle = -999;
   int eleIndex = 999;
   for( int l = 0; l < data_.el_N; ++l ){
      if( (*data_.el_pt)[l] <= 35. ) continue;     
      //if( fabs((*data_.el_eta)[l]) >= 1.4442 && fabs((*data_.el_eta)[l]) <= 1.566 ) continue; 
      //if( fabs((*data_.el_eta)[l]) >= leptEtaCut_ ) continue; 
      if( !isLowMass && (*data_.el_isHEEP)[l] != 1 ) continue;
      if(  isLowMass && (*data_.el_isTightElectron)[l] != 1 ) continue;
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
   
   for( int l = 0; l < data_.el_N; ++l ){
      if( eleIndex == 999 || l == eleIndex ) continue;
      if( !isLowMass && (*data_.el_isHEEP)[l] != 1 ) continue;
      if(  isLowMass && (*data_.el_isTightElectron)[l] != 1 ) continue;
      if( (*data_.el_pt)[l] <= AleptPtCut_ ) continue;
      //if( fabs((*data_.el_eta)[l]) >= 1.4442 && fabs((*data_.el_eta)[l]) <= 1.566 ) continue;
      //if( fabs((*data_.el_eta)[l]) >= AleptEtaCut_ ) continue;
      foundAEle++;
   }   
   for( int l = 0; l < data_.mu_N; ++l ){
     if( !isLowMass && (*data_.mu_isHighPtMuon)[l] != 1 ) continue;
     if(  isLowMass && (*data_.mu_isLooseMuon)[l] != 1 ) continue;
      if( (*data_.mu_trackIso)[l]/(*data_.mu_pt)[l] >= 0.1 ) continue;
      if( (*data_.mu_pt)[l] <= 20. ) continue;
      if( fabs((*data_.mu_eta)[l]) >= 2.4 ) continue;
      foundAMu++;
   }
   
   return foundEle;
      
}

//==============================================================================================
void ExoDiBosonAnalysis::findAK4Jets( void ){
  TLorentzVector jet;
  for( int j = 0; j < data_.njetsAK4; ++j ){ 
     jet.SetPtEtaPhiE( (*data_.jetAK4_pt)[j], (*data_.jetAK4_eta)[j], (*data_.jetAK4_phi)[j], (*data_.jetAK4_e)[j] );
     if( jet.DeltaR(Vcand[0].p4) < 0.8 ) continue;
     if( (*data_.jetAK4_IDLoose)[j] != 1 ) continue;
     if( (*data_.jetAK4_pt)[j] <= JetPtCutLoose_ ) continue;
     if( fabs((*data_.jetAK4_eta)[j]) >= JetEtaCut_ ) continue;
     if( jet.DeltaR(leptonCand_[0].p4) < 0.3 ) continue;
     JetCandidate Ajet(jet);
     Ajet.csv = (*data_.jetAK4_csv)[j];
     Ajet.flavor = 0;
     if( runOnMC_ ) Ajet.flavor = abs((*data_.jetAK4_flavor)[j]);
     AK4jetCand_.push_back(Ajet);
  }
}

//==============================================================================================
bool ExoDiBosonAnalysis::findMETCandidate( void ){
  
  TLorentzVector TLV;
  bool foundMET = false;
  if( (*data_.MET_et)[0] > 0. ){
  
     TLV.SetPtEtaPhiE( (*data_.MET_et)[0], 0., (*data_.MET_phi)[0], 0. );
                
     METCandidate metC(TLV);
     metC.sumEt = (*data_.MET_sumEt)[0];
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
void ExoDiBosonAnalysis::findExoCandidate( void ){

   TLorentzVector p4nu = getp4Nu();      
   MWW = (p4nu + leptonCand_[0].p4 + Vcand[0].p4).M();
   WMass = (p4nu + leptonCand_[0].p4).M();
   
   // TLorentzVector p4nu2 = getp4NuMethod2();
//    //Hist( "pzNu" )->Fill(p4nu2.Pz());
//
//    //Hist( "NuLeptInvMass"  )->Fill( (p4nu2 + leptonCand_[0].p4).M() );
//    MWWmethod2 = (p4nu2 + leptonCand_[0].p4 + fatJetCand_[0].p4).M();
//    WMassMethod2 = (p4nu2 + leptonCand_[0].p4).M();

   return;
            
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
    if ( Vcand.size() < 2 ) return;
    Hist( "VVdeltaEta"        )-> Fill( fabs( Vcand.at(0).p4.Eta()  - Vcand.at(1).p4.Eta() ) , weight_ ); 
    Hist( "DiBosonInvMass"    )->Fill( (Vcand.at(0).p4 + Vcand.at(1).p4).M(), weight_ );
    
    for(int i = 0; i < abs(Vcand.size());i++){
      if( Channel_ == "qVdijet" && i != jetINDX) continue;
      Hist( "VcandTau21"        )->Fill( Vcand.at(i).tau2/Vcand.at(i).tau1,weight_ );
      Hist( "VcandPrunedMass"   )->Fill( Vcand.at(i).prunedMass, weight_ );
      Hist( "VcandSoftdropMass" )->Fill( Vcand.at(i).softdropMass, weight_ );
      Hist( "VcandPt"           )->Fill( Vcand.at(i).p4.Pt() , weight_ );
      Hist( "VcandEta"          )->Fill( Vcand.at(i).p4.Eta(), weight_ );
      Hist( "VcandPhi"          )->Fill( Vcand.at(i).p4.Phi(), weight_ );
      Hist( "VcandMass"         )->Fill( Vcand.at(i).mass , weight_ );
    }
    

    // if ( Vcand.size() >= 2 ) {
    //       unsigned int tag = gRandom->Integer(1);
    //       unsigned int probe = 1;
    //       if ( tag == 1 ) probe = 0;
    //
    //       bool tagged = Vcand.at(tag).tau2/Vcand.at(tag).tau1 < 0.6 && Vcand.at(tag).softdropMass > 65. && Vcand.at(tag).softdropMass < 105.;
    //       hvv_pred->Accumulate( (Vcand.at(0).p4 + Vcand.at(1).p4).M(), Vcand.at(probe).rho, tagged, weight_);
    //       // std::cout<<"Using SoftdropSubjetCand_[probe][0] with rho == "<<SoftdropSubjetCand_[probe][0].rho<<std::endl;
    //       // hvv_pred->Accumulate( (SoftdropSubjetCand_[probe][0].p4 + SoftdropSubjetCand_[probe][1].p4).M(),SoftdropSubjetCand_[probe][0].rho, tagged, weight_);
    //     }

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
    Hist( "sumGenWeight" )->SetBinContent(1,nSumGenWeights_);
    Hist( "nEvents"               )->SetBinContent(1,nEvents_*weight_               );
    Hist( "nPassedFilter"        )->SetBinContent(1,nPassedFilters_*weight_        );
    Hist( "nPassedTrigger"        )->SetBinContent(1,nPassedTrigger_*weight_        );
    Hist( "nPassedFoundJets"      )->SetBinContent(1,nPassedFoundJets_*weight_      );
    Hist( "nPassedJetsDEta"       )->SetBinContent(1,nPassedJetsDEta_*weight_       );
    Hist( "nPassedMjj"            )->SetBinContent(1,nPassedMjj_*weight_            );
    Hist( "nPassedTau21Cut"       )->SetBinContent(1,nPassedTau21Cut_*weight_       );
    Hist( "nPassedPrunedJetMass"  )->SetBinContent(1,nPassedJetPrunedMass_*weight_  );
  }
  else if ( Channel_.find("WtagSF") != std::string::npos ){

    printCutFlow();
    theHistosManager_->formatHistos(Channel_);
    
    Hist( "sumGenWeight" )->SetBinContent(1,nSumGenWeights_);
    Hist( "nEvents" )->SetBinContent(1,nEvents_*weight_        );
    Hist( "nPassedFilter" )->SetBinContent(1,nPassedFilters_*weight_      );
    Hist( "nPassedTrigger"  )->SetBinContent(1,nPassedTrigger_*weight_    );
    Hist( "nPassedFoundLept")->SetBinContent(1,nPassedFoundLept_*weight_  );
    Hist( "nPassedVetoLep"  )->SetBinContent(1,nPassedVetoLep_*weight_    );
    Hist( "nPassedFoundMET" )->SetBinContent(1,nPassedFoundMET_*weight_   );
    Hist( "nPassedFoundW"   )->SetBinContent(1,nPassedFoundW_*weight_    );
    Hist( "nPassedFoundJet" )->SetBinContent(1,nPassedFoundJet_*weight_  );
    Hist( "nPassedLepJetDR" )->SetBinContent(1,nPassedLepJetDR_*weight_  );
    Hist( "nPassedPrunedJetMass"  )->SetBinContent(1,nPassedJetPrunedMass_*weight_  );
    Hist( "nPassed1bTag"    )->SetBinContent(1,nPassed1bTag_*weight_     );

  }
  // hvv_pred->SetCalculatedErrors();
  
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
    std::cout << "number of events                                " << nEvents_ << std::endl;
    std::cout << "passed filter                                   " << nPassedFilters_    << " --- eff = " << (double)nPassedFilters_/nEvents_ << std::endl; 
    std::cout << "passed trigger                                  " << nPassedTrigger_    << " --- eff = " << (double)nPassedTrigger_/nEvents_ << std::endl; 
    std::cout << "found at least 2 jets with pT > 200/ eta < 2.4  " << nPassedFoundJets_  << " --- eff = " << (double)nPassedFoundJets_/nEvents_ << std::endl;
    
    std::cout << "Passed dEta(j,j) < 1.3                          " << nPassedJetsDEta_   << " --- eff = " << (double)nPassedJetsDEta_/nEvents_ << std::endl;
    std::cout << "Passed M(j,j) cut                               " << nPassedMjj_        << " --- eff = " << (double)nPassedMjj_/nEvents_ << std::endl;
    std::cout << "Passed jet pruned mass cut                      " << nPassedJetPrunedMass_ << " --- eff = " << (double)nPassedJetPrunedMass_/nEvents_ << std::endl;
    // std::cout << "Passed tau 21 cut                               " << nPassedTau21Cut_ << " --- eff = " << (double)nPassedTau21Cut_/nEvents_ << std::endl;
  //   std::cout << "Passed jet pruned mass cut NOMINAL (after dEta and Mjj)" << nPassedJetPrunedMass_ << " --- eff = " << (double)nPassedJetPrunedMass_/(double)nPassedJetsDEta_ << std::endl;
  //   std::cout << "Passed tau 21 cut(after dEta and Mjj)                   " << nPassedTau21Cut_ << " --- eff = " << (double)nPassedTau21Cut_/(double)nPassedJetsDEta_ << std::endl;
  //   std::cout << "Passed jet pruned mass cut NOMINAL (after Mjj)" << nPassedJetPrunedMass_ << " --- eff = " << (double)nPassedJetPrunedMass_/(double)nPassedMjj_ << std::endl;
  //   std::cout << "Passed tau 21 cut(after  Mjj)                   " << nPassedTau21Cut_ << " --- eff = " << (double)nPassedTau21Cut_/(double)nPassedMjj_ << std::endl;
  }
  
  else if (Channel_.find("WtagSF") != std::string::npos){
    
    std::cout << "number of events		                            " << nEvents_ << std::endl;
    
    std::cout << "passed trigger        " << nPassedTrigger_        << " --- eff = " << (double)nPassedTrigger_/nEvents_ << std::endl; 
    std::cout << "passed filter HBHE    " << nPassedFilter_HBHE_    << " --- eff = " << (double)nPassedFilter_HBHE_/nEvents_ << std::endl; 
    std::cout << "passed filter CSCHalo " << nPassedFilter_CSCHalo_ << " --- eff = " << (double)nPassedFilter_CSCHalo_/nEvents_ << std::endl;  
    std::cout << "passed filter EEBadSc " << nPassedFilter_EEBadSc_ << " --- eff = " << (double)nPassedFilter_EEBadSc_/nEvents_ << std::endl; 
    std::cout << "passed filter GoodPV  " << nPassedGoodPVFilter_   << " --- eff = " << (double)nPassedGoodPVFilter_/nEvents_ << std::endl; 
    std::cout << "passed filter         " << nPassedFilters_        << " --- eff = " << (double)nPassedFilters_/nEvents_ << std::endl; 
    
    std::cout << "Passed found lep      " << nPassedFoundLept_      << " --- eff (relative, after pass filter)  = " << (double)nPassedFoundLept_/nEvents_     << " (" <<(double)nPassedFoundLept_/nPassedFilters_     <<") "<< std::endl;
    std::cout << "Passed VETO lep       " << nPassedVetoLep_        << " --- eff (relative, after pass filter)  = " << (double)nPassedVetoLep_/nEvents_       << " (" <<(double)nPassedVetoLep_/nPassedFilters_       <<") "<< std::endl;
    std::cout << "Passed found MET      " << nPassedFoundMET_       << " --- eff (relative, after pass filter)  = " << (double)nPassedFoundMET_/nEvents_      << " (" <<(double)nPassedFoundMET_/nPassedFilters_      <<") "<< std::endl;
    std::cout << "Passed found W        " << nPassedFoundW_         << " --- eff (relative, after pass filter)  = " << (double)nPassedFoundW_/nEvents_        << " (" <<(double)nPassedFoundW_/nPassedFilters_        <<") "<< std::endl;
    std::cout << "Passed found AK8      " << nPassedFoundJet_       << " --- eff (relative, after pass filter)  = " << (double)nPassedFoundJet_/nEvents_      << " (" <<(double)nPassedFoundJet_/nPassedFilters_      <<") "<< std::endl;
    std::cout << "Passed tight pT cut   " << nPassedLepJetDR_       << " --- eff (relative, after pass filter)  = " << (double)nPassedLepJetDR_/nEvents_      << " (" <<(double)nPassedLepJetDR_/nPassedFilters_      <<") "<< std::endl;
    std::cout << "Passed pruned M cut   " << nPassedJetPrunedMass_  << " --- eff (relative, after pass filter)  = " << (double)nPassedJetPrunedMass_/nEvents_ << " (" <<(double)nPassedJetPrunedMass_/nPassedFilters_ <<") "<< std::endl;
    std::cout << "Passed found b-tag    " << nPassed1bTag_          << " --- eff (relative, after pass filter)  = " << (double)nPassed1bTag_/nEvents_         << " (" <<(double)nPassed1bTag_/nPassedFilters_         <<") "<< std::endl;

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
      if( (Vcand.at(0).prunedMass > mWLow_ && Vcand.at(0).prunedMass <= mZHigh_) || 
          (Vcand.at(1).prunedMass > mWLow_ && Vcand.at(1).prunedMass <= mZHigh_ )){
        Hist( "PFHT650" )->Fill( Mjj);

        //Pass single tag
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
      if( (Vcand.at(0).prunedMass > mWLow_ && Vcand.at(0).prunedMass <= mZHigh_) && 
          (Vcand.at(1).prunedMass > mWLow_ && Vcand.at(1).prunedMass <= mZHigh_ )){
        Hist( "PFHT650" )->Fill( Mjj);

        //Pass double tag
        bool passedHT = false;
        bool passedSubstructure = false;
        bool passedALL = false;
        
        for( std::map<std::string,bool>::iterator it2 = (data_.HLT_isFired)->begin(); it2 != (data_.HLT_isFired)->end(); it2++){
          std::string iter = it2->first;
          bool value = it2->second;

          if( (iter).find("PFHT800")                        != std::string::npos && value ) Hist( "HT800_VV" )->Fill( Mjj);
          if( (iter).find("PFHT650_WideJetMJJ950DEtaJJ1p5") != std::string::npos && value ) Hist( "HT650_MJJ950_VV" )->Fill( Mjj);
          if( (iter).find("PFHT650_WideJetMJJ900DEtaJJ1p5") != std::string::npos && value ) Hist( "HT650_MJJ900_VV" )->Fill( Mjj);
          if( ((iter).find("PFHT800")                       != std::string::npos && value)
            ||((iter).find("PFHT650_WideJetMJJ900DEtaJJ1p5")!= std::string::npos && value)
              ||((iter).find("PFHT650_WideJetMJJ950DEtaJJ1p5")!= std::string::npos && value)) passedHT = true;
          
          if( ((iter).find("PFHT800")                       != std::string::npos && value)
            ||((iter).find("PFHT650_WideJetMJJ900DEtaJJ1p5")!= std::string::npos && value)
              ||((iter).find("PFHT650_WideJetMJJ950DEtaJJ1p5")!= std::string::npos && value)
                ||((iter).find("AK8PFJet360_TrimMass30")        != std::string::npos && value)
                  ||((iter).find("AK8PFHT700_TrimR0p1PT0p03Mass50")!= std::string::npos && value)) passedALL = true;


          //SUBSTRUCTURE TRIGGERS
          if( (iter).find("AK8PFJet360_TrimMass30")                    != std::string::npos && value ) Hist( "PFJet360_Trim_VV" ) ->Fill( Mjj);
          if( (iter).find("AK8PFHT700_TrimR0p1PT0p03Mass50")           != std::string::npos && value ) Hist( "HT700_Trim_VV" )    ->Fill( Mjj);
          if( (iter).find("AK8DiPFJet280_200_TrimMass30_BTagCSV0p45")  != std::string::npos && value ) Hist( "DiPFJet280_200_TrimMass30_VV" )->Fill( Mjj);
          if( ((iter).find("AK8PFJet360_TrimMass30")                   != std::string::npos && value)
            || ((iter).find("AK8PFHT700_TrimR0p1PT0p03Mass50")         != std::string::npos && value) ) passedSubstructure = true;
          // || ((iter).find("AK8DiPFJet280_200_TrimMass30_BTagCSV0p45")!= std::string::npos && value)) passedSubstructure = true;
        }
        
        if( passedHT )          Hist( "HT_VV" )->Fill( Mjj);
        if( passedSubstructure )Hist( "Substructure_VV" )->Fill( Mjj);
        if( passedALL )         Hist( "ALL_VV" )->Fill( Mjj);
        
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

      for(int i=0; i < abs(AdditionalJ.size()); i++ ){
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
          
  for(int i=0; i < abs(AK4jetCand_.size()); i++ ){
    if( (AK4bjetCand_.at(0).p4.Pt() == AK4jetCand_.at(i).p4.Pt()) || (AK4bjetCand_.at(1).p4.Pt() == AK4jetCand_.at(i).p4.Pt()))continue;
    for(int j=0; j < abs(AK4jetCand_.size()); j++ ){
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

////////////////////////////////////////////////////// GEN STUDIES ////////////////////////////////////////////////////////////////////////////
void ExoDiBosonAnalysis::doGroomingStudies(  TString sample  ){
  
  std::vector< std::map<int,TLorentzVector>::iterator	>	W	;
  std::vector< std::map<int,TLorentzVector>::iterator	>	Z	;
  std::vector< std::map<int,TLorentzVector>::iterator	>	H	;

  std::map<int,TLorentzVector>::iterator itW_p =  genCandidates_.find(24);
  W.push_back(itW_p);
  std::map<int,TLorentzVector>::iterator itW_m = genCandidates_.find(-24);
  W.push_back(itW_m);
  
  std::map<int,TLorentzVector>::iterator itZ_p =  genCandidates_.find(23);
  Z.push_back(itZ_p);
  std::map<int,TLorentzVector>::iterator itZ_m = genCandidates_.find(-23);
  Z.push_back(itZ_m);
    
  std::map<int,TLorentzVector>::iterator itH = genCandidates_.find(25)!=genCandidates_.end() ? genCandidates_.find(25) : genCandidates_.find(-25);

  std::map<int,TLorentzVector>::iterator itE = genCandidates_.find(11)!=genCandidates_.end() ? genCandidates_.find(11) : genCandidates_.find(-11);
  std::map<int,TLorentzVector>::iterator itM = genCandidates_.find(13)!=genCandidates_.end() ? genCandidates_.find(13) : genCandidates_.find(-13);
  std::map<int,TLorentzVector>::iterator itT = genCandidates_.find(15)!=genCandidates_.end() ? genCandidates_.find(15) : genCandidates_.find(-15);
  
  for( int i = 0; i < abs(Vcand.size()) ; i++){
    if( ((Vcand.at(i).p4).DeltaR(itE->second)) < 0.4 || ((Vcand.at(i).p4).DeltaR(itM->second)) < 0.4 || ((Vcand.at(i).p4).DeltaR(itT->second)) < 0.4) continue;
    for( int it = 0; it < abs(W.size()) ; it++){
      if( (Vcand.at(i).p4).DeltaR(W.at(it)->second) < 0.4 ){
        
        if(i==0)jet_mass_pruned_W1 = (Vcand.at(i)).prunedMass;
        if(i==1)jet_mass_pruned_W2 = (Vcand.at(i)).prunedMass;
        
        Hist( "recoWTau21" )->Fill( Vcand.at(i).tau2/Vcand.at(i).tau1,weight_ );
        Hist( "recoWPrunedMass" )->Fill( (Vcand.at(i)).prunedMass );
      }
    }
      for( int it = 0; it < abs(Z.size()) ; it++){
        if( (Vcand.at(i).p4).DeltaR(Z.at(it)->second) < 0.4 ){

          if(i==0)jet_mass_pruned_Z1 = (Vcand.at(i)).prunedMass;
          if(i==1)jet_mass_pruned_Z2 = (Vcand.at(i)).prunedMass;
          
          Hist( "recoZTau21" )->Fill( Vcand.at(i).tau2/Vcand.at(i).tau1,weight_ );
          Hist( "recoZPrunedMass" )->Fill( (Vcand.at(i)).prunedMass );
        }
      }
    }
  }
  
////////////////////////////////////////////////////// RHO RATIO (Sal) ////////////////////////////////////////////////////////////////////////////
// void ExoDiBosonAnalysis::setPredictedDistribution()
// {
//   fMistag_ = TFile::Open( "data/mistagRate_mod_wjetsmc.root" );
//   hMistag_ = (TH1D*)fMistag_->Get("rLoMod");
//
//   hvv_pred = new PredictedDistribution (hMistag_, "hvv_pred", "Predicted VV Mass", 100, 0, 5000);
//   hvv_pred->GetTaggableHist()->SetDirectory(0);
//   hvv_pred->GetObservedHist()->SetDirectory(0);
//   hvv_pred->GetPredictedHist()->SetDirectory(0);
//
// }
