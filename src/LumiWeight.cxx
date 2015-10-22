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
   
  //lumi weights for 50ns samples 
  if( sample.Contains("50ns") ){
    
    if( sample.Contains( "QCD_Pt_170to300_" ) ){
      xSec_ = 117276.;
      genEvents_ = 3438066.;   
    }
    else if( sample.Contains( "QCD_Pt_300to470_" ) ){
      xSec_ = 7823.;
      genEvents_ = 2630578.;   
    }
    else if( sample.Contains( "QCD_Pt_470to600_" ) ){
      xSec_ = 648.2;
      genEvents_ = 1939229.;   
    }
    else if( sample.Contains( "QCD_Pt_600to800_" ) ){
      xSec_ = 186.9;
      genEvents_ = 1890256.;   
    }
    else if( sample.Contains( "QCD_Pt_800to1000_" ) ){
      xSec_ = 32.293;
      genEvents_ = 1911296.;   
    }
    else if( sample.Contains( "QCD_Pt_1000to1400_" ) ){
      xSec_ = 9.4183;
      genEvents_ = 1461216.;   
    }  
    else if( sample.Contains( "QCD_Pt_1400to1800_" ) ){
      xSec_ = 0.84265;
      genEvents_ = 197959.;   
    }
    else if( sample.Contains( "QCD_Pt_1800to2400_" ) ){
      xSec_ = 0.114943;
      genEvents_ = 194924.;   
    }
    else if( sample.Contains( "QCD_Pt_2400to3200_" ) ){
      xSec_ = 0.006830;
      genEvents_ = 198383.;   
    }
    else if( sample.Contains( "QCD_Pt_3200toInf_" ) ){
      xSec_ = 0.000165;
      genEvents_ = 188696.;   
    }
    //single top samples
    if( sample.Contains( "ST_t-channel_top" ) ){
      xSec_ = 136.02*0.322;
      genEvents_ = 1273800.;      
    }
    else if( sample.Contains( "ST_t-channel_antitop" ) ){
      xSec_ = 80.95*0.322;
      genEvents_ = 681900.;                
    }
    else if( sample.Contains( "ST_tW_top" ) ){
      xSec_ = 35.6;
      genEvents_ = 998400.;                
    }   
    else if( sample.Contains( "ST_tW_antitop" ) ){
      xSec_ = 35.6;
      genEvents_ = 1000000.;                
    }      
    //VV samples
    else if( sample.Contains( "_WW_" ) ){
      xSec_ = 118.7;
      genEvents_ = 989608.;
    }
    else if( sample.Contains( "_WZ_" ) ){
      xSec_ = 66.1;
      genEvents_ = 996920.;
    }
    else if( sample.Contains( "_ZZ_" ) ){
      xSec_ = 15.4;
      genEvents_ = 998848.;
    } 	
    //W+Jets samples
    else if( sample.Contains( "WJetsToLNu" ) && !sample.Contains("_HT-") ){
      xSec_ = 61526.7;
      genEvents_ = 24089991.;
    }
    //TTbar samples 
    else if( sample.Contains( "TTJets" ) && sample.Contains( "amcatnlo" ) ){
      xSec_ = 831.76;
      genEvents_ = 4994250.;
    } 
    else if( sample.Contains( "TT_" ) && sample.Contains( "powheg" ) ){
      xSec_ = 831.76;
      genEvents_ = 19665194.;
    } 
    else if( sample.Contains( "DYJetsToLL" ) ){
      xSec_ = 6104.0;
      genEvents_ = 19925500.;
      // v3 = 28825132.
    }                 
  }     
        
  //25 ns samples
  else{
    
    if( sample.Contains( "QCD_Pt_170to300_" ) ){
      xSec_ = 117276.;
      genEvents_ = 3364368.;   
    }
    else if( sample.Contains( "QCD_Pt_300to470_" ) ){
      xSec_ = 7823.;
      genEvents_ = 2933611.;   
    }
    else if( sample.Contains( "QCD_Pt_470to600_" ) ){
      xSec_ = 648.2;
      genEvents_ = 1936832.;   
    }
    else if( sample.Contains( "QCD_Pt_600to800_" ) ){
      xSec_ = 186.9;
      genEvents_ = 1964128.;   
    }
    else if( sample.Contains( "QCD_Pt_800to1000_" ) ){
      xSec_ = 32.293;
      genEvents_ = 1937216.;   
    }
    else if( sample.Contains( "QCD_Pt_1000to1400_" ) ){
      xSec_ = 9.4183;
      genEvents_ = 1487136.;   
    }  
    else if( sample.Contains( "QCD_Pt_1400to1800_" ) ){
      xSec_ = 0.84265;
      genEvents_ = 197959.;   
    }
    else if( sample.Contains( "QCD_Pt_1800to2400_" ) ){
      xSec_ = 0.114943;
      genEvents_ = 193608.;   
    }
    else if( sample.Contains( "QCD_Pt_2400to3200_" ) ){
      xSec_ = 0.006830;
      genEvents_ = 194456.;   
    }
    else if( sample.Contains( "QCD_Pt_3200toInf_" ) ){
      xSec_ = 0.000165;
      genEvents_ = 192944.;   
    }
    else if( sample.Contains( "ST_t-channel_top" ) ){
       xSec_ = 136.02*0.322;
       genEvents_ = 3299800.;
    }  
    else if( sample.Contains( "ST_t-channel_antitop" ) ){
       xSec_ = 80.95*0.322;
       genEvents_ = 1695400.;
    }         
    else if( sample.Contains( "ST_s-channel" ) ){
       xSec_ = 11.36*0.322;
       //genEvents_ = 984400.; //das
       genEvents_ = 613384.; //genweights
    }	  
    else if( sample.Contains( "ST_t-channel" ) && !(sample.Contains("top") || sample.Contains("antitop")) ){
       xSec_ = 216.99*0.322;
       genEvents_ = 2966200.;
    }	
    else if( sample.Contains( "ST_tW_top" ) ){
       xSec_ = 35.6;
       genEvents_ = 995600.;
    } 
    else if( sample.Contains( "ST_tW_antitop" ) ){
       xSec_ = 35.6;
       genEvents_ = 1000000.;
    }   
    else if( sample.Contains( "TTJets" ) ){
       xSec_ = 831.76;
       //genEvents_ = 42730273.; //das
       genEvents_ = 14170480.; //genweights
    }
    else if( sample.Contains( "TT" ) && sample.Contains("powheg") ){
       xSec_ = 831.76;
       genEvents_ = 19899500.;
    }
    else if( sample.Contains( "_WW_" ) ){
       xSec_ = 118.7;
       genEvents_ = 994416.;
    }
    else if( sample.Contains( "_WZ_" ) ){
       xSec_ = 47.13;//66.1;
       genEvents_ = 991232.;
    }
    else if( sample.Contains( "_ZZ_" ) ){
       xSec_ = 16.5;//15.4;
       genEvents_ = 996168.;
    }      
    else if( sample.Contains( "WJetsToLNu_HT-100To200" ) ){
       xSec_ = 1.21*1347.;//1292.;
       genEvents_ = 10142187.;
    } 
    else if( sample.Contains( "WJetsToLNu_HT-200To400" ) ){
       xSec_ = 1.21*360.;//385.9;
       genEvents_ = 5231856.;
    } 
    else if( sample.Contains( "WJetsToLNu_HT-400To600" ) ){
       xSec_ = 1.21*48.9;//47.9;
       genEvents_ = 1901705.;
    } 
    else if( sample.Contains( "WJetsToLNu_HT-600ToInf" ) ){
       xSec_ = 1.21*18.77;//19.9;
       genEvents_ = 1036108.;
    } 	 
    else if( sample.Contains( "WJetsToLNu" ) && !sample.Contains("_HT-") ){
       xSec_ = 61526.7;
       genEvents_ = 24151270.;
    }
    else if( sample.Contains( "DYJetsToLL" ) ){
      xSec_ = 6104.0;
      genEvents_ = 28825132.;
      // v3 = 28825132.
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
    
  }
    
  if( sample.Contains( "_RSGravToWW_kMpl01_M-600_" ) ){
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
    xSec_ = 6104.;
    genEvents_ = 28825132.;
  }
   
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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
   

  // std::cout<<"sample == "<<sample<<std::endl;
  // std::cout<<"xSec_ == "<<xSec_<<std::endl;
  // std::cout<<"genevents == "<<genEvents_<<std::endl;
   	                                     
  return xSec_/genEvents_;
      
}
