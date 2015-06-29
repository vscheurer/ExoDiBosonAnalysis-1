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
  DeclareProperty( "dEtaCut"					, dEtaCut_					);
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
	
  // pdgMtop = 173.34;
  // pdgMw    = 80.385;
  //   pdgWidthtop = 1.29;
  //   pdgWidthw    = 2.085;
  
  pdgMtop = 172.7;
  pdgMw		= 81.0;   
  pdgWidthtop = 7.5;
  pdgWidthw    = 7.2;

  jetIndex_                 = 0;
   
  nEvents_                  = 0;
  nPassedTrigger_           = 0;	      
  nPassedJetPrunedMass_     = 0;
  nPassedTau21Cut_          = 0;  
  nPassedExoCandidateMass_  = 0;
  nPassedWTag_              = 0;
   
  Mjj                       = 0;
  jetsDeltaEta              = 0;
  nBTags                    = 0;
   
  nPassedFoundJets_				= 0;
  nPassedJetsDEta_				= 0;
  nPassedMjj_             = 0;
  nPassedWtagging_				= 0;
  nPassedFoundLept_				= 0;
	
  nPassedIsoLep_        = 0;
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
    DeclareVariable( jet_mass_pruned, "jet_mass_pruned"	, OutputTreeName_.c_str() );
    DeclareVariable( jet_mass_softdrop	, "jet_mass_softdrop", OutputTreeName_.c_str() );
    DeclareVariable( jet_tau2tau1   , "jet_tau2tau1"		, OutputTreeName_.c_str() );
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
  genJetCand      .clear();
	
  Leptonicb_			.clear();
  Hadronicb_			.clear();
  HadronicJ_			.clear();
   
}

