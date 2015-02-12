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

   /* AK8 b-jet histos */
   theAnalysis_->Book( TH1F( "AK8bjetPT" 	    , "AK8 b-jet pt"	     ,   200,  0. , 2000.  ) );
   theAnalysis_->Book( TH1F( "AK8bjetEta"	    , "AK8 b-jet eta"	     ,    50, -2.5,    2.5 ) );
   theAnalysis_->Book( TH1F( "AK8bjetPhi"	    , "AK8 b-jet phi"	     ,    32, -3.2,    3.2 ) );
   theAnalysis_->Book( TH1F( "AK8bjetCSV"	    , "AK8 b-jet csv"	     ,    50,  0. ,    1.  ) );
   theAnalysis_->Book( TH1F( "AK8bjetMass" 	    , "AK8 b-jet mass"	     ,    80,  0. ,  200.  ) );
   theAnalysis_->Book( TH1F( "AK8bjetPrunedMass"    , "AK8 b-jet pruned mass",    40,  0. ,  200.  ) );
   theAnalysis_->Book( TH1F( "tau21"     	    , "#tau_{21}"            ,    25,  0. ,    1.  ) );
   theAnalysis_->Book( TH1F( "tau31"     	    , "#tau_{31}"            ,    25,  0. ,    1.  ) );
   theAnalysis_->Book( TH1F( "tau32"     	    , "#tau_{32}"            ,    25,  0. ,    1.  ) );

   /* lepton histos */
   theAnalysis_->Book( TH1F( "leptonPT"   	    , "lepton pt"	     ,    30,  0. ,  600.  ) );		   
   theAnalysis_->Book( TH1F( "leptonPhi"   	    , "lepton #phi"	     ,    32, -3.2,    3.2 ) );		   
   theAnalysis_->Book( TH1F( "leptonEta"  	    , "lepton eta"	     ,    20, -2.5,    2.5 ) );		   

   /* MET histos */
   theAnalysis_->Book( TH1F( "MET"	  	    , "#slash{E}_T"	     ,   100,  0. , 1000.  ) );
   theAnalysis_->Book( TH1F( "METphi"	  	    , "MET $phi"	     ,    32, -3.2,    3.2 ) );
 
   /* leptonic W histos */
   theAnalysis_->Book( TH1F( "recoWPT"    	    , "W p_{T}" 	     ,    50,  0. , 1000.  ) );
   theAnalysis_->Book( TH1F( "recoWMT"    	    , "W M_{T}" 	     ,    30,  0. ,  600.  ) );
 
   /* AK4 jets histos */
   theAnalysis_->Book( TH1F( "nAJets"    	    , "# additional jets"    ,    21, -0.5,   20.5 ) );
   theAnalysis_->Book( TH1F( "nAJetsBTag"    	    , "# additional jets"    ,    21, -0.5,   20.5 ) );
   theAnalysis_->Book( TH1F( "AK4jetPt"    	    , "AK4 leading jet p_{T}",   100,  0. , 1000.  ) );
   theAnalysis_->Book( TH1F( "AK4jetCSV"    	    , "AK4 jet CSV"          ,    50,  0. ,    1.  ) );
   theAnalysis_->Book( TH1F( "AK4jetMass"    	    , "AK4 jet mass"         ,   150,  0. ,  300.  ) );

    /* topology histos */
   theAnalysis_->Book( TH1F( "lepJetDR"   	      , "#DeltaR(l,j)"	         , 100, 0. ,   10.  ) );
   theAnalysis_->Book( TH1F( "METJetDphi" 	      , "#Delta#phi(MET,j)"      ,  64, 0. ,    3.2 ) );
   theAnalysis_->Book( TH1F( "WJetDphi"     	      , "#Delta#phi(j,W)"        ,  64, 0. ,    3.2 ) );      

   /* top histos */
   theAnalysis_->Book( TH1F( "leptonictopmass"        , "leptonic top mass"      ,  40, 0. , 1000.  ) );
   theAnalysis_->Book( TH1F( "hadronictopmass"        , "hadronic top mass"      ,  40, 0. , 1000.  ) );
 
   /* MWH */
   theAnalysis_->Book( TH1F( "DiBosonInvMass"	      , "di-bosons inv mass"     , 500, 0. , 3000.  ) );

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

   /* other histos */
   theAnalysis_->Book( TH1F( "PUWeights"            , "pu weights"           ,   100,  0. ,    5.  ) );
   theAnalysis_->Book( TH1F( "htagweight"           , "h tag weights"        ,   100,  0. ,    5.  ) );
   theAnalysis_->Book( TH1F( "btagvweight"          , "b tag veto weights"   ,   100,  0. ,    5.  ) );
   theAnalysis_->Book( TH1F( "nVertices"            , "number of PVs"        ,    40,  0. ,   40.  ) );
  
}

