#ifndef FUN4ALLHEPMCPILEUPINPUTMANAGER_H__
#define FUN4ALLHEPMCPILEUPINPUTMANAGER_H__

#include "Fun4AllHepMCInputManager.h"

#include <fun4all/Fun4AllReturnCodes.h>

#include <string>
#include <map>
#include <fstream>
#include <iostream>

// forward declaration of classes in namespace
namespace HepMC
{
    class IO_GenEvent;
    class GenEvent;
};

class PHCompositeNode;

class Fun4AllHepMCPileupInputManager : public Fun4AllHepMCInputManager
{
 public:
  Fun4AllHepMCPileupInputManager(const std::string &name = "DUMMY", const std::string &nodename = "DST", const std::string &topnodename = "TOP");
  virtual ~Fun4AllHepMCPileupInputManager();

  int run(const int nevents = 0);

 protected:

};

#endif /* __FUN4ALLHEPMCINPUTMANAGER_H__ */
