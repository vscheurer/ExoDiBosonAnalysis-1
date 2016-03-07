#ifndef ExoDiBosonAnalysis_H
#define ExoDiBosonAnalysis_H

#include "core/include/SCycleBase.h"

#include "TLorentzVector.h"
#include <string>
// #include <algorithm>

#include "../ExoDiBosonAnalysis/include/InputData.h"
#include "../ExoDiBosonAnalysis/include/PUWeight.h"
#include "../ExoDiBosonAnalysis/include/LHEWeight.h"
#include "../ExoDiBosonAnalysis/include/HLTWeight.h"
#include "../ExoDiBosonAnalysis/include/BTagWeight.h"
#include "../ExoDiBosonAnalysis/include/LumiWeight.h"
#include "../ExoDiBosonAnalysis/include/JetCandidate.h"
#include "../ExoDiBosonAnalysis/include/LeptonCandidate.h"
#include "../ExoDiBosonAnalysis/include/METCandidate.h"
#include "../ExoDiBosonAnalysis/include/HiggsCandidate.h"
#include "../ExoDiBosonAnalysis/include/PredictedDistribution.h"
#include "../../GoodRunsLists/include/TGoodRunsListReader.h"


class HistosManager;
class NtupleManager;

class ExoDiBosonAnalysis : public SCycleBase {

public:
  ExoDiBosonAnalysis();
  ~ExoDiBosonAnalysis();

  virtual void BeginCycle()	throw( SError );
  virtual void EndCycle()		throw( SError );

  virtual void BeginInputData( const SInputData& )				throw( SError );
  virtual void EndInputData  ( const SInputData& )				throw( SError );
  virtual void BeginInputFile( const SInputData& )				throw( SError );
  virtual void ExecuteEvent	( const SInputData&, Double_t )	throw( SError );
   
  void setGenCandidates          ( void );
   
  void setWeight                 ( TString infile );
  void initWeight                ( void );
   
  void initData                  ( void );
  void reset                     ( void );
  InputData& getData             ( void ){ return data_; }
  void setNtupleManager          ( NtupleManager* ntupleManager ){ theNtupleManager_ = ntupleManager; }
  void printCutFlow              ( void );
  

  void fillHistos                ( std::string Channel );
       
  bool passedTTbarSelections     ( void );
  bool passedDijetSelections     (  TString infile  );
  bool passedDijetSelectionsAK4  (  TString infile  );
  bool applyJSON                 ( void );
  bool passedFilters             ( void );
  bool passedTrigger             ( void );
	
  bool findLeptonCandidate       ( void );     
  double getMuonScale            ( double oldpt );
  bool findMuonCandidate         ( void ); 
  bool findElectronCandidate     ( void ); 
  bool findMETCandidate          ( void );
  bool findWCandidate            ( void );
  bool findHadronicWCandidate    ( void );
  void findExoCandidate          ( void );
  
  void findAK4Jets             ( void ); 
  TLorentzVector getp4Nu         ( void );
  TLorentzVector getp4NuMethod2  ( void );


  bool findJetCandidates         ( void );
  bool findJetCandidatesAK4      ( void );

  void doJetTriggerEfficiency    	 ( void );
  void doJetTriggerEfficiency2    	 ( void );
  void doGenTTReco               ( void );
  void doGroomingStudies         (  TString infile  );

  void setPredictedDistribution();
     
private:
  ClassDef( ExoDiBosonAnalysis, 0 );  
       
  HistosManager* theHistosManager_;
  NtupleManager* theNtupleManager_;
  InputData      data_            ;
  PUWeight       PUWeight_        ;
  HLTWeight      HLTWeight_       ;
  BTagWeight     BTagWeight_      ;
  LumiWeight     LumiWeight_      ;
  TH1F*          hPUweights_      ;
  TFile*         fMistag_         ;
  TH1D*          hMistag_         ;
  PredictedDistribution * hvv_pred; 
  Root::TGoodRunsList m_grl;

  std::map<int,TLorentzVector>	genCandidates_	;
  std::vector<LeptonCandidate>	leptonCand_		;
  std::vector<JetCandidate	>	AK4jetCand_		;
  std::vector<JetCandidate	>	AK4bjetCand_	;
  std::vector<JetCandidate	>	Vcand				;
  std::vector<JetCandidate	>	genJetCand				;
  std::vector<HiggsCandidate	>	WCand_			;
  std::vector<METCandidate	>	METCand_			;
	 
  std::vector<JetCandidate	>	Leptonicb_	;
  std::vector<JetCandidate	>	Hadronicb_	;
  std::vector<JetCandidate	>	HadronicJ_	;
  std::vector<std::vector<JetCandidate> > PrunedSubjetCand_;
  std::vector<std::vector<JetCandidate> > SoftdropSubjetCand_;
  
  int jetINDX;
  
  int            ScaleMuonUpDown_  ;

  // XML configuration //
   
  /* general settings */    
  bool           isLowMass ;     
  std::string    InputTreeName_   ;
  std::string    OutputTreeName_  ;   
  bool           isSignal_        ;
  bool           runOnMC_         ;
  bool           GenStudies_       ;
  std::string    Channel_         ; 
  std::string    MassWindow_  ; 
  bool           Trigger_         ;
  bool           applyFilters_  ;
   
  bool           UsePruned_     ;

  /* leptonic selections */
  int    foundAEle              ;
  int    foundAMu               ;
  double         leptPtCut_	   ;
  double         leptEtaCut_	   ;
  double         AleptPtCut_	   ;
  double         AleptEtaCut_	;
  double         METCut_  	   ;
   