////////////////////////////////////////////////////////////////////
void HistosManager::formatHistos( void ){

   /* AK8 b-jet histos */
   theAnalysis_->Hist( "AK8bjetPT"  	       )->GetXaxis()->SetTitle( "p_{T}^{AK8} [GeV]"		    );
   theAnalysis_->Hist( "AK8bjetEta" 	       )->GetXaxis()->SetTitle( "#eta^{AK8}"			    );
   theAnalysis_->Hist( "AK8bjetPhi"  	       )->GetXaxis()->SetTitle( "#phi^{AK8} [GeV]"		    );
   theAnalysis_->Hist( "AK8bjetCSV" 	       )->GetXaxis()->SetTitle( "CSV^{AK8}"			    );
   theAnalysis_->Hist( "AK8bjetMass"           )->GetXaxis()->SetTitle( "jet mass [GeV]"		    );
   theAnalysis_->Hist( "AK8bjetPrunedMass"     )->GetXaxis()->SetTitle( "m_{jet}^{pruned} [GeV]"	    );
   theAnalysis_->Hist( "tau21"  	       )->GetXaxis()->SetTitle( "#tau_{21}"			    );
   theAnalysis_->Hist( "tau31"  	       )->GetXaxis()->SetTitle( "#tau_{31}"			    );
   theAnalysis_->Hist( "tau32"  	       )->GetXaxis()->SetTitle( "#tau_{32}"			    );

   /* lepton histos */            
   theAnalysis_->Hist( "leptonPT"   	       )->GetXaxis()->SetTitle( "lepton p_{T} [GeV]"		    );
   theAnalysis_->Hist( "leptonPhi"   	       )->GetXaxis()->SetTitle( "lepton #phi [rad]"		    );
   theAnalysis_->Hist( "leptonEta"  	       )->GetXaxis()->SetTitle( "lepton #eta"			    );

   /* MET histos */   
   theAnalysis_->Hist( "MET"	    	       )->GetXaxis()->SetTitle( "E_{T}^{miss} [GeV]"		    );
   theAnalysis_->Hist( "METphi"                )->GetXaxis()->SetTitle( "E_{T}^{miss} #phi [rad]"	    );

   /* leptonic W histos */
   theAnalysis_->Hist( "recoWPT"    	       )->GetXaxis()->SetTitle( "p_{T}(W) [GeV]"		    );
   theAnalysis_->Hist( "recoWMT"    	       )->GetXaxis()->SetTitle( "M_{T}(W) [GeV]"		    ); 

   /* AK4 jets histos */ 
   theAnalysis_->Hist( "nAJets"    	           )->GetXaxis()->SetTitle( "number of extra jets"	    );
   theAnalysis_->Hist( "nAJetsBTag"    	       )->GetXaxis()->SetTitle( "number of b-tagged extra jets"	    );
   theAnalysis_->Hist( "AK4jetPt"    	       )->GetXaxis()->SetTitle( "p_{T}^{AK4} [GeV]"		    );
   theAnalysis_->Hist( "AK4jetCSV"    	       )->GetXaxis()->SetTitle( "CSV^{AK4} [GeV]"		    );
   theAnalysis_->Hist( "AK4jetMass"    	       )->GetXaxis()->SetTitle( "mass^{AK4} [GeV]"		    );

    /* topology histos */   
   theAnalysis_->Hist( "lepJetDR"   	       )->GetXaxis()->SetTitle( "#DeltaR(l,j)"  		    );
   theAnalysis_->Hist( "METJetDphi" 	       )->GetXaxis()->SetTitle( "#Delta#phi(j,#slash{E}_{T}) [rad]" );
   theAnalysis_->Hist( "WJetDphi"   	       )->GetXaxis()->SetTitle( "#Delta#phi(j,W) [rad]" 	    );

   /* top histos */
   theAnalysis_->Hist( "leptonictopmass"     )->GetXaxis()->SetTitle( "leptonic top mass [GeV]"	    	    );
   theAnalysis_->Hist( "hadronictopmass"     )->GetXaxis()->SetTitle( "hadronic top mass [GeV]"	    	    );
         
   /* MWH */         
   theAnalysis_->Hist( "DiBosonInvMass"        )->GetXaxis()->SetTitle( "M_{WH} [GeV]"           	    );

   /* other histos */
   theAnalysis_->Hist( "PUWeights"            )->GetXaxis()->SetTitle( "PU weights"			    );
   theAnalysis_->Hist( "htagweight"           )->GetXaxis()->SetTitle( "h-tag weights"			    );
   theAnalysis_->Hist( "btagvweight"          )->GetXaxis()->SetTitle( "b-tag veto weights"		    );
   theAnalysis_->Hist( "nVertices"            )->GetXaxis()->SetTitle( "# primary vertices"                 );

   
   Utilities::OverflowToLast( theAnalysis_->Hist( "AK8bjetPT"  	      ) );
   Utilities::OverflowToLast( theAnalysis_->Hist( "AK8bjetEta" 	      ) );
   Utilities::OverflowToLast( theAnalysis_->Hist( "AK8bjetPhi" 	      ) );
   Utilities::OverflowToLast( theAnalysis_->Hist( "AK8bjetCSV" 	      ) );
   Utilities::OverflowToLast( theAnalysis_->Hist( "AK8bjetMass"       ) );
   Utilities::OverflowToLast( theAnalysis_->Hist( "AK8bjetPrunedMass" ) );
   Utilities::OverflowToLast( theAnalysis_->Hist( "tau21"	      ) );
   Utilities::OverflowToLast( theAnalysis_->Hist( "tau31"	      ) );
   Utilities::OverflowToLast( theAnalysis_->Hist( "tau32"	      ) );

   Utilities::OverflowToLast( theAnalysis_->Hist( "leptonPT"          ) );
   Utilities::OverflowToLast( theAnalysis_->Hist( "leptonPhi"         ) );
   Utilities::OverflowToLast( theAnalysis_->Hist( "leptonEta"         ) );
   
   Utilities::OverflowToLast( theAnalysis_->Hist( "MET" 	      ) );
   Utilities::OverflowToLast( theAnalysis_->Hist( "METphi"            ) );

   Utilities::OverflowToLast( theAnalysis_->Hist( "recoWPT"	      ) );
   Utilities::OverflowToLast( theAnalysis_->Hist( "recoWMT"	      ) );

   Utilities::OverflowToLast( theAnalysis_->Hist( "nAJets"    	      ) );
   Utilities::OverflowToLast( theAnalysis_->Hist( "nAJetsBTag"        ) );
   Utilities::OverflowToLast( theAnalysis_->Hist( "AK4jetPt"          ) );
   Utilities::OverflowToLast( theAnalysis_->Hist( "AK4jetCSV"         ) );
   Utilities::OverflowToLast( theAnalysis_->Hist( "AK4jetMass"        ) );

   Utilities::OverflowToLast( theAnalysis_->Hist( "lepJetDR"	      ) );
   Utilities::OverflowToLast( theAnalysis_->Hist( "METJetDphi"        ) );
   Utilities::OverflowToLast( theAnalysis_->Hist( "WJetDphi"	      ) );

   Utilities::OverflowToLast( theAnalysis_->Hist( "leptonictopmass"   ) );
   Utilities::OverflowToLast( theAnalysis_->Hist( "hadronictopmass"   ) );
   
   Utilities::OverflowToLast( theAnalysis_->Hist( "DiBosonInvMass"    ) );
   
   Utilities::OverflowToLast( theAnalysis_->Hist( "PUWeights"         ) );
   Utilities::OverflowToLast( theAnalysis_->Hist( "nVertices"         ) );
   Utilities::OverflowToLast( theAnalysis_->Hist( "htagweight"        ) );
   Utilities::OverflowToLast( theAnalysis_->Hist( "btagvweight"       ) );
      
}
