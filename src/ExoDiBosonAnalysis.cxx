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
   , weight_(1.)
   , lheweight_(1.)
   , puweight_(1.)
   , hltweight_(1.)
   , btagweight_(1.)
   , lumiweight_(1.){

   SetLogName( GetName() );
   
   /* general settings */   
   DeclareProperty( "InputTreeName"    , InputTreeName_     );
   DeclareProperty( "OutputTreeName"   , OutputTreeName_    );
   DeclareProperty( "isSignal"         , isSignal_	    );
   DeclareProperty( "runOnMC"          , runOnMC_	    );
   DeclareProperty( "GenFilter"        , genFilter_	    );
   DeclareProperty( "Flavour"          , Flavour_	    );
   DeclareProperty( "Channel"          , Channel_	    );
   DeclareProperty( "Trigger"          , Trigger_	    );

   /* leptonic selections */
   DeclareProperty( "LeptPtCut"        , leptPtCut_	    );
   DeclareProperty( "LeptEtaCut"       , leptEtaCut_	    );
   DeclareProperty( "AleptPtCut"       , AleptPtCut_	    );
   DeclareProperty( "AleptEtaCut"      , AleptEtaCut_	    );
   DeclareProperty( "METCut"           , METCut_	    );
   DeclareProperty( "WptCut"           , WptCut_	    );

   /* jet selections */
   DeclareProperty( "JetPtCutLoose"    , JetPtCutLoose_     );
   DeclareProperty( "JetPtCutTight"    , JetPtCutTight_     );
   DeclareProperty( "JetEtaCut"        , JetEtaCut_	    );  
   
   /* btag veto */
   DeclareProperty( "nAJetCut"         , nAJetCut_	    );
   DeclareProperty( "BtagVetoWP"       , BtagVetoWP_	    );
   
   /* top mass veto */
   DeclareProperty( "TopMassCut"       , TopMassCut_	    );
   DeclareProperty( "leptTopMassLow"   , leptTopMassLow_    );
   DeclareProperty( "leptTopMassHigh"  , leptTopMassHigh_   );
   DeclareProperty( "hadrTopMassLow"   , hadrTopMassLow_    );
   DeclareProperty( "hadrTopMassHigh"  , hadrTopMassHigh_   );
   
   /* pruned mass */   
   DeclareProperty( "VetoSR"           , VetoSR_	    );
   DeclareProperty( "mLow"             , mLow_  	    );
   DeclareProperty( "mHigh"            , mHigh_ 	    );

   /* WH mass window */
   DeclareProperty( "WHMass"           , WHMass_	    );

   /* weights settings */
   DeclareProperty( "LHEsample"         , LHEsample_	      );
   DeclareProperty( "xSec"              , xSec_  	      );
   DeclareProperty( "genEvents"         , genEvents_	      );
   DeclareProperty( "Lumi"              , Lumi_  	      );
   DeclareProperty( "PUdata"            , PUProfileData_      );
   DeclareProperty( "BTagEff4vetoData"  , BTagEff4vetoData_   );
   DeclareProperty( "BTagEff4fatjetData", BTagEff4fatjetData_ );
   DeclareProperty( "BTagEff4subjetData", BTagEff4subjetData_ );
      
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
   
   jetIndex_ = 0;
   
   nEvents_                 = 0;
   nPassedTrigger_          = 0;	   
   nPassedFoundLept_        = 0;	   
   nPassedFoundMET_         = 0;	   
   nPassedFoundW_           = 0;	   
   nPassedFoundJet_         = 0;	   
   nPassedLepJetDR_         = 0;	   
   nPassedJetPtTight_       = 0;	   
   nPassedAJetCut_          = 0;	   
   nPassedLepJetDR2_        = 0;	   
   nPassedMETJetDPhi_       = 0;	   
   nPassedJetWDPhi_         = 0;	   
   nPassedTopMass_          = 0;	   
   nPassedJetMass_          = 0;	   
   nPassedExoCandidateMass_ = 0;
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
      
   theHistosManager_->bookHistos(); 

   DeclareVariable( MWH         , "MWH"       , OutputTreeName_.c_str() );
   DeclareVariable( Mj          , "Mj"	      , OutputTreeName_.c_str() );  
   DeclareVariable( weight_     , "weight"    , OutputTreeName_.c_str() );
   DeclareVariable( puweight_   , "puweight"  , OutputTreeName_.c_str() );
   DeclareVariable( hltweight_  , "hltweight" , OutputTreeName_.c_str() );
   DeclareVariable( lumiweight_ , "lumiweight", OutputTreeName_.c_str() );
   DeclareVariable( btagweight_ , "btagweight", OutputTreeName_.c_str() );
   DeclareVariable( channel     , "channel"   , OutputTreeName_.c_str() );
     
   return;

}

