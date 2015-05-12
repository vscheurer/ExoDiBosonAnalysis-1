#include "include/LumiWeight.h"

#include <iostream>

//==============================================================================================
LumiWeight::LumiWeight( void ){

}

//==============================================================================================
LumiWeight::~LumiWeight( void ){

}

//==============================================================================================
double LumiWeight::getLumiWeight( TString sample ){

   xSec_ = 1.;
   genEvents_ = 1.;
              
   if( sample.Contains( "_TToLeptons_t-channel_" ) ){
      xSec_ = 136.05;
      genEvents_ = 3991000.;
   }
   else if( sample.Contains( "_TToLeptons_s-channel_" ) ){
      xSec_ = 7.2;
      genEvents_ = 500000.;   
   }
   else if( sample.Contains( "_T_tW-channel_" ) ){
      xSec_ = 35.6;
      genEvents_ = 986100.;   
   }
   else if( sample.Contains( "_TBarToLeptons_t-channel_" ) ){
      xSec_ = 80.97;
      genEvents_ = 1999800.;   
   }
   else if( sample.Contains( "_TBarToLeptons_s-channel_" ) ){
      xSec_ = 4.16;
      genEvents_ = 250000.;   
   } 
   else if( sample.Contains( "_Tbar_tW-channel_" ) ){
      xSec_ = 35.6;
      genEvents_ = 971800.;   
   }
   else if( sample.Contains( "_WJetsToLNu_HT-100to200_" ) ){
      xSec_ = 1817.;
      genEvents_ = 5262265.;   
   }
   else if( sample.Contains( "_WJetsToLNu_HT-200to400_" ) ){
      xSec_ = 471.6;
      genEvents_ = 4936077.;   
   }
   else if( sample.Contains( "_WJetsToLNu_HT-400to600_" ) ){
      xSec_ = 55.61;
      genEvents_ = 4640594.;   
   }
   else if( sample.Contains( "_WJetsToLNu_HT-600toInf_" ) ){
      xSec_ = 18.81;
      genEvents_ = 4581841.;   
   }
   else if( sample.Contains( "_TTJets_" ) ){
      xSec_ = 831.76;
      genEvents_ = 25446993.;   
   }
   else if( sample.Contains( "_RSGravitonToWW_M_1000_" ) ){
      // xSec_ = 2.37;
      xSec_ = 1.;
      genEvents_ = 27614.;   
   }
   else if( sample.Contains( "_RSGravitonToWW_M_2000_" ) ){
      // xSec_ = 0.04797;
      xSec_ = 1.;
      genEvents_ = 39068.;   
   }
   else if( sample.Contains( "_RSGravitonToWW_M_3000_" ) ){
      // xSec_ = 0.00292;
      xSec_ = 1.0;
      genEvents_ = 28983.;   
   }
   else if( sample.Contains( "_RSGravitonToWW_M_4000_" ) ){
      // xSec_ = 0.0002739;
      xSec_ = 1.;
      genEvents_ = 28687.;   
   }
   else if( sample.Contains( "_QCD_HT_250To500_ext_" ) ){
      xSec_ = 670500.;
      genEvents_ = 2004219.;  
   }
   else if( sample.Contains( "_QCD_HT_250To500_" ) ){
      xSec_ = 670500.;
      genEvents_ = 663953.;   
   }
   else if( sample.Contains( "_QCD_HT_500To1000_ext_" ) ){
      xSec_ = 26740.;
      genEvents_  = 3214312.;   
   }
   else if( sample.Contains( "_QCD_HT_500To1000_" ) ){
       xSec_ = 26740.;
      genEvents_ = 849033.;   
   }
   else if( sample.Contains( "_QCD_HT_1000ToInf_ext_" ) ){
      xSec_ = 769.7;
      genEvents_ = 1130720.;   
   }
   else if( sample.Contains( "_QCD_HT_1000ToInf_" ) ){
      xSec_ = 769.7;
      genEvents_ = 333733.;   
   }
	                                     
   return xSec_/genEvents_;
      
}
