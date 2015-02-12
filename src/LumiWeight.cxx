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
      genEvents_ = 3990985.;
   }
   else if( sample.Contains( "_TToLeptons_s-channel_" ) ){
      xSec_ = 7.2;
      genEvents_ = 499999.;   
   }
   else if( sample.Contains( "_T_tW-channel_" ) ){
      xSec_ = 35.6;
      genEvents_ = 986096.;   
   }
   else if( sample.Contains( "_TBarToLeptons_t-channel_" ) ){
      xSec_ = 80.97;
      genEvents_ = 1999793.;   
   }
   else if( sample.Contains( "_TBarToLeptons_s-channel_" ) ){
      xSec_ = 4.16;
      genEvents_ = 250000.;   
   } 
   else if( sample.Contains( "_Tbar_tW-channel_" ) ){
      xSec_ = 35.6;
      genEvents_ = 971797.;   
   }
   else if( sample.Contains( "_WJetsToLNu_HT-100to200_" ) ){
      xSec_ = 1817.;
      genEvents_ = 2350691.;   
   }
   else if( sample.Contains( "_WJetsToLNu_HT-200to400_" ) ){
      xSec_ = 471.6;
      genEvents_ = 2181725.;   
   }
   else if( sample.Contains( "_WJetsToLNu_HT-400to600_" ) ){
      xSec_ = 55.61;
      genEvents_ = 2413944.;   
   }
   else if( sample.Contains( "_WJetsToLNu_HT-600toInf_" ) ){
      xSec_ = 18.81;
      genEvents_ = 4581825.;   
   }
   else if( sample.Contains( "_TTJets_" ) ){
      xSec_ = 831.76;
      genEvents_ = 25446880.;   
   }
   else if( sample.Contains( "_RSGravitonToWW_M_1000_" ) ){
      //xSec_ = 2.37;
      xSec_ = 0.01;
      genEvents_ = 27614.;   
   }
   else if( sample.Contains( "_RSGravitonToWW_M_2000_" ) ){
      //xSec_ = 0.04797;
      xSec_ = 0.01;
      genEvents_ = 39068.;   
   }
   else if( sample.Contains( "_RSGravitonToWW_M_3000_" ) ){
      //xSec_ = 0.00292;
      xSec_ = 0.01;
      genEvents_ = 28983.;   
   }
   else if( sample.Contains( "_RSGravitonToWW_M_4000_" ) ){
      //xSec_ = 0.0002739;
      xSec_ = 0.01;
      genEvents_ = 28687.;   
   }
                                         
   return xSec_/genEvents_;
      
}