//==============================================================================================
void ExoDiBosonAnalysis::initData( void ){

   data_ = theNtupleManager_->getData();
      
}

//==============================================================================================
void ExoDiBosonAnalysis::reset( void ){

   genCandidates_.clear();
   leptonCand_   .clear();
   AK4jetCand_   .clear();
   fatJetCand_   .clear();
   METCand_      .clear();
   WCand_        .clear();
   
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
   
   if( Channel_ == "muon" && !foundMu ) return false;     

   if( Channel_ == "electron" && !foundEle ) return false;

   if( Channel_ == "tau" && !foundTau ) return false;
            
   return true;   
   
}

//==============================================================================================
void ExoDiBosonAnalysis::setWeight( TString infile ){

   if( !runOnMC_ ) return;

   //for( unsigned int v = 0; v < (data_.nPUTrue)->size(); ++v ){
   //   if( (*data_.bX)[v] == 0 ) puweight_ = PUWeight_.getPUWeight( (*data_.nPUTrue)[v] );
   //}
      
   //hltweight_ = HLTWeight_.getHLTWeight( leptonCand_[0].p4.Pt(), leptonCand_[0].p4.Eta() );
   
   lheweight_ = LHEWeight_.getLHEWeight(data_.lheV_pt);
      
   double lumiw = xSec_/genEvents_;
      
   lumiweight_ = lumiw*LumiWeight_.getLumiWeight( infile );
      
   btagvetow = 1.; 
   htagw = 1.;
   
   //if( BtagSFSysUpVeto_ ) btagvetow = BTagWeight_.getBTagSFWeightUp( AK4jetCand_, "veto" ); 
   //else if( BtagSFSysDownVeto_ ) btagvetow = BTagWeight_.getBTagSFWeightDown( AK4jetCand_, "veto" ); 
   //else btagvetow = BTagWeight_.getBTagWeight( AK4jetCand_, "veto" ); 
      
   if( nAJetCut_ == -1 ) btagvetow = 1.;

   btagweight_ =  btagvetow*htagw;
      
   weight_ = puweight_*lheweight_*lumiweight_*hltweight_*btagweight_;

   //std::cout << "pu w " << puweight_ << " hlt w " << hltweight_ << " btag w " << btagweight_ << " lumi w " << lumiweight_;
   //std::cout << " tot w " << weight_ << std::endl; 
   
}

//==============================================================================================
void ExoDiBosonAnalysis::ExecuteEvent( const SInputData&, Double_t ) throw( SError ) {

   initData();
      
   reset();
         
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
      	   	
   if( passedSelections() ){

       TString infile = TString(this->GetHistInputFile()->GetName());
	                       
       setWeight(infile);
       
       fillHistos();
       
       Mj = fatJetCand_[0].prunedMass;
       
       if( Channel_ == "muon" ) channel = 1;
       else if( Channel_ == "electron" ) channel = 0;
       else channel = 2;
       
   } 
   else 
      throw SError( SError::SkipEvent );
         
   return;

}