//==============================================================================================
void ExoDiBosonAnalysis::setGenCandidates( void ) {

  if( !runOnMC_ ) return;
  // if( !isSignal_ && !genFilter_ ) return;

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
      
  //hltweight_ = HLTWeight_.getHLTWeight( leptonCand_.at(0).p4.Pt(), leptonCand_.at(0).p4.Eta() );
   
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
	
  // Connect branches in tree
  initData();

  // Reset vectors
  reset();
	
  ////////////////////////////////////////////////////////////////////////////////////////////////////////
  //// Dijet analysis begins HERE/////////////////////////////////////////////////////////////////////////
  if( Channel_ == "VVdijet" || Channel_ == "qVdijet" ){

    // if( isSignal_ ){
  //     setGenCandidates();
  //     TLorentzVector genTLV;
  //     for( int jj = 0; jj < (data_.genJetAK8_pt)->size(); ++jj ){
  //       genTLV.SetPtEtaPhiE( (*data_.genJetAK8_pt)[jj], (*data_.genJetAK8_eta)[jj], (*data_.genJetAK8_phi)[jj], (*data_.genJetAK8_e)[jj] );
  //       JetCandidate genJet(genTLV);
  //       genJet.mass= (*data_.genJetAK8_mass)[jj];
  //       genJetCand.push_back( genJet );
  //   }
  // }

    nEvents_++;
    if( !passedTrigger() ) throw SError( SError::SkipEvent );
    nPassedTrigger_++;

    //Set weights xSec/genEvents
    TString infile = TString(this->GetHistInputFile()->GetName());
    setWeight(infile);




    // //Check QCD HT sample overlap regions
    // float ptJet  = -9999  ;
    // float HT    = 0.    ;
    //
    // for( int j = 0; j < data_.njetsAK4; ++j ){
    //   HT += (*data_.jetAK4_pt)[j];
    //   if( (*data_.jetAK4_pt)[j] > ptJet )  ptJet = (*data_.jetAK4_pt)[j];
    // }
    // Hist( "AK4jetHT")->Fill( HT, weight_ );
    // Hist( "AK4jetPt")->Fill( ptJet, weight_ );
    // Hist( "AK4jetHT_HTweight")->Fill( HT, HT );
    // Hist( "AK4jetPt_PTweight")->Fill( ptJet, ptJet);

    //Get diboson invariant mass
    if( passedDijetSelections() ){

      //Fill all histograms after full selection
      fillHistos();
      // MVV = (Vcand.at(0).p4 + Vcand.at(1).p4).M()  ;
      // Mj1 = Vcand.at(0).prunedMass          ;
      // Mj2 = Vcand.at(1).prunedMass          ;
    }
  }
  ////////////////////////////////////////////////////////////////////////////////////////////////////////
  //// SF measurements begins HERE/////////////////////////////////////////////////////////////////////////	
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
      findMETCandidate();
      findWCandidate();
      TLorentzVector p4nu					= getp4Nu();		
      TLorentzVector p4nuMethod2	= getp4NuMethod2();	

      Double_t deltaTmassMin = 999.;
      float chi2Min = 999999.;
      float Tmass = 0;
      float Wmass = 0;

      //Reconstruct hadronic top
      for(int i=0; i < 4; i++ ){
        Hadronicb_.push_back(AK4jetCand_[i]);
        for(int j=0; j < 4; j++ ){
          for(int k=0; k < 4; k++ ){
            Hadronicb_.push_back(AK4jetCand_[k]);
            if( i==j || i==k || j==k) continue;
            float deltaTmass = ((AK4jetCand_[i].p4 + AK4jetCand_[j].p4 + AK4jetCand_[k].p4).M())-pdgMtop;
            float deltaWmass = ((AK4jetCand_[i].p4 + AK4jetCand_[j].p4).M())-pdgMw;
           
            float chi2 = pow((deltaTmass/pdgWidthtop),2)+pow((deltaWmass/pdgWidthw),2);
            
            if(chi2 < chi2Min ){
              chi2Min = chi2;
              Tmass = (AK4jetCand_[i].p4 + AK4jetCand_[j].p4 + AK4jetCand_[k].p4).M();
              Wmass = (AK4jetCand_[i].p4 + AK4jetCand_[j].p4).M();
              Hadronicb_.at(0)=AK4jetCand_[i];
              Hadronicb_.at(1)=AK4jetCand_[j];
              Hadronicb_[2]=AK4jetCand_[k];
            }
          }
        }
      }
      if(abs(Hadronicb_[2].flavor) == 5){
        Hist( "tmass"			      	)->Fill ( Tmass);
        Hist( "wmass"			      	)->Fill ( Wmass);
        Hist( "Chi2"			      	)->Fill ( chi2Min);
        Hist( "Chi2vsMass"				)->Fill ( chi2Min,Tmass);
      }
            
      if( chi2Min > 90. ) throw SError( SError::SkipEvent );
			
      //Reconstruct leptonic top			
      for(int i=0; i < 4; i++ ){
        if (AK4jetCand_[i].p4.Pt() == Hadronicb_.at(0).p4.Pt() || AK4jetCand_[i].p4.Pt() == Hadronicb_.at(1).p4.Pt()  || AK4jetCand_[i].p4.Pt() == Hadronicb_[2].p4.Pt()) continue;
        Leptonicb_.push_back(AK4jetCand_[i]);
        // Double_t deltaR = AK4jetCand_[i].p4.DeltaR(leptonCand_.at(0).p4);
        Double_t deltaTmass = fabs(pdgMtop - ((p4nu + leptonCand_.at(0).p4 + AK4jetCand_[i].p4).M()));
        if(deltaTmass < deltaTmassMin ){
          // deltaRmin = deltaR;
          deltaTmassMin = deltaTmass;
          Leptonicb_.at(0)=AK4bjetCand_[i];
        }
      }
			
      Double_t TmassHad		= (Hadronicb_.at(0).p4 + Hadronicb_.at(1).p4 + Hadronicb_[2].p4).M();
      Double_t WmassHad		= (Hadronicb_.at(0).p4 + Hadronicb_.at(1).p4).M();
			
      Double_t TmassLep		= (p4nu + leptonCand_.at(0).p4 + Leptonicb_.at(0).p4).M();
      Double_t WmassLep		= TMath::Sqrt( 2*METCand_.at(0).p4.Pt()*leptonCand_.at(0).p4.Pt()*(1-cos(leptonCand_.at(0).p4.DeltaPhi(METCand_.at(0).p4))));
      // Double_t TmassLep2  = (p4nuMethod2 + leptonCand_.at(0).p4 + Leptonicb_.at(0).p4).M()  ;
      // 		Double_t TmassHad		= (Hadronicb_.at(0).p4 + HadronicJ_.at(0).p4 + HadronicJ_.at(1).p4).M();
      // 		Double_t WmassHad		= WCand_.at(1).p4.M();
      //
      if( !(fabs(pdgMtop - TmassLep) < 0.20*pdgMtop && abs(pdgMtop - TmassHad) < 0.20*pdgMtop) ) throw SError( SError::SkipEvent );
      //
      Hist( "LeptonicbCSV"				)->Fill ( Leptonicb_.at(0).csv, weight_    );
      Hist( "LeptonicbFlavor"			)->Fill ( Leptonicb_.at(0).flavor, weight_	);
      Hist( "HadronicbCSV"        )->Fill ( Hadronicb_[2].csv, weight_    );
      Hist( "HadronicbFlavor"     )->Fill ( Hadronicb_[2].flavor, weight_	);
      Hist( "HadronicTopMass"			)->Fill ( TmassHad, weight_	);
      Hist( "HadronicWMass"				)->Fill ( WmassHad , weight_	);
      Hist( "LeptonicWMass"				)->Fill ( WmassLep , weight_	);
      Hist( "LeptonicTopMass"			)->Fill ( TmassLep, weight_	);

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
  for( int i = 0; i < 2; i++){
    Hist( "Pt" ) -> Fill( ( Vcand.at(i).p4 ).Pt() , weight_ );
    Hist( "Eta" ) -> Fill( ( Vcand.at(i).p4).Eta() , weight_ );
    Hist( "PrunedMass_all"    )  ->Fill( Vcand.at(i).prunedMass, weight_ );
    Hist( "SoftdropMass_all"  )  ->Fill( Vcand.at(i).softdropMass, weight_ );
  }
  
  Hist( "Mjj_all") -> Fill( ( Vcand.at(0).p4 + Vcand.at(1).p4 ).M() , weight_ );
  
  if( isSignal_ ){
  

   
    ////////////////// FOR W ////////////////////

      std::map<int,TLorentzVector>::iterator it = genCandidates_.find(24)!=genCandidates_.end() ? genCandidates_.find(24) : genCandidates_.find(-24);
      if ( ((Vcand.at(0).p4).DeltaR(it->second)) < 0.2){
        
        if ( fabs(Vcand.at(0).p4.Eta()) <= 1.2) Hist( "Softdrop_eta1v2" ) -> Fill( Vcand.at(0).softdropMass, weight_ );        
        if ( fabs(Vcand.at(0).p4.Eta()) > 1.2 && fabs(Vcand.at(0).p4.Eta()) < 1.8) Hist( "Softdrop_eta1v8" ) -> Fill( Vcand.at(0).softdropMass, weight_ );       
        if ( fabs(Vcand.at(0).p4.Eta()) >= 1.8) Hist( "Softdrop_eta2v4" ) -> Fill( Vcand.at(0).softdropMass, weight_ );
        
    
        Hist( "SoftdropvsEta" ) -> Fill( Vcand.at(0).softdropMass, Vcand.at(0).p4.Eta() );
        Hist( "SoftdropvsPt" ) -> Fill( Vcand.at(0).softdropMass, Vcand.at(0).p4.Pt() );
        Hist( "recoWPrunedMass" )->Fill( (Vcand.at(0)).prunedMass );
        Hist( "recoWSoftdropMass" )->Fill( (Vcand.at(0)).softdropMass );
        
      }
      if ( ((Vcand.at(1).p4).DeltaR(it->second)) < 0.2){
        
        if ( fabs(Vcand.at(1).p4.Eta()) <= 1.2) Hist( "Softdrop_eta1v2" ) -> Fill( Vcand.at(1).softdropMass, weight_ );
        if ( fabs(Vcand.at(1).p4.Eta()) > 1.2 && fabs(Vcand.at(1).p4.Eta()) < 1.8) Hist( "Softdrop_eta1v8" ) -> Fill( Vcand.at(1).softdropMass, weight_ );
        if ( fabs(Vcand.at(1).p4.Eta()) >= 1.8) Hist( "Softdrop_eta2v4" ) -> Fill( Vcand.at(1).softdropMass, weight_ );
        
        Hist( "SoftdropvsEta" ) -> Fill( Vcand.at(1).softdropMass, Vcand.at(1).p4.Eta() );
        Hist( "SoftdropvsPt" ) -> Fill( Vcand.at(1).softdropMass, Vcand.at(1).p4.Pt() );
        
        Hist( "recoWPrunedMass" )->Fill( (Vcand.at(1)).prunedMass );
        Hist( "recoWSoftdropMass" )->Fill( (Vcand.at(1)).softdropMass );
      }
      for( int jj = 0; jj < abs(genJetCand.size()); jj++ ){
        if ( (genJetCand[jj].p4).Pt() >= JetPtCutTight_ && fabs((genJetCand[jj].p4).Eta() ) <= JetEtaCut_ && ((genJetCand[jj].p4).DeltaR(it->second)) < 0.2){
          Hist( "genWMass" )->Fill( (genJetCand[jj].p4).M() ); 
          if( (genJetCand[jj].p4).DeltaR(Vcand.at(0).p4) < 0.2)Hist( "GenVsSoftdrop" )->Fill( (genJetCand[jj].p4).M(),Vcand.at(0).softdropMass );
        }
      }
      ////////////////// FOR H ////////////////////
      std::map<int,TLorentzVector>::iterator itH = genCandidates_.find(25)!=genCandidates_.end() ? genCandidates_.find(25) : genCandidates_.find(-25);
      if (  ((Vcand.at(0).p4).DeltaR(itH->second)) < 0.2){
        Hist( "recoHPrunedMass" )->Fill( (Vcand.at(0)).prunedMass );
        Hist( "recoHSoftdropMass" )->Fill( (Vcand.at(0)).softdropMass );
      }
      if ( ((Vcand.at(1).p4).DeltaR(itH->second)) < 0.2){
        Hist( "recoHPrunedMass" )->Fill( (Vcand.at(1)).prunedMass );
        Hist( "recoHSoftdropMass" )->Fill( (Vcand.at(1)).softdropMass );
      }

      for( int jj = 0; jj < abs(genJetCand.size()); jj++ ){
        if ( (genJetCand[jj].p4).Pt() >= JetPtCutTight_ && fabs((genJetCand[jj].p4).Eta() ) <= JetEtaCut_ && ((genJetCand[jj].p4).DeltaR(itH->second)) < 0.2) Hist( "genHMass" )->Fill( (genJetCand[jj].p4).M() );
      }

    ////////////////// FOR Z ////////////////////

    std::map<int,TLorentzVector>::iterator itZ = genCandidates_.find(23)!=genCandidates_.end() ? genCandidates_.find(23) : genCandidates_.find(23);
    if ( ((Vcand.at(0).p4).DeltaR(itZ->second)) < 0.2){
       Hist( "recoZPrunedMass" )->Fill( (Vcand.at(0)).prunedMass );
       Hist( "recoZSoftdropMass" )->Fill( (Vcand.at(0)).softdropMass );
     }
    if ( ((Vcand.at(1).p4).DeltaR(itZ->second)) < 0.2){
      Hist( "recoZPrunedMass" )->Fill( (Vcand.at(1)).prunedMass );
      Hist( "recoZSoftdropMass" )->Fill( (Vcand.at(1)).softdropMass );
    }
    for( int jj = 0; jj < abs(genJetCand.size()); jj++ ){
      if ( (genJetCand[jj].p4).Pt() >= JetPtCutTight_ && fabs((genJetCand[jj].p4).Eta() ) <= JetEtaCut_ && ((genJetCand[jj].p4).DeltaR(itZ->second)) < 0.2) Hist( "genZMass" )->Fill( (genJetCand[jj].p4).M() );
    }
    
  }

    ////////////////////////////////////////////


  //Only select jets separated by |DeltaEta| < cut
  jetsDeltaEta = fabs( Vcand.at(0).p4.Eta()  - Vcand.at(1).p4.Eta() ) ; 
  if ( jetsDeltaEta <= dEtaCut_ ){
    Hist( "Mjj" ) -> Fill( ( Vcand.at(0).p4 + Vcand.at(1).p4 ).M() , weight_ );	
    passedDeltaEtaCut = true;	
  }	
	
  //Only select jets with Mjj > cut
  // Mjj = ( Vcand.at(0).p4 + Vcand.at(1).p4 ).M();	
  if ( ( Vcand.at(0).p4 + Vcand.at(1).p4 ).M() >= MjjCut_ ){
    Hist( "DeltaEta")	->Fill( jetsDeltaEta , weight_ ); 	
    passedMjjCut = true;
  }
	
	
  //Only select jets with cut < Tau21 < cut
  if( Channel_ == "VVdijet"){
    if( (Vcand.at(0).tau2/Vcand.at(0).tau1 >= Tau21HPLow_ && Vcand.at(0).tau2/Vcand.at(0).tau1 <= Tau21HPHigh_ && Vcand.at(1).tau2/Vcand.at(1).tau1 > Tau21Low_ && Vcand.at(1).tau2/Vcand.at(1).tau1 <= Tau21High_ ) ||
      (	 Vcand.at(1).tau2/Vcand.at(1).tau1 >= Tau21HPLow_ && Vcand.at(1).tau2/Vcand.at(1).tau1 <= Tau21HPHigh_ && Vcand.at(0).tau2/Vcand.at(0).tau1 > Tau21Low_ && Vcand.at(0).tau2/Vcand.at(0).tau1 <= Tau21High_ ) ) passedTau21Cut = true ;

    //Only select jets in groomed mass window
    if( UsePruned_ && ( Vcand.at(0).prunedMass > mPMLow_ && Vcand.at(0).prunedMass < mPMHigh_ ) && ( Vcand.at(1).prunedMass > mPMLow_ && Vcand.at(1).prunedMass < mPMHigh_ ) )				passedPrunedMassCut = true ;	
    else 
      if(  UseSD_ && ( Vcand.at(0).softdropMass > mSDLow_ && Vcand.at(0).softdropMass < mSDHigh_ ) && ( Vcand.at(1).softdropMass > mSDLow_ && Vcand.at(1).softdropMass < mSDHigh_ ) )	passedPrunedMassCut = true ;
		
  }
  else
  if( Channel_ == "qVdijet"){
    if( (Vcand.at(0).tau2/Vcand.at(0).tau1 > Tau21Low_ && Vcand.at(0).tau2/Vcand.at(0).tau1 <= Tau21High_ ) || ( Vcand.at(1).tau2/Vcand.at(1).tau1 > Tau21Low_ && Vcand.at(1).tau2/Vcand.at(1).tau1 <= Tau21High_ ) ) passedTau21Cut = true ;
    if( (Vcand.at(0).tau2/Vcand.at(0).tau1 > Tau21Low_ && Vcand.at(0).tau2/Vcand.at(0).tau1 <= Tau21High_ ) && ( Vcand.at(0).prunedMass > mPMLow_ && Vcand.at(0).prunedMass < mPMHigh_ ) ) passedPrunedMassCut = true;
    else
      if( (Vcand.at(1).tau2/Vcand.at(1).tau1 > Tau21Low_ && Vcand.at(1).tau2/Vcand.at(1).tau1 <= Tau21High_ ) && ( Vcand.at(1).prunedMass > mPMLow_ && Vcand.at(1).prunedMass < mPMHigh_ ) ) passedPrunedMassCut = true ;			
  } 
	
  if(passedPrunedMassCut && passedTau21Cut) passedWTag = true ;	
	
  if( passedDeltaEtaCut && passedMjjCut ){
    Hist( "Tau21"	)->Fill( Vcand.at(0).tau2/Vcand.at(0).tau1,weight_ );
    Hist( "Tau21"	)->Fill( Vcand.at(1).tau2/Vcand.at(1).tau1,weight_ );
    Hist( "PrunedMass"		)	->Fill( Vcand.at(0).prunedMass, weight_ );
    Hist( "PrunedMass"		)	->Fill( Vcand.at(1).prunedMass, weight_ );
    Hist( "SoftdropMass"	)	->Fill( Vcand.at(0).softdropMass, weight_ );
    Hist( "SoftdropMass"	)	->Fill( Vcand.at(1).softdropMass, weight_ );	
  }
	
  if ( passedDeltaEtaCut && passedMjjCut && passedPrunedMassCut ){
    Hist( "Tau21_punzi"	)->Fill( Vcand.at(0).tau2/Vcand.at(0).tau1,weight_ );
    Hist( "Tau21_punzi"	)->Fill( Vcand.at(1).tau2/Vcand.at(1).tau1,weight_ );
    Hist( "Tau21vsPt" 	)->Fill( Vcand.at(0).tau2/Vcand.at(0).tau1, (float)(Vcand.at(0).p4.Pt()) );
    Hist( "Tau21vsPt"	  )->Fill( Vcand.at(1).tau2/Vcand.at(1).tau1, (float)(Vcand.at(1).p4.Pt()) );
  }
  //Some trigger efficiencies without dEta requirement
  if( Vcand.at(0).p4.Pt() > 500 ){
    Hist( "TriggerEffPrunedMassDen_PtCut"  ) ->Fill( Vcand.at(0).prunedMass		);
    Hist( "TriggerEffSoftdropMassDen_PtCut") ->Fill( Vcand.at(0).softdropMass	);
		
    if( data_.isFired_HLT_AK8PFJet360_TrimMass30_v1 ){
      Hist( "TriggerEffPrunedMass_HLT_AK8PFJet360_TrimMass30_PtCut"											)->Fill ( Vcand.at(0).prunedMass		);
      Hist( "TriggerEffSoftdropMass_HLT_AK8PFJet360_TrimMass30_PtCut"										)->Fill ( Vcand.at(0).softdropMass	);
    }
    if( data_.isFired_HLT_AK8PFHT700_TrimR0p1PT0p03Mass50_v1 ){
      Hist( "TriggerEffPrunedMass_HLT_AK8PFHT700_TrimR0p1PT0p03Mass50_PtCut"						)->Fill ( Vcand.at(0).prunedMass		);
      Hist( "TriggerEffSoftdropMass_HLT_AK8PFHT700_TrimR0p1PT0p03Mass50_PtCut"					)->Fill ( Vcand.at(0).softdropMass	);
    }
    if( data_.isFired_HLT_AK8DiPFJet280_200_TrimMass30_BTagCSV0p41_v1 ){
      Hist( "TriggerEffPrunedMass_HLT_AK8DiPFJet280_200_TrimMass30_BTagCSV0p41_PtCut"		)->Fill ( Vcand.at(0).prunedMass		);
      Hist( "TriggerEffSoftdropMass_HLT_AK8DiPFJet280_200_TrimMass30_BTagCSV0p41_PtCut"	)->Fill ( Vcand.at(0).softdropMass	);
    }
    if( data_.isFired_HLT_AK8DiPFJet280_200_TrimMass30_BTagCSV0p41_v1 || data_.isFired_HLT_AK8PFHT700_TrimR0p1PT0p03Mass50_v1 || data_.isFired_HLT_AK8PFJet360_TrimMass30_v1 || data_.isFired_HLT_PFHT650_WideJetMJJ950DEtaJJ1p5_v1
    || data_.isFired_HLT_PFHT650_WideJetMJJ900DEtaJJ1p5_v1 || data_.isFired_HLT_PFHT900_v1){
      Hist( "TriggerEffPrunedMass_ALL_PtCut"		)->Fill ( Vcand.at(0).prunedMass		);
      Hist( "TriggerEffSoftdropMass_ALL_PtCut"	)->Fill ( Vcand.at(0).softdropMass	);
    }
    if( data_.isFired_HLT_AK8DiPFJet280_200_TrimMass30_BTagCSV0p41_v1 || data_.isFired_HLT_AK8PFHT700_TrimR0p1PT0p03Mass50_v1 || data_.isFired_HLT_AK8PFJet360_TrimMass30_v1){
      Hist( "TriggerEffPrunedMass_trimmed_PtCut"		)->Fill ( Vcand.at(0).prunedMass		);
      Hist( "TriggerEffSoftdropMass_trimmed_PtCut"	)->Fill ( Vcand.at(0).softdropMass	);
    }  
		
  }
	
  // Trigger efficiencies
  // if( passedDeltaEtaCut ) doJetRecoEfficiency();
   
   
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
  for( int j = 0; j < 2; ++j ){
    if( (*data_.jetAK8_IDLoose)[j]		!= 1							)continue;
    if( (*data_.jetAK8_pt)[j]					<= JetPtCutTight_	)continue;
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
    for( int jj = 0; jj < 2; ++jj ){
      if( (*data_.jetAK8_pt)[jj] == jetPt.at(0) ){
        TLV.SetPtEtaPhiE( (*data_.jetAK8_pt)[jj], (*data_.jetAK8_eta)[jj], (*data_.jetAK8_phi)[jj], (*data_.jetAK8_e)[jj] );
        JetCandidate leadingJet(TLV);
        leadingJet.csv					= -99																			;
        leadingJet.tau1					= (*data_.jetAK8_tau1)[jj]								;
        leadingJet.tau2					= (*data_.jetAK8_tau2)[jj]								;
        leadingJet.tau3					= (*data_.jetAK8_tau3)[jj]								;
        leadingJet.prunedMass		= (*data_.jetAK8_prunedmass)[jj]		;
        leadingJet.softdropMass	= (*data_.jetAK8_softdropmass)[jj]	;
        leadingJet.mass					= (*data_.jetAK8_mass)[jj]								;
        leadingJet.flavor				= -99																			;
        leadingJet.rcn					= (*data_.jetAK8_che)[jj]/(*data_.jetAK8_ne)[jj];
        Vcand.push_back( leadingJet );
        if( (*data_.jetAK8_softdropmass)[jj] < 5.) Hist("nConstituents")->Fill( (*data_.jetAK8_cm)[jj]+(*data_.jetAK8_nm)[jj] );
      }
      else
      if( (*data_.jetAK8_pt)[jj] == jetPt.at(1) ){
        TLV.SetPtEtaPhiE( (*data_.jetAK8_pt)[jj], (*data_.jetAK8_eta)[jj], (*data_.jetAK8_phi)[jj], (*data_.jetAK8_e)[jj] );
        JetCandidate secondJet(TLV);
        secondJet.csv					= -99																							;
        secondJet.tau1					= (*data_.jetAK8_tau1)[jj]											;
        secondJet.tau2					= (*data_.jetAK8_tau2)[jj]											;
        secondJet.tau3					= (*data_.jetAK8_tau3)[jj]											;
        secondJet.prunedMass		= (*data_.jetAK8_prunedmass)[jj]					;
        secondJet.softdropMass	= (*data_.jetAK8_softdropmass)[jj]				;
        secondJet.mass					= (*data_.jetAK8_mass)[jj]											;
        secondJet.flavor				= -99																						;
        secondJet.rcn						= (*data_.jetAK8_che)[jj]/(*data_.jetAK8_ne)[jj];
        Vcand.push_back( secondJet );
        if( (*data_.jetAK8_softdropmass)[jj] < 5.) Hist("nConstituents")->Fill((*data_.jetAK8_cm)[jj]+(*data_.jetAK8_nm)[jj]);
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
    if( newpt 									<= AleptPtCut_					)	continue;
    if( fabs((*data_.lep_eta)[l]) 		>= AleptEtaCut_				)	continue;
    foundAMu++;
  }
   
  int foundAEle = 0;
  for( unsigned int l = 0; l < (data_.lep_pt)->size(); ++l ){
    if( abs((*data_.lep_type)[l])											!= 11																) continue;
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
    if( (*data_.lep_isTightElectron)[l]		!= 1															)	continue;
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
    if( (*data_.lep_isLooseElectron)[l]		!= 1															) continue;
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
    if( leptonCand_.at(0).p4.DeltaR(jet) <= 1.0 ) continue;
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
    jetC.prunedMass = (*data_.jetAK8_prunedmass)[jetIndex]+getPrunedMassScale((*data_.jetAK8_prunedmass)[jetIndex]);
    jetC.softdropMass = (*data_.jetAK8_softdropmass)[jetIndex];
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
    if( (Channel_ == "electron" || Channel_ == "muon"  ) && jet.DeltaR(WCand_.at(0).p4) < 0.8 ) continue;
    if( (*data_.jetAK4_IDLoose)[j] != 1 ) continue;
    if( (*data_.jetAK4_pt)[j] <= 30. ) continue;
    if( fabs((*data_.jetAK4_eta)[j]) >= JetEtaCut_ ) continue;
    if( jet.DeltaR(leptonCand_.at(0).p4) < 0.3 ) continue;
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
  if( (*data_.MET_et).at(0) > 0. ){
   
    if( ScaleMuonUpDown_ == 0 ) TLV.SetPtEtaPhiE( (*data_.MET_et).at(0), 0., (*data_.MET_phi).at(0), 0. );
    else{

      TVector2 lepnew; lepnew.SetMagPhi( leptonCand_.at(0).p4.Pt(), leptonCand_.at(0).p4.Phi() );
      TVector2 lep; lep.SetMagPhi( leptonCand_.at(0).p4.Pt() - leptonCand_.at(0).scale, leptonCand_.at(0).p4.Phi() );
      TVector2 diff = lepnew - lep;
      TVector2 met; met.SetMagPhi( (*data_.MET_et).at(0), (*data_.MET_phi).at(0) );
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
    if (AK4jetCand_[i].p4.Pt() == Leptonicb_.at(0).p4.Pt() || AK4jetCand_[i].p4.Pt() <= 0. ) continue;
    for(int j=0; j != i && j < abs(AK4jetCand_.size()); j++ ){
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
void ExoDiBosonAnalysis::findExoCandidate( void ){

  TLorentzVector p4nu = getp4Nu();      
  MVV = (p4nu + leptonCand_.at(0).p4 + Vcand[jetIndex_].p4).M();
  WMass = (p4nu + leptonCand_.at(0).p4).M();
   
  TLorentzVector p4nu2 = getp4NuMethod2();
  //Hist( "pzNu" )->Fill(p4nu2.Pz());

  //Hist( "NuLeptInvMass"  )->Fill( (p4nu2 + leptonCand_.at(0).p4).M() );
  MVVmethod2 = (p4nu2 + leptonCand_.at(0).p4 + Vcand.at(0).p4).M();  
  WMassMethod2 = (p4nu2 + leptonCand_.at(0).p4).M();  

  return;
            
}

//==============================================================================================
void ExoDiBosonAnalysis::fillSFHistos( void ){
  Hist( "leptonPT"            )->Fill( leptonCand_.at(0).p4.Pt()	, weight_ );
  Hist( "leptonPhi"         	)->Fill( leptonCand_.at(0).p4.Phi(), weight_ );
  Hist( "leptonEta"        	 	)->Fill( leptonCand_.at(0).p4.Eta(), weight_ );
	
  // Hist( "WtransvMassLeptonic")->Fill( TMath::Sqrt( 2*METCand_.at(0).p4.Pt()*leptonCand_.at(0).p4.Pt()*(1-cos(leptonCand_.at(0).p4.DeltaPhi(METCand_.at(0).p4))) ), weight_ );
  if( abs(AK4jetCand_.size()) != 0 ){ 
    Hist( "AK4jetPt"       )->Fill( AK4jetCand_.at(0).p4.Pt(), weight_ );
    Hist( "AK4jetPt"       )->Fill( AK4jetCand_.at(1).p4.Pt(), weight_ );
    Hist( "AK4jetPt"       )->Fill( AK4jetCand_[2].p4.Pt(), weight_ );
    Hist( "AK4jetPt"       )->Fill( AK4jetCand_[3].p4.Pt(), weight_ );
    Hist( "AK4jetCSV"      )->Fill( AK4jetCand_.at(0).csv		, weight_ );
    Hist( "AK4jetCSV"      )->Fill( AK4jetCand_.at(1).csv		, weight_ );
    Hist( "AK4jetCSV"      )->Fill( AK4jetCand_[2].csv		, weight_ );
    Hist( "AK4jetCSV"      )->Fill( AK4jetCand_[3].csv		, weight_ );
    Hist( "AK4jetMass"     )->Fill( AK4jetCand_.at(0).p4.M()	, weight_ );
    Hist( "AK4jetMass"     )->Fill( AK4jetCand_.at(1).p4.M()	, weight_ );
    Hist( "AK4jetMass"     )->Fill( AK4jetCand_[2].p4.M()	, weight_ );
    Hist( "AK4jetMass"     )->Fill( AK4jetCand_[3].p4.M()	, weight_ );
  }
	
}

//==============================================================================================
void ExoDiBosonAnalysis::fillHistos( void ){


  if(Channel_ == "VVdijet"){
    // /* MVV */
    Hist( "VVdeltaEta"        )-> Fill( jetsDeltaEta , weight_ ); 
    Hist( "VcandTau21"        )->Fill( Vcand.at(0).tau2/Vcand.at(0).tau1,weight_ );
    Hist( "VcandTau21"        )->Fill( Vcand.at(1).tau2/Vcand.at(1).tau1,weight_ );
    Hist( "DiBosonInvMass"    )->Fill( (Vcand.at(0).p4 + Vcand.at(1).p4).M(), weight_ );
    Hist( "VcandPrunedMass"   )->Fill( Vcand.at(0).prunedMass, weight_ );
    Hist( "VcandPrunedMass"   )->Fill( Vcand.at(1).prunedMass, weight_ );
    Hist( "VcandSoftdropMass" )->Fill( Vcand.at(0).softdropMass, weight_ );
    Hist( "VcandSoftdropMass" )->Fill( Vcand.at(1).softdropMass, weight_ );
    Hist( "VcandPt1"          )->Fill( Vcand.at(0).p4.Pt() , weight_ );
    Hist( "VcandPt2"          )->Fill( Vcand.at(1).p4.Pt() , weight_ );
    Hist( "VcandEta1"         )->Fill( Vcand.at(0).p4.Eta(), weight_ );
    Hist( "VcandEta2"         )->Fill( Vcand.at(1).p4.Eta(), weight_ );
    Hist( "VcandPhi1"         )->Fill( Vcand.at(0).p4.Phi(), weight_ );
    Hist( "VcandPhi2"         )->Fill( Vcand.at(1).p4.Phi(), weight_ );
    Hist( "VcandMass1"        )->Fill( Vcand.at(0).mass , weight_ );
    Hist( "VcandMass2"        )->Fill( Vcand.at(1).mass , weight_ );
  }
	
}


//==============================================================================================
void ExoDiBosonAnalysis::findTopCandidate( void ){

  unsigned int size = abs(AK4jetCand_.size());
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
    dR = AK4jetCand_[j].p4.DeltaR(leptonCand_.at(0).p4);
    if( dR < dRtmp ){
      jetIndex = j;
      dRtmp = dR;  
    } 
  }
   
  TLorentzVector p4nu = getp4Nu();
  ltopmass = (p4nu + leptonCand_.at(0).p4 + AK4jetCand_[jetIndex].p4).M();

  TLorentzVector p4nu2 = getp4NuMethod2();
  ltopmassMethod2 = (p4nu2 + leptonCand_.at(0).p4 + AK4jetCand_[jetIndex].p4).M();
      
}
       			        
//==============================================================================================
void ExoDiBosonAnalysis::EndInputData( const SInputData& ) throw( SError ) {
		
  if (Channel_ == "VVdijet"){

    printCutFlow();
    theHistosManager_->formatHistos();

    //   Hist( "genEvents"               )->SetBinContent(1,genEvents_              );
    Hist( "nEvents"               )->SetBinContent(1,nEvents_               );
    Hist( "nPassedTrigger"        )->SetBinContent(1,nPassedTrigger_        );
    Hist( "nPassedFoundJets"      )->SetBinContent(1,nPassedFoundJets_      );
    Hist( "nPassedJetsDEta"       )->SetBinContent(1,nPassedJetsDEta_       );
    Hist( "nPassedMjj"            )->SetBinContent(1,nPassedMjj_            );
    Hist( "nPassedTau21Cut"       )->SetBinContent(1,nPassedTau21Cut_       );
    Hist( "nPassedPrunedJetMass"  )->SetBinContent(1,nPassedJetPrunedMass_  );
  }
  else if (Channel_ == "SFmuJets"){

    printCutFlow();
    theHistosManager_->formatHistos();

    Hist( "nEvents"         )->SetBinContent(1,nEvents_        );
    Hist( "nPassedIsoLep"     )->SetBinContent(1,nPassedIsoLep_    );
    Hist( "nPassedVetoLep"   )->SetBinContent(1,nPassedVetoLep_    );
    Hist( "nPassed1Jet"      )->SetBinContent(1,nPassed1Jet_        );
    Hist( "nPassed2Jet"      )->SetBinContent(1,nPassed2Jet_      );
    Hist( "nPassed3Jet"      )->SetBinContent(1,nPassed3Jet_      );
    Hist( "nPassed4Jet"      )->SetBinContent(1,nPassed4Jet_      );
    Hist( "nPassed1bTag"     )->SetBinContent(1,nPassed1bTag_      );
    Hist( "nPassed2bTag"     )->SetBinContent(1,nPassed2bTag_      );

  }

   
  return;

}

//==============================================================================================
void ExoDiBosonAnalysis::EndCycle() throw( SError ) {

  return;

}

//==============================================================================================
void ExoDiBosonAnalysis::printCutFlow( void ) {
	

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
//==============================================================================================
//Efficiency studies============================================================================
//==============================================================================================
//==============================================================================================
void ExoDiBosonAnalysis::doJetRecoEfficiency( void ){
	
  Mjj = ( Vcand.at(0).p4 + Vcand.at(1).p4 ).M();
  ///////////////////////////////////////////// denominators ///////////////////////////////////////////// 	
  Hist( "TriggerEffDen" ) ->Fill( Mjj);
	
  if( Mjj > MjjCut_ && (Vcand.at(0).prunedMass 	> 30 || Vcand.at(1).prunedMass		> 30) )	Hist( "TriggerEffPrunedMassDen"  ) ->Fill( Vcand.at(0).prunedMass   );
  if( Mjj > MjjCut_ && (Vcand.at(0).softdropMass	> 30 || Vcand.at(1).softdropMass > 30) )	Hist( "TriggerEffSoftdropMassDen") ->Fill( Vcand.at(0).softdropMass );
  // if( Mjj > )	Hist( "TriggerEffPrunedMassDen"  ) ->Fill( Vcand.at(0).prunedMass   );
  // if( Mjj > )	Hist( "TriggerEffSoftdropMassDen") ->Fill( Vcand.at(0).softdropMass );
	
  if( ( Vcand.at(0).prunedMass		> mPMLow_ && Vcand.at(0).prunedMass		< mPMHigh_ ) && ( Vcand.at(1).prunedMass		> mPMLow_ && Vcand.at(1).prunedMass		< mPMHigh_ ) )Hist( "TriggerEffPruningCut"				)->Fill ( Mjj );
  if( ( Vcand.at(0).softdropMass > mSDLow_ && Vcand.at(0).softdropMass	< mSDHigh_ ) && ( Vcand.at(1).softdropMass	> mSDLow_ && Vcand.at(1).softdropMass	< mSDHigh_ ) )Hist( "TriggerEffSoftdropCut"				)->Fill ( Mjj );
  if( ( Vcand.at(0).prunedMass		> mPMLow_ && Vcand.at(0).prunedMass		< mPMHigh_ ) || ( Vcand.at(1).prunedMass		> mPMLow_ && Vcand.at(1).prunedMass		< mPMHigh_ ) )Hist( "TriggerEffPruningCut_qstar"	)->Fill ( Mjj );
  if( ( Vcand.at(0).softdropMass > mSDLow_ && Vcand.at(0).softdropMass	< mSDHigh_ ) || ( Vcand.at(1).softdropMass	> mSDLow_ && Vcand.at(1).softdropMass	< mSDHigh_ ) )Hist( "TriggerEffSoftdropCut_qstar"	)->Fill ( Mjj );
	
  if( ( Vcand.at(0).tau2/Vcand.at(0).tau1 > Tau21Low_ && Vcand.at(0).tau2/Vcand.at(0).tau1 < Tau21High_ ) && ( Vcand.at(1).tau2/Vcand.at(1).tau1 > Tau21Low_ && Vcand.at(1).tau2/Vcand.at(1).tau1 < Tau21High_ ) )Hist( "TriggerEffTau21Cut"				)->Fill ( Mjj );
  if( ( Vcand.at(0).tau2/Vcand.at(0).tau1 > Tau21Low_ && Vcand.at(0).tau2/Vcand.at(0).tau1 < Tau21High_ ) || ( Vcand.at(1).tau2/Vcand.at(1).tau1 > Tau21Low_ && Vcand.at(1).tau2/Vcand.at(1).tau1 < Tau21High_ ) )Hist( "TriggerEffTau21Cut_qstar"	)->Fill ( Mjj );
  
  ///////////////////////////////////////////// HLT_AK8PFJet360_TrimMass30 /////////////////////////////////////////////
		
  if( data_.isFired_HLT_AK8PFJet360_TrimMass30_v1 ){
		
    Hist( "TriggerEff_HLT_AK8PFJet360_TrimMass30" )->Fill ( Mjj );
    if( ( Vcand.at(0).prunedMass		> mPMLow_ && Vcand.at(0).prunedMass		< mPMHigh_ ) && ( Vcand.at(1).prunedMass		> mPMLow_ && Vcand.at(1).prunedMass		< mPMHigh_	) )	Hist( "TriggerEff_HLT_AK8PFJet360_TrimMass30_wPruningCut"				)->Fill ( Mjj );	  
    if( ( Vcand.at(0).softdropMass	> mSDLow_ && Vcand.at(0).softdropMass	< mSDHigh_ ) && ( Vcand.at(1).softdropMass	> mSDLow_ && Vcand.at(1).softdropMass	< mSDHigh_	) )	Hist( "TriggerEff_HLT_AK8PFJet360_TrimMass30_wSoftdropCut"			)->Fill ( Mjj );	  
    if( ( Vcand.at(0).prunedMass		> mPMLow_ && Vcand.at(0).prunedMass		< mPMHigh_ ) || ( Vcand.at(1).prunedMass		> mPMLow_ && Vcand.at(1).prunedMass		< mPMHigh_	) )	Hist( "TriggerEff_HLT_AK8PFJet360_TrimMass30_wPruningCut_qstar"	)->Fill ( Mjj );	  
    if( ( Vcand.at(0).softdropMass	> mSDLow_ && Vcand.at(0).softdropMass	< mSDHigh_ ) || ( Vcand.at(1).softdropMass	> mSDLow_ && Vcand.at(1).softdropMass	< mSDHigh_	) )	Hist( "TriggerEff_HLT_AK8PFJet360_TrimMass30_wSoftdropCut_qstar")->Fill ( Mjj );
		
    if( ( Vcand.at(0).tau2/Vcand.at(0).tau1 > Tau21Low_ && Vcand.at(0).tau2/Vcand.at(0).tau1 < Tau21High_ ) && ( Vcand.at(1).tau2/Vcand.at(1).tau1 > Tau21Low_ && Vcand.at(1).tau2/Vcand.at(1).tau1 < Tau21High_ ) )Hist( "TriggerEff_HLT_AK8PFJet360_TrimMass30_wTau21Cut"  )->Fill ( Mjj );
	  
    if( Mjj > MjjCut_ && (Vcand.at(0).prunedMass		> 30 || Vcand.at(1).prunedMass		> 30) ) Hist( "TriggerEffPrunedMass_HLT_AK8PFJet360_TrimMass30_wMjjCut"			)->Fill ( Vcand.at(0).prunedMass		);
    if( Mjj > MjjCut_ && (Vcand.at(0).softdropMass	> 30 || Vcand.at(1).softdropMass	> 30) ) Hist( "TriggerEffSoftdropMass_HLT_AK8PFJet360_TrimMass30_wMjjCut"		)->Fill ( Vcand.at(0).softdropMass	);
  }
	
  ///////////////////////////////////////////// HLT_AK8PFHT700_TrimR0p1PT0p03Mass50_v1 ///////////////////////////////////////////// 
  if( data_.isFired_HLT_AK8PFHT700_TrimR0p1PT0p03Mass50_v1 ){
		
    Hist( "TriggerEff_HLT_AK8PFHT700_TrimR0p1PT0p03Mass50" )->Fill ( Mjj );
    if( ( Vcand.at(0).prunedMass		> mPMLow_ && Vcand.at(0).prunedMass		< mPMHigh_ ) && ( Vcand.at(1).prunedMass		> mPMLow_ && Vcand.at(1).prunedMass		< mPMHigh_	) )	Hist( "TriggerEff_HLT_AK8PFHT700_TrimR0p1PT0p03Mass50_wPruningCut"				)->Fill ( Mjj );	  
    if( ( Vcand.at(0).softdropMass	> mSDLow_ && Vcand.at(0).softdropMass	< mSDHigh_ ) && ( Vcand.at(1).softdropMass	> mSDLow_ && Vcand.at(1).softdropMass	< mSDHigh_	) )	Hist( "TriggerEff_HLT_AK8PFHT700_TrimR0p1PT0p03Mass50_wSoftdropCut"			)->Fill ( Mjj );	  
    if( ( Vcand.at(0).prunedMass		> mPMLow_ && Vcand.at(0).prunedMass		< mPMHigh_ ) || ( Vcand.at(1).prunedMass		> mPMLow_ && Vcand.at(1).prunedMass		< mPMHigh_	) )	Hist( "TriggerEff_HLT_AK8PFHT700_TrimR0p1PT0p03Mass50_wPruningCut_qstar"		)->Fill ( Mjj );	  
    if( ( Vcand.at(0).softdropMass	> mSDLow_ && Vcand.at(0).softdropMass	< mSDHigh_ ) || ( Vcand.at(1).softdropMass	> mSDLow_ && Vcand.at(1).softdropMass	< mSDHigh_	) )	Hist( "TriggerEff_HLT_AK8PFHT700_TrimR0p1PT0p03Mass50_wSoftdropCut_qstar"	)->Fill ( Mjj );
		
    if( ( Vcand.at(0).tau2/Vcand.at(0).tau1 > Tau21Low_ && Vcand.at(0).tau2/Vcand.at(0).tau1 < Tau21High_ ) && ( Vcand.at(1).tau2/Vcand.at(1).tau1 > Tau21Low_ && Vcand.at(1).tau2/Vcand.at(1).tau1 < Tau21High_ ) )Hist( "TriggerEff_HLT_AK8PFHT700_TrimR0p1PT0p03Mass50_wTau21Cut"  )->Fill ( Mjj );
	  
    if( Mjj > MjjCut_ && (Vcand.at(0).prunedMass		> 30 || Vcand.at(1).prunedMass		> 30) ) Hist( "TriggerEffPrunedMass_HLT_AK8PFHT700_TrimR0p1PT0p03Mass50_wMjjCut"		)->Fill ( Vcand.at(0).prunedMass		);
    if( Mjj > MjjCut_ && (Vcand.at(0).softdropMass	> 30 || Vcand.at(1).softdropMass	> 30) ) Hist( "TriggerEffSoftdropMass_HLT_AK8PFHT700_TrimR0p1PT0p03Mass50_wMjjCut"	)->Fill ( Vcand.at(0).softdropMass	);
  }
  ///////////////////////////////////////////// HLT_AK8DiPFJet280_200_TrimMass30_BTagCSV0p41_v1 /////////////////////////////////////////////  
  if( data_.isFired_HLT_AK8DiPFJet280_200_TrimMass30_BTagCSV0p41_v1 ){
		
    Hist( "TriggerEff_HLT_AK8DiPFJet280_200_TrimMass30_BTagCSV0p41" )->Fill ( Mjj );
    if( ( Vcand.at(0).prunedMass		> mPMLow_ && Vcand.at(0).prunedMass		< mPMHigh_ ) && ( Vcand.at(1).prunedMass		> mPMLow_ && Vcand.at(1).prunedMass		< mPMHigh_	) )	Hist( "TriggerEff_HLT_AK8DiPFJet280_200_TrimMass30_BTagCSV0p41_wPruningCut"				)->Fill ( Mjj );	  
    if( ( Vcand.at(0).softdropMass	> mSDLow_ && Vcand.at(0).softdropMass	< mSDHigh_ ) && ( Vcand.at(1).softdropMass	> mSDLow_ && Vcand.at(1).softdropMass	< mSDHigh_	) )	Hist( "TriggerEff_HLT_AK8DiPFJet280_200_TrimMass30_BTagCSV0p41_wSoftdropCut"			)->Fill ( Mjj );	  
    if( ( Vcand.at(0).prunedMass		> mPMLow_ && Vcand.at(0).prunedMass		< mPMHigh_ ) || ( Vcand.at(1).prunedMass		> mPMLow_ && Vcand.at(1).prunedMass		< mPMHigh_	) )	Hist( "TriggerEff_HLT_AK8DiPFJet280_200_TrimMass30_BTagCSV0p41_wPruningCut_qstar"		)->Fill ( Mjj );	  
    if( ( Vcand.at(0).softdropMass	> mSDLow_ && Vcand.at(0).softdropMass	< mSDHigh_ ) || ( Vcand.at(1).softdropMass	> mSDLow_ && Vcand.at(1).softdropMass	< mSDHigh_	) )	Hist( "TriggerEff_HLT_AK8DiPFJet280_200_TrimMass30_BTagCSV0p41_wSoftdropCut_qstar"	)->Fill ( Mjj );
		
    if( ( Vcand.at(0).tau2/Vcand.at(0).tau1 > Tau21Low_ && Vcand.at(0).tau2/Vcand.at(0).tau1 < Tau21High_ ) && ( Vcand.at(1).tau2/Vcand.at(1).tau1 > Tau21Low_ && Vcand.at(1).tau2/Vcand.at(1).tau1 < Tau21High_ ) )Hist( "TriggerEff_HLT_AK8DiPFJet280_200_TrimMass30_BTagCSV0p41_wTau21Cut"  )->Fill ( Mjj );
	  
    if( Mjj > MjjCut_ && (Vcand.at(0).prunedMass		> 30 || Vcand.at(1).prunedMass	> 30) ) Hist( "TriggerEffPrunedMass_HLT_AK8DiPFJet280_200_TrimMass30_BTagCSV0p41_wMjjCut"			)->Fill ( Vcand.at(0).prunedMass		);
    if( Mjj > MjjCut_ && (Vcand.at(0).softdropMass	> 30 || Vcand.at(1).softdropMass	> 30) ) Hist( "TriggerEffSoftdropMass_HLT_AK8DiPFJet280_200_TrimMass30_BTagCSV0p41_wMjjCut"	)->Fill ( Vcand.at(0).softdropMass	);
  }
	
  ///////////////////////////////////////////// HLT_PFHT900 ///////////////////////////////////////////// 
  if( data_.isFired_HLT_PFHT600_v1 ){
		
    Hist( "TriggerEff_HLT_PFHT600" )->Fill ( Mjj );
  
    if( ( Vcand.at(0).prunedMass		> mPMLow_ && Vcand.at(0).prunedMass		< mPMHigh_ ) && ( Vcand.at(1).prunedMass		> mPMLow_ && Vcand.at(1).prunedMass		< mPMHigh_ ) )	Hist( "TriggerEff_HLT_PFHT600_wPruningCut"	)->Fill ( Mjj );
    if( ( Vcand.at(0).prunedMass		> mPMLow_ && Vcand.at(0).prunedMass		< mPMHigh_ ) || ( Vcand.at(1).prunedMass		> mPMLow_ && Vcand.at(1).prunedMass		< mPMHigh_ ) )	Hist( "TriggerEff_HLT_PFHT600_wPruningCut_qstar"	)->Fill ( Mjj );
    if( ( Vcand.at(0).softdropMass	> mSDLow_ && Vcand.at(0).softdropMass	< mSDHigh_ ) && ( Vcand.at(1).softdropMass	> mSDLow_ && Vcand.at(1).softdropMass	< mSDHigh_ ) )	Hist( "TriggerEff_HLT_PFHT600_wSoftdropCut"	)->Fill ( Mjj );
	
    if( ( Vcand.at(0).tau2/Vcand.at(0).tau1 > Tau21Low_ && Vcand.at(0).tau2/Vcand.at(0).tau1 < Tau21High_ ) && ( Vcand.at(1).tau2/Vcand.at(1).tau1 > Tau21Low_ && Vcand.at(1).tau2/Vcand.at(1).tau1 < Tau21High_ ) )Hist( "TriggerEff_HLT_PFHT600_wTau21Cut" )->Fill ( Mjj );
  }
  ///////////////////////////////////////////// HLT_PFHT900 ///////////////////////////////////////////// 
  if( data_.isFired_HLT_PFHT900_v1 ){
		
    Hist( "TriggerEff_HLT_PFHT650" )->Fill ( Mjj );
  
    if( ( Vcand.at(0).prunedMass		> mPMLow_ && Vcand.at(0).prunedMass		< mPMHigh_ ) && ( Vcand.at(1).prunedMass		> mPMLow_ && Vcand.at(1).prunedMass		< mPMHigh_ ) )	Hist( "TriggerEff_HLT_PFHT650_wPruningCut"	)->Fill ( Mjj );
    if( ( Vcand.at(0).prunedMass		> mPMLow_ && Vcand.at(0).prunedMass		< mPMHigh_ ) || ( Vcand.at(1).prunedMass		> mPMLow_ && Vcand.at(1).prunedMass		< mPMHigh_ ) )	Hist( "TriggerEff_HLT_PFHT650_wPruningCut_qstar"	)->Fill ( Mjj );
    if( ( Vcand.at(0).softdropMass	> mSDLow_ && Vcand.at(0).softdropMass	< mSDHigh_ ) && ( Vcand.at(1).softdropMass	> mSDLow_ && Vcand.at(1).softdropMass	< mSDHigh_ ) )	Hist( "TriggerEff_HLT_PFHT650_wSoftdropCut"	)->Fill ( Mjj );
	
    if( ( Vcand.at(0).tau2/Vcand.at(0).tau1 > Tau21Low_ && Vcand.at(0).tau2/Vcand.at(0).tau1 < Tau21High_ ) && ( Vcand.at(1).tau2/Vcand.at(1).tau1 > Tau21Low_ && Vcand.at(1).tau2/Vcand.at(1).tau1 < Tau21High_ ) )Hist( "TriggerEff_HLT_PFHT650_wTau21Cut" )->Fill ( Mjj );
  }
  ///////////////////////////////////////////// HLT_PFHT900 ///////////////////////////////////////////// 
  if( data_.isFired_HLT_PFHT900_v1 ){
		
    Hist( "TriggerEff_HLT_PFHT900" )->Fill ( Mjj );
  
    if( ( Vcand.at(0).prunedMass		> mPMLow_ && Vcand.at(0).prunedMass		< mPMHigh_ ) && ( Vcand.at(1).prunedMass		> mPMLow_ && Vcand.at(1).prunedMass		< mPMHigh_ ) )	Hist( "TriggerEff_HLT_PFHT900_wPruningCut"	)->Fill ( Mjj );
    if( ( Vcand.at(0).prunedMass		> mPMLow_ && Vcand.at(0).prunedMass		< mPMHigh_ ) || ( Vcand.at(1).prunedMass		> mPMLow_ && Vcand.at(1).prunedMass		< mPMHigh_ ) )	Hist( "TriggerEff_HLT_PFHT900_wPruningCut_qstar"	)->Fill ( Mjj );
    if( ( Vcand.at(0).softdropMass	> mSDLow_ && Vcand.at(0).softdropMass	< mSDHigh_ ) && ( Vcand.at(1).softdropMass	> mSDLow_ && Vcand.at(1).softdropMass	< mSDHigh_ ) )	Hist( "TriggerEff_HLT_PFHT900_wSoftdropCut"	)->Fill ( Mjj );
	
    if( ( Vcand.at(0).tau2/Vcand.at(0).tau1 > Tau21Low_ && Vcand.at(0).tau2/Vcand.at(0).tau1 < Tau21High_ ) && ( Vcand.at(1).tau2/Vcand.at(1).tau1 > Tau21Low_ && Vcand.at(1).tau2/Vcand.at(1).tau1 < Tau21High_ ) )Hist( "TriggerEff_HLT_PFHT900_wTau21Cut" )->Fill ( Mjj );
  }
  
  ///////////////////////////////////////////// HLT_PFHT650_WideJetMJJ950DEtaJJ1p5 ///////////////////////////////////////////// 
  if( data_.isFired_HLT_PFHT650_WideJetMJJ950DEtaJJ1p5_v1 ){
		
    Hist( "TriggerEff_HLT_PFHT650_WideJetMJJ950DEtaJJ1p5" )->Fill ( Mjj );
  
    if( ( Vcand.at(0).prunedMass		> mPMLow_ && Vcand.at(0).prunedMass		< mPMHigh_ ) && ( Vcand.at(1).prunedMass		> mPMLow_ && Vcand.at(1).prunedMass		< mPMHigh_ ) )	Hist( "TriggerEff_HLT_PFHT650_WideJetMJJ950DEtaJJ1p5_wPruningCut"	)->Fill ( Mjj );
    if( ( Vcand.at(0).prunedMass		> mPMLow_ && Vcand.at(0).prunedMass		< mPMHigh_ ) || ( Vcand.at(1).prunedMass		> mPMLow_ && Vcand.at(1).prunedMass		< mPMHigh_ ) )	Hist( "TriggerEff_HLT_PFHT650_WideJetMJJ950DEtaJJ1p5_wPruningCut_qstar"	)->Fill ( Mjj );
    if( ( Vcand.at(0).softdropMass	> mSDLow_ && Vcand.at(0).softdropMass	< mSDHigh_ ) && ( Vcand.at(1).softdropMass	> mSDLow_ && Vcand.at(1).softdropMass	< mSDHigh_ ) )	Hist( "TriggerEff_HLT_PFHT650_WideJetMJJ950DEtaJJ1p5_wSoftdropCut")->Fill ( Mjj );
	
    if( ( Vcand.at(0).tau2/Vcand.at(0).tau1 > Tau21Low_ && Vcand.at(0).tau2/Vcand.at(0).tau1 < Tau21High_ ) && ( Vcand.at(1).tau2/Vcand.at(1).tau1 > Tau21Low_ && Vcand.at(1).tau2/Vcand.at(1).tau1 < Tau21High_ ) )Hist( "TriggerEff_HLT_PFHT650_WideJetMJJ950DEtaJJ1p5_wTau21Cut" )->Fill ( Mjj );
  }
  ///////////////////////////////////////////// HLT_PFHT650_WideJetMJJ900DEtaJJ1p5 ///////////////////////////////////////////// 
  if( data_.isFired_HLT_PFHT650_WideJetMJJ900DEtaJJ1p5_v1 ){
		
    Hist( "TriggerEff_HLT_PFHT650_WideJetMJJ900DEtaJJ1p5" )->Fill ( Mjj );
  
    if( ( Vcand.at(0).prunedMass		> mPMLow_ && Vcand.at(0).prunedMass		< mPMHigh_ ) && ( Vcand.at(1).prunedMass		> mPMLow_ && Vcand.at(1).prunedMass		< mPMHigh_ ) )	Hist( "TriggerEff_HLT_PFHT650_WideJetMJJ900DEtaJJ1p5_wPruningCut"	)->Fill ( Mjj );
    if( ( Vcand.at(0).prunedMass		> mPMLow_ && Vcand.at(0).prunedMass		< mPMHigh_ ) || ( Vcand.at(1).prunedMass		> mPMLow_ && Vcand.at(1).prunedMass		< mPMHigh_ ) )	Hist( "TriggerEff_HLT_PFHT650_WideJetMJJ900DEtaJJ1p5_wPruningCut_qstar"	)->Fill ( Mjj );
    if( ( Vcand.at(0).softdropMass	> mSDLow_ && Vcand.at(0).softdropMass	< mSDHigh_ ) && ( Vcand.at(1).softdropMass	> mSDLow_ && Vcand.at(1).softdropMass	< mSDHigh_ ) )	Hist( "TriggerEff_HLT_PFHT650_WideJetMJJ900DEtaJJ1p5_wSoftdropCut"	)->Fill ( Mjj );
	
    if( ( Vcand.at(0).tau2/Vcand.at(0).tau1 > Tau21Low_ && Vcand.at(0).tau2/Vcand.at(0).tau1 < Tau21High_ ) && ( Vcand.at(1).tau2/Vcand.at(1).tau1 > Tau21Low_ && Vcand.at(1).tau2/Vcand.at(1).tau1 < Tau21High_ ) )Hist( "TriggerEff_HLT_PFHT650_WideJetMJJ900DEtaJJ1p5_wTau21Cut" )->Fill ( Mjj );
  }
  
  ///////////////////////////////////////////// OR HT only /////////////////////////////////////////////
  
  if( data_.isFired_HLT_PFHT650_WideJetMJJ950DEtaJJ1p5_v1 || data_.isFired_HLT_PFHT650_WideJetMJJ900DEtaJJ1p5_v1 || data_.isFired_HLT_PFHT900_v1 || data_.isFired_HLT_PFHT600_v1 || data_.isFired_HLT_PFHT650_v1  ){
	  
    Hist( "TriggerEff_HT" )->Fill ( Mjj );
  
    if( ( Vcand.at(0).prunedMass		> mPMLow_ && Vcand.at(0).prunedMass		< mPMHigh_ ) && ( Vcand.at(1).prunedMass		> mPMLow_ && Vcand.at(1).prunedMass		< mPMHigh_ ) )	Hist( "TriggerEff_HT_wPruningCut"				)->Fill ( Mjj );		
    if( ( Vcand.at(0).softdropMass	> mSDLow_ && Vcand.at(0).softdropMass	< mSDHigh_ ) && ( Vcand.at(1).softdropMass	> mSDLow_ && Vcand.at(1).softdropMass	< mSDHigh_ ) )	Hist( "TriggerEff_HT_wSoftdropCut"			)->Fill ( Mjj );	  
    if( ( Vcand.at(0).prunedMass		> mPMLow_ && Vcand.at(0).prunedMass		< mPMHigh_ ) || ( Vcand.at(1).prunedMass		> mPMLow_ && Vcand.at(1).prunedMass		< mPMHigh_ ) )	Hist( "TriggerEff_HT_wPruningCut_qstar"	)->Fill ( Mjj );
    if( ( Vcand.at(0).softdropMass	> mSDLow_ && Vcand.at(0).softdropMass	< mSDHigh_ ) || ( Vcand.at(1).softdropMass	> mSDLow_ && Vcand.at(1).softdropMass	< mSDHigh_ ) )	Hist( "TriggerEff_HT_wSoftdropCut_qstar")->Fill ( Mjj );

    if( ( Vcand.at(0).tau2/Vcand.at(0).tau1 > Tau21Low_ && Vcand.at(0).tau2/Vcand.at(0).tau1 < Tau21High_ ) && ( Vcand.at(1).tau2/Vcand.at(1).tau1 > Tau21Low_ && Vcand.at(1).tau2/Vcand.at(1).tau1 < Tau21High_ ) )Hist( "TriggerEff_HT_wTau21Cut" )->Fill ( Mjj );
  }
	
  //**************************** OR trimmed only ****************************//
  if( data_.isFired_HLT_AK8DiPFJet280_200_TrimMass30_BTagCSV0p41_v1 || data_.isFired_HLT_AK8PFHT700_TrimR0p1PT0p03Mass50_v1 || data_.isFired_HLT_AK8PFJet360_TrimMass30_v1){
    if( ( Vcand.at(0).prunedMass		> mPMLow_ && Vcand.at(0).prunedMass		< mPMHigh_ ) || ( Vcand.at(1).prunedMass		> mPMLow_ && Vcand.at(1).prunedMass		< mPMHigh_ ) )	Hist( "TriggerEff_trimmed_wPruningCut_qstar"		)->Fill( Mjj);
    if( ( Vcand.at(0).prunedMass		> mPMLow_ && Vcand.at(0).prunedMass		< mPMHigh_ ) && ( Vcand.at(1).prunedMass		> mPMLow_ && Vcand.at(1).prunedMass		< mPMHigh_ ) )	Hist( "TriggerEff_trimmed_wPruningCut"		)->Fill( Mjj);
    if( ( Vcand.at(0).softdropMass	> mSDLow_ && Vcand.at(0).softdropMass	< mSDHigh_ ) && ( Vcand.at(1).softdropMass	> mSDLow_ && Vcand.at(1).softdropMass	< mSDHigh_ ) )	Hist( "TriggerEff_trimmed_wSoftdropCut"	)->Fill( Mjj	);
    if( ( Vcand.at(0).softdropMass	> mSDLow_ && Vcand.at(0).softdropMass	< mSDHigh_ ) || ( Vcand.at(1).softdropMass	> mSDLow_ && Vcand.at(1).softdropMass	< mSDHigh_ ) )	Hist( "TriggerEff_trimmed_wSoftdropCut_qstar"	)->Fill( Mjj	);
  }  
	
  //**************************** OR ****************************//
  
  if( data_.isFired_HLT_AK8PFJet360_TrimMass30_v1 || data_.isFired_HLT_AK8PFHT700_TrimR0p1PT0p03Mass50_v1 || data_.isFired_HLT_AK8DiPFJet280_200_TrimMass30_BTagCSV0p41_v1 || data_.isFired_HLT_PFHT650_WideJetMJJ950DEtaJJ1p5_v1 || data_.isFired_HLT_PFHT650_WideJetMJJ900DEtaJJ1p5_v1 || data_.isFired_HLT_PFHT900_v1  ){
	  
    Hist( "TriggerEff_ALL" )->Fill ( Mjj );
  
    if( ( Vcand.at(0).prunedMass		> mPMLow_ && Vcand.at(0).prunedMass		< mPMHigh_ ) && ( Vcand.at(1).prunedMass		> mPMLow_ && Vcand.at(1).prunedMass		< mPMHigh_ ) )	Hist( "TriggerEff_ALL_wPruningCut"				)->Fill ( Mjj );		
    if( ( Vcand.at(0).softdropMass	> mSDLow_ && Vcand.at(0).softdropMass	< mSDHigh_ ) && ( Vcand.at(1).softdropMass	> mSDLow_ && Vcand.at(1).softdropMass	< mSDHigh_ ) )	Hist( "TriggerEff_ALL_wSoftdropCut"			)->Fill ( Mjj );	  
    if( ( Vcand.at(0).prunedMass		> mPMLow_ && Vcand.at(0).prunedMass		< mPMHigh_ ) || ( Vcand.at(1).prunedMass		> mPMLow_ && Vcand.at(1).prunedMass		< mPMHigh_ ) )	Hist( "TriggerEff_ALL_wPruningCut_qstar"	)->Fill ( Mjj );
    if( ( Vcand.at(0).softdropMass	> mSDLow_ && Vcand.at(0).softdropMass	< mSDHigh_ ) || ( Vcand.at(1).softdropMass	> mSDLow_ && Vcand.at(1).softdropMass	< mSDHigh_ ) )	Hist( "TriggerEff_ALL_wSoftdropCut_qstar")->Fill ( Mjj );

    if( ( Vcand.at(0).tau2/Vcand.at(0).tau1 > Tau21Low_ && Vcand.at(0).tau2/Vcand.at(0).tau1 < Tau21High_ ) && ( Vcand.at(1).tau2/Vcand.at(1).tau1 > Tau21Low_ && Vcand.at(1).tau2/Vcand.at(1).tau1 < Tau21High_ ) )Hist( "TriggerEff_ALL_wTau21Cut" )->Fill ( Mjj );
  }
	
  return;
}
