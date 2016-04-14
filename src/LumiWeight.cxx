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
  
  if( sample.Contains( "Fall15" ) ){
    //single top samples
    if( sample.Contains( "ST_t-channel_top" ) ){ //DONE
      xSec_ = 136.02*0.3272;
      genEvents_ = 3299200.;
    }  
    else if( sample.Contains( "ST_t-channel_antitop" ) ){ //DONE
      xSec_ = 80.95*0.3272;
      genEvents_ = 1630900.;
    }         

    else if( sample.Contains( "ST_s-channel" ) ){ //DONE
      xSec_ = 11.36*0.3272;
      //genEvents_ = 984400.; //das
      genEvents_ = 621946.; //genweights 
    }	  
    else if( sample.Contains( "ST_tW_top" ) ){ //DONE
      xSec_ = 35.6;
      genEvents_ = 1000000.;
    } 
    else if( sample.Contains( "ST_tW_antitop" ) ){ //DONE
      xSec_ = 35.6;
      genEvents_ = 999400.;
    }   
    else if( sample.Contains( "TT" ) && sample.Contains("herwig") ){ //TO DO
      xSec_ = 831.76;
      genEvents_ = 19409316;  //DAS 17520956.
    }

    else if( sample.Contains( "TT" ) && sample.Contains("pythia8")){ //DONE
      xSec_ = 831.76;
      genEvents_ = 97994456.;
    }

    else if( sample.Contains( "WWToLNuQQ") ){ //DONE
      xSec_ = 49.997;
      genEvents_ = 6996000.;
    }
    else if( sample.Contains( "WZTo1L1Nu2Q" ) ){  //DONE
      xSec_ = 10.71;
      //genEvents_ = 978512.;//das
      genEvents_ = 11466086.; //gen weights
    }   
    else if( sample.Contains( "ZZTo2L2Q" ) ){  //DONE
      xSec_ = 3.22;
      //genEvents_ = 18790122.;//das
      genEvents_ = 9660541.;//gen weights
    } 
    
    else if( sample.Contains( "WJetsToLNu_HT-100To200" ) ){ //DONE
      xSec_ = 1.21*1345.;//1292.;
      genEvents_ = 10205377.;
    } 
    else if( sample.Contains( "WJetsToLNu_HT-200To400" ) ){ //DONE
      xSec_ = 1.21*359.7;//385.9;
      genEvents_ = 4949568.;
    } 
    else if( sample.Contains( "WJetsToLNu_HT-400To600" ) ){ //DONE
      xSec_ = 1.21*48.91;//47.9;
      genEvents_ = 1722920.;
    } 
    else if( sample.Contains( "WJetsToLNu_HT-600To800" ) ){ //DONE
      xSec_ = 1.21*12.05;//47.9;
      genEvents_ = 3767766.;
    } 
    else if( sample.Contains( "WJetsToLNu_HT-800To1200" ) ){ //DONE
      xSec_ = 1.21*5.501;//47.9;
      genEvents_ = 1568277.;
    } 
    else if( sample.Contains( "WJetsToLNu_HT-1200To2500" ) ){ //DONE
      xSec_ = 1.21*1.329;//47.9;
      genEvents_ = 246239.;
    } 
    else if( sample.Contains( "WJetsToLNu_HT-2500ToInf" ) ){ //DONE
      xSec_ = 1.21*0.03216;//47.9;
      genEvents_ = 251982.;
    } 
  }
  else{
    if( sample.Contains( "ST_t-channel_top" ) ){
    xSec_ = 136.02*0.3272;
    genEvents_ = 3299800.;
  }  
  if( sample.Contains( "ST_t-channel_antitop" ) ){
    xSec_ = 80.95*0.3272;
    genEvents_ = 1680200.;
  }         
  if( sample.Contains( "ST_t-channel" ) && sample.Contains( "ext" ) ){
    xSec_ = 216.99*0.322;
    //genEvents_ = 29954054.; //das
    genEvents_ =  6456052.; //gen weights
  }  
  else if( sample.Contains( "ST_s-channel" ) ){
    xSec_ = 11.36*0.3272;
    //genEvents_ = 984400.; //das
    genEvents_ = 613384.; //genweights
  }	  
  else if( sample.Contains( "ST_tW_top" ) ){
    xSec_ = 35.6;
    genEvents_ = 995600.;
  } 
  else if( sample.Contains( "ST_tW_antitop" ) ){
    xSec_ = 35.6;
    genEvents_ = 988500.;
  }   
  else if( sample.Contains( "TT" ) && sample.Contains("herwig") ){
    xSec_ = 831.76;
    genEvents_ = 16640209;  //DAS 17520956.
  }
  else if( sample.Contains( "TT" ) && sample.Contains("pythia8") && !sample.Contains("Fall15")){
    xSec_ = 831.76;
    genEvents_ = 19757192.; //LOWMASS 17427174
  }
  else if( sample.Contains( "_WW_" ) && !sample.Contains( "powheg" ) ){
    xSec_ = 118.7;
    genEvents_ = 993640.;
  }
  else if( sample.Contains( "_WW" ) && sample.Contains( "powheg" ) ){
    xSec_ = 49.997;
    genEvents_ = 1951600.;
  }
  else if( sample.Contains( "_WZ_" ) && !sample.Contains( "amcatnlo" ) ){
    xSec_ = 47.13;
    genEvents_ = 978512.;
  }
  else if( sample.Contains( "_WZ" ) && sample.Contains( "amcatnlo" ) ){
    xSec_ = 10.71;
    //genEvents_ = 978512.;//das
    genEvents_ = 14346866; //gen weights
  }
  else if( sample.Contains( "_ZZ_" ) && !sample.Contains( "amcatnlo" ) ){
    xSec_ = 16.5;
    genEvents_ = 996944.;
  }      
  else if( sample.Contains( "_ZZ" ) && sample.Contains( "amcatnlo" ) ){
    xSec_ = 3.22;
    //genEvents_ = 18790122.;//das
    genEvents_ = 11863244.;//gen weights
  } 
  else if( sample.Contains( "WJetsToLNu_HT-100To200" ) ){
    xSec_ = 1.21*1345.;//1292.;
    genEvents_ = 10152718.;
  } 
  else if( sample.Contains( "WJetsToLNu_HT-200To400" ) ){
    xSec_ = 1.21*359.7;//385.9;
    genEvents_ = 5221599.;
  } 
  else if( sample.Contains( "WJetsToLNu_HT-400To600" ) ){
    xSec_ = 1.21*48.91;//47.9;
    genEvents_ = 1745914.;
  } 
  else if( sample.Contains( "WJetsToLNu_HT-600To800" ) ){
    xSec_ = 1.21*12.05;//47.9;
    genEvents_ = 4041997.;
  } 
  else if( sample.Contains( "WJetsToLNu_HT-800To1200" ) ){
    xSec_ = 1.21*5.501;//47.9;
    genEvents_ = 1574633.;
  } 
  else if( sample.Contains( "WJetsToLNu_HT-1200To2500" ) ){
    xSec_ = 1.21*1.329;//47.9;
    genEvents_ = 255637.;
  } 
  else if( sample.Contains( "WJetsToLNu_HT-2500ToInf" ) ){
    xSec_ = 1.21*0.03216;//47.9;
    genEvents_ = 253036.;
  } 
  else if( sample.Contains( "WJetsToLNu_HT-600ToInf" ) ){
    xSec_ = 1.21*18.77;//19.9;
    genEvents_ = 1039152.;
  } 

else if( sample.Contains( "_DYJetsToLL_" ) && sample.Contains("-madgraphMLM-")){
    xSec_ = 4895.0;
    genEvents_ = 9042031.;
  }
   
    
  else if( sample.Contains( "QCD_Pt_170to300_" ) ){
    xSec_ = 117276.;
    // genEvents_ = 3364368.;
    genEvents_ = 2582714; //OK!!!   
  }
  else if( sample.Contains( "QCD_Pt_300to470_" ) ){
    xSec_ = 7823.; //OK
    // genEvents_ = 2933611.;
    genEvents_ = 2360270; //OK!
  }
  else if( sample.Contains( "QCD_Pt_470to600_" ) ){
    xSec_ = 648.2; //OK
    // genEvents_ = 1936832.;
    genEvents_ = 1685205;   //OK!!
  }
  else if( sample.Contains( "QCD_Pt_600to800_" ) ){
    xSec_ = 186.9; //OK
    // genEvents_ = 1964128.;
    genEvents_ = 1492632; //OK!
     
  }
  else if( sample.Contains( "QCD_Pt_800to1000_" ) ){
    xSec_ = 32.293; //OK
    // genEvents_ = 1937216.;
    genEvents_ = 1863188;   //OK!
    
  }
  else if( sample.Contains( "QCD_Pt_1000to1400_" ) ){
    xSec_ = 9.4183; //OK
    // genEvents_ = 1487136.;
    genEvents_ = 1479203;   //OK!
  }  
  else if( sample.Contains( "QCD_Pt_1400to1800_" ) ){
    xSec_ = 0.84265; //OK
    // genEvents_ = 197959.;
    genEvents_ = 174095;   //OK!!
  }
  else if( sample.Contains( "QCD_Pt_1800to2400_" ) ){
    xSec_ = 0.114943; //OK
    // genEvents_ = 193608.;
    genEvents_ = 193608;    //OK!!!!
    
  }
  else if( sample.Contains( "QCD_Pt_2400to3200_" ) ){
    xSec_ = 0.006830; //OK
    genEvents_ = 194456.;   //OK!!!!
  }
  else if( sample.Contains( "QCD_Pt_3200toInf_" ) ){
    xSec_ = 0.000165445; //OK
    // genEvents_ = 192944.;
    genEvents_ = 191778;   //ok!
  }
  
  
  
  else if( sample.Contains( "WJetsToQQ_HT-600ToInf" ) ){
    xSec_ = 95.14;
    genEvents_ = 1006060.;
  }
  else if( sample.Contains( "ZJetsToQQ_HT600toInf" ) ){
    xSec_ = 5.670000;
    genEvents_ = 982095.;
  } 
  else if( sample.Contains( "QCD_HT200to300" ) ){
    xSec_ = 1735000.0;
    genEvents_ =18718905.;
  }
  else if( sample.Contains( "QCD_HT300to500" ) ){
    xSec_ = 366800.0;
    genEvents_ =19826197.;
  }
  else if( sample.Contains( "QCD_HT500to700" ) ){
    xSec_ = 29370.0;
    genEvents_ =19664159.;
  }
  else if( sample.Contains( "QCD_HT700to1000" ) ){
    xSec_ = 6524.0;
    genEvents_ = 15356448.;
  }
  else if( sample.Contains( "QCD_HT1000to1500" ) ){
    xSec_ = 1064.0;
    genEvents_ = 4963895.;
  } 
  else if( sample.Contains( "QCD_HT1500to2000" ) ){
    xSec_ = 121.5;
    genEvents_ = 3868886.;
  }
  else if( sample.Contains( "QCD_HT2000toInf" ) ){
    xSec_ = 25.42;
    genEvents_ = 1912529.;
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

  else if( sample.Contains( "_RSGravToWW_kMpl01_M-600_" ) ){
    // xSec_ = 2.37;
    xSec_ = 1.;
    // genEvents_ = 27614.; //PHYS14
    genEvents_ = 30000.;    //SPRING15
  }
  else if( sample.Contains( "_RSGravToWW_kMpl01_M-800_" ) ){
    // xSec_ = 2.37;
    xSec_ = 1.;
    // genEvents_ = 27614.; //PHYS14
    genEvents_ = 30000.;    //SPRING15
  }
  else if( sample.Contains( "_RSGravToWW_kMpl01_M-1000_" ) ){
    // xSec_ = 2.37;
    xSec_ = 1.;
    // genEvents_ = 27614.; //PHYS14
    genEvents_ = 29751.;    //SPRING15
  }
  else if( sample.Contains( "_RSGravToWW_kMpl01_M-1200_" ) ){
    // xSec_ = 2.37;
    xSec_ = 1.;
    // genEvents_ = 27614.; //PHYS14
    genEvents_ = 29176.;    //SPRING15
  }
  else if( sample.Contains( "_RSGravToWW_kMpl01_M-1400_" ) ){
    // xSec_ = 2.37;
    xSec_ = 1.;
    // genEvents_ = 27614.; //PHYS14
    genEvents_ = 30000.;    //SPRING15
  }
  else if( sample.Contains( "_RSGravToWW_kMpl01_M-1600_" ) ){
    // xSec_ = 2.37;
    xSec_ = 1.;
    // genEvents_ = 27614.; //PHYS14
    genEvents_ = 29028.;    //SPRING15
  }
  else if( sample.Contains( "_RSGravToWW_kMpl01_M-1800_" ) ){
    // xSec_ = 2.37;
    xSec_ = 1.;
    // genEvents_ = 27614.; //PHYS14
    genEvents_ = 98980.;    //SPRING15
  }
  else if( sample.Contains( "_RSGravToWW_kMpl01_M-2000_" ) ){
    // xSec_ = 0.04797;
    xSec_ = 1.;
    // genEvents_ = 39068.;
    genEvents_ = 29680.;    //SPRING15
  }
  else if( sample.Contains( "_RSGravToWW_kMpl01_M-2500_" ) ){
    xSec_ = 1.; //0.012210
    genEvents_ = 30000.;
  }
  else if( sample.Contains( "_RSGravToWW_kMpl01_M-3000_" ) ){
    // xSec_ = 0.00292;
    xSec_ = 1.0;
    // genEvents_ = 28983.;
    genEvents_ = 30000.;    //SPRING15
  }
  else if( sample.Contains( "_RSGravToWW_kMpl01_M-3500_" ) ){
    xSec_ = 1.; //0.000952
    genEvents_ = 30000.;
  }
  else if( sample.Contains( "_RSGravToWW_kMpl01_M-4000_" ) ){
    // xSec_ = 0.0002739;
    xSec_ = 1.;
    // genEvents_ = 28687.;
    genEvents_ = 30000.;    //SPRING15
  }
  else if( sample.Contains( "_RSGravToWW_kMpl01_M-4500_" ) ){
    xSec_ = 1.; //0.000094
    genEvents_ = 30000.;
  }
  else if( sample.Contains( "_RSGravToZZ_kMpl01_M-800_" ) ){
    // xSec_ = 
    xSec_ = 1.;
    genEvents_ = 29839.;    //SPRING15
  }
  else if( sample.Contains( "_RSGravToZZ_kMpl01_M-1000_" ) ){
    // xSec_ = 
    xSec_ = 1.;
    genEvents_ = 29586.;    //SPRING15
  }
  else if( sample.Contains( "_RSGravToZZ_kMpl01_M-1200_" ) ){
    // xSec_ =
    xSec_ = 1.;
    genEvents_ = 29514.;    //SPRING15
  }
  else if( sample.Contains( "_RSGravToZZ_kMpl01_M-1400_" ) ){
    // xSec_ = 
    xSec_ = 1.;
    genEvents_ = 30000.;    //SPRING15
  }
  else if( sample.Contains( "_RSGravToZZ_kMpl01_M-1600_" ) ){
    // xSec_ = 
    xSec_ = 1.;
    genEvents_ = 27803.;    //SPRING15
  }
  else if( sample.Contains( "_RSGravToZZ_kMpl01_M-1800_" ) ){
    // xSec_ = 
    xSec_ = 1.;
    genEvents_ = 100000.;    //SPRING15
  }
  else if( sample.Contains( "_RSGravToZZ_kMpl01_M-2000_" ) ){
    // xSec_ =
    xSec_ = 1.;
    genEvents_ = 29751.;    //SPRING15
  }
  else if( sample.Contains( "_RSGravToZZ_kMpl01_M-2500_" ) ){
    xSec_ = 1.; 
    genEvents_ = 30000.;
  }
  else if( sample.Contains( "_RSGravToZZ_kMpl01_M-3000_" ) ){
    // xSec_ = 
    xSec_ = 1.0;
    genEvents_ = 30000.;    //SPRING15
  }
  else if( sample.Contains( "_RSGravToZZ_kMpl01_M-3500_" ) ){
    xSec_ = 1.; 
    genEvents_ = 30000.;
  }
  else if( sample.Contains( "_RSGravToZZ_kMpl01_M-4000_" ) ){
    // xSec_ = 
    xSec_ = 1.;
    genEvents_ = 29829.;    //SPRING15
  }
  else if( sample.Contains( "_RSGravToZZ_kMpl01_M-4500_" ) ){
    xSec_ = 1.; //
    genEvents_ = 30000.;
  }

  else if( sample.Contains( "QstarToQW_M-600" ) ){
    xSec_ = 1.; //346.200000
    genEvents_ = 30000.;
  }  
  else if( sample.Contains( "QstarToQW_M-800" ) ){
    xSec_ = 1.; //108.700000
    genEvents_ = 30000.;
  }    
  else if( sample.Contains( "QstarToQW_M-1000" ) ){
    xSec_ = 1.; //108.700000
    genEvents_ = 29836.;
  }  
  else if( sample.Contains( "QstarToQW_M-1200" ) ){
    xSec_ = 1.; //65.840000
    genEvents_ = 30000.;
  } 
  else if( sample.Contains( "QstarToQW_M-1400" ) ){
    xSec_ = 1.; //41.760000
    genEvents_ = 29823.;
  } 
  else if( sample.Contains( "QstarToQW_M-1600" ) ){
    xSec_ = 1.; //108.700000
    genEvents_ = 30000.;
  } 
  else if( sample.Contains( "QstarToQW_M-1800" ) ){
    xSec_ = 1.; //18.120000
    genEvents_ = 30000.;
  } 
  else if( sample.Contains( "QstarToQW_M-2000" ) ){
    xSec_ = 1.; // 12.190000
    genEvents_ = 30000.;
  } 
  else if( sample.Contains( "QstarToQW_M-2500" ) ){
    xSec_ = 1.; //4.835000
    genEvents_ = 30000.;
  } 
  else if( sample.Contains( "QstarToQW_M-3000" ) ){
    xSec_ = 1.; //2.016000
    genEvents_ = 30000.;
  } 
  else if( sample.Contains( "QstarToQW_M-3500" ) ){
    xSec_ = 1.; // 0.873300
    genEvents_ = 30000.;
  } 
  else if( sample.Contains( "QstarToQW_M-4500" ) ){
    xSec_ = 1.; // 0.425500
    genEvents_ = 30000.;
  }
  else if( sample.Contains( "QstarToQW_M-4500" ) ){
    xSec_ = 1.; //0.219900
    genEvents_ = 28965.;
  }
  else if( sample.Contains( "QstarToQW_M-5000" ) ){
    xSec_ = 1.; //0.124400
    genEvents_ = 30000.;
  }   
  else if( sample.Contains( "QstarToQW_M-6000" ) ){
    xSec_ = 1.; //0.048910
    genEvents_ = 28130.;
  }  
  else if( sample.Contains( "QstarToQW_M-7000" ) ){
    xSec_ = 1.; //
    genEvents_ = 30000.;
  }

  else if( sample.Contains( "QstarToQZ_M-600" ) ){
    xSec_ = 1.; //
    genEvents_ = 30000.;
  } 
  else if( sample.Contains( "QstarToQZ_M-800" ) ){
    xSec_ = 1.; //
    genEvents_ = 29704.;
  } 
  else if( sample.Contains( "QstarToQZ_M-1000" ) ){
    xSec_ = 1.; //
    genEvents_ = 30000.;
  } 
  else if( sample.Contains( "QstarToQZ_M-1200" ) ){
    xSec_ = 1.; //
    genEvents_ = 30000.;
  } 
  else if( sample.Contains( "QstarToQZ_M-1400" ) ){
    xSec_ = 1.; //
    genEvents_ = 27912.;
  } 
  else if( sample.Contains( "QstarToQZ_M-1600" ) ){
    xSec_ = 1.; //
    genEvents_ = 30000.;
  } 
  else if( sample.Contains( "QstarToQZ_M-1800" ) ){
    xSec_ = 1.; //
    genEvents_ = 30000.;
  } 
  else if( sample.Contains( "QstarToQZ_M-2000" ) ){
    xSec_ = 1.; //
    genEvents_ = 30000.;
  } 
  else if( sample.Contains( "QstarToQZ_M-2500" ) ){
    xSec_ = 1.; //
    genEvents_ = 30000.;
  } 
  else if( sample.Contains( "QstarToQZ_M-3000" ) ){
    xSec_ = 1.; //
    genEvents_ = 30000.;
  } 
  
  else if( sample.Contains( "QstarToQZ_M-3500" ) ){
    xSec_ = 1.; //0.316400
    genEvents_ = 29260.;
  } 
  else if( sample.Contains( "QstarToQZ_M-4000" ) ){
    xSec_ = 1.; //0.152600
    genEvents_ = 30000.;
  } 
  else if( sample.Contains( "QstarToQZ_M-4500" ) ){
    xSec_ = 1.; //
    genEvents_ = 30000.;
  }   
  else if( sample.Contains( "QstarToQZ_M-5000" ) ){
    xSec_ = 1.; //
    genEvents_ = 30000.;
  }     
  else if( sample.Contains( "QstarToQZ_M-6000" ) ){
    xSec_ = 1.; //
    genEvents_ = 29809.;
  }  
  else if( sample.Contains( "QstarToQZ_M-7000" ) ){
    xSec_ = 1.; //
    genEvents_ = 30000.;
  }    
  else if( sample.Contains( "BulkGravToWW_narrow_M-600" ) ){
    xSec_ = 1.;
    genEvents_ = 30000.;   
  }
  else if( sample.Contains( "BulkGravToWW_narrow_M-800" ) ){
    xSec_ = 1.;
    genEvents_ = 30000.;   
  }
  else if( sample.Contains( "BulkGravToWW_narrow_M-1000" ) ){
    xSec_ = 1.;
    genEvents_ = 30000.;   
  }
  else if( sample.Contains( "BulkGravToWW_narrow_M-1200" ) ){
    xSec_ = 1.;
    genEvents_ = 30000.;   
  }
  else if( sample.Contains( "BulkGravToWW_narrow_M-1400" ) ){
    xSec_ = 1.;
    genEvents_ = 30000.;   
  }
  else if( sample.Contains( "BulkGravToWW_narrow_M-1600" ) ){
    xSec_ = 1.;
    genEvents_ = 29000.;   
  }
  else if( sample.Contains( "BulkGravToWW_narrow_M-1800" ) ){
    xSec_ = 1.;
    genEvents_ = 30000.;   
  }
  else if( sample.Contains( "BulkGravToWW_narrow_M-2000" ) ){
    xSec_ = 1.;
    genEvents_ = 30000.;   
  }
  else if( sample.Contains( "BulkGravToWW_narrow_M-2500" ) ){
    xSec_ = 1.;
    genEvents_ = 30000.;   
  }
  else if( sample.Contains( "BulkGravToWW_narrow_M-3000" ) ){
    xSec_ = 1.;
    genEvents_ = 30000.;   
  }
  else if( sample.Contains( "BulkGravToWW_narrow_M-3500" ) ){
    xSec_ = 1.;
    genEvents_ = 30000.;   
  }
  else if( sample.Contains( "BulkGravToWW_narrow_M-4000" ) ){
    xSec_ = 1.;
    genEvents_ = 30000.;
  }
  else if( sample.Contains( "BulkGravToWW_narrow_M-4500" ) ){
    xSec_ = 1.;
    genEvents_ = 30000.;
  }
  else if( sample.Contains( "_QCD_Pt-15TTo7000_" ) ){
    xSec_ = 89731000000.;
    genEvents_ = 9755422.;
  } 
  else if( sample.Contains( "WprimeToWZ_M-1000" ) ){
    xSec_ = 1.;
    genEvents_ = 29388.;
  }
  else if( sample.Contains( "WprimeToWZ_M-1200" ) ){
    xSec_ = 1.;
    genEvents_ = 30000.;
  }
  else if( sample.Contains( "WprimeToWZ_M-1400" ) ){
    xSec_ = 1.;
    genEvents_ = 30000.;
  }
  else if( sample.Contains( "WprimeToWZ_M-1600" ) ){
    xSec_ = 1.;
    genEvents_ = 30000.;
  }
  else if( sample.Contains( "WprimeToWZ_M-1800" ) ){
    xSec_ = 1.;
    genEvents_ = 100000.;
  }
  else if( sample.Contains( "WprimeToWZ_M-2000" ) ){
    xSec_ = 1.;
    genEvents_ = 30000.;
  }
  else if( sample.Contains( "WprimeToWZ_M-2500" ) ){
    xSec_ = 1.;
    genEvents_ = 30000.;
  }
  else if( sample.Contains( "WprimeToWZ_M-3000" ) ){
    xSec_ = 1.;
    genEvents_ = 30000.;
  }
  else if( sample.Contains( "WprimeToWZ_M-3500" ) ){
    xSec_ = 1.;
    genEvents_ = 30000.;
  }
  else if( sample.Contains( "WprimeToWZ_M-4000" ) ){
    xSec_ = 1.;
    genEvents_ = 30000.;
  }
  else if( sample.Contains( "WprimeToWZ_M-4500" ) ){
    xSec_ = 1.;
    genEvents_ = 29690.;
  }
  
  else if( sample.Contains( "BulkGravToZZ_narrow_M-1000" ) ){
    xSec_ = 1.;
    genEvents_ = 30000.;
  }
  else if( sample.Contains( "BulkGravToZZ_narrow_M-1200" ) ){
    xSec_ = 1.;
    genEvents_ = 30000.;
  }
  else if( sample.Contains( "BulkGravToZZ_narrow_M-1400" ) ){
    xSec_ = 1.;
    genEvents_ = 30000.;
  }
  else if( sample.Contains( "BulkGravToZZ_narrow_M-1600" ) ){
    xSec_ = 1.;
    genEvents_ = 30000.;
  }
  else if( sample.Contains( "BulkGravToZZ_narrow_M-1800" ) ){
    xSec_ = 1.;
    genEvents_ = 30000.;
  }
  else if( sample.Contains( "BulkGravToZZ_narrow_M-2000" ) ){
    xSec_ = 1.;
    genEvents_ = 29200.;
  }
  else if( sample.Contains( "BulkGravToZZ_narrow_M-2500" ) ){
    xSec_ = 1.;
    genEvents_ = 28800.;
  }
  else if( sample.Contains( "BulkGravToZZ_narrow_M-3000" ) ){
    xSec_ = 1.;
    genEvents_ = 30000.;
  }
  else if( sample.Contains( "BulkGravToZZ_narrow_M-3500" ) ){
    xSec_ = 1.;
    genEvents_ = 30000.;
  }
  else if( sample.Contains( "BulkGravToZZ_narrow_M-4000" ) ){
    xSec_ = 1.;
    genEvents_ = 30000.;
  }
  else if( sample.Contains( "BulkGravToZZ_narrow_M-4500" ) ){
    xSec_ = 1.;
    genEvents_ = 29200.;
  }
  else if( sample.Contains( "WprimeToWZToWhadZhad_narrow_M-1000" ) ){
    xSec_ = 1.;
    genEvents_ = 30000.;
  }
  else if( sample.Contains( "WprimeToWZToWhadZhad_narrow_M-1200" ) ){
    xSec_ = 1.;
    genEvents_ = 30000.;
  }
  else if( sample.Contains( "WprimeToWZToWhadZhad_narrow_M-1400" ) ){
    xSec_ = 1.;
    genEvents_ = 30000.;
  }
  else if( sample.Contains( "WprimeToWZToWhadZhad_narrow_M-1600" ) ){
    xSec_ = 1.;
    genEvents_ = 30000.;
  }
  else if( sample.Contains( "WprimeToWZToWhadZhad_narrow_M-1800" ) ){
    xSec_ = 1.;
    genEvents_ = 30000.;
  }
  else if( sample.Contains( "WprimeToWZToWhadZhad_narrow_M-2000" ) ){
    xSec_ = 1.;
    genEvents_ = 30000.;
  }
  else if( sample.Contains( "WprimeToWZToWhadZhad_narrow_M-2500" ) ){
    xSec_ = 1.;
    genEvents_ = 30000.;
  }
  else if( sample.Contains( "WprimeToWZToWhadZhad_narrow_M-3000" ) ){
    xSec_ = 1.;
    genEvents_ = 30000.;
  }
  else if( sample.Contains( "WprimeToWZToWhadZhad_narrow_M-3500" ) ){
    xSec_ = 1.;
    genEvents_ = 30000.;
  }
  else if( sample.Contains( "WprimeToWZToWhadZhad_narrow_M-4000" ) ){
    xSec_ = 1.;
    genEvents_ = 30000.;
  }
  else if( sample.Contains( "WprimeToWZToWhadZhad_narrow_M-4500" ) ){
    xSec_ = 1.;
    genEvents_ = 30000.;
  }
  
  
  else if( sample.Contains( "ZprimeToWW_narrow_M-1000" ) ){
    xSec_ = 1.;
    genEvents_ = 30000.;
  }
  else if( sample.Contains( "ZprimeToWW_narrow_M-1200" ) ){
    xSec_ = 1.;
    genEvents_ = 30000.;
  }
  else if( sample.Contains( "ZprimeToWW_narrow_M-1400" ) ){
    xSec_ = 1.;
    genEvents_ = 30000.;
  }
  else if( sample.Contains( "ZprimeToWW_narrow_M-1600" ) ){
    xSec_ = 1.;
    genEvents_ = 30000.;
  }
  else if( sample.Contains( "ZprimeToWW_narrow_M-1800" ) ){
    xSec_ = 1.;
    genEvents_ = 30000.;
  }
  else if( sample.Contains( "ZprimeToWW_narrow_M-2000" ) ){
    xSec_ = 1.;
    genEvents_ = 30000.;
  }
  else if( sample.Contains( "ZprimeToWW_narrow_M-2500" ) ){
    xSec_ = 1.;
    genEvents_ = 30000.;
  }
  else if( sample.Contains( "ZprimeToWW_narrow_M-3000" ) ){
    xSec_ = 1.;
    genEvents_ = 30000.;
  }
  else if( sample.Contains( "ZprimeToWW_narrow_M-3500" ) ){
    xSec_ = 1.;
    genEvents_ = 30000.;
  }
  else if( sample.Contains( "ZprimeToWW_narrow_M-4000" ) ){
    xSec_ = 1.;
    genEvents_ = 30000.;
  }
  else if( sample.Contains( "ZprimeToWW_narrow_M-4500" ) ){
    xSec_ = 1.;
    genEvents_ = 30000.;
  }
}
  
   // std::cout<< "Lumi weight: XSEC/GENEVENTS = " << xSec_ << "/" << genEvents_ << std::endl;

  return xSec_/genEvents_;
  
      
}