//==============================================================================================
bool ExoDiBosonAnalysis::passedTrigger( void ){

   if( !Trigger_ ) return true;
   
   if( Channel_ == "muon" || (Channel_.find("ttbarmu") != std::string::npos) ){
      if( data_.isFired_HLT_Mu40_v1 ){ nPassedTrigger_++; return true;}
   }
   else if( Channel_ == "electron" || (Channel_.find("ttbarel") != std::string::npos) ){
      if( data_.isFired_HLT_Ele95_CaloIdVT_GsfTrkIdT_v1 ) { nPassedTrigger_++; return true;}
   }
   else return false;

   return false;
    
}

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
      if( leptonCand_[0].p4.DeltaR(fatJetCand_[0].p4) > 1.0 ) foundJet2 = true;
      if( fatJetCand_[0].p4.Pt() > JetPtCutTight_ ) foundJet3 = true;
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
   
   if( (Channel_.find("ttbar") == std::string::npos && najet <= nAJetCut_) ||
       (Channel_.find("ttbar") != std::string::npos && najet  > nAJetCut_) ) najetCut = true;
   
   if( nAJetCut_ != -1 && !najetCut ) return false;
   nPassedAJetCut_++;    
      
   /*************************************************************/            
   bool lepJetDR = false;
   if( foundLept && foundJet1 && leptonCand_[0].p4.DeltaR(fatJetCand_[0].p4) > TMath::Pi()/2. ) lepJetDR = true;    

   if( Channel_.find("ttbar") == std::string::npos && !lepJetDR ) return false;
   nPassedLepJetDR2_++;
    
   /*************************************************************/      
   bool METJetDPhi = false;
   if( foundMET && foundJet1 && fabs(METCand_[0].p4.DeltaPhi(fatJetCand_[0].p4)) > 2. ) METJetDPhi = true;

   if( Channel_.find("ttbar") == std::string::npos && !METJetDPhi ) return false;
   nPassedMETJetDPhi_++;
     
   /*************************************************************/         
   bool JetWDPhi = false;
   if( foundW && foundJet1 && fabs(fatJetCand_[0].p4.DeltaPhi(WCand_[0].p4)) > 2. ) JetWDPhi = true;

   if( Channel_.find("ttbar") == std::string::npos && !JetWDPhi ) return false;
   nPassedJetWDPhi_++;   

   /*************************************************************/         
   findTopCandidate();
   if( TopMassCut_ && ((ltopmass > leptTopMassLow_ && ltopmass < leptTopMassHigh_) || (htopmass > hadrTopMassLow_ && htopmass < hadrTopMassHigh_)) ) return false;   
   nPassedTopMass_++;
             
   /*************************************************************/                  
   if( VetoSR_ && fatJetCand_[0].prunedMass > 110. && fatJetCand_[0].prunedMass < 135 ) return false;
   
   bool foundJet = false;   
   if( foundJet1 && fatJetCand_[0].prunedMass > mLow_ && fatJetCand_[0].prunedMass < mHigh_ ) foundJet = true;

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
   if( MWH > low && MWH < up ){
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
   bool foundLept = false;
   double ptMu = -999;
   unsigned int muIndex = -999;
   double scale = 0.;
   double newpt = 0.;
   double scale_ = 0.;
   for( unsigned int l = 0; l < (data_.lep_pt)->size(); ++l ){
      if( abs((*data_.lep_type)[l]) != 13 ) continue;
      if( (*data_.lep_isHighPtMuon)[l] != 1 ) continue;
      scale = getMuonScale((*data_.lep_pt)[l]);
      newpt = (*data_.lep_pt)[l]+scale;
      if( (*data_.lep_trackIso)[l]/newpt >= 0.1 ) continue;
      if( newpt <= leptPtCut_ ) continue;
      if( fabs((*data_.lep_eta)[l]) >= leptEtaCut_ ) continue;
      foundLept = true;
      if( newpt > ptMu ){   
         ptMu = newpt;
         TLV.SetPtEtaPhiE( newpt, (*data_.lep_eta)[l], (*data_.lep_phi)[l], (*data_.lep_e)[l]+scale );  
	 muIndex = l;
	 scale_ = scale;
      }      
   }
   
   if( foundLept ){
     LeptonCandidate muCand(TLV);
     muCand.iso = (*data_.lep_trackIso)[muIndex]/newpt;
     muCand.scale = scale_;
     leptonCand_.push_back( muCand );
   }
   
   int foundAMu = 0;
   scale = 0.;
   for( unsigned int l = 0; l < (data_.lep_pt)->size(); ++l ){
      if( abs((*data_.lep_type)[l]) != 13 ) continue;   
      if( muIndex == -999 || l == muIndex ) continue;
      if( (*data_.lep_isHighPtMuon)[l] != 1 ) continue;
      scale = getMuonScale((*data_.lep_pt)[l]);
      newpt = (*data_.lep_pt)[l]+scale;
      if( (*data_.lep_trackIso)[l]/newpt >= 0.1 ) continue;
      if( newpt <= AleptPtCut_ ) continue;
      if( fabs((*data_.lep_eta)[l]) >= AleptEtaCut_ ) continue;
      foundAMu++;
   }
   
   int foundAEle = 0;
   for( unsigned int l = 0; l < (data_.lep_pt)->size(); ++l ){
      if( abs((*data_.lep_type)[l]) != 11 ) continue;
      if( (*data_.lep_isHEEP)[l] != 1 ) continue;
      if( (*data_.lep_pt)[l] <= 35. ) continue;
      if( fabs((*data_.lep_eta)[l]) >= 1.442 && fabs((*data_.lep_eta)[l]) <= 1.56 ) continue;
      if( fabs((*data_.lep_eta)[l]) >= 2.5 ) continue;
      foundAEle++;
   }
    
   if( (foundAMu+foundAEle)<1 && foundLept ) return true;
   else return false;
   
}

