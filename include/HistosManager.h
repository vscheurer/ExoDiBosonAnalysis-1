#ifndef HISTOSMANAGER_H
#define HISTOSMANAGER_H
#include <string>

class ExoDiBosonAnalysis;

class HistosManager {

public:
   HistosManager( ExoDiBosonAnalysis * theAnalysis);
   ~HistosManager( void );

   void bookHistos       ( std::string Channel  );
   void formatHistos     ( std::string Channel  );
   
private:
   ExoDiBosonAnalysis* theAnalysis_;
   std::string         Channel_;
   
};

#endif // HISTOSMANAGER_H
