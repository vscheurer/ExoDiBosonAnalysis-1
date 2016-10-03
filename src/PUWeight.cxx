#include "include/PUWeight.h"

#include "TFile.h"

#include <iostream>

//==============================================================================================
// Get MC pile-up scenario from string representation
PUWeight::Scenario PUWeight::toScenario(const std::string& str) {
  PUWeight::Scenario sc = Winter15_25ns;
  if( str == "PUS25ns" ) sc = Winter15_25ns;
  else if( str == "PUS25ns76X" )sc = Fall15_25ns;
  else if( str == "PUS25ns80X" )sc = Spring16_25ns;
  else {
    std::cerr << "\n\nERROR unknown scenario '" << str << "'" << std::endl;
    throw std::exception();
  }

  return sc;
}

//==============================================================================================
// MC pile-up scenario to string representation
std::string PUWeight::toString(const PUWeight::Scenario sc) {
  std::string str;
  if     ( sc == Winter15_25ns) str = "PUS25ns";
  else if( sc == Fall15_25ns  ) str = "PUS25ns76X";
  else if( sc == Spring16_25ns) str = "PUS25ns80X";
  else {
    std::cerr << "\n\nERROR unknown scenario '" << sc << "'" << std::endl;
    throw std::exception();
  }

  return str;
}

//==============================================================================================
// Constructor. Initializes default behaviour to return PU weight of 1
PUWeight::PUWeight()
  : isInit_(false), nPUMax_(0) {}

//==============================================================================================
// Initialise weights for a given MC pile-up scenario. Can only be
// called once.
void PUWeight::initPUWeights(const std::string& nameOfDataDistribution, const PUWeight::Scenario sc) {

  if( isInit_ ) {
    std::cerr << "\n\nERROR in PUWeight: weights already initialised" << std::endl;
    // throw std::exception();
  }

  // Get data distribution from file
  TFile file(nameOfDataDistribution.c_str(), "READ");
  TH1* h = NULL;
  file.GetObject("pileup",h);
  if( h == NULL ) {
    std::cerr << "\n\nERROR in PUWeight: Histogram 'pileup' does not exist in file '" << nameOfDataDistribution << "'\n.";
    throw std::exception();
  }
  h->SetDirectory(0);
  file.Close();

  // Computing weights
  puWeigths_ = generateWeights(sc,h);
  nPUMax_ = puWeigths_.size();

  // Clean up
  delete h;

  isInit_ = true;
}

//==============================================================================================
// Get weight factor dependent on number of added PU interactions
double PUWeight::getPUWeight(const int nPU) const {

  double w = 1.;
  if( isInit_ ) {
    if( nPU >= nPUMax_ ) {
      //std::cerr << "WARNING: Number of PU vertices = " << nPU << " out of histogram binning." << std::endl;
      // In case nPU is out-of data-profile binning,
      // use weight from last bin
      w = puWeigths_.back();
    } else {
      w = puWeigths_.at(nPU);
    }
  }

  return w;
}