//==============================================================================================
bool ExoDiBosonAnalysis::findElectronCandidate( void ){

   TLorentzVector TLV;
   bool foundEle = false;
   double ptEle = -999;
   unsigned int eleIndex = -999;
   for( unsigned int l = 0; l < (data_.lep_pt)->size(); ++l ){
      if( abs((*data_.lep_type)[l]) != 11 ) continue;
      if( (*data_.lep_pt)[l] <= 35. ) continue;     
      if( fabs((*data_.lep_eta)[l]) >= 1.4442 && fabs((*data_.lep_eta)[l]) <= 1.566 ) continue;            
      if( fabs((*data_.lep_eta)[l]) >= leptEtaCut_ ) continue; 
      if( (*data_.lep_isHEEP)[l] != 1 ) continue;
      if( (*data_.lep_pt)[l] <= leptPtCut_ ) continue;
      foundEle = true;
      if( (*data_.lep_pt)[l] > ptEle ){   
         ptEle = (*data_.lep_pt)[l];
         TLV.SetPtEtaPhiE( (*data_.lep_pt)[l], (*data_.lep_eta)[l], (*data_.lep_phi)[l], (*data_.lep_e)[l] );         
	 eleIndex = l;
      }
   }
      
   if( foundEle )
    leptonCand_.push_back( LeptonCandidate( TLV ) );
   
   int foundAEle = 0;
   for( unsigned int l = 0; l < (data_.lep_pt)->size(); ++l ){
      if( abs((*data_.lep_type)[l]) != 11 ) continue;
      if( eleIndex == -999 || l == eleIndex ) continue;
      if( (*data_.lep_isHEEP)[l] != 1 ) continue;
      if( (*data_.lep_pt)[l] <= AleptPtCut_ ) continue;
      if( fabs((*data_.lep_eta)[l]) >= 1.4442 && fabs((*data_.lep_eta)[l]) <= 1.566 ) continue;
      if( fabs((*data_.lep_eta)[l]) >= AleptEtaCut_ ) continue;
      foundAEle++;
   }

   int foundAMu = 0;
   for( unsigned int l = 0; l < (data_.lep_pt)->size(); ++l ){
      if( abs((*data_.lep_type)[l]) != 13 ) continue;   
      if( (*data_.lep_isHighPtMuon)[l] != 1 ) continue;
      if( (*data_.lep_trackIso)[l]/(*data_.lep_pt)[l] >= 0.1 ) continue;
      if( (*data_.lep_pt)[l] <= 20. ) continue;
      if( fabs((*data_.lep_eta)[l]) >= 2.4 ) continue;
      foundAMu++;
   }
   
   if( (foundAMu+foundAEle)<1 && foundEle ) return true;
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
   int   jetIndex    = -9999;
   float tau1        = -9999;
   float tau2        = -9999;
   float tau3        = -9999;
   
   for( int j = 0; j < data_.njetsAK8; ++j ){
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
     jetC.prunedMass = (*data_.jetAK8_prunedmass)[jetIndex]+getPrunedMassScale((*data_.jetAK8_prunedmass)[jetIndex]);
     jetC.mass = (*data_.jetAK8_mass)[jetIndex];
     fatJetCand_.push_back( jetC );
   }
                        
   return foundJet;

}

