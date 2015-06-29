#ifndef VCANDIDATE_H
#define VCANDIDATE_H

#include "../ExoDiBosonAnalysis/include/RecoCandidate.h"

class VCandidate : public RecoCandidate {

public:
   VCandidate( TLorentzVector tlv );
   ~VCandidate( void );
      
private:

};

#endif // VCANDIDATE_H