#ifndef ExoDiBosonAnalysis_H
#define ExoDiBosonAnalysis_H

#include "core/include/SCycleBase.h"

#include "TLorentzVector.h"
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
  bool selectChannel             ( void );
   
  void setWeight                 ( TString infile );
  void initWeight                ( void );
   
  void initData                  ( void );
  void reset                     ( void );
  InputData& getData             ( void ){ return data_; }
  void setNtupleManager          ( NtupleManager* ntupleManager ){ theNtupleManager_ = ntupleManager; }
  void printCutFlow              ( void );

  void fillHistos                ( void );
  void fillSFHistos              ( void );

  double getMuonScale            ( double oldpt );
  double getPrunedMassScale      ( double prunedmass );
              
  bool passedSelections          ( void );
  bool passedTTbarSelections     ( void );
  bool passedDijetSelections 	 ( void );
  bool passedTrigger             ( void );
	
  bool findLeptonCandidate       ( void );     
  bool findMuonCandidate         ( void ); 
  bool findElectronCandidate     ( void ); 
  bool findMETCandidate          ( void );
  bool findWCandidate            ( void );
  bool findHadronicWCandidate    ( void );
  bool findJetCandidate          ( void );
  void findExtraJets             ( void );
  void findTopCandidate          ( void );
  void findExoCandidate          ( void );   
  TLorentzVector getp4Nu         ( void );
  TLorentzVector getp4NuMethod2  ( void );


  bool findJetCandidates         ( void );

  void doLeptonRecoEfficiency    ( void );
  bool run4Synch                 ( void );
  void doJetRecoEfficiency    	 ( void );
     
private:
  ClassDef( ExoDiBosonAnalysis, 0 );  
       
  HistosManager* theHistosManager_;
  NtupleManager* theNtupleManager_;
  InputData      data_            ;
  PUWeight       PUWeight_        ;
  LHEWeight      LHEWeight_       ;
  HLTWeight      HLTWeight_       ;
  BTagWeight     BTagWeight_      ;
  LumiWeight     LumiWeight_      ;

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

  // XML configuration //
   
  /* general settings */         
  std::string    InputTreeName_   ;
  std::string    OutputTreeName_  ;   
  bool           isSignal_        ;
  bool           runOnMC_         ;
  bool           genFilter_       ;
  std::string    Flavour_         ; 
  std::string    Channel_         ; 
  bool           Trigger_         ;
  bool           Synch_           ;
	
  bool           UsePruned_     ;
  bool           UseSD_         ;

  /* leptonic selections */
  double         leptPtCut_	   ;
  double         leptEtaCut_	   ;
  double         AleptPtCut_	   ;
  double         AleptEtaCut_	;
  double         METCut_  	   ;
  double         WptCut_  	   ;
   
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
  /* btag veto */
  int            nAJetCut_	   ; // if it's -1 the cut is not applied
  std::string    BtagVetoWP_      ;

  /* top mass veto */
  bool           TopMassCut_      ;
  double         leptTopMassLow_  ;
  double         leptTopMassHigh_ ;
  double         hadrTopMassLow_  ;
  double         hadrTopMassHigh_ ;
   
  /* pruned mass */
  bool           VetoSR_          ;
  double         mPMLow_		   ;
  double         mPMHigh_	   ;
  double         mSDLow_		   ;
  double         mSDHigh_	   ; 
  /* WH mass window */
  double         WHMass_          ; // if it's -1 no window is applied otherwise put the mass of the resonance and the 15% window is automatically taken into account
      
  /* weights settings */            
  std::string    LHEsample_       ;
  double         xSec_            ;
  double         genEvents_       ;
  double         Lumi_            ;
  std::string    PUProfileData_   ;
  std::string    BTagEff4vetoData_  ;
  std::string    BTagEff4fatjetData_;
  std::string    BTagEff4subjetData_;
   
  /* systematics */
  bool           BtagSFSysUpVeto_  ;
  bool           BtagSFSysDownVeto_;
  int            ScaleMuonUpDown_  ;
  int            ScalePrunedMass_  ;

  // END OF XML CONFIGURATION //
   
  std::map<std::string,double>	bTagWPmap_	;
  int            					jetIndex_	;
  int            					channel		;
   
  float		pdgMtop;
  float		pdgMw; 
  float		pdgWidthtop;
  float		pdgWidthw;   
  float		weight_			;
  float		lheweight_		;
  float		puweight_		;
  float		hltweight_		;
  float		btagweight_		;
  float		lumiweight_		;
  float		btagvetow		; 
  float		htagw				;   
  float		Mjj				;
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
   
  int    nEvents_                ;
  int    nPassedTrigger_         ;  
  int    nPassedFoundLept_       ;
  int    nPassedFoundMET_        ;
  int    nPassedFoundW_          ;
  int    nPassedFoundJet_        ;
  int    nPassedLepJetDR_        ;
  int    nPassedJetPtTight_      ;
  int    nPassedAJetCut_         ;
  int    nPassedLepJetDR2_       ;
  int    nPassedMETJetDPhi_      ;
  int    nPassedJetWDPhi_        ;
  int    nPassedTopMass_         ;    
  int    nPassedJetMass_         ;     
  int    nPassedJetPrunedMass_   ;
  int    nPassedTau21Cut_        ;
  int    nPassedExoCandidateMass_;
  int    nPassedWTag_				 ;
   
   
  //Dijet cut flow
  int    nPassedFoundJets_	 ;
  int    nPassedJetsDEta_		 ;
  int    nPassedMjj_			 ;
  int    nPassedWtagging_		 ;
	
  //TTbar SF cut flow
  int    nPassedIsoLep_		;
  int    nPassedVetoLep_		;
  int    nPassed1Jet_			;
  int    nPassed2Jet_			;
  int    nPassed3Jet_			;
  int    nPassed4Jet_			;
  int    nPassed1bTag_			;
  int    nPassed2bTag_			;
	
  /* for synch */
  int run;
  int event;
  int lumi;
  int nPV;

  float pfMET;
  float pfMETPhi;

  int nLooseEle; //number of electrons with looseID
  int nLooseMu; //number of electrons with looseID	

  //SELECTED LEPTON - the most energetic one satisfying HEEP_ID/HighPtMuon_ID :
  float l_pt; 
  float l_eta; 
  float l_phi; 

  //FAT JET: the most energetic AK8 jet satisfying loosejetID && cleaned from the all HEEP/highPtMuon leptons in a cone dR=1.0:
  float jet_pt; 
  float jet_eta; 
  float jet_phi; 
  float jet_mass_pruned;
  float jet_mass_softdrop; 
  float jet_tau2tau1; 

  //W boson:
  float W_pt;
  float W_eta;
  float W_phi;

  //lvj MASS:
  float m_lvj;

  //AK4 JETS collection: - cleaned from the all HEEP/highPtMuon leptons && dR>=1.0 from the fat jet && isLooseJetId
  int njets;  //AK4 jets
  int nbtag;  //number of AK4 jets b-tagged with iCSVM
  float jet2_pt;  //1st most energetic AK4 
  float jet2_btag;  //1st most energetic AK4 
  float jet3_pt;  //2nd most energetic AK4 
  float jet3_btag;  //2nd most energetic AK4 

}; // class ExoDiBosonAnalysis

#endif // ExoDiBosonAnalysis_H