  /* jet selections */
  double         MjjCut_	   	;
  double         dEtaCut_	   	;
  double         JetPtCutLoose_   	;
  double         JetPtCutTight_   	;
  double         JetEtaCut_	   	; 
  bool           Tau21Cut_	   		;  
  double         Tau21Low_	   		;
  double         Tau21High_	   	;
  double         Tau21HPLow_	   		;
  double         Tau21HPHigh_	   	;      

  /* pruned mass */
  bool           VetoSR_          ;
  double         mWLow_		   ;
  double         mWHigh_	   ;
  double         mZLow_		   ;
  double         mZHigh_	   ;

  double         xSec_            ;
  double         genEvents_       ;
  double         Lumi_            ;
  std::string    PUProfileData_   ;
  std::string    JSONfile_;
  std::string    BTagEff4vetoData_  ;
  std::string    BTagEff4fatjetData_;
  std::string    BTagEff4subjetData_;
   

  // END OF XML CONFIGURATION //
   
  int  channel		;
  int  category		;
  int run;
  int event;
  int lumi;
   
  float		pdgMtop;
  float		pdgMw; 
  float		pdgWidthtop;
  float		pdgWidthw;   
  float		weight_			;
  float		weight			;
  float  genweight_   ;
  float		puweight_		;
  float		hltweight_		;
  float  btagweight_  ;
  float  lumiweight_  ;
  float  btagvetow    ;
  float  htagw        ;  
  float		Mjj				;
  float  	MWW				;
  float  	MVV				;
  float  	MVVmethod2		;
  float  	Mj1				;
  float  	Mj2				;
  float 	htopmass			;
  float  	ltopmass			;
  float		ltopmassMethod2;
  float		Mj					;
  float		WMass				;
  float		WMassMethod2	;
  float		jetsDeltaEta	;
  int		nBTags			;
  
  int nSumGenWeights_;
  int    nPVs             ; 
  int    nEvents_                ;
  int    nPassedFilters_         ;  
  int    nPassedTrigger_         ;  
  int    nPassedChi2_         ;  
  
  int     nak4jets;

  int    nPassedTopMass_         ;    
  int    nPassedJetMass_         ;     
  int    nPassedJetPrunedMass_   ;
  int    nPassedTau21Cut_        ;
  int    nPassedWTag_				 ;
  
  int    nPassedFilter_HBHEIso_;
  int    nPassedFilter_HBHE_;
  int    nPassedFilter_CSCHalo_;
  int    nPassedFilter_HCALlaser_;
  int    nPassedFilter_ECALDeadCell_;
  int    nPassedFilter_GoodVtx_;
  int    nPassedFilter_TrkFailure_;
  int    nPassedFilter_EEBadSc_;
  int    nPassedFilter_ECALlaser_;
  int    nPassedFilter_TrkPOG_;
  int    nPassedFilter_TrkPOG_manystrip_;
  int    nPassedFilter_TrkPOG_toomanystrip_;
  int    nPassedFilter_TrkPOG_logError_;
  int    nPassedFilter_METFilters_;
  int    nPassedMETFiltersAll_;
  int    nPassedTrkFiltersAll_;
  int    nPassedGoodPVFilter_;
   
   
  //Dijet cut flow
  int    nPassedFoundJets_	 ;
  int    nPassedJetsDEta_		 ;
  int    nPassedMjj_			 ;
  int    nPassedWtagging_		 ;
	
  //TTbar W-tag SF cut flow
  int    nPassedFoundLept_  ;
  int    nPassedFoundMET_   ;
  int    nPassedIsoLep_     ;
  int    nPassedVetoLep_		;
  int    nPassedFoundW_			;
  int    nPassedFoundJet_   ;
  int    nPassedLepJetDR_   ;
  int    nPassed1bTag_      ;

	
  /* for tree */
  int nPV;

  float pfMET;
  float pfMETPhi;

  int nLooseEle; //number of electrons with looseID
  int nLooseMu; //number of electrons with looseID	

  //SELECTED LEPTON - the most energetic one satisfying HEEP_ID/HighPtMuon_ID :
  float l_pt; 
  float l_eta; 
  float l_phi; 
  float l_iso ;

  //FAT JET: the most energetic AK8 jet satisfying loosejetID && cleaned from the all HEEP/highPtMuon leptons in a cone dR=1.0:
  
  float jet_deta; 
  
  float jet_pt_jet1; 
  float jet_eta_jet1; 
  float jet_phi_jet1; 
  float jet_mass_jet1;
  float jet_mass_pruned_jet1;
  float jet_mass_pruned_W1;
  float jet_mass_pruned_Z1;
  float jet_mass_softdrop_jet1; 
  float jet_tau2tau1_jet1; 
  
  float jet_pt_jet2; 
  float jet_eta_jet2; 
  float jet_phi_jet2; 
  float jet_mass_jet2;
  float jet_mass_pruned_jet2;
  float jet_mass_pruned_W2;
  float jet_mass_pruned_Z2;
  float jet_mass_softdrop_jet2; 
  float jet_tau2tau1_jet2; 
  
  
  float sum_genweights; 
  float jet_rho; 

  //W boson:
  float W_pt;
  float W_eta;
  float W_phi;

  //lvj MASS:
  float m_lvj;

  int njets;  //AK4 jets
  int nbtag;  //number of AK4 jets b-tagged with iCSVM 
  

  float jet_mass_pruned ;
  float jet_pt ;
  float jet_csv ;
  float jet_eta ;
  float jet_phi ;
  float jet_tau2tau1 ;
  
  
  float Wlept_pt ;
  float Wlept_mt ;
  int   realW    ;
  

}; // class ExoDiBosonAnalysis

#endif // ExoDiBosonAnalysis_H

