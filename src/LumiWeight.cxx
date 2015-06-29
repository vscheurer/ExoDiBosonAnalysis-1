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
   
   if( sample.Contains( "ST_t-channel_top" ) ){ //ok
      xSec_ = 216.99; //amc@NLO
      genEvents_ = 2966200.;
   }
   else if( sample.Contains( "ST_s-channel_top" ) ){ //ok
      xSec_ = 10.11;  //amc@NLO
      genEvents_ = 984400.;
   }
   else if( sample.Contains( "ST_tW-channel_top" ) ){ //ok
      xSec_ = 38.09;  //powheg
      genEvents_ = 995600.;
   }
   else if( sample.Contains( "ST_t-channel_antitop" ) ){ //ok
      xSec_ = 80.95; //powheg
      genEvents_ = 1695400.;
   }
   //else if( sample.Contains( "ST_s-channel_antitop" ) ){
   //   xSec_ = 136.05;
   //   genEvents_ = 3991000.;
   //}         
   else if( sample.Contains( "ST_tW-channel_antitop" ) ){ //ok
      xSec_ = 38.09; //powheg
      genEvents_ = 1000000.;
   }   
   else if( sample.Contains( "TTJets" ) ){ //ok
      xSec_ = 831.76;
      genEvents_ = 42730273.;
   }
   else if( sample.Contains( "_WW_" ) ){ //ok
      xSec_ = 63.21;
      genEvents_ = 994416.;
   }
   else if( sample.Contains( "_WZ_" ) ){ //ok
      xSec_ = 22.82;
      genEvents_ = 991232.;
   }
   else if( sample.Contains( "_ZZ_" ) ){ //ok
      xSec_ = 10.32;
      genEvents_ = 996168.;
   }      
   else if( sample.Contains( "WJetsToLNu_HT-100To200" ) ){ //ok
      xSec_ = 1292.;
      genEvents_ = 10142187.;
   } 
   else if( sample.Contains( "WJetsToLNu_HT-200To400" ) ){ //ok
      xSec_ = 385.9;
      genEvents_ = 5231856.;
   } 
   else if( sample.Contains( "WJetsToLNu_HT-400To600" ) ){ //ok
      xSec_ = 47.9;
      genEvents_ = 1901705.;
   } 
   else if( sample.Contains( "WJetsToLNu_HT-600ToInf" ) ){ //ok
      xSec_ = 19.9;
      genEvents_ = 1036108.;
   }          
      //
   //
   // if( sample.Contains( "_TToLeptons_t_" ) ){
   //    xSec_ = 136.05;
   //    genEvents_ = 3991000.;
   // }
   // else if( sample.Contains( "_TToLeptons_s_" ) ){
   //    xSec_ = 7.2;
   //    genEvents_ = 500000.;
   // }
   // else if( sample.Contains( "_T_tW_" ) ){
   //    xSec_ = 35.6;
   //    genEvents_ = 986100.;
   // }
   // else if( sample.Contains( "_TBarToLeptons_t_" ) ){
   //    xSec_ = 80.97;
   //    genEvents_ = 1999800.;
   // }
   // else if( sample.Contains( "_TBarToLeptons_s_" ) ){
   //    xSec_ = 4.16;
   //    genEvents_ = 250000.;
   // }
   // else if( sample.Contains( "_Tbar_tW_" ) ){
   //    xSec_ = 35.6;
   //    genEvents_ = 971800.;
   // }
   // else if( sample.Contains( "_WJetsToLNu_HT_100to200_" ) ){
   //    xSec_ = 1817.;
   //    genEvents_ = 5262265.;
   // }
   // else if( sample.Contains( "_WJetsToLNu_HT_200to400_" ) ){
   //    xSec_ = 471.6;
   //    genEvents_ = 4936077.;
   // }
   // else if( sample.Contains( "_WJetsToLNu_HT_400to600_" ) ){
   //    xSec_ = 55.61;
   //    genEvents_ = 4640594.;
   // }
   // else if( sample.Contains( "_WJetsToLNu_HT_600toInf_" ) ){
   //    xSec_ = 18.81;
   //    genEvents_ = 4581841.;
   // }
   // else if( sample.Contains( "_TTJets_" ) ){
   //    xSec_ = 831.76;
   //    genEvents_ = 25446993.;
   // }

   else if( sample.Contains( "_RSGravitonToWW_M_600_" ) ){
      // xSec_ = 2.37;
      xSec_ = 1.;
      // genEvents_ = 27614.; //PHYS14
      genEvents_ = 30000.;    //SPRING15
   }
   else if( sample.Contains( "_RSGravitonToWW_M_800_" ) ){
      // xSec_ = 2.37;
      xSec_ = 1.;
      // genEvents_ = 27614.; //PHYS14
      genEvents_ = 30000.;    //SPRING15
   }
   else if( sample.Contains( "_RSGravitonToWW_M_1000_" ) ){
      // xSec_ = 2.37;
      xSec_ = 1.;
      // genEvents_ = 27614.; //PHYS14
      genEvents_ = 29751.;    //SPRING15
   }
   else if( sample.Contains( "_RSGravitonToWW_M_1200_" ) ){
      // xSec_ = 2.37;
      xSec_ = 1.;
      // genEvents_ = 27614.; //PHYS14
      genEvents_ = 29176.;    //SPRING15
   }
   else if( sample.Contains( "_RSGravitonToWW_M_1400_" ) ){
      // xSec_ = 2.37;
      xSec_ = 1.;
      // genEvents_ = 27614.; //PHYS14
      genEvents_ = 30000.;    //SPRING15
   }
   else if( sample.Contains( "_RSGravitonToWW_M_1600_" ) ){
      // xSec_ = 2.37;
      xSec_ = 1.;
      // genEvents_ = 27614.; //PHYS14
      genEvents_ = 29028.;    //SPRING15
   }
   else if( sample.Contains( "_RSGravitonToWW_M_1800_" ) ){
      // xSec_ = 2.37;
      xSec_ = 1.;
      // genEvents_ = 27614.; //PHYS14
      genEvents_ = 98980.;    //SPRING15
   }
   else if( sample.Contains( "_RSGravitonToWW_M_2000_" ) ){
      // xSec_ = 0.04797;
      xSec_ = 1.;
      // genEvents_ = 39068.;
      genEvents_ = 29680.;    //SPRING15
   }
   else if( sample.Contains( "_RSGravitonToWW_M_3000_" ) ){
      // xSec_ = 0.00292;
      xSec_ = 1.0;
      // genEvents_ = 28983.;
      genEvents_ = 30000.;    //SPRING15
   }
   else if( sample.Contains( "_RSGravitonToWW_M_4000_" ) ){
      // xSec_ = 0.0002739;
      xSec_ = 1.;
      // genEvents_ = 28687.;
      genEvents_ = 30000.;    //SPRING15
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
   else if( sample.Contains( "_DYJetsToLL_" ) ){
      xSec_ = 4746.;
      genEvents_ = 2829164.;   
   }
   
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   else if( sample.Contains( "QCD_PT_170to300_" ) ){
      xSec_ = 117276.;
      genEvents_ = 3364368.;   
   }
   else if( sample.Contains( "QCD_PT_300to470_" ) ){
      xSec_ = 7823.;
      genEvents_ = 2933611.;   
   }
   else if( sample.Contains( "QCD_PT_470to600_" ) ){
      xSec_ = 648.2;
      genEvents_ = 1936832.;   
   }
   else if( sample.Contains( "QCD_PT_600to800_" ) ){
      xSec_ = 186.9;
      genEvents_ = 1878856.;   
   }
   else if( sample.Contains( "QCD_PT_800to1000_" ) ){
      xSec_ = 32.293;
      genEvents_ = 1937216.;   
   }
   else if( sample.Contains( "QCD_PT_1000to1400_" ) ){
      xSec_ = 9.4183;
      genEvents_ = 1487136.;   
   }  
   else if( sample.Contains( "QCD_PT_1400to1800_" ) ){
      xSec_ = 0.84265;
      genEvents_ = 197959.;   
   }
   else if( sample.Contains( "QCD_PT_1800to2400_" ) ){
      xSec_ = 0.114943;
      genEvents_ = 193608.;   
   }
   else if( sample.Contains( "QCD_PT_2400to3200_" ) ){
      xSec_ = 0.00682981;
      genEvents_ = 194456.;   
   }
   else if( sample.Contains( "QCD_PT_3200toInf_" ) ){
      xSec_ = 0.000165445;
      genEvents_ = 192944.;   
   }
   
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   else if( sample.Contains( "BulkGravToWW_M_600" ) ){
      xSec_ = 1.;
      genEvents_ = 30000.;   
   }
   else if( sample.Contains( "BulkGravToWW_M_800" ) ){
      xSec_ = 1.;
      genEvents_ = 30000.;   
   }
   else if( sample.Contains( "BulkGravToWW_M_1000" ) ){
      xSec_ = 1.;
      genEvents_ = 30000.;   
   }
   else if( sample.Contains( "BulkGravToWW_M_1200" ) ){
      xSec_ = 1.;
      genEvents_ = 30000.;   
   }
   else if( sample.Contains( "BulkGravToWW_M_1400" ) ){
      xSec_ = 1.;
      genEvents_ = 30000.;   
   }
   else if( sample.Contains( "BulkGravToWW_M_1600" ) ){
      xSec_ = 1.;
      genEvents_ = 29000.;   
   }
   else if( sample.Contains( "BulkGravToWW_M_1800" ) ){
      xSec_ = 1.;
      genEvents_ = 30000.;   
   }
   else if( sample.Contains( "BulkGravToWW_M_2000" ) ){
      xSec_ = 1.;
      genEvents_ = 30000.;   
   }
   else if( sample.Contains( "BulkGravToWW_M_2500" ) ){
      xSec_ = 1.;
      genEvents_ = 30000.;   
   }
   else if( sample.Contains( "BulkGravToWW_M_3000" ) ){
      xSec_ = 1.;
      genEvents_ = 30000.;   
   }
   else if( sample.Contains( "BulkGravToWW_M_3500" ) ){
      xSec_ = 1.;
      genEvents_ = 30000.;   
   }
   else if( sample.Contains( "BulkGravToWW_M_4000" ) ){
      xSec_ = 1.;
      genEvents_ = 30000.;
   }
   // else if( sample.Contains( "BulkGravToWW_M_4500" ) ){
   //    xSec_ = 1.;
   //    genEvents_ = .;
   // }
   
   
   //
   // std::cout<<"sample == "<<sample<<std::endl;
   // std::cout<<"xSec_ == "<<xSec_<<std::endl;
   // std::cout<<"genevents == "<<genEvents_<<std::endl;
   	                                     
   return xSec_/genEvents_;
      
}