//==============================================================================================
void ExoDiBosonAnalysis::findExtraJets( void ){

   TLorentzVector jet;
   for( int j = 0; j < data_.njetsAK4; ++j ){ 
      jet.SetPtEtaPhiE( (*data_.jetAK4_pt)[j], (*data_.jetAK4_eta)[j], (*data_.jetAK4_phi)[j], (*data_.jetAK4_e)[j] );
      if( jet.DeltaR(fatJetCand_[0].p4) < 0.8 ) continue;
      if( (*data_.jetAK4_IDLoose)[j] != 1 ) continue;
      if( (*data_.jetAK4_pt)[j] <= 30. ) continue;
      if( fabs((*data_.jetAK4_eta)[j]) >= JetEtaCut_ ) continue;
      if( jet.DeltaR(leptonCand_[0].p4) < 0.3 ) continue;
      JetCandidate Ajet(jet);
      Ajet.csv = (*data_.jetAK4_csv)[j];
      Ajet.flavor = abs((*data_.jetAK4_flavor)[j]);
      AK4jetCand_.push_back(Ajet);
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
void ExoDiBosonAnalysis::findExoCandidate( void ){

   TLorentzVector p4nu = Utilities::NuMomentum( leptonCand_[0].p4.Px(), leptonCand_[0].p4.Py(), leptonCand_[0].p4.Pz(), leptonCand_[0].p4.Pt(), leptonCand_[0].p4.E(), METCand_[0].p4.Px(), METCand_[0].p4.Py() );   
      
   MWH = (p4nu + leptonCand_[0].p4 + fatJetCand_[jetIndex_].p4).M();
      
   return;
      
}

//==============================================================================================
void ExoDiBosonAnalysis::fillHistos( void ){
         
   /* lepton histos */
   Hist( "leptonPT"         	 )->Fill( leptonCand_[0].p4.Pt(), weight_ );
   Hist( "leptonPhi"         	 )->Fill( leptonCand_[0].p4.Phi(), weight_ );
   Hist( "leptonEta"        	 )->Fill( leptonCand_[0].p4.Eta(), weight_ );

   /* MET histos */
   Hist( "MET"              	 )->Fill( METCand_[0].p4.Pt(), weight_ );
   Hist( "METphi"              	 )->Fill( METCand_[0].p4.Phi(), weight_ );

   /* leptonic W histos */
   Hist( "recoWPT"          	 )->Fill( WCand_[0].p4.Pt(), weight_ );
   Hist( "recoWMT"          	 )->Fill( TMath::Sqrt( 2*METCand_[0].p4.Pt()*leptonCand_[0].p4.Pt()*(1-cos(leptonCand_[0].p4.DeltaPhi(METCand_[0].p4))) ), weight_ );
   
   /* topology histos */
   Hist( "lepJetDR"         	 )->Fill( leptonCand_[0].p4.DeltaR(fatJetCand_[jetIndex_].p4), weight_ );
   Hist( "METJetDphi"       	 )->Fill( fabs(METCand_[0].p4.DeltaPhi(fatJetCand_[jetIndex_].p4)), weight_ );
   Hist( "WJetDphi"         	 )->Fill( fabs(fatJetCand_[jetIndex_].p4.DeltaPhi(WCand_[0].p4)), weight_ );

   /* top histos */
   Hist( "leptonictopmass"       )->Fill( ltopmass,weight_ );
   Hist( "hadronictopmass"       )->Fill( htopmass,weight_ );

   /* MWH */
   Hist( "DiBosonInvMass"        )->Fill( MWH, weight_ );
   
   /* other histos */
   Hist( "PUWeights"        	 )->Fill( puweight_ );
   Hist( "nVertices"        	 )->Fill( data_.nPVs, weight_ );
   Hist( "htagweight"            )->Fill(htagw);
   Hist( "btagvweight"           )->Fill(btagvetow);

   /* AK8 b-jet histos */
   Hist( "AK8bjetPT"       	 )->Fill( fatJetCand_[jetIndex_].p4.Pt(), weight_ );
   Hist( "AK8bjetEta"      	 )->Fill( fatJetCand_[jetIndex_].p4.Eta(), weight_ );
   Hist( "AK8bjetPhi"      	 )->Fill( fatJetCand_[jetIndex_].p4.Phi(), weight_ );
   Hist( "AK8bjetCSV"      	 )->Fill( fatJetCand_[jetIndex_].csv, weight_ );
   Hist( "AK8bjetPrunedMass" 	 )->Fill( fatJetCand_[jetIndex_].prunedMass, weight_ );
   Hist( "AK8bjetMass"       	 )->Fill( fatJetCand_[jetIndex_].mass, weight_ );
   Hist( "tau21"	         )->Fill( fatJetCand_[jetIndex_].tau2/fatJetCand_[jetIndex_].tau1,weight_ );
   Hist( "tau31"	         )->Fill( fatJetCand_[jetIndex_].tau3/fatJetCand_[jetIndex_].tau1,weight_ );
   Hist( "tau32"	         )->Fill( fatJetCand_[jetIndex_].tau3/fatJetCand_[jetIndex_].tau2,weight_ );
          
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
      dR = AK4jetCand_[j].p4.DeltaR(fatJetCand_[jetIndex_].p4);
      if( dR < dRtmp ){
          jetIndex = j;
	  dRtmp = dR;  
      } 
   }
   
   htopmass = (AK4jetCand_[jetIndex].p4+fatJetCand_[jetIndex_].p4).M();
   
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
   
   TLorentzVector p4nu = Utilities::NuMomentum( leptonCand_[0].p4.Px(), leptonCand_[0].p4.Py(), leptonCand_[0].p4.Pz(), leptonCand_[0].p4.Pt(), leptonCand_[0].p4.E(), METCand_[0].p4.Px(), METCand_[0].p4.Py() );
   ltopmass = (p4nu + leptonCand_[0].p4 + AK4jetCand_[jetIndex].p4).M();
   
}
       			        
//==============================================================================================
void ExoDiBosonAnalysis::EndInputData( const SInputData& ) throw( SError ) {

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
   m_logger << INFO << "jet mass cut		                                 " << nPassedJetMass_ << " --- eff = " << (double)nPassedJetMass_/nEvents_ << std::endl;
   m_logger << INFO << "WH mass window		                                 " << nPassedExoCandidateMass_ << " --- eff = " << (double)nPassedExoCandidateMass_/nEvents_ << std::endl;

   m_logger << INFO << std::endl; 
   
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
   std::cout << "jet mass cut		                                 " << nPassedJetMass_ << " --- eff = " << (double)nPassedJetMass_/nEvents_ << std::endl;
   std::cout << "WH mass window		                                 " << nPassedExoCandidateMass_ << " --- eff = " << (double)nPassedExoCandidateMass_/nEvents_ << std::endl;

   std::cout << std::endl; 

   
}