//==============================================================================================
// Generate weights for given data PU distribution
// Scenarios from: https://twiki.cern.ch/twiki/bin/view/CMS/Pileup_MC_Gen_Scenarios
// Code adapted from: https://twiki.cern.ch/twiki/bin/viewauth/CMS/PileupReweighting
std::vector<double> PUWeight::generateWeights(const PUWeight::Scenario sc, const TH1* data_npu_estimated) const {

  // Store probabilites for each pu bin
  unsigned int nPUMax = 0;
  double *npuProbs = 0;

  if( sc == Winter15_25ns ) {
    std::cout<<"IN WINTER 15!!!!"<<std::endl;
  
    nPUMax = 52;
    double npuWinter15_25ns[52] = {
      4.8551E-07,
      1.74806E-06,
      3.30868E-06,
      1.62972E-05,
      4.95667E-05,
      0.000606966,
      0.003307249,
      0.010340741,
      0.022852296,
      0.041948781,
      0.058609363,
      0.067475755,
      0.072817826,
      0.075931405,
      0.076782504,
      0.076202319,
      0.074502547,
      0.072355135,
      0.069642102,
      0.064920999,
      0.05725576,
      0.047289348,
      0.036528446,
      0.026376131,
      0.017806872,
      0.011249422,
      0.006643385,
      0.003662904,
      0.001899681,
      0.00095614,
      0.00050028,
      0.000297353,
      0.000208717,
      0.000165856,
      0.000139974,
      0.000120481,
      0.000103826,
      8.88868E-05,
      7.53323E-05,
      6.30863E-05,
      5.21356E-05,
      4.24754E-05,
      3.40876E-05,
      2.69282E-05,
      2.09267E-05,
      1.5989E-05,
      4.8551E-06,
      2.42755E-06,
      4.8551E-07,
      2.42755E-07,
      1.21378E-07,
      4.8551E-08};
      npuProbs = npuWinter15_25ns;
      std::cout<<"npuWinter15_25ns[0] = " << npuWinter15_25ns[0] <<"    npuProbs[0] = "<<npuProbs[0]<<std::endl;
    }
  
    else if( sc == Fall15_25ns ) {   //from https://github.com/cms-sw/cmssw/blob/CMSSW_7_6_X/SimGeneral/MixingModule/python/mix_2015_25ns_FallMC_matchData_PoissonOOTPU_cfi.py
      std::cout<<"IN FALL 15!!!!"<<std::endl;
  
      nPUMax = 50;
      double npuFall15_25ns[50] = {
        0.000108643,
        0.000388957,
        0.000332882,
        0.00038397,
        0.000549167,
        0.00105412,
        0.00459007,
        0.0210314,
        0.0573688,
        0.103986,
        0.142369,
        0.157729,
        0.147685,
        0.121027,
        0.08855,
        0.0582866,
        0.0348526,
        0.019457,
        0.0107907,
        0.00654313,
        0.00463195,
        0.00370927,
        0.0031137,
        0.00261141,
        0.00215499,
        0.00174491,
        0.00138268,
        0.00106731,
        0.000798828,
        0.00057785,
        0.00040336,
        0.00027161,
        0.000176535,
        0.00011092,
        6.75502e-05,
        4.00323e-05,
        2.32123e-05,
        1.32585e-05,
        7.51611e-06,
        4.25902e-06,
        2.42513e-06,
        1.39077e-06,
        8.02452e-07,
        4.64159e-07,
        2.67845e-07,
        1.5344e-07,
        8.68966e-08,
        4.84931e-08,
        2.6606e-08,
        1.433e-08}; 
        npuProbs = npuFall15_25ns;
        std::cout<<"npuFall15_25ns[0] = " << npuFall15_25ns[0] <<"    npuProbs[0] = "<<npuProbs[0]<<std::endl;
      }
      else if( sc == Spring16_25ns ) {   //from https://github.com/cms-sw/cmssw/blob/CMSSW_8_1_X/SimGeneral/MixingModule/python/mix_2016_25ns_SpringMC_PUScenarioV1_PoissonOOTPU_cfi.py
        std::cout<<"IN SPRING 16!!!!"<<std::endl;
  
        nPUMax = 50;
        double npuSpring16_25ns[50] = {
          0.000829312873542,
           		0.00124276120498,
           		0.00339329181587,
           		0.00408224735376,
           		0.00383036590008,
          		0.00659159288946,
           		0.00816022734493,
           		0.00943640833116,
           		0.0137777376066,
           		0.017059392038,
           		0.0213193035468,
           		0.0247343174676,
           		0.0280848773878,
           		0.0323308476564,
           		0.0370394341409,
           		0.0456917721191,
           		0.0558762890594,
           		0.0576956187107,
           		0.0625325287017,
           		0.0591603758776,
           		0.0656650815128,
           		0.0678329011676,
           		0.0625142146389,
           		0.0548068448797,
           		0.0503893295063,
           		0.040209818868,
           		0.0374446988111,
           		0.0299661572042,
           		0.0272024759921,
           		0.0219328403791,
           		0.0179586571619,
           		0.0142926728247,
           		0.00839941654725,
           		0.00522366397213,
           		0.00224457976761,
           		0.000779274977993,
           		0.000197066585944,
           		7.16031761328e-05,
           		0.0,
          		0.0,
          		0.0,
          		0.0,
          		0.0,
          		0.0,
          		0.0,
          		0.0,
          		0.0,
           		0.0,
           		0.0,
           		0.0
            }; 
          npuProbs = npuSpring16_25ns;
          std::cout<<"npuSpring16_25ns[0] = " << npuSpring16_25ns[0] <<"    npuProbs[0] = "<<npuProbs[0]<<std::endl;
        } 

      // Check that binning of data-profile matches MC scenario
      if( nPUMax != static_cast<unsigned int>(data_npu_estimated->GetNbinsX()) ) {
        std::cerr << "\n\nERROR number of bins (" << data_npu_estimated->GetNbinsX() << ") in data PU-profile does not match number of bins (" << nPUMax << ") in MC scenario " << toString(sc) << std::endl;
        throw std::exception();
      }

      std::vector<double> result(nPUMax,0.);
      double s = 0.;
      for(unsigned int npu = 0; npu < nPUMax; ++npu) {
        const double npu_estimated = data_npu_estimated->GetBinContent(data_npu_estimated->GetXaxis()->FindBin(npu));
        result[npu] = npu_estimated / npuProbs[npu];
        s += npu_estimated;
      }
      // normalize weights such that the total sum of weights over thw whole sample is 1.0, i.e., sum_i  result[i] * npu_probs[i] should be 1.0 (!)
      for(unsigned int npu = 0; npu < nPUMax; ++npu) {
        result[npu] /= s;
      }

      return result;
    }

